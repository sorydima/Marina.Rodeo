/*
 * mangler module
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

#include "utils.h"

#include "../../parser/msg_parser.h"	/* struct sip_msg */
#include "../../mem/mem.h"
#include "../../data_lump.h"

#include <stdio.h>


int
patch (struct sip_msg *msg, char *oldstr, unsigned int oldlen, char *newstr,
       unsigned int newlen)
{
	int off;
	struct lump *anchor;

	if (oldstr == NULL)
		return -1;

	if (newstr == NULL)
		return -2;
	off = oldstr - msg->buf;
	if (off < 0)
		return -3;
	if ((anchor = del_lump (msg, off, oldlen, 0)) == 0)
	{
		LM_ERR("lumping with del_lump\n");
		return -4;
	}
	if ((insert_new_lump_after (anchor, newstr, newlen, 0)) == 0)
	{
		LM_ERR("lumping with insert_new_lump_after\n");
		return -5;
	}

	return 0;
}


/* TESTED */
int
patch_content_length (struct sip_msg *msg, unsigned int newValue)
{

	struct hdr_field *contentLength;
	char *s, pos[11];
	int len;

	contentLength = msg->content_length;
	if (contentLength == NULL)	/* maybe not yet parsed */
	{
		if (parse_headers (msg, HDR_CONTENTLENGTH_F, 0) == -1)
		{
			LM_ERR("parse headers on Content-Length failed\n");
			return -1;
		}
		contentLength = msg->content_length;
		if (contentLength == NULL)
		{
			LM_ERR("failed to parse headers on Content-Length "
					"succeeded but msg->content_length is still NULL\n");
			return -2;
		}
	}
	/* perhaps dangerous because buffer is static ? */
	//pos = int2str(newValue,&len);
	len = snprintf ((char *) pos, 10, "%u", newValue);
	s = pkg_malloc (len);
	if (s == NULL)
	{
		LM_ERR("unable to allocate %d bytes in pkg mem\n", len);
		return -3;
	}
	memcpy (s, pos, len);
	/* perhaps we made it and no one called int2str,might use sprintf */
	if (patch
	    (msg, contentLength->body.s, contentLength->body.len, s, len) < 0)
	{
		pkg_free (s);
		LM_ERR("lumping failed\n");
		return -4;
	}

	LM_DBG ("succeeded in altering Content-Length to new value %u\n",newValue);

	return 0;

}
