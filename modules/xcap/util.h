/*
 * xcap module - XCAP operations module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2012 AG Projects
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

#ifndef XCAP_UTIL_H
#define XCAP_UTIL_H

#include "../../str.h"
#include "../../ut.h"
#include "doc.h"


#define STR_MATCH(s1, s2)   ((s1)->len==(s2)->len && memcmp((s1)->s, (s2)->s, (s1)->len)==0)

static inline int xcap_doc_type(const str *auid)
{
	static str pres_rules = str_init("pres-rules");
	static str oma_pres_rules = str_init("org.openmobilealliance.pres-rules");
	static str rls_services = str_init("rls-services");
	static str pidf_manipulation = str_init("pidf-manipulation");
	static str resource_list = str_init("resource-list");

	if (STR_MATCH(auid, &pres_rules))
		return PRES_RULES;
	else if (STR_MATCH(auid, &rls_services))
		return RLS_SERVICES;
	else if (STR_MATCH(auid, &resource_list))
		return RESOURCE_LISTS;
	else if (STR_MATCH(auid, &pidf_manipulation))
		return PIDF_MANIPULATION;
	else if (STR_MATCH(auid, &oma_pres_rules))
		return OMA_PRES_RULES;
	return -1;
}

#undef STR_MATCH


#endif

