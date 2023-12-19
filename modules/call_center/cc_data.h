/*
 * call center module - call queuing and distributio
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2014 Marina.Rodeo Solutions
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
 */



#ifndef CC_CC_DATA_H_
#define CC_CC_DATA_H_

#include "../../str.h"
#include "../../locking.h"
#include "../../hash_func.h"
#include "../../parser/msg_parser.h"


typedef enum {
	AUDIO_WELCOME,
	AUDIO_QUEUE,
	AUDIO_DISSUADING,
	AUDIO_FLOW_ID,
	MAX_AUDIO
} audio_files;

typedef enum {
	CC_MSRP_POLICY_LB,
	CC_MSRP_POLICY_FULL_AGENT
} msrp_policies;

struct cc_flow {
	str id;
	unsigned int is_new;
	/* configuration data */
	unsigned int priority;
	unsigned int skill;
	unsigned int max_wrapup;
	unsigned int diss_hangup;
	unsigned int diss_ewt_th;
	unsigned int diss_qsize_th;
	unsigned int diss_onhold_th;
	str recordings[MAX_AUDIO];
	str cid;
	/* runtime data */
	int ref_cnt;
	float avg_call_duration;
	unsigned long processed_calls;
	unsigned int logged_agents;
	unsigned int ongoing_calls;
	/* statistics */
	stat_var *st_incalls;
	stat_var *st_dist_incalls;
	stat_var *st_answ_incalls;
	stat_var *st_answ_inchats;
	stat_var *st_aban_incalls;
	stat_var *st_onhold_calls;
	stat_var *st_onhold_chats;
	stat_var *st_queued_calls;
	float avg_waittime;
	unsigned long avg_waittime_no;

	struct cc_flow *next;
};


#define MAX_SKILLS_PER_AGENT 64

typedef enum {
	CC_AGENT_FREE,
	CC_AGENT_WRAPUP,
	CC_AGENT_INCALL,
	CC_AGENT_INCHAT
}agent_state;

typedef enum {
	CC_MEDIA_RTP,
	CC_MEDIA_MSRP,
	CC_MEDIA_NO /* keep this at the end */
}media_type;

struct media_info {
	unsigned int sessions;
	str location; /* sip address*/
	str did;  /* shorcut for username in sips address */
};

struct cc_agent {
	str id;
	unsigned int is_new;
	/* configuration data */
	struct media_info media[CC_MEDIA_NO];
	/* skills */
	unsigned int no_skills;
	unsigned int skills[MAX_SKILLS_PER_AGENT];
	unsigned int wrapup_time;
	/* runtime data */
	int ref_cnt;
	agent_state state;
	unsigned int ongoing_sessions[CC_MEDIA_NO];
	unsigned int logged_in;
	/* seconds to the end of wrap up (relative to internal time)*/
	int wrapup_end_time;
	/* statistics */
	stat_var *st_dist_incalls;
	stat_var *st_answ_incalls;
	stat_var *st_answ_inchats;
	stat_var *st_aban_incalls;
	float avg_talktime;
	unsigned long avg_talktime_no;

	struct cc_agent *next;
};


struct cc_list {
	unsigned int lid;
	unsigned int calls_no;
	struct cc_call *first;
	struct cc_call *last;
};


struct cc_skill {
	str name;
	unsigned int id;
	unsigned int is_new;
	struct cc_skill *next;
};


#define CC_AG_OFFLINE 0
#define CC_AG_ONLINE  1

struct cc_data {
	gen_lock_t *lock;
	/* sub-structures */
	struct cc_flow *flows;
	struct cc_agent *agents[2];
	struct cc_agent *last_online_agent;
	struct cc_skill *skills_map;
	struct cc_list queue;
	struct cc_list list;
	/* old data */
	struct cc_flow *old_flows;
	struct cc_agent *old_agents;
	/* call related data */
	gen_lock_set_t *call_locks;
	unsigned int next_lock_to_use;
	struct cc_call *calls;
	/* skills related data */
	unsigned int last_skill_id;
	/* tracking data */
	unsigned int loggedin_agents;
	float avt_waittime;
	unsigned long avt_waittime_no;
	unsigned long totalnr_agents;
};


typedef enum {
	CC_CALL_NONE,
	CC_CALL_WELCOME,
	CC_CALL_DISSUADING1,
	CC_CALL_DISSUADING2,
	CC_CALL_QUEUED,
	CC_CALL_PRE_TOAGENT,
	CC_CALL_TOAGENT,
	CC_CALL_ENDED
} call_state;

static inline str *call_state_str(call_state state)
{
	static str call_state_s[] = {
		str_init("none"),
		str_init("welcome"),
		str_init("dissuading1"),
		str_init("dissuading2"),
		str_init("queued"),
		str_init("preagent"),
		str_init("toagent"),
		str_init("ended"),
		/* unused */
		str_init("unknown"),
	};
	int size = (sizeof(call_state_s)/sizeof(call_state_s[0]));
	return &call_state_s[(state < size - 1)?state:size - 1];
}

#define FSTAT_INCALL  (1<<0)
#define FSTAT_DIST    (1<<1)
#define FSTAT_ANSW    (1<<2)
#define FSTAT_ABAN    (1<<3)

