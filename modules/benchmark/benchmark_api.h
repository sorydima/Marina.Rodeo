/*
 * Benchmarking module for Marina.Rodeo
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 Collax GmbH
 *                    (Bastian Friedrich <bastian.friedrich@collax.com>)
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 Voice Sistem SRL
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
 */

#ifndef BENCHMARK_API_H
#define BENCHMARK_API_H

#include "../../sr_module.h"

typedef int (*bm_register_timer_f)(char *tname, int mode, unsigned int *id);
typedef int (*bm_start_timer_f)(unsigned int id);
typedef int (*bm_log_timer_f)(unsigned int id);

struct bm_binds {
	bm_register_timer_f bm_register;
	bm_start_timer_f bm_start;
	bm_log_timer_f bm_log;
};

typedef int(*load_bm_f)(struct bm_binds *bmb);

int load_bm(struct bm_binds *bmb);

static inline int load_bm_api( struct bm_binds *bmb )
{
	load_bm_f load_bm;

	/* import the benchmark auto-loading function */
	if ( !(load_bm=(load_bm_f)find_export("load_bm", 0)))
	{
		LM_ERR("can't import load_bm\n");
		return -1;
	}
	/* let the auto-loading function load all benchmarking stuff */
	if (load_bm( bmb )==-1)
	{
		LM_ERR("load_bm failed\n");
		return -1;
	}

	return 0;
}

#endif /* BENCHMARK_API_H */
