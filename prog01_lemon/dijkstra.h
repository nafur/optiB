#pragma once

#include "lemon/list_graph.h"

using namespace std;
using namespace lemon;

struct Dijkstra
{
	private:
		const ListGraph& g;
		const ListGraph::EdgeMap<int>& weight;
	
	public:
		Dijkstra(const ListGraph& graph, const ListGraph::EdgeMap<int>& weight):
			g(graph), 
			weight(weight), 
			dist(0),
			pred(0)
			{}
		~Dijkstra()
		{
			if (this->dist != 0) delete this->dist;
			if (this->pred != 0) delete this->pred;
		}
	
		ListGraph::NodeMap<int>* dist;
		ListGraph::NodeMap<ListGraph::Node>* pred;
		void dijkstra(const ListGraph::Node& source);
};
