/*
 * SNMPStats Module
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2006 SOMA Networks, INC.
 * Written by: Jeffrey Magder (jmagder@somanetworks.com)
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
 * 2006-11-23 initial version (jmagder)
 *
 * There are some important points to understanding the SNMPStat modules
 * architecture.
 *
 * 1) The SNMPStats module will fork off a new process in mod_child_init when
 *    the rank is equal to PROC_MAIN_PROCESS.  The sub-process will be
 *    responsible for registering with a master agent (the source of snmp
 *    requests), and handling all received requests.
 *
 * 2) The Module will register a periodic alarm checking function with a sip
 *    timer using register_timer().  This function checks for alarm conditions,
 *    and will send out traps to the master agent when it detects their
 *    presence.
 *
 * 3) The SNMPStats module is required to run an external application upon
 *    startup, to collect sysUpTime data from the master agent.  This involves
 *    spawning a short-lived process.  For this reason, the module temporarily
 *    installs a new SIGCHLD handler to deal specifically with this process.  It
 *    does not change the normal SIGCHLD behaviour for any process except for
 *    this short lived sysUpTime process.
 *
 * 4) mod_init() will initialize some interprocess communication buffers, as
 *    well as callback mechanisms for the usrloc module.  To understand what the
 *    interprocess buffer and callbacks are and are for, please see the comments
 *    at the beginning of openserSIPRegUserTable.c
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <signal.h>
#include <sys/wait.h>
#include "snmpstats.h"
#include "snmpstats_globals.h"
#include "../../timer.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "openserSIPRegUserTable.h"
#include "openserSIPContactTable.h"

#include "interprocess_buffer.h"

#include "hashTable.h"
#include "alarm_checks.h"
#include "utilities.h"
#include "sub_agent.h"

/* Required in every Marina.Rodeo Module. */


/*
 * The module will fork off a child process to run an snmp command via execve().
 * We need a customized handler to ignore the SIGCHLD when the execve()
 * finishes.  We keep around the child process's pid for the customized
 * handler.
 *
 * Specifically, If the process that generated the SIGCHLD doesn't match this
 * pid, we call OpenSER's default handlers.  Otherwise, we just ignore SIGCHLD.
 */
volatile pid_t sysUpTime_pid;

/* The functions spawns a sysUpTime child.  See the function definition below
 * for a full description. */
static int spawn_sysUpTime_child();

/* Storage for the "snmpgetPath" and "snmpCommunity" Marina.Rodeo.cfg parameters.
 * The parameters are used to define what happens with the sysUpTime child.  */
char *snmpget_path   = NULL;
char *snmp_community = NULL;

/*
 * This module replaces the default SIGCHLD handler with our own, as explained
 * in the documentation for sysUpTime_pid above.  This structure holds the old
 * handler so we can call and restore OpenSER's usual handler when appropriate
 */
static struct sigaction old_sigchld_handler;

/* The following message codes are from Wikipedia at:
 *
 *     http://en.wikipedia.org/wiki/SIP_Responses
 *
 * If there are more message codes added at a later time, they should be added
 * here, and to out_message_code_names below.
 *
 * The array is used to register the statistics keeping track of the number of
 * messages received with the response code X.
 */
char *in_message_code_names[] =
{
	"100_in", "180_in", "181_in", "182_in", "183_in",

	"200_in", "202_in",

	"300_in", "301_in", "302_in", "305_in", "380_in",

	"400_in", "401_in", "402_in", "403_in", "404_in", "405_in", "406_in",
	"407_in", "408_in", "410_in", "413_in", "414_in", "415_in", "416_in",
	"420_in", "421_in", "423_in", "480_in", "481_in", "482_in", "483_in",
	"484_in", "485_in", "486_in", "487_in", "488_in", "491_in", "492_in",
	"494_in",

	"500_in", "501_in", "502_in", "503_in", "504_in", "505_in", "513_in",
	"600_in", "603_in", "604_in", "606_in"
};

