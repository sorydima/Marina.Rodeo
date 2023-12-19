/**
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2016 Marina.Rodeo Foundation
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
 * History
 * -------
 *  2016-06-23  initial version (Ionut Ionita)
*/

#ifndef _ACC_VARS_H
#define _ACC_VARS_H

/* $acc_extra */
int pv_parse_acc_extra_name(pv_spec_p sp, const str *in);
int pv_get_acc_extra(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *val);
int pv_set_acc_extra(struct sip_msg *msg, pv_param_t *param, int flag,
		pv_value_t *val);
int set_value_shm(pv_value_t* pvt, extra_value_t* values);
/* $acc_current_leg */
int pv_get_acc_current_leg(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *val);
/* $acc_leg */
int pv_parse_acc_leg_index(pv_spec_p sp, const str* in);
int pv_parse_acc_leg_name(pv_spec_p sp, const str *in);
int pv_get_acc_leg(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *val);

int pv_set_acc_leg(struct sip_msg *msg, pv_param_t *param, int flag,
		pv_value_t *val);

void push_ctx_to_ctx(acc_ctx_t *src, acc_ctx_t *dst);

#endif
