/*
 * back-to-back entities modules
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
 *  2011-06-27  added authentication support (Ovidiu Sas)
 */

#ifndef  _B2B_H_
#define  _B2B_H_

#include "../../str.h"
#include "../../parser/msg_parser.h"
#include "../uac_auth/uac_auth.h"
#include "../tm/tm_load.h"
#include "../signaling/signaling.h"
#include "dlg.h"
#include "client.h"
#include "server.h"
#include "../../db/db.h"
#include "../../cachedb/cachedb.h"

/* modes to write in db */
#define NO_DB         0
#define WRITE_THROUGH 1
#define WRITE_BACK    2

extern int uac_auth_loaded;
extern str b2b_key_prefix;

extern unsigned int server_hsize;
extern unsigned int client_hsize;
extern struct tm_binds tmb;
extern uac_auth_api_t uac_auth_api;
extern struct script_route_ref *req_route_ref;
extern struct script_route_ref *reply_route_ref;
extern str db_url;
extern str b2be_cdb_url;
extern db_con_t *b2be_db;
extern db_func_t b2be_dbf;
extern cachedb_funcs b2be_cdbf;
extern cachedb_con *b2be_cdb;
extern str b2be_dbtable;
extern int b2be_db_mode;
extern int serialize_backend;
extern int b2b_ctx_idx;
extern str cdb_key_prefix;
extern int passthru_prack;

void *b2b_get_context(void);

int mi_print_b2be_all_dlgs(mi_item_t *resp_arr, b2b_table htable,
	unsigned int hsize, int ua_sessions);
int mi_print_b2be_dlg(b2b_dlg_t* dlg, mi_item_t *to);

#ifdef B2B_ENTITIES_LOCK_DBG
#define B2BE_LOCK_DBG(op, table, index) \
	LM_INFO("B2B_LOCK %s %s[%d] +%d\n", op, (table==server_htable)?"server":"client", index, __LINE__);
#else
#define B2BE_LOCK_DBG(op, table, index)
#endif

#define B2BE_LOCK_GET(table, hash_index) \
	do { \
		B2BE_LOCK_DBG("lock", table, hash_index); \
		lock_get(&table[hash_index].lock); \
	} while (0)

#define B2BE_LOCK_RELEASE(table, hash_index) \
	do { \
		B2BE_LOCK_DBG("unlock", table, hash_index); \
		lock_release(&table[hash_index].lock); \
	} while (0)

#endif
