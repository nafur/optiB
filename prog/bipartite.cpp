#include "bipartite.h"

#include <set>
#include "graph.h"

bool Bipartite::colorDFS(const ListGraph::Node& node)
{
	int nextCol = ((*this->classes)[node] % 2) + 1;
	for (ListGraph::IncEdgeIt e(this->g, node); e != INVALID; ++e)
	{
		ListGraph::Node other = this->g.u(e);
		if (other == node) other = this->g.v(e);
		
		int oCol = (*this->classes)[other];
		
		if (oCol == 0)
		{
//			cout << "coloring node " << this->g.id(other) << " with " << nextCol << endl;
			(*this->classes)[other] = nextCol;
			if (! this->colorDFS(other)) return false;
		}
		else if ( oCol != nextCol)
		{
//				cout << "coloring node " << this->g.id(other) << " with " << nextCol << " failed!" << endl;
				return false;
		}
	}
	return true;
}

bool Bipartite::bipartite()
{
	if (this->classes != 0) delete this->classes;
	this->classes = new ListGraph::NodeMap<int>(this->g);
	
	set<ListGraph::Node> nodes;
	
	for (ListGraph::NodeIt n(this->g); n != INVALID; ++n)
	{ // start with no colors
		(*this->classes)[n] = 0;
		
		int i = this->g.id(n);
		if (i==12 || i==33 || i==18 || i==68 || i==53 || i==37 || i==54 || i==50 || i==45 || i==65 || i==24) nodes.insert(n);
	}
	
	dumpSubGraph("data_2/graph1_subgraph.lgf", this->g, nodes);
	
	for (ListGraph::NodeIt n(this->g); n != INVALID; ++n)
	{
		// node already has a color
		if ((*this->classes)[n] != 0) continue;
		
		// node has no color: perform dfs
		// w.l.o.g. n has color 1
		(*this->classes)[n] = 1;
		if (! this->colorDFS(n))
		{
			return false;
		}
	}
	
	return true;
}