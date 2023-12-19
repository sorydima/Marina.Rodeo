/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2015 - Marina.Rodeo Foundation
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

#ifndef OPENSSL_TRACE_H
#define OPENSSL_TRACE_H

#include "../../trace_api.h"
#include "../../net/trans_trace.h"
#include "../tls_mgm/tls_helper.h"
#include "../tls_mgm/tls_trace_common.h"

static inline int trace_tls( struct tcp_connection* conn, SSL* ctx,
	trans_trace_event event, trans_trace_status status, str* data);

static inline void tls_append_cert_info(X509* cert, char client, trace_message message, trace_proto_t* tprot)
{
	str subj, issuer;

	if ( !cert || !message || !tprot )
		return;

	subj.s   = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
	issuer.s = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);

	subj.len = strlen( subj.s );
	issuer.len = strlen( issuer.s );

	if ( client ) {
		add_trace_data( message, "client-subject", &subj );
		add_trace_data( message, "client-issuer", &issuer );
	} else {
		add_trace_data( message, "server-subject", &subj );
		add_trace_data( message, "server-issuer", &issuer );
	}

	OPENSSL_free( subj.s );
	OPENSSL_free( issuer.s );
}

static inline void tls_append_master_secret( SSL* ctx, struct tls_data* data )
{
	static char ssl_print_master_buf[SSL_MAX_MASTER_KEY_LENGTH * 2];

	str master;
	SSL_SESSION* s;

	s = SSL_get1_session( ctx );
	if ( !s ) {
		LM_DBG("no session to get master key from!\n");
		return;
	}

	master.s = ssl_print_master_buf;
#if OPENSSL_VERSION_NUMBER < 0x10100000L
	master.len = string2hex( s->master_key, s->master_key_length, ssl_print_master_buf );
#else
	master.len = SSL_SESSION_get_master_key(s, (unsigned char *)master.s,
		SSL_MAX_MASTER_KEY_LENGTH * 2);
#endif

	data->tprot->add_payload_part( data->message, "master-key", &master);
	/* this will not always free the session, probably never will just
	 * decrease the session refcount */
	SSL_SESSION_free( s );
}

static void add_certificates( SSL* ssl, struct tls_data* data)
{
	X509* cert;

	cert = SSL_get_peer_certificate( ssl );
	tls_append_cert_info(cert, 1/* client */, data->message, data->tprot);


	cert = SSL_get_certificate( ssl );
	tls_append_cert_info(cert, 0/* server */, data->message, data->tprot);
}

static inline int trace_tls( struct tcp_connection* conn, SSL* ctx,
		trans_trace_event event, trans_trace_status status, str* message)
{
	struct tls_data* data;
	union sockaddr_union src, dst;

	if ( !conn || !TLS_TRACE_IS_ON(conn) || !(data=conn->proto_data) )
		return 0;

	if ( data->trace_route_ref ) {
		check_trace_route( data->trace_route_ref, conn );
		/* avoid doing this multiple times */
		data->trace_route_ref = NULL;
	}

	/* check if tracing is deactivated from the route for this connection */
	if ( conn->flags & F_CONN_TRACE_DROPPED )
		return 0;

	if ( !data->message ) {
		if ( tcpconn2su( conn, &src, &dst ) < 0 ) {
			LM_ERR("can't get network info from connection!\n");
			return -1;
		}

		data->message = create_trace_message( conn->cid, &src, &dst,
				conn->type, data->dest );
		if ( !data->message ) {
			LM_ERR("failed to create trace message!\n");
			return -1;
		}
	}

	add_certificates( ctx, data);
	tls_append_master_secret( ctx, data);

	add_trace_data( data->message, "Event", &trans_trace_str_event[event]);
	add_trace_data( data->message, "Status", &trans_trace_str_status[status]);

	if ( message && message->s && message->len) {
		add_trace_data( data->message, "Message", message);
	}

	conn->proto_flags |= F_TLS_TRACE_READY;

	return 0;
}

#endif	/* OPENSSL_TRACE_H */
