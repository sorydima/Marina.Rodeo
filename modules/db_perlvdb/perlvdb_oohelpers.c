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

#include "perlvdb_oohelpers.h"

#include "../../mem/mem.h"

SV *perlvdb_perlmethod(SV *class,
		       const char* method,
		       SV *param1,
		       SV *param2,
		       SV *param3,
		       SV *param4) {

	I32 res;
	SV *retval = NULL;

	dSP;

	               ENTER;
		                      SAVETMPS;

	PUSHMARK(SP);

	/* passed stack:
	 * class, and optionally parameters
	 */
	XPUSHs(class);

	if (param1) {
		XPUSHs(param1);
	}

	if (param2) {
		XPUSHs(param2);
	}

	if (param3) {
		XPUSHs(param3);
	}

	if (param4) {
		XPUSHs(param4);
	}

	PUTBACK;

	res = call_method(method, G_SCALAR | G_EVAL);

	SPAGAIN;

	if (res == 0) {
		/* should never happened - G_EVAL and G_SCALAR specified */
		retval = &PL_sv_undef;
	} else if (res == 1) {
		/* This is the only return from call_method with G_SCALAR | G_EVAL */
		retval = POPs;
	} else {
		/* More than one result in Scalar context??? */
		LM_CRIT("got more than one result from scalar method!\n");
		while (res--) { /* Try to clean stack. This
				   should never happen anyway.*/
			retval = POPs;
		}
	}

	SvREFCNT_inc(retval);

	PUTBACK;
	FREETMPS;
	LEAVE;

	return retval;
}

