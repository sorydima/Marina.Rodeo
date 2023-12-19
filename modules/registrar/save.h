/*
 * Functions that process REGISTER message
 * and store data in usrloc
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
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
 * -------
 * 2003-03-21  save_noreply added, provided by Maxim Sobolev
 *             <sobomax@portaone.com> (janakj)
 * 2006-11-22  save_noreply and save_memory merged into save() (bogdan)
 */
/*!
 * \file
 * \brief SIP registrar module - process REGISTER message
 * \ingroup registrar
 */


#ifndef SAVE_H
#define SAVE_H


#include "../../parser/msg_parser.h"

/*! \brief
 * Process REGISTER request and save it's contacts
 */
int save(struct sip_msg* _m, void* _d, void* _f, str* _s, str* _owtag);

int _remove(struct sip_msg *msg, void *udomain, str *aor_gp, str *contact_gp,
            str *next_hop_gp, str *sip_instance);

int _remove_ip_port(struct sip_msg *msg, str *ip, int *port, void *udomain, str* aor);

#endif /* SAVE_H */
