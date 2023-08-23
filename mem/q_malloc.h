/*
 * simple & fast malloc library
 *
 * Copyright (C) 2001-2003 FhG Fokus
 * Copyright (C) 2019 Marina.Rodeo Solutions
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

#ifndef q_malloc_h
#define q_malloc_h

#include <stdio.h>
#include "meminfo.h"
#include "../dprint.h"
#include "common.h"

#undef UN_HASH

#if defined(__CPU_sparc64) || defined(__CPU_sparc)
/* tricky, on sun in 32 bits mode long long must be 64 bits aligned
 * but long can be 32 bits aligned => malloc should return long long
 * aligned memory */
	#define QM_ROUNDTO		sizeof(long long)
#else
	/* address alignment, in bytes (2^n) */
	#define QM_ROUNDTO		sizeof(void *)
#endif

#define Q_MALLOC_OPTIMIZE_FACTOR 14UL /*used below */
#define Q_MALLOC_OPTIMIZE  ((unsigned long)(1UL<<Q_MALLOC_OPTIMIZE_FACTOR))
								/* size to optimize for,
									(most allocs <= this size),
									must be 2^k */

#define QM_HASH_SIZE ((unsigned long)(Q_MALLOC_OPTIMIZE/QM_ROUNDTO + \
		(sizeof(long)*8 - Q_MALLOC_OPTIMIZE_FACTOR) + 1))

#define QM_FRAG(p) \
	((struct qm_frag *)(p) - 1)

/* hash structure:
 * 0 .... Q_MALLOC_OPTIMIZE/QM_ROUNDTO  - small buckets, size increases with
 *                            QM_ROUNDTO from bucket to bucket
 * +1 .... end -  size = 2^k, big buckets */

#ifdef DBG_MALLOC
#ifndef QM_DBG_MALLOC_HIST
#define QM_DBG_MALLOC_HIST 1
#endif
struct qm_frag_dbg {
       const char* file;
       const char* func;
       unsigned long line;
};

#define qm_dbg_coords(_frag) \
       (_frag)->dbg[0].file, (_frag)->dbg[0].func, (_frag)->dbg[0].line
#else
#define qm_dbg_coords(_frag)
#endif

#ifdef DBG_MALLOC
#if QM_DBG_MALLOC_HIST > 1
#define qm_dbg_move(_frag) \
       memmove(&(_frag)->dbg[1], &(_frag)->dbg[0], \
                       (QM_DBG_MALLOC_HIST - 1) * sizeof(struct qm_frag_dbg))
#define qm_dbg_clear(_frag) \
       memset(&(_frag)->dbg[1], 0, \
                       (QM_DBG_MALLOC_HIST - 1) * sizeof(struct qm_frag_dbg))
#else /* QM_DBG_MALLOC_HIST */
#define qm_dbg_move(_frag)
#define qm_dbg_clear(_frag)
#endif /* QM_DBG_MALLOC_HIST */
#define qm_dbg_fill(_frag, _file, _func, _line) \
       do { \
               qm_dbg_move(_frag); \
               (_frag)->dbg[0].file = _file; \
               (_frag)->dbg[0].func = _func; \
               (_frag)->dbg[0].line = _line; \
       } while(0)

#else /* DBG_MALLOC */
#define qm_dbg_fill(_frag, _file, _func, _line)
#define qm_dbg_clear(_frag)
#endif /* DBG_MALLOC */


struct qm_frag {
	unsigned long size;
	union {
		struct qm_frag *nxt_free;
		long is_free;
	} u;
#ifdef DBG_MALLOC
	struct qm_frag_dbg dbg[QM_DBG_MALLOC_HIST];
	unsigned long check;
#endif
#ifdef SHM_EXTRA_STATS
	unsigned long statistic_index;
#endif
} __attribute__ ((aligned (QM_ROUNDTO)));

#define QM_FRAG_OVERHEAD (sizeof(struct qm_frag))

