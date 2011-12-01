#include "allocation.h"

#include <iostream>
#include <fstream>
#include <sstream>

void Allocation::load(const string& filename)
{
	ifstream file(filename);
	
	file.seekg(24);

	file >> this->machines >> ws;
	string line;
	getline(file, line);
	
	int tmp;
		
	for (int i = 0; i < this->machines; i++)
	{
		vector<int> v;
		for (int j = 0; j < this->plants; j++)
		{
			file >> ws >> tmp;
			v.push_back(tmp);
		}
		this->values.push_back(v);
	}
}

int Allocation::allocate()
{
	return 0;
}