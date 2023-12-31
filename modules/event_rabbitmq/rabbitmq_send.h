/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2011 Marina.Rodeo Solutions
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


#ifndef _RMQ_SEND_H_
#define _RMQ_SEND_H_

#include "event_rabbitmq.h"

#define RMQ_SEND_RETRY 3

typedef struct _rmq_send {
	evi_reply_sock *sock;
	evi_async_ctx_t async_ctx;
	char msg[0];
} rmq_send_t;

struct rmq_cb_ipc_param {
	evi_async_ctx_t async_ctx;
	enum evi_status status;
};

void rmq_process(int rank);
int rmq_create_pipe(void);
void rmq_destroy_pipe(void);
int rmq_init_writer(void);
int rmq_send(rmq_send_t * rmqs);
void rmq_free_param(rmq_params_t *rmqp);
void rmq_destroy(evi_reply_sock *sock);

extern struct timeval conn_timeout_tv;
extern str rmq_static_holder;

#endif
