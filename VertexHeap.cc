
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

#include <stdlib.h>

#include "Graph.h"
#include "VertexComparator.h"
#include "VertexList.h"
#include "VertexHeap.h"

#define CAPACITY 1024

#define LEFT_CHILD_INDEX(parent)   ((parent*2)+1)
#define RIGHT_CHILD_INDEX(parent)  ((parent*2)+2)
#define PARENT_INDEX(child)        ((child-1)>>1)

VertexHeap::VertexHeap()
  : capacity(CAPACITY), size(0)
{
    items = (Vertex **) calloc( capacity, sizeof (Vertex *) );
}

VertexHeap::~VertexHeap() {
    if ( items != 0 ) free(items);
}

VertexMinHeap::VertexMinHeap( VertexComparator compare )
  : VertexHeap(), compare(compare)
{ }

VertexMinHeap::~VertexMinHeap() { }

Vertex *
VertexMinHeap::left_child( int parent ) const {
    return items[ LEFT_CHILD_INDEX(parent) ];
}

Vertex *
VertexMinHeap::right_child( int parent ) const {
    return items[ RIGHT_CHILD_INDEX(parent) ];
}

Vertex *
VertexMinHeap::parent( int parent ) const {
    return items[ PARENT_INDEX(parent) ];
}

int
VertexMinHeap::last_index() const {
    return size - 1;
}

bool
VertexMinHeap::has_left_child( int parent ) const {
    return LEFT_CHILD_INDEX(parent) < size;
}

bool
VertexMinHeap::has_right_child( int parent ) const {
    return RIGHT_CHILD_INDEX(parent) < size;
}

bool
VertexMinHeap::has_parent( int child ) const {
    return child > 0;
}

void
VertexMinHeap::swap( int i, int j ) const {
    Vertex *tmp = items[ i ];
    items[ i ] = items [ j ];
    items[ j ] = tmp;
}

void
VertexMinHeap::sift() {
    int index = 0;

    while ( has_left_child(index) ) {
        int child = LEFT_CHILD_INDEX(index);
        if ( has_right_child(index) ) {
            int right = RIGHT_CHILD_INDEX( index );
            if ( compare(items[right], items[child]) < 0 ) child = right;
        }
        if ( compare(items[index], items[child]) < 0 ) return;
        swap( index, child );
        index = child;
    }
}

void
VertexMinHeap::bubble() {
    int index = last_index();

    while ( has_parent(index) ) {
        int parent = PARENT_INDEX( index );
        if ( compare(items[parent], items[index]) < 1 ) return; // <=
        swap( parent, index );
        index = parent;
    }
}

void
VertexMinHeap::add( Vertex *vertex ) {
    items[size++] = vertex;
    bubble();
}

Vertex *
VertexMinHeap::delete_min() {
    if ( size == 0 ) return NULL;
    Vertex *vertex = items[0];
    items[0] = items[ --size ];
    sift();
    return vertex;
}

bool
VertexMinHeap::is_empty() {
    return size == 0;
}

bool
VertexMinHeap::not_empty() {
    return size != 0;
}

/* vim: set autoindent expandtab sw=4 : */
