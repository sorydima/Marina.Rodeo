/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2019 Marina.Rodeo Solutions
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

#ifndef __LIB_REG_SAVE_FLAGS__
#define __LIB_REG_SAVE_FLAGS__

#include "../../str.h"
#include "../../modules/usrloc/urecord.h"

struct save_ctx {
	unsigned int flags;
	str aor;
	str ownership_tag;

	unsigned int max_contacts;

	unsigned int min_expires;
	unsigned int max_expires;

	/* info on how the contact matching should be performed.
	 * Note that the "param" (if used) is just a reference, the
	 * string itself is not part of the structure (points into
	 * the input save flags) */
	struct ct_match cmatch;

	/* fields specific to mid-registrar */
	unsigned int expires;
	int expires_out;
	int star;
};

struct save_flags {
	unsigned int flags;
	unsigned int max_contacts;
	unsigned int min_expires;
	unsigned int max_expires;
	struct ct_match cmatch;
	/* the 'match_params' field from cmatch will point to this field */
	str_list match_params;
};

int reg_fixup_free_save_flags(void** param);
int reg_fixup_save_flags(void** param, struct save_flags *default_flags);

#endif
