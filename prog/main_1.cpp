#include <iostream>
#include <set>
#include <sstream>
#include <cstdlib>

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

#include "debug.h"
#include "graph.h"
#include "mst.h"
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
	cout << "We first sort all edges by inserting them into a priority queue, resulting in a complexity of O(m * log(m))." << endl
	<< "For each edge, we then check if it connects two different node sets. This is the case exactly n times." << endl
	<< "If this is the case, we merge two vertex sets by iterating over all vertices." << endl
	<< "Otherwise, we continue with the next edge." << endl
	<< endl
	<< "Overall, this results in a complexity of O(m * log(m) + m + n * n) = O(n*n + m*log(m))." << endl
	<< endl << "Using a more sophisticated set datastructure that is optimized to perform union operations might result in a slightly better complexity."
	<< endl;
	
	cout << endl << "***** Aufgabe 2 *****" << endl;
	cout << "Dijkstra's Algorithm " << endl;
	cout << "This is not the most efficient dijkstra implementation, as a fibbonaci heap is necessary for this." << endl
	<< "As we use a simple priority queue, we have a slightly higher complexity." << endl
	<< "Using a traditional priority queue, we have to insert a node with it's current distance to the queue, every time this node is updated." << endl
	<< "Thereby, the queue can contain each node multiple times." << endl
	<< endl
	<< "We have the following complexity estimation:" << endl
	<< "Over the run of the algorithm, the queue can contain at most m nodes, m being the number of edges." << endl
	<< "For n of these nodes, being the first occurences of the specific node, we iterate over all (at most n) incident edges and update the distances of the incident nodes." << endl
	<< "An update of a distance will then produce an insertion of a node to the priority queue, resulting in a log(m) overhead for reorganizing the heap underneath." << endl
	<< "For all other nodes, we will notice that the distance they had when being inserted is not the distance they have in this moment. If this is the case, they are ignored." << endl
	<< endl
	<< "Thus, we have a worst case complexity of O(m * log(m) + m)." << endl
	<< "As log(m) is at most log(n*n) = log(n) * 2, the complexity is O(m * log(n))" << endl
	<< "Optimal dijkstra results in a worst case complexity of O(n * log(n) + m).\n"
	<< "As our graphs usually have only as many edges as they have nodes, our implementation will not be much slower.\n"
	<< "If the triangle inequality holds in the graph, our implementation will be as fast as the optimal one, as no nodes are inserted a second time." << endl;
	
	cout << endl << "***** Aufgabe 3 *****" << endl;
	cout << "Algorithm to efficiently find a good approximation for a steiner tree" << endl;
	cout << "Idea:" << endl;
	cout << "\tRun Dijkstra to find all shortest paths from every terminal node to all other terminal nodes" << endl;
	cout << "\tCreate an intermediate graph containing all terminal nodes" << endl;
	cout << "\tFor each pair of nodes insert an edge with weight being the length of shortest path between those nodes into the intermediate graph" << endl;
	cout << "\tCalculate a MST on this intermediate graph" << endl;
	cout << "\tReplace every edge in the intermediate graph with the corresponding shortest path" << endl;
	cout << "The result is a connected graph containing at least all terminal nodes" << endl;
	cout << "Note that the result is however not garantueed to be a tree (i.e. it can contain cycles)" << endl;
	cout << "An example for this behaviour, in which it is obviously not optimal, is the following graph: " << endl;
	cout << "V = (a, b, c, d, e), E = ((a,b), (a,e), (b,e), (c,e), (d,e)), Terminal nodes = (a, b, c, d)" << endl;
	cout << "A MST in the intermediate graph is (a,b), (a,d), (b,c) with an overall weight of 5" << endl;
	cout << "However, an optimal steiner tree would be (a,e), (b,e), (c,e), (d,e) with an overall weight of 4" << endl;

	cout << endl << "***** Aufgabe 4 *****" << endl;
	
	cout << endl << "*** 4 a) ***" << endl;
	START_TIMER(tmr_mst)
	for (int i=1; i<7; i++)
	{
		stringstream filename;
		filename << "data_1/Graph" << i << ".lgf";
		
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();
		
		cout << "Calculating MST for graph " << i << "...";
		MST mst(g, weight);
		int w = mst.kruskal();
		
		cout << " overall weight is " << w << endl;
		cout << "the output of the edges is disabled. Please enable it in the code at line " << (__LINE__+2) << endl << endl;

/*		cout << "MST contains the following edges" << endl;
		for (set<ListGraph::Edge>::iterator it = mst.mst->begin(); it != mst.mst->end(); ++it)
			cout << "\t" << g.id(g.u(*it)) << ", " << g.id(g.v(*it)) << endl;
*/
	}
	STOP_TIMER(tmr_mst)

	cout << endl << "*** 4 b) and c) ***" << endl;
	for (int i=1; i<7; i++)
	{
		stringstream filename;
		filename << "data_1/Graph" << i << ".lgf";
		
		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		graphReader(g, filename.str()).edgeMap("weight", weight).run();

		cout << "Calculating steiner trees for graph " << i << endl;
		
		for (int term = 1; term < termFiles[i-1]+1; term++)
		{
			START_TIMER(tmr_steiner)
			stringstream termfname;
			termfname << "data_1/Graph" << i << "_Terminals";
			if (termFiles[i-1] != 1) termfname << term;
			termfname << ".txt";
			set<ListGraph::Node> terminals;
			readTerminals(termfname.str(), g, terminals);
			
			Steiner steiner(g, weight);
			int steinerw = steiner.steiner(terminals);
			cout << "Upper bound for terminals " << term << ": " << steinerw << endl;
			cout << "steiner: ";
			STOP_TIMER(tmr_steiner)
			if (i == 1)
			{
				cout << "Printing steiner tree for first example." << endl;
				cout << "note that the given ids are not garantued to match those in the file..." << endl;
				for (ListGraph::EdgeIt e(*steiner.s); e != INVALID; ++e)
				{
					cout << "\t" << steiner.s->id(steiner.s->u(e))+1 << " -- " << steiner.s->id(steiner.s->v(e))+1 << endl;
				}
			}
		}
	}
}
