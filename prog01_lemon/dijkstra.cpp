#include "dijkstra.h"

#include <queue>

void Dijkstra::dijkstra(const ListGraph::Node& source)
{
	if (this->dist != 0) delete this->dist;
	this->dist = new ListGraph::NodeMap<int>(this->g);
	if (this->pred != 0) delete this->pred;
	this->pred = new ListGraph::NodeMap<ListGraph::Node>(this->g);
	
	for (ListGraph::NodeIt n(this->g); n != INVALID; ++n)
		(*this->dist)[n] = -1;
	(*this->dist)[source] = 0;
	
	priority_queue<ListGraph::Node> todo;
	todo.push(source);
	
	while (! todo.empty())
	{
		ListGraph::Node cur = todo.top();
		todo.pop();
		
		for (ListGraph::IncEdgeIt e(this->g, cur); e != INVALID; ++e)
		{
			ListGraph::Node v = this->g.u(e);
			if (v == cur) v = this->g.v(e);
			
			int w = this->weight[e];
			
			if (((*this->dist)[v] == -1) || ((*this->dist)[cur] + w < (*this->dist)[v]))
			{
				(*this->dist)[v] = (*this->dist)[cur] + w;
				(*this->pred)[v] = cur;
				todo.push(v);
			}	
		}
	}
}
