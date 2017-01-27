
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

#include <unistd.h>
#include <string>

#include "PointCut.h"
#include "Aspect.h"

#ifndef _EDGELIST_H_
#define _EDGELIST_H_

class Edge;

typedef Edge *EdgeTransform( Edge * );
typedef bool EdgePredicate( Edge * );
typedef long EdgeReducer( long, Edge * );

/**
 * TODO - make members private and close the interface
 */
class EdgeList {
public:
    Edge *edge;
    EdgeList *next;
    EdgeList *previous;
    EdgeList( Edge *edge, EdgeList *next = 0 );
    virtual ~EdgeList();
    EdgeList * map( EdgeTransform * );
    EdgeList * filter( EdgePredicate * );
    long reduce( long initial, EdgeReducer *reducer );
    void destroy();
};

#endif

/* vim: set autoindent expandtab sw=4 : */
