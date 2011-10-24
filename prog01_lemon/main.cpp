#include <iostream>
#include <set>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "lemon/list_graph.h"
#include "lemon/lgf_reader.h"

#include "prim.h"
#include "dijkstra.h"

#define START_TIMER(x) clock_t x = clock();
#define STOP_TIMER(x) cout << (clock() - x) / (CLOCKS_PER_SEC / 1000) << " ms" << endl;

using namespace std;
using namespace lemon;

int main()
{
	srand(time(NULL));
	
	for (int i=1; i<7; i++)
	{
		stringstream filename;
		filename << "data/Graph" << i << ".lgf";
		
		cout << "Reading " << filename.str() << endl;
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();
		
		cout << "Calculating MST..." << endl;
		START_TIMER(tmr_mst)
		Prim p(g, weight);
		int w = p.prim();
		cout << "MST weight is " << w << endl;
/*		cout << "MST contains the following edges" << endl;
		for (set<ListGraph::Edge>::iterator it = p.mst->begin(); it != p.mst->end(); ++it)
			cout << "\t" << g.id(g.u(*it)) << ", " << g.id(g.v(*it)) << endl;
*/
		STOP_TIMER(tmr_mst)

		int uid = rand() % countNodes(g);
		int vid = rand() % countNodes(g);
		int vi=vid, ui=uid;
		ListGraph::Node u, v;
		for (ListGraph::NodeIt n(g); n != INVALID; ++n, --ui, --vi)
		{
			if (ui == 0) u = n;
			if (vi == 0) v = n;
		}
		cout << "Calculating distance between " << uid+1 << " and " << vid+1 << " using dijkstra..." << endl;
		START_TIMER(tmr_dist)
		Dijkstra dij(g, weight);
		dij.dijkstra(u);
		cout << "distance is " << (*dij.dist)[v] << endl;
		STOP_TIMER(tmr_dist)
		
	}
	
	
}
