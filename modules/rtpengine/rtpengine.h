/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2003 Porta Software Ltd
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
 * History:
 * ---------
 * 2014-06-17 Imported from rtpproxy module
*/


#ifndef _RTPENGINE_H
#define _RTPENGINE_H

#include "bencode.h"
#include "../../str.h"

/* flags for set, node, and socket management */
#define RTPE_TEARDOWN_NODE    (1<<0)
#define RTPE_TEARDOWN_SET     (1<<1)
#define RTPE_TEARDOWN_SOCKETS (1<<2)

struct rtpe_node {
	unsigned int		idx;			/* overall index */
	str					rn_url;			/* unparsed, deletable, NULL-term */
	int					rn_umode;
	char				*rn_address;	/* substring of rn_url */
	int					rn_disabled;	/* found unaccessible? */
	unsigned			rn_weight;		/* for load balancing */
	unsigned int		rn_recheck_ticks;
	int					rn_flags;
	struct rtpe_node	*rn_next;
};


struct rtpe_set{
	unsigned int 		id_set;
	unsigned			weight_sum;
	unsigned int		rtpe_node_count;
	int 				set_disabled;
	unsigned int		set_recheck_ticks;
	int 				set_flags;
	struct rtpe_node	*rn_first;
	struct rtpe_node	*rn_last;
	struct rtpe_set     *rset_next;
};


struct rtpe_set_head{
	struct rtpe_set		*rset_first;
	struct rtpe_set		*rset_last;
};


struct rtpe_version{
	unsigned int version;
	int version_flags;
	struct rtpe_version *version_next;
};


struct rtpe_version_head{
	unsigned int version_count;
	struct rtpe_version *version_first;
	struct rtpe_version *version_last;
};

#define RTPENGINE_TABLE_VERSION 1

#endif
