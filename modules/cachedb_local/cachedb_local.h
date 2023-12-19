/*
 * memory cache system module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Anca Vamanu
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
 *  2009-01-30  initial version (Anca Vamanu)
 */

#ifndef _MEMCACHE_
#define _MEMCACHE_

#include "../../cachedb/cachedb.h"
#include "../../cachedb/cachedb_cap.h"
#include "hash.h"

#define HASH_SIZE_DEFAULT 9 /* power of two */
#define DEFAULT_COLLECTION_NAME "default"

extern int cache_htable_size;
extern int local_exec_threshold;

typedef struct {
	struct cachedb_id *id;
	unsigned int ref;
	struct cachedb_pool_con_t *next;

	/* local cache hash structure */
	struct lcache_col* col;
} lcache_con;

typedef struct lcache_rpm_cache {
	str col_name;
	lcache_htable_t *col_htable;
	struct lcache_rpm_cache *next;
} lcache_rpm_cache_t;

typedef struct lcache_col {
	str col_name;

	lcache_htable_t *col_htable;
	int size;

	int replicated;

	osips_malloc_f malloc;
	osips_realloc_f realloc;
	osips_free_f free;
	lcache_rpm_cache_t *rpm_cache;

	struct lcache_col* next;
} lcache_col_t;

typedef struct url_lst {
	str url;
	struct url_lst* next;
} url_lst_t;

int _lcache_htable_insert(lcache_col_t *cache_col, str* attr, str* value,
	int expires, int isrepl);
int _lcache_htable_remove(lcache_col_t *cache_col ,str* attr, int isrepl);

extern lcache_col_t* lcache_collection;
extern url_lst_t* url_list;

#endif
