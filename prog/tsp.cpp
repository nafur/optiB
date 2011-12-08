#include "tsp.h"

#include "prim.h"
#include "graph.h"
#include <lemon/matching.h>
#include <lemon/core.h>
#include <lemon/euler.h>
#include <list>
#include <iostream>
#include <cassert>

int TSP::degree(const ListGraph& g, const ListGraph::Node& n, const set<ListGraph::Edge>& edges, const ListGraph::NodeMap<ListGraph::Node>& mapping)
{
	int deg = 0;
	for (set<ListGraph::Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
	{
		if (mapping[g.u(*it)] == n) deg++;
		if (mapping[g.v(*it)] == n) deg++;
	}
	return deg;
}

/**
	perform christofides approximation
	
	this works as follows:
	* calculate mst
	* identify vertices in mst with odd degree
	* calculate minimum weighted matching on these vertices
	* add matching edges to mst
	* identify euler tour
	* iterate over euler tour
		- if next node is already visited, 
*/
int TSP::tsp()
{
	if (this->edges != 0) delete this->edges;
	this->edges = new set<ListGraph::Edge>();

	// calculate mst
	Prim p(this->g, this->weight);
	p.prim();
	
	// copy subgraph induced by vertices with odd degree
	ListGraph matchg;
	ListGraph::EdgeMap<ListGraph::Edge> edgemap(this->g);
	ListGraph::NodeMap<ListGraph::Node> nodemap(this->g);
	ListGraph::EdgeMap<int> matchw(matchg);
	
	GraphCopy<ListGraph, ListGraph> copy(this->g, matchg);
	copy.edgeRef(edgemap);
	copy.nodeRef(nodemap);
	copy.edgeMap(this->weight, matchw);
	copy.run();
	
	ListGraph::Node node;
	for (ListGraph::NodeIt n(matchg); n != INVALID; )
	{ // erase nodes with even degree
		if (this->degree(this->g, n, *p.mst, nodemap) % 2 == 0)
		{
			node = n;
			++n;
			matchg.erase(node);
		}
		else ++n;
	}
	
	for (ListGraph::EdgeIt e(matchg); e != INVALID; ++e)
	{ // convert max matching to min matching
		matchw[e] = 1000 - matchw[e];
	}
	// calculate matching on remaining nodes
	MaxWeightedMatching<ListGraph, ListGraph::EdgeMap<int>> m(matchg, matchw);
	m.init();
	m.start();
	m.run();
	
	ListGraph eulerg;
	ListGraph::EdgeMap<ListGraph::Edge> eulermap(eulerg);
	ListGraph::NodeMap<ListGraph::Node> eulernodemap(eulerg);
	ListGraph::NodeMap<bool> visited(eulerg);
	
	GraphCopy<ListGraph, ListGraph> copy2(this->g, eulerg);
	copy2.nodeCrossRef(eulernodemap);
	copy2.edgeCrossRef(eulermap);
	copy2.run();

	for (ListGraph::EdgeIt e(eulerg); e != INVALID; ++e)
	{ // copy edges in matching
		if (m.matching(edgemap[eulermap[e]]))
		{
			eulerg.addEdge(eulerg.u(e), eulerg.v(e));
		}
		if (p.mst->count(eulermap[e]) == 0) eulerg.erase(e);
	}
	
	dumpGraph("data_2/Deutschland_Euler.lgf", eulerg);
	
	// iterate over eulerian cycle
	int weight = 0;
	EulerIt<ListGraph> e(eulerg);
	ListGraph::Node last = eulerg.u(e);
	ListGraph::Node first = eulerg.v(e);
	++e;
	if ((eulerg.u(e) == first) || (eulerg.v(e) == first))
	{
		ListGraph::Node tmp = last;
		last = first;
		first = tmp;
	}
	ListGraph::Node skip = last;
	
	for (; e != INVALID; ++e)
	{
		ListGraph::Node cur;
		visited[last] = true;
		if (eulerg.u(e) == last) cur = eulerg.v(e);
		else cur = eulerg.u(e);
//		cout << "from " << eulerg.id(last) << " to " << eulerg.id(cur) << endl;
		
		if (! visited[cur])
		{
			ListGraph::Edge edge = findEdge(this->g, eulernodemap[last], eulernodemap[cur]);
			assert(edge != INVALID);
			this->edges->insert(edge);
			weight += this->weight[edge];
			skip = cur;
		}
		last = cur;
	}
	
	return weight;
}