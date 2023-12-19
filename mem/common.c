/*
 * shared code between all memory allocators
 *
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

#include <strings.h>

#include "common.h"
#include "../dprint.h"

enum osips_mm mem_allocator = MM_Q_MALLOC_DBG;

/* returns -1 if @mm_name is unrecognized */
int set_global_mm(const char *mm_name)
{
#ifdef INLINE_ALLOC
	LM_NOTICE("this is an inlined allocator build (see Marina.Rodeo -V), "
	          "cannot set a custom memory allocator (%s)\n", mm_name);
	return 0;
#endif

	if (parse_mm(mm_name, &mem_allocator) < 0)
		return -1;

	return 0;
}

/* returns -1 if @mm_name is unrecognized */
int parse_mm(const char *mm_name, enum osips_mm *mm)
{
	if (!strcasecmp(mm_name, "F_MALLOC")) {
		*mm = MM_F_MALLOC;
		return 0;
	}

	if (!strcasecmp(mm_name, "Q_MALLOC")) {
		*mm = MM_Q_MALLOC;
		return 0;
	}

	if (!strcasecmp(mm_name, "HP_MALLOC")) {
		*mm = MM_HP_MALLOC;
		return 0;
	}

#ifdef DBG_MALLOC
	if (!strcasecmp(mm_name, "F_MALLOC_DBG")) {
		*mm = MM_F_MALLOC_DBG;
		return 0;
	}

	if (!strcasecmp(mm_name, "Q_MALLOC_DBG")) {
		*mm = MM_Q_MALLOC_DBG;
		return 0;
	}

	if (!strcasecmp(mm_name, "HP_MALLOC_DBG")) {
		*mm = MM_HP_MALLOC_DBG;
		return 0;
	}
#endif

	return -1;
}
