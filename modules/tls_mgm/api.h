/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2015-2021 Marina.Rodeo Solutions
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * In addition, as a special exception, the Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
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


#ifndef TLS_API_H
#define TLS_API_H

#include "../../trace_api.h"
#include "../../net/trans_trace.h"

#include "tls_helper.h"

typedef struct tls_domain * (*tls_find_server_domain_f) (struct ip_addr *, unsigned short);
typedef struct tls_domain * (*tls_find_client_domain_f) (struct ip_addr *, unsigned short);
typedef struct tls_domain * (*tls_find_client_domain_name_f) (str *);
typedef void (*tls_release_domain_f) (struct tls_domain *);

/* TLS conn ops */
typedef int (*tls_conn_init_f)(struct tcp_connection *c,
    struct tls_domain *tls_dom);
typedef void (*tls_conn_clean_f)(struct tcp_connection* c,
    struct tls_domain **tls_dom);
typedef int (*tls_update_fd_f)(struct tcp_connection* c, int fd);
typedef int (*tls_async_connect_f)(struct tcp_connection *con, int fd,
    int timeout, trace_dest t_dst);
typedef int (*tls_write_f)(struct tcp_connection *c, int fd, const void *buf,
    size_t len, short *poll_events);
typedef int (*tls_blocking_write_f)(struct tcp_connection *c, int fd,
    const char *buf, size_t len, int handshake_timeout, int send_timeout,
    trace_dest t_dst);
typedef int (*tls_fix_read_conn_f)(struct tcp_connection *c, int fd,
    int async_timeout, trace_dest t_dst, int lock);
typedef int (*tls_read_f)(struct tcp_connection * c,struct tcp_req *r);
typedef int (*tls_conn_extra_match_f)(struct tcp_connection *c, void *id);

enum os_tls_library {
    TLS_LIB_NONE,
    TLS_LIB_OPENSSL,
    TLS_LIB_WOLFSSL
};

typedef int (*get_tls_library_used_f)(void);

struct tls_mgm_binds {
    tls_find_server_domain_f find_server_domain;
    tls_find_client_domain_f find_client_domain;
    tls_find_client_domain_name_f find_client_domain_name;
    tls_release_domain_f release_domain;

    tls_conn_init_f tls_conn_init;
    tls_conn_clean_f tls_conn_clean;
    tls_update_fd_f tls_update_fd;
    tls_async_connect_f tls_async_connect;
    tls_write_f tls_write;
    tls_blocking_write_f tls_blocking_write;
    tls_fix_read_conn_f tls_fix_read_conn;
    tls_read_f tls_read;
    tls_conn_extra_match_f tls_conn_extra_match;

    get_tls_library_used_f get_tls_library_used;
};


typedef int(*load_tls_mgm_f)(struct tls_mgm_binds *binds);

static inline int load_tls_mgm_api(struct tls_mgm_binds *binds) {
    load_tls_mgm_f load_tls;

    /* import the DLG auto-loading function */
    if (!(load_tls = (load_tls_mgm_f) find_export("load_tls_mgm", 0)))
        return -1;

    /* let the auto-loading function load all DLG stuff */
    if (load_tls(binds) == -1)
        return -1;

    return 0;
}

#endif	/* TLS_API_H */
