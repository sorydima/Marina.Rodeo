/*
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C)  2001-2003 FhG FOKUS
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C)  2004,2005 Free Software Foundation, Inc.
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C)  2005 iptelorg GmbH
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C)  2006 enum.at
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C)  2021 - Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * In addition, as a special exception, the Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
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

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509v3.h>

#include "../../ut.h"
#include "../tls_mgm/tls_helper.h"

static inline int get_cert(X509** cert, SSL *ssl, int my)
{	
	*cert = my ? SSL_get_certificate(ssl) : SSL_get_peer_certificate(ssl);
	if (!*cert) {
		LM_ERR("failed to get certificate from SSL structure\n");
		return -1;
	}

	return 0;
}

int openssl_tls_var_version(void *ssl, str *res)
{
	str version;
	static char buf[1024];

	version.s = (char*)SSL_get_version(ssl);
	version.len = version.s ? strlen(version.s) : 0;
	if (version.len >= 1024) {
		LM_ERR("version string too long\n");
		return -1;
	}
	memcpy(buf, version.s, version.len);

	res->s = buf;
	res->len = version.len;

	return 0;
}

int openssl_tls_var_desc(void *ssl, str *res)
{
	static char buf[128];

	buf[0] = '\0';
	SSL_CIPHER_description(SSL_get_current_cipher(ssl), buf, 128);
	res->s = buf;
	res->len = strlen(buf);

	return 0;
}

int openssl_tls_var_cipher(void *ssl, str *res)
{
	str cipher;
	static char buf[1024];

	cipher.s = (char*)SSL_CIPHER_get_name(SSL_get_current_cipher(ssl));
	cipher.len = cipher.s ? strlen(cipher.s) : 0;
	if (cipher.len >= 1024) {
		LM_ERR("cipher name too long\n");
		return -1;
	}
	memcpy(buf, cipher.s, cipher.len);
	res->s = buf;
	res->len = cipher.len;

	return 0;
}

int openssl_tls_var_bits(void *ssl, str *str_res, int *int_res)
{
	str bits;
	static char buf[1024];

	*int_res = SSL_CIPHER_get_bits(SSL_get_current_cipher(ssl), 0);
	bits.s = int2str(*int_res, &bits.len);
	if (bits.len >= 1024) {
		LM_ERR("bits string too long\n");
		return -1;
	}
	memcpy(buf, bits.s, bits.len);
	str_res->s = buf;
	str_res->len = bits.len;
	
	return 0;
}

int openssl_tls_var_cert_vers(int ind, void *ssl, str *res)
{
	static char buf[INT2STR_MAX_LEN];
	X509* cert;
	char* version;
	int my;

	if (ind & VAR_CERT_PEER) {
		my = 0;
	} else if (ind & VAR_CERT_LOCAL) {
		my = 1;
	} else {
		LM_CRIT("bug in call to get_tls_var_cert_version\n");
		return -1;
	}

	if (get_cert(&cert, ssl, my) < 0) return -1;
	version = int2str(X509_get_version(cert), &res->len);
	memcpy(buf, version, res->len);
	res->s = buf;

	if (!my) X509_free(cert);
	return 0;
}

int openssl_tls_var_sn(int ind, void *ssl, str *str_res, int *int_res)
{
	static char buf[INT2STR_MAX_LEN];
	X509* cert;
	int my, serial;
	char* sn;

	if (ind & VAR_CERT_PEER) {
		my = 0;
	} else if (ind & VAR_CERT_LOCAL) {
		my = 1;
	} else {
		LM_CRIT("could not determine certificate\n");
		return -1;
	}

	if (get_cert(&cert, ssl, my) < 0)
		return -1;

	serial = ASN1_INTEGER_get(X509_get_serialNumber(cert));
	sn = int2str( serial, &str_res->len);
	memcpy(buf, sn, str_res->len);
	str_res->s = buf;
	*int_res = serial;

	if (!my) X509_free(cert);
	return 0;
}

int openssl_tls_var_comp(int ind, void *ssl, str *res)
{
	static char buf[1024];
	X509* cert;
	X509_NAME* name;
	X509_NAME_ENTRY* e;
	ASN1_STRING* asn1;
	int nid = NID_commonName, index, my = 0, issuer = 0;
	char* elem;
	str text;
	UNUSED(elem);

	text.s = 0;

	LM_DBG("ind = %x", ind);
	if (ind & VAR_CERT_PEER) {
		my = 0;
		ind = ind ^ VAR_CERT_PEER;
	} else if (ind & VAR_CERT_LOCAL) {
		my = 1;
		ind = ind ^ VAR_CERT_LOCAL;
	} else {
		LM_CRIT("could not determine certificate\n");
		return -1;
	}

	if (ind & VAR_CERT_SUBJECT) {
		issuer = 0;
		ind = ind ^ VAR_CERT_SUBJECT;
	} else if (ind & VAR_CERT_ISSUER) {
		issuer = 1;
		ind = ind ^ VAR_CERT_ISSUER;
	} else {
		LM_CRIT("could not determine subject or issuer\n");
		return -1;
	}

	switch(ind) {
		case VAR_COMP_CN: nid = NID_commonName;             break;
		case VAR_COMP_O:  nid = NID_organizationName;       break;
		case VAR_COMP_OU: nid = NID_organizationalUnitName; break;
		case VAR_COMP_C:  nid = NID_countryName;            break;
		case VAR_COMP_ST: nid = NID_stateOrProvinceName;    break;
		case VAR_COMP_L:  nid = NID_localityName;           break;
		case VAR_COMP_SUBJECT_SERIAL: nid = NID_serialNumber;break;
		default:      nid = NID_undef;
	}

	if (get_cert(&cert, ssl, my) < 0) return -1;

	name = issuer ? X509_get_issuer_name(cert) : X509_get_subject_name(cert);
	if (!name) {
		LM_ERR("cannot extract subject or issuer name from peer"
				" certificate\n");
		goto err;
	}

	if (nid == NID_undef) { /* dump the whole cert info into buf */
		X509_NAME_oneline(name, buf, sizeof(buf));
		res->s = buf;
		res->len = strlen(buf);
	} else {
		index = X509_NAME_get_index_by_NID(name, nid, -1);
		if (index == -1) {
			switch(ind) {
			case VAR_COMP_CN: elem = "CommonName";              break;
			case VAR_COMP_O:  elem = "OrganizationName";        break;
			case VAR_COMP_OU: elem = "OrganizationalUnitUname"; break;
			case VAR_COMP_C:  elem = "CountryName";             break;
			case VAR_COMP_ST: elem = "StateOrProvinceName";     break;
			case VAR_COMP_L:  elem = "LocalityName";            break;
			case VAR_COMP_SUBJECT_SERIAL:  elem = "SubjectSerialNumber";break;
			default:      elem = "Unknown";                 break;
			}
			LM_DBG("element %s not found in "
				"certificate subject/issuer\n", elem);
			goto err;
		}

		e = X509_NAME_get_entry(name, index);
		asn1 = X509_NAME_ENTRY_get_data(e);
		text.len = ASN1_STRING_to_UTF8((unsigned char**)(void*)&text.s, asn1);
		if (text.len < 0 || text.len >= 1024) {
			LM_ERR("failed to convert ASN1 string\n");
			goto err;
		}
		memcpy(buf, text.s, text.len);
		res->s = buf;
		res->len = text.len;

		OPENSSL_free(text.s);
	}
	if (!my) X509_free(cert);

	return 0;
 err:
	if (text.s) OPENSSL_free(text.s);
	if (!my) X509_free(cert);
	return -1;
}

