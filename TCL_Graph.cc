
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

#include "Graph.h"
#include "VertexList.h"
#include "VertexQueue.h"

#include "TCLTraceAdvice.h"
#include "AppInit.h"

/**
 */
int
edge_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    Edge *e = (Edge *)data;

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
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(e)) );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "advice") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "advice [objref]" );
            return TCL_ERROR;
        }

        TCLTraceAdvice *advice;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(advice)) != TCL_OK ) {
            return TCL_ERROR;
        }

        e->insert( advice );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for edge", TCL_STATIC );

    return TCL_OK;
}

/**
 */
int
vertex_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    Vertex *u = (Vertex *)data;

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
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(u)) );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "id") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "id" );
            return TCL_ERROR;
        }
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)( u->id() )) );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "connect") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "connect value" );
            return TCL_ERROR;
        }
        Vertex *v;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(v)) != TCL_OK ) {
            return TCL_ERROR;
        }
        Edge *e = u->connect( v );
        Tcl_Obj *result;
        result = Tcl_NewStringObj( "edge", -1 );
        Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)( u->id() )) );
        Tcl_AppendObjToObj( result, Tcl_NewStringObj(",",-1) );
        Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)( v->id() )) );
        char *edge_name = Tcl_GetString(result);
        Tcl_CreateObjCommand( interp, edge_name, edge_obj, (ClientData)e, 0 );
        Tcl_ResetResult( interp );
        Tcl_SetObjResult( interp, result );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "advice") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "advice [objref]" );
            return TCL_ERROR;
        }

        TCLTraceAdvice *advice;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(advice)) != TCL_OK ) {
            return TCL_ERROR;
        }

        u->insert( advice );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for vertex [reference id connect advice]", TCL_STATIC );

    return TCL_OK;
}

/**
 */
int
vertex_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 1 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "" );
        return TCL_ERROR;
    }

    Vertex *v = new Vertex();

    Tcl_Obj *result;
    result = Tcl_NewStringObj( "vertex", -1 );
    Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)( v->id() )) );

    char *name = Tcl_GetString(result);
    Tcl_CreateObjCommand( interp, name, vertex_obj, (ClientData)v, 0 );
    Tcl_ResetResult( interp );
    Tcl_SetObjResult( interp, result );

    return TCL_OK;
}

/**
 */
int
graph_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    Graph *g = (Graph *)data;

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
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(g)) );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "vertex") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "vertex" );
            return TCL_ERROR;
        }
        Vertex *v = new Vertex();
        g->add( v );

        Tcl_Obj *result;
        result = Tcl_NewStringObj( "vertex", -1 );
        Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)( v->id() )) );
        char *name = Tcl_GetString(result);
        Tcl_CreateObjCommand( interp, name, vertex_obj, (ClientData)v, 0 );
        Tcl_ResetResult( interp );
        Tcl_SetObjResult( interp, result );

        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "DFS") ) {
        if ( objc == 2 ) {
            g->DFS();
            return TCL_OK;
        }

        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "DFS vertex" );
            return TCL_ERROR;
        }
        Vertex *v;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(v)) != TCL_OK ) {
            return TCL_ERROR;
        }
        g->reset();
        g->DFS( v );
        if ( g->acyclic ) {
            Tcl_SetResult( interp, (char *)"acyclic", TCL_STATIC );
        } else {
            Tcl_SetResult( interp, (char *)"cyclic", TCL_STATIC );
        }
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "BFS") ) {
        if ( objc == 2 ) {
            g->BFS();
            return TCL_OK;
        }

        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "BFS vertex" );
            return TCL_ERROR;
        }
        Vertex *v;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(v)) != TCL_OK ) {
            return TCL_ERROR;
        }
        g->reset();
        g->BFS( v );
        if ( g->acyclic ) {
            Tcl_SetResult( interp, (char *)"acyclic", TCL_STATIC );
        } else {
            Tcl_SetResult( interp, (char *)"cyclic", TCL_STATIC );
        }
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "tsort") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "tsort vertex" );
            return TCL_ERROR;
        }
        Vertex *v;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(v)) != TCL_OK ) {
            return TCL_ERROR;
        }
        g->reset();
        VertexList *list = g->TSort( v, 0 );
        // need to return this as a list of the vertices
        // but what - the names are not known, just the addresses

        if ( g->acyclic == false ) {
            Tcl_SetResult( interp, (char *)"cycle detected", TCL_STATIC );
            return TCL_ERROR;
        }

        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for graph object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
graph_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 2 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    Graph *g = new Graph();
    Tcl_CreateObjCommand( interp, name, graph_obj, (ClientData)g, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(g)) );
    return TCL_OK;
}

/**
 */
