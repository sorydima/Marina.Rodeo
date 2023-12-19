/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2014 Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Marina.Rodeo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * history:
 * ---------
 *  2014-08-23  created (bogdan)
 */

#include <sys/time.h>
#include <sys/resource.h>

#include "io_wait.h"
#include "globals.h"

/* one reactor per process variable */
io_wait_h _worker_io;
/* max number of fds per reactor */
unsigned int reactor_size = 0;

#define FD_MEM_PERCENT  10

int init_reactor_size(void)
{
	struct rlimit lim;
	int n, pc;
	char *mem_type;
	unsigned long mem_size;

#if defined(PKG_MALLOC)
	mem_type = "pkg";
	mem_size = pkg_mem_size;
#else
	mem_type = "system";
	mem_size = 2*1024*1024*1024UL;  // assume 2Gb per process to avoid reaching limits below
#endif

	n = sizeof(struct fd_map) + sizeof(struct pollfd);

	if (open_files_limit > 0) {
		/* the fd limit was explicitly set, so just follow but only warn
		 * if too much memory is to consumed by reactor */
		pc = 100 * n * open_files_limit / mem_size;
		if (pc >= 80) {
			LM_ERR("required memory for a %d files reactor is over 80%% of "
				   "the configured %s mem (%luMb)\n",
				   open_files_limit, mem_type, mem_size/1024/1024);
			LM_ERR("Please consider increasing the %s memory or reduce the "
				   "limit of open files...Exiting\n", mem_type);
			return -1;
		} else if (pc >= 50) {
			LM_WARN("required memory for a %d files reactor is over 50%% of "
					"the configured %s mem (%luMb)\n",
					open_files_limit, mem_type, mem_size/1024/1024);
			LM_WARN("%s memory may not be enough at runtime (consider "
					"increasing it), still continuing\n", mem_type);
		}
		/* seems to have enough mem -> size the reactor based on open files */
		reactor_size = open_files_limit;
	} else {
		/* auto detect the limit of open files */
		if (getrlimit(RLIMIT_NOFILE, &lim)<0){
			LM_ERR("cannot get the maximum number of file descriptors: %s\n",
				   strerror(errno));
			return -1;
		}

		/* calculate the size to fit into 10% of mem */
		reactor_size = mem_size / n * FD_MEM_PERCENT / 100;

		if (reactor_size < lim.rlim_cur) {
			LM_WARN("shrinking reactor size from %lu (autodetected via rlimit) "
					"to %d (limited by memory of %d%% from %luMb)\n",
					(unsigned long)lim.rlim_cur, reactor_size, FD_MEM_PERCENT, mem_size/1024/1024);
			LM_WARN("use 'open_files_limit' to enforce other limit or "
					"increase %s memory\n", mem_type);
		} else {
			/* enouhg memory, use as limit the fd limit */
			reactor_size = lim.rlim_cur;
		}
	}

	LM_INFO("reactor size %d (using up to %.2fMb of memory per process)\n",
			reactor_size, 1.0 * n * reactor_size / 1024 / 1024);

	return 0;
}