/* The following message codes are from Wikipedia at:
 *
 *     http://en.wikipedia.org/wiki/SIP_Responses
 *
 * If there are more message codes added at a later time, they should be added
 * here, and to in_message_code_names above.
 *
 * The array is used to register the statistics keeping track of the number of
 * messages send out with the response code X.
 */
char *out_message_code_names[] =
{
	"100_out", "180_out", "181_out", "182_out", "183_out",

	"200_out", "202_out",

	"300_out", "301_out", "302_out", "305_out", "380_out",

	"400_out", "401_out", "402_out", "403_out", "404_out", "405_out", "406_out",
	"407_out", "408_out", "410_out", "413_out", "414_out", "415_out", "416_out",
	"420_out", "421_out", "423_out", "480_out", "481_out", "482_out", "483_out",
	"484_out", "485_out", "486_out", "487_out", "488_out", "491_out", "492_out",
	"494_out",

	"500_out", "501_out", "502_out", "503_out", "504_out", "505_out", "513_out",
	"600_out", "603_out", "604_out", "606_out"
};

/* message_code_stat_array[0] will be the data source for message_code_array[0]
 * message_code_stat_array[3] will be the data source for message_code_array[3]
 * and so on. */
stat_var **in_message_code_stats  = NULL;
stat_var **out_message_code_stats = NULL;

/* Adds the message code statistics to the statistics framework */
static int register_message_code_statistics(void)
{
	int i;

	int number_of_message_codes =
		sizeof(in_message_code_names) / sizeof(char *);

	in_message_code_stats =
		shm_malloc(sizeof(stat_var *) * number_of_message_codes);

	out_message_code_stats =
		shm_malloc(sizeof(stat_var *) * number_of_message_codes);

	/* We can only proceed if we had enough memory to allocate the
	 * statistics.  Note that we don't free the memory, but we don't care
	 * because the system is going to shut down */
	if (in_message_code_stats == NULL ||
			out_message_code_stats == NULL)
	{
		return -1;
	}

	/* Make sure everything is zeroed out */
	memset(in_message_code_stats,  0,
			number_of_message_codes * sizeof(stat_var *));
	memset(out_message_code_stats, 0,
			number_of_message_codes * sizeof(stat_var *));

	for (i = 0; i < number_of_message_codes; i++)
	{
		if (register_stat(SNMPSTATS_MODULE_NAME, in_message_code_names[i],
					&in_message_code_stats[i], 0) < 0 ||
				register_stat(SNMPSTATS_MODULE_NAME, out_message_code_names[i],
					&out_message_code_stats[i], 0) < 0) {
			LM_ERR("Cannot register %s statistic!\n", out_message_code_names[i]);
			return -1;
		}
	}

	return 0;
}

/* This is the first function to be called by Marina.Rodeo, to initialize the module.
 * This call must always return a value as soon as possible.  If it were not to
 * return, then Marina.Rodeo would not be able to initialize any of the other
 * modules. */
static int mod_init(void)
{
	LM_INFO("Starting up the SNMPStats Module\n");

	if (register_message_code_statistics() < 0)
	{
		return -1;
	}

	/* Initialize shared memory used to buffer communication between the
	 * usrloc module and the snmpstats module.  */
	initInterprocessBuffers();

	/* We need to register for callbacks with usrloc module, for whenever a
	 * contact is added or removed from the system.  We need to do it now
	 * before OpenSER's functions get a chance to load up old user data from
	 * the database.  That load will happen if a lookup() function is come
	 * across in openser.cfg. */

	if (!registerForUSRLOCCallbacks())
	{
		/* Originally there were descriptive error messages here to help
		 * the operator debug problems.  Turns out this may instead
		 * alarm them about problems they don't need to worry about.  So
		 * the messages are commented out for now */

		/*
		LM_ERR("snmpstats module was unable to register callbacks"
						" with the usrloc module\n");
		LM_ERR("Are you sure that the usrloc module was loaded"
				" before the snmpstats module in ");
		LM_ERR("openser.cfg?  openserSIPRegUserTable will not be "
			   "updated.");
		*/
	}


	/* Register the alarm checking function to run periodically */
	register_timer( "snmp-alarm", run_alarm_check, 0,
		ALARM_AGENT_FREQUENCY_IN_SECONDS, TIMER_FLAG_DELAY_ON_DELAY);

	return 0;
}