int
VertexList_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    VertexList *list = (VertexList *)data;

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
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(list)) );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "insert") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "insert [vertex]" );
            return TCL_ERROR;
        }

        Vertex *v;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(v)) != TCL_OK ) {
            return TCL_ERROR;
        }
        VertexList *that = new VertexList( v, list );

        Tcl_Command token = Tcl_GetCommandFromObj( interp, objv[0] );
        Tcl_CmdInfo info;
        if ( Tcl_GetCommandInfoFromToken(token, &info) == 0 ) {
            Tcl_SetResult( interp, (char *)"could not find list", TCL_STATIC );
            return TCL_ERROR;
        }
        info.objClientData = (ClientData)that;
        if ( Tcl_SetCommandInfoFromToken(token, &info) == 0 ) {
            Tcl_SetResult( interp, (char *)"could not update list", TCL_STATIC );
            return TCL_ERROR;
        }

        Tcl_ResetResult( interp );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "map") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "map proc" );
            return TCL_ERROR;
        }

        for ( ; list != NULL ; list = list->next ) {
            Tcl_Command element = Tcl_CreateObjCommand(
                interp, "vertex", vertex_obj, (ClientData)list->vertex, NULL
            );
            Tcl_Obj *arg = Tcl_NewStringObj( "vertex", -1 );
            Tcl_Obj *CONST ov[] = { objv[2], arg };
            Tcl_EvalObjv( interp, 2, ov, 0 );
        }

        Tcl_ResetResult( interp );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "destroy") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "destroy" );
            return TCL_ERROR;
        }

        list->destroy();

        Tcl_ResetResult( interp );
        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for VertexList object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
VertexList_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 2 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    VertexList *list = NULL;

    Tcl_CreateObjCommand( interp, name, VertexList_obj, (ClientData)list, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(list)) );
    return TCL_OK;
}


/**
 */
int
VertexQueue_obj(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    VertexQueue *q = (VertexQueue *)data;

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

    if ( Tcl_StringMatch(command, "enqueue") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "enqueue [vertex]" );
            return TCL_ERROR;
        }

        Vertex *v;
        if ( Tcl_GetLongFromObj(interp,objv[2],(long*)&(v)) != TCL_OK ) {
            return TCL_ERROR;
        }

        q->enqueue( v );

        Tcl_ResetResult( interp );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "dequeue") ) {
        if ( objc != 2 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "vertex" );
            return TCL_ERROR;
        }

        if ( q->is_empty() ) {
            Tcl_SetResult( interp, (char *)"queue is empty", TCL_STATIC );
            return TCL_ERROR;
        }

        Vertex *v = q->dequeue();

        if ( v == 0 ) {
            Tcl_SetResult( interp, (char *)"BUG - queue not empty but queue returned null", TCL_STATIC );
            return TCL_ERROR;
        }

        Tcl_Obj *result;
        result = Tcl_NewStringObj( "vertex", -1 );
        Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)( v->id() )) );

        char *name = Tcl_GetString(result);
        Tcl_CreateObjCommand( interp, name, vertex_obj, (ClientData)v, 0 );
        Tcl_ResetResult( interp );
        Tcl_SetObjResult( interp, result );

        return TCL_OK;
    }

    Tcl_SetResult( interp, (char *)"Unknown command for VertexQueue object", TCL_STATIC );
    return TCL_OK;
}

/**
 */
int
VertexQueue_cmd(
    ClientData data, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]
) {
    if ( objc != 2 ) {
        Tcl_ResetResult( interp );
        Tcl_WrongNumArgs( interp, 1, objv, "name" );
        return TCL_ERROR;
    }
    char *name = Tcl_GetStringFromObj( objv[1], NULL );

    VertexQueue *q = new VertexQueue();

    Tcl_CreateObjCommand( interp, name, VertexQueue_obj, (ClientData)q, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(q)) );
    return TCL_OK;
}


/**
 */
static bool
Graph_Module( Tcl_Interp *interp ) {
    Tcl_Command command;

    command = Tcl_CreateObjCommand(interp, "graph",        graph_cmd,       (ClientData)0, NULL);
    if ( command == NULL )  return false;

    command = Tcl_CreateObjCommand(interp, "vertex",       vertex_cmd,      (ClientData)0, NULL);
    if ( command == NULL )  return false;

    command = Tcl_CreateObjCommand(interp, "VertexQueue",   VertexQueue_cmd,  (ClientData)0, NULL);
    if ( command == NULL )  return false;

    command = Tcl_CreateObjCommand(interp, "VertexList",   VertexList_cmd,  (ClientData)0, NULL);
    if ( command == NULL )  return false;

    return true;
}

app_init( Graph_Module );

/* vim: set autoindent expandtab sw=4 : */
