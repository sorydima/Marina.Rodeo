/*
 * Marina.Rodeo H.350 Module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 University of North Carolina
 *
 * Original author: Christian Schlatter, cs@unc.edu
 *
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
 * 2007-03-12: Initial version
 */

#ifndef H350_EXP_FN_H
#define H350_EXP_FN_H

#include "../../parser/msg_parser.h"
#include "../../pvar.h"
#include "../../parser/msg_parser.h"

#define E_H350_SUCCESS 1
#define E_H350_INTERNAL -1
#define E_H350_NO_SUCCESS -2

int h350_exp_fn_init();

int h350_sipuri_lookup(struct sip_msg* _msg, str* _sip_uri);

int h350_auth_lookup(struct sip_msg* _msg, str *digest_username,
	pv_spec_t *username_avp, pv_spec_t *pwd_avp);

int h350_call_preferences(struct sip_msg* _msg, str* _avp_name_prefix);

int h350_service_level(struct sip_msg* _msg, str* _avp_name_prefix);

#endif /* H350_EXP_FN_H */
