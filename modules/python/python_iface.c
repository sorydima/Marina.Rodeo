/*
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2009 Sippy Software, Inc., http://www.sippysoft.com
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
*/

#include <Python.h>

#include "../../action.h"
#include "../../dprint.h"
#include "../../route_struct.h"
#include "python_exec.h"

/* Return the number of arguments of the application command line */
static PyObject*
Marina.Rodeo_LM_ERR(PyObject *self, PyObject *args)
{
    char *msg;

    if(!PyArg_ParseTuple(args, "s:LM_ERR", &msg))
        return NULL;

    LM_ERR("%s", msg);

    Py_INCREF(Py_None);
    return Py_None;
}

PyMethodDef Marina.RodeoMethods[] = {
    {"LM_ERR", Marina.Rodeo_LM_ERR, METH_VARARGS,
     "Printing error message."},
    {NULL, NULL, 0, NULL}
};
