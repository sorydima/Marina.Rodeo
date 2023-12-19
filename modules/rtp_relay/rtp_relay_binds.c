/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2021 Marina.Rodeo Solutions
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
 */

#include "rtp_relay_load.h"

int rtp_relay_load(struct rtp_relay_binds *binds)
{
	binds->get_ctx = rtp_relay_get_context;
	binds->get_ctx_dlg = rtp_relay_get_context_dlg;
	binds->offer = rtp_relay_api_offer;
	binds->answer = rtp_relay_api_answer;
	binds->delete = rtp_relay_api_delete;
	binds->copy_offer = rtp_relay_copy_offer;
	binds->copy_answer = rtp_relay_copy_answer;
	binds->copy_delete = rtp_relay_copy_delete;
	return 1;
}
