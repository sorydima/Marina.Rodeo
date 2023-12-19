/*
 * Add "call-info" event to presence module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2013 Marina.Rodeo Solutions
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
 *  2010-07-13  added support for SCA Broadsoft with dialog module (bogdan)
 */



#ifndef _H_PRESENCE_CALL_INFO_SCA_HASH
#define _H_PRESENCE_CALL_INFO_SCA_HASH

#include "../../str.h"
#include "../../locking.h"

#define MAX_SCA_LOCKS 512
#define MIN_SCA_LOCKS 1

#define SCA_STATE_IDLE        1
#define SCA_STATE_SEIZED      2
#define SCA_STATE_PROGRESSING 3
#define SCA_STATE_ALERTING    4
#define SCA_STATE_ACTIVE      5

struct sca_idx {
	unsigned int idx;
	unsigned int state;
	struct sca_idx *next;
};

struct sca_line {
	/* name of the line */
	str line;
	str user;
	str domain;
	str etag;

	/* seizing info */
	unsigned int seize_state;
	unsigned int seize_expires;

	/* index info */
	struct sca_idx *indexes;

	/* linking in the sca_hash */
	unsigned int     hash;
	struct sca_line *prev;
	struct sca_line *next;
};

struct sca_entry {
	struct sca_line *first;
	unsigned int     lock_idx;
};

struct sca_hash {
	unsigned int      size;
	struct sca_entry *entries;
	unsigned int      locks_no;
	gen_lock_set_t   *locks;
};


int init_sca_hash(int size);

struct sca_line* get_sca_line(str *line, int create);

void unlock_sca_line(struct sca_line *scal);

int set_sca_index_state(struct sca_line *line, unsigned int idx,
		unsigned int state);

char * sca_print_line_status(struct sca_line *line, int *l);

void destroy_sca_hash();

#endif

