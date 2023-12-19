/*
 * Digest Authentication Module
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
 */

#ifndef AUTH_API_H
#define AUTH_API_H


#include "../../parser/digest/digest.h"
#include "../../parser/digest/digest_parser.h"
#include "../../parser/msg_parser.h"
#include "../../parser/hf.h"
#include "../../str.h"
#include "../../usr_avp.h"
#include "../../lib/digest_auth/digest_auth.h"
#include "../../lib/digest_auth/dauth_nonce.h"

typedef enum auth_result {
	AUTH_ERROR = -5,    /* Error occurred, a reply has not been sent out */
	NO_CREDENTIALS,     /* Credentials missing */
	STALE_NONCE,        /* Stale nonce */
	INVALID_PASSWORD,   /* Invalid password */
	USER_UNKNOWN,       /* User non existant */
	ERROR,              /* Error occurred, a reply has been sent out -> */
	                    /* return 0 to the Marina.Rodeo core */
	AUTHORIZED,         /* Authorized. If returned by pre_auth, */
	                    /* no digest authorization necessary */
	DO_AUTHORIZATION,   /* Can only be returned by pre_auth. */
	                    /* Means to continue doing authorization */
} auth_result_t;


/*
 * Purpose of this function is to find credentials with given realm,
 * do sanity check, validate credential correctness and determine if
 * we should really authenticate (there must be no authentication for
 * ACK and CANCEL
 */
typedef auth_result_t (*pre_auth_t)(struct sip_msg* _m, str* _realm,
		hdr_types_t _hftype, struct hdr_field** _h);
auth_result_t pre_auth(struct sip_msg* _m, str* _realm,
		hdr_types_t _hftype, struct hdr_field** _h);


/*
 * Purpose of this function is to do post authentication steps like
 * marking authorized credentials and so on.
 */
typedef auth_result_t (*post_auth_t)(struct sip_msg* _m, struct hdr_field* _h);
auth_result_t post_auth(struct sip_msg* _m, struct hdr_field* _h);

/*
 * Calculate the response and compare with the given response string
 * Authorization is successful if this two strings are same
 */
typedef int (*check_response_t)(const dig_cred_t* _cred, const str* _method,
    const str* _msg_body, const HASHHEX* _ha1);
int check_response(const dig_cred_t* _cred, const str* _method,
    const str* _msg_body, const HASHHEX* _ha1);

struct calc_HA1_arg {
	int use_hashed;
	alg_t alg;
	union {
		const struct digest_auth_credential *open;
		const str *ha1;
	} creds;
	const str* nonce;
	const str* cnonce;
};

typedef int (*calc_HA1_t)(const struct calc_HA1_arg *params, HASHHEX *_sess_key)
    __attribute__ ((warn_unused_result));

/*
 * Build {WWW,Proxy}-Authenticate header field
 */
typedef char *(*build_auth_hf_t)(struct nonce_context *ncp, struct nonce_params *calc_np,
	int _stale, const str_const *_realm, int* _len,
    const str_const *alg_val, const str_const* _hf_name,  const str_const *opaque);

/*
 * Build Authentication-Info header field
 */
typedef str *(*build_auth_info_hf_t)(str *msg_body, str *method, dig_cred_t *cred,
	struct digest_auth_credential *auth_data);

/*
 * Strip the beginning of realm
 */
void strip_realm(str *_realm);


/*
 * Auth module API
 */
typedef struct auth_api {
	int rpid_avp;          /* Name of AVP containing Remote-Party-ID */
	int     rpid_avp_type; /* type of the RPID AVP */
	pre_auth_t  pre_auth;  /* The function to be called before auth */
	post_auth_t post_auth; /* The function to be called after auth */
	calc_HA1_t  calc_HA1;  /* calculate H(A1) as per spec */
	check_response_t check_response; /* check auth response */
	build_auth_hf_t build_auth_hf;   /* build {WWW,Proxy}-Authenticate header field */
	build_auth_info_hf_t build_auth_info_hf; /* build Authentication-Info header */
} auth_api_t;


typedef int (*bind_auth_t)(auth_api_t* api);
int bind_auth(auth_api_t* api);


#endif /* AUTH_API_H */
