/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (c) 2011 VoIP Embedded, Inc. <http://www.voipembedded.com/>
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
 * 2011-12-07 Initial revision (osas@voipembedded.com)
 */

#ifndef PARSE_MIN_EXPIRES_H
#define PARSE_MIN_EXPIRES_H 1

#include "msg_parser.h"
#include "parse_sst.h"

/**
 * Parses the "Min-Expires" header for the given msg.
 *
 * @param msg the msg to be parsed
 * @return 0 on success
 */
int parse_min_expires(struct sip_msg *msg);

#endif /* ! PARSE_MIN_EXPIRES_H */
