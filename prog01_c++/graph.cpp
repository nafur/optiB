#include "graph.h"

#include <algorithm>
#include <assert.h>
#include <string>
#include <sstream>
using std::pair;
using std::string;
using std::stringstream;
using std::getline;
using std::istream;
using std::ostream;

graph& graph::add_vertex(vertex::vertex_id id){
	assert(vertices.insert(std::pair<vertex::vertex_id, vertex>(id,vertex(id))).second);
	return *this;
}

graph& graph::rm_vertex(vertex::vertex_id id){
	assert(vertices.erase(id) == 1);
	for(vertex_it vit = vertices.begin(); vit != vertices.end(); ++vit){
		vit->second.edges.erase(id);
	}
	return *this;
}

vertex& graph::get_vertex(vertex::vertex_id id, vertex_it& vit){
	vit = vertices.find(id);
	assert(vit != vertices.end());
	return vit->second;
}

vertex& graph::get_vertex(vertex::vertex_id id){
	vertex_it vit;
	return get_vertex(id, vit);
}

graph& graph::connect(vertex::vertex_id id1, vertex::vertex_id id2, const edge& e){
	vertex& v1 = get_vertex(id1);
	vertex& v2 = get_vertex(id2);
	
	assert(v1.edges.insert(pair<vertex::vertex_id, edge>(id2,e)).second);
	assert(v2.edges.insert(pair<vertex::vertex_id, edge>(id1,e)).second);
	
	return *this;
}

istream& graph::readlgf(istream& is){
	unsigned char mode;
	string line;
	while(!is.eof()){
		getline(is,line);
		if(line.size() == 0 || line[0] == '#') continue;
		else if(line == "@nodes") mode = 1;
		else if(line == "label") mode = 2;
		else if(line == "@edges") mode = 3;
		else if(line == "    weight") mode = 4;
		else{
			stringstream ss(line);
			if(mode == 2){
				vertex::vertex_id id;
				ss >> id;
				add_vertex(id);
			}
			else if(mode == 4){
				vertex::vertex_id id1, id2;
				edge::weight_type w;
				ss >> id1 >> id2 >> w;
				connect(id1, id2, edge(w));
			}
			else assert(false);
		}
	}
	return is;
}

ostream& graph::writelgf(ostream& os){
	os << "@nodes\nlabel\n";
	for(vertex_it it = vertices.begin(); it != vertices.end(); ++it){
		os << it->second.id << "\n";
	}
	os << "@edges\n    weight\n";
	for(vertex_it it = vertices.begin(); it != vertices.end(); ++it){
		vertex& v1 = it->second;
		for(vertex::edge_it it2 = v1.edges.begin(); it2 !=v1.edges.end(); ++it2)
			os << v1.id << " " << it2->first << it2->second.weight;
	}
	
	return os;
}

bool graph::has_vertex(vertex::vertex_id id) const{
	return vertices.find(id) != vertices.end();
}
