/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2011 Marina.Rodeo Solutions
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
 *
 *
 * history:
 * ---------
 *  2011-05-xx  created (razvancrainea)
 */


#ifndef _EV_DATAGRAM_H_
#define _EV_DATAGRAM_H_

/* transport protocols name */
#define UDP_NAME	"udp"
#define UDP_STR		{ UDP_NAME, sizeof(UDP_NAME) - 1}
#define UNIX_NAME	"unix"
#define UNIX_STR	{ UNIX_NAME, sizeof(UNIX_NAME) - 1}
/* module flag */
#define DGRAM_UDP_FLAG		(1 << 30)
#define DGRAM_UNIX_FLAG		(1 << 29)

/* separation char */
#define COLON_C				':'

struct dgram_socks {
	int udp_sock;
	int unix_sock;
};

#endif
