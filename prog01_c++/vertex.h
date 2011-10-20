#pragma once

#include <map>
#include <string>
using std::string;
using std::map;

#include "edge.h"

struct vertex{
	typedef unsigned int vertex_id;
	vertex_id id;
	typedef map<vertex_id, edge>::iterator edge_it;
	map<vertex_id,edge> edges;
	
	vertex(vertex_id);
	vertex(const vertex&);
	
	bool is_neighbour(vertex_id);
};
