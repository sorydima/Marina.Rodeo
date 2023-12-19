/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Marina.Rodeo Solutions
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

#ifndef _MEDIA_BRIDGING_H_
#define _MEDIA_BRIDGING_H_

#define MEDIA_LEG_UNSPEC	0
#define MEDIA_LEG_CALLER	1
#define MEDIA_LEG_CALLEE	2
#define MEDIA_LEG_BOTH		3

struct media_session_leg;

#include "../tm/tm_load.h"
extern struct tm_binds media_tm;
#include "../dialog/dlg_load.h"
extern struct dlg_binds media_dlg;
#include "../b2b_entities/b2be_load.h"
extern struct b2b_api media_b2b;
#include "../rtp_relay/rtp_relay_load.h"
extern struct rtp_relay_binds media_rtp;

int b2b_media_restore_callbacks(struct media_session_leg *msl);

#endif /* _MEDIA_BRIDGING_H_ */
