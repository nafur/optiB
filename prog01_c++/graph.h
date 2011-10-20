#pragma once

#include <map>
#include <iostream>

using std::map;
using std::istream;
using std::ostream;

#include "vertex.h"
#include "edge.h"

struct graph{
	map<vertex::vertex_id, vertex> vertices;
	map<vertex::vertex_id, map<vertex::vertex_id, edge>> edges;
	
	istream& readlgf(istream&);
	ostream& writelgf(ostream&);
};
