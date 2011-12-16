#include "tsp.h"

#include "mst.h"
#include "graph.h"
#include <lemon/matching.h>
#include <lemon/connectivity.h>
#include <lemon/core.h>
#include <lemon/euler.h>
#include <list>
#include <vector>
#include <limits>
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

int TSP::processEulerian(const ListGraph& eulerg, const ListGraph::NodeMap<ListGraph::Node>& eulernodemap, const ListGraph::Node& start, const bool addEdges)
{
	// iterate over eulerian cycle, starting at given node
	// last always contains last node on cycle, cur the current one
	// edges from EulerIt are not directed, so we have to find out which is the first and which the second one
	int weight = 0;
	ListGraph::NodeMap<bool> visited(eulerg);
	ListGraph::Node last = start;
	ListGraph::Node skip = last;
	
	// walk the eulerian cycle
	for (EulerIt<ListGraph> e(eulerg, start); e != INVALID; ++e)
	{
		ListGraph::Node cur;
		visited[last] = true;
		if (eulerg.u(e) == last) cur = eulerg.v(e);
		else cur = eulerg.u(e);
		// cur is the new node now, last the previous one and skip the last one that was not visited before
		
		if (! visited[cur])
		{ // cur is visited for the first time, thus create edge from skip to cur
			ListGraph::Edge edge = findEdge(this->g, eulernodemap[skip], eulernodemap[cur]);
			assert(edge != INVALID); // just to be sure, we have had an error here...
			this->edges->insert(edge);
			weight += this->weight[edge]; // add weight to our sum
			skip = cur; // next edge should start at this node
		}
		last = cur;
	}
	// insert last edge (not done in the loop, as first node was marked as visited
	this->edges->insert(findEdge(this->g, eulernodemap[skip], eulernodemap[start]));
	
	return weight;
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
int TSP::christofides()
{
	if (this->edges != 0) delete this->edges;
	this->edges = new set<ListGraph::Edge>();

	// calculate mst
	MST mst(this->g, this->weight);
	mst.prim();
	
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
		if (this->degree(this->g, n, *mst.mst, nodemap) % 2 == 0)
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
	
	GraphCopy<ListGraph, ListGraph> copy2(this->g, eulerg);
	copy2.nodeCrossRef(eulernodemap).edgeCrossRef(eulermap).run();
	
	// make a copy of the edges as removing the iterator is even uglier than above...
	list<ListGraph::Edge> edges;
	for (ListGraph::EdgeIt e(eulerg); e != INVALID; ++e) edges.push_back(e);
	
	for (list<ListGraph::Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
	{ // copy edges in matching
		if (mst.mst->count(eulermap[*it]) == 0) eulerg.erase(*it);

		ListGraph::Edge cur = edgemap[eulermap[*it]];
		if (! matchg.valid(cur)) continue;
		if (m.matching(cur))
		{
			eulerg.addEdge(eulerg.u(*it), eulerg.v(*it));
		}
	}
	
	// find best eulerian path
	ListGraph::Node best;
	int min = numeric_limits<int>::max();
	for (ListGraph::NodeIt n(eulerg); n != INVALID; ++n)
	{
		this->edges->clear();
		int res = this->processEulerian(eulerg, eulernodemap, n, false);
		if (min > res)
		{
			min = res;
			best = n;
		}
		assert(this->edges->size() == (unsigned int)countNodes(eulerg));
	}
	
	this->edges->clear();
	return this->processEulerian(eulerg, eulernodemap, best, true);
}

/**
	edge swapping heuristic
	
	start with some hamilton cycle (we'll take the result of christofides)
	take a pair of edges, try to connect the nodes differently
	terminate, if no pair of edges can be improved further
*/
int TSP::edgeSwapping()
{
	if (this->edges != 0) delete this->edges;
	this->edges = new set<ListGraph::Edge>();
	
	// copy graph and remove edges
	ListGraph g;
	ListGraph::NodeMap<ListGraph::Node> map(this->g);
	ListGraph::NodeMap<ListGraph::Node> xmap(g);
	ListGraph::EdgeMap<int> w(g);
	
	GraphCopy<ListGraph, ListGraph> copy(this->g, g);
	copy.nodeRef(map).nodeCrossRef(xmap).run();
	
	ListGraph::EdgeIt e(g);
	while (e != INVALID)
	{
		ListGraph::Edge edge = e;
		++e;
		g.erase(edge);
	}
	
	// start with a good approximation, so copy result of christofides
	this->christofides();
	for (set<ListGraph::Edge>::iterator it = this->edges->begin(); it != this->edges->end(); ++it)
	{
		ListGraph::Edge edge = g.addEdge(map[this->g.u(*it)], map[this->g.v(*it)]);
		w[edge] = this->weight[*it];
	}
	
	// try to swap edges until no changes are done
	int changed = 1;
	while (changed > 0)
	{
		changed = 0;
		for (ListGraph::EdgeIt e1(g); e1 != INVALID;)
		{ // for all edges
			ListGraph::Node nodes[4] = { g.u(e1), g.v(e1), g.u(e1), g.v(e1) };
			ListGraph::Edge e1c = e1;
			++e1;
			
			for (ListGraph::EdgeIt e2(g); e2 != INVALID;)
			{ // and all edge combination
				nodes[2] = g.u(e2);
				nodes[3] = g.v(e2);
				ListGraph::Edge e2c = e2;
				++e2;
				
				// edges are adjacent, so skip it
				if (g.u(e1c) == g.u(e2c)) continue;
				if (g.u(e1c) == g.v(e2c)) continue;
				if (g.v(e1c) == g.u(e2c)) continue;
				if (g.v(e1c) == g.v(e2c)) continue;
				
				// ref is current weight of the connections
				int ref = 	this->weight[findEdge(this->g, xmap[nodes[0]], xmap[nodes[1]])] + 
							this->weight[findEdge(this->g, xmap[nodes[2]], xmap[nodes[3]])];
				// there are two other possible connections
				int chg1 = 	this->weight[findEdge(this->g, xmap[nodes[0]], xmap[nodes[2]])] + 
							this->weight[findEdge(this->g, xmap[nodes[1]], xmap[nodes[3]])];
				int chg2 = 	this->weight[findEdge(this->g, xmap[nodes[0]], xmap[nodes[3]])] + 
							this->weight[findEdge(this->g, xmap[nodes[1]], xmap[nodes[2]])];
				if (chg1 < ref)
				{ // if this one would be better, try it
					g.erase(e1c);
					g.erase(e2c);
					ListGraph::Edge tmp1 = g.addEdge(nodes[0], nodes[2]);
					ListGraph::Edge tmp2 = g.addEdge(nodes[1], nodes[3]);
					if (connected(g))
					{ // if graph is still connected, apply the change
						changed++;
						break;
					}
					// otherwise, undo the changes
					g.erase(tmp1);
					g.erase(tmp2);
					e1c = g.addEdge(nodes[0], nodes[1]);
					e2c = g.addEdge(nodes[2], nodes[3]);
				}
				if (chg2 < ref)
				{ // if this one would be better, try it
					g.erase(e1c);
					g.erase(e2c);
					ListGraph::Edge tmp1 = g.addEdge(nodes[0], nodes[3]);
					ListGraph::Edge tmp2 = g.addEdge(nodes[1], nodes[2]);
					if (connected(g))
					{ // if graph is still connected, apply the change
						changed++;
						break;
					}
					// otherwise, unto the changes
					g.erase(tmp1);
					g.erase(tmp2);
					e1c = g.addEdge(nodes[0], nodes[1]);
					e2c = g.addEdge(nodes[2], nodes[3]);
				}
			}
		}
	}
	
	// produce actual results...
	int res = 0;
	this->edges->clear();
	for (ListGraph::EdgeIt e(g); e != INVALID; ++e)
	{
		ListGraph::Edge edge = findEdge(this->g, xmap[g.u(e)], xmap[g.v(e)]);
		this->edges->insert(edge);
		res += this->weight[edge];
	}
	
	return res;
}
