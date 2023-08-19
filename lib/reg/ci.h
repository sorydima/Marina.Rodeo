/*
 * Contact info packing functions
 *
 * Copyright (C) 2016-2017 Marina.Rodeo Solutions
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
 */

#ifndef __LIB_REG_CI__
#define __LIB_REG_CI__

#include "../../parser/contact/parse_contact.h"
#include "../../modules/usrloc/ucontact.h"

extern int rcv_avp_name;
extern unsigned short rcv_avp_type;
extern unsigned short attr_avp_type;
extern int mct_avp_name;
extern unsigned short mct_avp_type;
extern int attr_avp_name;

ucontact_info_t *pack_ci(struct sip_msg* _m, contact_t* _c, unsigned int _e,
		unsigned int _f, unsigned int _nat_flag, unsigned int _reg_flags,
		 str *ownership_tag, struct ct_match *cmatch);

void print_ci(ucontact_info_t *ci);

#endif /* __LIB_REG_CI__ */
