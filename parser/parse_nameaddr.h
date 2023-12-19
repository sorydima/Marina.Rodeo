/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
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
 * History
 * --------
 * 2003-03-24 Created by janakj
 */

#ifndef PARSE_NAMEADDR_H
#define PARSE_NAMEADDR_H

#include <stdio.h>
#include "../str.h"

/*
 * Name-addr structure, see RFC3261 for more details
 */
typedef struct name_addr {
	str name;   /* Display name part */
	str uri;    /* Uri part without surrounding <> */
	int len;    /* Total length of the field (including all
		    * whitechars present in the parsed message */
} name_addr_t;


/*
 * Parse name-addr part, the given string can be longer,
 * parsing will stop when closing > is found
 */
int parse_nameaddr(str* _s, name_addr_t* _a);


/*
 * Print a name-addr structure, just for debugging
 */
void print_nameaddr(FILE* _o, name_addr_t* _a);


#endif /* PARSE_NAMEADDR_H */
