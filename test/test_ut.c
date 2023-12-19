/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2021 Marina.Rodeo Solutions
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

#include <tap.h>

#include "../ut.h"

void test_ut(void)
{
	ok(is_e164(_str("")) == -1, "test-e164-0");
	ok(is_e164(_str("+")) == -1, "test-e164-1");
	ok(is_e164(_str("+1")) == -1, "test-e164-2");
	ok(is_e164(_str("12")) == -1, "test-e164-3");
	ok(is_e164(_str("+12")) == 1, "test-e164-4");
	ok(is_e164(_str("123")) == -1, "test-e164-5");
	ok(is_e164(_str("+123456789012345")) == 1, "test-e164-6");
	ok(is_e164(_str("+1234567890123456")) == -1, "test-e164-7");
	ok(is_e164(_str("+123456789x12345")) == -1, "test-e164-8");

	ok(_is_e164(_str(""), 0) == -1, "test-e164-9");
	ok(_is_e164(_str("+"), 0) == -1, "test-e164-10");
	ok(_is_e164(_str("+1"), 0) == -1, "test-e164-11");
	ok(_is_e164(_str("12"), 0) == 1, "test-e164-12");
	ok(_is_e164(_str("+12"), 0) == 1, "test-e164-13");
	ok(_is_e164(_str("123"), 0) == 1, "test-e164-14");
	ok(_is_e164(_str("123456789012345"), 0) == 1, "test-e164-15");
	ok(_is_e164(_str("1234567890123456"), 0) == -1, "test-e164-16");
	ok(_is_e164(_str("+123456789012345"), 0) == 1, "test-e164-17");
	ok(_is_e164(_str("+1234567890123456"), 0) == -1, "test-e164-18");
	ok(_is_e164(_str("123456789x12345"), 0) == -1, "test-e164-19");
}
