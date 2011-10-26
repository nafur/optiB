#include "dijkstra.h"
#include "graph.h"

#include <iostream>

#include <queue>

/*
	Just a hint, if you look closer at this algorithm:
	
	This is not exactly dijkstra!
	Dijkstra would always select the node with the smallest distance available, thus resulting in at most n iterations overall.
	This selection however requires to store the node distance pairs in a fibbonaci heap to allow fast reorganizing.
	
	Instead, we just use a regular priority queue with the following mechanism:
	If we find a shorter path to some node (i.e. we update dist and pred) we insert this node to the queue.
	Thus, nodes might be contained multiple times (though less than n times) in the queue.
	However, we pop always the nearest node (if the node has already been processed, we drop it).
	At the end, when all nodes are processed, the remaining entries in the queue are dropped.
	
	The worst-case runtime is worse than one would expect from dijkstra, but in practice its good :-)
*/

void Dijkstra::dijkstra(const ListGraph::Node& source)
{
	// create new result maps
	if (this->dist != 0) delete this->dist;
	this->dist = new ListGraph::NodeMap<int>(this->g);
	if (this->pred != 0) delete this->pred;
	this->pred = new ListGraph::NodeMap<ListGraph::Node>(this->g);
	
	// initialize distances
	for (ListGraph::NodeIt n(this->g); n != INVALID; ++n)
		(*this->dist)[n] = -1;
	(*this->dist)[source] = 0;
	(*this->pred)[source] = source;
	
	// start at source
	priority_queue<cmpNode> todo;
	todo.push(cmpNode(source, 0));
	
	// we count the number of processed nodes
	// this should reduce the runtime, but is not necessary for this algorithm to work
	int cnt = 0;
	int max = countNodes(this->g);
	
	while (! todo.empty())
	{
		// already processed all nodes, we are done
		if (cnt == max) break;
		
		// get nearest node from queue
		ListGraph::Node cur = todo.top().n;
		int curdist = todo.top().w;
		todo.pop();

		// we already processed this node (with a smaller distance), so drop it
		if ((*this->dist)[cur] < curdist) continue;
		cnt++; // we got another one
		
		for (ListGraph::IncEdgeIt e(this->g, cur); e != INVALID; ++e)
		{ // go through all edges of this node
			ListGraph::Node v = this->g.u(e);
			if (v == cur) v = this->g.v(e);
			
			int w = this->weight[e];
			
			if (((*this->dist)[v] == -1) || ((*this->dist)[cur] + w < (*this->dist)[v]))
			{ // other node of the edge has no or larger distance
				(*this->dist)[v] = (*this->dist)[cur] + w;
				(*this->pred)[v] = cur;
				// insert it, possibly again, into the queue
				todo.push(cmpNode(v, (*this->dist)[v]));
			}	
		}
	}
}
