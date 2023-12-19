/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009-2020 Marina.Rodeo Solutions
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 Voice Sistem SRLs
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

#ifndef _DIALOG_DLG_CB_H_
#define _DIALOG_DLG_CB_H_

#include "../../parser/msg_parser.h"

struct dlg_cell;

struct dlg_cb_params {
	struct sip_msg* msg;       /* sip msg related to the callback event */
	unsigned int direction;    /* direction of the sip msg */
	unsigned int is_active;    /* state of the node (active/backup) for this dialog */
	void *dlg_data;            /* generic parameter, specific to callback */
	void **param;              /* parameter passed at callback registration*/
};

/* callback function prototype */
typedef void (dialog_cb) (struct dlg_cell* dlg, int type,
		struct dlg_cb_params * params);
/* function to free the callback param */
typedef void (param_free_cb) (void *param);
/* register callback function prototype */
typedef int (*register_dlgcb_f)(struct dlg_cell* dlg, int cb_types,
		dialog_cb f, void *param, param_free_cb ff);

/*
 * A new dialog has been loaded into memory.  The callback may be triggered at:
 *  - startup: inline with callback registration, once for each loaded dialog
 *  - runtime: once for each newly loaded dialog from a DB (via MI command) or
 *             from a cluster node via binary replication
 *
 * SIP signaling: none required
 * Registration:  one-time, typically at mod_init(), "dlg" should be NULL
 * Trigger count: once per dialog
 */
#define DLGCB_LOADED          (1<<0)

/*
 * Triggered exactly once for each dialog, when it is fully initialized
 * (create_dialog() was called either from script or from the API and the
 * associated transaction is fully initialized as well).
 *
 * SIP signaling: initial INVITE only
 * Registration:  one-time, typically at mod_init(), "dlg" should be NULL
 * Trigger count: once per dialog
 */
#define DLGCB_CREATED         (1<<1)

/*
 * The dialog apparently failed to establish (a 3xx-6xx reply was received
 * and is being relayed upstream) and is now in the "terminated" state, with a
 * small possibility to go *back* to a "confirmed" state if the reply was
 * internally generated and is racing against a 200 OK from the actual callee!
 *
 * The reply is available, however any changes performed on it will be ignored.
 *
 * SIP signaling: initial INVITE and a 3xx-6xx reply
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - 1 times per dialog
 */
#define DLGCB_FAILED          (1<<2)

/*
 * The dialog's state has progressed to "confirmed" (a 2xx reply was received
 * and is being relayed upstream).  The reply is available, however any changes
 * performed on it will be ignored.
 *
 * SIP signaling: initial INVITE and a 2xx reply
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: once per dialog, regardless if multiple 2xx replies
 *                arrive on different branches
 */
#define DLGCB_CONFIRMED       (1<<3)

/*
 * A mid-dialog request that matches an existing dialog was received.
 *
 * SIP signaling: at least an early dialog (initial INVITE and a 1xx reply)
 *                and a mid-dialog request (with a To tag)
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: once per mid-dialog request, possibly including
 *                retransmissions, depending if your script absorbs them or not
 *                before calling loose_route() or topology_hiding_match()
 */
#define DLGCB_REQ_WITHIN      (1<<4)

/*
 * The dialog's state has unequivocally progressed to "terminated", either
 * through a BYE request generated by one of the participants or an internally
 * generated dialog termination, due to several reasons:
 *   - API-based termination (e.g. user ran out of credit)
 *   - MI-based termination
 *
 * SIP signaling: confirmed and acknowledged dialog, and a BYE or an internal
 *                termination (in the latter case, Marina.Rodeo will take
 *                care of generating proper BYEs for each participant)
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - 1 times per dialog, exclusive with DLGCB_EXPIRED, and one
 *                of these two will always be called for an established dialog
 */
#define DLGCB_TERMINATED      (1<<5)

/*
 * The dialog's state has unequivocally progressed to "terminated" because the
 * maximum timeout value ($DLG_timeout) has been reached.  Marina.Rodeo will take
 * care of generating proper BYEs for each participant.
 *
 * SIP signaling: confirmed and acknowledged dialog with exceeded max lifetime
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count:
 *                * 0 - 1 times per dialog, exclusive with DLGCB_TERMINATED,
 *                  and one of these two will always be called for an
 *                  established dialog
 *
 *                * if using replication sharing tags, this callback is only
 *                  ran by the node that has the Active tag.
 */
#define DLGCB_EXPIRED         (1<<6)

