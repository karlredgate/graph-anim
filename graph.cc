
#include <iostream>
using namespace std;

#include "graph.h"

int Vertex::serial = 0;

Vertex::Vertex( Tcl_Interp *interp )
    : Traced(interp), next(0), edge(0), parent(0)
{
    serialize();
}

void Vertex::visit() {
    _visit_();
}

void Vertex::reset() {
    discovered = false;
    explored   = false;
}

Edge *
Vertex::connect( Vertex *v ) {
    Edge *e = new Edge( interp, v );
    e->next = edge;
    edge = e;
    return e;
}

void Edge::visit() {
    _visit_();
}

void Graph::add( Vertex *vertex ) {
    vertex->next = vertices;
    vertices = vertex;
}

void Graph::reset() {
    Vertex *v = vertices;
    while ( v != 0 ) {
        v->reset();
        v = v->next;
    }
}

void Graph::DFS( Vertex *u ) {
    acyclic = true;
    u->_enter_();
    u->discovered = true;
    u->visit();
    for ( Edge *edge = u->edge ; edge != 0 ; edge = edge->next ) {
	edge->_enter_();
	edge->_visit_();
        Vertex *v = edge->vertex;
        if ( v->discovered ) {
	    if ( v->explored == false ) {
		// This is a back edge
		cout << "Back edge found {" << dec << u->id
		     << "," << dec << v->id << "}" << endl;
		acyclic = false;
	    }
	    edge->_leave_();
	    continue;
	}
        v->parent = u;
        DFS( v );
	edge->_leave_();
    }
    u->explored = true;
    u->_leave_();
}

VertexList *
Graph::TSort( Vertex *u ) {
    VertexList *list = 0;

    acyclic = true;
    u->_enter_();
    u->discovered = true;
    u->visit();
    for ( Edge *edge = u->edge ; edge != 0 ; edge = edge->next ) {
	edge->_enter_();
	edge->_visit_();
        Vertex *v = edge->vertex;
        if ( v->discovered ) {
	    if ( v->explored == false ) {
		// This is a back edge
		cout << "Back edge found {" << dec << u->id
		     << "," << dec << v->id << "}" << endl;
		acyclic = false;
	    }
	    edge->_leave_();
	    continue;
	}
        v->parent = u;
        list = TSort( v );
	edge->_leave_();
    }
    u->explored = true;
    u->_leave_();
    return new VertexList( u, list );
}
