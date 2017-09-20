
#include <stdio.h>
#include <node.h>

#include "Node_Vertex.h"
#include "Node_Edge.h"
#include "Node_Graph.h"

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Value;

using node::AtExit;

static void
at_exit_cb1( void* arg ) {
  Isolate* isolate = static_cast<Isolate*>(arg);
  HandleScope scope(isolate);
  Local<Object> obj = Object::New(isolate);
  assert(!obj.IsEmpty()); // assert VM is still alive
  assert(obj->IsObject());

  fprintf( stderr, "at exit callback\n" );
}

void init( Local<Object> exports ) {
  GraphProxy::Init( exports );
  EdgeProxy::Init( exports );
  VertexProxy::Init( exports );
  AtExit(at_exit_cb1, exports->GetIsolate());
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

/* vim: set autoindent expandtab sw=4 : */
