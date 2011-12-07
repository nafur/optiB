#include "tsp.h"

#include "prim.h"
#include "graph.h"
#include <lemon/matching.h>
#include <lemon/core.h>
#include <lemon/euler.h>
#include <list>
#include <iostream>

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
	int pw = p.prim();
	cout << "MST weight: " << pw << endl;
	
	// copy subgraph induced by vertices with odd degree
	ListGraph matchg;
	ListGraph::EdgeMap<ListGraph::Edge> edgemap(this->g);
	ListGraph::EdgeMap<int> matchw(matchg);
	
	GraphCopy<ListGraph, ListGraph> copy(this->g, matchg);
	copy.edgeRef(edgemap);
	copy.edgeMap(this->weight, matchw);
	copy.run();
	
	for (ListGraph::NodeIt n(matchg); n != INVALID; ++n)
	{ // erase nodes with even degree
		if (countIncEdges(matchg, n) % 2 == 0) matchg.erase(n);
	}
	for (ListGraph::EdgeIt e(matchg); e != INVALID; ++e)
	{ // convert max matching to min matching
		matchw[e] = 1000 - matchw[e];
	}
	cout << "Queued for matching: " << countNodes(matchg) << endl;
	
	// calculate matching on remaining nodes
	MaxWeightedMatching<ListGraph, ListGraph::EdgeMap<int>> m(matchg, matchw);
	m.init();
	m.start();
	m.run();
	
	cout << "Matching size: " << m.matchingSize() << endl;
	
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
	cout << "Eulergraph has " << countEdges(eulerg) << " edges" << endl;
	cout << "Eulergraph has " << countNodes(eulerg) << " nodes" << endl;
	
	// TODO: this graph has no eulerian cycle... something is wrong in the code above
	dumpGraph("data_2/deutschland.lgf", eulerg);
	
	// iterate over eulerian cycle
	int weight = 0;
	EulerIt<ListGraph> e(eulerg);
//	ListGraph::Node last = eulerg.u(e);
//	ListGraph::Node first = eulerg.u(e);
	for (; e != INVALID; ++e)
	{
		cout << "from " << eulerg.id(eulerg.u(e)) << " to " << eulerg.id(eulerg.v(e)) << endl;
		visited[eulerg.u(e)] = true;
		
/*		if (! visited[eulerg.v(e)])
		{
			ListGraph::Edge edge = findEdge(this->g, eulernodemap[eulerg.v(e)], eulernodemap[last]);
			if (edge == INVALID) edge = findEdge(this->g, eulernodemap[last], eulernodemap[eulerg.v(e)]);
			if (edge == INVALID)
			{
				cout << "something weird happend" << endl;
			}
			this->edges->insert(edge);
			weight += this->weight[edge];
			last = eulerg.v(e);
		}
*/	}
	
	return weight;
}