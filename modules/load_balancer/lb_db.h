/*
 * load balancer module - complex call load balancing
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Voice Sistem SRL
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */



#ifndef LB_LB_DB_H_
#define LB_LB_DB_H_

#define LB_TABLE_NAME    "load_balancer"
#define LB_ID_COL        "id"
#define LB_GRP_ID_COL    "group_id"
#define LB_DST_URI_COL   "dst_uri"
#define LB_RESOURCES_COL "resources"
#define LB_PMODE_COL     "probe_mode"
#define LB_ATTRS_COL     "attrs"

#define LB_NO_COLS 6

#include "../../str.h"
#include "lb_data.h"

int init_lb_db(const str *db_url, char *table);

int lb_connect_db(const str *db_url);

void lb_close_db(void);

int lb_db_load_data( struct lb_data *data);

#endif
