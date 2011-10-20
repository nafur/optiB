#include "vertex.h"

vertex::vertex(vertex_id id):id(id),edges(){};
vertex::vertex(const vertex& v):id(v.id),edges(v.edges){}

bool vertex::is_neighbour(vertex_id id){
	return edges.find(id) != edges.end();
}
