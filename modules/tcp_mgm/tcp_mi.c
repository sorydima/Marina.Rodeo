/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2022 Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "tcp_mi.h"
#include "tcp_db.h"

#include "../../dprint.h"

/* reloads data from the db */
mi_response_t *tcp_mi_reload(const mi_params_t *_, struct mi_handler *__)
{
	struct tcp_path *new_paths, *old_paths;
	int new_paths_sz;

	LM_INFO("reload data MI command received!\n");

	if (!tcp_db_url.s)
		return init_mi_error(500, MI_SSTR("DB url not set"));

	if (tcp_reload_paths(&new_paths, &new_paths_sz) < 0) {
		LM_ERR("failed to load TCP data\n");
		return init_mi_error(500, MI_SSTR("Failed to reload"));
	}

	lock_start_write(tcp_paths_lk);

	old_paths = tcp_paths;
	tcp_paths = new_paths;
	*tcp_paths_sz = new_paths_sz;

	lock_stop_write(tcp_paths_lk);

	shm_free(old_paths);
	return init_mi_result_ok();
}
