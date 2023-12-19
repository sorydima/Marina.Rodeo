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
 * mib2c.array-user.conf,
 *
 * This file implements the openserSIPRegUserLookupTable.  For a full
 * description of the table, please see the OPENSER-SIP-SERVER-MIB.
 *
 * This file consists of many more functions than the other header files.
 * This is because this table is writable, bringing a lot of SNMP overhead.
 *
 * Most of the contents are auto-generated (aside from white space and comment
 * changes), and can be ignored.  The functions that have been modified are:
 *
 * 1) openserSIPRegUserLookupTable_extract_index()
 *
 * 2) openserSIPRegUserLookupTable_can_[activate|deactivate|delete]()
 *
 * 3) openserSIPRegUserLookupTable_set_reserve1()
 *
 * 4) openserSIPRegUserLookupTable_set_action()
 *
 * Full details can be found in openserSIPRegUserLookupTable.c.  You can safely
 * ignore the other functions.
 */

#ifndef OPENSERSIPREGUSERLOOKUPTABLE_H
#define OPENSERSIPREGUSERLOOKUPTABLE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include "../../config.h"


/* This structure represnts a row in the table */
typedef struct openserSIPRegUserLookupTable_context_s
{
	netsnmp_index index;

	/** UNSIGNED32 = ASN_UNSIGNED */
	unsigned long  openserSIPRegUserLookupIndex;

	/** SnmpAdminString = ASN_OCTET_STR */
	unsigned char *openserSIPRegUserLookupURI;
	long           openserSIPRegUserLookupURI_len;

	/** UNSIGNED32 = ASN_UNSIGNED */
	unsigned long  openserSIPRegUserIndex;

	/** RowStatus = ASN_INTEGER */
	long openserSIPRegUserLookupRowStatus;

	void * data;

} openserSIPRegUserLookupTable_context;

/*
 * Initializes the openserSIPRegUserLookupTable table.  This step is easier
 * than in the other tables because there is no table population.  All table
 * population takes place during run time.
 */
void init_openserSIPRegUserLookupTable(void);


/*
 * Initialize the openserSIPRegUserLookupTable table by defining how it is
 * structured.
 *
 * This function is mostly auto-generated.
 */
void initialize_table_openserSIPRegUserLookupTable(void);

/*
 * This function was auto-generated and didn't need modifications from its
 * auto-generation.  It is called to handle an SNMP GET request.
 */
int openserSIPRegUserLookupTable_get_value(netsnmp_request_info *,
		netsnmp_index *, netsnmp_table_request_info *);

const openserSIPRegUserLookupTable_context *
	openserSIPRegUserLookupTable_get_by_idx(netsnmp_index *);

const openserSIPRegUserLookupTable_context *
	openserSIPRegUserLookupTable_get_by_idx_rs(
			netsnmp_index *,
			int row_status);

/* oid declarations */
extern oid    openserSIPRegUserLookupTable_oid[];
extern size_t openserSIPRegUserLookupTable_oid_len;


#define openserSIPRegUserLookupTable_TABLE_OID OPENSER_OID,3,1,2,1,5,9


/* column number definitions for table openserSIPRegUserLookupTable */
#define COLUMN_OPENSERSIPREGUSERLOOKUPINDEX     1
#define COLUMN_OPENSERSIPREGUSERLOOKUPURI       2
#define COLUMN_OPENSERSIPREGUSERINDEX           3
#define COLUMN_OPENSERSIPREGUSERLOOKUPROWSTATUS 4

#define openserSIPRegUserLookupTable_COL_MIN 2
#define openserSIPRegUserLookupTable_COL_MAX 4


/* Handles index extraction for row creation */
int openserSIPRegUserLookupTable_extract_index(
		openserSIPRegUserLookupTable_context *ctx, netsnmp_index *hdr);

/* Handle RESERVE1 and RESERVE2 phases of an SNMP SET */
void openserSIPRegUserLookupTable_set_reserve1(netsnmp_request_group *);
void openserSIPRegUserLookupTable_set_reserve2(netsnmp_request_group *);

/* Handle the SET and ACTION phases of an SNMP SET */
void openserSIPRegUserLookupTable_set_action(netsnmp_request_group *);
void openserSIPRegUserLookupTable_set_commit(netsnmp_request_group *);

/* Handle Resource cleanup if the ACTION or RESERVE1/RESERVE2 phases of an
 * SNMPSET fail */
void openserSIPRegUserLookupTable_set_free(netsnmp_request_group *);
void openserSIPRegUserLookupTable_set_undo(netsnmp_request_group *);

openserSIPRegUserLookupTable_context *
	openserSIPRegUserLookupTable_duplicate_row(
			openserSIPRegUserLookupTable_context*);

netsnmp_index * openserSIPRegUserLookupTable_delete_row(
		openserSIPRegUserLookupTable_context*);

/* Used to check if there is a reason why a row can't be activated
 * (There is no reason in our implementation)
 */
int openserSIPRegUserLookupTable_can_activate(
		openserSIPRegUserLookupTable_context *undo_ctx,
		openserSIPRegUserLookupTable_context *row_ctx,
		netsnmp_request_group * rg);

/* Used to check if there is a reason why a row can't be deactivated
 * (There is no reason in our implementation)
 */
int openserSIPRegUserLookupTable_can_deactivate(
		openserSIPRegUserLookupTable_context *undo_ctx,
		openserSIPRegUserLookupTable_context *row_ctx,
		netsnmp_request_group * rg);

/* Used to check if there is a reason why a row can't be deleted
 * (There is no reason in our implementation)
 */
int openserSIPRegUserLookupTable_can_delete(
		openserSIPRegUserLookupTable_context *undo_ctx,
		openserSIPRegUserLookupTable_context *row_ctx,
		netsnmp_request_group * rg);

/* Basic structural setups of the new row */
openserSIPRegUserLookupTable_context * openserSIPRegUserLookupTable_create_row(
		netsnmp_index*);


#ifdef __cplusplus
}
#endif

#endif /** OPENSERSIPREGUSERLOOKUPTABLE_H */
