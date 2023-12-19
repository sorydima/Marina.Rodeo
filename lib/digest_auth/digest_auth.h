/*
 * digest_auth library
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2011 VoIP Embedded Inc.
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2013 Marina.Rodeo Solutions
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
 *
 * History:
 * --------
 *  2011-05-13  initial version (Ovidiu Sas)
 */

#ifndef _DIGEST_AUTH_H_
#define _DIGEST_AUTH_H_

#include "dauth_calc_md5.h"
#include "dauth_calc_sha256.h"
#include "dauth_calc_sha512t256.h"

#define WWW_AUTH_CODE       401
#define WWW_AUTH_HDR        "WWW-Authenticate"
#define PROXY_AUTH_CODE     407
#define PROXY_AUTH_HDR      "Proxy-Authenticate"

/* First/Last supported algorithm */
#define FIRST_ALG_SPTD (ALG_UNSPEC)
#define LAST_ALG_SPTD  (ALG_SHA512_256SESS)

typedef union {
	HASH_MD5 MD5;
	HASH_SHA256 SHA256;
	HASH_SHA512t256 SHA512t256;
} HASH;

typedef union {
	HASHHEX_MD5 MD5;
	HASHHEX_SHA256 SHA256;
	HASHHEX_SHA512t256 SHA512t256;
	char _start[0];
} HASHHEX;

struct digest_auth_calc;
struct authenticate_body;
struct match_auth_hf_desc;

struct digest_auth_response {
	HASH RespHash;
	const struct digest_auth_calc *digest_calc;
};

struct digest_auth_credential {
        str realm;
        str user;
        str passwd;
};

struct dauth_algorithm_match {
	int algmask;
};

#define DAUTH_ALGMATCH_ALL      (const struct dauth_algorithm_match){.algmask = ~0}
#define DAUTH_ALGMATCH_MSK(_am) (const struct dauth_algorithm_match){.algmask = (_am)}

#define DAUTH_AHFM_ANYSUP (&MATCH_AUTH_HF(dauth_algorithm_check, \
    &DAUTH_ALGMATCH_ALL))
#define DAUTH_AHFM_MSKSUP(_am) (&MATCH_AUTH_HF(dauth_algorithm_check, \
    &DAUTH_ALGMATCH_MSK(_am)))

int digest_algorithm_available(alg_t);
int dauth_algorithm_check(const struct authenticate_body *,
    const struct match_auth_hf_desc *);
int dauth_fixup_algorithms(void** param);

#endif
