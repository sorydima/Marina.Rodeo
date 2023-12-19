/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Voice Sistem
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
 *  2006-02-07  initial version (bogdan)
 *  2006-11-28  modified stats_trans_rpl to track individual message codes
 *              (Jeffrey Magder - SOMA Networks)
 */


#ifndef _T_STATS_H
#define _T_STATS_H

#include "../../statistics.h"

extern int tm_enable_stats;


/* statistic variables */
extern stat_var *tm_rcv_rpls;
extern stat_var *tm_rld_rpls;
extern stat_var *tm_loc_rpls;
extern stat_var *tm_uas_trans;
extern stat_var *tm_uac_trans;
extern stat_var *tm_trans_2xx;
extern stat_var *tm_trans_3xx;
extern stat_var *tm_trans_4xx;
extern stat_var *tm_trans_5xx;
extern stat_var *tm_trans_6xx;
extern stat_var *tm_trans_inuse;

extern stat_var *tm_retran_req_T11;
extern stat_var *tm_retran_req_T12;
extern stat_var *tm_retran_req_T13;
extern stat_var *tm_retran_req_T2;
extern stat_var *tm_retran_rpl_T2;
extern stat_var *tm_timeout_fr;
extern stat_var *tm_timeout_fr_inv;

extern stat_var *tm_cluster_reply_tx;
extern stat_var *tm_cluster_request_tx;
extern stat_var *tm_cluster_cancel_tx;
extern stat_var *tm_cluster_reply_rx;
extern stat_var *tm_cluster_request_rx;
extern stat_var *tm_cluster_cancel_rx;


#ifdef STATISTICS
/* update the statistics regading the final codes of the transactions
 * A single transaction will generate a single update on one of
 * these statistics
 */
inline static void stats_trans_code( int code)
{
	if (tm_enable_stats) {
		if (code>=700) {
			return;
		} else if (code>=600) {
			update_stat( tm_trans_6xx, 1);
		} else if (code>=500) {
			update_stat( tm_trans_5xx, 1);
		} else if (code>=400) {
			update_stat( tm_trans_4xx, 1);
		} else if (code>=300) {
			update_stat( tm_trans_3xx, 1);
		} else if (code>=200) {
			update_stat( tm_trans_2xx, 1);
		}
	}
}

/* update the statistics regading the final replies sent to UAC side
 * A single transaction may generate multiple updates on different
 * statistics if (1) there is a retransmission of the final reply or
 * (2) there are multiple final replies (like multi 200 OK)
 */
inline static void stats_trans_rpl( int code, int local )
{
	stat_var *numerical_stat;

	if (tm_enable_stats) {
		if (local)
			update_stat( tm_loc_rpls, 1);
		else
			update_stat( tm_rld_rpls, 1);

		numerical_stat =
			get_stat_var_from_num_code(code, 1);

		/* Increment the status code. */
		if (numerical_stat != NULL)
			update_stat(numerical_stat, 1);

	}
}

inline static void stats_trans_new( int local ) {
	if (tm_enable_stats) {
		update_stat( tm_trans_inuse, 1 );
		if (local)
			update_stat( tm_uac_trans, 1 );
		else
			update_stat( tm_uas_trans, 1 );
	}
}
#else
	#define stats_trans_code( _code )
	#define stats_trans_rpl( _code , _local )
	#define stats_trans_new( _local )
#endif

#endif
