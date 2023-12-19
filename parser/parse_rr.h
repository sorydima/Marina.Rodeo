/*
 * Route & Record-Route Parser
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
 */


#ifndef PARSE_RR_H
#define PARSE_RR_H

#include <stdio.h>
#include "msg_parser.h"
#include "parse_nameaddr.h"
#include "parse_param.h"
#include "hf.h"


/*
 * Structure representing a Route & Record-Route HF body
 */
typedef struct rr {
	name_addr_t nameaddr; /* Name-addr part */
	param_t* r2;          /* Hook to r2 parameter */
	param_t* params;      /* Linked list of other parameters */
	int len;              /* Length of the whole route field */
	int deleted;		  /* is this header to be removed ? */
	struct rr* next;      /* Next RR in the list */
} rr_t;


/*
 * Parse Route & Record-Route header fields
 */
int parse_rr(struct hdr_field* _r);

/*
 * Parse the body of Route & Record-Route headers
 */
int parse_rr_body(char *buf, int len, rr_t **head);

/*
 * Free list of rr
 * _c is head of the list
 */
void free_rr(rr_t** _r);


/*
 * Free list of rr
 * _c is head of the list
 */
void shm_free_rr(rr_t** _r);


/*
 * Print list of rrs, just for debugging
 */
void print_rr(FILE* _o, rr_t* _r);


/*
 * Duplicate a single (first) or the whole list of rr_t structure
 * using pkg_malloc
 */
int duplicate_rr(rr_t** _new, rr_t* _r, int _first);


/*
 * Duplicate a single (first) or the whole list of rr_t structure
 * using shm_malloc
 */
int shm_duplicate_rr(rr_t** _new, rr_t* _r, int _first);

/*
 * print body for all RR headers in comma separated string
 */
int print_rr_body(struct hdr_field *iroute, str *oroute, int order,
		int no_change, unsigned int * nb_recs);

/*
 * Function returns the first uri
 * from Path without any duplication.
 */
int get_path_dst_uri(str *_p, str *_dst);

#endif /* PARSE_RR_H */
