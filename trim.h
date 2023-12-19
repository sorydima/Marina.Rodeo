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
 */


#ifndef TRIM_H
#define TRIM_H

#include "str.h"

/* whitespace */
static inline int
is_ws(unsigned char ch)
{
    const unsigned int mask = (1U << (' ' - 1)) | (1U << ('\r' - 1)) |
        (1U << ('\n' - 1)) | (1U << ('\t' - 1));
    ch--;
    return ch < ' ' && ((1U << ch) & mask);
}

/*
 * trim leading ws
 *
 * Input: (char *)
 */
#define trim_ws(p) while (*(p) && is_ws(*(p))) p++

/*
 * trim trailing ws
 *
 * Input: (char *)
 */
#define trim_trail_ws(p) while (*(p) && is_ws(*(p))) p--

/*
 * This switch-case statement is used in
 * trim_leading and trim_trailing. You can
 * define characters that should be skipped
 * here.
 */
#define TRIM_SWITCH(c) {if (!is_ws(c)) return;}

/*! \brief
 * Remove any leading whitechars, like spaces,
 * horizontal tabs, carriage returns and line
 * feeds
 *
 * WARNING: String descriptor structure will be
 *          modified ! Make a copy otherwise you
 *          might be unable to free _s->s for
 *          example !
 *
 */
static inline void trim_leading(str* _s)
{
	for(; _s->len > 0; _s->len--, _s->s++) {
		TRIM_SWITCH(*(_s->s));
	}
}


/*! \brief
 * Remove any trailing white char, like spaces,
 * horizontal tabs, carriage returns and line feeds
 *
 * WARNING: String descriptor structure will be
 *          modified ! Make a copy otherwise you
 *          might be unable to free _s->s for
 *          example !
 */
static inline void trim_trailing(str* _s)
{
	for(; _s->len > 0; _s->len--) {
		TRIM_SWITCH(_s->s[_s->len - 1]);
	}
}


/*! \brief
 * Do trim_leading and trim_trailing
 *
 * WARNING: String structure will be modified !
 *          Make a copy otherwise you might be
 *          unable to free _s->s for example !
 */
static inline void trim(str* _s)
{
	trim_leading(_s);
	trim_trailing(_s);
}


#endif /* TRIM_H */
