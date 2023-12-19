/*
 * Path handling for intermediate proxies
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Inode GmbH (Andreas Granig <andreas.granig@inode.info>)
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
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../sr_module.h"
#include "../../mem/mem.h"
#include "../../mod_fix.h"
#include "../rr/api.h"

#include "path.h"
#include "path_mod.h"


int enable_double_path = 1; /* Enable using of 2 Path by default */


/* If received-param of current Route uri should be used
 * as dst-uri. */
int use_received = 0;

/*
 * Module destroy function prototype
 */
static void destroy(void);

/*
 * Module child-init function prototype
 */
static int child_init(int rank);

/*
 * Module initialization function prototype
 */
static int mod_init(void);

/*
 * rr callback API
 */
struct rr_binds path_rrb;


/*
 * Exported functions
 */
static const cmd_export_t cmds[] = {
	{"add_path", (cmd_function)add_path, {
		{CMD_PARAM_STR|CMD_PARAM_OPT,0,0}, {0,0,0}},
		REQUEST_ROUTE},
	{"add_path_received", (cmd_function)add_path_received, {
		{CMD_PARAM_STR|CMD_PARAM_OPT,0,0}, {0,0,0}},
		REQUEST_ROUTE},
	{0,0,{{0,0,0}},0}
};

/*
 * Exported parameters
 */
static const param_export_t params[] = {
	{"use_received", INT_PARAM, &use_received },
	{"enable_double_path", INT_PARAM, &enable_double_path },
	{ 0, 0, 0 }
};

static module_dependency_t *get_deps_use_received(const param_export_t *param)
{
	if (! *(int *)param->param_pointer)
		return NULL;

	return alloc_module_dep(MOD_TYPE_DEFAULT, "rr", DEP_ABORT);
}

static const dep_export_t deps = {
	{ /* Marina.Rodeo module dependencies */
		{ MOD_TYPE_NULL, NULL, 0 },
	},
	{ /* modparam dependencies */
		{ "use_received", get_deps_use_received },
		{ NULL, NULL },
	},
};

/*
 * Module interface
 */
struct module_exports exports = {
	"path",
	MOD_TYPE_DEFAULT,/* class of this module */
	MODULE_VERSION,
	DEFAULT_DLFLAGS, /* dlopen flags */
	0,				 /* load function */
	&deps,           /* Marina.Rodeo module dependencies */
	cmds,       /* Exported functions */
	0,          /* Exported async functions */
	params,     /* Exported parameters */
	0,          /* exported statistics */
	0,          /* exported MI functions */
	0,          /* exported pseudo-variables */
	0,			/* exported transformations */
	0,          /* extra processes */
	0,          /* module pre-initialization function */
	mod_init,   /* module initialization function */
	0,          /* response function */
	destroy,    /* destroy function */
	child_init, /* child initialization function */
	0           /* reload confirm function */
};


static int child_init(int rank)
{
	return 0;
}


static int mod_init(void)
{
	LM_INFO("initializing...\n");

	if (use_received) {
		if (load_rr_api(&path_rrb) != 0) {
			LM_ERR("failed to load rr-API\n");
			return -1;
		}
		if (path_rrb.register_rrcb(path_rr_callback, 0, 0) != 0) {
			LM_ERR("failed to register rr callback\n");
			return -1;
		}
	}

	return 0;
}


static void destroy(void)
{
}


