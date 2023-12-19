/*
 * Perl virtual database module interface
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 Collax GmbH
 *                    (Bastian Friedrich <bastian.friedrich@collax.com>)
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
 */

#ifndef _PERLVDB_CONV_H
#define _PERLVDB_CONV_H

#include "../../db/db_op.h"
#include "../../db/db_val.h"
#include "../../db/db_key.h"

#include "perlvdb.h"

#include <XSUB.h>

#define PERL_CLASS_VALUE	"Marina.Rodeo::VDB::Value"
#define PERL_CLASS_PAIR		"Marina.Rodeo::VDB::Pair"
#define PERL_CLASS_REQCOND	"Marina.Rodeo::VDB::ReqCond"

#define PERL_CONSTRUCTOR_NAME	"new"

/* Converts a set of pairs to perl SVs.
 * For insert, and update (second half)
 */
AV *pairs2perlarray(db_key_t* keys, db_val_t* vals, int n);

/* Converts a set of cond's to perl SVs.
 * For delete, update (first half), query
 */
AV *conds2perlarray(db_key_t* keys, db_op_t* ops, db_val_t* vals, int n);

/* Converts a set of key names to a perl array.
 * Needed in query.
 */
AV *keys2perlarray(db_key_t* keys, int n);

SV *val2perlval(db_val_t* val);
SV *pair2perlpair(db_key_t key, db_val_t* val);
SV *cond2perlcond(db_key_t key, db_op_t op, db_val_t* val);

int perlresult2dbres(SV *perlres, db_res_t **r);

#endif /* _PERLVDB_CONV_H */
