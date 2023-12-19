/**
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2016 Marina.Rodeo Foundation
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
 * History
 * -------
 *  2016-09-xx  initial version (rvlad-patrascu)
 */

#ifndef _SIP_I_H_
#define _SIP_I_H_

#define DEFAULT_PARAM_SUBF_SEP "|"

#define ISUP_MIME_S "application/ISUP;version=itu-t92+"
#define DEFAULT_COUNTRY_CODE "+1"
#define DEFAULT_PART_HEADERS "Content-Disposition:signal;handling=optional" CRLF
#define MAX_NUM_LEN 15  /* E.164 number - max 15 digits */

enum tr_isup_subtype {
	TR_ISUP_PARAM, TR_ISUP_PARAM_STR
};

struct isup_parse_fixup {
	int isup_params_idx;
	int subfield_idx;
};

#endif /* _SIP_I_H_ */
