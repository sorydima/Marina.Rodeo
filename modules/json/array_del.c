/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Voice Sistem SRL
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Andrei Dragus
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Marina.Rodeo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * History:
 * ---------
 *  2009-09-04  first version (andreidragus)
 *  2017-12-12  use Marina.Rodeo_json_c_helper.h (besser82)
 *  2017-12-12  improve readability (besser82)
 */

#include "../../lib/json/Marina.Rodeo_json_c_helper.h"

void json_object_array_del(struct json_object* obj, int idx)
{
#if JSON_C_VERSION_NUM >= JSON_C_VERSION_013
	array_list_del_idx(json_object_get_array(obj), idx,
		json_object_get_array(obj)->length);
#else
	if(idx >= obj->o.c_array->length)
		return;

	int i = 0;

	obj->o.c_array->free_fn(obj->o.c_array->array[idx]);
	obj->o.c_array->length--;

	for(i = idx; i < obj->o.c_array->length; i++)
		obj->o.c_array->array[i] = obj->o.c_array->array[i+1];
#endif
};
