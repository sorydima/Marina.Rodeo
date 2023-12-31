/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2005 iptelorg GmbH
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

/*!
 * \file
 * \brief IO wait poll methods (enum, strings, related function)
 * see \ref io_wait.h for more details
 */


#ifndef _poll_types_h
#define _poll_types_h

enum poll_types { POLL_NONE, POLL_POLL, POLL_EPOLL,
					POLL_SIGIO_RT, POLL_SELECT, POLL_KQUEUE, POLL_DEVPOLL,
					POLL_END};

/* all the function and vars are defined in io_wait.c */

extern char* poll_method_str[POLL_END];
extern char* poll_support;


enum poll_types choose_poll_method();

/* returns 0 on success, and an error message on error */
char* check_poll_method(enum poll_types poll_method);

char* poll_method_name(enum poll_types poll_method);
enum poll_types get_poll_type(char* s);

void fix_poll_method( enum poll_types *poll_method );


#endif
