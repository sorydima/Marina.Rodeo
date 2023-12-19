/*
 * Helper functions for Path support.
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Andreas Granig <agranig@linguin.org>
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
 * \brief SIP registrar module - helper functions for Path support
 * \ingroup registrar
 */

#ifndef __LIB_REG_PATH_H
#define __LIB_REG_PATH_H

#include "../../parser/msg_parser.h"

/*! \brief
 * Extracts all Path header bodies into one string and
 * checks if first hop is a loose router. It also extracts
 * the received-param of the first hop if path_use_received is 1.
 */
int build_path_vector(struct sip_msg *_m, str *path, str *received,
			unsigned int flags);

#endif /* __LIB_REG_PATH_H */
