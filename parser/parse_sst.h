/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (c) 2006 SOMA Networks, Inc. <http://www.somanetworks.com/>
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
 * 2006-02-17 Initial revision (dhsueh@somanetworks.com)
 */

#ifndef PARSE_SST_H
#define PARSE_SST_H 1


#include "msg_parser.h"
#include "hf.h"


/**
 * Indicate the "refresher=" value of the Session-Expires header.
 */
enum sst_refresher {
	sst_refresher_unspecified,
	sst_refresher_uac,
	sst_refresher_uas,
};


/**
 * We will treat the 'void* parsed' field of struct hdr_field as
 * a pointer to a struct session_expires.
 */
struct session_expires {
	unsigned            interval; /* in seconds */
	enum sst_refresher  refresher;
};


enum parse_sst_result {
	parse_sst_success,
	parse_sst_header_not_found,	/* no header */
	parse_sst_no_value,			/* no interval specified */
#if NOT_IMPLEMENTED_YET
	parse_sst_duplicate,		/* multiple s-e / x / min-se headers found */
#endif
	parse_sst_out_of_mem,
	parse_sst_parse_error,		/* something puked */
};


/**
 * Allocate a zeroed-out struct session_expires.
 */
struct session_expires *
malloc_session_expires( void );


/**
 * Deallocates memory previously allocated via malloc_session_expires().
 */
void
free_session_expires( struct session_expires * );


/**
 * Parses the (should be only one instance) single instance of the
 * "Session-Expires" or "x" header in the msg.  Note that the header
 * is not automatically parsed in parse_headers()[1] so you'll have to
 * call this function to get the information.
 *
 * Because of time constraints, this function is coded assuming there is
 * NO WHITESPACE in any of the body -- note that the augBNF for the
 * Session-Expires body allows sep whitespace between tokens:
 *   delta-seconds SWS ";" SWS "refresher" SWS "=" SWS ( "uac" / "uas" )
 *
 * Note[1]: it looks like only the frequently-used headers are
 * automatically parsed in parse_headers() (indicated by a parse_<name>
 * function of the form "char* parse_<name>(char *buf, char *end, foo*)
 * and a struct foo with a member called "error").
 *
 * @param msg the sip message to examine
 * @param se the place to store session-expires information into, if
 *         provided; note that result is also available in
 *         *((struct session_expires *)msg->session_expires->parsed)
 * @return parse_sst_result
 */
enum parse_sst_result
parse_session_expires( struct sip_msg *msg, struct session_expires *se );
/**
 * helper function for parse_session_expires
 */
enum parse_sst_result
parse_session_expires_body( struct hdr_field *hf );


/**
 * Parses the (should be only one instance) single instance of the
 * "Min-SE" header in the msg.  Note that this header is not automatically
 * parsed in parse_headers() so you'll have to call this function to get
 * the information.
 *
 * @param msg the sip message to examine
 * @param min_se the place to store the Min-SE value, if provided; note that
 *         result is also available in (unsigned)msg->min_se->parsed
 * @return parse_sst_result
 */
enum parse_sst_result
parse_min_se( struct sip_msg *msg, unsigned *min_se );

/**
 * Parses the given instance of "Min-SE" header.
 *
 * @param hf the header field structure to be parsed
 * @return parse_sst_result
 */
enum parse_sst_result
parse_min_se_body( struct hdr_field *hf );

#endif /* ! PARSE_SST_H */
