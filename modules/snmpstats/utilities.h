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
 *
 * This file was created to group together utility functions that were useful
 * throughout the SNMPStats module, without belonging to any file in particular.
 */

#ifndef _SNMP_UTILITIES_
#define _SNMP_UTILITIES_

#include <time.h>

#include "../../str.h"
#include "../../sr_module.h"

/* Performs sanity checks on the parameters passed to a string configuration
 * file parameter handler. */
int stringHandlerSanityCheck( modparam_t type, void *val, char *parameterName);

/*
 * This function is a wrapper around the standard statistic framework.  It will
 * return the value of the statistic denoted with statName, or zero if the
 * statistic was not found.
 */
int get_statistic(char *statName);

/* Returns a pointer to an SNMP DateAndTime OCTET STRING representation of the
 * time structure.  Note that the pointer is to static data, so it shouldn't be
 * counted on to be around if this function is called again. */
char * convertTMToSNMPDateAndTime(struct tm *timeStructure);

#endif
