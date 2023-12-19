/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2020 Marina.Rodeo Solutions
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <tap.h>

#include "../../../dprint.h"
#include "../../../dset.h"
#include "../../../test/ut.h"
#include "../../../parser/parse_methods.h"
#include "../../../parser/msg_parser.h"
#include "../../../lib/reg/common.h"

#include "../../usrloc/usrloc.h"
#include "../reg_mod.h"
#include "../lookup.h"


static void fill_ucontact_info(ucontact_info_t *ci)
{
	static char cid_buf[9];
	static str callid = {cid_buf, 0};
	static str no_ua = str_init("n/a");

	update_act_time();

	memset(ci, 0, sizeof *ci);

	callid.len = sprintf(cid_buf, "%x", rand());
	ci->callid = &callid;
	ci->user_agent = &no_ua;
	ci->q = Q_UNSPECIFIED;
	ci->expires = get_act_time() + 120;
	ci->methods = ALL_METHODS;
}


static void test_lookup(void)
{
	udomain_t *d;
	urecord_t *r;
	ucontact_t *c;
	ucontact_info_t ci;
	str aor = str_init("alice");
	str aor_ruri = str_init("sip:alice@localhost");
	str ct1 = str_init("sip:cell@127.0.0.1:44444;"
			"pn-provider=apns;"
			"pn-prid=ZTY4ZDJlMzODE1NmUgKi0K;"
			"pn-param=ezenSQIywP8:APA91bHFH7p41WUFljaUPM2PPEjQUEslb6NtIqN6Pyc"
			         "gN5eDCyzuomQMyWboTVum0MY8YL_3E8vFIZUur_B71DHVgXQVD6UfZJ"
			         "mAq9Px0UY8YjVmo2LnmCocmFRBU0gPMV2ebheGGWCc");
	str ct2 = str_init("sip:desk@127.0.0.2");
	struct sip_msg msg;
	struct lookup_flags flags;

	memset(&flags, 0, sizeof flags);

	ok(ul.register_udomain("location", &d) == 0, "get 'location' udomain");

	mk_sip_req("INVITE", "sip:alice@localhost", &msg);
	ok(reg_lookup(&msg, d, NULL, NULL) == LOOKUP_NO_RESULTS, "lookup-1");

	ul.lock_udomain(d, &aor);
	ok(ul.insert_urecord(d, &aor, &r, 0) == 0, "create AoR");

	fill_ucontact_info(&ci);
	ci.methods = METHOD_UNDEF;
	ok(ul.insert_ucontact(r, &ct2, &ci, NULL, 1, &c) == 0, "insert Contact");
	ul.unlock_udomain(d, &aor);

	ok(reg_lookup(&msg, d, NULL, NULL) == LOOKUP_OK, "lookup-2");

	set_ruri(&msg, &aor_ruri);
	flags.flags = REG_LOOKUP_METHODFILTER_FLAG;
	ok(reg_lookup(&msg, d, &flags, NULL) == LOOKUP_METHOD_UNSUP,
		"lookup-3");

	c->methods = ALL_METHODS;

	set_ruri(&msg, &aor_ruri);
	ok(reg_lookup(&msg, d, NULL, NULL) == LOOKUP_OK, "lookup-4");

	set_ruri(&msg, &aor_ruri);
	ok(reg_lookup(&msg, d, &flags, NULL) == LOOKUP_OK,
		"lookup-5");

	ok(ul.delete_ucontact(r, c, NULL, 0) == 0, "delete ucontact");

	fill_ucontact_info(&ci);
	ci.flags |= FL_PN_ON; /* this is needed until we rewrite to call save() */
	ok(ul.insert_ucontact(r, &ct1, &ci, NULL, 1, &c) == 0, "insert ct1 (PN)");

	set_ruri(&msg, &aor_ruri);
	ok(reg_lookup(&msg, d, NULL, NULL) == LOOKUP_PN_SENT, "lookup-6");

	fill_ucontact_info(&ci);
	ok(ul.insert_ucontact(r, &ct2, &ci, NULL, 1, &c) == 0, "insert ct2 (normal)");

	set_ruri(&msg, &aor_ruri);
	ok(reg_lookup(&msg, d, NULL, NULL) == LOOKUP_OK, "lookup-7");

	/* the PN contact should just trigger a PN without becoming a branch */
	ok(str_match(&msg.new_uri, &ct2), "lookup-7: R-URI is ct2");

	/* test the "r" flag (branch lookup) */
	{
		str aor2 = str_init("bob"), aor3 = str_init("carol");

		ul.lock_udomain(d, &aor2);
		ok(ul.insert_urecord(d, &aor2, &r, 0) == 0, "create AoR 2");
		ul.unlock_udomain(d, &aor2);

		ul.lock_udomain(d, &aor3);
		ok(ul.insert_urecord(d, &aor3, &r, 0) == 0, "create AoR 3");
		fill_ucontact_info(&ci);
		ci.methods = METHOD_UNDEF;
		ok(ul.insert_ucontact(r, &ct2, &ci, NULL, 1, &c) == 0, "insert Contact for AoR 3");
		ul.unlock_udomain(d, &aor3);

		/* ensure the AoR expansion process doesn't stop on a non-existing AoR */
		str ruri1 = str_init("sip:FOOBAR@foobar.com");
		ok(append_branch(NULL, &ruri1, NULL, NULL, 1, 0, NULL) == 1, "append AoR-2");

		str ruri2 = str_init("sip:carol@foobar.com");
		ok(append_branch(NULL, &ruri2, NULL, NULL, 1, 0, NULL) == 1, "append AoR-3");

		set_ruri(&msg, &aor_ruri);
		flags.flags = REG_BRANCH_AOR_LOOKUP_FLAG;
		ok(reg_lookup(&msg, d, &flags, NULL) == LOOKUP_OK, "lookup-8");
		ok(get_nr_branches() == 1, "get-nr-branches");
	}
}


