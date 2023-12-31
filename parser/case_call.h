/*
 * Call-ID Header Name Parsing Macros
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
 * ----------
 * 2003-02-28 scratchpad compatibility abandoned (jiri)
 * 2003-01-27 next baby-step to removing ZT - PRESERVE_ZT (jiri)
 */


#ifndef CASE_CALL_H
#define CASE_CALL_H


#define ID_INF_CASE                      \
	switch(LOWER_DWORD(val)) {           \
		case __id1_:                     \
			hdr->type = HDR_CALLID_T;    \
			hdr->name.len = 7;           \
			return (p + 4);              \
		                                 \
		case __id2_:                     \
			hdr->type = HDR_CALLID_T;    \
			hdr->name.len = 7;           \
			p += 4;                      \
			goto dc_end;                 \
		                                 \
		case __inf_:                     \
			p += 4;                      \
			if ( HAVE(1) && LOWER_BYTE(*p) == 'o') {\
				hdr->type = HDR_CALL_INFO_T; \
				hdr->name.len = 9;       \
				p += 1;                  \
				goto dc_cont;            \
			}                            \
			goto other;                  \
		}


#define call_CASE      \
	p += 4;            \
	if (!HAVE(4))      \
		goto other;    \
	val = READ(p);     \
	ID_INF_CASE;       \
	goto other;


#endif /* CASE_CALL_H */
