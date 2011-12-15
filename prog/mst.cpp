#include "mst.h"
#include "graph.h"

#include <iostream>
#include <set>
#include <queue>

using namespace std;
using namespace lemon;

int MST::kruskal()
{
	ListGraph::NodeMap<int> vertices(this->g);
	
	int cnt = countNodes(this->g);
	int* map = new int[cnt];
	
	// sorted edges
	priority_queue<cmpEdge> edges;
	for (ListGraph::EdgeIt e(this->g); e != INVALID; ++e)
		edges.push(cmpEdge(e, this->weight[e]));
	
	if (this->mst != 0) delete this->mst;
	this->mst = new set<ListGraph::Edge>();

	// initialize node sets	
	int nodenum = 0;
	for (ListGraph::NodeIt n(this->g); n != INVALID; ++n)
	{ // vertices just maps to [0, nodeCount), sets are maintained in map
		vertices[n] = nodenum;
		map[nodenum] = nodenum;
		nodenum++;
	}
	int weight = 0;
	ListGraph::Edge cur;
	
	while (edges.size() > 0)
	{
		cur = edges.top().e;
		int s1 = map[vertices[this->g.u(cur)]], s2 = map[vertices[this->g.v(cur)]];
		if (s1 == s2)
		{ // vertices are in the same set
			edges.pop();
			continue;
		}
		weight += edges.top().w;
		// update sets
		for (int i=0; i<cnt; i++)
			if (map[i] == s1) map[i] = s2;
		edges.pop();

		this->mst->insert(cur);
	}
	
	delete[] map;
	
	return weight;
}

int MST::prim()
{
	set<ListGraph::Node> vertices;
	priority_queue<cmpEdge> edges;
	
	if (this->mst != 0) delete this->mst;
	this->mst = new set<ListGraph::Edge>();
	
	ListGraph::NodeIt n(this->g);
	vertices.insert(n);
	ListGraph::Node cur = n;
	
	int weight = 0;
	
	while (vertices.size() < (unsigned int)countNodes(this->g))
	{
		// add all edges from cur node
		for (ListGraph::IncEdgeIt e(this->g, cur); e != INVALID; ++e)
		{
			ListGraph::Edge edge = e;
			edges.push(cmpEdge(edge, this->weight[edge]));
		}
		
		// find best edge
		ListGraph::Edge best;
		ListGraph::Node next;
		int curw = 0;
		do
		{
			if (edges.size() == 0)
			{
				cerr << "edges.size() == 0. it seems the graph is not connected..." << endl;
				exit(1);
			}
			best = edges.top().e;
			curw = edges.top().w;
			edges.pop();
			next = this->g.u(best);
			if (vertices.count(next)) next = this->g.v(best);
		} // drop edge if it would close a cycle
		while (vertices.count(next) > 0);
		
		// add to mst
		vertices.insert(next);
		this->mst->insert(best);
		weight += curw;
		cur = next;
	}
	return weight;
}
