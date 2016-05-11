
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

#include "Advice.h"
#include "PointCut.h"

class AdviceList {
public:
    Advice *advisor;
    AdviceList *next;

    AdviceList( Advice *advisor, AdviceList *next )
    : advisor(advisor), next(next) { }

    ~AdviceList() {
        if ( next    != NULL ) delete next;
        if ( advisor != NULL ) delete advisor;
    }
};

PointCut::PointCut() : advisors(NULL) {
}

PointCut::~PointCut() {
    if ( advisors != NULL ) delete advisors;
}

void
PointCut::insert( Advice *advisor ) {
    AdviceList *cons = new AdviceList( advisor, advisors );
    advisors = cons;
}

void
PointCut::_enter_() {
    for ( AdviceList *element = advisors ; element != NULL ; element = element->next ) {
        element->advisor->_enter_();
    }
}

void
PointCut::_leave_() {
    for ( AdviceList *element = advisors ; element != NULL ; element = element->next ) {
        element->advisor->_leave_();
    }
}

void
PointCut::_visit_() {
    for ( AdviceList *element = advisors ; element != NULL ; element = element->next ) {
        element->advisor->_visit_();
    }
}

#if 0
// Change to this - to avoid replication of the for loops
//
int (TMyClass::*pt2ConstMember)(float, char, char) const = NULL;

class TMyClass
{
public:
   int DoIt(float a, char b, char c){ cout << "TMyClass::DoIt"<< endl; return a+b+c;};
   int DoMore(float a, char b, char c) const
         { cout << "TMyClass::DoMore" << endl; return a-b+c; };

   /* more of TMyClass */
};
pt2ConstMember = &TMyClass::DoIt; // note: <pt2Member> may also legally point to &DoMore

// Calling Function using Function Pointer

(*this.*pt2ConstMember)(12, 'a', 'b');
#endif

/* vim: set autoindent expandtab sw=4 : */
