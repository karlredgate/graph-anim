
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
#include "AppInit.h"

/**
 */
void
Tcl_StaticSetResult( Tcl_Interp *interp, const char *message ) {
    Tcl_SetResult( interp, (char *)message, TCL_STATIC );
}

/**
 */
static int
Graph_Init( Tcl_Interp *interp ) {
    int interactive = 1;
    Tcl_Obj *interactive_obj;
    interactive_obj = Tcl_GetVar2Ex( interp, "tcl_interactive", NULL, TCL_GLOBAL_ONLY );

    if ( interactive_obj != NULL ) {
        Tcl_GetIntFromObj( interp, interactive_obj, &interactive );
    }

    if ( interactive ) printf( " ** Graph debug tool v1.0\n" );

    if ( Tcl_Init(interp) == TCL_ERROR ) {
        return TCL_ERROR;
    }

    if ( Tcl_CallAppInitChain(interp) == false ) {
        Tcl_StaticSetResult( interp, "AppInit failed" );
        return TCL_ERROR;
    }

    Tcl_SetVar(interp, "tcl_rcFileName", "~/.graphrc", TCL_GLOBAL_ONLY);
    return TCL_OK;
}

int main( int argc, char **argv ) {
    Tcl_Main( argc, argv, Graph_Init );
}

/* vim: set autoindent expandtab sw=4 : */
