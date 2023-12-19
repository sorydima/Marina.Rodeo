/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2019 Marina.Rodeo Project
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
 * Foundation Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include "clustering.h"

int enable_clustering = 0;

static struct clusterer_binds c_api;


int ureg_cluster_shtag_is_active( str *tag_name, int c_id)
{
	if ( c_id<=0 || tag_name->len==0 ||
	(enable_clustering && c_api.shtag_get( tag_name, c_id)==SHTAG_STATE_ACTIVE) )
		/* no clustering support or sharing tag found on active */
		return 1;

	return 0;
}


int ureg_init_cluster(shtag_cb_f f)
{
	if (load_clusterer_api(&c_api)!=0) {
		LM_ERR("failed to find clusterer API - is clusterer "
			"module loaded?\n");
		return -1;
	}

	/* register callback to see when the sharing tag becomes active */
	if (c_api.shtag_register_callback( NULL /*any tag*/, -1/*any cluster*/,
	NULL/*param*/, f )<0) {
		LM_ERR("failed to register shatag callback\n");
		return -1;
	}

	return 0;
}


