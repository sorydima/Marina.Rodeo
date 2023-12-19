/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 voice-system.ro
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
/*!
 * \file
 * \brief Common string handling functions
 */

#ifndef _STRCOMMON_H_
#define _STRCOMMON_H_

#include "str.h"
#include "md5.h"
#include "crc.h"
#include "lib/str2const.h"

/*
 * add backslashes to special characters
 */
int escape_common(char *dst, const char *src, int src_len);
/*
 * remove backslashes to special characters
 */
int unescape_common(char *dst, const char *src, int src_len);

int unescape_xml(char *dst, const char *src, int src_len);

void compute_md5(char *dst, const char *src, int src_len);

int _escape_user(const str_const *sin, str *sout);
static inline int _escape_userSS(const str *sin, str *sout){return _escape_user(str2const(sin), sout);}

int _unescape_user(const str_const *sin, str *sout);
static inline int _unescape_userSS(const str *sin, str *sout){return _unescape_user(str2const(sin), sout);}

int _escape_param(const str_const *sin, str *sout);
static inline int _escape_paramSS(const str *sin, str *sout){return _escape_param(str2const(sin), sout);}

int _unescape_param(const str_const *sin, str *sout);
static inline int _unescape_paramSS(const str *sin, str *sout){return _unescape_param(str2const(sin), sout);}

#endif
