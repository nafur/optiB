CXX=g++ -Wall -Werror -g -std=c++0x ${OPTIMIZE}

OBJECTS=graph.o debug.o dijkstra.o prim.o kruskal.o steiner.o

all: main.exe
	
%.exe: %.cpp ${OBJECTS}
	${CXX} -o $@ $< ${OBJECTS}

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CXX} -o $@ -c $<
	
.PHONY: clean
clean:
	rm -rf *.o *.exe

run: all
	./main.exe
