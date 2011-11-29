#pragma once

#include <set>

#include <lemon/list_graph.h>

using namespace std;
using namespace lemon;

struct Redundant
{
	private:
		const ListGraph& g;
		const ListGraph::EdgeMap<int>& weight;
	
	public:
		Redundant(const ListGraph& graph, const ListGraph::EdgeMap<int>& weight):
			g(graph),
			weight(weight),
			redundant(0)
			{}
		
		~Redundant()
		{
			if (this->redundant != 0) delete this->redundant;
		}
		
		set<ListGraph::Edge>* redundant;
		
		int redundant();
}