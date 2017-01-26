
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

#include "VertexList.h"
#include "Graph.h"


/**
 */
VertexList::VertexList( Vertex *vertex, VertexList *next )
 : vertex(vertex), next(next), previous(0)
{
    if ( next == 0 ) return;
    next->previous = this;
}

/**
 * Deleting the VertexList just deletes the list, not the
 * vertices contained in the list.
 */
VertexList::~VertexList() {
    if ( next != 0 ) delete next;
}

/**
 */
void
VertexList::destroy() {
    if ( next != 0 ) next->destroy();
    delete vertex;
}

/**
 */
void
VertexList::each( VertexTransform *transform ) {
    // don't really want this - transform needs to create a new object
    // this should not
    transform( this->vertex );
    if ( next != 0 ) next->each( transform );
}

/**
 * This one needs a copy constructor.  But what does that mean for
 * a vertex that contains nothing.
 */
VertexList *
VertexList::map( VertexTransform *transform ) {
    VertexList *that = NULL;
    // that = this->clone();
    transform( that->vertex );
    if ( next != 0 ) {
        that->next = NULL;
    }
    return that;
}

/**
 * Return a list of vertices for which predicate evaluates to true.
 * The vertices are not cloned, they are linked in the new list.
 * The list is a new list.
 */
VertexList *
VertexList::filter( VertexPredicate *predicate ) {
    VertexList *dot = this;

    if ( dot == NULL ) return NULL;
    if ( dot->next == NULL ) {
        if ( predicate(dot->vertex) == false ) return NULL;
        return new VertexList( dot->vertex );
    }
    VertexList *that = dot->next->filter( predicate );
    if ( predicate(dot->vertex) == false ) return that;
    return new VertexList( dot->vertex, that );
}

/**
 */
long
VertexList::reduce( long initial, VertexReducer *reducer ) {
    VertexList *dot = this;
    while ( dot != NULL ) {
        initial += reducer( initial, dot->vertex );
        dot = dot->next;
    }
    return initial;
}

/* vim: set autoindent expandtab sw=4 : */
