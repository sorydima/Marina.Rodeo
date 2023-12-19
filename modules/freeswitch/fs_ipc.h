/*
 * Inter-process communication primitives
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2017 Marina.Rodeo Solutions
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 */

#ifndef __FS_IPC__
#define __FS_IPC__

#include "fs_api.h"

typedef struct _fs_ipc_esl_cmd {
	fs_evs *sock;
	str fs_cmd;
	unsigned long esl_reply_id;
} fs_ipc_esl_cmd;

typedef struct _fs_ipc_esl_event {
	fs_evs *sock;
	str name;
	char *body;
} fs_ipc_esl_event;

int fs_ipc_init(void);
unsigned long fs_ipc_send_esl_cmd(fs_evs *sock, const str *fs_cmd);
int fs_ipc_dispatch_esl_event(fs_evs *sock, const str *name,
                              const char *body, ipc_handler_type ipc_type);

#endif /* __FS_IPC__ */
