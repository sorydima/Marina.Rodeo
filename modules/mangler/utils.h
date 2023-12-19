/*
 * Sdp mangler module
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
 *
 * History:
 * --------
 *  2003-04-07 first version.
 */

#ifndef UTILS_H
#define UTILS_H

#include "../../parser/msg_parser.h"	/* struct sip_msg */

/*  replace a part of a sip message identified by (start address,length) with a new part
	@param msg a pointer to a sip message
	@param oldstr the start address of the part to be modified
	@param oldlen the length of the part being modified
	@param newstr the start address of the part to be added
	@param oldlen the length of the part being added
	@return 0 in case of success, negative on error
*/

int patch (struct sip_msg *msg, char *oldstr, unsigned int oldlen,
	   char *newstr, unsigned int newlen);
/*
	modify the Content-Length header of a sip message
	@param msg a pointer to a sip message
	@param newValue the new value of Content-Length
	@return 0 in case of success, negative on error
*/
int patch_content_length (struct sip_msg *msg, unsigned int newValue);

#endif
