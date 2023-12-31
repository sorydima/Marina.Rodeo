/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2007 SOMA Networks, Inc.
 * Written by Ovidiu Sas (osas)
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
 * 2007-07-16 initial version (osas)
 */


#include <stdio.h>  /* for snprintf() */
#include <string.h> /* for memset() */
#include <stdlib.h> /* For atoi() */

#include "../../parser/parser_f.h"
#include "../../parser/sdp/sdp.h"
#include "../../ut.h"
#include "../../dprint.h"
#include "../dialog/dlg_hash.h"

#include "qos_mi.h"
#include "qos_handlers.h"
#include "qos_ctx_helpers.h"

/**
 * The binding to the dialog module functions. Most importantly the
 * register_dlgcb function.
 */
extern struct dlg_binds *dlg_binds;


/**
 * Local function prototypes. See function definition for
 * documentation.
 */
static void setup_dialog_callbacks(struct dlg_cell *did, qos_ctx_t *ctx);

static void qos_dialog_destroy_CB(struct dlg_cell* did, int type, struct dlg_cb_params * params);
static void qos_dialog_request_CB(struct dlg_cell* did, int type, struct dlg_cb_params * params);
static void qos_dialog_response_CB(struct dlg_cell* did, int type,struct dlg_cb_params * params);


/**
 * The value of the message flag to flag an INVITE we want to process
 * through the QoS module.
 */
//static int qos_flag = 0;



/**
 * A helper function to setup all the callbacks from the dialog module
 * after we find intrest in the dialog.
 *
 * @param did The Dialog ID.
 * @param info The qos information.
 *
 */

static void setup_dialog_callbacks(struct dlg_cell *did, qos_ctx_t *ctx)
{
	dlg_binds->register_dlgcb(did, DLGCB_REQ_WITHIN,
			qos_dialog_request_CB, (void *)ctx, NULL);

	dlg_binds->register_dlgcb(did, DLGCB_RESPONSE_FWDED|DLGCB_RESPONSE_WITHIN,
			qos_dialog_response_CB, (void *)ctx, NULL);

	dlg_binds->register_dlgcb(did, DLGCB_DESTROY,
			qos_dialog_destroy_CB, (void *)ctx, NULL);

	dlg_binds->register_dlgcb(did, DLGCB_MI_CONTEXT,
			qos_dialog_mi_context_CB, (void *)ctx, NULL);

	return;
}

/**
 * Every time a new dialog is created (from a new INVITE) the dialog
 * module will call this callback function. We need to track the
 * dialogs lifespan from this point forward until it is terminated
 * with a BYE, CANCEL, etc. In the process, we will see if either or
 * both ends of the conversation are trying to re-negotiate the media.
 *
 * This function will setup the other types of dialog callbacks
 * required to track the lifespan of the dialog.
 *
 *
 * @param did   - The dialog ID
 * @param type  - The trigger event type (CREATED)
 * @param msg   - The SIP message that triggered the callback (INVITE)
 * @param param - The pointer to nothing. As we did not attach
 *                anything to this callback in the dialog module.
 */
void qos_dialog_created_CB(struct dlg_cell *did, int type, struct dlg_cb_params * params)
{
	qos_ctx_t *qos_ctx = NULL;
	struct sip_msg* msg = params->msg;
	unsigned int dir = params->direction, role, other_role;

	if (dir == DLG_DIR_UPSTREAM) {
		role = QOS_CALLEE;
		other_role = QOS_CALLER;
	} else if (dir == DLG_DIR_DOWNSTREAM) {
		role = QOS_CALLER;
		other_role = QOS_CALLEE;
	} else {
		LM_ERR("Unknown dir %d\n", dir);
		return;
	}

	if (msg == NULL || msg == FAKED_REPLY) {
		LM_ERR("Improper msg\n");
		return;
	}

	/* look only at INVITE */
	if (msg->first_line.type != SIP_REQUEST ||
		msg->first_line.u.request.method_value != METHOD_INVITE) {
		LM_WARN("Dialog create callback called with a non-INVITE req.\n");
		return;
	}

	qos_ctx = build_new_qos_ctx();
	if (qos_ctx==NULL) {
		/* Error message printed in build_new_qos_ctx() */
		return;
	}

	LM_DBG("setup_dialog_callbacks( %p , %p )\n", did, qos_ctx);
	setup_dialog_callbacks(did, qos_ctx);

	run_create_cbs(qos_ctx, msg);

	if (parse_sdp(msg)) {
		lock_get(&qos_ctx->lock);
		add_sdp(qos_ctx, dir, msg, role, other_role);
		lock_release(&qos_ctx->lock);
	}


	return;
}


