#pragma once

#include <string>
#include <vector>

using namespace std;

struct Allocation
{
	private:
		int machines;
		int plants;
		
		vector<vector<int>> values;
	
		void load(const string& filename);
	
	public:
		Allocation(const string& filename, const int plants):
			machines(0),
			plants(plants),
			distribution(0)
		{
			this->load(filename);
		}
		~Allocation()
		{
			if (this->distribution != 0) delete this->distribution;
		}
		
		vector<int>* distribution;
		int allocate();
};
