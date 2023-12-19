/*
 * Contact header field body parser
 *
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
 * History:
 * -------
 *  2003-03-25 Adapted to use new parameter parser (janakj)
 */


#ifndef PARSE_CONTACT_H
#define PARSE_CONTACT_H

#include <stdio.h>
#include "../hf.h"
#include "../../str.h"
#include "../msg_parser.h"
#include "contact.h"


typedef struct contact_body {
	unsigned char star;    /* Star contact */
	contact_t* contacts;   /* List of contacts */
} contact_body_t;


/*
 * Parse contact header field body
 */
int parse_contact(struct hdr_field* _h);


/*
 * Free all memory
 */
void free_contact(contact_body_t** _c);


/*
 * Print structure, for debugging only
 */
void log_contact(contact_body_t* _c);


/*
 * Contact header field iterator, returns next contact if any, it doesn't
 * parse message header if not absolutely necessary
 */
int contact_iterator(contact_t** c, struct sip_msg* msg, contact_t* prev);


/*
 * Indicates whether the param's value should be quoted
 */
int should_quote_contact_param_value(str *val);

#endif /* PARSE_CONTACT_H */
