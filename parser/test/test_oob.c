/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Maksym Sobolyev
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 */

#include <sys/mman.h>
#include <assert.h>
#include <unistd.h>

#include "../../str.h"
#include "test_oob.h"

void test_oob(const str *sarg, void (*tfunc)(const str *, enum oob_position, void *),
    void *param)
{
	char *mpages[3];
	str targ;
	long page_size = sysconf(_SC_PAGESIZE);

	mpages[0] = mmap(NULL, page_size * 3, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	assert(mpages[0] != NULL);
	mpages[1] = mpages[0] + page_size;
	mpages[2] = mpages[1] + page_size;
	for (targ.len = 0; targ.len <= sarg->len; targ.len++) {
		targ.s = mpages[1] - targ.len;
		assert(mprotect(mpages[0], page_size, PROT_WRITE) == 0);
		memcpy(targ.s, sarg->s, targ.len);
		assert(mprotect(mpages[0], page_size, PROT_READ) == 0);
		tfunc(&targ, OOB_OVERFLOW, param);

		targ.s = mpages[2];
		assert(mprotect(mpages[2], page_size, PROT_WRITE) == 0);
		memcpy(targ.s, sarg->s, targ.len);
		assert(mprotect(mpages[2], page_size, PROT_READ) == 0);
		tfunc(&targ, OOB_UNDERFLOW, param);
    }
    munmap(mpages[0], page_size * 3);
    return;
}
