
default: test

PACKAGE = graph-anim
PWD := $(shell pwd)
OS := $(shell uname -s)
include Makefiles/$(OS).mk

CXXFLAGS += -g

OBJS =
OBJS += PointCut.o
OBJS += Advice.o
OBJS += TCLTraceAdvice.o
OBJS += Aspect.o
OBJS += Graph.o
OBJS += ANN.o

tk_graph: $(OBJS) tk_graph.o

	$(CXX) -o $@ $^ -ltcl -ltk

graph: $(OBJS) shell.o
	$(CXX) -o $@ $^ -ltcl

# Add .d dependencies

Aspect.o Graph.o : Aspect.h
PointCut.o : PointCut.h
ANN.o : ANN.h

test: graph
	./graph tests/simple.tcl

tk_test: graph
	./tk_graph g.tcl

clean:
	rm *.o graph
