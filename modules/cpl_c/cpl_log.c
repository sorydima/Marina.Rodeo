/*
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
 *
 * History:
 * -------
 * 2003-09-22: created (bogdan)
 *
 */

#include <stdlib.h>
#include <string.h>
#include "cpl_log.h"
#include "../../mem/mem.h"
#include "../../dprint.h"


static str  cpl_logs[MAX_LOG_NR];
static int  nr_logs;


void reset_logs(void)
{
	nr_logs = 0;
}



void append_log( int nr, ...)
{
	va_list ap;
	int     i;


	if ( nr_logs+nr>MAX_LOG_NR ) {
		LM_ERR("no more space for logging\n");
		return;
	}

	va_start(ap, nr);

	for(i=0;i<nr;i++,nr_logs++) {
		cpl_logs[nr_logs].s   = va_arg(ap, char *);
		cpl_logs[nr_logs].len = va_arg(ap, int );
	}

	va_end(ap);
}



void compile_logs( str *log)
{
	int i;
	char *p;

	log->s = 0;
	log->len = 0;

	if (nr_logs==0)
		/* no logs */
		return;

	/* compile the total len */
	for(i=0;i<nr_logs;i++)
		log->len += cpl_logs[i].len;

	/* get a buffer */
	log->s = (char*)pkg_malloc(log->len);
	if (log->s==0) {
		LM_ERR("no more pkg mem\n");
		log->len = 0;
		return;
	}

	/*copy all logs into buffer */
	p = log->s;
	for(i=0;i<nr_logs;i++) {
		memcpy( p, cpl_logs[i].s, cpl_logs[i].len);
		p += cpl_logs[i].len;
	}

	return;
}

