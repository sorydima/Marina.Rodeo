/*
 * eXtended JABber module
 *
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
 */


#ifndef _XJAB_UTIL_H_
#define _XJAB_UTIL_H_

#include "xjab_base.h"
#include "xjab_jcon.h"
#include "../../str.h"

/**********             ***/

typedef struct _xj_jmsg_queue
{
	int len;		// maximum size of the queue
	int size;		// number of elements in the queue
	int cache;		// cache time (seconds)
	int *expire;	// expire time of the queued message
	xj_sipmsg *jsm;	// pointer to the message
	xj_jcon *ojc;	// pointer to the connection which will be used on sending
} t_xj_jmsg_queue, *xj_jmsg_queue;

/**********             ***/

typedef struct _xj_jcon_pool
{
	int len;					// maximum len of the pool
	xj_jcon *ojc;				// the connections to the Jabber
	t_xj_jmsg_queue jmqueue;	// messages queue
} t_xj_jcon_pool, *xj_jcon_pool;

/**********   LOOK AT IMPLEMENTATION OF FUNCTIONS FOR DESCRIPTION    ***/

xj_jcon_pool xj_jcon_pool_init(int, int, int);
int xj_jcon_pool_add(xj_jcon_pool, xj_jcon);
xj_jcon xj_jcon_pool_get(xj_jcon_pool, xj_jkey);
int xj_jcon_pool_del(xj_jcon_pool, xj_jkey);
void xj_jccon_pool_free(xj_jcon_pool);
void xj_jcon_pool_print(xj_jcon_pool);
int xj_jcon_pool_add_jmsg(xj_jcon_pool, xj_sipmsg, xj_jcon);
int xj_jcon_pool_del_jmsg(xj_jcon_pool, int);

/**********             ***/

#endif