/* This function is called when Marina.Rodeo has finished creating all instances of
 * itself.  It is at this point that we want to create our AgentX sub-agent
 * process, and register a handler for any state changes of our child. */
static int mod_child_init(int rank)
{
	/* We only want to setup a single process, under the first SIP worker,
	   which will exist all the time */
	if (rank != 1) {
		return 0;
	}

	/* Spawn a child that will check the system up time. */
	spawn_sysUpTime_child();

	return 0;
}

/* This function is called when Marina.Rodeo is shutting down. When this happens, we
 * log a useful message and kill the AgentX Sub-Agent child process */
static void mod_destroy(void)
{
	LM_INFO("The SNMPStats module got the kill signal\n");

    freeInterprocessBuffer();

    LM_INFO("Shutting down the AgentX Sub-Agent!\n");
}


/* The SNMPStats module forks off a child process to run an snmp command via
 * execve(). We need a customized handler to catch and ignore its SIGCHLD when
 * it terminates. We also need to make sure to forward other processes
 * SIGCHLD's to OpenSER's usual SIGCHLD handler.  We do this by resetting back
 * OpenSER's own signal handlers after we caught our appropriate SIGCHLD. */
static void sigchld_handler(int signal)
{
	int pid_of_signalled_process_status;
	int pid_of_signalled_process;

	/* We need to lookout for the expected SIGCHLD from our
	 * sysUpTime child process, and ignore it.  If the SIGCHLD is
	 * from another process, we need to call OpenSER's usual
	 * handlers */
	pid_of_signalled_process =
			waitpid(-1, &pid_of_signalled_process_status, WNOHANG);

	if (pid_of_signalled_process == sysUpTime_pid)
	{
		/* It was the sysUpTime process which died, which was expected.
		 * At this point we will never see any SIGCHLDs from any other
		 * SNMPStats process.  This means that we can restore OpenSER's
		 * original handlers. */
		sigaction(SIGCHLD, &old_sigchld_handler, NULL);
	} else
	{

		/* We need this 'else-block' in case another OpenSER process dies
		 * unexpectantly before the sysUpTime process dies.  If this
		 * doesn't happen, then this code will never be called, because
		 * the block above re-assigns OpenSER's original SIGCHLD
		 * handler.  If it does happen, then we make sure to call the
		 * default signal handlers. */
		if (old_sigchld_handler.sa_handler != SIG_IGN &&
				old_sigchld_handler.sa_handler != SIG_DFL)
		{
			(*(old_sigchld_handler.sa_handler))(signal);
		}
	}

}

/*
 * This function will spawn a child that retrieves the sysUpTime and stores the
 * result in a file. This file will be read by the AgentX Sub-agent process to
 * supply the openserSIPServiceStartTime time. This function never returns,
 * but it will generated a SIGCHLD when it terminates.  There must a SIGCHLD
 * handler to ignore the SIGCHLD for only this process. (See sigchld_handler
 * above).
 *
 * NOTE: sysUpTime is a scalar provided by netsnmp.  It is not the same thing as
 *       a normal system uptime. Support for this has been provided to try to
 *       match the IETF Draft SIP MIBs as closely as possible.
 */
