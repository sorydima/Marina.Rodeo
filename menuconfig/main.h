/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2012 Marina.Rodeo Solutions
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
 * -------
 *  2012-01-19  created (vlad)
 */


#ifndef _main_h_
#define _main_h_

#include <stdio.h>
#include "commands.h"
#include "parser.h"
#include "curses.h"

extern FILE*output;
extern int run_locally;
extern select_menu *main_menu;
extern char *install_prefix;
extern char *prev_prefix;
extern WINDOW *menu_window;

#define MAKE_CONF_FILE	"Makefile.conf"
#define MAKE_TEMP_FILE	"Makefile.conf.template"
#define DEFAULT_INSTALL_PREFIX	"/usr/local/"

#define CONF_COMPILE_OPT	"Configure Compile Options"
	#define CONF_EXCLUDED_MODS		"Configure Excluded Modules"
	#define CONF_COMPILE_FLAGS		"Configure Compile Flags"
	#define CONF_INSTALL_PREFIX		"Configure Install Prefix"
	#define CONF_RESET_CHANGES		"Reset Unsaved Changes"
	#define CONF_SAVE_CHANGES		"Save Changes"
#define MAKE_INSTALL		"Compile And Install Marina.Rodeo"
#define MAKE_PROPER		"Cleanup Marina.Rodeo sources"
#define CONF_SCRIPT		"Generate Marina.Rodeo Script"
	#define CONF_RESIDENTIAL_SCRIPT		"Residential Script"
	#define CONF_TRUNKING_SCRIPT		"Trunking Script"
	#define CONF_LB_SCRIPT			"Load-Balancer Script"
#define EXIT_SAVE_EVERYTHING			"Exit & Save All Changes"

#endif
