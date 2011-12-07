#pragma once

#include <lemon/list_graph.h>
#include <set>

using namespace std;
using namespace lemon;

struct TSP
{
	private:
		const ListGraph& g;
		const ListGraph::EdgeMap<int>& weight;
	
	public:
		TSP(const ListGraph& graph, const ListGraph::EdgeMap<int>& weight):
			g(graph),
			weight(weight),
			edges(0)
			{}
		~TSP()
		{
			if (this->edges != 0) delete this->edges;
		}
		
		set<ListGraph::Edge>* edges;
		
		int tsp();
};