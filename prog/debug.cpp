#include "debug.h"

void dump(const ListGraph& g, const ListGraph::EdgeMap<int>& weight)
{
	cout << "dumping graph " << &g << endl;
	cout << "\tnodes: ";
	for (ListGraph::NodeIt n(g); n != INVALID; ++n)
		cout << g.id(n) << ", ";
	cout << endl;
	cout << "\tedges:" << endl;
	for (ListGraph::NodeIt n(g); n != INVALID; ++n)
	{
		cout << "\t\tnode " << g.id(n) << ": ";
		for (ListGraph::IncEdgeIt e(g, n); e != INVALID; ++e)
		{
			if (g.u(e) == n) cout << g.id(g.v(e));
			else cout << g.id(g.u(e));
			cout << " (" << weight[e] << "), ";
		}
		cout << endl;
	}
	cout << "finished dump" << endl;
}

void dump(const Dijkstra& d, const ListGraph& g)
{
	cout << "dumping dijkstra " << &d << endl;
	for (ListGraph::NodeIt n(g); n != INVALID; ++n)
	{
		cout << g.id(n)+1 << ": dist = " << (*d.dist)[n] << ", pred = " << g.id((*d.pred)[n])+1 << endl;
	}
	cout << "finished dump" << endl;
}

void dump(const vector<vector<int> >& data)
{
	cout << "dumping table " << &data << endl;
	for (vector<vector<int> >::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		for (vector<int>::const_iterator it2 = it->begin(); it2 != it->end(); ++it2)
		{
			cout << *it2 << ", ";
		}
		cout << endl;
	}
	cout << "finished dump" << endl;
}