/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2022 Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
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
 */

#ifndef TCP_PATH_H
#define TCP_PATH_H

#include "../../rw_locking.h"
#include "../../ip_addr.h"
#include "../../net/tcp_conn_defs.h"

struct tcp_path {
	enum sip_protos proto;

	struct net remote_addr;
	char remote_any;
	unsigned short remote_port;

	struct net local_addr;
	char local_any;
	unsigned short local_port;

	int priority;
	struct tcp_conn_profile prof;
};

extern struct tcp_path *tcp_paths;
extern int *tcp_paths_sz;
extern rw_lock_t *tcp_paths_lk;

int tcp_path_init(void);
void tcp_path_destroy(void);

int tcp_store_path(int *int_vals, char **str_vals, struct tcp_path *path);

int tcp_mgm_get_profile(union sockaddr_union *remote,
         union sockaddr_union *local, enum sip_protos proto,
         struct tcp_conn_profile *out_profile);

#endif /* TCP_PATH_H */
