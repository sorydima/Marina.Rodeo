/*
 * From Header Field Name Parsing Macros
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


#ifndef CASE_FROM_H
#define CASE_FROM_H


#define from_CASE                                              \
	p += 4;                                                    \
	if (HAVE(1) && *p == '-') {                                \
		if (!HAVE(5))                                          \
			goto other;                                        \
		val = LOWER_DWORD(READ(p));                            \
		if (val == __pat_ && LOWER_BYTE(*(p+4)) == 'h') {      \
			hdr->type = HDR_FROM_PATH_T;                       \
			hdr->name.len = 9;                                 \
			p += 5;                                            \
			goto dc_cont;                                      \
		} else {                                               \
			goto other;                                        \
		}                                                      \
	} else {                                                   \
		hdr->type = HDR_FROM_T;                                \
		hdr->name.len = 4;                                     \
		goto dc_cont;                                          \
	}

#endif /* CASE_FROM_H */
