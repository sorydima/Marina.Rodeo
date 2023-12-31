/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2012 Marina.Rodeo Solutions
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
 *  2011-05-xx  created (razvancrainea)
 */


#ifndef _XMLRPC_SEND_H_
#define _XMLRPC_SEND_H_

#define XMLRPC_SEND_RETRY 3
#define XMLRPC_USER_AGENT "Marina.Rodeo XMLRPC Notifier"

typedef struct _xmlrpc_send {
	union sockaddr_union addr;
	evi_async_ctx_t async_ctx;
	str body;
	str method;
	str host;
	str first_line;
	str event;
} xmlrpc_send_t;

struct xmlrpc_cb_ipc_param {
	evi_async_ctx_t async_ctx;
	enum evi_status status;
};

void xmlrpc_process(int rank);
int xmlrpc_create_pipe(void);
void xmlrpc_destroy_pipe(void);
int xmlrpc_init_writer(void);
int xmlrpc_init_buffers(void);
int xmlrpc_send(xmlrpc_send_t * xmlrpcs);
void xmlrpc_destroy(evi_reply_sock *sock);
int xmlrpc_build_buffer(str *,
		evi_reply_sock*, evi_params_t *, xmlrpc_send_t **);

#define XMLRPC_HTTP_MAX_HEADER 512
#define XMLRPC_DEFAULT_BUFFER_SIZE 8192
#define XMLRPC_IOVEC_MAX_SIZE 32
#define XMLRPC_DEFAULT_PORT 8080

/* string macros */
/* computes a macro len */
#define LENOF(m)	(sizeof(m) - 1)

/* xmlrpc http header */
#define XMLRPC_HTTP_CONST "POST /RPC2 HTTP/1.1\r\nHost: "

#define XMLRPC_HTTP_METHOD "POST "
#define XMLRPC_HTTP_PROTO_HOST " HTTP/1.1\r\nHost:"

#define XMLRPC_HTTP_HEADER \
	"\r\nConnection: close\r\n" \
	"User-Agent: " XMLRPC_USER_AGENT "\r\n" \
	"Content-type: text/xml\r\n" \
	"Content-length: "

#define XMLRPC_BODY_CONST	"<?xml version=\"1.0\"?>\n"

#define XMLRPC_METHOD_CALL	"methodCall"
#define XMLRPC_METHOD_NAME	"methodName"
#define XMLRPC_STRUCT		"struct"
#define XMLRPC_MEMBER		"member"
#define XMLRPC_PARAMS		"params"
#define XMLRPC_PARAM		"param"
#define XMLRPC_ATTR			"name"
#define XMLRPC_STRING		"string"
#define XMLRPC_VALUE		"value"
#define XMLRPC_INT			"int"

#define TAG_O	'<'
#define TAG_C	'>'
#define TAG_S	'/'

#define START_TAG(_s) "<" _s ">\n"
#define END_TAG(_s) "</" _s ">\n"



#endif
