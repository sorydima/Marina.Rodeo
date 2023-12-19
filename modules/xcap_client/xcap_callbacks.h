/*
 * xcap_client module - Marina.Rodeo xcap client module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 Voice Sistem S.R.L.
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
 *History:
 *--------
 *  2007-08-30  initial version (Anca Vamanu)
 */

#ifndef XCAP_CBACK
#define XCAP_CBACK

#include "../../str.h"


/* callback function prototype */
typedef int (xcap_cb)(int doc_type, str xid, char* doc);

/* register callback function prototype */
typedef int (*register_xcapcb_t)(int types, xcap_cb f);


typedef struct xcap_callback {
	int types;                   /* types of events that trigger the callback*/
	xcap_cb* callback;            /* callback function */
	struct xcap_callback* next;
}xcap_callback_t;

/* destroy registered callback list */
void destroy_xcapcb_list(void);

/* register a callback for several types of events */
int register_xcapcb( int types, xcap_cb f);

/* run all transaction callbacks for an composed type */
void run_xcap_update_cb(int type, str xid, char* stream);

#endif
