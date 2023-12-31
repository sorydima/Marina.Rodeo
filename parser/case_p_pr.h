/*
 * P-Preferred-Identity Header Field Name Parsing Macros
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Juha Heinanen
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

#ifndef CASE_P_PR_H
#define CASE_P_PR_H


#define TITY_CASE                     \
	if (LOWER_DWORD(val) == _tity_) { \
		hdr->type = HDR_PPI_T;        \
		hdr->name.len = 20;           \
		p += 4;                       \
		goto dc_cont;                 \
	}                                 \


#define IDEN_CASE                     \
	if (LOWER_DWORD(val) == _iden_) { \
		p += 4;                       \
		val = READ(p);                \
		TITY_CASE;                    \
		goto other;                   \
	}


#define RED__CASE                     \
	if (LOWER_DWORD(val) == _red__) { \
		p += 4;                       \
		val = READ(p);                \
		IDEN_CASE;                    \
		goto other;                   \
	}


#define EFER_CASE                      \
	if (LOWER_DWORD(val) == _efer_) {  \
		p += 4;                        \
		val = READ(p);                 \
		RED__CASE;                     \
		goto other;                    \
	}


#define p_pr_CASE     \
	p += 4;           \
	if (!HAVE(16))    \
		goto other;   \
	val = READ(p);    \
	EFER_CASE;        \
	goto other;


#endif /* CASE_P_PR_H */
