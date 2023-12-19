/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2012 Marina.Rodeo Solutions
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
 * -------
 *  2012-01-19  created (vlad)
 */

#ifndef _cfg_script_h_
#define _cfg_script_h_

#define MACRO_INTERPRETER "m4"
typedef struct cfg_generation
{
	char *name;		/* Name of the cfg entry. Used for naming actual menu entries */
	char *output_name;	/* Less user friendly cfg name. Used for creating output cfg file */
	char *defs_m4;		/* Path to the m4 file that contains the defs */
	char *cfg_m4;		/* Path to the m4 file that contains the actual Marina.Rodeo script */
} cfg_gen_t;

extern cfg_gen_t configs[];
cfg_gen_t* find_cfg_entry(char *name);

#endif