/**
 * This callback is called when ever a dialog isdestroyed.
 *
 * @param did - The Dialog ID / structure pointer. Used as an ID only.
 * @param type - The termination cause/reason.
 * @param params - pointer to the dlg_cb params
 */
static void qos_dialog_destroy_CB(struct dlg_cell* did, int type, struct dlg_cb_params * params)
{
	struct sip_msg* msg = params->msg;
	qos_ctx_t* qos_ctx = (qos_ctx_t*)*(params->param);

	/* run the QOSCB_TERMINATED callback */
	run_qos_callbacks(QOSCB_TERMINATED, qos_ctx, NULL, 0, msg);

	/* Free the param qos_info_t memory */
	if (qos_ctx) {
		destroy_qos_ctx(qos_ctx);
		params->param = NULL;
	}
	return;
}

/**
 *
 * @param did - The dialog structure. The pointer is used as an ID.
 * @param type - The reason for the callback. DLGCB_REQ_WITHIN
 * @param msg - The SIP message that causes the callback.
 * @param param - The qos information
 */
static void qos_dialog_request_CB(struct dlg_cell* did, int type, struct dlg_cb_params * params)
{
	struct sip_msg* msg = params->msg;
	unsigned int dir = params->direction, role, other_role;
	qos_ctx_t* qos_ctx = (qos_ctx_t*)*(params->param);

	if (dir == DLG_DIR_UPSTREAM) {
		role = QOS_CALLEE;
		other_role = QOS_CALLER;
	} else if (dir == DLG_DIR_DOWNSTREAM) {
		role = QOS_CALLER;
		other_role = QOS_CALLEE;
	} else {
		LM_ERR("Unknown dir %d\n", dir);
		return;
	}

	if (msg->first_line.type == SIP_REQUEST) {
		if (    (msg->first_line.u.request.method_value == METHOD_INVITE) ||
			(msg->first_line.u.request.method_value == METHOD_UPDATE) ||
			(msg->first_line.u.request.method_value == METHOD_ACK) ||
			(msg->first_line.u.request.method_value == METHOD_PRACK)) {
			if (parse_sdp(msg)) {
				lock_get(&qos_ctx->lock);
				add_sdp(qos_ctx, dir, msg, role, other_role);
				lock_release(&qos_ctx->lock);
			}
		} else {
			LM_DBG("Ignoring non-carrying SDP req\n");
			return;
		}
	} else {
		LM_ERR("not a SIP_REQUEST\n");
		return;
	}

	return;
}

/**
 * This callback is called on any response message in the lifespan of
 * the dialog. The callback is called just before the message is
 * copied to pkg memory so it is still mutable.
 *
 * @param did - The dialog structure. The pointer is used as an ID.
 * @param type - The reason for the callback. DLGCB_CONFIRMED
 * @param msg - The SIP message that causes the callback.
 * @param param - The qos information
 */
static void qos_dialog_response_CB(struct dlg_cell* did, int type, struct dlg_cb_params * params)
{
	struct sip_msg* msg = params->msg;
	unsigned int dir = params->direction, role, other_role;
	qos_ctx_t* qos_ctx = (qos_ctx_t*)*(params->param);

	if (dir == DLG_DIR_UPSTREAM) {
		role = QOS_CALLEE;
		other_role = QOS_CALLER;
	} else if (dir == DLG_DIR_DOWNSTREAM) {
		role = QOS_CALLER;
		other_role = QOS_CALLEE;
	} else {
		LM_ERR("Unknown dir %d\n", dir);
		return;
	}

	if (msg->first_line.type == SIP_REPLY) {
		if (msg->first_line.u.reply.statuscode > 100 &&
			msg->first_line.u.reply.statuscode < 300) {
			if (parse_sdp(msg)) {
				lock_get(&qos_ctx->lock);
				add_sdp(qos_ctx, dir, msg, role, other_role);
				lock_release(&qos_ctx->lock);
			}
		} else if (msg->first_line.u.reply.statuscode > 399 &&
			msg->first_line.u.reply.statuscode < 700) {
			lock_get(&qos_ctx->lock);
			remove_sdp(qos_ctx, dir, msg, role, other_role);
			lock_release(&qos_ctx->lock);
		}
	} else {
		LM_ERR("not a SIP_REPLY\n");
		return;
	}

	return;
}

