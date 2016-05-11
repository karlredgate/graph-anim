
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

#include "Advice.h"

#ifndef _POINTCUT_H_
#define _POINTCUT_H_

class AdviceList;

/**
 * PointCut defines the list of "join points" or places
 * in the program flow that "advice" will be called.  The
 * "advice" is a function that is called at that join point.
 *
 * This PointCut object contains a list of Advice objects
 * that each have calls for the specific join point.
 */
class PointCut {
private:
    AdviceList *advisors;

public:
    PointCut();
    virtual ~PointCut();

    virtual void _enter_();
    virtual void _leave_();
    virtual void _visit_();

    void insert( Advice *advice );
};

#endif

/* vim: set autoindent expandtab sw=4 : */
