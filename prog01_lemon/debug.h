#pragma once

#include <iostream>
#include <set>

#include "lemon/list_graph.h"

using namespace std;
using namespace lemon;

void dump(const ListGraph& g, const ListGraph::EdgeMap<int>& weight);
//void dump(ListGraph::EdgeMap<int>& map);
//void dump(ListGraph::NodeMap<int>& map);
//void dump(set<ListGraph::Node>& set);
