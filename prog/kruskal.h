#pragma once

#include <set>

#include <lemon/list_graph.h>

using namespace std;
using namespace lemon;

struct Kruskal
{
	private:
		const ListGraph& g;
		const ListGraph::EdgeMap<int>& weight;
		
	public:
		Kruskal(const ListGraph& graph, const ListGraph::EdgeMap<int>& weight):
			g(graph),
			weight(weight),
			mst(0)
			{}
		~Kruskal()
		{
			if (this->mst != 0) delete this->mst;
		}
		
		set<ListGraph::Edge>* mst;
		
		// returns weight of mst
		int kruskal();
};
