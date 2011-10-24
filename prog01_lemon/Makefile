CXX=g++ -Wall -Werror -g -std=c++0x -O2

OBJECTS=dijkstra.o prim.o

all: main.exe
	
%.exe: %.cpp ${OBJECTS}
	${CXX} -o $@ $< ${OBJECTS}

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CXX} -o $@ -c $<
	
.PHONY: clean
clean:
	rm -rf *.o *.exe