struct qm_frag_end {
#ifdef DBG_MALLOC
	unsigned long check1;
	unsigned long check2;
	unsigned long reserved1;
	unsigned long reserved2;
#endif
	unsigned long size;
	struct qm_frag *prev_free;
} __attribute__ ((aligned (QM_ROUNDTO)));

struct qm_frag_lnk {
	struct qm_frag head;
	struct qm_frag_end tail;
	unsigned long no;
};

struct qm_block {
	char *name; /* purpose of this memory block */

	unsigned long size; /* total size */
	unsigned long used; /* alloc'ed size*/
	unsigned long real_used; /* used+malloc overhead*/
	unsigned long max_real_used;
	unsigned long fragments; /* number of fragments in use */

	struct qm_frag *first_frag;
	struct qm_frag_end *last_frag_end;

	struct qm_frag_lnk free_hash[QM_HASH_SIZE];
} __attribute__ ((aligned (QM_ROUNDTO)));

struct qm_block *qm_malloc_init(char *address, unsigned long size, char *name);

#ifdef DBG_MALLOC
void *qm_malloc(struct qm_block*, unsigned long size, const char *file,
                const char *func, unsigned int line);
void  qm_free(struct qm_block*, void *p, const char *file, const char *func,
				unsigned int line);
void *qm_realloc(struct qm_block*, void *p, unsigned long size,
					const char *file, const char *func, unsigned int line);
#ifndef INLINE_ALLOC
void *qm_malloc_dbg(struct qm_block*, unsigned long size, const char *file,
                    const char *func, unsigned int line);
void qm_free_dbg(struct qm_block*, void *p, const char *file, const char *func,
				unsigned int line);
void *qm_realloc_dbg(struct qm_block*, void *p, unsigned long size,
					const char *file, const char *func, unsigned int line);
#endif
#else
void *qm_malloc(struct qm_block*, unsigned long size);
void  qm_free(struct qm_block*, void *p);
void *qm_realloc(struct qm_block*, void *p, unsigned long size);
#endif

void qm_status(struct qm_block*);
#if !defined INLINE_ALLOC && defined DBG_MALLOC
void qm_status_dbg(struct qm_block*);
#endif
void qm_info(struct qm_block*, struct mem_info*);

/*
 * On success, returns the currrent number of fragments
 * Internally aborts on failure
 */
int qm_mem_check(struct qm_block *qm);

static inline unsigned long qm_frag_size(void *p)
{
	if (!p)
		return 0;

	return QM_FRAG(p)->size;
}

#ifdef SHM_EXTRA_STATS
void qm_stats_core_init(struct qm_block *qm, int core_index);
unsigned long qm_stats_get_index(void *ptr);
void qm_stats_set_index(void *ptr, unsigned long idx);

#ifdef DBG_MALLOC
static inline const char *qm_frag_file(void *p) { return QM_FRAG(p)->dbg[0].file; }
static inline const char *qm_frag_func(void *p) { return QM_FRAG(p)->dbg[0].func; }
static inline unsigned long qm_frag_line(void *p) { return QM_FRAG(p)->dbg[0].line; }
#else
static inline const char *qm_frag_file(void *p) { return NULL; }
static inline const char *qm_frag_func(void *p) { return NULL; }
static inline unsigned long qm_frag_line(void *p) { return 0; }
#endif
#endif

#ifdef STATISTICS
static inline unsigned long qm_get_size(struct qm_block *qm)
{
	return qm->size;
}
static inline unsigned long qm_get_used(struct qm_block *qm)
{
	return qm->used;
}
static inline unsigned long qm_get_free(struct qm_block *qm)
{
	return qm->size - qm->real_used;
}
static inline unsigned long qm_get_real_used(struct qm_block *qm)
{
	return qm->real_used;
}
static inline unsigned long qm_get_max_real_used(struct qm_block *qm)
{
	return qm->max_real_used;
}
static inline unsigned long qm_get_frags(struct qm_block *qm)
{
	return qm->fragments;
}
#endif /* STATISTICS */

unsigned long qm_get_dbg_pool_size(unsigned int hist_size);

#endif
