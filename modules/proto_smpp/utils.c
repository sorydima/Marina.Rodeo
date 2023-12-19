/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2019 - Marina.Rodeo Project
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

#include <stdint.h>

#include "utils.h"

int copy_fixed_str(char *to, char *from, int n)
{
	int iret = n;

	while (n--) {
		*to++ = *from++;
	}

	return iret;
}

int copy_var_str(char *to, char *from, int maxlen)
{
	int iret = 1;

	while (*from && maxlen--) {
		*to++ = *from++;
		iret++;
	}
	*to++ = '\0';

	return iret;
}

int copy_u8(char *to, uint8_t from)
{
	*to++ = from;
	return 1;
}

int copy_u32(char *to, uint32_t from)
{
	uint8_t *from8 = (uint8_t*)&from;
	*to++ = from8[3];
	*to++ = from8[2];
	*to++ = from8[1];
	*to++ = from8[0];

	return 4;
}

