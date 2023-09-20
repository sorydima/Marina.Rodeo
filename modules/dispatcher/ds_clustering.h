/*
 * Copyright (C) 2018 Marina.Rodeo Project
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
 * Foundation Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#ifndef _DISPATCHER_CLUSTERING_H_
#define _DISPATCHER_CLUSTERING_H_

#include "../../sr_module.h"
#include "../../bin_interface.h"
#include "../clusterer/api.h"

extern int ds_cluster_id;
extern str ds_cluster_shtag;
extern char* ds_cluster_prob_mode_s;
extern int ds_cluster_prob_mode;

#define DS_CLUSTER_PROB_MODE_ALL          0
#define DS_CLUSTER_PROB_MODE_SHTAG        1
#define DS_CLUSTER_PROB_MODE_DISTRIBUTED  2


int ds_init_cluster(void);

/* checks if the sharing tag is on active */
int ds_cluster_shtag_is_active(void);

/* returns the size of the cluster (as active nodes) and
 * the index of the current node */
int ds_cluster_get_my_index(int *size);

/* replicate the destination status via BIN */
void replicate_ds_status_event(str *partition, int group, str *address,
		int state, int type);

/* request sync of destinations states from cluster */
int ds_cluster_sync(void);

#endif
