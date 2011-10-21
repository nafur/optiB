#pragma once

#include <map>

#include "graph.h"
#include "edge.h"
#include "vertex.h"

void dijkstra(graph& g, vertex source, std::map<vertex::vertex_id, edge::weight_type> weights, std::map<vertex::vertex_id, vertex::vertex_id> pred);
