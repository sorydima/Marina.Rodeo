/*
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
 * --------
 *  2004-03-16  created (bogdan)
 */

/*! \file
 *  \brief USRLOC - Module callbacks
 *  \ingroup usrloc
 */

#ifndef _UL_CALLBACKS_H
#define _UL_CALLBACKS_H

#include "ucontact.h"
#include "urecord.h"
#include "../../lib/list.h"

typedef enum ul_cb_types {
	UL_CONTACT_INSERT     = (1<<0),
	UL_CONTACT_UPDATE     = (1<<1),
	UL_CONTACT_DELETE     = (1<<2), /* exclusive with EXPIRE */
	UL_CONTACT_EXPIRE     = (1<<3), /* exclusive with DELETE */
	UL_AOR_INSERT         = (1<<4),
	UL_AOR_UPDATE         = (1<<5),
	UL_AOR_DELETE         = (1<<6), /* exclusive with EXPIRE */
	UL_AOR_EXPIRE         = (1<<7), /* exclusive with DELETE */
	ULCB_MAX              = ((1<<8)-1),
} ul_cb_type;

typedef union ul_cb_extra {
	struct {
		unsigned short prev_proto;
		unsigned short prev_port;
		str prev_name;
	} contact_update;
} ul_cb_extra;


#define is_contact_cb(type) \
	(type & \
	(UL_CONTACT_INSERT|UL_CONTACT_UPDATE|UL_CONTACT_DELETE|UL_CONTACT_EXPIRE))

#define is_aor_cb(type) \
	(type & \
	(UL_AOR_INSERT|UL_AOR_UPDATE|UL_AOR_DELETE|UL_AOR_EXPIRE))

/*! \brief callback function prototype
 *
 * @binding: depending on the registered type,
 *             it should be casted to either (ucontact_t *) or (urecord_t *)
 * @type:    type of the callback
 * @extra:   extra parameters provided for each type of callback
 */
typedef void (ul_cb) (void *binding, ul_cb_type type, ul_cb_extra *extra);


struct ul_callback {
	int id;                    /*!< id of this callback - useless */
	ul_cb_type types;          /*!< types of events that trigger the callback*/
	ul_cb *callback;           /*!< callback function */

	struct list_head list;
};

struct ulcb_head_list {
	struct list_head first;
	ul_cb_type reg_types;
};


extern struct ulcb_head_list*  ulcb_list;


#define exists_ulcb_type(_types_) \
	( (ulcb_list->reg_types)&(_types_) )


int ul_init_cbs();

void destroy_ulcb_list();


/*! \brief register a callback for several types of events
 *
 * @types:       mask of callback types
 * @f:           registered function
 */
int register_ulcb(ul_cb_type types, ul_cb f);

/*! \brief run all transaction callbacks for an event type
 *
 * @type: the callback type
 * @binding: value to be passed to the callback
 *    - an (ucontact_t *) for contact callbacks
 *    - an (urecord_t *) for AoR callbacks
 */
static inline void run_ul_callbacks(ul_cb_type type, void *binding, ul_cb_extra *extra)
{
	struct list_head *_;
	struct ul_callback *cbp;

	list_for_each(_, &ulcb_list->first) {
		cbp = list_entry(_, struct ul_callback, list);
		if (cbp->types & type) {
			LM_DBG("contact=%p, callback type %d/%d, id %d entered\n",
			       binding, type, cbp->types, cbp->id);

			if (is_contact_cb(type)) {
				cbp->callback(binding, type, extra);
			} else if (is_aor_cb(type)) {
				cbp->callback(binding, type, extra);
			}
		}
	}
}

#endif
