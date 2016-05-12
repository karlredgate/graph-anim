
CXXFLAGS += -g

OBJS =
OBJS += PointCut.o
OBJS += Advice.o
OBJS += TCLTraceAdvice.o
OBJS += Aspect.o
OBJS += Graph.o
OBJS += test.o

graph: $(OBJS)
	$(CXX) -o $@ $^ -ltcl -ltk

# Add .d dependencies

Aspect.o Graph.o : Aspect.h
PointCut.o : PointCut.h

test: graph
	./graph g.tcl

clean:
	rm *.o graph
