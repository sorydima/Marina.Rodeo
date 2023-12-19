/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2016 Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
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
 * History:
 * ---------
 *  2016-02-01  first version (bogdan)
 */

#ifndef SL_CB_H_
#define SL_CB_H_

#include "str.h"
#include "ip_addr.h"
#include "parser/msg_parser.h"


enum sl_cb_type {SLCB_REPLY_OUT=0, SLCB_ACK_IN, SLCB_REQUEST_OUT,
	SLCB_LAST };

/* callback function prototype */
typedef void (sl_cb_t) (struct sip_msg* req, str *buffer, int rpl_code,
		union sockaddr_union *dst, struct socket_info *sock, int proto);

/* register callback function prototype */
typedef int (*register_slcb_t)(enum sl_cb_type, unsigned int fmask, sl_cb_t f);



/* frees all memory used by the callbacks */
void destroy_slcb_lists();

/* register a SL callback */
int register_slcb(enum sl_cb_type, unsigned int fmask, sl_cb_t f);

/* run SL callbacks for a given type */
void slcb_run_reply_out(struct sip_msg *req, str *buffer,
		union sockaddr_union *dst, int rpl_code);
void slcb_run_ack_in(struct sip_msg *req);
void slcb_run_req_out(struct sip_msg *req, str *buffer,
		union sockaddr_union *dst, struct socket_info *sock, int proto);

#endif


