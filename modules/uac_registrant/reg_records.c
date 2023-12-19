/*
 * registrant module
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2011 VoIP Embedded Inc.
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
 *  2011-02-11  initial version (Ovidiu Sas)
 */

#include <stdio.h>
#include <stdlib.h>

#include "reg_records.h"

extern unsigned int default_expires;
extern const str uac_reg_state[];

static char call_id_ftag_buf[MD5_LEN];

int send_unregister(unsigned int hash_index, reg_record_t *rec, str *auth_hdr,
	unsigned int all_contacts);

void reg_print_record(reg_record_t *rec) {
	LM_DBG("checking uac=[%p] state=[%d][%.*s] expires=[%d]"
			" last_register_sent=[%d] registration_timeout=[%d]"
			" auth_user[%p][%d]->[%.*s] auth_password=[%p][%d]->[%.*s]"
			" sock=[%p] clustering=[%.*s/%d] enabled=[%s]\n",
		rec, rec->state,
		uac_reg_state[rec->state].len, uac_reg_state[rec->state].s, rec->expires,
		(unsigned int)rec->last_register_sent, (unsigned int)rec->registration_timeout,
		rec->auth_user.s, rec->auth_user.len, rec->auth_user.len, rec->auth_user.s,
		rec->auth_password.s, rec->auth_password.len,
		rec->auth_password.len, rec->auth_password.s, rec->td.send_sock,
		rec->cluster_shtag.len, rec->cluster_shtag.s, rec->cluster_id,
		rec->flags&REG_ENABLED ? "yes" : "no");
	LM_DBG("    RURI=[%p][%d]->[%.*s]\n", rec->td.rem_target.s, rec->td.rem_target.len,
			rec->td.rem_target.len, rec->td.rem_target.s);
	LM_DBG("      To=[%p][%d]->[%.*s]\n", rec->td.rem_uri.s, rec->td.rem_uri.len,
			rec->td.rem_uri.len, rec->td.rem_uri.s);
	LM_DBG("    From=[%p][%d]->[%.*s] tag=[%p][%d]->[%.*s]\n",
			rec->td.loc_uri.s, rec->td.loc_uri.len,
			rec->td.loc_uri.len, rec->td.loc_uri.s,
			rec->td.id.loc_tag.s, rec->td.id.loc_tag.len,
			rec->td.id.loc_tag.len, rec->td.id.loc_tag.s);
	LM_DBG(" Call-Id=[%p][%d]->[%.*s]\n", rec->td.id.call_id.s, rec->td.id.call_id.len,
			rec->td.id.call_id.len, rec->td.id.call_id.s);
	LM_DBG(" Contact=[%p][%d]->[%.*s] [%p][%d]->[%.*s]\n",
			rec->contact_uri.s, rec->contact_uri.len,
			rec->contact_uri.len, rec->contact_uri.s,
			rec->contact_params.s, rec->contact_params.len,
			rec->contact_params.len, rec->contact_params.s);
	if (rec->td.obp.s && rec->td.obp.len) {
		LM_DBG(" Proxy=[%p][%d]->[%.*s]\n",
			rec->td.obp.s, rec->td.obp.len, rec->td.obp.len, rec->td.obp.s);
	}

	return;
}


static void gen_call_id_ftag(str *aor, str *now, str *call_id_ftag)
{
	int i = 0;
	str src[3];
	int n;
        int l = 0;
        char *ch;
	str random_string;

       
        n = rand();
	ch = int2str(n , &l);


	call_id_ftag->len = MD5_LEN;
	call_id_ftag->s = call_id_ftag_buf;
	random_string.len = l;
	random_string.s= ch;

	src[i++] = *aor;
	src[i++]= random_string;
	if(now->s && now->len)
		src[i++] = *now;
	
	

	MD5StringArray(call_id_ftag->s, src, i);
	return;
}

void new_call_id_ftag_4_record(reg_record_t *rec, str *now)
{
	str call_id_ftag;
	char *p = (char *)(rec + 1);

	/* generate the new Call-ID and From tag */
	gen_call_id_ftag(&rec->td.rem_uri, now, &call_id_ftag);
	memcpy(p, call_id_ftag.s, call_id_ftag.len);

	/* reset the CSeq for the new Call-ID/ftag */
	rec->td.loc_seq.value = 0;
	//rec->td.loc_seq.is_set = 1;

	return;
}

