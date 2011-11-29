#include "kruskal.h"
#include "graph.h"

#include <iostream>
#include <set>
#include <queue>

using namespace std;
using namespace lemon;

int Kruskal::kruskal()
{
	ListGraph::NodeMap<int> vertices(this->g);
	
	int cnt = countNodes(this->g);
	int map[cnt];
	
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
	
	return weight;
}
