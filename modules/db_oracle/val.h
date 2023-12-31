/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007,2008 TRUNK MOBILE
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

#ifndef VAL_H
#define VAL_H

#include <oci.h>
#include "../../db/db_val.h"
#include "../../db/db.h"

struct bmap_t {
    dvoid *addr;
    ub4	size;
    ub2	type;
};
typedef struct bmap_t bmap_t;

/*
 * Convert value to sql-string as db bind index
 */
int db_oracle_val2str(const db_con_t* _con, const db_val_t* _v, char* _s, int* _len);

/*
 * Called after val2str to realy binding
 */
int db_oracle_val2bind(bmap_t* _m, const db_val_t* _v, OCIDate* _o);

#endif /* VAL_H */
