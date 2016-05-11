
CXXFLAGS += -g

graph: Graph.o Traced.o test.o
	$(CXX) -o $@ $^ -ltcl -ltk

test: graph
	./graph g.tcl

clean:
	rm *.o graph