int openssl_tls_var_alt(int ind, void *ssl, str *res)
{
	static char buf[1024];
	int type = GEN_URI, my = 0, n, found = 0;
	STACK_OF(GENERAL_NAME)* names = 0;
	GENERAL_NAME* nm;
	X509* cert;
	str text;
	struct ip_addr ip;

	if (ind & VAR_CERT_PEER) {
		my = 0;
		ind = ind ^ VAR_CERT_PEER;
	} else if (ind & VAR_CERT_LOCAL) {
		my = 1;
		ind = ind ^ VAR_CERT_LOCAL;
	} else {
		LM_CRIT("could not determine certificate\n");
		return -1;
	}

	switch(ind) {
		case VAR_COMP_E:    type = GEN_EMAIL; break;
		case VAR_COMP_HOST: type = GEN_DNS;   break;
		case VAR_COMP_URI:  type = GEN_URI;   break;
		case VAR_COMP_IP:   type = GEN_IPADD; break;
		default:
			LM_CRIT("ind=%d\n", ind);
			return -1;
	}

	if (get_cert(&cert, ssl, my) < 0) return -1;

	names = X509_get_ext_d2i(cert, NID_subject_alt_name, NULL, NULL);
	if (!names) {
		LM_ERR("cannot get certificate alternative subject\n");
		goto err;

	}

	for (n = 0; n < sk_GENERAL_NAME_num(names); n++) {
		nm = sk_GENERAL_NAME_value(names, n);
		if (nm->type != type) continue;
		switch(type) {
		case GEN_EMAIL:
		case GEN_DNS:
		case GEN_URI:
			text.s = (char*)nm->d.ia5->data;
			text.len = nm->d.ia5->length;
			if (text.len >= 1024) {
				LM_ERR("alternative subject text too long\n");
				goto err;
			}
			memcpy(buf, text.s, text.len);
			res->s = buf;
			res->len = text.len;
			found = 1;
			break;

		case GEN_IPADD:
			ip.len = nm->d.iPAddress->length;
			ip.af = (ip.len == 16) ? AF_INET6 : AF_INET;
			memcpy(ip.u.addr, nm->d.iPAddress->data, ip.len);
			text.s = ip_addr2a(&ip);
			text.len = strlen(text.s);
			memcpy(buf, text.s, text.len);
			res->s = buf;
			res->len = text.len;
			found = 1;
			break;
		}
		break;
	}
	if (!found) goto err;

	if (names) sk_GENERAL_NAME_pop_free(names, GENERAL_NAME_free);
	if (!my) X509_free(cert);
	return 0;
 err:
	if (names) sk_GENERAL_NAME_pop_free(names, GENERAL_NAME_free);
	if (!my) X509_free(cert);
	return -1;
}

