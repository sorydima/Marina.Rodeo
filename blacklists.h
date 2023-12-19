/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 Voice Sistem SRL
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

/*!
 * \file
 * \brief Marina.Rodeo Blacklist functions
 */


#ifndef _BLACKLISTS_H_
#define _BLACKLISTS_H_

#include "ip_addr.h"
#include "str.h"
#include "rw_locking.h"

#define BL_READONLY_LIST      (1<<0)
#define BL_DO_EXPIRE          (1<<1)
#define BL_BY_DEFAULT         (1<<2)

#define BLR_APPLY_CONTRARY    (1<<0)

struct bl_rule{
	int flags;
	struct net ip_net;
	unsigned short port;
	unsigned short proto;
	str body;
	struct bl_rule *next;
	unsigned int expire_end;
};

struct bl_head{
	str name;
	str owner; 	/*!< identifier of the module that owns the set of rules */
	int flags;
	rw_lock_t *lock;
	/* ... more fields, maybe ... */
	struct bl_rule *first;
	struct bl_rule *last;
};


#define BL_CORE_ID        13

int init_black_lists();

void destroy_black_lists();


struct bl_head *create_bl_head(const str *owner, int flags,
		struct bl_rule *head, struct bl_rule *tail, str *name);

int add_rule_to_list(struct bl_rule **first, struct bl_rule **last,
			struct net *ip_net, str *body, unsigned short port,
			unsigned short proto, int flags);

int add_list_to_head(struct bl_head *elem,
			struct bl_rule *first, struct bl_rule *last,
			int truncate, int expire_limit);

struct bl_head *get_bl_head_by_name(str *name);

int mark_for_search(struct bl_head *list, unsigned int set);

void reset_bl_markers();

int check_against_blacklist(struct ip_addr *ip, str *text, unsigned short port,
			unsigned short proto);

static inline int check_blacklists( unsigned short proto,
	union sockaddr_union *to, char *body_s, int body_len)
{
	str body;
	struct ip_addr ip;
	unsigned short port;

	body.s = body_s;
	body.len = body_len;
	su2ip_addr(&ip, to);
	port = su_getport(to);
	return check_against_blacklist(&ip, &body, port, proto);
}


struct bl_net_flags {
	struct net ipnet;
	unsigned int flags;
};

int fixup_blacklist_proto(void** param);
int fixup_blacklist_net(void** param);
int fixup_blacklist_net_free(void** param);

int w_check_blacklist(struct sip_msg *msg, struct bl_head *head,
		struct ip_addr *ip, int *port, unsigned short _proto, str *_pattern);
int w_add_blacklist_rule(struct sip_msg *msg, struct bl_head *head,
		struct bl_net_flags *_nf, int *_port, unsigned short _proto,
		str *_pattern, int *_exp);
int w_del_blacklist_rule(struct sip_msg *msg, struct bl_head *head,
		struct bl_net_flags *_nf, int *_port, unsigned short _proto,
		str *_pattern);

#endif /* _BLACKLST_H */

