/*
 * Domain module headers
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2002-2003 Juha Heinanen
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
 */


#ifndef DOMAIN_MOD_H
#define DOMAIN_MOD_H


#include "../../db/db.h"
#include "../../str.h"
#include "../../usr_avp.h"


/*
 * Constants
 */
#define DOM_HASH_SIZE 128

/* flags for param source for is_domain_local() */
#define PARAM_SOURCE_NONE  (0)
#define PARAM_SOURCE_AVP   (1<<0)
#define PARAM_SOURCE_RURI  (1<<1)
#define PARAM_SOURCE_FROM  (1<<2)


/*
 * Type definitions
 */
struct domain_list {
	str domain;
	str attrs;
	struct domain_list *next;
};

typedef struct param_source {
	int source;       /* One of PARAM_SOURCE_XXX from above */

	int avp_type;     /* If source is an avp, the avp type else 0 */
	int_str avp_name; /* If source is an avp, the avp name else NULL */
} param_source;

/*
 * Module parameters variables
 */
extern int db_mode;             /* Database usage mode: 0 = no cache, 1 = cache */
extern str domain_table;	/* Domain table name */
extern str domain_col;   	/* Domain column name */
extern str domain_attrs_col;   	/* Domain attributes column name */


/*
 * Other module variables
 */
extern struct domain_list **hash_table_1; /* Hash table for domains */
extern struct domain_list **hash_table_2; /* Hash table for domains */
extern struct domain_list ***hash_table;  /* Current hash table */


#endif /* DOMAIN_MOD_H */
