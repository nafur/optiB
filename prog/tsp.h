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
		
		int degree(const ListGraph& g, const ListGraph::Node& n, const set<ListGraph::Edge>& edges, const ListGraph::NodeMap<ListGraph::Node>& mapping);
		int processEulerian(const ListGraph& eulerg, const ListGraph::NodeMap<ListGraph::Node>& eulernodemap, const ListGraph::Node& start, const bool addEdges);
	
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