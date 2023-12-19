/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2013-2020 Marina.Rodeo Solutions
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
 */

#include "../../ut.h"
#include "../../bin_interface.h"
#include "../../socket_info.h"
#include "../../timer.h"
#include "../../rw_locking.h"
#include "../clusterer/api.h"

#ifndef _DIALOG_DLG_REPLICATION_H_
#define _DIALOG_DLG_REPLICATION_H_

#define REPLICATION_DLG_CREATED		1
#define REPLICATION_DLG_UPDATED		2
#define REPLICATION_DLG_DELETED		3
#define REPLICATION_DLG_CSEQ		4

#define DLG_BIN_V3      3
#define DLG_BIN_V4      4

#define BIN_VERSION DLG_BIN_V4

extern int dialog_repl_cluster;
extern int profile_repl_cluster;

extern str dlg_repl_cap;
extern str prof_repl_cap;

extern struct clusterer_binds clusterer_api;

extern str shtag_dlg_val;

extern int cluster_auto_sync;

int dlg_init_clustering(void);

void replicate_dialog_created(struct dlg_cell *dlg);
void replicate_dialog_updated(struct dlg_cell *dlg);
void replicate_dialog_deleted(struct dlg_cell *dlg);
void replicate_dialog_cseq_updated(struct dlg_cell *dlg, int leg);

int dlg_replicated_create(bin_packet_t *packet, struct dlg_cell *cell,
	str *ftag, str *ttag, unsigned int hid, int safe, int from_sync);
int dlg_replicated_update(bin_packet_t *packet);
int dlg_replicated_delete(bin_packet_t *packet);

void receive_dlg_repl(bin_packet_t *packet);
void rcv_cluster_event(enum clusterer_event ev, int node_id);

mi_response_t *mi_sync_cl_dlg(const mi_params_t *params,
								struct mi_handler *async_hdl);

int get_shtag_state(struct dlg_cell *dlg);
int set_dlg_shtag(struct dlg_cell *dlg, str *tag_name);

#endif /* _DIALOG_DLG_REPLICATION_H_ */

