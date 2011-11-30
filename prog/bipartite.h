#pragma once

#include <lemon/list_graph.h>

using namespace std;
using namespace lemon;

struct Bipartite
{
	private:
		const ListGraph& g;
		
		bool colorDFS(const ListGraph::Node& node);
	
	public:
		Bipartite(const ListGraph& graph):
			g(graph),
			classes(0)
			{}
		~Bipartite()
		{
			if (this->classes != 0) delete classes;
		}
		
		ListGraph::NodeMap<int>* classes;
		
		bool bipartite();
};