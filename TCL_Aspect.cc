
/*
 * Copyright (c) 2012 Karl N. Redgate
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>

#include "platform_tcl.h"
#include "TCLTraceAdvice.h"
#include "AppInit.h"

/**
 */
int
Advice_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    TCLTraceAdvice *a = (TCLTraceAdvice *)data;

    if ( objc == 1 ) {
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(a)) );
        return TCL_OK;
    }

    if ( objc < 2 || objc > 3 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "command [value]" );
        return TCL_ERROR;
    }
    char *command = Tcl_GetStringFromObj( objv[1], NULL );

    if ( Tcl_StringMatch(command, "enter") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "enter script" );
            return TCL_ERROR;
        }
        a->_enter_( objv[2] );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "leave") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "leave script" );
            return TCL_ERROR;
        }
        a->_leave_( objv[2] );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "visit") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "visit script" );
            return TCL_ERROR;
        }
        a->_visit_( objv[2] );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for Advice object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
Advice_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 2 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    TCLTraceAdvice *a = new TCLTraceAdvice( interp );

    Tcl_CreateObjCommand( interp, name, Advice_obj, (ClientData)a, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(a)) );
    return TCL_OK;
}

/**
 */
static bool
Aspect_Module( Tcl_Interp *interp ) {
    Tcl_Command command;

    command = Tcl_CreateObjCommand(interp, "Advice", Advice_cmd, (ClientData)0, NULL);
    if ( command == NULL )  return false;

    return true;
}

app_init( Aspect_Module );

/* vim: set autoindent expandtab sw=4 : */
