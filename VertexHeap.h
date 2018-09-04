
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

#include "VertexComparator.h"

#ifndef _VERTEXHEAP_H_
#define _VERTEXHEAP_H_

class Vertex;
class VertexList;

class VertexHeap {
protected:
    int capacity;
    int size;
    Vertex **items;
public:
    VertexHeap();
    virtual ~VertexHeap();
};

class VertexMinHeap : public VertexHeap {
private:
    VertexComparator compare;

    int last_index() const;
    bool has_left_child( int ) const;
    bool has_right_child( int ) const;
    bool has_parent( int ) const;
    Vertex * left_child( int ) const;
    Vertex * right_child( int ) const;
    Vertex * parent( int ) const;
    void swap( int, int ) const;
    void sift();
    void bubble();
public:
    VertexMinHeap( VertexComparator );
    virtual ~VertexMinHeap();

    void add( Vertex *vertex );
    Vertex * delete_min();
    bool is_empty();
    bool not_empty();
};

#endif

/* vim: set autoindent expandtab sw=4 : */
