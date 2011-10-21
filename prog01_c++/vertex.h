#pragma once

#include <map>
#include <string>

#include "edge.h"

struct vertex{
	typedef unsigned int vertex_id;
	vertex_id id;
	typedef std::map<vertex_id, edge>::iterator edge_it;
	std::map<vertex_id,edge> edges;
	
	vertex(vertex_id);
	vertex(const vertex&);
	
	bool is_neighbour(vertex_id);
};
