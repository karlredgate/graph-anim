
graph: graph.o test.o
	$(CXX) -o $@ $^ -ltcl -ltk

test: graph
	./graph g.tcl

clean:
	rm *.o graph
