/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2014 Marina.Rodeo Foundation
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Marina.Rodeo Solutions
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __QR_ACC_H__
#define __QR_ACC_H__

#include <time.h>

#include "../tm/tm_load.h"
#include "../dialog/dlg_load.h"
#include "qr_stats.h"
#include "../drouting/dr_api.h"

#define QR_TM_180_RCVD (1<<0)

extern struct tm_binds tmb;
extern struct dlg_binds dlgcb;
extern struct dr_binds drb;

typedef struct qr_trans_prop {
	qr_gw_t *gw;
	gen_lock_t *prop_lock;
	struct timespec invite;
	char state;
} qr_trans_prop_t;

typedef struct qr_dialog_prop {
	qr_gw_t *gw;
	struct timespec time_200OK;
} qr_dialog_prop_t;

void update_gw_stats(qr_gw_t *);
void update_grp_stats(qr_grp_t );
void qr_acc(void *param);
void qr_check_reply_tmcb(struct cell*, int ,struct tmcb_params*);
void show_stats(qr_gw_t *gw);

#endif
