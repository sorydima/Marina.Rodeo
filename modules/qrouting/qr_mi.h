/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Marina.Rodeo Solutions
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __QR_MI__
#define __QR_MI__

mi_cmd_f mi_qr_status_0;
mi_cmd_f mi_qr_status_1;
mi_cmd_f mi_qr_status_2;
mi_cmd_f mi_qr_status_3;

mi_cmd_f mi_qr_reload_0;

mi_cmd_f mi_qr_disable_dst_2;
mi_cmd_f mi_qr_disable_dst_3;

mi_cmd_f mi_qr_enable_dst_2;
mi_cmd_f mi_qr_enable_dst_3;

int qr_set_dst_state(qr_rule_t *rules, int rule_id, str *dst_name,
                     int active, mi_response_t **err_resp);

#endif /* __QR_MI__ */
