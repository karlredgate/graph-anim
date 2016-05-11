
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

#include "TCLTraceAdvice.h"

void
TCLTraceAdvice::_call_hook( Tcl_Obj *hook ) {
    if ( interp == 0 ) return;
    if ( hook == 0 ) return;
    Tcl_EvalObjEx( interp, hook, TCL_EVAL_GLOBAL );
    while ( Tcl_DoOneEvent(TCL_ALL_EVENTS|TCL_DONT_WAIT) ) ;
    Tcl_Sleep( 200 );
}

TCLTraceAdvice::TCLTraceAdvice( Tcl_Interp *interp ) : Advice(), interp(interp) {
    _enter_( "puts {ENTER}\n" );
    _leave_( "puts {LEAVE}\n" );
    _visit_( "puts {VISIT}\n" );
}

TCLTraceAdvice::~TCLTraceAdvice() {
}

void
TCLTraceAdvice::_enter_() {
    _call_hook( enter_hook );
}

void
TCLTraceAdvice::_leave_() {
    _call_hook( leave_hook );
}

void
TCLTraceAdvice::_visit_() {
    _call_hook( visit_hook );
}

void
TCLTraceAdvice::_enter_( Tcl_Obj *obj ) {
    enter_hook = obj;
    Tcl_IncrRefCount( enter_hook );
}

void
TCLTraceAdvice::_leave_( Tcl_Obj *obj ) {
    leave_hook = obj;
    Tcl_IncrRefCount( leave_hook );
}

void
TCLTraceAdvice::_visit_( Tcl_Obj *obj ) {
    visit_hook = obj;
    Tcl_IncrRefCount( visit_hook );
}

void
TCLTraceAdvice::_enter_( const char *script ) {
    _enter_( Tcl_NewStringObj(script, -1) );
}

void
TCLTraceAdvice::_leave_( const char *script ) {
    _leave_( Tcl_NewStringObj(script, -1) );
}

void
TCLTraceAdvice::_visit_( const char *script ) {
    _visit_( Tcl_NewStringObj(script, -1) );
}

void
TCLTraceAdvice::_interp_( Tcl_Interp *_ ) {
    interp = _;
}

/* vim: set autoindent expandtab sw=4 : */
