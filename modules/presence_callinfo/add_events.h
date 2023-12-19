/*
 * presence_callinfo module - add_event header file
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2010 Ovidiu Sas
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2013 Marina.Rodeo Solutions
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
 * History:
 * --------
 *  2010-03-11  initial version (osas)
 *  2010-07-13  added support for SCA Broadsoft with dialog module (bogdan)
 */

#ifndef _CALLINFO_ADD_EV_H_
#define _CALLINFO_ADD_EV_H_

#include "../../parser/msg_parser.h"

#define CI_hdr_name_s       "Call-Info: "
#define CI_hdr_name_len     (sizeof(CI_hdr_name_s)-1)
#define CI_hdr_AI_param_s   "appearance-index"
#define CI_hdr_AI_param_len (sizeof(CI_hdr_AI_param_s)-1)
#define CI_hdr_AS_param_s   "appearance-state"
#define CI_hdr_AS_param_len (sizeof(CI_hdr_AS_param_s)-1)

#include "sca_hash.h"

int callinfo_add_events();

unsigned int get_appearance_index(struct sip_msg *msg);

int do_callinfo_publish(struct sca_line *sca);

int terminate_line_sieze(struct sca_line *sca);

#endif
