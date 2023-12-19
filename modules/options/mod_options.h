/*
 * Options Reply Module
 *
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

#ifndef OPT_RPL_H
#define OPT_RPL_H

#define ACPT_STR "Accept: "
#define ACPT_STR_LEN 8
#define ACPT_ENC_STR "Accept-Encoding: "
#define ACPT_ENC_STR_LEN 17
#define ACPT_LAN_STR "Accept-Language: "
#define ACPT_LAN_STR_LEN 17
#define SUPT_STR "Supported: "
#define SUPT_STR_LEN 11
#define HF_SEP_STR "\r\n"
#define HF_SEP_STR_LEN 2

/*
 * I think RFC3261 is not precise if a proxy should accept any
 * or no body (because it is not the endpoint of the media)
 */
#define ACPT_DEF "*/*"
#define ACPT_ENC_DEF ""
#define ACPT_LAN_DEF "en"
#define SUPT_DEF ""

#endif /* OPT_RPL_H */
