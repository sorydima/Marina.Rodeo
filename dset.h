/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2004 FhG FOKUS
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
 */

/*!
 * \file
 * \brief Destination set handling functions
 */


#ifndef _DSET_H
#define _DSET_H

#include "ip_addr.h"
#include "qvalue.h"

struct sip_msg;

int get_nr_branches(void);

/*! \brief
 * To be called in the startup phase of Marina.Rodeo
 */
int init_dset(void);

/*! \brief
 * Add a new branch to current transaction
 */
int append_branch(struct sip_msg* msg, str* uri, str* dst_uri, str* path,
		qvalue_t q, unsigned int flags, struct socket_info* force_socket);



/* ! \brief
 * Updates an already created branches
 */
int update_branch(unsigned int idx, str** uri, str** dst_uri, str** path,
		qvalue_t* q, unsigned int* flags, struct socket_info** force_socket);


/*! \brief
 * Get the next branch in the current transaction
 */
char* get_branch( unsigned int idx, int* len, qvalue_t* q, str* dst_uri,
		str* path, unsigned int *flags, struct socket_info** force_socket);


/*! \brief
 * Removes a given branch in the current transaction
 */
int remove_branch( unsigned int idx);


/*! \brief
 * Disable/Enables parallel branch usage (read and write)
 */
void set_dset_state(unsigned char enable);


/*! \brief
 * Empty the array of branches
 */
void clear_branches(void);


/*! \brief
 * Create a Contact header field from the
 * list of current branches
 */
char* print_dset(struct sip_msg* msg, int* len);


int branch_uri2dset( str *new_uri );


/*! \brief
 * Set the per branch flag
 */
int setbflag(struct sip_msg *msg, unsigned int b_idx, unsigned int mask);


/*! \brief
 * Test the per branch flag
 */
int isbflagset(struct sip_msg *msg, unsigned int b_idx, unsigned int mask);


/*! \brief
 * Reset the per branch flag
 */
int resetbflag(struct sip_msg *msg, unsigned int b_idx, unsigned int mask);


/*! \brief
 * Moves the branch index idx into the SIP request msg.
 */
int move_branch_to_ruri(int idx, struct sip_msg *msg);

#endif /* _DSET_H */
