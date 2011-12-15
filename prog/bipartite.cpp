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
			(*this->classes)[other] = nextCol;
			if (! this->colorDFS(other)) return false;
		}
		else if ( oCol != nextCol) return false;
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
	}
	
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