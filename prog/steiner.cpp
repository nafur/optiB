#include "steiner.h"

#include "debug.h"
#include "dijkstra.h"
#include "mst.h"

#include <cassert>

#include <map>
#include <iostream>

/*
	To calculate all shortest paths, we use dijkstra.
	This is not the fastest possible solution, but still reasonably fast.
*/

int Steiner::steiner(const set<ListGraph::Node> terminals)
{
	if (this->s != 0) delete this->s;
	this->s = new ListGraph();
	if (this->sweight != 0) delete this->sweight;
	this->sweight = new ListGraph::EdgeMap<int>(*this->s);
	
	// perform dijkstra for every terminal
	ListGraph::NodeMap<Dijkstra*> dijk(this->g);
	for (set<ListGraph::Node>::iterator it = terminals.begin(); it != terminals.end(); ++it)
	{
		dijk[*it] = new Dijkstra(this->g, this->weight);
		dijk[*it]->dijkstra(*it);
	}

	// build intermediate graph
	ListGraph intermediate;
	ListGraph::EdgeMap<int> iweight(intermediate);
	map<ListGraph::Node, ListGraph::Node> imapper;
	
	for (set<ListGraph::Node>::iterator it = terminals.begin(); it != terminals.end(); ++it)
	{
		ListGraph::Node n = intermediate.addNode();
		imapper[n] = *it;
	}
	for (ListGraph::NodeIt it1(intermediate); it1 != INVALID; ++it1)
	{
		ListGraph::NodeIt it2 = it1;
		for (++it2; it2 != INVALID; ++it2)
		{
			ListGraph::Edge e = intermediate.addEdge(it1, it2);
			iweight[e] = (*dijk[imapper[it1]]->dist)[imapper[it2]];
		}
	}
	
	// compute mst
	MST mst(intermediate, iweight);
	mst.prim();
//	Kruskal mst(intermediate, iweight);
//	mst.kruskal();

	// build final graph
	map<ListGraph::Node, ListGraph::Node> smapper;
	for (set<ListGraph::Edge>::iterator it = mst.mst->begin(); it != mst.mst->end(); ++it)
	{ // for each edge in the mst
		// add end nodes to graph
		ListGraph::Node u = imapper[intermediate.u(*it)];
		if (smapper.count(u) == 0) smapper[u] = this->s->addNode();
		ListGraph::Node v = imapper[intermediate.v(*it)];
		if (smapper.count(v) == 0) smapper[v] = this->s->addNode();

		ListGraph::Node last = v;
		ListGraph::Node cur = v;
		do
		{ // walk through path
			cur = (*dijk[u]->pred)[cur];
			if (smapper.count(cur) == 0) smapper[cur] = this->s->addNode();
			// add edge to graph, if not already existing
			if (findEdge(*this->s, smapper[last], smapper[cur]) == INVALID)
			{
				ListGraph::Edge e = this->s->addEdge(smapper[last], smapper[cur]);
				(*this->sweight)[e] = (*dijk[u]->dist)[last] - (*dijk[u]->dist)[cur];
			}
			last = cur;
		}
		while (cur != u);
	}
	
	// compute overall weight
	int overallw = 0;
	for (ListGraph::EdgeIt e(*this->s); e != INVALID; ++e)
	{
		overallw += (*this->sweight)[e];
	}
	
	// clean up dijkstras
	for (set<ListGraph::Node>::iterator it = terminals.begin(); it != terminals.end(); ++it)
	{
		delete dijk[*it];
	}

	return overallw;
}