int match_reload_record(void *e_data, void *data, void *n_data)
{
	reg_record_t *rec = (reg_record_t*)e_data;
	reg_record_t *new_rec = (reg_record_t*)n_data;
	record_coords_t *coords = (record_coords_t *)data;

	if (!str_strcmp(&coords->contact, &rec->contact_uri) &&
		!str_strcmp(&coords->registrar, &rec->td.rem_target)) {
		if (!(new_rec->flags&REG_ENABLED) && rec->flags&REG_ENABLED &&
			rec->state == REGISTERED_STATE) {
			if(send_unregister((unsigned long)coords->extra, rec, NULL, 0)==1)
				rec->state = UNREGISTERING_STATE;
			else
				rec->state = INTERNAL_ERROR_STATE;
		} else if (new_rec->flags&REG_ENABLED && rec->flags&REG_ENABLED &&
				rec->state == REGISTERED_STATE) {
			memcpy(new_rec->td.id.call_id.s, rec->td.id.call_id.s,
			    new_rec->td.id.call_id.len);
			memcpy(new_rec->td.id.loc_tag.s, rec->td.id.loc_tag.s,
			    new_rec->td.id.loc_tag.len);
			new_rec->td.loc_seq.value = rec->td.loc_seq.value;
			new_rec->last_register_sent = rec->last_register_sent;
			new_rec->registration_timeout = rec->registration_timeout;
			new_rec->state = rec->state;
		}

		return 1;
	} else
		return 0;  /* continue search */
}

