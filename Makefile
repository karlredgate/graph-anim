
graph: graph.o test.o
	$(CXX) -o $@ $^ -ltcl -ltk

clean:
	rm *.o graph
