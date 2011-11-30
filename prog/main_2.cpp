#include <iostream>
#include <set>
#include <sstream>
#include <cstdlib>

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

#include "debug.h"
#include "bipartite.h"

using namespace std;
using namespace lemon;

int main()
{
	srand(time(NULL));

	cout << endl << "*** 2) ***" << endl;
	for (int i=1; i<5; i++)
	{
		stringstream filename;
		filename << "data_2/graph" << i << ".lgf";
		
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();	
		
		cout << "Checking if graph " << i << " is bipartite..." << endl;
		
		Bipartite b(g);
		if (b.bipartite()) cout << "yes, it is!" << endl;
		else cout << "no, its not..." << endl;
		
		cout << "Dumping classes: " << endl;
		for (ListGraph::NodeIt n(g); n != INVALID; ++n)
		{
			cout << g.id(n)+1 << " " << (*b.classes)[n] << ", ";
		}
		cout << endl;
	}
}
