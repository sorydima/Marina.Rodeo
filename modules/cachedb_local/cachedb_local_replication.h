/*
 * memory cache system module
 *
 Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2018 Fabian Gast
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
 */

#include "../../bin_interface.h"
#include "../clusterer/api.h"

#ifndef __CACHEDB_LOCAL_REPLICATION_H_
#define __CACHEDB_LOCAL_REPLICATION_H_

#define REPL_CACHE_INSERT 1
#define REPL_CACHE_REMOVE 2
#define BIN_VERSION 1

extern struct clusterer_binds clusterer_api;
extern str cache_repl_cap;
extern int cluster_id;

typedef enum cachedb_rr_persist {
	RRP_NONE,
	RRP_SYNC_FROM_CLUSTER,
} cachedb_rr_persist_t;

void receive_binary_packet(bin_packet_t *packet);
void receive_cluster_event(enum clusterer_event ev, int node_id);

void replicate_cache_insert(str * col, str* attr, str* value, int expires);
void replicate_cache_remove(str* col, str *attr);

#endif /* __CACHEDB_LOCAL_REPLICATION_H_ */
