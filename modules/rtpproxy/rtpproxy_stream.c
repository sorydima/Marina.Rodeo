/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2008 Sippy Software, Inc., http://www.sippysoft.com
 *
 * This file is part of ser, a free SIP server.
 *
 * ser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * For a license to use the ser software under conditions
 * other than those described here, or to purchase support for this
 * software, please contact iptel.org by e-mail at the following addresses:
 *    info@iptel.org
 *
 * ser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "../../ip_addr.h"
#include "../../parser/msg_parser.h"
#include "../../sr_module.h"
#include "../../ut.h"
#include "rtpproxy.h"
#include "nhelpr_funcs.h"
#include "rtpproxy_vcmd.h"

static int
rtpproxy_stream(struct sip_msg* msg, str *pname, int count,
            nh_set_param_t *setid, pv_spec_t *var, int stream2uac)
{
    int nitems, ret = -1;
    str callid, from_tag, to_tag;
    struct rtpp_node *node;
    struct rtpp_set *set;
    char cbuf[16];
    struct rtpproxy_vcmd vstream;

    RTPP_VCMD_INIT(vstream, 10,
        {cbuf,        0}, /*.vu[0] P<count> */
        {" ",         1},
        {NULL,        0}, /*.vu[2] callid */
        {" ",         1},
        {NULL,        0}, /*.vu[4] pname */
        {" session ", 9},
        {NULL,        0}, /*.vu[6] from tag */
        {";1 ",       3},
        {NULL,        0}, /*.vu[8] to tag */
        {";1",        2}
    );

    if (get_callid(msg, &callid) == -1 || callid.len == 0) {
        LM_ERR("can't get Call-Id field\n");
        return -1;
    }
    if (get_to_tag(msg, &to_tag) == -1) {
        LM_ERR("can't get To tag\n");
        return -1;
    }
    if (get_from_tag(msg, &from_tag) == -1 || from_tag.len == 0) {
        LM_ERR("can't get From tag\n");
        return -1;
    }
    vstream.vu[0].iov_len = sprintf(cbuf, "P%d", count);
    STR2IOVEC(callid, vstream.vu[2]);
    STR2IOVEC(*pname, vstream.vu[4]);

    nitems = vstream.useritems;
    if (stream2uac == 0) {
        if (to_tag.len == 0)
            return -1;
        STR2IOVEC(to_tag, vstream.vu[6]);
        STR2IOVEC(from_tag, vstream.vu[8]);
    } else {
        STR2IOVEC(from_tag, vstream.vu[6]);
        STR2IOVEC(to_tag, vstream.vu[8]);
        if (to_tag.len <= 0)
            nitems -= 2;
    }
	if (nh_lock) {
		lock_start_read( nh_lock );
	}

	set = get_rtpp_set(setid);
	if (!set) {
		LM_ERR("no set found\n");
		goto end;
	}

    node = select_rtpp_node(msg, callid, set, var, 1);
    if (!node) {
        LM_ERR("no available proxies\n");
        goto end;
    }

    if (!HAS_CAP(node, CODECS)) {
        LM_ERR("required functionality is not "
          "supported by the version of the RTPproxy running on the selected "
          "node.  Please upgrade the RTPproxy and try again.\n");
        goto end;
    }
    send_rtpp_command(node, &vstream, nitems);

	ret = 1;
end:
	if (nh_lock) {
		lock_stop_read( nh_lock );
	}
    return ret;
}

static int
rtpproxy_stream4_f(struct sip_msg *msg, str *pname, int count,
    nh_set_param_t *setid, pv_spec_t *var,  int stream2uac)
{
    return rtpproxy_stream(msg, pname, count, setid, var, stream2uac);
}

int
rtpproxy_stream2uac4_f(struct sip_msg* msg, str *pname, int *count,
                nh_set_param_t *setid, pv_spec_t *var)
{

    return rtpproxy_stream4_f(msg, pname, *count, setid, var, 1);
}

int
rtpproxy_stream2uas4_f(struct sip_msg* msg, str *pname, int *count,
                nh_set_param_t *setid, pv_spec_t *var)
{

    return rtpproxy_stream4_f(msg, pname, *count, setid, var, 0);
}


static int
rtpproxy_stop_stream(struct sip_msg* msg, nh_set_param_t *setid, pv_spec_t *var,
                int stream2uac)
{
    int nitems, ret = -1;
    str callid, from_tag, to_tag;
    struct rtpp_node *node;
    struct rtpp_set *set;
    struct rtpproxy_vcmd vststrm;

    RTPP_VCMD_INIT(vststrm, 8,
        {"S",         1}, /*.vu[0] */
        {" ",         1},
        {NULL,        0}, /*.vu[2] callid */
        {" ",         1},
        {NULL,        0}, /*.vu[4] from tag */
        {";1 ",       3},
        {NULL,        0}, /*.vu[6] to tag */
        {";1",        2}
    );

    if (get_callid(msg, &callid) == -1 || callid.len == 0) {
        LM_ERR("can't get Call-Id field\n");
        return -1;
    }
    if (get_to_tag(msg, &to_tag) == -1) {
        LM_ERR("can't get To tag\n");
        return -1;
    }
    if (get_from_tag(msg, &from_tag) == -1 || from_tag.len == 0) {
        LM_ERR("can't get From tag\n");
        return -1;
    }
    STR2IOVEC(callid, vststrm.vu[2]);
    nitems = vststrm.useritems;
    if (stream2uac == 0) {
        if (to_tag.len == 0)
            return -1;
        STR2IOVEC(to_tag, vststrm.vu[4]);
        STR2IOVEC(from_tag, vststrm.vu[6]);
    } else {
        STR2IOVEC(from_tag, vststrm.vu[4]);
        STR2IOVEC(to_tag, vststrm.vu[6]);
        if (to_tag.len <= 0)
            nitems -= 2;
    }

	if (nh_lock) {
		lock_start_read( nh_lock );
	}

    
	set = get_rtpp_set(setid);
	if (!set) {
		LM_ERR("no set found\n");
		goto end;
	}

	node = select_rtpp_node(msg, callid, set, var, 1);
    if (!node) {
        LM_ERR("no available proxies\n");
        goto end;
    }
    if (!HAS_CAP(node, CODECS)) {
        LM_ERR("required functionality is not "
          "supported by the version of the RTPproxy running on the selected "
          "node.  Please upgrade the RTPproxy and try again.\n");
        goto end;
    }
    send_rtpp_command(node, &vststrm, nitems);

	ret = 1;
end:
	if (nh_lock) {
		lock_stop_read( nh_lock );
	}
    return ret;
}

int
rtpproxy_stop_stream2uac2_f(struct sip_msg* msg, nh_set_param_t *setid, pv_spec_t *var)
{

    return rtpproxy_stop_stream(msg, setid, var, 1);
}

int
rtpproxy_stop_stream2uas2_f(struct sip_msg* msg, nh_set_param_t *setid, pv_spec_t *var)
{

    return rtpproxy_stop_stream(msg, setid, var, 0);
}
