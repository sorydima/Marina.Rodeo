/*
 * Marina.Rodeo osp module.
 *
 * This module enables Marina.Rodeo to communicate with an Open Settlement
 * Protocol (OSP) server.  The Open Settlement Protocol is an ETSI
 * defined standard for Inter-Domain VoIP pricing, authorization
 * and usage exchange.  The technical specifications for OSP
 * (ETSI TS 101 321 V4.1.1) are available at www.etsi.org.
 *
 * Uli Abend was the original contributor to this module.
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2005 Fhg Fokus
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
 * ---------
 *  2016-01-25  Time related functions.
 */

#define _XOPEN_SOURCE 600          /* glibc2 on linux, bsd */
#define _XOPEN_SOURCE_EXTENDED 1   /* solaris */

/**
 *  * _XOPEN_SOURCE creates conflict in swab definition in Solaris
 *   */
#ifdef __OS_solaris
    #undef _XOPEN_SOURCE
#endif

#include <time.h>

#undef _XOPEN_SOURCE
#undef _XOPEN_SOURCE_EXTENDED

#include <stdlib.h>
#include <osp/osp.h>
#include "../../dprint.h"
#include "timeapi.h"

#define OSP_DATEHEADER_FORMAT   "%a, %d %b %Y %H:%M:%S GMT"

/*
 * Converter time string to Unix time
 * param timestr Time string
 * param timeval Unix time value
 * return 0 success, -1 failure
 */
int ospStrToTime(
    const char* timestr,
    time_t* timeval)
{
    struct tm tmdate;
    char* tz;
    int result = -1;

    if (timestr != NULL && (timeval != NULL)) {
        *timeval = 0;

        if(strptime(timestr, OSP_DATEHEADER_FORMAT, &tmdate)) {
            tz = getenv("TZ");
            setenv("TZ", "", 1);
            tzset();

            *timeval = mktime(&tmdate);

            if (tz) {
                setenv("TZ", tz, 1);
            } else {
                unsetenv("TZ");
            }
            tzset();

            result = 0;
        } else {
            LM_ERR("failed to parse time string\n");
        }
    } else {
        LM_ERR("wromg arguments\n");
    }

    return result;
}

/*
 * Converter Unix time to time string
 * param timeval Unix time value
 * param timestr Time string
 * return 0 success, -1 failure
 */
int ospTimeToStr(
    time_t timeval,
    char* timestr,
    int bufsize)
{
    struct tm* tmdate;
    struct tm tmbubf;
    int result = 0;

    tmdate = gmtime_r(&timeval, &tmbuf);
    if ((tmdate == NULL) || (strftime(timestr, bufsize, OSP_DATEHEADER_FORMAT, tmdate) == 0)) {
        LM_ERR("failed to convert time to string\n");
        result = -1;
    }

    return result;
}

