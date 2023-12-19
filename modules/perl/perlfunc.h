/*
 * Perl module for Marina.Rodeo
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Collax GmbH
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

#ifndef PERL_FUNC_H
#define PERL_FUNC_H

#include "../../parser/msg_parser.h"

/* fixup for perl_exec and perl_exec_simple */
int perl_fixup(void** param, int param_no);

/*
 * Run a perl function without a sip message parameter.
 */
int perl_exec_simple(struct sip_msg* _msg, str *_fnc_s, str *_param_s);

/*
 * Run function with a reference to the current SIP message.
 * An optional string may be passed to perl_exec_string.
 */
int perl_exec(struct sip_msg* _msg, str* _fnc_s, str* mystr);

#endif /* PERL_FUNC_H */
