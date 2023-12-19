/*
 * MySQL module row related functions
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2008 1&1 Internet AG
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


#include "../../dprint.h"
#include "../../mem/mem.h"
#include "../../db/db_row.h"
#include "../../db/db_ut.h"
#include "my_con.h"
#include "val.h"
#include "row.h"


/**
 * Convert a row from result into db API representation
 */
int db_mysql_convert_row(const db_con_t* _h, db_res_t* _res, db_row_t* _r)
{
	unsigned long* lengths;
	int i;

	if ((!_h) || (!_res) || (!_r)) {
		LM_ERR("invalid parameter value\n");
		return -1;
	}

	/* Save the number of columns in the ROW structure */
	ROW_N(_r) = RES_COL_N(_res);

	if (CON_HAS_PS(_h)) {
		for(i=0; i < CON_MYSQL_PS(_h)->cols_out; i++) {
			if (db_mysql_str2val(RES_TYPES(_res)[i], &(ROW_VALUES(_r)[i]),
			CON_PS_OUTCOL(_h, i).null?NULL:CON_PS_OUTCOL(_h, i).buf,
			CON_PS_OUTCOL(_h,i).len) < 0) {
				LM_ERR("failed to convert value from stmt\n");
				db_free_row(_r);
				return -3;
			}
		}
	} else {
		lengths = mysql_fetch_lengths(CON_RESULT(_h));
		for(i = 0; i < RES_COL_N(_res); i++) {
			if (db_mysql_str2val(RES_TYPES(_res)[i], &(ROW_VALUES(_r)[i]),
			((MYSQL_ROW)CON_ROW(_h))[i], lengths[i]) < 0) {
				LM_ERR("failed to convert value\n");
				LM_DBG("free row at %p\n", _r);
				db_free_row(_r);
				return -3;
			}
		}
	}
	return 0;
}
