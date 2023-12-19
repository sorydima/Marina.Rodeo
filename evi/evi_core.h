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

#ifndef EVI_CORE_H
#define EVI_CORE_H

/* events id declared - these must be always incremented by one */
/* FIXME - first EVI is E_CORE_SR_STATUS_CHANGED, done outside of EVI core here, 
 * which is why we start indexing at 1 */ 
#define EVI_THRESHOLD_ID	1
#define EVI_SHM_THRESHOLD_ID	2
#define EVI_PKG_THRESHOLD_ID	3
#define EVI_PROC_AUTO_SCALE_ID	4
#define EVI_TCP_DISCONNECT	5


#define EVI_CORE_PREFIX		"E_CORE_"

#define CORE_EVENT_STR(_event) \
		{ EVI_CORE_PREFIX # _event, sizeof(EVI_CORE_PREFIX # _event)-1 }

extern int evi_register_core(void);

#endif /* EVI_CORE_H */
