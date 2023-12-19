/*
 * back-to-back entities module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Free Software Fundation
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
 *  2009-08-03  initial version (Anca Vamanu)
 */

#ifndef _B2B_SERVER_H_
#define _B2B_SERVER_H_

#include "../../parser/msg_parser.h"
#include "dlg.h"
#include "b2be_load.h"
#include "ua_api.h"

str* _server_new(struct sip_msg* msg, str* local_contact, b2b_notify_t b2b_cback,
	str *mod_name, str* logic_key, struct ua_sess_init_params *ua_init_params,
	struct b2b_tracer *tracer, void *param, b2b_param_free_cb free_param);
str* server_new(struct sip_msg*, str* local_contact, b2b_notify_t, str *,
		str*, struct b2b_tracer*, void *, b2b_param_free_cb);

dlg_t* b2b_server_build_dlg(b2b_dlg_t* dlg, unsigned int maxfwd);

void b2b_server_tm_cback( struct cell *t, int type, struct tmcb_params *ps);

#endif
