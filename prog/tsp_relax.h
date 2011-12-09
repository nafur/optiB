#pragma once

#include <lemon/list_graph.h>
#include <set>

using namespace std;
using namespace lemon;

struct TSPRelaxation
{
	private:
		const ListGraph& g;
		const ListGraph::EdgeMap<int>& weight;
		
	public:
		TSPRelaxation(const ListGraph& graph, const ListGraph::EdgeMap<int>& weight):
			g(graph),
			weight(weight)
			{}
		
		// first relaxation
		int mstPlusOne();
		// second relaxation
		int mstOnSubgraph();
};