#pragma once

#include "lemon/list_graph.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;
using namespace lemon;

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

void readTerminals(const string& filename, const ListGraph& g, set<ListGraph::Node>& terminals);
