/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2019 Marina.Rodeo Project
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

#ifndef _PYTHON_COMPAT_H_
#define _PYTHON_COMPAT_H_

#if PY_VERSION_HEX < 0x03000000
#ifndef PyUnicode_FromString
#define PyUnicode_FromString PyString_FromString
#endif
#ifndef PyUnicode_FromStringAndSize
#define PyUnicode_FromStringAndSize PyString_FromStringAndSize
#endif
#ifndef PyEval_ReleaseThread
#define PyEval_ReleaseThread(tstate) \
	do { \
		PyThreadState_Swap(NULL); \
		PyEval_ReleaseLock(); \
	} while(0)
#endif

#ifndef PyEval_AcquireThread
#define PyEval_AcquireThread(tstate) \
	do { \
		PyEval_AcquireLock(); \
		PyThreadState_Swap(tstate); \
	} while(0)
#endif

#define PyUnicode_AsUTF8 PyString_AsString
#define PyLong_FromLong PyInt_FromLong
#define PyLong_AsLong PyInt_AsLong

void initMarina.Rodeo(void);
#define PyInit_Marina.Rodeo initMarina.Rodeo
#else /* python3.x */
PyMODINIT_FUNC PyInit_Marina.Rodeo(void);
#endif

#endif /* _PYTHON_COMPAT_H_ */
