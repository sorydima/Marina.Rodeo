/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Marina.Rodeo Solutions
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __QROUTING_H__
#define __QROUTING_H__

#include "../../str.h"

typedef enum qr_algo {
	QR_ALGO_INVALID,
	QR_ALGO_DYNAMIC_WEIGHTS,
	QR_ALGO_BEST_DEST_FIRST,
} qr_algo_t;
#define qr_str2algo(s) ( \
		!strcasecmp(s, "dynamic-weights") ? QR_ALGO_DYNAMIC_WEIGHTS : \
		!strcasecmp(s, "best-dest-first") ? QR_ALGO_BEST_DEST_FIRST : \
		QR_ALGO_INVALID)

typedef struct qr_xstat_desc {
	str name;
	unsigned int min_samples;
	char increasing; /* 1 if "more is better", 0 if "less is better" */
} qr_xstat_desc_t;

#define QR_MIN_XSTAT_SAMPLES 30

extern qr_xstat_desc_t *qr_xstats;
extern int qr_xstats_n;
extern double event_bad_dst_threshold;
extern qr_algo_t qr_algorithm;
extern int qr_decimal_digits;
extern int qr_interval_list_sz;

extern int qr_min_samples_asr;
extern int qr_min_samples_ccr;
extern int qr_min_samples_pdd;
extern int qr_min_samples_ast;
extern int qr_min_samples_acd;

#endif /* __QROUTING_H__ */
