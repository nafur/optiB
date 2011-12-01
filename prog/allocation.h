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
			plants(plants)
		{
			this->load(filename);
		}
		~Allocation()
		{
//			if (this->values != 0) delete[] this->values;
		}
		
		int allocate();
};
