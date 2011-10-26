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
		cerr << "read " << line << endl;
		terminals.insert(g.nodeFromId(atoi(line.c_str())));
	}
	file.close();
}
