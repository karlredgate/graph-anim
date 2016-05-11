
CXXFLAGS += -g

OBJS =
OBJS += PointCut.o
OBJS += Advice.o
OBJS += TCLTraceAdvice.o
OBJS += Aspect.o
OBJS += Traced.o
OBJS += Graph.o
OBJS += test.o

graph: $(OBJS)
	$(CXX) -o $@ $^ -ltcl -ltk

test: graph
	./graph g.tcl

clean:
	rm *.o graph
