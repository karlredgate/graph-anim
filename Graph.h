
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

#ifndef _GRAPH_H_
#define _GRAPH_H_

class Vertex;
class VertexList;
class VertexQueue;
class Edge;
class EdgeList;

class Edge : public Aspect {
private:
    int _weight;
public:
    Vertex *vertex;
    Edge *next;

    Edge( Vertex *vertex = 0 );
    virtual ~Edge();

    virtual void visit();
    void weight( int value );
    int weight();
};

/**
 * tedge - is the transposed edges, use to generate graph Gt
 */
class Vertex : public Aspect {
private:
    static int serial;
    int serialize();
    int _id;

public:
    EdgeList *edges;
    Edge *tedge;
    Vertex *parent;
    bool discovered, explored;
    int distance;
    int finished;

    Vertex();
    virtual ~Vertex();

    int id() const;
    virtual void visit();
    void reset();
    Edge * connect( Vertex * );
};

class Graph : public Aspect {
private:
    int tick;

public:
    VertexList *vertices;
    bool acyclic;

    Graph();
    virtual ~Graph();

    void add( Vertex * );
    void reset();

    void BFS();
    void BFS( Vertex * );

    void DFS();
    void DFS( Vertex * );

    VertexList *TSort( Vertex *, VertexList * );
    VertexList *TSort();
};

#endif

/* vim: set autoindent expandtab sw=4 : */