struct cc_call {
	unsigned int id;
	unsigned int lock_idx;
	char ign_cback; /* ignore callbacks because agent_free was called */
	int fst_flags;  /* flow stats flags */
	media_type media;
	call_state state; /* call state */
	call_state prev_state;
	short ref_cnt; 
	short no_rejections;
	short setup_time;
	unsigned int eta;
	unsigned int last_start;
	unsigned int queue_start;
	unsigned int recv_time;
	str caller_dn;
	str caller_un;
	str script_param;
	/* b2b id */
	str b2bua_id;
	/* b2b agent id */
	str b2bua_agent_id;
	/* flow the call belong to */
	struct cc_flow *flow;
	/* agent taking this call  */
	struct cc_agent *agent;
	/* queue-ing link */
	struct cc_call *higher_in_queue;
	struct cc_call *lower_in_queue;
	struct cc_call *next_list;
	struct cc_call *prev_list;
};

#define is_call_in_queue(_data, _call) \
	((_call)->lower_in_queue || (_call)->higher_in_queue || \
		(_data->queue.first==_call && _data->queue.last==_call))

#define can_agent_take_chats( _agent) \
	( _agent->state==CC_AGENT_FREE || \
	  ( _agent->state==CC_AGENT_INCHAT \
	    && _agent->media[CC_MEDIA_MSRP].sessions > \
	      (_agent->ongoing_sessions[CC_MEDIA_MSRP] + \
	      /* if agent has ongoing MSRP wrapup, keep one channel free here */ \
	      ((get_ticks() <= _agent->wrapup_end_time)?1:0) ) \
	  ) \
	)

struct cc_data* init_cc_data(void);

void free_cc_data(struct cc_data *data);

str* get_skill_by_id(struct cc_data *data, unsigned int id);

int add_cc_flow( struct cc_data *data, str *id, int priority, str *skill,
		str *cid, int max_wrapup, int diss_hangup, int diss_ewt_th,
		int diss_qsize_th, int diss_onhold_th, str *recordings );

void update_cc_agent_att(struct cc_agent *agent, unsigned long duration);

int add_cc_agent( struct cc_data *data, str *id, struct media_info *media,
		str *skills, unsigned int logstate, unsigned int wrapup_time,
		unsigned int wrapup_end_time);

void update_cc_flow_awt(struct cc_flow *flow, unsigned long duration);

struct cc_agent* get_agent_by_name(struct cc_data *data, str *name,
		struct cc_agent **prev_agent);

struct cc_flow *get_flow_by_name(struct cc_data *data, str *name);

struct cc_call* new_cc_call(struct cc_data *data, struct cc_flow *flow,
		str *dn, str *un, str *param);

void free_cc_call(struct cc_data *data, struct cc_call *call);

struct cc_agent* get_free_agent_by_skill(struct cc_data *data,
		media_type media, unsigned int skill);

void log_agent_to_flows(struct cc_data *data, struct cc_agent *agent,
		int login);

void agent_raise_event(struct cc_agent *agent, struct cc_call *call);

void clean_cc_old_data(struct cc_data *data);

void clean_cc_unref_data(struct cc_data *data);

int cc_queue_push_call(struct cc_data *data, struct cc_call *call, int top);

struct cc_call *cc_queue_pop_call_for_agent(struct cc_data *data,
		struct cc_agent *agent, media_type media);

void cc_queue_rmv_call( struct cc_data *data, struct cc_call *call);


static inline void remove_cc_agent(struct cc_data* data, 
		struct cc_agent* agent, struct cc_agent* prev_agent)
{
	struct cc_agent* tmp_agent;
	if(prev_agent == agent) /* if on top of the list*/
		data->agents[agent->logged_in] = agent->next;
	else
		prev_agent->next = agent->next;

	if (agent->logged_in && data->last_online_agent == agent) {
		/* if agent was the last in the list */
		if (data->agents[CC_AG_ONLINE] == NULL)
			data->last_online_agent = NULL;
		else {
			if (prev_agent == agent) {
				LM_CRIT("last_online_agent pointer not correct"
				 "- pointing to the first record in list but next not NULL\n");
				/* search for the real last */
				for(tmp_agent= data->agents[CC_AG_ONLINE]; tmp_agent;
				tmp_agent= tmp_agent->next)
					data->last_online_agent = tmp_agent;
			}
			else
				data->last_online_agent = prev_agent;
		}
	}
}


static inline void move_cc_agent_to_end( struct cc_data *data,
		struct cc_agent *agent, struct cc_agent *prev_agent)
{
	struct cc_agent *tmp_ag;

	/* move it to the end of the list*/
	if(data->last_online_agent != agent) {
		remove_cc_agent(data, agent, prev_agent);
		if(!data->last_online_agent) {
			LM_CRIT("last_online_agent NULL\n");
			if(data->agents[CC_AG_ONLINE] == NULL)
				data->agents[CC_AG_ONLINE] = agent;
			else {
				for (tmp_ag = data->agents[CC_AG_ONLINE]; tmp_ag;
				tmp_ag= tmp_ag->next)
				{
					prev_agent = tmp_ag;
				}
				prev_agent->next = agent;
				agent->next = NULL;
				data->last_online_agent = agent;
			}
		}
		else {
			data->last_online_agent->next = agent;
			agent->next = NULL;
			data->last_online_agent = agent;
		}
	}
}


static inline void add_cc_agent_top( struct cc_data *data,
		struct cc_agent *agent)
{
	agent->next = data->agents[ agent->logged_in ];
	data->agents[ agent->logged_in ] = agent;
}


static inline void agent_switch_login(struct cc_data* data, 
			struct cc_agent* agent, struct cc_agent* prev_agent)
{
	/* take out of the current list */
	remove_cc_agent(data, agent, prev_agent);
	agent->logged_in ^= 1;
	agent_raise_event( agent, NULL);
	/* add on top of the new one */
	add_cc_agent_top(data, agent);
}
#endif
