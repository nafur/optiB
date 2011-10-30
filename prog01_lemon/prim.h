#pragma once

#include <set>

#include <lemon/list_graph.h>

using namespace std;
using namespace lemon;

struct Prim
{
	private:
		const ListGraph& g;
		const ListGraph::EdgeMap<int>& weight;
		
	public:
		Prim(const ListGraph& graph, const ListGraph::EdgeMap<int>& weight):
			g(graph),
			weight(weight),
			mst(0)
			{}
		~Prim()
		{
			if (this->mst != 0) delete this->mst;
		}
		
		set<ListGraph::Edge>* mst;
		
		// returns weight of mst
		int prim();
};
