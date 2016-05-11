
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
#include <tcl.h>

#include "Traced.h"

#ifndef _GRAPH_H_
#define _GRAPH_H_

class Vertex;
class Edge;

class Edge : public Traced {
private:
    int _weight;
public:
    Vertex *root;
    Vertex *vertex;
    Edge *next;

    Edge( Tcl_Interp *interp, Vertex *vertex = 0 );
    virtual ~Edge();

    virtual void visit();
    void weight( int value );
    int weight();
};

class Vertex : public Traced {
private:
    static int serial;
    int serialize();
    int _id;

public:
    Vertex *next;
    Edge *edge;
    Vertex *parent;
    bool discovered, explored;
    int distance;
    int finished;

    Vertex( Tcl_Interp * );
    virtual ~Vertex();

    int id() const;
    virtual void visit();
    void reset();
    Edge * connect( Vertex * );
};

/**
 * TODO - make members private and close the interface
 */
class VertexList {
public:
    Vertex *vertex;
    VertexList *next;
    VertexList *previous;
    VertexList( Vertex *vertex, VertexList *next = 0 );
    virtual ~VertexList();
};

class VertexQueue {
private:
    VertexList *head;
    VertexList *tail;
public:
    VertexQueue();
    virtual ~VertexQueue();

    void enqueue( Vertex *vertex );
    Vertex * dequeue();
    bool is_empty();
    bool not_empty();
};

class Graph {
private:
    int tick;
public:
    Tcl_Interp *interp;
    Vertex *root;
    Vertex *vertices;
    bool acyclic;

    Graph( Tcl_Interp *interp );
    virtual ~Graph();

    void add( Vertex * );
    void reset();

    void BFS( Vertex * );
    void BFS();

    void DFS( Vertex * );
    void DFS();

    VertexList *TSort( Vertex *, VertexList * );
    VertexList *TSort();
};

class MaxHeap {
public:
    class Element {
    public:
        int key;
        Vertex *vertex;
        Element( Vertex *vertex ) : vertex(vertex) {}
    };
    Element **elements;

    MaxHeap( int size ) {
        elements = new Element *[size];
    }
};

#endif

/* vim: set autoindent expandtab sw=4 : */
