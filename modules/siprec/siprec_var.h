/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2021 Marina.Rodeo Project
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
 */

#ifndef _SIPREC_VAR_H_
#define _SIPREC_VAR_H_

#include "../../str.h"
#include "../../pvar.h"
#include "../../socket_info.h"

struct srec_var {
	str group, caller, callee, media, headers;
	struct socket_info *si;
};

int init_srec_var(void);
int pv_parse_siprec(pv_spec_p sp, const str *in);
int pv_get_siprec(struct sip_msg *msg,  pv_param_t *param,
		pv_value_t *val);
int pv_set_siprec(struct sip_msg* msg, pv_param_t *param,
		int op, pv_value_t *val);

struct srec_var *get_srec_var(void);

#endif /* _SIPREC_VAR_H_ */
