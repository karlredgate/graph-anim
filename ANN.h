
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

#include "Graph.h"

#ifndef _NEURALNET_H_
#define _NEURALNET_H_

/**
 */
class Neuron : public Vertex {
public:
    Neuron();
    virtual ~Neuron();
};

/**
 * dendrite is incoming, axon would be outgoing.
 * But an axon output should go to multiple and there is a single axon
 */
class Dendrite : public Edge {
public:
    Dendrite();
    Dendrite( Neuron * );
    virtual ~Dendrite();
};

/**
 */
class Layer : public Graph {
public:
    bool connect( Layer * );
    Layer();
    Layer( int );
    virtual ~Layer();
};

/**
 */
class Perceptron {
private:
    Layer *in;
    Layer *hidden;
    Layer *out;
public:
    Perceptron();
    virtual ~Perceptron();
};

#endif

/* vim: set autoindent expandtab sw=4 : */
