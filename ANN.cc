
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
#include "ANN.h"

/**
 * Incoming
 * Axon would be outgoing
 */
Dendrite::Dendrite()
  : Edge()
{ }

/**
 */
Dendrite::Dendrite( Neuron *neuron )
  : Edge(neuron)
{ }

Dendrite::~Dendrite() {
}

/**
 */
Neuron::Neuron()
    : Vertex()
{
}

Neuron::~Neuron() {
}

/**
 */
Layer::Layer() : Graph() { }

Layer::~Layer() {
}

void *
_connect( void *parent, Vertex *child ) {
    Vertex *_parent = (Vertex *)parent;
    _parent->connect( child );
    return parent;
}

bool
Layer::connect( Layer *target ) {
    for ( VertexList *v = vertices ; v != NULL ; v = v->next ) {
        // target->vertices->reduce( v->vertex, _connect );
    }
    return true;
}

/**
 */
Perceptron::Perceptron() {
    // Construct layers
}

Perceptron::~Perceptron() {
}

/* vim: set autoindent expandtab sw=4 : */
