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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "common.h"

/* common registrar modparams */
int expires_max_deviation;  /*!< +/- max deviation for contact lifetimes */
int max_contacts = 0;		/*!< Maximum number of contacts per AOR
                                 (0 == no checking) */
int max_username_len = USERNAME_MAX_SIZE;
int max_domain_len   = DOMAIN_MAX_SIZE;
int max_aor_len      = MAX_AOR_LEN;
int max_contact_len  = CONTACT_MAX_SIZE;

int reg_init_globals(void)
{
	if (reg_init_lookup() != 0) {
		LM_ERR("failed to init lookup() support\n");
		return -1;
	}

	realm_prefix.len = strlen(realm_prefix.s);
	rcv_param.len = strlen(rcv_param.s);

	if (expires_max_deviation < 0) {
		expires_max_deviation = -expires_max_deviation;
		LM_ERR("'expires_max_deviation' cannot be negative, fixing to %d\n",
		       expires_max_deviation);
	}

	if (expires_max_deviation > RAND_MAX/2) {
		expires_max_deviation = RAND_MAX/2;
		LM_ERR("'expires_max_deviation' is too large, fixing to %d\n",
		       expires_max_deviation);
	}

	if (max_expires && max_expires < min_expires) {
		LM_ERR("max_expires (%d) < min_expires (%d), "
		       "bumping max_expires up to %d\n", max_expires,
		       min_expires, min_expires);
		max_expires = min_expires;
	}

	if (default_expires < min_expires) {
		LM_ERR("default_expires (%d) < min_expires (%d), "
		       "bumping default_expires up to %d\n", default_expires,
		       min_expires, min_expires);
		default_expires = min_expires;
	}

	if (max_expires && default_expires > max_expires) {
		LM_ERR("default_expires (%d) > max_expires (%d), "
		       "bumping default_expires down to %d\n", default_expires,
		       max_expires, max_expires);
		default_expires = max_expires;
	}

	/* Normalize default_q parameter */
	if (default_q != Q_UNSPECIFIED) {
		if (default_q > MAX_Q) {
			LM_DBG("default_q = %d, lowering to MAX_Q: %d\n", default_q, MAX_Q);
			default_q = MAX_Q;
		} else if (default_q < MIN_Q) {
			LM_DBG("default_q = %d, raising to MIN_Q: %d\n", default_q, MIN_Q);
			default_q = MIN_Q;
		}
	}

	reg_use_domain = !!ul.use_domain;

	if (gruu_secret.s)
		gruu_secret.len = strlen(gruu_secret.s);

	/* fix the flags */
	tcp_persistent_flag = get_flag_id_by_name(FLAG_TYPE_MSG,
	                                          tcp_persistent_flag_s, 0);
	tcp_persistent_flag = (tcp_persistent_flag >= 0) ?
	                       (1 << tcp_persistent_flag) : 0;

	return 0;
}