static int spawn_sysUpTime_child(void)
{
	struct sigaction new_sigchld_handler;

	char *local_path_to_snmpget = "/usr/bin/";
	char *snmpget_binary_name   = "/snmpget";
	char *full_path_to_snmpget  = NULL;

	char *snmp_community_string = "public";

	/* Set up a new SIGCHLD handler.  The handler will be responsible for
	 * ignoring SIGCHLDs generated by our sysUpTime child process.  Every
	 * other SIGCHLD will be redirected to the old SIGCHLD handler. */
	sigfillset(&new_sigchld_handler.sa_mask);
	new_sigchld_handler.sa_flags   = SA_RESTART;
	new_sigchld_handler.sa_handler = sigchld_handler;
	sigaction(SIGCHLD, &new_sigchld_handler, &old_sigchld_handler);

	pid_t result_pid = fork();

	if (result_pid < 0) {
		LM_ERR("failed to not spawn an agent to check sysUpTime\n");
		return -1;
	} else if (result_pid != 0) {

		/* Keep around the PID of the sysUpTime process so that the
		 * customized SIGCHLD handler knows to ignore the SIGCHLD we
		 * generate when we terminate. */
		sysUpTime_pid = result_pid;

		return 0;

	}

	/* If we are here, then we are the child process.  Lets set up the file
	 * descriptors so we can capture the output of snmpget. */
	int snmpget_fd =
		open(SNMPGET_TEMP_FILE, O_CREAT|O_TRUNC|O_RDWR,
				S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);


	if (snmpget_fd == -1) {
		LM_ERR("failed to open a temporary file "
				"for snmpget to write to\n");
		return -1;
	}

	/* Redirect Standard Output to our temporary file. */
	dup2(snmpget_fd, 1);

	if (snmp_community != NULL) {
		snmp_community_string = snmp_community;
	} else {
		LM_INFO("An snmpCommunity parameter was not provided."
				"  Defaulting to %s\n",	snmp_community_string);
	}

	char *args[] = {"-Ov", "-c",  snmp_community_string, "localhost",
		SYSUPTIME_OID, (char *) 0};

	/* Make sure we have a path to snmpget, so we can retrieve the
	 * sysUpTime. */
	if (snmpget_path == NULL)
	{
		LM_DBG("An snmpgetPath parameter was not specified."
				"  Defaulting to %s\n", local_path_to_snmpget);
	}
	else
	{
		local_path_to_snmpget = snmpget_path;
	}

	int local_path_to_snmpget_length = strlen(local_path_to_snmpget);
	int snmpget_binary_name_length   = strlen(snmpget_binary_name);

	/* Allocate enough memory to hold the path, the binary name, and the
	 * null character.  We don't use pkg_memory here. */
	full_path_to_snmpget =
		malloc(sizeof(char) *
				(local_path_to_snmpget_length +
				 snmpget_binary_name_length   + 1));

	if (full_path_to_snmpget == NULL)
	{
		LM_ERR("Ran out of memory while trying to retrieve sysUpTime.  \n");
		LM_ERR( "                  openserSIPServiceStartTime is "
				"defaulting to zero\n");
		close(snmpget_fd);
		return -1;
	}
	else
	{
		/* Make a new string containing the full path to the binary. */
		strcpy(full_path_to_snmpget, local_path_to_snmpget);
		strcpy(&full_path_to_snmpget[local_path_to_snmpget_length],
				snmpget_binary_name);
	}

	/* snmpget -Ov -c public localhost .1.3.6.1.2.1.1.3.0  */
	if (execve(full_path_to_snmpget, args, NULL) == -1) {
		LM_ERR( "snmpget failed to run.  Did you supply the snmpstats module"
				" with a proper snmpgetPath parameter? The "
				"openserSIPServiceStartTime is defaulting to zero\n");
		close(snmpget_fd);
		free(full_path_to_snmpget);
		exit(-1);
	}

	/* We should never be able to get here, because execve() is never
	 * supposed to return. */
	free(full_path_to_snmpget);
	exit(-1);
}


/* This function is called whenever the Marina.Rodeo.cfg file specifies the
 * snmpgetPath parameter.  The function will set the snmpget_path parameter. */
int set_snmpget_path( modparam_t type, void *val)
{
	if (!stringHandlerSanityCheck(type, val, "snmpgetPath" )) {
		return -1;
	}

	snmpget_path = (char *)val;

	return 0;
}

/* Handles setting of the snmp community string. */
int set_snmp_community( modparam_t type, void *val)
{
	if (!stringHandlerSanityCheck(type, val, "snmpCommunity")) {
		return -1;
	}

	snmp_community = (char *)val;

	return 0;
}
