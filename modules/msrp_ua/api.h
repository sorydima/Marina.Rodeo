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

#ifndef _MSRP_UA_API_H_
#define _MSRP_UA_API_H_

#include "../../parser/msg_parser.h"
#include "../proto_msrp/msrp_parser.h"

enum msrp_ua_event_type {
	MSRP_UA_SESS_ESTABLISHED = 1,
	MSRP_UA_SESS_FAILED,
	MSRP_UA_SESS_TERMINATED
};

struct msrp_ua_notify_params {
	enum msrp_ua_event_type event;
	struct sip_msg *msg;
	str *accept_types;
	str *session_id;
};

/* notifications about the SIP session */
typedef int (*msrp_ua_notify_cb_f)(struct msrp_ua_notify_params *params,
	void *hdl_param);

/* MSRP request received */
typedef int (*msrp_ua_req_cb_f)(struct msrp_msg *req, void *hdl_param);
/* MSRP reply received */
typedef int (*msrp_ua_rpl_cb_f)(struct msrp_msg *rpl, void *hdl_param);

struct msrp_ua_handler {
	str *name;
	void *param;
	msrp_ua_notify_cb_f notify_cb;
	msrp_ua_req_cb_f msrp_req_cb;
	msrp_ua_rpl_cb_f msrp_rpl_cb;
};

typedef int (*init_uas_f)(struct sip_msg *msg, str *accept_types,
	struct msrp_ua_handler *hdl);
typedef int (*init_uac_f)(str *accept_types, str *from_uri, str *to_uri,
	str *ruri, struct msrp_ua_handler *hdl);

typedef int (*end_session_f)(str *session_id);

enum msrp_failure_report_type {
	MSRP_FAILURE_REPORT_YES,
	MSRP_FAILURE_REPORT_PARTIAL,
	MSRP_FAILURE_REPORT_NO
};

typedef int (*send_message_f)(str *session_id, str *mime, str *body,
	enum msrp_failure_report_type failure_report, int success_report);

struct msrp_ua_binds {
	init_uas_f init_uas;
	init_uac_f init_uac;
	end_session_f end_session;
	send_message_f send_message;
};

typedef void (*load_msrp_ua_f)(struct msrp_ua_binds *binds);

static inline int load_msrp_ua_api(struct msrp_ua_binds *binds) {
	load_msrp_ua_f load_msrp_ua;

	/* import the msrp_ua auto-loading function */
	if (!(load_msrp_ua = (load_msrp_ua_f)find_export("load_msrp_ua", 0)))
		return -1;

	/* let the auto-loading function load all msrp API functions */
	load_msrp_ua(binds);

	return 0;
}

#endif
