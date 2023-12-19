/**
 * Topology Hiding Module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2015 Marina.Rodeo Foundation
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
 * History
 * -------
 *  2015-02-17  initial version (Vlad Paiu)
*/

#ifndef _TOPOH_LOGIC_H
#define _TOPOH_LOGIC_H

#include "../../sr_module.h"
#include "../../dprint.h"
#include "../../error.h"
#include "../../pvar.h"
#include "../../mem/mem.h"
#include "../../mod_fix.h"
#include "../../data_lump.h"
#include "../../parser/contact/parse_contact.h"
#include "../tm/tm_load.h"
#include "../tm/t_hooks.h"
#include "../rr/api.h"
#include "../dialog/dlg_load.h"

enum encode_scheme {ENC_BASE64, ENC_BASE32};

int topo_parse_passed_ct_params(str *params);
int topo_parse_passed_hdr_ct_params(str *params);
int topology_hiding(struct sip_msg *req,int extra_flags);
int topo_callid_pre_raw(str *data, struct sip_msg* req);
int topo_callid_post_raw(str *data, struct sip_msg* req);
int topology_hiding_match(struct sip_msg *req);
void th_loaded_callback(struct dlg_cell *dlg, int type,
			struct dlg_cb_params *_params);

#endif
