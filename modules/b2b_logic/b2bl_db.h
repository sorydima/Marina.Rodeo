/*
 * back-to-back logic module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2011 Free Software Fundation
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
 * History:
 * --------
 *  2011-04-04  initial version (Anca Vamanu)
 */

#ifndef B2BL_DB_H
#define B2BL_DB_H

#include "records.h"

#define UPDATE_DBFLAG(dlg) do{ \
	if(dlg->db_flag==NO_UPDATEDB_FLAG) \
		dlg->db_flag = UPDATEDB_FLAG; \
}while(0)

void b2b_logic_dump(int no_lock);
int b2b_logic_restore(void);
void b2bl_db_insert(b2bl_tuple_t* tuple);
void b2bl_db_update(b2bl_tuple_t* tuple);

#endif
