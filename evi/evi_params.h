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
 *  2011-05-xx  created (razvancrainea)
 */

#ifndef _EVI_PARAMS_H_
#define _EVI_PARAMS_H_

#include "../str.h"

#define EVI_INT_VAL		0x01	/* val is int */
#define EVI_STR_VAL		0x02	/* val is str */

#define EVI_FREE_LIST		(1<<31)	/* should free params list */

typedef struct evi_param_ {
	int flags;
	union {
		int n;
		str s;
	} val;
	str name;
	struct evi_param_ *next;
} evi_param_t, *evi_param_p;

/*
 * Remember to initilize this structure with 0
 * or use the functions below to alloc and free it
 */
typedef struct evi_params_ {
	int flags;
	evi_param_p first;
	evi_param_p last;
} evi_params_t, *evi_params_p;

/* used to build parameters list */
evi_params_p evi_get_params(void);
/* frees all parameters */
void evi_free_params(evi_params_p);

/* generic parameter add */
int evi_param_add(evi_params_p list, const str *name, const void *param, int flags);

/* adds an integer to the list */
#define evi_param_add_int(p_list, p_name, p_int) \
		evi_param_add(p_list, p_name, p_int, EVI_INT_VAL)

/* adds a string to the list */
#define evi_param_add_str(p_list, p_name, p_str) \
		evi_param_add(p_list, p_name, p_str, EVI_STR_VAL)

/* creates a new parameter */
evi_param_p evi_param_create(evi_params_p list, const str *name);

/* sets the value of a parameter */
int evi_param_set(evi_param_p element, const void *param, int flags);

/* sets an integer value to a parameter */
#define evi_param_set_int(p_el, p_int) \
		evi_param_set(p_el, p_int, EVI_INT_VAL)

/* sets a string value to a parameter */
#define evi_param_set_str(p_el, p_str) \
		evi_param_set(p_el, p_str, EVI_STR_VAL)

evi_params_p evi_dup_shm_params(evi_params_p);
void evi_free_shm_params(evi_params_p);


#endif
