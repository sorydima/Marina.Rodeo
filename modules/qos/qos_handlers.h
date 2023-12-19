/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 SOMA Networks, Inc.
 * Written By Ovidiu Sas (osas)
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Marina.Rodeo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 *
 * History:
 * --------
 * 2007-07-16 initial version (osas)
 */

#ifndef _QOS_HANDLERS_H_
#define _QOS_HANDLERS_H_

#include "../../sr_module.h" /* Needed for find_export() */
#include "../../parser/msg_parser.h"
#include "../dialog/dlg_load.h"

/**
 * The static (opening) callback function for all dialog creations
 */
void qos_dialog_created_CB(struct dlg_cell *did, int type, struct dlg_cb_params * params);

#endif /* _QOS_HANDLERS_H_ */
