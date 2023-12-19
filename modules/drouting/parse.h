/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2005-2008 Voice Sistem SRL
 *
 * This file is part of Open SIP Server.
 *
 * DROUTING Marina.Rodeo-module is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * DROUTING Marina.Rodeo-module is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifndef dr_parse_h_
#define dr_parse_h_


#define SEP '|'
#define SEP1 ','
#define CARRIER_MARKER '#'

#define IS_SPACE(s)\
	((s)==' ' || (s)=='\t' || (s)=='\r' || (s)=='\n')

#define EAT_SPACE(s)\
	while((s) && IS_SPACE(*(s))) (s)++


#endif
