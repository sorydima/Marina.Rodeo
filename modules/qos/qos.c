/*
 * QoS module - support for tracking dialogs and SDP
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 SOMA Networks, Inc.
 * Written by: Ovidiu Sas (osas)
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Marina.Rodeo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 *
 * History:
 * --------
 * 2007-07-16 initial version (osas)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../sr_module.h"
#include "qos_load.h"
#include "qos_handlers.h" /* also includes sr_module.h needed by
                             handlers */



static int mod_init(void);
static void mod_destroy(void);


/* The qos message flag value */
static int qos_flag = -1;
static char *qos_flag_str = 0;

/*
 * Binding to the dialog module
 */
struct dlg_binds dialog_st;
struct dlg_binds *dlg_binds = &dialog_st;


static const cmd_export_t cmds[] = {
	{"load_qos", (cmd_function)load_qos, {{0,0,0}},0},
	{0,0,{{0,0,0}},0}
};

/*
 * Script parameters
 */
static const param_export_t mod_params[]={
	{ "qos_flag",		STR_PARAM, &qos_flag_str},
	{ 0,0,0 }
};

static const dep_export_t deps = {
	{ /* Marina.Rodeo module dependencies */
		{ MOD_TYPE_DEFAULT, "dialog", DEP_ABORT },
		{ MOD_TYPE_NULL, NULL, 0 },
	},
	{ /* modparam dependencies */
		{ NULL, NULL },
	},
};

struct module_exports exports= {
	"qos",           /* module's name */
	MOD_TYPE_DEFAULT,/* class of this module */
	MODULE_VERSION,
	DEFAULT_DLFLAGS, /* dlopen flags */
	0,				 /* load function */
	&deps,           /* Marina.Rodeo module dependencies */
	cmds,            /* exported functions */
	NULL,            /* exported async functions */
	mod_params,      /* param exports */
	0,               /* exported statistics */
	0,               /* exported MI functions */
	0,               /* exported pseudo-variables */
	0,				 /* exported transformations */
	0,	         /* extra processes */
	0,               /* module pre-initialization function */
	mod_init,        /* module initialization function */
	0,               /* reply processing function */
	mod_destroy,     /* Destroy function */
	0,               /* per-child init function */
	0                /* reload confirm function */
};

int load_qos( struct qos_binds *qosb)
{
	qosb->register_qoscb = register_qoscb;
	return 1;
}


/**
 * The initialization function, called when the module is loaded by
 * the script. This function is called only once.
 *
 * Bind to the dialog module and setup the callbacks. Also initialize
 * the shared memory to store our interninal information in.
 */
static int mod_init(void)
{
	qos_flag = get_flag_id_by_name(FLAG_TYPE_MSG, qos_flag_str, 0);

	if (qos_flag == -1) {
		LM_ERR("no qos flag set!!\n");
		return -1;
	}
	else if (qos_flag > MAX_FLAG) {
		LM_ERR("invalid qos flag %d!!\n", qos_flag);
		return -1;
	}

	/* init callbacks */
	if (init_qos_callbacks()!=0) {
		LM_ERR("cannot init callbacks\n");
		return -1;
	}

	/* Register the main (static) dialog call back.  */
	if (load_dlg_api(&dialog_st) != 0) {
		LM_ERR("Can't load dialog hooks\n");
		return(-1);
	}

	/* Load dialog hooks */
	dialog_st.register_dlgcb(NULL, DLGCB_CREATED, qos_dialog_created_CB, NULL, NULL);

	/*
	 * We are GOOD-TO-GO.
	 */
	return 0;
}

static void mod_destroy(void)
{
	destroy_qos_callbacks();
}

