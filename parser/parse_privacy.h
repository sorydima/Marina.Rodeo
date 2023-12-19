/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (c) 2006 Juha Heinanen
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

#ifndef PARSE_PRIVACY_H
#define PARSE_PRIVACY_H

#include "../mem/mem.h"
#include "msg_parser.h"


/* bitmap of Privacy header privacy values
 * (http://www.iana.org/assignments/sip-priv-values)
 */
enum privacy_value {
	PRIVACY_USER=1,
	PRIVACY_HEADER=2,
	PRIVACY_SESSION=4,
	PRIVACY_NONE=8,
	PRIVACY_CRITICAL=16,
	PRIVACY_ID=32,
	PRIVACY_HISTORY=64
};


/*
 * casting macro for accessing enumeration of priv-values
 */
#define get_privacy_values(p_msg) \
	((unsigned int)(long)((p_msg)->privacy->parsed))


/*
 * Parse Privacy HF.  Returns 0 on success and -1 on failure.
 */
int parse_privacy(struct sip_msg *msg);


/*
 * Parse a privacy value pointed by start that can be at most max_len long.
 * Returns length of matched privacy value or NULL otherwise.
 */
unsigned int parse_priv_value(char* start, unsigned int max_len,
                              unsigned int* value);


#endif /* PARSE_PRIVACY_H */
