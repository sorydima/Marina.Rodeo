/*
 * mid-registrar contact storing
 *
 * This module is intended to be used as a middle layer SIP component in
 * environments where a large proportion of SIP UAs (e.g. mobile devices)
 * register at high enough frequencies that they actually degrade the
 * performance of their registrars.
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2016-2020 Marina.Rodeo Solutions
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

#ifndef __MID_REG_SAVE_
#define __MID_REG_SAVE_

#include "../../parser/msg_parser.h"
#include "../../lib/reg/save_flags.h"

#define MAX_CONTACT_BUFFER 1024

#define E_INFO "P-Registrar-Error: "
#define E_INFO_LEN (sizeof(E_INFO) - 1)

#define CONTACT_BEGIN "Contact: "
#define CONTACT_BEGIN_LEN (sizeof(CONTACT_BEGIN) - 1)

#define Q_PARAM ";q="
#define Q_PARAM_LEN (sizeof(Q_PARAM) - 1)

#define EXPIRES_PARAM ";expires="
#define EXPIRES_PARAM_LEN (sizeof(EXPIRES_PARAM) - 1)

#define SIP_PROTO "sip:"
#define SIP_PROTO_SIZE (sizeof(SIP_PROTO) - 1)

#define SIP_INSTANCE ";+sip.instance="
#define SIP_INSTANCE_SIZE (sizeof(SIP_INSTANCE) - 1)

#define CONTACT_SEP ", "
#define CONTACT_SEP_LEN (sizeof(CONTACT_SEP) - 1)

int mid_reg_save(struct sip_msg *msg, udomain_t *ud, struct save_flags *flags,
                          str *to_uri, int *expires, str *owtag);

#endif /* __MID_REG_SAVE_ */
