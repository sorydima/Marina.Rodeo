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
 *
 */


#ifndef _PIKE_TIMER_H
#define _PIKE_TIMER_H


struct list_link {
	struct list_link *next;
	struct list_link *prev;
};


#define has_timer_set(_ll) \
	((_ll)->prev || (_ll)->next)

#define is_list_empty(_head) \
	((_head)->next == (_head))

#define update_in_timer( _head, _ll) \
	do { \
		remove_from_timer( _head, _ll);\
		append_to_timer( _head, _ll); \
	}while(0)


void append_to_timer(struct list_link *head, struct list_link *ll );

void remove_from_timer(struct list_link *head, struct list_link *ll);

void check_and_split_timer(struct list_link *head, unsigned int time,
		struct list_link *split, unsigned char *mask);


#endif

