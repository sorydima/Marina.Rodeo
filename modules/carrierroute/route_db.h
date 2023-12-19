/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 1&1 Internet AG
 *
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

/**
 * @file route_db.h
 * @brief Functions for loading routing data from a database.
 */

#ifndef SP_ROUTE_ROUTE_DB_H
#define SP_ROUTE_ROUTE_DB_H

#include "../../db/db.h"
#include "carrier_tree.h"

/**
 * Initializes the db API
 *
 * @return 0 means ok, -1 means an error occurred.
 */
int db_init(void);

void main_db_close(void);

int db_child_init(void);

void db_destroy(void);

/**
 * Loads the routing data from the database given in global
 * variable db_url and stores it in routing tree rd.
 *
 * @param rd Pointer to the route data tree where the routing data
 * shall be loaded into
 *
 * @return 0 means ok, -1 means an error occurred
 *
 */
int load_route_data (struct rewrite_data * rd);

int load_user_carrier(str * user, str * domain);

#endif
