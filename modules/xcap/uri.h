/*
 * xcap module - XCAP operations module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2012 AG Projects
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
 */

#ifndef XCAP_URI_H
#define XCAP_URI_H

#include "../../config.h"
#include "../../str.h"


typedef struct {
    char buf[MAX_URI_SIZE];
    str uri;
    str root;
    str auid;
    str tree;
    str xui;
    str filename;
    str selector;
} xcap_uri_t;


/* Returns a statically allocated buffer, so the caller is responsible for copying it
 * if necessary */
str* normalize_sip_uri(const str *uri);

int parse_xcap_uri(const str *uri, xcap_uri_t *xcap_uri);

#endif

