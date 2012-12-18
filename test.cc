
#include <iostream>
#include <tcl.h>
#include <tk.h>
#if 0
#include <tix.h>
#endif

#include "graph.h"

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

    if ( Tcl_StringMatch(command, "enter") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "enter script" );
            return TCL_ERROR;
        }
        e->_enter_( objv[2] );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "leave") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "leave script" );
            return TCL_ERROR;
        }
        e->_leave_( objv[2] );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "visit") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "visit script" );
            return TCL_ERROR;
        }
        e->_visit_( objv[2] );
        return TCL_OK;
    }

    Tcl_SetResult( interp, "Unknown command for edge", TCL_STATIC );

    return TCL_OK;
}


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
        Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(u->id)) );
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
	Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)(u->id)) );
	Tcl_AppendObjToObj( result, Tcl_NewStringObj(",",-1) );
	Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)(v->id)) );
	char *edge_name = Tcl_GetString(result);
        Tcl_CreateObjCommand( interp, edge_name, edge_obj, (ClientData)e, 0 );
	Tcl_ResetResult( interp );
	Tcl_SetObjResult( interp, result );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "enter") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "enter script" );
            return TCL_ERROR;
        }
        u->_enter_( objv[2] );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "leave") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "leave script" );
            return TCL_ERROR;
        }
        u->_leave_( objv[2] );
        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "visit") ) {
        if ( objc != 3 ) {
            Tcl_ResetResult( interp );
            Tcl_WrongNumArgs( interp, 1, objv, "visit script" );
            return TCL_ERROR;
        }
        u->_visit_( objv[2] );
        return TCL_OK;
    }

    Tcl_SetResult( interp, "Unknown command for vertex", TCL_STATIC );

    return TCL_OK;
}

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
        Vertex *v = new Vertex( interp );
        g->add( v );

	Tcl_Obj *result;
	result = Tcl_NewStringObj( "vertex", -1 );
	Tcl_AppendObjToObj( result, Tcl_NewLongObj((long)(v->id)) );
	char *name = Tcl_GetString(result);
        Tcl_CreateObjCommand( interp, name, vertex_obj, (ClientData)v, 0 );
	Tcl_ResetResult( interp );
	Tcl_SetObjResult( interp, result );

        return TCL_OK;
    }

    if ( Tcl_StringMatch(command, "DFS") ) {
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
            Tcl_SetResult( interp, "acyclic", TCL_STATIC );
	} else {
            Tcl_SetResult( interp, "cyclic", TCL_STATIC );
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
        VertexList *list = g->TSort( v );
	if ( g->acyclic == false ) {
            Tcl_SetResult( interp, "cycle detected", TCL_STATIC );
	    return TCL_ERROR;
	}
        return TCL_OK;
    }

    Tcl_SetResult( interp, "Unknown command for graph object", TCL_STATIC );
    return TCL_OK;
}

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

    Graph *g = new Graph( interp );
    Tcl_CreateObjCommand( interp, name, graph_obj, (ClientData)g, 0 );
    Tcl_SetObjResult( interp, Tcl_NewLongObj((long)(g)) );
    return TCL_OK;
}

static int Graph_Init( Tcl_Interp *interp ) {
    if (Tcl_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }
    if (Tk_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }
#if 0
    if (Tix_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }
#endif
    Tcl_StaticPackage(interp, "Tk", Tk_Init, Tk_SafeInit);

    Tcl_CreateObjCommand(interp, "graph",  graph_cmd,  (ClientData)0, NULL);

    Tcl_SetVar(interp, "tcl_rcFileName", "~/.graphrc", TCL_GLOBAL_ONLY);
    return TCL_OK;
}

int main( int argc, char **argv ) {
    Tk_Main( argc, argv, Graph_Init );
}
