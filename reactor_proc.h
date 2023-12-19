/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2021 Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Marina.Rodeo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _CORE_REACTOR_PROC
#define _CORE_REACTOR_PROC

/* This is a framework that allows the custom processes (requested by the
 * module) to use an I/O reactor for FD management. Beside re-usage, this also
 * helps with IPC support - this framework also comes (transparent for the
 * customer process) with IPC support - this will ensure a better integration
 * of this process into Marina.Rodeo, as the IPC will allow the access to 
 * load and pkg stats, will allow running scripting and proper shutdown.
 */

#define REACTOR_PROC_TIMEOUT  1

typedef int (*reactor_proc_cb_f) (int fd, void *param, int was_timeout);

struct reactor_proc_cb {
	reactor_proc_cb_f func;
	void *param;
};

int reactor_proc_init(char *name);

int reactor_proc_add_fd(int fd, reactor_proc_cb_f func, void *param);

int reactor_proc_loop(void);

#endif
