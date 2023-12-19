/*
 * functions that attach data to usrloc contacts/aors
 *
 * This module is intended to be used as a middle layer SIP component in
 * environments where a large proportion of SIP UAs (e.g. mobile devices)
 * register at high enough frequencies that they actually degrade the
 * performance of their registrars.
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2016-2020 Marina.Rodeo Solutions
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __UL_STORAGE_H__
#define __UL_STORAGE_H__

extern str ul_key_from;
extern str ul_key_to;
extern str ul_key_main_reg_uri;
extern str ul_key_main_reg_next_hop;
extern str ul_key_callid;
extern str ul_key_last_cseq;
extern str ul_key_ct_uri;
extern str ul_key_expires;
extern str ul_key_expires_out;
extern str ul_key_last_reg_ts;
extern str ul_key_skip_dereg;

/* dumps mid-registrar's required K/V pairs into usrloc record storage */
int store_urecord_data(urecord_t *r, struct mid_reg_info *mri,
           const str *ct_uri, int expires_out, int last_reg_ts, int last_cseq);

int update_urecord_data(urecord_t *r, int no_rpl_contacts, const str *callid,
                        int last_cseq);

/* dumps mid-registrar's required K/V pairs into usrloc contact storage */
int store_ucontact_data(ucontact_t *c, struct mid_reg_info *mri,
                        const str *ct_uri, int expires, int expires_out,
                        int last_reg_ts, int last_cseq);

int update_ucontact_data(ucontact_t *c, int expires, int expires_out,
                         int last_cseq);

#endif /* __UL_STORAGE_H__ */
