
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

#include "VertexList.h"
#include "VertexQueue.h"


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

bool
VertexQueue::not_empty() {
    return head != 0;
}

/* vim: set autoindent expandtab sw=4 : */
