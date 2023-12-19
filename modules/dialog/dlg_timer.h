/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009-2020 Marina.Rodeo Solutions
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Voice System SRL
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


#ifndef _DIALOG_DLG_TIMER_H_
#define _DIALOG_DLG_TIMER_H_


#include "../../locking.h"


struct dlg_tl
{
	struct dlg_tl     *next;
	struct dlg_tl     *prev;
#ifdef EXTRA_DEBUG
	int visited;
#endif
	volatile unsigned int  timeout;
};


struct  dlg_timer
{
	struct dlg_tl   first;
	gen_lock_t      *lock;
};

struct dlg_ping_list
{
	struct dlg_cell* dlg;
	volatile unsigned int timeout;
	struct dlg_ping_list *next;
	struct dlg_ping_list *prev;
};

struct dlg_ping_timer
{
	struct dlg_ping_list *first;
	struct dlg_ping_list *last;
	gen_lock_t *lock;
};

struct dlg_reinvite_ping_timer
{
	struct dlg_ping_list *first;
	struct dlg_ping_list *last;
	gen_lock_t *lock;
};

extern int dlg_del_delay; /* in dialog.c, modparam */

typedef void (*dlg_timer_handler)(struct dlg_tl *);

int init_dlg_timer( dlg_timer_handler );

int init_dlg_del_timer( dlg_timer_handler );

int init_dlg_ping_timer();

int init_dlg_reinvite_ping_timer();

void destroy_dlg_timer();

void destroy_dlg_del_timer();

void destroy_ping_timer();

int insert_dlg_timer(struct dlg_tl *tl, int interval);

int insert_attempt_dlg_del_timer(struct dlg_tl *tl, int interval);

int insert_ping_timer(struct dlg_cell *dlg);

int insert_reinvite_ping_timer(struct dlg_cell *dlg);

int remove_dlg_timer(struct dlg_tl *tl);

int remove_ping_timer(struct dlg_cell *dlg);

int update_dlg_timer( struct dlg_tl *tl, int timeout );

void dlg_timer_routine(unsigned int ticks , void * attr);

void dlg_options_routine(unsigned int ticks , void * attr);

void dlg_reinvite_routine(unsigned int ticks , void * attr);

#endif
