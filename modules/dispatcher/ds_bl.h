/**
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2012 Marina.Rodeo Solutions
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

#ifndef _DS_BL_H_
#define _DS_BL_H_

#include "../../blacklists.h"
#include "dispatch.h"

#define DS_BL_MAX_SETS		32

typedef struct _ds_bl_temp {
	char *text;
	str partition_name;
	struct _ds_bl_temp *next;
} ds_bl_temp_t;

struct ds_bl {
	unsigned int no_sets;
	unsigned int sets[DS_BL_MAX_SETS];

	str partition_name;
	struct bl_head *bl;
	struct ds_bl *next;
};

int set_ds_bl(modparam_t type, void *val);
int set_ds_bl_partition(char *val, str partition_name);

int init_ds_bls(void);

void destroy_ds_bls(void);

int populate_ds_bls(ds_set_t *sets, str partition_name);

#endif /* _DS_BL_H_ */
