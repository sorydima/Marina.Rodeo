/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Voice Sistem SRL
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

#ifndef _DB_PS_H
#define _DB_PS_H

typedef void * db_ps_t;

/** Is any prepared statement provided for the next query? */
#define CON_HAS_PS(cn)  ((cn)->curr_ps)

/** Does the connection has attached an uninitialized prepared statement? */
#define CON_HAS_UNINIT_PS(cn)  (*((cn)->curr_ps)==NULL)

/** Pointer to the currently used prepared statement */
#define CON_CURR_PS(cn)      (*(cn)->curr_ps)

/** Wipe the address of the currently used prepared statement */
#define CON_RESET_CURR_PS(cn)    *((void***)&(cn)->curr_ps)=NULL

/** Set the address of the currently used prepared statement */
#define CON_SET_CURR_PS(cn, ptr)    *((void***)&(cn)->curr_ps)=ptr

#endif


