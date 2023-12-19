/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2022 - Marina.Rodeo Solutions
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

#ifndef _MSRP_RELAY_H_
#define _MSRP_RELAY_H_

#include "../auth/api.h"
#include "../../ut.h"

extern auth_api_t auth_api;
extern struct msrp_binds msrp_api;
extern void *msrp_hdl;

extern struct script_route_ref *auth_route_ref;

extern struct msrp_url *my_url_list;

extern int msrp_sessions_hsize;
extern gen_hash_t *msrp_sessions;

#define SESS_HAVE_PEER_CONN     (1<<0)
#define SESS_ACCEPTED_PEER_CONN (1<<1)

struct msrp_session {
	str session_id;
	str top_from;
	unsigned int expires;
	unsigned int flags;
	/* saved only if the peer connected to us first */
	union sockaddr_union peer_src_su;
};

#endif  /* _MSRP_RELAY_H_ */
