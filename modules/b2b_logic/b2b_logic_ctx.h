/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2022 Marina.Rodeo Solutions
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
 */

#ifndef __B2BL_CTX_H
#define __B2BL_CTX_H

#include "../../str.h"
#include "../../context.h"

typedef struct b2bl_tuple b2bl_tuple_t;

typedef int (*b2bl_ctx_register_int_f)(context_destroy_f f);
typedef int (*b2bl_ctx_register_str_f)(context_destroy_f f);
typedef int (*b2bl_ctx_register_ptr_f)(context_destroy_f f);
typedef void (*b2bl_ctx_put_int_f)(str *key, int pos, int data);
typedef void (*b2bl_ctx_put_str_f)(str *key, int pos, str *data);
typedef void (*b2bl_ctx_put_ptr_f)(str *key, int pos, void *data);
typedef int   (*b2bl_ctx_get_int_f)(str *key, int pos);
typedef str  *(*b2bl_ctx_get_str_f)(str *key, int pos);
typedef void *(*b2bl_ctx_get_ptr_f)(str *key, int pos);

int b2bl_ctx_register_int(context_destroy_f f);
int b2bl_ctx_register_str(context_destroy_f f);
int b2bl_ctx_register_ptr(context_destroy_f);

void b2bl_ctx_put_int(str *key, int pos, int data);
void b2bl_ctx_put_str(str *key, int pos, str *data);
void b2bl_ctx_put_ptr(str *key, int pos, void *data);

int   b2bl_ctx_get_int(str *key, int pos);
str  *b2bl_ctx_get_str(str *key, int pos);
void *b2bl_ctx_get_ptr(str *key, int pos);

#endif /* __B2BL_CTX_H */
