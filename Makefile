
default: test

PACKAGE = graph-anim
PWD := $(shell pwd)
OS := $(shell uname -s)
include Makefiles/$(OS).mk

CXXFLAGS += -Iinclude/$(OS) -Iinclude/Generic
CXXFLAGS += -g

OBJS =
OBJS += PointCut.o
OBJS += Advice.o
OBJS += TCLTraceAdvice.o
OBJS += Aspect.o
OBJS += EdgeList.o
OBJS += VertexList.o
OBJS += VertexQueue.o
OBJS += VertexReducers.o
OBJS += Graph.o
OBJS += ANN.o
OBJS += TCL_Graph.o
OBJS += AppInit.o

tk_graph: $(OBJS) tk_graph.o

	$(CXX) -o $@ $^ -ltcl -ltk

graph: $(OBJS) shell.o
	$(CXX) -o $@ $^ -ltcl

# Add .d dependencies

Aspect.o Graph.o : Aspect.h
PointCut.o : PointCut.h
VertexList.o : VertexList.h
VertexQueue.o : VertexQueue.h
Graph.o : Graph.h
ANN.o : ANN.h

test: graph
	./graph tests/simple.tcl
	./graph tests/vertexlist.tcl
	./graph tests/tsort.tcl

tk_test: graph
	./tk_graph g.tcl

clean:
	rm -f *.o graph tk_graph
