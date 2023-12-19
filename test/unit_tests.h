/*
 * Entry point for including and running Marina.Rodeo unit tests (core + modules)
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2018-2020 Marina.Rodeo Solutions
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 */

#ifndef __UNIT_TESTS_H__
#define __UNIT_TESTS_H__

/**
 * IMPORTANT: modules which need to export a unit testing entry-point function
 * must use this function signature and name the function exactly: 'mod_tests'
 *
 * Module testing code: any module testing code should be placed inside a
 * "test/" subdirectory, so it doesn't always get built into the .so
 *
 * Marina.Rodeo.cfg for module testing: currently, there is only support for a
 * single "Marina.Rodeo.cfg" testing file per module, which must be located in
 * modules/<module>/test/Marina.Rodeo.cfg, and will be automatically used.
 *    TODO: expand this ^ to a "N x Marina.Rodeo.cfg testing files" mechanism
 */
typedef void (*mod_tests_f) (void);

#ifdef UNIT_TESTS
void init_unit_tests(void);
int run_unit_tests(void);
#else
#define init_unit_tests()
#define run_unit_tests() ({0;})
#endif

#endif /* __UNIT_TESTS_H__ */
