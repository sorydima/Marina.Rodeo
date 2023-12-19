/*
 * load balancer module - complex call load balancing
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Voice Sistem SRL
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */



#ifndef _LB_LB_PARSER_H_
#define _LB_LB_PARSER_H_

#include "../../str.h"

struct lb_res_str {
	str name;

	str fs_url;       /* fs_url || val */
	unsigned int val;
};

struct lb_res_str_list {
	int n;
	struct lb_res_str* resources;
};

struct lb_res_str* search_resource_str( struct lb_res_str_list *lb_rl,
		str *name);

struct lb_res_str_list *parse_resources_list(char *r_list, int has_val);

#endif

