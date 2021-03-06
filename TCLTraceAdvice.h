
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

#include "Advice.h"

#ifndef _TCLTRACEADVICE_H_
#define _TCLTRACEADVICE_H_

class TCLTraceAdvice : public Advice {
    Tcl_Interp *interp;
    Tcl_Obj *enter_hook;
    Tcl_Obj *leave_hook;
    Tcl_Obj *visit_hook;
    void _call_hook( Tcl_Obj *hook );

public:
    TCLTraceAdvice( Tcl_Interp *interp );
    virtual ~TCLTraceAdvice();

    virtual void _enter_();
    virtual void _leave_();
    virtual void _visit_();

    void _enter_( Tcl_Obj *obj );
    void _leave_( Tcl_Obj *obj );
    void _visit_( Tcl_Obj *obj );

    void _enter_( const char *script );
    void _leave_( const char *script );
    void _visit_( const char *script );

    void _interp_( Tcl_Interp *_ );
};

#endif

/* vim: set autoindent expandtab sw=4 : */
