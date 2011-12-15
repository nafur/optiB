#include <iostream>
#include <set>
#include <sstream>
#include <cstdlib>

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

#include "graph.h"
#include "debug.h"
#include "bipartite.h"
#include "allocation.h"
#include "tsp.h"
#include "tsp_relax.h"

using namespace std;
using namespace lemon;

int main()
{
	srand(time(NULL));
	
	cout << endl << "*** 1) ***" << endl;
	cout << endl;
	cout << "A minimal network that is 1-redundant (still connected if one edge fails)" << endl;
	cout << "is the union of connected cycles. If the graph is metric, the optimal solution" << endl;
	cout << "will be a solution for the TSP." << endl;
	cout << "(Actually, we don't know if the above holds, but TSP should at least be a good" << endl;
	cout << "approximation...)" << endl;
	cout << endl;
	cout << "Therefore, we implement a heuristic to find a hamiltonian cycle that is as" << endl;
	cout << "short as possible. To be exact, we implement the Christofides-Heuristic." << endl;
	cout << "The idea of this one is as follows:" << endl;
	cout << "\tTake a MST of the graph" << endl;
	cout << "\tTake all nodes, that have odd degree within the MST" << endl;
	cout << "\tCompute a matching on these nodes" << endl;
	cout << "\tAdd all matching edges to the MST" << endl;
	cout << "\tThe extended MST now has an eulerian cycle, because all nodes have even degree" << endl;
	cout << "\tIterate over some eulerian cycle" << endl;
	cout << "\t\tIf next node is visited for the first time (i.e. is new)" << endl;
	cout << "\t\t\tadd edge from last new node to the next one to result" << endl;
	cout << "\t\tIf next node has already been visited" << endl;
	cout << "\t\t\tskip node" << endl;
	cout << endl;
	cout << "This approximation is a 1.5-Approximation, because" << endl;
	cout << "\tThe MST is smaller than the TSP, as the TSP without some edge is a spanning tree" << endl;
	cout << "\tThe matching has at least half the weight of a MST" << endl;
	cout << "\tThe refactoring of the eulerian cycle only decreases the weight" << endl;
	cout << endl;
	
	START_TIMER(tmr_tsp)
	ListGraph g;
	ListGraph::EdgeMap<int> weight(g);
	readMatrix("data_2/Deutschland.txt", g, weight);
	TSP tsp(g, weight);
	int w = tsp.tsp();
	cout << "result has weight " << w << endl;	
	STOP_TIMER(tmr_tsp)
	
	cout << "printing the hamilton cycle is disabled. enable it in the code at line " << (__LINE__+1) << endl << endl;
	/* // print approximation
	for (set<ListGraph::Edge>::iterator it = tsp.edges->begin(); it != tsp.edges->end(); ++it)
		cout << g.id(g.u(*it)) << " -- " << g.id(g.v(*it)) << endl;
	*/

	cout << endl << "*** 2) ***" << endl;
	cout << endl;
	cout << "Checking if a graph is bipartite actually is the same as 2-coloring:" << endl;
	cout << "If you can color the nodes with two colors, such that every two nodes" << endl;
	cout << "that are connected do not have the same color, you are done." << endl;
	cout << "If cou can not do that, there must be a cycle of odd length, which" << endl;
	cout << "violates the assumption that the graph is bipartite." << endl;
	cout << endl;
	cout << "So what we do is exactly this: we color the graph with colors 1 and 2." << endl;
	cout << "We start with all nodes having no color." << endl;
	cout << "For all nodes n" << endl;
	cout << "\tif n is colored, skip" << endl;
	cout << "\tcolor n with 1" << endl;
	cout << "\tdo DFS(n, 1)" << endl;
	cout << endl;
	cout << "DFS(n, i):" << endl;
	cout << "\tn has color i, let other color be j" << endl;
	cout << "\tFor all neighbours m of n:" << endl;
	cout << "\t\tif m is not colored:" << endl;
	cout << "\t\t\tcolor m with j" << endl;
	cout << "\t\t\tdo DFS(m, j)" << endl;
	cout << "\t\tif m has color i:" << endl;
	cout << "\t\t\tm and n have same color, return error" << endl;
	cout << endl;
	cout << "If this methods succeeds, the graph is bipartite, otherwise it's not." << endl;
	cout << endl;
	
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
		if (b.bipartite())
		{
			cout << "yes, it is!" << endl;
			cout << "printing color classes is disabled. enable it in the code at line " << (__LINE__+1) << endl << endl;
			/* //print color classes
			for (ListGraph::NodeIt n(g); n != INVALID; ++n)
				cout << "Node " << g.id(n)+1 << " has color " << (*b.classes)[n] << endl;
			*/
		}
		else cout << "no, it's not!" << endl;
	}
	STOP_TIMER(tmr_bipartite)
	
	cout << endl << "*** 3) ***" << endl;
	cout << endl;
	cout << "Although the resource allocation problem looks np complete at first sight," << endl;
	cout << "it is possible to solve it in polynomial time." << endl;
	cout << "We are using a dynamic programming scheme:" << endl;
	cout << "\tf is int[machines][plants]" << endl;
	cout << "\tf[i][j] is the maximum profit when" << endl;
	cout << "\t\ti machines can be used" << endl;
	cout << "\t\tplants j, j+1, ... can be used" << endl;
	cout << endl;
	cout << "Filling f is quite simple. Just start at the last plant. For this one" << endl;
	cout << "the corresponding column of the given table can be copied." << endl;
	cout << "For every other plant, you just have to check every combination of" << endl;
	cout << "distributing the available machines to the current and the next plant." << endl;
	cout << "The overall result will be f[machines][0]" << endl;
	cout << endl;
	cout << "As the number of distributions to split up k machines on two plants" << endl;
	cout << "is only k+1, the overall complexity is O(machines * machines * plants)." << endl;
	
	START_TIMER(tmr_rescallo)
	for (int i=1; i<4; i++)
	{
		stringstream filename;
		filename << "data_2/RescAllo" << i << ".txt";
		Allocation a(filename.str(), 10);
		cout << "Maximum profit for instance " << i << ": " << a.allocate() << endl;
		cout << "Distribution over plants is: ";
		for (vector<int>::iterator it = a.distribution->begin(); it != a.distribution->end(); ++it)
		{
			cout << *it << ", ";
		}
		cout << endl;
	}
	STOP_TIMER(tmr_rescallo)
	
	cout << endl << "*** 4) ***" << endl;
	cout << endl;
	cout << "*** a) ***" << endl;
	cout << "A solution for the TSP is always a spanning tree with one additional edge." << endl;
	cout << "Therefore, the weight of a MST plus the shortest remaining edge is lower then the one of a TSP tour." << endl;
	cout << endl;
	cout << "For the second relaxation, a similar argument holds: A solution for the TSP" << endl;
	cout << "is always a 1-Tree (a 1-Tree is a graph consisting of a spanning tree on the" << endl;
	cout << "graph without some arbitrary node plus two edges incident to this node)." << endl;
	cout << "As we always take the smallest 1-Tree, it's weight is lower than the one of a TSP tour." << endl;
	cout << endl;
	cout << "*** b) ***" << endl;
	cout << "We'll run the second heuristic multiple times and take a random node each time..." << endl;
	
	START_TIMER(tmr_tsp_relax)
	int files[] = {15, 75, 150};
	for (int i=0; i<3; i++)
	{
		stringstream filename;
		filename << "data_2/TSP" << files[i] << ".data";

		ListGraph g;
		ListGraph::EdgeMap<int> weight(g);
		readMatrix(filename.str(), g, weight);
		
		TSPRelaxation tsp(g, weight);
		int val1 = tsp.mstPlusOne();
		cout << "1st lower bound for TSP" << files[i] << " is " << val1 << endl;
		int val = 0, num = 0;
		for (; num * num < countNodes(g); num++)
			val = max(val, tsp.mstOnSubgraph());
		cout << "2nd lower bound for TSP" << files[i] << " is " << val << " from " << num << " tries" << endl;
		cout << "2nd bound is about " << ((double)val / (double)val1 * 100 - 100) << " % better..." << endl;
	}
	STOP_TIMER(tmr_tsp_relax)
	
	cout << endl;
	cout << "*** c) ***" << endl;
	cout << "While the second relaxation always yields a higher (and thereby better) bound," << endl;
	cout << "it get's less better when the graph grows larger." << endl;
	cout << "While the result is 15% to 37% better on the smallest graph," << endl;
	cout << "the gain on the largest graph is only about 1.5% to 2.5%." << endl;
	cout << endl;
	
	return 0;
}
