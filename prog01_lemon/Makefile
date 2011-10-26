CXX=g++ -Wall -Werror -g -std=c++0x

OBJECTS=graph.o debug.o dijkstra.o prim.o steiner.o

all: main.exe
	
%.exe: %.cpp ${OBJECTS}
	${CXX} -o $@ $< ${OBJECTS}

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CXX} -o $@ -c $<
	
.PHONY: clean
clean:
	rm -rf *.o *.exe
