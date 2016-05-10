
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

#include "Traced.h"
#include "Graph.h"

/**
 */
Edge::Edge( Tcl_Interp *interp, Vertex *vertex )
  : Traced(interp), vertex(vertex), next(0), weight(0)
{ }

Edge::~Edge() {
}

void Edge::visit() {
    _visit_();
}

/**
 */
Vertex::Vertex( Tcl_Interp *interp )
    : Traced(interp), next(0), edge(0), parent(0)
{
    serialize();
}

Vertex::~Vertex() {
    if ( edge != 0 ) delete edge;
}

int Vertex::serial = 0;

int
Vertex::serialize() {
    return _id = serial++;
}

int
Vertex::id() const {
    return _id;
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

/**
 */
VertexList::VertexList( Vertex *vertex, VertexList *next )
 : vertex(vertex), next(next), previous(0)
{
    if ( next == 0 ) return;
    next->previous = this;
}

/**
 */
VertexList::~VertexList() {
    if ( next != 0 ) delete next;
}

VertexQueue::VertexQueue()
  : head(0), tail(0)
{ }

VertexQueue::~VertexQueue() {
    if ( head != 0 ) delete head;
}

void
VertexQueue::enqueue( Vertex *vertex ) {
    VertexList *list = new VertexList( vertex, head );
    head = list;
    if ( tail == 0 ) tail = head;
}

Vertex *
VertexQueue::dequeue() {
    if ( is_empty() ) return 0;

    VertexList *last = tail;

    if ( head == tail ) {
        head = 0;
        tail = 0;
        goto done;
    }

    tail = last->previous;
    tail->next = 0;
    last->previous = 0;

done:
    Vertex *v = last->vertex;
    last->next = 0;
    delete last;

    return v;
}

bool
VertexQueue::is_empty() {
    return head == 0;
}

/**
 */
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

    acyclic = true;
}

void Graph::traverse_edges( Vertex *u ) {
    acyclic = true;
}

void Graph::DFS( Vertex *u ) {
    u->_enter_();
    u->discovered = true;
    u->visit();

    for ( Edge *edge = u->edge ; edge != NULL ; edge = edge->next ) {
        edge->_enter_();
        edge->_visit_();
        Vertex *v = edge->vertex;

        if ( v->discovered ) {
            if ( v->explored == false ) {
                // This is a back edge
                cout << "Back edge found {" << dec << u->id()
                     << "," << dec << v->id() << "}" << endl;
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
                cout << "Back edge found {" << dec << u->id()
                     << "," << dec << v->id() << "}" << endl;
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

/* vim: set autoindent expandtab sw=4 : */
