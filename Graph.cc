
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

#include "Graph.h"
#include "VertexList.h"
#include "VertexQueue.h"

/**
 */
Edge::Edge( Vertex *vertex )
  : vertex(vertex), next(0), _weight(0)
{ }

Edge::~Edge() {
}

void Edge::visit() {
    pointcut._visit_();
}

void
Edge::weight( int value ) {
    _weight = value;
}

int
Edge::weight() {
    return _weight;
}

/**
 */
Vertex::Vertex()
    : edge(0), tedge(0), parent(0),
      discovered(false), explored(false),
      distance(0), finished(0)
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
    pointcut._visit_();
}

void Vertex::reset() {
    discovered = false;
    explored   = false;
    distance = 0;
    finished = 0;
    parent = NULL;
}

Edge *
Vertex::connect( Vertex *v ) {
    Edge *e = new Edge( v );
    e->next = edge;
    edge = e;
    return e;
}

/**
 */
Graph::Graph() : Aspect(), tick(0), vertices(0) { }

Graph::~Graph() {
    vertices->destroy();
    delete vertices;
}

void Graph::add( Vertex *vertex ) {
    vertices = new VertexList( vertex, vertices );
}

void Graph::reset() {
    VertexList *list = vertices;

    while ( list != NULL ) {
        list->vertex->reset();
        list = list->next;
    }

    acyclic = true;
    tick = 0;
}

void Graph::BFS() {
    reset();

    for ( VertexList *v = vertices ; v != NULL ; v = v->next ) {
        if ( v->vertex->discovered ) continue;
        BFS( v->vertex );
    }
}

/**
 * The following represents the colors:
 *
 *         discovered  explored
 * White    false       false
 * Gray     true        false
 * Black    true        true
 */
void Graph::BFS( Vertex *start ) {
    VertexQueue q;

    start->discovered = true;
    q.enqueue( start );

    while ( q.not_empty() ) {
        Vertex *u = q.dequeue();

        u->pointcut._enter_();
        u->visit();

        for ( Edge *edge = u->edge ; edge != NULL ; edge = edge->next ) {
            edge->pointcut._enter_();
            edge->visit();

            Vertex *v = edge->vertex;

            if ( v->discovered ) {
                edge->pointcut._leave_();
                continue;
            }

            v->discovered = true;
            v->distance = u->distance + 1;
            v->parent = u;
            q.enqueue( v );

            edge->pointcut._leave_();
        }

        u->explored = true;
        u->pointcut._leave_();
    }
}

void Graph::DFS() {
    reset();

    for ( VertexList *v = vertices ; v != NULL ; v = v->next ) {
        if ( v->vertex->discovered ) continue;
        DFS( v->vertex );
    }
}

void Graph::DFS( Vertex *u ) {
    tick += 1;

    u->pointcut._enter_();

    u->discovered = true;
    u->distance = tick;
    u->visit();

    for ( Edge *edge = u->edge ; edge != NULL ; edge = edge->next ) {
        edge->pointcut._enter_();
        edge->visit();

        Vertex *v = edge->vertex;

        if ( v->discovered ) {
            if ( v->explored == false ) {
                // This is a back edge
                cout << "Back edge found {" << dec << u->id()
                     << "," << dec << v->id() << "}" << endl;
                acyclic = false;
            }
            edge->pointcut._leave_();
            continue;
        }

        v->parent = u;
        DFS( v );
        edge->pointcut._leave_();
    }

    u->explored = true;
    u->finished = tick;
    u->pointcut._leave_();
}

VertexList *
Graph::TSort() {
    reset();
    // what about the other roots
    return TSort(vertices->vertex, 0);
}

VertexList *
Graph::TSort( Vertex *u, VertexList *list ) {
    if ( u == 0 ) {
        // generate some error
        return 0;
    }

    acyclic = true;

    u->pointcut._enter_();

    u->discovered = true;
    u->visit();

    for ( Edge *edge = u->edge ; edge != 0 ; edge = edge->next ) {
        edge->pointcut._enter_();
        edge->visit();

        Vertex *v = edge->vertex;

        if ( v->discovered ) {
            if ( v->explored == false ) {
                // This is a back edge
                cout << "Back edge found {" << dec << u->id()
                     << "," << dec << v->id() << "}" << endl;
                acyclic = false;
            }
            edge->pointcut._leave_();
            continue;
        }
        v->parent = u;
        list = TSort( v, list );
        edge->pointcut._leave_();
    }

    u->explored = true;
    u->pointcut._leave_();

    return new VertexList( u, list );
}

/* vim: set autoindent expandtab sw=4 : */
