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
		cerr << "foo" << endl;
		for (ListGraph::IncEdgeIt e(this->g, cur); e != INVALID; ++e)
		{
			ListGraph::Edge edge = e;
			edges.push(cmpEdge(edge, this->weight[edge]));
		}
		
		cerr << "searching best..." << endl;
		ListGraph::Edge best;
		ListGraph::Node next;
		do
		{
			best = edges.top().e;
			cerr << "got best" << endl;
			edges.pop();
			next = this->g.u(best);
			cett << "got next" << endl;
			if (next == cur) next = this->g.v(best);
		}
		while (vertices.count(next) > 0);
		
		cerr << "Interint to vertices..." << endl;
		vertices.insert(next);
		cerr << "Inserting to mst... " << this->g.id(best) << endl;
		this->mst->insert(best);
		cerr << "done..." << endl;
	}
}
