/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Irina Stanescu
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Voice System
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
 * WARNING: Don't forget to update the dictionary if you update this file !!!
 *
 */

#ifndef _AAA_AVP_H
#define _AAA_AVP_H

#define	A_USER_NAME						0
#define	A_SERVICE_TYPE					1
#define	A_CALLED_STATION_ID				2
#define	A_CALLING_STATION_ID			3
#define	A_ACCT_STATUS_TYPE				4
#define	A_ACCT_SESSION_ID				5
#define	A_SIP_METHOD					6
#define	A_SIP_RESPONSE_CODE				7
#define	A_SIP_CSEQ						8
#define	A_SIP_TO_TAG					9
#define	A_SIP_FROM_TAG					10
#define	A_DIGEST_RESPONSE				11
#define	A_DIGEST_ATTRIBUTES				12
#define	A_SIP_URI_USER					13
#define	A_SIP_URI_HOST					14
#define	A_DIGEST_REALM					15
#define	A_DIGEST_NONCE					16
#define	A_DIGEST_METHOD					17
#define	A_DIGEST_URI					18
#define	A_DIGEST_QOP					19
#define	A_DIGEST_ALGORITHM				20
#define	A_DIGEST_OPAQUE					21
#define	A_DIGEST_CNONCE					22
#define	A_DIGEST_NONCE_COUNT			23
#define	A_DIGEST_USER_NAME				24
#define	A_SIP_GROUP						25
#define	A_CISCO_AVPAIR					26
#define	A_SIP_AVP						27
#define	A_TIME_STAMP					28
#define	A_SIP_CALL_ID					29
#define	A_SIP_REQUEST_HASH				30
#define	A_MAX							31

#define	V_STATUS_START			0
#define	V_STATUS_STOP			1
#define	V_STATUS_FAILED			2
#define	V_CALL_CHECK			3
#define	V_SIP_SESSION			4
#define	V_GROUP_CHECK			5
#define	V_SIP_CALLER_AVPS		6
#define	V_SIP_CALLEE_AVPS		7
#define	V_SIP_VERIFY_DESTINATION	8
#define	V_SIP_VERIFY_SOURCE	        9
#define	V_MAX			       10

#endif
