#pragma once

#include <map>
#include <iostream>

#include "vertex.h"
#include "edge.h"

struct graph{
	typedef std::map<vertex::vertex_id, vertex>::iterator vertex_it;
	std::map<vertex::vertex_id, vertex> vertices;
	
	graph& add_vertex(vertex::vertex_id);
	graph& rm_vertex(vertex::vertex_id);
	vertex& get_vertex(vertex::vertex_id, vertex_it&);
	vertex& get_vertex(vertex::vertex_id);
	
	graph& connect(vertex::vertex_id, vertex::vertex_id, const edge&);
	graph& disconnect(vertex::vertex_id, vertex::vertex_id);	
	
	std::istream& readlgf(std::istream&);
	std::ostream& writelgf(std::ostream&);
	
	bool has_vertex(vertex::vertex_id) const;
};
