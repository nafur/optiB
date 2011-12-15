#include "allocation.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "debug.h"

void Allocation::load(const string& filename)
{
	ifstream file(filename);
	
	// skip "#max number of machines "
	file.seekg(24);

	file >> this->machines >> ws;
	string line;
	// skip column explanations
	getline(file, line);
	
	int tmp;		
	for (int i = 0; i <= this->machines; i++)
	{
		vector<int> v;
		// skip machine number
		file >> ws >> tmp;
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
	if (this->distribution != 0) delete this->distribution;
	this->distribution = new vector<int>();
	
	// make table for dynamic programming
	vector<vector<int> > f;
	// save number of machines allocated at current plant
	vector<vector<int> > dist;
	f.resize(this->machines + 1);
	dist.resize(this->machines + 1);
	for (vector<vector<int> >::iterator it = f.begin(); it != f.end(); ++it)
		it->resize(this->plants);
	for (vector<vector<int> >::iterator it = dist.begin(); it != dist.end(); ++it)
		it->resize(this->plants);

	// initialize last plant
	for (int i = 0; i <= this->machines; i++)
	{
		f[i][this->plants - 1] = this->values[i][this->plants - 1];
		dist[i][this->plants - 1] = i;
	}
	
	// iterate for all other plants
	for (int plant = this->plants - 2; plant >= 0; plant--)
	{
		// initialize first value
		f[0][plant] = this->values[0][plant];
		dist[0][plant] = 0;
		for (int machine = 1; machine <= this->machines; machine++)
		{
			int max = 0;
			for (int x = 0; x <= machine; x++)
			{ // try every combination
				if (this->values[x][plant] + f[machine-x][plant+1] > max)
				{
					max = this->values[x][plant] + f[machine-x][plant+1];
					dist[machine][plant] = x;
				}
			}
			f[machine][plant] = max;
		}
	}

	// retrieve distribution of machines
	// dist contains the number of machines allocated at the current plant
	this->distribution->resize(this->plants);
	int remaining = this->machines;
	for (int plant = 0; plant < this->plants; plant++)
	{
		(*this->distribution)[plant] = dist[remaining][plant];
		remaining -= dist[remaining][plant];
	}

	return f[this->machines][0];
}