int openssl_tls_var_check_cert(int ind, void *ssl, str *str_res, int *int_res)
{
	static str succ = str_init("1");
	static str fail = str_init("0");
	int err;
	X509* cert = 0;

	switch (ind) {
	case VAR_CERT_VERIFIED:   err = X509_V_OK;                              break;
	case VAR_CERT_REVOKED:    err = X509_V_ERR_CERT_REVOKED;                break;
	case VAR_CERT_EXPIRED:    err = X509_V_ERR_CERT_HAS_EXPIRED;            break;
	case VAR_CERT_SELFSIGNED: err = X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT; break;
	default:
		LM_CRIT("unexpected parameter value \"%d\"\n", ind);
		return -1;
	}

	if ((cert = SSL_get_peer_certificate(ssl)) && SSL_get_verify_result(ssl) == err) {
		str_res->s = succ.s;
		str_res->len = succ.len;
		*int_res   = 1;
	} else {
		str_res->s = fail.s;
		str_res->len = fail.len;
		*int_res   = 0;
	}

	if (cert) X509_free(cert);
	return 0;
}

int openssl_tls_var_validity(int ind, void *ssl, str *res)
{
	static char buf[1024];
	X509* cert;
	BUF_MEM* p;
	BIO* mem = 0;
	ASN1_TIME* date;
	int my = 0;

	if (get_cert(&cert, ssl, my) < 0) return -1;

	switch (ind) {
	case VAR_CERT_NOTBEFORE: date = X509_get_notBefore(cert); break;
	case VAR_CERT_NOTAFTER:  date = X509_get_notAfter(cert);  break;
	default:
		LM_CRIT("unexpected parameter value \"%d\"\n", ind);
		goto err;
	}

	mem = BIO_new(BIO_s_mem());
	if (!mem) {
		LM_ERR("failed to create memory BIO\n");
		goto err;
	}

	if (!ASN1_TIME_print(mem, date)) {
		LM_ERR("failed to print certificate date/time\n");
		goto err;
	}

	BIO_get_mem_ptr(mem, &p);
	if (p->length >= 1024) {
		LM_ERR("Date/time too long\n");
		goto err;
	}
	memcpy(buf, p->data, p->length);
	res->s = buf;
	res->len = p->length;

	BIO_free(mem);
	if (!my) X509_free(cert);

	return 0;
err:
	if (mem) BIO_free(mem);
	if (!my) X509_free(cert);
	return -1;
}
