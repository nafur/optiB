#pragma once

#include <map>
#include <iostream>

using std::map;
using std::istream;
using std::ostream;

#include "vertex.h"
#include "edge.h"

struct graph{
	typedef map<vertex::vertex_id, vertex>::iterator vertex_it;
	map<vertex::vertex_id, vertex> vertices;
	
	graph& add_vertex(vertex::vertex_id);
	graph& rm_vertex(vertex::vertex_id);
	vertex& get_vertex(vertex::vertex_id, vertex_it&);
	vertex& get_vertex(vertex::vertex_id);
	
	graph& connect(vertex::vertex_id, vertex::vertex_id, const edge&);
	graph& disconnect(vertex::vertex_id, vertex::vertex_id);	
	
	istream& readlgf(istream&);
	ostream& writelgf(ostream&);
};