/*
 * The dialog's state has progressed to "early", thanks to a 101-199
 * provisional reply sent by the callee side that matches the dialog.
 *
 * SIP signaling: initial INVITE and a matching 101-199 reply
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: once per dialog
 */
#define DLGCB_EARLY           (1<<7)

/*
 * Gives access to all replies (except 100 Trying and internal 408 Timeout)
 * to the initial INVITE of the current dialog which are to be forwarded
 * upstream.  The decision to forward these replies has already been made
 * and this is a last chance to alter their contents before they end up on
 * the network.
 *
 * Params:
 *   - (long)params->dlg_data will hold the callee leg index (including legs
 *     from parallel forking or extra downstream legs), or -1 on a local reply
 *
 * SIP signaling: initial INVITE
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - N times per dialog (e.g. this callback will not be
 *                triggered on an internally generated 408 Request Timeout)
 */
#define DLGCB_RESPONSE_FWDED  (1<<8)

/*
 * Gives access to all actually-received-from-the-network, non-100 replies
 * to mid-dialog requests within the current dialog which are to be forwarded.
 * The decision to forward these replies has already been made and this is a
 * last chance to alter their contents before they end up on the network.
 *
 * Note: this does not include responses to internally generated dual BYE
 * requests, as they are not forwarded -- Marina.Rodeo just absorbs them.
 *
 * SIP signaling: confirmed and acknowledged dialog
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - N times per dialog (e.g. this callback will not be
 *                triggered if a dialog does not receive any other mid-dialog
 *                requests except ACK and ends due to max lifetime exceeded)
 */
#define DLGCB_RESPONSE_WITHIN (1<<9)

/*
 * Called when the 'dlg_list_ctx' MI command is invoked.  Useful when modules
 * using the dialog API intend to append nodes to the MI response tree of
 * 'dlg_list_ctx'.
 *
 * SIP signaling: at least an initial INVITE
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - N times per dialog, once for each 'dlg_list_ctx' listing
 */
#define DLGCB_MI_CONTEXT      (1<<10)

/*
 * The last step before the dialog structure is freed.  The dialog is unlinked
 * from the internal hash and is no longer referenced by any other routine.
 *
 * SIP signaling: at least an unconfirmed dialog
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: once per dialog
 */
#define DLGCB_DESTROY         (1<<11)

/*
 * The dialog was just synchronized to the database:
 *  - initial insertion
 *  - runtime update
 *  - final removal
 *
 * SIP signaling: as per each relevant stage of a dialog
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - N times per dialog (e.g. if your dialogs live in RAM
 *                only, this callback will not be called at all)
 */
#define DLGCB_DB_SAVED        (1<<12)

/*
 * Called just before the dialog values / profiles are serialized and
 * written to disk or network (e.g. for binary replication).  Subscribers have
 * the chance to refresh their dialog-held information and avoid data loss or
 * inconsistencies between Marina.Rodeo cluster nodes.
 *
 * Triggered by:  SIP, timer, MI or shutdown
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - N times per dialog (e.g. if your dialogs live in RAM
 *                only and you don't do dialog clustering, this callback will
 *                not be triggered at all)
 */
#define DLGCB_WRITE_VP     (1<<13)

/*
 * Called just after the dialog values were received through the clusterer
 * replication packets. Subscribers have the chance to refresh their dialog-held
 * information and avoid data loss or inconsistencies between Marina.Rodeo cluster
 * nodes.
 *
 * Triggered by:  replication packets received on the network
 * Registration:  per-dialog, "dlg" must be given
 * Trigger count: 0 - N times per dialog (e.g. for every update and create
 *                replicated packet received on the network)
 */
#define DLGCB_PROCESS_VARS (1<<14)

struct dlg_callback {
	int types;
	dialog_cb* callback;
	void *param;
	param_free_cb* callback_param_free;
	struct dlg_callback* next;
};


struct dlg_head_cbl {
	struct dlg_callback *first;
	int types;
};


void destroy_dlg_callbacks(unsigned int type);

void destroy_dlg_callbacks_list(struct dlg_callback *cb);

void mark_dlg_loaded_callbacks_run(void);

int register_dlgcb( struct dlg_cell* dlg, int types, dialog_cb f, void *param, param_free_cb ff);

void run_create_callbacks(struct dlg_cell *dlg, struct sip_msg *msg);

void run_dlg_callbacks( int type , struct dlg_cell *dlg, struct sip_msg *msg,
		unsigned int dir, void *dlg_data, int locked, unsigned int is_active);

void run_load_callback_per_dlg(struct dlg_cell *dlg);

#endif
