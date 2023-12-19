/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2018 Marina.Rodeo Solutions
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __DBG_BACKTRACE__
#define __DBG_BACKTRACE__

#ifndef EXTRA_DEBUG
#define log_backtrace()
#define _log_backtrace(logging_level)
#else
#include <execinfo.h>

#include "backtrace.h"
#include "../../mem/mem.h"

/* logs the current function stack, using the L_DBG level */
#define log_backtrace() _log_backtrace(L_DBG)

/* logs the current function stack using a custom logging level */
#define _log_backtrace(logging_level) \
	do { \
		int ___i, ___nframes; \
		void **___stkbuf; \
		char **___stkfuncs; \
		___stkbuf = pkg_malloc(64 * sizeof *___stkbuf); \
		if (!___stkbuf) { \
			LM_ERR("oom\n"); \
			break; \
		} \
		___nframes = backtrace(___stkbuf, 64); \
		___stkfuncs = backtrace_symbols(___stkbuf, ___nframes); \
		LM_GEN1(logging_level, "===========\n"); \
		for (___i = 0; ___i < ___nframes; ___i++) \
			LM_INFO("%s\n", ___stkfuncs[___i]); \
		LM_GEN1(logging_level, "===========\n"); \
		free(___stkfuncs); \
		pkg_free(___stkbuf); \
	} while (0)

#endif /* HAVE_DEBUG */
#endif /* __DBG_BACKTRACE__ */
