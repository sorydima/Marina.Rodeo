/*
 * reg_db_handler module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2011 VoIP Embedded, Inc.
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
 * 2011-12-16  initial version (Ovidiu Sas)
 */

#ifndef REG_DB_HANDLER
#define REG_DB_HANDLER

#include <stdio.h>
#include <stdlib.h>

#include "reg_records.h"


#define REGISTRAR_COL			"registrar"
#define PROXY_COL			"proxy"
#define AOR_COL				"aor"
#define THIRD_PARTY_REGISTRANT_COL	"third_party_registrant"
#define USERNAME_COL			"username"
#define PASSWORD_COL			"password"
#define BINDING_URI_COL			"binding_URI"
#define BINDING_PARAMS_COL		"binding_params"
#define EXPIRY_COL			"expiry"
#define FORCED_SOCKET_COL		"forced_socket"
#define CLUSTER_SHTAG_COL		"cluster_shtag"
#define STATE_COL				"state"

#define REG_TABLE_NAME			"registrant"

#define REG_TABLE_VERSION		3

#define REG_TABLE_TOTAL_COL_NO		12

#define REG_FETCH_SIZE			128

#define REG_KEY_COL_NO 3

#define REG_DB_STATE_ENABLED  0

extern str registrar_column;
extern str proxy_column;
extern str aor_column;
extern str third_party_registrant_column;
extern str username_column;
extern str password_column;
extern str binding_URI_column;
extern str binding_params_column;
extern str expiry_column;
extern str forced_socket_column;
extern str cluster_shtag_column;
extern str state_column;

extern str reg_table_name;

extern unsigned int timer_interval;

int init_reg_db(const str *db_url);
int connect_reg_db(const str *db_url);
int load_reg_info_from_db(unsigned int mode, record_coords_t *coords);
int reg_update_db_state(reg_record_t *rec);
void destroy_reg_db(void);

#endif
