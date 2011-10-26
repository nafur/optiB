#include "steiner.h"

#include "dijkstra.h"
#include "debug.h"

#include <map>
#include <iostream>

/*
	To calculate all shortest paths, we use dijkstra.
	This is not the fastest possible solution, but still reasonably fast.
*/

int Steiner::steiner(const set<ListGraph::Node> terminals)
{
	cerr << "start" << endl;
	if (this->s != 0) delete this->s;
	this->s = new ListGraph();
	
	cerr << "dijkstras" << endl;

	// perform dijkstra for every terminal
	ListGraph::NodeMap<Dijkstra*> dijk(this->g);
	for (set<ListGraph::Node>::iterator it = terminals.begin(); it != terminals.end(); ++it)
	{
		dijk[*it] = new Dijkstra(this->g, this->weight);
		dijk[*it]->dijkstra(*it);
	}

	dump(this->g, this->weight);	
	
	cerr << "intermediate" << endl;
	
	// build intermediate graph
	ListGraph intermediate;
	ListGraph::EdgeMap<int> iweight(intermediate);
	map<ListGraph::Node, ListGraph::Node> stog;
	map<ListGraph::Node, ListGraph::Node> gtos;
	
	for (set<ListGraph::Node>::iterator it = terminals.begin(); it != terminals.end(); ++it)
	{
		ListGraph::Node n = intermediate.addNode();
		stog[n] = *it;
		gtos[*it] = n;
	}
	dump(intermediate, iweight);
	cerr << "inserting edges..." << endl;
	for (ListGraph::NodeIt it1(intermediate); it1 != INVALID; ++it1)
	{
		ListGraph::NodeIt it2 = it1;
		++it2;
		for (; it2 != INVALID; ++it2)
		{
			cerr << "inserting edge " << intermediate.id(it1) << " and " << intermediate.id(it2) << endl;
			ListGraph::Edge e;
			cerr << "addEdge..." << endl;
			intermediate.addEdge(it1, it2);
			cerr << "setting weight" << endl;
			iweight[e] = (*dijk[stog[it1]]->dist)[stog[it2]];
		}
	}
	
	
	cerr << "cleanup" << endl;

	// clean up dijkstras
	for (ListGraph::NodeIt n(this->g); n != INVALID; ++n)
		delete dijk[n];
	
	return 0;
}
