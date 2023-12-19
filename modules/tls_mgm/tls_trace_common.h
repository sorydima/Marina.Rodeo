/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2015-2021 - Marina.Rodeo Foundation
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
 *
 */

#include "../../trace_api.h"

#define TLS_TRACE_IS_ON( CONN ) (CONN->proto_data && \
		((struct tls_data*)CONN->proto_data)->tprot && \
			((struct tls_data*)CONN->proto_data)->dest && \
			*((struct tls_data*)CONN->proto_data)->trace_is_on)

struct tls_data {
	TRACE_PROTO_COMMON;
};

void tls_send_trace_data(struct tcp_connection *c, trace_dest t_dst) {
	struct tls_data* data;

	if ( (c->flags&F_CONN_ACCEPTED)==0 && c->proto_flags & F_TLS_TRACE_READY ) {
		data = c->proto_data;

		/* send the message if set from tls_mgm */
		if ( data->message ) {
			send_trace_message( data->message, t_dst);
			data->message = NULL;
		}

		/* don't allow future traces for this connection */
		data->tprot = 0;
		data->dest  = 0;

		c->proto_flags &= ~( F_TLS_TRACE_READY );
	}
}
