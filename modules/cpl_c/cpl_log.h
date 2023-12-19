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
 *
 * History:
 * -------
 * 2003-09-22: created (bogdan)
 *
 */


#ifndef _CPL_LOG_H_
#define _CPL_LOG_H_

#include <stdarg.h>
#include "../../str.h"


#define MAX_LOG_NR    64

#define ERR     "Error: "
#define ERR_LEN (sizeof(ERR)-1)
#define WARN    "Warning: "
#define WARN_LEN (sizeof(WARN)-1)
#define NOTE     "Notice: "
#define NOTE_LEN (sizeof(NOTE)-1)

#define LF       "\n"
#define LF_LEN   (1)


void reset_logs();

void append_log( int nr, ...);

void compile_logs( str *log);

#endif

