#include "graph.h"

void readTerminals(const string& filename, const ListGraph& g, set<ListGraph::Node>& terminals)
{
	ifstream file;
	file.open(filename);
	string line;
	while (! file.eof())
	{
		getline(file, line);
		if (line.size() == 0) continue;
		terminals.insert(g.nodeFromId(atoi(line.c_str()) - 1));
	}
	file.close();
}
