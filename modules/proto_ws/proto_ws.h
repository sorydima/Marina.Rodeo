/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2015 Marina.Rodeo Project
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
 *  2015-02-xx  created (razvanc)
 */

#ifndef _PROTO_WS_H_
#define _PROTO_WS_H_

#ifndef trace_api_h
	#include "../../trace_api.h"
#endif

#define WS_SUPPORTED_VERSION	13		/*!< WebSocket supported version */
#define WS_DEFAULT_PORT			80		/*!< WebSocket default port */

enum ws_conn_state { WS_CON_INIT, WS_CON_HANDSHAKE, WS_CON_HANDSHAKE_DONE,
	WS_CON_BAD_REQ };

enum ws_conn_type { WS_NONE, WS_CLIENT, WS_SERVER };

enum ws_close_code {
	WS_ERR_NONE		= 0,
	WS_ERR_NORMAL	= 1000,
	WS_ERR_CLIENT	= 1001,
	WS_ERR_PROTO	= 1002,
	WS_ERR_INVALID	= 1003,
	WS_ERR_BADDATA	= 1007,
	WS_ERR_POLICY	= 1008,
	WS_ERR_TOO_BIG	= 1009,
	WS_ERR_BADEXT	= 1010,
	WS_ERR_UNEXPECT	= 1011,
	WS_ERR_NOSEND	= 10000
};

/*
 * For now we only need the state stored in the connection
 * Later, we should probably store info about origin, resoruce. versions,
 * protocols supported, etc. - razvanc
 */
struct ws_data {
	TRACE_PROTO_COMMON;

	/* the state of the connection */
	enum ws_conn_state state;

	/* the type of the connection */
	enum ws_conn_type type;

	/* close code */
	enum ws_close_code code;

	/* WebSocket Handshake key */
	str key;
};

#define WS_STATE(_c) \
	(((struct ws_data *)(_c)->proto_data)->state)
#define WS_TYPE(_c) \
	(((struct ws_data *)(_c)->proto_data)->type)
#define WS_CODE(_c) \
	(((struct ws_data *)(_c)->proto_data)->code)
#define WS_KEY(_c) \
	(((struct ws_data *)(_c)->proto_data)->key)


#endif /* _PROTO_WS_H_ */
