#include "tsp_relax.h"

#include "mst.h"
#include <limits>
#include <cstdlib>

/**
	first relaxation of tsp
	idea:
		take mst
		add shortest edge
*/
int TSPRelaxation::mstPlusOne()
{
	// calculate mst
	MST mst(this->g, this->weight);
	int w = mst.prim();
	
	// minimum edge found
	int min = numeric_limits<int>::max();
	for (ListGraph::EdgeIt e(this->g); e != INVALID; ++e)
	{
		// edge is in mst, so do not take it
		if ((*mst.mst).count(e) != 0) continue;
		// edge is shorter than shortest found yet
		if (this->weight[e] < min) min = this->weight[e];
	}
	// return weight of mst + shortest other one
	return w + min;
}

/**
	second relaxation of tsp
	idea:
		remove some (random) node
		take mst
		add shortest two edges of the removed node
*/
int TSPRelaxation::mstOnSubgraph()
{
	// create a copy of the graph
	ListGraph g;
	ListGraph::EdgeMap<int> weight(g);
	ListGraph::NodeMap<ListGraph::Node> nodemap(g);
	
	GraphCopy<ListGraph, ListGraph> copy(this->g, g);
	copy.edgeMap(this->weight, weight).nodeCrossRef(nodemap).run();
	
	// remove a random node
	// removed will contain the node of this->g corresponding to the removed one afterwards
	int del = rand() % countNodes(g);
	ListGraph::Node removed;
	for (ListGraph::NodeIt n(g); n != INVALID; ++n)
	{
		if (del == 0)
		{
			removed = nodemap[n];
			g.erase(n);
			break;
		}
		del--;
	}
	
	// calculate mst
	MST mst(g, weight);
	int w = mst.prim();
	
	// search for two shortest edges incident to the removed node
	int mins[] = {numeric_limits<int>::max(), numeric_limits<int>::max()};
	for (ListGraph::IncEdgeIt e(this->g, removed); e != INVALID; ++e)
	{ // iterate over all incident nodes
		if (this->weight[e] < mins[0])
		{ // shortest found yet
			mins[1] = mins[0];
			mins[0] = this->weight[e];
		}
		// 2nd-shortest
		else if (this->weight[e] < mins[1]) mins[1] = this->weight[e];
	}
	
	return w + mins[0] + mins[1];
}
