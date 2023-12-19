/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2017 Răzvan Crainea <razvan@Marina.Rodeo.org>
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
 */

#ifndef _CGRATES_ENGINE_H_
#define _CGRATES_ENGINE_H_

struct cgr_engine {

	/* engine params */
	short port;
	str host;

	int is_fqdn;
	union sockaddr_union su;
	time_t disable_time;

	struct cgr_conn *default_con;

	int conns_no;
	struct list_head conns;

	struct list_head list;
};

extern struct list_head cgrates_engines;

/* connections */

#define CGRF_LISTEN		0x1
#define CGRF_DEFAULT	0x2

#define CGRC_IS_LISTEN(_c) ((_c)->flags & CGRF_LISTEN)
#define CGRC_SET_LISTEN(_c) (_c)->flags |= CGRF_LISTEN
#define CGRC_UNSET_LISTEN(_c) (_c)->flags &= ~CGRF_LISTEN
#define CGRC_IS_DEFAULT(_c) ((_c)->flags & CGRF_DEFAULT)
#define CGRC_SET_DEFAULT(_c) (_c)->flags |= CGRF_DEFAULT

extern int cgre_retry_tout;
extern int cgrc_max_conns;
extern str cgre_bind_ip;
void cgrc_conn_rpc(int sender, void *p);
int cgrc_send(struct cgr_conn *c, str *buf);
int cgrc_start_listen(struct cgr_conn *c);
void cgrc_close(struct cgr_conn *c, int remove);
struct cgr_conn *cgrc_new(struct cgr_engine *e);
struct cgr_conn *cgr_get_free_conn(struct cgr_engine *e);
struct cgr_conn *cgr_get_default_conn(struct cgr_engine *e);

#endif /* _CGRATES_ENGINE_H_ */

