/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (c) 2004 Juha Heinanen
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
 * -------
 * 2006-03-02  parse_allow() parses and cumulates all ALLOW headers (bogdan)
 */

#ifndef PARSE_ALLOW_H
#define PARSE_ALLOW_H

#include "../mem/mem.h"
#include "msg_parser.h"


/*
 * casting macro for accessing Allow body
 */
#define get_allow_methods(p_msg) \
	(((struct allow_body*)(p_msg)->allow->parsed)->allow_all)


struct allow_body {
	unsigned int allow;            /* allow mask for the current hdr */
	unsigned int allow_all;        /* allow mask for the all allow hdr - it's
	                                * set only for the first hdr in sibling
	                                * list*/
};

/*
 * Parse all Allow HFs
 */
int parse_allow( struct sip_msg *msg);


static inline void free_allow(struct allow_body **ab)
{
	if (ab && *ab) {
		pkg_free(*ab);
		*ab = 0;
	}
}

#endif /* PARSE_ALLOW_H */
