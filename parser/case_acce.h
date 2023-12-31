/*
 * Accept and Accept-Language Header Field Name Parsing Macros
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

#ifndef CASE_ACCE_H
#define CASE_ACCE_H


#define age_CASE                              \
	switch(LOWER_DWORD(val)) {                \
		case _age1_:                          \
			hdr->type = HDR_ACCEPTLANGUAGE_T; \
			hdr->name.len = 15;               \
			return (p + 4);                   \
		case _age2_:                          \
			hdr->type = HDR_ACCEPTLANGUAGE_T; \
			hdr->name.len = 15;               \
			p += 4;                           \
			goto dc_cont;                     \
		}


#define angu_CASE              \
	switch(LOWER_DWORD(val)) { \
		case _angu_:           \
			p += 4;            \
			val = READ(p);     \
			age_CASE;          \
			goto other;        \
	}


#define on_CASE                                  \
	if (LOWER_BYTE(*p) == 'o') {                 \
		p++;                                     \
		if (LOWER_BYTE(*p) == 'n') {             \
			hdr->type = HDR_ACCEPTDISPOSITION_T; \
			hdr->name.len = 18;                  \
			p++;                                 \
			goto dc_cont;                        \
		}                                        \
	}


#define siti_CASE              \
	switch(LOWER_DWORD(val)) { \
		case _siti_:           \
			p += 4;            \
			val = READ(p);     \
			on_CASE;           \
			goto other;        \
	}


#define ispo_CASE              \
	switch(LOWER_DWORD(val)) { \
		case _ispo_:           \
			p += 4;            \
			val = READ(p);     \
			siti_CASE;         \
			goto other;        \
	}


#define ptld_CASE              \
	switch(LOWER_DWORD(val)) { \
		case _pt_l_:           \
			p += 4;            \
			if (!HAVE(8))      \
				goto other;    \
			val = READ(p);     \
			angu_CASE;         \
			goto other;        \
		case _pt_d_:           \
			p += 4;            \
			if (!HAVE(10))     \
				goto other;    \
			val = READ(p);     \
			ispo_CASE;         \
			goto other;        \
	}


#define acce_CASE                           \
	p += 4;                                 \
	if (HAVE(4)) {                          \
		val = READ(p);                      \
		ptld_CASE;                          \
	}                                       \
	if (HAVE(2) && LOWER_BYTE(*p) == 'p') { \
		p++;                                \
		if (LOWER_BYTE(*p) == 't') {        \
			hdr->type = HDR_ACCEPT_T;       \
			hdr->name.len = 6;              \
			p++;                            \
			goto dc_cont;                   \
		}                                   \
	}                                       \
	goto other;


#endif /* CASE_ACCE_H */
