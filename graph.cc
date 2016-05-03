
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
Graph::TSort() {
    reset();
    return TSort(root, 0);
}

VertexList *
Graph::TSort( Vertex *u, VertexList *list ) {
    if ( u == 0 ) {
	// generate some error
        return 0;
    }

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
        list = TSort( v, list );
	edge->_leave_();
    }
    u->explored = true;
    u->_leave_();
    return new VertexList( u, list );
}

Graph::~Graph() {
    Vertex *v = vertices;
    while ( v ) {
        Vertex *u = v->next;
	delete v;
	v = u;
    }
}
