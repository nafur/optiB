#include <iostream>
#include <set>
#include <sstream>
#include <cstdlib>

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

#include "debug.h"
#include "graph.h"
#include "prim.h"
#include "kruskal.h"
#include "dijkstra.h"
#include "steiner.h"

using namespace std;
using namespace lemon;

int main()
{
	const int termFiles[] = {1,1,1,4,3,1};
	srand(time(NULL));
	
	cout << "***** Aufgabe 1 *****" << endl;
	cout << "Kruskal's Algorithm " << endl;
	
	cout << endl << "***** Aufgabe 2 *****" << endl;
	cout << "Dijkstra's Algorithm " << endl;
	
	cout << endl << "***** Aufgabe 3 *****" << endl;
	cout << "Algorithm to efficiently find a good approximation for a steiner tree" << endl;
	cout << "Idea:" << endl;
	cout << "\tRun Dijkstra to find all shortest paths from every terminal node to all other terminal nodes" << endl;
	cout << "\tCreate an intermediate graph containing all terminal nodes" << endl;
	cout << "\tFor each pair of nodes insert an edge with weight being the length of shortest path between those nodes" << endl;
	cout << "\tCalculate a MST on this intermediate graph" << endl;
	cout << "\tReplace every edge in the intermediate graph with the corresponding shortest path" << endl;
	cout << "The result is a connected graph containing at least all terminal nodes" << endl;
	cout << "Note that the result is however not garantueed to be a tree (i.e. it can contain cycles)" << endl;
	cout << "An example for this behaviour, in which it is obviously not optimal, is the following graph: " << endl;
	cout << "V = (a, b, c, d, e), E = ((a,b), (a,e), (b,e), (c,e), (d,e)), Terminal nodes = (a, b, c, d)" << endl;
	cout << "A MST in the intermediate graph is (a,b), (a,d), (b,c) with an overall weight of 5" << endl;
	cout << "However, an optimal steiner tree would be (a,e), (b,e), (c,e), (d,e) with an overall weight of 4" << endl;

	cout << endl << "***** Aufgabe 3 *****" << endl;
	
	
	START_TIMER(tmr_mst)
	for (int i=1; i<7; i++)
	{
		stringstream filename;
		filename << "data/Graph" << i << ".lgf";
		
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();
		
		cout << "Calculating MST for graph " << i << "...";
//		Prim p(g, weight);
//		int w = p.prim();
		Kruskal k(g, weight);
		int w = k.kruskal();
		
		cout << " overall weight is " << w << endl;

/*		cout << "MST contains the following edges" << endl;
		for (set<ListGraph::Edge>::iterator it = p.mst->begin(); it != p.mst->end(); ++it)
			cout << "\t" << g.id(g.u(*it)) << ", " << g.id(g.v(*it)) << endl;
*/
	}
	STOP_TIMER(tmr_mst)

	for (int i=1; i<7; i++)
	{
		stringstream filename;
		filename << "data/Graph" << i << ".lgf";
		
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();

		cout << "Calculating steiner trees for graph " << i << endl;
		
		for (int term = 1; term < termFiles[i-1]+1; term++)
		{
			START_TIMER(tmr_steiner)
			stringstream termfname;
			termfname << "data/Graph" << i << "_Terminals";
			if (termFiles[i-1] != 1) termfname << term;
			termfname << ".txt";
			set<ListGraph::Node> terminals;
			readTerminals(termfname.str(), g, terminals);
			
			Steiner steiner(g, weight);
			int steinerw = steiner.steiner(terminals);
			cout << "Upper bound for terminals " << term << ": " << steinerw << endl;
			cout << "steiner: ";
			STOP_TIMER(tmr_steiner)
		}
	}
}
