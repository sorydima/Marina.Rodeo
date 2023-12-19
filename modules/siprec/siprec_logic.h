/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2017 Marina.Rodeo Project
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
 * History:
 * ---------
 *  2017-06-20  created (razvanc)
 */

#ifndef _SIPREC_LOGIC_H_
#define _SIPREC_LOGIC_H_

#include "siprec_sess.h"
#include "../b2b_entities/b2be_load.h"

int src_start_recording(struct sip_msg *msg, struct src_sess *sess);
void tm_start_recording(struct cell *t, int type, struct tmcb_params *ps);
int srec_register_callbacks(struct src_sess *sess);
int srec_restore_callback(struct src_sess *sess);
void srec_logic_destroy(struct src_sess *sess);
int src_pause_recording(void);
int src_resume_recording(void);

extern int srec_dlg_idx;
extern struct b2b_api srec_b2b;
extern str skip_failover_codes;
int src_init(void);

#endif /* _SIPREC_LOGIC_H_ */
