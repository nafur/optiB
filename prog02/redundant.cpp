#include "redundant.h"

#include "prim.h"
#include "steiner.h"

#include <cassert>

int Redundant::redundant()
{
	if (this->redundant != 0) delete this->redundant;
	this->redundant = new set<ListGraph::Edge>();
	
	ListGraph g(this->g);
	
	Prim p(this->g, this->weight);
	int w = p.prim();
	
	ListGraph::NodeMap<int> degree(this->g);
	for (set<ListGraph::Edge>::iterator it = p.mst->begin(); it != p.mst->end(); ++it)
	{
		degree[this->g.u(*it)]++;
		degree[this->g.v(*it)]++;
	}
	
	set<ListGraph::Node> leafs;
	
	for (ListGraph::NodeIt n(this->g); n != INVALID; ++n)
	{
		assert(degree[n] > 0);
		if (degree[n] == 1) leafs.insert(n);
	}
	
	Steiner s(this->g, this->weight);
	w += s.steiner(leafs);
	
	return 0;
}