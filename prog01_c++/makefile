CXX=g++ -Wall -Werror -g -std=c++0x ${OPTIMIZE}

OBJECTS=graph.o vertex.o edge.o

TEMPLATES=#

all: main.exe
	
%.exe: %.cpp ${OBJECTS} ${TEMPLATES}
	${CXX} -o $@ $< ${OBJECTS}

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CXX} -o $@ -c $<
	
.PHONY: clean
clean:
	rm -rf *.o *.exe
