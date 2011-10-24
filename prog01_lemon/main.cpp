#include <iostream>
#include <set>

#include "lemon/list_graph.h"
#include "lemon/lgf_reader.h"

#include "prim.h"

using namespace std;
using namespace lemon;

int main()
{
	cout << "Fooo" << endl;
	
	ListGraph g;
	ListGraph::EdgeMap<int> weight(g);
	graphReader(g, "Graph1.lgf").edgeMap("weight", weight).run();
	
/*
	Dijkstra dij(g, weight);
	dij.dijkstra(g.nodeFromId(3));
	for (ListGraph::NodeIt n(g); n != INVALID; ++n)
	{
		cout << g.id(n) << " " << (*dij.dist)[n] << endl;
	}
*/
	Prim p(g, weight);
	p.prim();
	for (set<ListGraph::Edge>::iterator it = p.mst->begin(); it != p.mst->end(); ++it)
	{
		cout << "Edge: " << g.id(g.u(*it)) << ", " << g.id(g.v(*it)) << endl;
	}
	
}
