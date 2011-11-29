#include "redundant.h"

#include "prim.h"

int Redundant::redundant()
{
	if (this->s != 0) delete this->s;
	this->s = new ListGraph();
	if (this->sweight != 0) delete this->sweight;
	this->sweight = new ListGraph::EdgeMap<int>(*this->s);
	
	// copy graph
	GraphCopy<ListGraph, ListGraph> copy(*this->g, *this->s);
	
	
	int overallw = 0;
	
	Prim mst(this->g, this->weight);
	mst.prim();
	
	return overallw;
}