/*
 * DBText module core functions
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
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
 * 2003-02-04 created by Daniel
 *
 */


#ifndef _DBT_RES_H_
#define _DBT_RES_H_

#include "../../db/db_op.h"
#include "../../db/db_res.h"

#include "dbt_lib.h"

typedef struct _dbt_result
{
	int nrcols;
	int nrrows;
	dbt_column_p colv;
	dbt_row_p rows;
	dbt_row_p last;
} dbt_result_t, *dbt_result_p;

//typedef db_res_t dbt_result_t, *dbt_result_p;

typedef struct _dbt_con
{
	dbt_cache_p con;
	dbt_result_p res;
	dbt_row_p row;
} dbt_con_t, *dbt_con_p;

#define DBT_CON_CONNECTION(db_con) (((dbt_con_p)((db_con)->tail))->con)
#define DBT_CON_RESULT(db_con)     (((dbt_con_p)((db_con)->tail))->res)
#define DBT_CON_ROW(db_con)        (((dbt_con_p)((db_con)->tail))->row)

dbt_result_p dbt_result_new(dbt_table_p, int*, int);
int dbt_result_free(dbt_result_p);
int dbt_row_match(dbt_table_p _dtp, dbt_row_p _drp, int* _lkey,
				 db_op_t* _op, db_val_t* _v, int _n);
int dbt_result_extract_fields(dbt_table_p _dtp, dbt_row_p _drp,
				int* lres, dbt_result_p _dres);
int dbt_result_print(dbt_result_p _dres);

int* dbt_get_refs(dbt_table_p, db_key_t*, int);
int dbt_cmp_val(dbt_val_p _vp, db_val_t* _v);
dbt_row_p dbt_result_new_row(dbt_result_p _dres);

#endif

