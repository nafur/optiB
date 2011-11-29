#pragma once

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
			s(0),
			sweight(0)
			{}
		~Redundant()
		{
			if (this->s != 0) delete this->s;
			if (this->sweight != 0) delete this->sweight;
		}
		
		ListGraph* s;
		ListGraph::EdgeMap<int>* sweight;
		
		ListGraph::EdgeMap<ListGraph::Edge>* edgeReg;
		ListGraph::NodeMap<ListGraph::Node>* nodeReg;
				
		int redundant();
};