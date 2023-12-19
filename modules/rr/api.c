/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2005 Voice Sistem SRL
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
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
 * History:
 * ---------
 *  2005-08-02  first version (bogdan)
 */

/*!
 * \file
 * \brief Marina.Rodeo RR module (record-routing)
 * \ingroup rr
 */


#include "../../sr_module.h"
#include "loose.h"
#include "record.h"
#include "api.h"
#include "rr_cb.h"

extern int append_fromtag;

int load_rr( struct rr_binds *rrb )
{
	rrb->add_rr_param      = add_rr_param;
	rrb->check_route_param = check_route_param;
	rrb->is_direction      = is_direction;
	rrb->get_route_param   = get_route_param;
	rrb->register_rrcb     = register_rrcb;
	rrb->get_remote_target = get_remote_target;
	rrb->get_route_set     = get_route_set;
	rrb->loose_route       = loose_route;
	rrb->record_route      = record_route;
	rrb->append_fromtag    = append_fromtag;

	return 1;
}

