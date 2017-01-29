
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

#include "Activations.h"

/**
 */
Activation::Activation( float _threshold )
    : _threshold(_threshold)
{ }

Activation::~Activation() {
}

/**
 */
Step::Step( float lower, float upper )
    : Activation(1), lower(lower), upper(upper)
{ }

Step::~Step() {
}

float
Step::operator () ( float net ) {
    if ( net < threshold() ) return lower;
    return upper;
}

/**
 */
Ramp::Ramp( float epsilon, float lower, float upper )
    : Step(lower,upper), epsilon(epsilon)
{ }

Ramp::~Ramp() {
}

float
Ramp::operator () ( float net ) {
    float x = net - threshold();
    if ( x >= epsilon ) return upper;
    if ( x <= epsilon ) return lower;
    return x;
}

/* vim: set autoindent expandtab sw=4 : */
