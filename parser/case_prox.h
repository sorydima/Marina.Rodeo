/*
 * Proxy-Require, Proxy-Authorization Header Field Name Parsing Macros
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
 *
 * History:
 * --------
 * 2003-02-28 scratchpad compatibility abandoned (jiri)
 * 2003-01-27 next baby-step to removing ZT - PRESERVE_ZT (jiri)
 */


#ifndef CASE_PROX_H
#define CASE_PROX_H


#define ION_CASE                           \
	switch(LOWER_DWORD(val)) {             \
		case _ion1_:                       \
			hdr->type = HDR_PROXYAUTH_T;   \
			hdr->name.len = 19;            \
			return (p + 4);                \
		case _ion2_:                       \
			hdr->type = HDR_PROXYAUTH_T;   \
			hdr->name.len = 19;            \
			p += 4;                        \
		goto dc_cont;                      \
	}


#define IZAT_CASE                  \
	switch(LOWER_DWORD(val)) {     \
		case _izat_:               \
				p += 4;            \
				if (!HAVE(4))      \
					goto other;    \
				val = READ(p);     \
				ION_CASE;          \
				goto other;        \
	}

#define TE_CASE                                                  \
	if ( LOWER_BYTE(*p) == 't'  && LOWER_BYTE(*(p+1)) == 'e' ) { \
		hdr->type = HDR_PROXY_AUTHENTICATE_T;                    \
		hdr->name.len = 18;                                      \
		p += 2;                                                  \
		goto dc_cont;                                            \
	}

#define TICA_CASE                  \
	switch(LOWER_DWORD(val)) {     \
		case _tica_:               \
				p += 4;            \
				if (!HAVE(4))      \
					goto other;    \
				val = READ(p);     \
				TE_CASE;           \
				goto other;        \
	}

#define TH2_CASE               \
	switch(LOWER_DWORD(val)) { \
		case _thor_:           \
			p += 4;            \
			if (!HAVE(4))      \
				goto other;    \
			val = READ(p);     \
			IZAT_CASE;         \
			goto other;        \
		case _then_:           \
			p += 4;            \
			if (!HAVE(4))      \
				goto other;    \
			val = READ(p);     \
			TICA_CASE;         \
			goto other;        \
	}

#define QUIR_CASE                                   \
	switch(LOWER_DWORD(val)) {                      \
		case _quir_:                                \
			p += 4;                                 \
			if (!HAVE(1))                           \
				goto other;                         \
			switch(LOWER_BYTE(*p)) {                \
				case 'e':                           \
					hdr->type = HDR_PROXYREQUIRE_T; \
					hdr->name.len = 13;             \
					p++;                            \
					goto dc_cont;                   \
			}                                       \
			goto other;                             \
	}


#define PROX2_CASE                 \
	switch(LOWER_DWORD(val)) {     \
		case _y_au_:               \
				p += 4;            \
				if (!HAVE(4))      \
					goto other;    \
				val = READ(p);     \
				TH2_CASE;          \
				goto other;        \
		case _y_re_:               \
				p += 4;            \
				if (!HAVE(4))      \
					goto other;    \
				val = READ(p);     \
				QUIR_CASE;         \
				goto other;        \
	}


#define prox_CASE         \
		p += 4;           \
		if (!HAVE(4))     \
			goto other;   \
		val = READ(p);    \
		PROX2_CASE;       \
		goto other;


#endif /* CASE_PROX_H */
