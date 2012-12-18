
#include <unistd.h>
#include <string>
#include <tcl.h>

class Traced {
    void _call_hook( Tcl_Obj *hook ) {
	if ( interp == 0 ) return;
	if ( hook == 0 ) return;
	Tcl_EvalObjEx( interp, hook, TCL_EVAL_GLOBAL );
	while ( Tcl_DoOneEvent(TCL_ALL_EVENTS|TCL_DONT_WAIT) ) ;
	Tcl_Sleep( 200 );
    }
public:
    Tcl_Interp *interp;
    Tcl_Obj *enter_hook;
    Tcl_Obj *leave_hook;
    Tcl_Obj *visit_hook;

    // Traced() : interp(0), enter_hook(0), leave_hook(0), visit_hook(0) {}
    Traced( Tcl_Interp *interp ) : interp(interp) {
	_enter_( "puts {ENTER}\n" );
	_leave_( "puts {LEAVE}\n" );
	_visit_( "puts {VISIT}\n" );
    }
    ~Traced() {}

    void _enter_() { _call_hook( enter_hook ); }
    void _leave_() { _call_hook( leave_hook ); }
    void _visit_() { _call_hook( visit_hook ); }

    void _enter_( Tcl_Obj *obj ) {
	enter_hook = obj;
	Tcl_IncrRefCount( enter_hook );
    }
    void _leave_( Tcl_Obj *obj ) {
	leave_hook = obj;
	Tcl_IncrRefCount( leave_hook );
    }
    void _visit_( Tcl_Obj *obj ) {
	visit_hook = obj;
	Tcl_IncrRefCount( visit_hook );
    }

    void _enter_( char *script ) {
	_enter_( Tcl_NewStringObj(script, -1) );
    }
    void _leave_( char *script ) {
	_leave_( Tcl_NewStringObj(script, -1) );
    }
    void _visit_( char *script ) {
	_visit_( Tcl_NewStringObj(script, -1) );
    }

    void _interp_( Tcl_Interp *_ ) { interp = _; }
};

class Vertex;
class Edge;

class Edge : public Traced {
public:
    Vertex *vertex;
    Edge *next;
    int weight;

    Edge( Tcl_Interp *interp, Vertex *vertex = 0 )
    : Traced(interp), vertex(vertex), next(0), weight(0) {}
    ~Edge() {}

    virtual void visit();
};

class Vertex : public Traced {
public:
    Vertex *next;
    Edge *edge;
    Vertex *parent;
    bool discovered, explored;
    // std::string name;

    static int serial;
    int id;
    int serialize() { return id = serial++; }

    Vertex( Tcl_Interp * );
    ~Vertex() {}

    virtual void visit();
    void reset();
    Edge * connect( Vertex * );
};

class VertexList {
public:
    Vertex *vertex;
    VertexList *next;
    VertexList( Vertex *vertex, VertexList *next = 0 )
    : vertex(vertex), next(next) {}
    ~VertexList() {
	if ( next != 0 ) delete next;
    }
};

class Graph {
public:
    Tcl_Interp *interp;
    Vertex *vertices;
    bool acyclic;

    Graph( Tcl_Interp *interp ) : interp(interp), vertices(0) {}
    ~Graph() {}

    void add( Vertex * );
    void reset();
    void DFS( Vertex * );
    VertexList *TSort( Vertex * );
};

class MaxHeap {
public:
    class Element {
    public:
	int key;
	Vertex *vertex;
        Element( Vertex *vertex ) : vertex(vertex) {}
    };
    Element **elements;

    MaxHeap( int size ) {
        elements = new Element *[size];
    }
};