static void test_purr(void)
{
	ucontact_id id = 0UL;
	char *p;

	ok(!strcmp(pn_purr_pack(0UL), "000.00000.00000000"), "purr-1");
	ok(!strcmp(pn_purr_pack(18446744073709551615UL),
	           "fff.fffff.ffffffff"), "purr-2");

	/* tricky PURR formats (all bad) */
	ok(pn_purr_unpack(_str("000.00000.0000000"), &id) == -1, "purr-4");
	ok(pn_purr_unpack(_str("000.00000.000000000"), &id) == -1, "purr-5");
	ok(pn_purr_unpack(_str("00.000000.00000000"), &id) == -1, "purr-6");
	ok(pn_purr_unpack(_str("0000.0000.00000000"), &id) == -1, "purr-7");
	ok(pn_purr_unpack(_str("000.0000.000000000"), &id) == -1, "purr-8");
	ok(pn_purr_unpack(_str("000.000000.0000000"), &id) == -1, "purr-9");
	ok(pn_purr_unpack(_str("000000000.00000000"), &id) == -1, "purr-10");
	ok(pn_purr_unpack(_str("000.00000000000000"), &id) == -1, "purr-11");
	ok(pn_purr_unpack(_str("000000000000000000"), &id) == -1, "purr-12");
	ok(pn_purr_unpack(_str(".00.00000.00000000"), &id) == -1, "purr-13");
	ok(pn_purr_unpack(_str("000.00000.0000000."), &id) == -1, "purr-14");
	ok(pn_purr_unpack(_str(".................."), &id) == -1, "purr-15");

	ok(pn_purr_unpack(_str("000.00000.00000000"), &id) == 0, "purr-16");
	ok(id == 0UL, "purr-17");

	ok(pn_purr_unpack(_str("fff.fffff.ffffffff"), &id) == 0, "purr-18");
	ok(id == 18446744073709551615UL, "purr-19");

	p = pn_purr_pack(12345678901234567890UL);
	ok(pn_purr_unpack(_str(p), &id) == 0, "purr-20");
	ok(id == 12345678901234567890UL, "purr-21");
}


void mod_tests(void)
{
	test_lookup();
	test_purr();
}
