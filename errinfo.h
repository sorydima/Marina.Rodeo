/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Voice Sistem SRL
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

/*!
 * \file errinfo.h
 * \brief Error handling
 */


#ifndef _errinfo_h_
#define _errinfo_h_

#include "str.h"

/*! \name ErrorClasses  error clases */
#define OSER_EC_PARSER	1 /*!< parse error */
#define OSER_EC_PMEMORY	2 /*!< private memory error */
#define OSER_EC_SMEMORY	3 /*!< share memory error */
#define OSER_EC_ASSERT	4 /*!< assertion error */

#define OSER_EL_CRITIC	1
#define OSER_EL_HIGH	2
#define OSER_EL_MEDIUM	3 /*!< severity level normal - used by parsing errors */
#define OSER_EL_NORMAL	4
#define OSER_EL_LOW	5

typedef struct err_info_
{
	int eclass;		/*!< error class */
	int level;		/*!< severity level (lower is higher) */
	str info;		/*!< error details */
	int rcode;		/*!< recommended reply code */
	str rreason;	/*!< recommended reply reason phrase */
} err_info_t;

void init_err_info();
void set_err_info(int ec, int el, char *info);
void set_err_reply(int rc, char *rr);
err_info_t* get_err_info();

#endif
