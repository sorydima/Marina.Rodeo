/*
 * XMPP Module
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Voice Sistem S.R.L.
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
 * Author: Andreea Spirea
 *
 */

#ifndef _NETWORK_H
#define _NETWORK_H

extern int net_listen(char *server, int port);
extern int net_connect(char *server, int port);
extern int net_send(int fd, const char *buf, int len);
extern int net_printf(int fd, char *format, ...) __attribute__ ((format (printf, 2, 3)));
extern char *net_read_chunk(int fd, int size);
extern char *net_read_static(int fd);

#endif /* _NETWORK_H */
