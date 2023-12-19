/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2015 Marina.Rodeo Project
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Marina.Rodeo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * history:
 * ---------
 *  2015-07-xx created (rvlad-patrascu)
 */

#ifndef _EV_VIRTUAL_H_
#define _EV_VIRTUAL_H_

#include "../../locking.h"
#include "../../str.h"
#include "../../evi/evi_transport.h"

#define VIRT_NAME	"virtual"
#define VIRT_STR	{ VIRT_NAME, sizeof(VIRT_NAME) - 1}
#define VIRT_FLAG	(1<<24)

#define PARALLEL_TYPE 0
#define PARALLEL_STR "PARALLEL"
#define PARALLEL_LEN 8
#define FAILOVER_TYPE 1
#define FAILOVER_STR "FAILOVER"
#define FAILOVER_LEN 8
#define RROBIN_TYPE 2
#define RROBIN_STR 	"ROUND-ROBIN"
#define RROBIN_LEN 11

#define SEP_SPACE	' '
#define SEP_TAB		'\t'

#define DEFAULT_FAILOVER_TIMEOUT 30

struct virtual_socket {
	unsigned int type;
	unsigned int nr_sockets;
	struct sub_socket *current_sock;	/* current socket to raise */
	struct sub_socket *list_sockets;	/* list of actual sockets */
	struct virtual_socket *next;
	struct virtual_socket *prev;
};

struct sub_socket {
	str sock_str;
	const evi_export_t *trans_mod;
	evi_reply_sock *sock;

	gen_lock_t *lock;
	unsigned int last_failed;

	struct sub_socket *next;
};

struct virtual_cb_param {
	struct sub_socket *current_sock;
	str sip_msg_buf;
	str ev_name;
	evi_params_t *evi_params;
};

#endif
