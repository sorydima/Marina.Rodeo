/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 SOMA Networks, Inc.
 * Written by Ovidiu Sas (osas)
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
 * History:
 * --------
 *  2007-07-11  initial version (osas)
 */

#ifndef _QOS_QOS_CB_H_
#define _QOS_QOS_CB_H_

#include "../../parser/msg_parser.h"

struct qos_ctx_st;

struct qos_cb_params {
	struct sip_msg *msg;       /* sip msg related to the callback event */
	struct qos_sdp_st *sdp;    /* pointer to the sdp that is added/updated/removed */
	unsigned int role;
	void **param;              /* parameter passed at callback registration*/
};

/* callback function prototype */
typedef void (qos_cb) (struct qos_ctx_st *qos, int type,
		struct qos_cb_params *params);
/* register callback function prototype */
typedef int (*register_qoscb_f)(struct qos_ctx_st *qos, int cb_types,
		qos_cb f, void *param);


#define QOSCB_CREATED      (1<<0)
#define QOSCB_ADD_SDP      (1<<1)
#define QOSCB_UPDATE_SDP   (1<<2)
#define QOSCB_REMOVE_SDP   (1<<3)
#define QOSCB_TERMINATED   (1<<4)

/*
 * Callback logic ....
 *

   --INVITE(SDP)-->
         +----------------<QOSCB_ADD>

  <---183(SDP)----
         +----------------<QOSCB_UPDATE>

  <---200(SDP)----
         +----------------<QOSCB_UPDATE>
   -----ACK------->


   -----BYE------->
         +----------------<QOSCB_REMOVE>
  <-----200-------

 */

struct qos_callback {
	int types;
	qos_cb* callback;
	void *param;
	struct qos_callback* next;
};


struct qos_head_cbl {
	struct qos_callback *first;
	int types;
};

int init_qos_callbacks();

void destroy_qos_callbacks();

void destroy_qos_callbacks_list(struct qos_callback *cb);

int register_qoscb(struct qos_ctx_st* qos, int types, qos_cb f, void *param);

void run_create_cbs(struct qos_ctx_st *qos, struct sip_msg *msg);

void run_qos_callbacks( int type, struct qos_ctx_st *qos,
			struct qos_sdp_st *sdp, unsigned int role,
			struct sip_msg *msg);


#endif
