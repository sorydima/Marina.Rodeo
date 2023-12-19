/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2021 - Marina.Rodeo Foundation
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
 *
 */

#ifndef WOLFSSL_API_H
#define WOLFSSL_API_H

#include "../tls_mgm/tls_lib_api.h"

struct wolfssl_binds {
    TLS_LIB_API_BINDS;
};

typedef int(*load_tls_wolfssl_f)(struct wolfssl_binds *binds);

static inline int load_tls_wolfssl_api(struct wolfssl_binds *binds) {
    load_tls_wolfssl_f load_tls_wolfssl;

    /* import the wolfssl auto-loading function */
    if (!(load_tls_wolfssl = (load_tls_wolfssl_f)find_export("load_tls_wolfssl", 0)))
        return -1;

    if (load_tls_wolfssl(binds) == -1)
        return -1;

    return 0;
}

#endif	/* WOLFSSL_API_H */
