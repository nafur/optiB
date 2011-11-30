#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

using namespace std;
using namespace lemon;

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
	
	stringstream dotfile;
	dotfile << argv[1] << ".dot";

	FILE* f = fopen(dotfile.str().c_str(), "w");
	fprintf(f, "graph {\n");
	
	for (ListGraph::EdgeIt e(g); e != INVALID; ++e)
	{
		fprintf(f, "\t%u -- %u [label=%u]\n", g.id(g.u(e))+1, g.id(g.v(e))+1, weight[e]);
	}
	
	fprintf(f, "}\n");
	fclose(f);

	stringstream shell;
	shell << "fdp -T png -o " << argv[1] << ".png " << argv[1] << ".dot";
	system(shell.str().c_str());
	
	stringstream viewer;
	viewer << "geeqie " << argv[1] << ".png";
	system(viewer.str().c_str());
	
}