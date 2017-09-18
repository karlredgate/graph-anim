
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

#include "ANN.h"

#include "TCLTraceAdvice.h"
#include "AppInit.h"

/**
 */
int
Perceptron_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    Perceptron *q = (Perceptron *)data;

    if ( objc < 2 || objc > 3 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "command [value]" );
        return TCL_ERROR;
    }
    char *command = Tcl_GetStringFromObj( objv[1], NULL );

    if ( Tcl_StringMatch(command, "reference") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "reference" );
            return TCL_ERROR;
        }
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for VertexQueue object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
Perceptron_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 2 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    Perceptron *q = new Perceptron();

    Tcl_CreateObjCommand( interp, name, Perceptron_obj, (ClientData)q, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
    return TCL_OK;
}


/**
 */
int
Layer_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    Layer *q = (Layer *)data;

    if ( objc < 2 || objc > 3 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "command [value]" );
        return TCL_ERROR;
    }
    char *command = Tcl_GetStringFromObj( objv[1], NULL );

    if ( Tcl_StringMatch(command, "reference") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "reference" );
            return TCL_ERROR;
        }
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "connect") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "connect value" );
            return TCL_ERROR;
        }
        Layer *v;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(v)) != TCL_OK ) {
            return TCL_ERROR;
        }
        q->connect( v );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for VertexQueue object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
Layer_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( (objc < 2) or (objc > 3) ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name [neuron-count]" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    int neuron_count;
    if ( objc == 3 ) {
        if ( Tcl_GetIntFromObj(interp,objv[2],&neuron_count) != TCL_OK ) {
            return TCL_ERROR;
        }
    }

    Layer *q = new Layer( neuron_count );

    Tcl_CreateObjCommand( interp, name, Layer_obj, (ClientData)q, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
    return TCL_OK;
}


/**
 */
int
Neuron_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    Neuron *q = (Neuron *)data;

    if ( objc < 2 || objc > 3 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "command [value]" );
        return TCL_ERROR;
    }
    char *command = Tcl_GetStringFromObj( objv[1], NULL );

    if ( Tcl_StringMatch(command, "reference") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "reference" );
            return TCL_ERROR;
        }
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for VertexQueue object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
Neuron_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 2 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    Neuron *q = new Neuron();

    Tcl_CreateObjCommand( interp, name, Neuron_obj, (ClientData)q, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
    return TCL_OK;
}


/**
 */
int
Dendrite_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    Dendrite *q = (Dendrite *)data;

    if ( objc < 2 || objc > 3 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "command [value]" );
        return TCL_ERROR;
    }
    char *command = Tcl_GetStringFromObj( objv[1], NULL );

    if ( Tcl_StringMatch(command, "reference") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "reference" );
            return TCL_ERROR;
        }
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for VertexQueue object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
Dendrite_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 2 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    Dendrite *q = new Dendrite();

    Tcl_CreateObjCommand( interp, name, Dendrite_obj, (ClientData)q, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
    return TCL_OK;
}


/**
 */
static bool
ANN_Module( Tcl_Interp *interp ) {
    Tcl_Command command;

    command = Tcl_CreateObjCommand(interp, "Perceptron", Perceptron_cmd, (ClientData)0, NULL);
    if ( command == NULL )  return false;

    command = Tcl_CreateObjCommand(interp, "Layer",      Layer_cmd,      (ClientData)0, NULL);
    if ( command == NULL )  return false;

    command = Tcl_CreateObjCommand(interp, "Neuron",     Neuron_cmd,     (ClientData)0, NULL);
    if ( command == NULL )  return false;

    command = Tcl_CreateObjCommand(interp, "Dendrite",   Dendrite_cmd,   (ClientData)0, NULL);
    if ( command == NULL )  return false;

    return true;
}

app_init( ANN_Module );

/* vim: set autoindent expandtab sw=4 : */
