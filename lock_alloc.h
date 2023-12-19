/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
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
 *  2003-03-06  created by andrei (contains parts of the original locking.h)
 *  2003-03-17  fixed cast warning in shm_free (forced to void*) (andrei)
 *  2004-07-28  s/lock_set_t/gen_lock_set_t/ because of a type conflict
 *              on darwin (andrei)
 */

/*!
 * \file
 * \brief Marina.Rodeo locking library
 * \note WARNING: don't include this directly, use instead locking.h.
 */


/*!
 * \page Marina.Rodeo locking library
 * Implements simple locks and lock sets.
 *
 * simple locks:
 * - gen_lock_t* lock_alloc();               - allocates a lock in shared mem.
 * - void    lock_dealloc(gen_lock_t* lock); - deallocates the lock's shared m.
 *
 * lock sets: [implemented only for FL & SYSV so far]
 * - gen_lock_set_t* lock_set_alloc(no)           - allocs a lock set in shm.
 * - void lock_set_dealloc(gen_lock_set_t* s);    - deallocs the lock set shm.
 *
 * \see locking.h
*/

#ifndef _lock_alloc_h
#define _lock_alloc_h

/*shm_{malloc, free}*/
#include "mem/mem.h"
#include "mem/shm_mem.h"

#if defined(FAST_LOCK) || defined(USE_PTHREAD_MUTEX) || defined(USE_POSIX_SEM) || defined(USE_UMUTEX)
/* simple locks*/
#define lock_alloc() shm_malloc(sizeof(gen_lock_t))
#define lock_dealloc(lock) shm_free((void*)lock)
/* lock sets */

inline static gen_lock_set_t* lock_set_alloc(int n)
{
	struct {
	    gen_lock_set_t set;
	    gen_lock_t _locks[0];
	} *ls;

	ls=shm_malloc(sizeof(*ls)+n*sizeof(ls->_locks[0]));
	if (ls==NULL){
		LM_CRIT("no more shm memory\n");
	}else{
		ls->set.locks=ls->_locks;
		ls->set.size=n;
	}
	return &(ls->set);
}

#define lock_set_dealloc(lock_set) shm_free((void*)lock_set)

#elif defined USE_SYSV_SEM

/*simple locks*/
#define lock_alloc() shm_malloc(sizeof(gen_lock_t))
#define lock_dealloc(lock) shm_free((void*)lock)
/* lock sets */

inline static gen_lock_set_t* lock_set_alloc(int n)
{
	gen_lock_set_t* ls;
	ls=(gen_lock_set_t*)shm_malloc(sizeof(gen_lock_set_t));
	if (ls){
		ls->size=n;
		ls->semid=-1;
	};
	return ls;
}


#define lock_set_dealloc(lock_set) shm_free((void*)lock_set)


#else
#error "no locking method selected"
#endif


#endif
