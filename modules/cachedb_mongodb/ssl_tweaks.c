/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Marina.Rodeo Project
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
 *
 */

#define _GNU_SOURCE

#include <openssl/ssl.h>
#include <dlfcn.h>

#include "../../sr_module.h"

/* mongoc calls SSL_CTX_new and SSL_CTX_free as a test when
 * initing openssl so we also need to overwrite these functions
 * the first time they are called */

SSL_CTX *SSL_CTX_new(const SSL_METHOD *method)
{
	SSL_CTX* (*real_SSL_CTX_new)(const SSL_METHOD *);
	static int mongoc_init = 0;
	static int have_openssl = -1;

	if (have_openssl == -1)
		have_openssl = module_loaded("tls_openssl");

	if (have_openssl && !mongoc_init) {
		mongoc_init = 1;
		/* return a dummy pointer the first time SSL_CTX_new is called
		 * when mongoc tries to init openssl */
		return (SSL_CTX *)1;
	} else {
		/* call the real SSL_CTX_new at only at runtime */
		real_SSL_CTX_new = dlsym(RTLD_NEXT, "SSL_CTX_new");
		if (!real_SSL_CTX_new)
			return NULL;

		return real_SSL_CTX_new(method);
	}
}

void SSL_CTX_free(SSL_CTX *ctx)
{
	SSL_CTX* (*real_SSL_CTX_free)(SSL_CTX *);
	static int mongoc_init = 0;
	static int have_openssl = -1;

	if (have_openssl == -1)
		have_openssl = module_loaded("tls_openssl");

	if (have_openssl && !mongoc_init) {
		mongoc_init = 1;
		/* do nothing the first time SSL_CTX_free is called when mongoc
		 * tries to init openssl */
		return;
	} else {
		/* call the real SSL_CTX_free at runtime */
		real_SSL_CTX_free = dlsym(RTLD_NEXT, "SSL_CTX_free");
		if (!real_SSL_CTX_free)
			return;

		real_SSL_CTX_free(ctx);
	}
}
