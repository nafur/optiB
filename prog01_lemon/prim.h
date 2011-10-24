#pragma once

#include <set>

#include "lemon/list_graph.h"

using namespace std;
using namespace lemon;

struct Prim
{
	private:
		ListGraph& g;
		ListGraph::EdgeMap<int>& weight;
		
	public:
		Prim(ListGraph& graph, ListGraph::EdgeMap<int>& weight):
			g(graph),
			weight(weight),
			mst(0)
			{}
		~Prim()
		{
			if (this->mst != 0) delete this->mst;
		}
		
		set<ListGraph::Edge>* mst;
		void prim();
};
