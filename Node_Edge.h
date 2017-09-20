
#include <node.h>
#include <node_object_wrap.h>

#include "Graph.h"

#ifndef _NODE_EDGE_H_
#define _NODE_EDGE_H_

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

class EdgeProxy : public node::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    inline double val() const { return value; }
private:
    explicit EdgeProxy(double value = 0);
    virtual ~EdgeProxy();
    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;
    Edge *edge;
    double value;
};

#endif

/* vim: set autoindent expandtab sw=4 : */
