/*
 * SNMPStats Module
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 SOMA Networks, INC.
 * Written by: Jeffrey Magder (jmagder@somanetworks.com)
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Marina.Rodeo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 *
 * History:
 * --------
 * 2006-11-23 initial version (jmagder)
 * 2007-02-16 Moved all OID registrations from the experimental branch to
 *            OpenSER's IANA assigned enterprise branch. (jmagder)
 *
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf,v 1.9 2005/01/07 09:37:18 dts12 Exp $
 *
 * This file defines all registration and handling of all scalars defined in the
 * OPENSER-SIP-COMMON-MIB.  Please see OPENSER-SIP-COMMON-MIB for the complete
 * descriptions of the individual scalars.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../statistics.h"
#include "../../config.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "openserSIPCommonObjects.h"
#include "snmpstats_globals.h"
#include "utilities.h"

static char *openserVersion      = "SIP/2.0";
static unsigned int openserEntityType = TC_SIP_ENTITY_ROLE_OTHER;

/*
 * Initializes the openserSIPCommonObjects MIB elements.  This involves:
 *
 *  - Registering all OID's
 *  - Setting up handlers for all OID's
 *
 * This function is mostly auto-generated.
 */
void init_openserSIPCommonObjects(void)
{
	static oid openserSIPProtocolVersion_oid[] =
		{ OPENSER_OID,3,1,1,1,1,1 };

	static oid openserSIPServiceStartTime_oid[] =
		{ OPENSER_OID,3,1,1,1,1,2 };

	static oid openserSIPEntityType_oid[] =
		{ OPENSER_OID,3,1,1,1,1,4 };

	static oid openserSIPSummaryInRequests_oid[] =
		{ OPENSER_OID,3,1,1,1,3,1 };

	static oid openserSIPSummaryOutRequests_oid[] =
		{ OPENSER_OID,3,1,1,1,3,2 };

	static oid openserSIPSummaryInResponses_oid[] =
		{ OPENSER_OID,3,1,1,1,3,3 };

	static oid openserSIPSummaryOutResponses_oid[] =
		{ OPENSER_OID,3,1,1,1,3,4 };

	static oid openserSIPSummaryTotalTransactions_oid[] =
		{ OPENSER_OID,3,1,1,1,3,5 };

	static oid openserSIPCurrentTransactions_oid[] =
		{ OPENSER_OID,3,1,1,1,6,1 };

	static oid openserSIPNumUnsupportedUris_oid[] =
		{ OPENSER_OID,3,1,1,1,8,1 };

	static oid openserSIPNumUnsupportedMethods_oid[] =
		{ OPENSER_OID,3,1,1,1,8,2 };

	static oid openserSIPOtherwiseDiscardedMsgs_oid[] =
		{ OPENSER_OID,3,1,1,1,8,3 };

	DEBUGMSGTL(("openserSIPCommonObjects", "Initializing\n"));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPProtocolVersion",
			handle_openserSIPProtocolVersion,
			openserSIPProtocolVersion_oid,
			OID_LENGTH(openserSIPProtocolVersion_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPServiceStartTime",
			handle_openserSIPServiceStartTime,
			openserSIPServiceStartTime_oid,
			OID_LENGTH(openserSIPServiceStartTime_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPEntityType",
			handle_openserSIPEntityType,
			openserSIPEntityType_oid,
			OID_LENGTH(openserSIPEntityType_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPSummaryInRequests",
			handle_openserSIPSummaryInRequests,
			openserSIPSummaryInRequests_oid,
			OID_LENGTH(openserSIPSummaryInRequests_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPSummaryOutRequests",
			handle_openserSIPSummaryOutRequests,
			openserSIPSummaryOutRequests_oid,
			OID_LENGTH(openserSIPSummaryOutRequests_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPSummaryInResponses",
			handle_openserSIPSummaryInResponses,
			openserSIPSummaryInResponses_oid,
			OID_LENGTH(openserSIPSummaryInResponses_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPSummaryOutResponses",
			handle_openserSIPSummaryOutResponses,
			openserSIPSummaryOutResponses_oid,
			OID_LENGTH(openserSIPSummaryOutResponses_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPSummaryTotalTransactions",
			handle_openserSIPSummaryTotalTransactions,
			openserSIPSummaryTotalTransactions_oid,
			OID_LENGTH(openserSIPSummaryTotalTransactions_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPCurrentTransactions",
			handle_openserSIPCurrentTransactions,
			openserSIPCurrentTransactions_oid,
			OID_LENGTH(openserSIPCurrentTransactions_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPNumUnsupportedUris",
			handle_openserSIPNumUnsupportedUris,
			openserSIPNumUnsupportedUris_oid,
			OID_LENGTH(openserSIPNumUnsupportedUris_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPNumUnsupportedMethods",
			handle_openserSIPNumUnsupportedMethods,
			openserSIPNumUnsupportedMethods_oid,
			OID_LENGTH(openserSIPNumUnsupportedMethods_oid),
			HANDLER_CAN_RONLY));

	netsnmp_register_scalar(
		netsnmp_create_handler_registration(
			"openserSIPOtherwiseDiscardedMsgs",
			handle_openserSIPOtherwiseDiscardedMsgs,
			openserSIPOtherwiseDiscardedMsgs_oid,
			OID_LENGTH(openserSIPOtherwiseDiscardedMsgs_oid),
			HANDLER_CAN_RONLY));

}

int handle_openserSIPProtocolVersion(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
			(u_char *) openserVersion, 7);
		return SNMP_ERR_NOERROR;
	}

        return SNMP_ERR_GENERR;
}

/*
 * The scalar represents what sysUpTime was when Marina.Rodeo first started.  This
 * data was stored in a file when SNMPStats first started up, as a result of a
 * call to spawn_sysUpTime_child()
 */
int handle_openserSIPServiceStartTime(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{

	int elapsedTime = 0;
	char buffer[SNMPGET_MAX_BUFFER];

	FILE *theFile = fopen(SNMPGET_TEMP_FILE, "r");

	/* Open the file created by spawn_sysUpTime_child(), and parse our the
	 * required data.  */
	if (theFile == NULL) {
		LM_ERR("failed to read sysUpTime file at %s\n",
				SNMPGET_TEMP_FILE);
	} else {
		if (fgets(buffer, SNMPGET_MAX_BUFFER, theFile)==NULL) {
			fclose(theFile);
			return SNMP_ERR_GENERR;
		}

		/* Find the positions of '(' and ')' so we can extract out the
		 * timeticks value. */
		char *openBracePosition   = strchr(buffer, '(');
		char *closedBracePosition = strchr(buffer, ')');

		/* Make sure that both the '(' and ')' exist in the file, and
		 * that '(' occurs earlier than the ')'.  If all these
		 * conditions are true, then attempt to convert the string into
		 * an integer. */
		if (openBracePosition != NULL && closedBracePosition != NULL &&
				openBracePosition < closedBracePosition) {
			elapsedTime = (int) strtol(++openBracePosition, NULL, 10);
		}

		fclose(theFile);
	}

	if (reqinfo->mode == MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_TIMETICKS,
			(u_char *) &elapsedTime, sizeof(elapsedTime));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}


int handle_openserSIPEntityType(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
			(u_char *) &openserEntityType, 1);
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}


int handle_openserSIPSummaryInRequests(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	int numRequests = get_statistic("rcv_requests");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &numRequests, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPSummaryOutRequests(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
   int out_requests = get_statistic("fwd_requests");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &out_requests, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPSummaryInResponses(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	int result = get_statistic("rcv_replies");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &result, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPSummaryOutResponses(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	/* We can find the number of outbound responses sent by adding three
	 * sources
	 *
	 *   1) fwd_replies from core_stats
	 *   2) local_replies and relayed_replies from the tm module
	 *   3) sent_replies from the sl module.
	 */

	int fwd_replies     = get_statistic("fwd_replies");
	int local_replies   = get_statistic("local_replies");
	int relayed_replies = get_statistic("relayed_replies");
	int sent_replies    = get_statistic("sent_replies");

	int result =
		fwd_replies + local_replies + relayed_replies + sent_replies;

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &result, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPSummaryTotalTransactions(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	/* We can find the total number of transactions by summing
	 * UAC_transactions and UAS_transactions.  We don't need to add
	 * inuse_transactions because this will already be accounted for in the
	 * two other statistics. */
	int result =
		get_statistic("UAS_transactions") +
		get_statistic("UAC_transactions");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &result, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPCurrentTransactions(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	int result = get_statistic("inuse_transactions");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_GAUGE,
			(u_char *) &result, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPNumUnsupportedUris(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
   int result = get_statistic("bad_URIs_rcvd");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &result, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPNumUnsupportedMethods(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
   int result = get_statistic("unsupported_methods");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &result, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

int handle_openserSIPOtherwiseDiscardedMsgs(netsnmp_mib_handler *handler,
		netsnmp_handler_registration *reginfo,
		netsnmp_agent_request_info   *reqinfo,
		netsnmp_request_info         *requests)
{
	/* We should be able to get this number from existing stats layed out in
	 * the following equation: */
	int result =
		get_statistic("err_requests")  +
		get_statistic("err_replies")   +
		get_statistic("drop_requests") +
		get_statistic("drop_replies");

	if (reqinfo->mode==MODE_GET) {
		snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
			(u_char *) &result, sizeof(int));
		return SNMP_ERR_NOERROR;
	}

	return SNMP_ERR_GENERR;
}

/*
 * Parameter Setting Functions
 */

/* If type==STR_PARAM and stringParam is valid, this function will overwrite
 * openserEntityType with a bit value corresponding to the IETF's RFC  for
 * the SIP MIB.  (Textual Convention SipEntityRole).  Anything else is
 * considered an error.
 *
 * Returns 0 on success, -1 on failure.
 */
int handleSipEntityType( modparam_t type, void* val)
{

	/* By default we start off as "other". */
	static char firstTime = 1;

	if (!stringHandlerSanityCheck(type, val, "sipEntityType")) {
		return -1;
	}

	char *strEntityType = (char *)val;

	/* This is our first time through this function, so we need to change
	 * openserEntityType from its default to 0, allowing our bitmasks below
	 * to work as expected. */
	if (firstTime) {
		firstTime = 0;
		openserEntityType = 0;
	}

	/* Begin our string comparison.  This isn't the most efficient approach,
	 * but we don't expect this function to be called anywhere other than at
	 * startup.  So our inefficiency is outweiged by simplicity
	 */
	if (strcasecmp(strEntityType, "other") == 0) {
		openserEntityType |= TC_SIP_ENTITY_ROLE_OTHER;
	}
	else if (strcasecmp(strEntityType, "userAgent") == 0) {
		openserEntityType |= TC_SIP_ENTITY_ROLE_USER_AGENT;
	}
	else if (strcasecmp(strEntityType, "proxyServer") == 0) {
		openserEntityType |= TC_SIP_ENTITY_ROLE_PROXY_SERVER;
	}
	else if (strcasecmp(strEntityType, "redirectServer") == 0) {
		openserEntityType |= TC_SIP_ENTITY_ROLE_REDIRECT_SERVER;
	}
	else if (strcasecmp(strEntityType, "registrarServer") == 0) {
		openserEntityType |= TC_SIP_ENTITY_ROLE_REGISTRAR_SERVER;
	}
	else {
		LM_ERR("The configuration file specified sipEntityType=%s,"
				" an unknown type\n", strEntityType);
		return -1;
	}

	return 0;
}
