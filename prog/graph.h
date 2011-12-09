#pragma once

#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;
using namespace lemon;

// needed to put edges in priority queue
struct cmpEdge
{
	ListGraph::Edge e;
	int w;
	
	cmpEdge(const ListGraph::Edge& e, const int w):
		e(e),
		w(w)
		{}
	cmpEdge(const cmpEdge& edge):
		e(edge.e),
		w(edge.w)
		{}
	
	bool operator<(const cmpEdge& e) const
	{
		return this->w > e.w;
	}
};

// needed to put nodes in priority queue
struct cmpNode
{
	ListGraph::Node n;
	int w;
	
	cmpNode(const ListGraph::Node& n, const int w):
		n(n),
		w(w)
		{}
	cmpNode(const cmpNode& n):
		n(n.n),
		w(n.w)
		{}
	
	bool operator<(const cmpNode& n) const
	{
		return this->w > n.w;
	}
};

// special read helper
void readTerminals(const string& filename, const ListGraph& g, set<ListGraph::Node>& terminals);
void readMatrix(const string& filename, ListGraph& g, ListGraph::EdgeMap<int>& weight);

// dump graphs to lgf format
void dumpGraph(const string& filename, const ListGraph& g, const ListGraph::EdgeMap<int>& weight);
void dumpGraph(const string& filename, const ListGraph& g);
void dumpSubGraph(const string& filename, const ListGraph& g, const set<ListGraph::Edge>& edges);
