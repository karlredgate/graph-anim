
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

#include "EdgeList.h"
#include "Graph.h"


/**
 */
EdgeList::EdgeList( Edge *edge, EdgeList *next )
 : edge(edge), next(next), previous(0)
{
    if ( next == 0 ) return;
    next->previous = this;
}

/**
 * Deleting the EdgeList just deletes the list, not the
 * vertices contained in the list.
 */
EdgeList::~EdgeList() {
    if ( next != 0 ) delete next;
}

/**
 */
void
EdgeList::destroy() {
    if ( next != 0 ) next->destroy();
    delete edge;
}

/**
 * This one needs a copy constructor.  But what does that mean for
 * a edge that contains nothing.
 */
EdgeList *
EdgeList::map( EdgeTransform *transform ) {
    EdgeList *that = NULL;
    // that = this->clone();
    transform( that->edge );
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
EdgeList *
EdgeList::filter( EdgePredicate *predicate ) {
    EdgeList *dot = this;

    if ( dot == NULL ) return NULL;
    if ( dot->next == NULL ) {
        if ( predicate(dot->edge) == false ) return NULL;
        return new EdgeList( dot->edge );
    }
    EdgeList *that = dot->next->filter( predicate );
    if ( predicate(dot->edge) == false ) return that;
    return new EdgeList( dot->edge, that );
}

/**
 */
long
EdgeList::reduce( long initial, EdgeReducer *reducer ) {
    EdgeList *dot = this;

    while ( dot != NULL ) {
        initial = reducer( initial, dot->edge );
        dot = dot->next;
    }

    return initial;
}

/* vim: set autoindent expandtab sw=4 : */
