#include <iostream>
#include <set>
#include <sstream>
#include <ctime>

#include "lemon/list_graph.h"
#include "lemon/lgf_reader.h"

#include "prim.h"

#define START_TIMER(x) clock_t x = clock();
#define STOP_TIMER(x) cout << (clock() - x) / (CLOCKS_PER_SEC / 1000) << " ms" << endl;

using namespace std;
using namespace lemon;

int main()
{
	for (int i=1; i<7; i++)
	{
		stringstream filename;
		filename << "data/Graph" << i << ".lgf";
		
		cout << "Reading " << filename.str() << endl;
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();
		
		cout << "Calculation MST..." << endl;
		START_TIMER(tmr_mst)
		Prim p(g, weight);
		p.prim();
/*		cout << "MST contains the following edges" << endl;
		for (set<ListGraph::Edge>::iterator it = p.mst->begin(); it != p.mst->end(); ++it)
			cout << "\t" << g.id(g.u(*it)) << ", " << g.id(g.v(*it)) << endl;
*/
		STOP_TIMER(tmr_mst)
	}
	
/*
	Dijkstra dij(g, weight);
	dij.dijkstra(g.nodeFromId(3));
	for (ListGraph::NodeIt n(g); n != INVALID; ++n)
	{
		cout << g.id(n) << " " << (*dij.dist)[n] << endl;
	}
*/
	
}
