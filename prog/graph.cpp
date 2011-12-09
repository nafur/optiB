#include "graph.h"

void readTerminals(const string& filename, const ListGraph& g, set<ListGraph::Node>& terminals)
{
	ifstream file;
	file.open(filename);
	string line;
	while (! file.eof())
	{
		getline(file, line);
		if (line.size() == 0) continue;
		terminals.insert(g.nodeFromId(atoi(line.c_str()) - 1));
	}
	file.close();
}

struct TestEOL { bool operator()(char c) { return c == '\n'; } };

void readMatrix(const string& filename, ListGraph& g, ListGraph::EdgeMap<int>& weight)
{
	g.clear();
	// get number of lines / nodes
	fstream f(filename);
	TestEOL test;
	int count = count_if(istreambuf_iterator<char>(f), istreambuf_iterator<char>(), test);
	
	ListGraph::Node* nodes;
	nodes = new ListGraph::Node[count];
	
	for (int i = 0; i < count; i++) nodes[i] = g.addNode();
	
	ifstream file;
	file.open(filename);
	
	int tmp;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			file >> ws >> tmp;
			if (i < j)
			{
				ListGraph::Edge e = g.addEdge(nodes[i], nodes[j]);
				weight[e] = tmp;
			}
		}
	}
		
	file.close();
	
	delete[] nodes;
}

void dumpGraph(const string& filename, const ListGraph& g, const ListGraph::EdgeMap<int>& weight)
{
	graphWriter(g, filename).edgeMap("weight", weight).run();
}

void dumpGraph(const string& filename, const ListGraph& g)
{
	ListGraph::EdgeMap<int> weight(g);
	graphWriter(g, filename).edgeMap("weight", weight).run();
}

void dumpSubGraph(const string& filename, const ListGraph& g, const set<ListGraph::Edge>& edges)
{
	ListGraph sub;
	ListGraph::EdgeMap<ListGraph::Edge> edgemap(g);
	
	GraphCopy<ListGraph, ListGraph> copy(g, sub);
	copy.edgeRef(edgemap);
	copy.run();
	
	for (ListGraph::EdgeIt e(g); e != INVALID; ++e)
	{
		if (edges.count(e) == 0) sub.erase(edgemap[e]);
	}
	
	dumpGraph(filename, sub);
}

void dumpSubGraph(const string& filename, const ListGraph& g, const set<ListGraph::Node>& nodes)
{
	ListGraph sub;
	ListGraph::NodeMap<ListGraph::Node> nodemap(g);
	
	GraphCopy<ListGraph, ListGraph> copy(g, sub);
	copy.nodeRef(nodemap);
	copy.run();
	
	for (ListGraph::NodeIt n(g); n != INVALID; ++n)
	{
		if (nodes.count(n) == 0) sub.erase(nodemap[n]);
	}
	
	dumpGraph(filename, sub);
}
