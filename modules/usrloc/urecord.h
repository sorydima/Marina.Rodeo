/*
 * Usrloc record structure
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2003 FhG Fokus
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
 * History:
 * ---------
 */

/*! \file
 *  \brief USRLOC - Usrloc record structure
 *  \ingroup usrloc
 */


#ifndef URECORD_H
#define URECORD_H

#include <stdio.h>
#include <time.h>

#include "../../map.h"
#include "../../str.h"
#include "../../qvalue.h"
#include "../../str_list.h"
#include "../../db/db_insertq.h"

#include "ucontact.h"
#include "hslot.h"


struct hslot;

/*! \brief
 * Basic hash table element
 */
typedef struct urecord {
	str* domain;                   /*!< Pointer to domain we belong to
                                    * ( null terminated string) */
	str aor;                       /*!< Address of record */
	unsigned int aorhash;          /*!< Hash over address of record */
	unsigned int label;            /*!< Labels over AVL tree */
	unsigned short next_clabel;    /*!< Labels to be assigned to contacts */
	ucontact_t* contacts;          /*!< One or more contact fields */
	ucontact_t* remote_aors;       /*!< AoRs present in remote POPs */

	struct hslot* slot;            /*!< Collision slot in the hash table
                                    * array we belong to */

	int no_clear_ref;              /*!< Keep the record while positive */
	int is_static;

	map_t kv_storage;              /*!< data attached by API subscribers >*/
} urecord_t;


/* Create a new record */
int new_urecord(str* _dom, str* _aor, urecord_t** _r);


/* Free all memory associated with the element */
void free_urecord(urecord_t* _r);

/*
 * Add a new contact
 */
ucontact_t* mem_insert_ucontact(urecord_t* _r, str* _c, ucontact_info_t* _ci);


/*
 * Remove the contact from lists
 */
void mem_remove_ucontact(urecord_t* _r, ucontact_t* _c);


/*
 * Remove contact from the list and delete
 */
void mem_delete_ucontact(urecord_t* _r, ucontact_t* _c);


/*
 * Timer handler
 */
int timer_urecord(urecord_t* _r,query_list_t **ins_list);


/*
 * Delete the whole record from database
 */
int db_delete_urecord(urecord_t* _r);


/*
 * Delete the whole record from the cache database
 */
int cdb_delete_urecord(urecord_t* _r);

/* ===== Module interface ======== */


/*
 * Release urecord previously obtained
 * through get_urecord
 */
void release_urecord(urecord_t* _r, char skip_replication);


/*
 * Insert new contact
 */
int insert_ucontact(urecord_t* _r, str* _contact, ucontact_info_t* _ci,
        const struct ct_match *match, char skip_replication, ucontact_t** _c);


/*
 * Delete ucontact from urecord
 */
int delete_ucontact(urecord_t* _r, struct ucontact* _c,
        const struct ct_match *match, char skip_replication);


/*
 * Get pointer to ucontact with given contact
 */
int get_ucontact(urecord_t* _r, str* _c, str* _callid, int _cseq,
        const struct ct_match *match, struct ucontact** _co);
int get_simple_ucontact(urecord_t* _r, str* _c, struct ucontact** _co);


/*! \brief
 * Returns the next contact_id key for the given record and advances
 * the internal counter
 */
uint64_t next_contact_id(urecord_t* _r);

/*
 * Prepares the K/V store of an urecord_t to be persisted to DB by serializing
 * it and storing it in one of the contact's K/V store using an internal key
 * ("urec_store_key").
 */
int persist_urecord_kv_store(urecord_t* _r);
/*
 * Attempts to set the K/V store of an urecord_t using the contact's K/V store
 * data under the "urec_store_key" key.
 */
void restore_urecord_kv_store(urecord_t *_r, ucontact_t *_c);

/*! \brief
 * Fetch a key from the record-level storage
 * NOTE: assumes the corresponding udomain lock is properly acquired
 *
 * Returns: NULL on error/key not found, value pointer otherwise
 */
int_str_t *get_urecord_key(urecord_t* _rec, const str* _key);

/*! \brief
 * Create or re-assign a key-value pair within record-level storage.
 *   ("_key" and "_val" will be fully duplicated in shared memory)
 *
 * NOTE: assumes the corresponding udomain lock is properly acquired
 *
 * Returns: NULL on error, new value pointer otherwise
 */
int_str_t *put_urecord_key(urecord_t* _rec, const str* _key,
                           const int_str_t* _val);

#endif /* URECORD_H */
