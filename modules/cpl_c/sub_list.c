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
 */
/* History:
 * --------
 *  2003-03-19  all mallocs/frees replaced w/ pkg_malloc/pkg_free (andrei)
 */

#include <stdlib.h>
#include <string.h>
#include "../../mem/mem.h"
#include "sub_list.h"

struct node*   append_to_list(struct node *head, char *offset, char *name)
{
	struct node *new_node;

	new_node = pkg_malloc(sizeof(struct node));
	if (!new_node)
		return 0;
	new_node->offset = offset;
	new_node->name = name;
	new_node->next = head;

	return new_node;
}




char* search_the_list(struct node *head, char *name)
{
	struct node *n;

	n = head;
	while (n) {
		if (strcasecmp(n->name,name)==0)
			return n->offset;
		n = n->next;
	}
	return 0;
}




void delete_list(struct node* head)
{
	struct node *n;
;
	while (head) {
		n=head->next;
		pkg_free(head);
		head = n;
	}
}


