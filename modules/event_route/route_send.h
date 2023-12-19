/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2014 VoIP Embedded, Inc.
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 *
 */


#ifndef _ROUTE_SEND_H_
#define _ROUTE_SEND_H_


#define ROUTE_SEND_RETRY 3

typedef struct _route_send {
	struct script_route_ref *ev_route;
	str event;
	evi_params_t params;
} route_send_t;

int route_build_buffer(str *event_name, evi_reply_sock *sock,
		evi_params_t *params, route_send_t **msg);

int route_send(route_send_t *route_s);
void route_run(struct script_route route, struct sip_msg* msg,
		evi_params_t *params, str *event);

#endif
