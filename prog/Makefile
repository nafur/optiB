CXX=g++ -Wall -Werror -pedantic -g -std=c++0x ${OPTIMIZE}

OBJ1=graph.o debug.o dijkstra.o prim.o kruskal.o steiner.o
OBJ2=debug.o bipartite.o allocation.o
OBJR=

VALGRIND=valgrind --leak-check=full --undef-value-errors=yes

all: main_1.exe main_2.exe render.exe

main_1.exe: main_1.cpp ${OBJ1}
	${CXX} -o $@ $< ${OBJ1}

main_2.exe: main_2.cpp ${OBJ2}
	${CXX} -o $@ $< ${OBJ2}

render.exe: render.cpp ${OBJR}
	${CXX} -o $@ $< ${OBJR}

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CXX} -o $@ -c $<
	
.PHONY: clean
clean:
	rm -rf *.o *.exe

CUREXE=main_2.exe

run: all
	./${CUREXE}

memtest: all
	${VALGRIND} ./${CUREXE} > /dev/null