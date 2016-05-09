
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
public:
    Vertex *root;
    Vertex *vertex;
    Edge *next;
    int weight;

    Edge( Tcl_Interp *interp, Vertex *vertex = 0 )
    : Traced(interp), vertex(vertex), next(0), weight(0) {}
    ~Edge() {}

    virtual void visit();
};

class Vertex : public Traced {
public:
    Vertex *next;
    Edge *edge;
    Vertex *parent;
    bool discovered, explored;
    // std::string name;

    static int serial;
    int id;
    int serialize() { return id = serial++; }

    Vertex( Tcl_Interp * );
    ~Vertex() { if ( edge ) delete edge; }

    virtual void visit();
    void reset();
    Edge * connect( Vertex * );
};

class VertexList {
public:
    Vertex *vertex;
    VertexList *next;
    VertexList( Vertex *vertex, VertexList *next = 0 )
    : vertex(vertex), next(next) {}
    ~VertexList() {
        if ( next != 0 ) delete next;
    }
};

class Graph {
private:
    void traverse_paths( Vertex * );
    void traverse_edges( Vertex * );
public:
    Tcl_Interp *interp;
    Vertex *root;
    Vertex *vertices;
    bool acyclic;

    Graph( Tcl_Interp *interp ) : interp(interp), vertices(0) {}
    ~Graph();

    void add( Vertex * );
    void reset();
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