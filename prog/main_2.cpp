#include <iostream>
#include <set>
#include <sstream>
#include <cstdlib>

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

#include "debug.h"
#include "bipartite.h"
#include "allocation.h"

using namespace std;
using namespace lemon;

int main()
{
	srand(time(NULL));

	cout << endl << "*** 2) ***" << endl;
	START_TIMER(tmr_bipartite)
	for (int i=1; i<5; i++)
	{
		stringstream filename;
		filename << "data_2/graph" << i << ".lgf";
		
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();	
		
		cout << "Checking if graph " << i << " is bipartite... ";
		
		Bipartite b(g);
		if (b.bipartite()) cout << "yes, it is!" << endl;
		else cout << "no, it's not!" << endl;
		
		/*
		cout << "Dumping classes: " << endl;
		for (ListGraph::NodeIt n(g); n != INVALID; ++n)
		{
			cout << g.id(n)+1 << " " << (*b.classes)[n] << ", ";
		}
		cout << endl;
		*/
	}
	STOP_TIMER(tmr_bipartite)
	
	cout << endl << "*** 3) ***" << endl;
	START_TIMER(tmr_rescallo)
	for (int i=1; i<4; i++)
	{
		stringstream filename;
		filename << "data_2/RescAllo" << i << ".txt";
		Allocation a(filename.str(), 10);
		cout << "Maximum profit for instance " << i << ": " << a.allocate() << endl;
	}
	STOP_TIMER(tmr_rescallo)
}
