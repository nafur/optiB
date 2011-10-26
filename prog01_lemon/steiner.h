#pragma once

#include "lemon/list_graph.h"

#include <set>

using namespace std;
using namespace lemon;

struct Steiner
{
	private:
		const ListGraph& g;
		const ListGraph::EdgeMap<int>& weight;
		
	public:
		Steiner(const ListGraph& graph, const ListGraph::EdgeMap<int>& weight):
			g(graph),
			weight(weight),
			s(0),
			sweight(0)
			{}
		~Steiner()
		{
			if (this->s != 0) delete this->s;
			if (this->sweight != 0) delete this->sweight;
		}
		
		ListGraph* s;
		ListGraph::EdgeMap<int>* sweight;
		
		int steiner(const set<ListGraph::Node> terminals);
};
