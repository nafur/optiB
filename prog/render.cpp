#include <iostream>

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/graph_to_eps.h>
#include <lemon/color.h>
#include <lemon/color.cc>

using namespace std;
using namespace lemon;

#define VIEWER "geeqie"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cerr << "please give lgf file as argument" << endl;
		return 1;
	}
	
	ListGraph g;
	ListGraph::EdgeMap<int> weight(g);
	graphReader(g, argv[1]).edgeMap("weight", weight).run();
	
//	graphToEps(g, "/tmp/lgftmp.eps").arcWidths(weight).
//		run();
	cout << WHITE.red() << endl;
	
}