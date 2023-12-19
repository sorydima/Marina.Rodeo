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

#ifndef _parser_h_
#define _parser_h_

#include "menus.h"
#include "cfg.h"

#define GRP_START_STR	"#DEFS_GROUP_START"
#define GRP_END_STR		"#DEFS_GROUP_END"

#define SKIP_LINE_STR "##"
#define SKIP_LINE_STRL 2

int parse_dep_line(char *line,select_menu *parent);
int parse_include_line(char *line,select_menu *parent);
int parse_defs_line(char *line,select_menu *parent,int *group_idx,int *start_grp);
int parse_prefix_line(char *line,select_menu *menu);
int parse_defs_m4_line(char *line,select_menu *menu);
int parse_defs_m4(select_menu *curr_menu,cfg_gen_t *curr_cfg);
int parse_make_conf();
#endif
