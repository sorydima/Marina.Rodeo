/*
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
 *   2003-08-04  created by andrei
 *   2004-11-12  minor api extension, added *count (andrei)
 */

/*!
 * \file
 * \brief regexp and regexp substitutions implementations
 */

#ifndef _re_h
#define _re_h

#include "str.h"
#include "pvar.h"
#include "parser/msg_parser.h"
#include <sys/types.h> /* for regex */
#include <regex.h>

#define WITH_SEP	1
#define WITHOUT_SEP	0

enum replace_special { REPLACE_NMATCH, REPLACE_CHAR, REPLACE_URI,
	REPLACE_SPEC };

struct replace_with{
	int offset; /* offset in string */
	int size;   /* size of replace "anchor" in string */
	enum replace_special type;
	union{
		int nmatch;
		char c;
		pv_spec_t spec;
	}u;
};

struct subst_expr{
	regex_t* re;
	str replacement;
	int replace_all;
	int n_escapes; /* escapes number (replace[] size) */
	int max_pmatch ; /* highest () referenced */
	struct replace_with replace[1]; /* 0 does not work on all compilers */
};

struct replace_lst{
	int offset;
	int size;   /* at offset, delete size bytes and replace them with rpl */
	str rpl;
	struct replace_lst *next;
};



void subst_expr_free(struct subst_expr* se);
void replace_lst_free(struct replace_lst* l);
int parse_repl(struct replace_with * rw, char ** begin,
				char * end, int *max_token_nb, int flag);
struct subst_expr*  subst_parser(str* subst);
struct replace_lst* subst_run( struct subst_expr* se, const char* input,
		                       struct sip_msg* msg, int *count);
str* subst_str(const char* input, struct sip_msg* msg,
				struct subst_expr* se, int* count);



#endif

