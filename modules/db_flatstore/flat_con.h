/*
 * Flatstore module connection structure
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2004 FhG Fokus
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

#ifndef _FLAT_CON_H
#define _FLAT_CON_H

#include <stdio.h>
#include <time.h>
#include "flat_id.h"

struct flat_con {
	struct flat_id* id;    /* Connection identifier */
	int ref;               /* Reference count */
	FILE* file;            /* File descriptor structure */
	struct flat_con* next; /* Next connection in the pool */
};


/*
 * Some convenience wrappers
 */
#define CON_FILE(db_con) (((struct flat_con*)((db_con)->tail))->file)

/* returns the filename of the table */
#define CON_FILENAME(db_con) (((struct flat_con*)((db_con)->tail))->id->table)


/*
 * Create a new connection structure,
 * open the MySQL connection and set reference count to 1
 */
struct flat_con* flat_new_connection(struct flat_id* id);


/*
 * Close the connection and release memory
 */
void flat_free_connection(struct flat_con* con);


/*
 * Reopen a connection
 */
int flat_reopen_connection(struct flat_con* con);


#endif /* _FLAT_CON_H */
