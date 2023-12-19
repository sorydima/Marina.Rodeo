/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2018 Marina.Rodeo Solutions
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
 */

#ifndef _STREAM_SEND_H_
#define _STREAM_SEND_H_

#define STREAM_SEND_RETRY 3

#include <sys/time.h>

typedef struct _stream_send {
	union sockaddr_union addr;
	struct timeval time;
	evi_async_ctx_t async_ctx;
	str message;
	int id;
} stream_send_t;

struct stream_cb_ipc_param {
	evi_async_ctx_t async_ctx;
	enum evi_status status;
};

void stream_process(int rank);
int stream_init_process(void);
void stream_destroy_pipe(void);
int stream_init_writer(void);
int stream_init_buffers(void);
int stream_send(stream_send_t * streams);
void stream_destroy(evi_reply_sock *sock);
int stream_build_buffer(str *,
		evi_reply_sock*, evi_params_t *, stream_send_t **);

#define STREAM_DEFAULT_TIMEOUT 1000
#define STREAM_BUFFER_SIZE 8192
#define JSONRPC_VERSION "2.0"

extern int stream_timeout;
extern unsigned stream_reliable_mode;
extern char *stream_event_param;

#endif