int add_record(uac_reg_map_t *uac, str *now, unsigned int mode,
	record_coords_t *coords)
{
	reg_record_t *record;
	unsigned int size;
	dlg_t *td;
	str call_id_ftag;
	char *p;
	slinkedl_list_t *list;
	slinkedl_element_t *new_elem = NULL;

	/* Reserve space for record */
	size = sizeof(reg_record_t) + MD5_LEN +
		uac->to_uri.len + uac->from_uri.len + uac->registrar_uri.len +
		uac->auth_user.len + uac->auth_password.len +
		uac->contact_uri.len + uac->contact_params.len + uac->proxy_uri.len +
		uac->cluster_shtag.len;

	if (mode == REG_DB_LOAD_RECORD) {
		new_elem = slinkedl_new_element(&reg_alloc, size, (void**)&record);
		if (!new_elem) {
			LM_ERR("oom\n");
			return -1;
		}
	} else {
		if(mode==REG_DB_LOAD) list = reg_htable[uac->hash_code].p_list;
		else list = reg_htable[uac->hash_code].s_list;

		record = (reg_record_t*)slinkedl_append(list, size);
		if(!record) {
			LM_ERR("oom\n");
			return -1;
		}
	}

	memset(record, 0, size);

	record->expires = uac->expires;

	td = &(record->td);
	p = (char *)(record + 1);

	/* Setting the td->id */
	gen_call_id_ftag(&uac->to_uri, now, &call_id_ftag);
	memcpy(p, call_id_ftag.s, call_id_ftag.len);
	td->id.call_id.s = p;
	td->id.call_id.len = MD5_LEN - 5;
	td->id.loc_tag.s = p + MD5_LEN - 5;
	td->id.loc_tag.len = 5;
	p += MD5_LEN;

	//td->id.rem_tag.s = NULL;
	//td->id.rem_tag.len = 0;

	/* Setting the CSeq */
	td->loc_seq.value = 0;
	td->loc_seq.is_set = 1;
	//td->loc_seq.rem_tag.s = NULL;
	//td->loc_seq.rem_tag.len = 0;

	/* Setting the remote URI */
	td->rem_uri.s = p;
	td->rem_uri.len = uac->to_uri.len;
	memcpy(p, uac->to_uri.s, uac->to_uri.len);
	p += uac->to_uri.len;

	/* Setting the outbound proxy */
	if (uac->proxy_uri.s && uac->proxy_uri.len) {
		td->obp.s = p;
		td->obp.len = uac->proxy_uri.len;
		memcpy(p, uac->proxy_uri.s, uac->proxy_uri.len);
		p += uac->proxy_uri.len;
	}

	/* Setting the local URI */
	if(uac->from_uri.s && uac->from_uri.len) {
		LM_DBG("got from [%.*s]\n", uac->from_uri.len, uac->from_uri.s);
		td->loc_uri.s = p;
		td->loc_uri.len = uac->from_uri.len;
		memcpy(p, uac->from_uri.s, uac->from_uri.len);
		p += uac->from_uri.len;
	} else {
		td->loc_uri.s = td->rem_uri.s;
		td->loc_uri.len = td->rem_uri.len;
	}

	/* Setting the Remote target URI */
	td->rem_target.s = p;
	td->rem_target.len = uac->registrar_uri.len;
	memcpy(p, uac->registrar_uri.s, uac->registrar_uri.len);
	p += uac->registrar_uri.len;

	/* Setting the Local/Remote Display Name */
	//td->loc_dname.s = td->rem_dname.s = NULL;
	//td->loc_dname.len = td->rem_dname.len = 0;

	//td->T_flags = 0;
	td->state = DLG_CONFIRMED;

	/* Setting the Route set */
	//td->route_set = NULL;
	/* Setting the hooks */
	//td->hooks <- no hooks for REGISTER
	/* Setting the socket */
	td->send_sock = uac->send_sock;
	/* Done with td */

	if (uac->auth_user.s && uac->auth_user.len) {
		record->auth_user.s = p;
		record->auth_user.len = uac->auth_user.len;
		memcpy(p, uac->auth_user.s, uac->auth_user.len);
		p += uac->auth_user.len;
	}

	if (uac->auth_password.s && uac->auth_password.len) {
		record->auth_password.s = p;
		record->auth_password.len = uac->auth_password.len;
		memcpy(p, uac->auth_password.s, uac->auth_password.len);
		p += uac->auth_password.len;
	}

	record->contact_uri.s = p;
	record->contact_uri.len = uac->contact_uri.len;
	memcpy(p, uac->contact_uri.s, uac->contact_uri.len);
	p += uac->contact_uri.len;

	if (uac->contact_params.s && uac->contact_params.len) {
		record->contact_params.s = p;
		record->contact_params.len = uac->contact_params.len;
		memcpy(p, uac->contact_params.s, uac->contact_params.len);
		p += uac->contact_params.len;
	}

	/* Setting the clustering options */
	record->cluster_id = uac->cluster_id;
	if (uac->cluster_shtag.len) {
		record->cluster_shtag.s = p;
		record->cluster_shtag.len = uac->cluster_shtag.len;
		memcpy(p, uac->cluster_shtag.s, uac->cluster_shtag.len);
		p += uac->cluster_shtag.len;
	}

	/* Setting the flags */
	record->flags = uac->flags;

	if (mode == REG_DB_LOAD_RECORD) {
		coords->extra = (void*)(unsigned long)uac->hash_code;
		if (slinkedl_replace(reg_htable[uac->hash_code].p_list,
			match_reload_record, coords, new_elem) == 0)
			/* this is a new record altogether */
			slinkedl_append_element(reg_htable[uac->hash_code].p_list, new_elem);
	}

	reg_print_record(record);

	return 0;
}

void *reg_alloc(size_t size) { return shm_malloc(size); }
void reg_free(void *ptr) { shm_free(ptr); return; }

int init_reg_htable(void) {
	int i;

	reg_htable = (reg_table_t)shm_malloc(reg_hsize * sizeof(reg_entry_t));
	if(!reg_htable) {
		LM_ERR("oom\n");
		return -1;
	}

	for(i= 0; i<reg_hsize; i++) {
		lock_init(&reg_htable[i].lock);
		reg_htable[i].p_list = slinkedl_init(&reg_alloc, &reg_free);
		LM_DBG("reg_htable[%d].p_list=[%p]\n", i, reg_htable[i].p_list);
		if (reg_htable[i].p_list == NULL) {
			LM_ERR("oom while allocating list\n");
			return -1;
		}
		reg_htable[i].s_list = NULL;
	}
	return 0;
}


void destroy_reg_htable(void) {
	int i;

	if (reg_htable) {
		for(i=0; i<reg_hsize; i++) {
			lock_destroy(&reg_htable[i].lock);
			slinkedl_list_destroy(reg_htable[i].p_list);
			reg_htable[i].p_list = NULL;
		}
		shm_free(reg_htable);
		reg_htable = NULL;
	}
}

