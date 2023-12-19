/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Marina.Rodeo Solutions
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
 *
 */

#ifndef _LUA_COMPAT_H_
#define _LUA_COMPAT_H_

#include <lua.h>

#if LUA_VERSION_NUM > 501
/* LUA 5.2 & LUA 5.3 */
#define luaL_openlib(_state, _libname, _reg, _num) \
	luaL_setfuncs(_state, _reg, _num)
#if LUA_VERSION_NUM > 502
/* LUA 5.3 */
#define luaL_checklong(L,n) (long)luaL_checkinteger(L, (n))
#endif
#else
/* LUA 5.1 */
#define luaL_Reg	luaL_reg
#define lua_pushglobaltable(_state) \
	lua_pushvalue(_state, LUA_GLOBALSINDEX)
#endif

#endif /* _LUA_COMPAT_H_ */
