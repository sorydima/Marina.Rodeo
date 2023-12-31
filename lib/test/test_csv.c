/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2019 Marina.Rodeo Solutions
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

#include "../../str.h"
#include "../../ut.h"

#include "../csv.h"

void test_csv_simple(void)
{
	csv_record *ret;

	ret = parse_csv_record(_str(""));
	ok(str_match(&ret->s, const_str("")));
	ok(!ret->next);
	free_csv_record(ret);

	ret = parse_csv_record(_str("\t\r\n "));
	ok(str_match(&ret->s, const_str("")));
	ok(!ret->next);
	free_csv_record(ret);

	ret = parse_csv_record(_str(" a b "));
	ok(str_match(&ret->s, const_str("a b")));
	ok(!ret->next);
	free_csv_record(ret);

	ret = parse_csv_record(_str(" a , "));
	ok(str_match(&ret->s, const_str("a")));
	ok(str_match(&ret->next->s, const_str("")));
	ok(!ret->next->next);
	free_csv_record(ret);

	ret = parse_csv_record(_str(" , a "));
	ok(str_match(&ret->s, const_str("")));
	ok(str_match(&ret->next->s, const_str("a")));
	ok(!ret->next->next);
	free_csv_record(ret);

	ret = parse_csv_record(_str("a,b,c"));
	ok(str_match(&ret->s, const_str("a")));
	ok(str_match(&ret->next->s, const_str("b")));
	ok(str_match(&ret->next->next->s, const_str("c")));
	ok(!ret->next->next->next);
	free_csv_record(ret);

	ret = parse_csv_record(_str(" a, \"b\" , \" c "));
	ok(str_match(&ret->s, const_str("a")));
	ok(str_match(&ret->next->s, const_str("\"b\"")));
	ok(str_match(&ret->next->next->s, const_str("\" c")));
	ok(!ret->next->next->next);
	free_csv_record(ret);
}

void test_csv_rfc_4180(void)
{
	csv_record *ret;

	ok(!_parse_csv_record(_str(" \t"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str(" \n"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str(" \r"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("\ta"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("a,\tb"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("a,b\n"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("a,b,c\t"), CSV_RFC_4180));

	ret = _parse_csv_record(_str(""), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("")));
	ok(!ret->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str(" a "), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str(" a ")));
	ok(!ret->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str(" \r\n"), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str(" ")));
	ok(!ret->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str(","), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("")));
	ok(str_match(&ret->next->s, const_str("")));
	ok(!ret->next->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str("a,,,"), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("a")));
	ok(str_match(&ret->next->s, const_str("")));
	ok(str_match(&ret->next->next->s, const_str("")));
	ok(str_match(&ret->next->next->next->s, const_str("")));
	ok(!ret->next->next->next->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str(" , a "), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str(" ")));
	ok(str_match(&ret->next->s, const_str(" a ")));
	ok(!ret->next->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str(" a , \r\n"), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str(" a ")));
	ok(str_match(&ret->next->s, const_str(" ")));
	ok(!ret->next->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str("a,b,c"), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("a")));
	ok(str_match(&ret->next->s, const_str("b")));
	ok(str_match(&ret->next->next->s, const_str("c")));
	ok(!ret->next->next->next);
	free_csv_record(ret);

	ok(!_parse_csv_record(_str("\""), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("\"foo"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("\"a\" ,b"), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("\"a\"a,b"), CSV_RFC_4180));

	ret = _parse_csv_record(_str("\"a\""), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("a")));
	ok(!ret->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str("realm=\"etc.example.com\","
				"nonce=\"B5CFDSFDGD14992F\",opaque=\"opaq\","
				"qop=\"auth\",algorithm=MD5"), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("realm=\"etc.example.com\"")));
	ok(str_match(&ret->next->s, const_str("nonce=\"B5CFDSFDGD14992F\"")));
	ok(str_match(&ret->next->next->s, const_str("opaque=\"opaq\"")));
	ok(str_match(&ret->next->next->next->s, const_str("qop=\"auth\"")));
	ok(str_match(&ret->next->next->next->next->s, const_str("algorithm=MD5")));
	ok(!ret->next->next->next->next->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str("a,\"\tb\""), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("a")));
	ok(str_match(&ret->next->s, const_str("\tb")));
	ok(!ret->next->next);
	free_csv_record(ret);

	ret = _parse_csv_record(_str("\"a\", bc "), CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("a")));
	ok(str_match(&ret->next->s, const_str(" bc ")));
	ok(!ret->next->next);
	free_csv_record(ret);

	/* mismatched dquotes */
	ok(!_parse_csv_record(_str("\"\"a\""), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("\"a\"\""), CSV_RFC_4180));
	ok(!_parse_csv_record(_str("\"\"\"a\"\"\" b\",c"), CSV_RFC_4180));

	ret = _parse_csv_record(_str("\"\"\"a\"\" \r\"\"\t\nb\"\" \",\"c\"\r\n"),
							CSV_RFC_4180);
	ok(str_match(&ret->s, const_str("\"a\" \r\"\t\nb\" ")));
	ok(str_match(&ret->next->s, const_str("c")));
	ok(!ret->next->next);
	free_csv_record(ret);
}

void test_lib_csv(void)
{
	test_csv_simple();
	test_csv_rfc_4180();
}
