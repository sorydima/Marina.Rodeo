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

/* the cluster ID  */
int nt_cluster_id = 0;

str nt_cluster_shtag = {NULL,0};

static struct clusterer_binds c_api;


int nt_cluster_shtag_is_active(void)
{
	if ( nt_cluster_id<=0 || nt_cluster_shtag.s==NULL ||
	c_api.shtag_get(&nt_cluster_shtag,nt_cluster_id)==SHTAG_STATE_ACTIVE )
		/* no clustering support or sharing tag found active */
		return 1;

	return 0;
}


int nt_init_cluster(void)
{
	if (load_clusterer_api(&c_api)!=0) {
		LM_ERR("failed to find clusterer API - is clusterer "
			"module loaded?\n");
		return -1;
	}

	/* "register" the sharing tag */
	if (nt_cluster_shtag.s) {
		nt_cluster_shtag.len = strlen(nt_cluster_shtag.s);
		if (c_api.shtag_get( &nt_cluster_shtag, nt_cluster_id)<0) {
			LM_ERR("failed to initialized the sharing tag <%.*s>\n",
				nt_cluster_shtag.len, nt_cluster_shtag.s);
			return -1;
		}
	} else {
		nt_cluster_shtag.len = 0;
	}

	return 0;
}


