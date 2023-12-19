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

#include "evi_modules.h"
#include "evi_core.h"
#include "../ut.h"

/* static events exported by the core */
static str evi_core_table[] = {
	CORE_EVENT_STR(THRESHOLD),
	/* FIXME - if no statistics, the EVI ids will not be working anymore,
	 * since we don't save the actual ID registered in EVI */
#ifdef STATISTICS
	CORE_EVENT_STR(SHM_THRESHOLD),
#endif
	CORE_EVENT_STR(PKG_THRESHOLD),
	CORE_EVENT_STR(PROC_AUTO_SCALE),
	CORE_EVENT_STR(TCP_DISCONNECT),
};

int evi_register_core(void)
{
	int i, size = sizeof(evi_core_table) / sizeof(str);

	for (i = 0; i < size; i++) {
		if (EVI_ERROR == evi_publish_event(evi_core_table[i]))
			return -1;
	}
	return 0;
}


