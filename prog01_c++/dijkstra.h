#pragma once

#include <map>

#include "graph.h"
#include "edge.h"
#include "vertex.h"

using namespace std;

void dijkstra(graph& g, map<vertex::vertex_id, edge::weight_type> weights, map<vertex::vertex_id, vertex::vertex_id> pred);
