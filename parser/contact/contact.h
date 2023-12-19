/*
 * Contact data type
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
 *  2003-030-25 Adapted to use new parameter parser (janakj)
 */


#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>
#include "../../str.h"
#include "../parse_param.h"


/*
 * Structure representing a Contact HF body
 */
typedef struct contact {
	str name;               /* Name part */
	str uri;                /* contact uri */
	param_t* instance;      /* +sip.instance parameter hook */
	param_t* q;             /* q parameter hook */
	param_t* expires;       /* expires parameter hook */
	param_t* methods;       /* methods parameter hook */
	param_t* received;      /* received parameter hook */
	param_t* params;        /* List of all parameters */
	int len;                /* Total length of the element */
	struct contact* next;   /* Next contact in the list */
} contact_t;


/*
 * Parse contacts in a Contact HF
 *
 * WARNING: "_s" will be mangled, make a copy beforehand!
 */
int parse_contacts(str* _s, contact_t** _c);


/*
 * Free list of contacts
 * _c is head of the list
 */
void free_contacts(contact_t** _c);


/*
 * Debug print a list of contacts, just for debugging
 */
void log_contacts(contact_t* _c);


#endif /* CONTACT_H */
