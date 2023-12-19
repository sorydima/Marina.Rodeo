/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2019 - Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or * (at your option) any later version
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
 */

#ifndef _NET_TCP_COMMON_H_
#define _NET_TCP_COMMON_H_

/* blocking connect on a non-blocking socket */
int tcp_connect_blocking(int s, const struct sockaddr *servaddr,
		socklen_t addrlen);

/* blocking connect on a non-blocking socket with timeout */
int tcp_connect_blocking_timeout(int fd, const struct sockaddr *servaddr,
                        socklen_t addrlen, int timeout_ms);


int tcp_sync_connect_fd(union sockaddr_union* src, union sockaddr_union* dst,
                 enum sip_protos proto, struct tcp_conn_profile *prof, enum si_flags flags);

struct tcp_connection* tcp_sync_connect(struct socket_info* send_sock,
               union sockaddr_union* server, struct tcp_conn_profile *prof,
               int *fd, int send2main);

/* Attempts do a connect to the given destination. It returns:
 *   1 - connect was done local (completed)
 *   0 - connect launched as async (in progress)
 *  -1 - error
 */
int tcp_async_connect(struct socket_info* send_sock,
           union sockaddr_union* server, struct tcp_conn_profile *prof,
           int timeout, struct tcp_connection** c, int *ret_fd, int send2main);

/* Responsible for writing the TCP send chunks - called under con write lock
 *	* if returns = 1 : the connection will be released for more writting
 *	* if returns = 0 : the connection will be released
 *	* if returns < 0 : the connection will be released as BAD /  broken
 */
int tcp_async_write(struct tcp_connection* con,int fd);

int tcp_write_on_socket(struct tcp_connection* con, int fd,
		char *buf, int len, int write_timeout, int async_write_timeout);

/* adds an async chunk to the connection pending list */
int tcp_async_add_chunk(struct tcp_connection *con, char *buf,
		int len, int lock);

/* returns the first chunk to be written */
struct tcp_async_chunk *tcp_async_get_chunk(struct tcp_connection *con);

void tcp_async_update_write(struct tcp_connection *con, int len);

#endif /* _NET_TCP_COMMON_H_ */
