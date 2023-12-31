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
 *  2011-09-xx  created (vlad-paiu)
 */

#ifndef _CACHEDB_ID_H
#define _CACHEDB_ID_H

#include "../str.h"

#define CACHEDB_TLS_DOM_PARAM "tls_domain="
#define CACHEDB_TLS_DOM_PARAM_LEN (sizeof(CACHEDB_TLS_DOM_PARAM)-1)

/** Structure representing a database ID */
struct cachedb_id {
	char* scheme;        /**< URL scheme */
	char* group_name;    /**< Name of the URL group */
	char* username;      /**< Username, case sensitive */
	char* password;      /**< Password, case sensitive */
	char* host;          /**< Host or IP, case insensitive */
	unsigned short port; /**< Port number */
	char* database;      /**< Database, case sensitive */
	char* extra_options; /**< Extra Options */
	char* initial_url;   /**< Initial full URL */
	int flags;           /**< Flags for signaling various events */
};

#define CACHEDB_ID_NO_URL (1<<0)
#define CACHEDB_ID_MULTIPLE_HOSTS (1<<1)

/**
 * Create a new connection identifier
 * \param url database URL
 * \return new allocated db_id structure, NULL on failure
 */
struct cachedb_id* new_cachedb_id(const str* url);


/**
 * Compare two connection identifiers
 * \param id1 first identifier
 * \param id2 second identifier
 * \return 1 if both identifier are equal, 0 if there not equal
 */
int cmp_cachedb_id(struct cachedb_id* id1, struct cachedb_id* id2);


/**
 * Free a connection identifier
 * \param id the identifier that should released
 */
void free_cachedb_id(struct cachedb_id* id);


#endif /* _CACHEDB_ID_H */
