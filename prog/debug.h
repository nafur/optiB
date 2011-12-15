#pragma once

#include <iostream>
#include <set>
#include <ctime>
#include <vector>

#include "dijkstra.h"

#include <lemon/list_graph.h>

#define START_TIMER(x) clock_t x = clock();
#define STOP_TIMER(x) cout << "this took " << (clock() - x) / (CLOCKS_PER_SEC / 1000) << " ms" << endl << endl;

using namespace std;
using namespace lemon;

void dump(const ListGraph& g, const ListGraph::EdgeMap<int>& weight);
//void dump(ListGraph::EdgeMap<int>& map);
//void dump(ListGraph::NodeMap<int>& map);
//void dump(set<ListGraph::Node>& set);
void dump(const Dijkstra& d, const ListGraph& g);
void dump(const vector<vector<int> >& data);