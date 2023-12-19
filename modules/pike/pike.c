/*
 * PIKE module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Marina.Rodeo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * History:
 * --------
 *  2003-03-11  updated to the new module exports interface (andrei)
 *  2003-03-11  converted to the new locking interface: locking.h --
 *               major changes (andrei)
 *  2003-03-16  flags export parameter added (janakj)
 *  2008-04-17  new parameter to control the module's log regarding the
 *               blocking/unblocking of IPs (bogdan)
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "../../sr_module.h"
#include "../../error.h"
#include "../../dprint.h"
#include "../../script_cb.h"
#include "../../ut.h"
#include "../../mem/shm_mem.h"
#include "../../evi/evi_modules.h"
#include "../../timer.h"
#include "../../locking.h"
#include "../../status_report.h"
#include "ip_tree.h"
#include "timer.h"
#include "pike_mi.h"
#include "pike_funcs.h"





static int pike_init(void);
static int pike_exit(void);



/* parameters */
static int time_unit = 2;
static int max_reqs  = 30;
static char *pike_route_s = NULL;
int timeout   = 120;
int pike_log_level = L_WARN;

/* global variables */
gen_lock_t*             timer_lock=0;
struct list_link*       timer = 0;

/* event id */
static str pike_block_event = str_init("E_PIKE_BLOCKED");
event_id_t pike_event_id = EVI_ERROR;

/* status/repport group */
void *pike_srg;

static const cmd_export_t cmds[]={
	{"pike_check_req", (cmd_function)pike_check_req, {{0,0,0}},
		REQUEST_ROUTE},
	{0,0,{{0,0,0}},0}
};

static const param_export_t params[]={
	{"sampling_time_unit",    INT_PARAM,  &time_unit},
	{"reqs_density_per_unit", INT_PARAM,  &max_reqs},
	{"remove_latency",        INT_PARAM,  &timeout},
	{"pike_log_level",        INT_PARAM,  &pike_log_level},
	{"check_route",           STR_PARAM,  &pike_route_s},
	{0,0,0}
};

static const mi_export_t mi_cmds [] = {
	{MI_PIKE_LIST, "lists the nodes in the pike tree", 0, 0, {
		{mi_pike_list, {0}},
		{EMPTY_MI_RECIPE}}
	},
	{MI_PIKE_RM, "remove a node from the tree", 0, 0, {
		{mi_pike_rm, {"ip", 0}},
		{EMPTY_MI_RECIPE}}
	},
	{EMPTY_MI_EXPORT}
};

struct module_exports exports= {
	"pike",
	MOD_TYPE_DEFAULT,/* class of this module */
	MODULE_VERSION,
	DEFAULT_DLFLAGS, /* dlopen flags */
	0,				 /* load function */
	NULL,            /* Marina.Rodeo module dependencies */
	cmds,
	0,
	params,
	0,           /* exported statistics */
	mi_cmds,     /* exported MI functions */
	0,           /* exported pseudo-variables */
	0,			 /* exported transformations */
	0,           /* extra processes */
	0,           /* module pre-initialization function */
	pike_init,   /* module initialization function */
	(response_function) 0,
	(destroy_function) pike_exit,   /* module exit function */
	0,           /* per-child init function */
	0            /* reload confirm function */
};




static int pike_init(void)
{
	struct script_route_ref *rt;

	LM_INFO("initializing...\n");

	if (timeout <= time_unit) {
		LM_WARN("remove_latency smaller than sampling_time_unit! "
				"Having a smaller or equal value for remove_latency may "
				"lead to missing UNBLOCK events!\n");
		timeout = time_unit + 1;
		LM_NOTICE("Forcing remove_latency to %ds\n", timeout);
	}

	/* alloc the timer lock */
	timer_lock=lock_alloc();
	if (timer_lock==0) {
		LM_ERR(" alloc locks failed!\n");
		goto error1;
	}
	/* init the lock */
	if (lock_init(timer_lock)==0){
		LM_ERR(" init lock failed\n");
		goto error1;
	}

	/* init the IP tree */
	if ( init_ip_tree(max_reqs)!=0 ) {
		LM_ERR(" ip_tree creation failed!\n");
		goto error2;
	}

	/* init timer list */
	timer = (struct list_link*)shm_malloc(sizeof(struct list_link));
	if (timer==0) {
		LM_ERR(" cannot alloc shm mem for timer!\n");
		goto error3;
	}
	timer->next = timer->prev = timer;

	/* registering timing functions  */
	register_timer( "pike-clean", clean_routine , 0, 1 ,
		TIMER_FLAG_DELAY_ON_DELAY);
	register_timer( "pike-swap", swap_routine , 0, time_unit,
		TIMER_FLAG_DELAY_ON_DELAY );

	if (pike_route_s && *pike_route_s) {
		rt = ref_script_route_by_name( pike_route_s, sroutes->request,
			RT_NO, REQUEST_ROUTE, 0);
		if ( !ref_script_route_is_valid(rt) ) {
			LM_ERR("route <%s> does not exist\n",pike_route_s);
			return -1;
		}

		/* register the script callback to get all requests and replies */
		if (register_script_cb( run_pike_route ,
		PARSE_ERR_CB|REQ_TYPE_CB|RPL_TYPE_CB|PRE_SCRIPT_CB, (void*)rt )!=0 ) {
			LM_ERR("failed to register script callbacks\n");
			goto error3;
		}
	}

	if((pike_event_id = evi_publish_event(pike_block_event)) == EVI_ERROR)
		LM_ERR("cannot register pike flood start event\n");

	pike_srg = sr_register_group_with_identifier( CHAR_INT("pike"),
		0 /*is_public*/, CHAR_INT_NULL /*identifier*/,
		1, CHAR_INT_NULL /*status_txt*/,
		100 /*max_reports*/);
	if (pike_srg==NULL) {
		LM_ERR("failed to register SR identifier for reporting\n");
		goto error3;
	}


	return 0;
error3:
	destroy_ip_tree();
error2:
	lock_destroy(timer_lock);
error1:
	if (timer_lock) lock_dealloc(timer_lock);
	timer_lock = 0;
	return -1;
}



static int pike_exit(void)
{
	LM_INFO("destroying...\n");

	/* destroy semaphore */
	if (timer_lock) {
		lock_destroy(timer_lock);
		lock_dealloc(timer_lock);
	}

	/* empty the timer list head */
	if (timer) {
		shm_free(timer);
		timer = 0;
	}

	/* destroy the IP tree */
	destroy_ip_tree();

	return 0;
}


