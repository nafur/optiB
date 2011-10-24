#include "prim.h"
#include "graph.h"

#include <set>
#include <queue>

using namespace std;
using namespace lemon;

void Prim::prim()
{
	set<ListGraph::Node> vertices;
	priority_queue<cmpEdge> edges;
	
	if (this->mst != 0) delete this->mst;
	this->mst = new set<ListGraph::Edge>();
	
	ListGraph::NodeIt n(this->g);
	vertices.insert(n);
	ListGraph::Node cur = n;
	
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
		do
		{
			if (edges.size() == 0)
			{
				cerr << "edges.size() == 0. it seems the graph is not connected..." << endl;
				exit(1);
			}
			best = edges.top().e;
			edges.pop();
			next = this->g.u(best);
			if (vertices.count(next)) next = this->g.v(best);
		} // drop edge if it would close a cycle
		while (vertices.count(next) > 0);
		
		// add to mst
		vertices.insert(next);
		this->mst->insert(best);
		cur = next;
	}
}
