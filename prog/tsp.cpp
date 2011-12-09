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
		- replace edges using already visited nodes inbetween by a direct edge
*/
int TSP::tsp()
{
	if (this->edges != 0) delete this->edges;
	this->edges = new set<ListGraph::Edge>();

	// calculate mst
	Prim p(this->g, this->weight);
	p.prim();
	
	// dump mst to file
	dumpSubGraph("data_2/Deutschland_MST.lgf", this->g, *p.mst);
	
	// copy subgraph induced by vertices with odd degree: create copy, run GraphCopy
	ListGraph matchg;
	ListGraph::EdgeMap<ListGraph::Edge> edgemap(this->g);
	ListGraph::NodeMap<ListGraph::Node> nodemap(this->g);
	ListGraph::EdgeMap<int> matchw(matchg);
	
	GraphCopy<ListGraph, ListGraph> copy(this->g, matchg);
	copy.edgeRef(edgemap).nodeRef(nodemap).edgeMap(this->weight, matchw);
	copy.run();
	
	// and now remove all edges with even degree	
	ListGraph::Node node;
	for (ListGraph::NodeIt n(matchg); n != INVALID; )
	{ // erase nodes with even degree
		if (this->degree(this->g, n, *p.mst, nodemap) % 2 == 0)
		{ // just removing the node that the iterator is pointing at puts iterator in undefined state
			node = n;
			++n;
			matchg.erase(node);
		}
		else ++n;
	}
	
	// convert max matching to min matching
	// TODO: max matching -> min matching is kind of ugly
	for (ListGraph::EdgeIt e(matchg); e != INVALID; ++e)
	{ 
		matchw[e] = -matchw[e];
	}
	// calculate matching on remaining nodes
	MaxWeightedPerfectMatching<ListGraph, ListGraph::EdgeMap<int>> m(matchg, matchw);
	m.run();
	
	// now create another graph copy that contains the mst edges and the matching edges
	// we will search a eulerian path in this graph afterwards
	ListGraph eulerg;
	ListGraph::EdgeMap<ListGraph::Edge> eulermap(eulerg);
	ListGraph::NodeMap<ListGraph::Node> eulernodemap(eulerg);
	ListGraph::NodeMap<bool> visited(eulerg);
	
	GraphCopy<ListGraph, ListGraph> copy2(this->g, eulerg);
	copy2.nodeCrossRef(eulernodemap).edgeCrossRef(eulermap).run();
	
	// make a copy of the edges as removing the iterator is even uglier than above...
	list<ListGraph::Edge> edges;
	for (ListGraph::EdgeIt e(eulerg); e != INVALID; ++e) edges.push_back(e);
	
	for (list<ListGraph::Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
	{ // copy edges in matching
	
		ListGraph::Edge cur = edgemap[eulermap[*it]];
		if (m.matching(cur))
		{
			eulerg.addEdge(eulerg.u(*it), eulerg.v(*it));
		}
		if (p.mst->count(eulermap[*it]) == 0) eulerg.erase(*it);
	}
	
	dumpGraph("data_2/Deutschland_Euler.lgf", eulerg);
	
	// iterate over eulerian cycle
	// last always contains last node on cycle, cur the current one
	// edges from EulerIt are not directed, so we have to find out which is the first and which the second one
	int weight = 0;
	EulerIt<ListGraph> e(eulerg);
	ListGraph::Node last = eulerg.u(e);
	ListGraph::Node first = eulerg.v(e);
	++e;
	if ((eulerg.u(e) == first) || (eulerg.v(e) == first))
	{ // second edge incident to node that was assumed to be first one, swap them
		ListGraph::Node tmp = last;
		last = first;
		first = tmp;
	}
	// insert the first edge
	ListGraph::Edge edge = findEdge(this->g, eulernodemap[first], eulernodemap[last]);
	this->edges->insert(edge);
	visited[first] = true;

	// start node of next edge to be inserted (skip refers to the fact, that already visited nodes between skip and cur are skipped...)
	ListGraph::Node skip = last;
	
	// walk the eulerian cycle
	for (; e != INVALID; ++e)
	{
		ListGraph::Node cur;
		visited[last] = true;
		if (eulerg.u(e) == last) cur = eulerg.v(e);
		else cur = eulerg.u(e);
		// cur is the new node now, last the previous one and skip the last one that was not visited before
//		cout << "from " << eulerg.id(last) << " to " << eulerg.id(cur) << endl;
		
		if (! visited[cur])
		{ // cur is visited for the first time, thus create edge from skip to cur
//			cout << "inserting " << eulerg.id(skip) << " to " << eulerg.id(cur) << endl;
			ListGraph::Edge edge = findEdge(this->g, eulernodemap[skip], eulernodemap[cur]);
			assert(edge != INVALID); // just to be sure, we have had an error here...
			this->edges->insert(edge);
			weight += this->weight[edge]; // add weight to our sum
			skip = cur; // next edge should start at this node
		}
		last = cur;
	}
	// insert last edge (not done in the loop, as first node was marked as visited
	this->edges->insert(findEdge(this->g, eulernodemap[skip], eulernodemap[first]));
	
	// dump hamilton cycle...
	dumpSubGraph("data_2/Deutschland_Tour.lgf", this->g, *this->edges);
	
	return weight;
}