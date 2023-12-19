/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Maksym Sobolyev
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

struct digest_auth_credential;
struct digest_auth_response;

struct digest_auth_calc {
	int (*HA1)(const struct digest_auth_credential *, HASHHEX *)
	    __attribute__ ((warn_unused_result));
	int (*HA1sess)(const str_const *, const str_const *, HASHHEX *)
	    __attribute__ ((warn_unused_result));
	int (*HA2)(const str_const *, const str_const *, const str_const *,
	    int, HASHHEX *) __attribute__ ((warn_unused_result));
	int (*response)(const HASHHEX *ha1, const HASHHEX *ha2,
	    const str_const *nonce, const str_const *qop_val, const str_const* nc,
	    const str_const* cnonce, struct digest_auth_response *response)
	    __attribute__ ((warn_unused_result));
        int (*response_hash_bcmp)(const struct digest_auth_response *,
	    const str_const *hex);
        char *(*response_hash_fill)(const struct digest_auth_response *,
            char *hex, int len);
	const str_const algorithm_val;
	int HASHLEN;
	int HASHHEXLEN;
};

const struct digest_auth_calc* get_digest_calc(alg_t algorithm);
