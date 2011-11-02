#include <assert.h>
#include <iostream>
#include <vector>

using std::vector; using std::cout; using std::cerr; using std::ostream;

struct knapsack_field{
	unsigned int height, width;
	vector<double> data;
	
	static const double infty;
	
	knapsack_field(unsigned int height, unsigned int width):
		height(height), width(width), data(width*height, infty){}
	double& operator()(unsigned int i, unsigned int j){
		assert(i >= 0); assert(i < height);
		assert(j >= 0); assert(j < width);
		return data[i * width + j];
	}
	
	double operator()(unsigned int i, unsigned int j) const{
		assert(i >= 0); assert(i < height);
		assert(j >= 0); assert(j < width);
		return data[i * width + j];	
	}
};

const double knapsack_field::infty = -1.0/0.0;

ostream& operator<<(ostream& os, const knapsack_field& f){
	os << "B\t";
	
	for(unsigned int j = 0; j < f.width; ++j)
		os << "f" << f.width - j << "(b)\t";
	os << "\n";
	
	for(unsigned int j = 0; j < f.width +1; ++j)
		os << "--------";
	os << "\n";
	
	for(unsigned int i = 0; i < f.height; ++i){
		os << i << "\t";
		for(unsigned int j = 0; j < f.width; ++j){
			os << f(i,j) <<"\t";
		}
		os << "\n";
	}
	return os;
}

struct item{
	double profit;
	unsigned int weight;
	
	item(double profit, int weight):
		profit(profit), weight(weight){}
};

int knapsack(const vector<item>& items, unsigned int limit, bool multi = true){
	if(items.size() == 0) return 0;
	
	
	knapsack_field field(limit+1, items.size());
	
	//linke Spalte
	{
		unsigned int j = 0;
		for(unsigned int i = 0; i <= limit / items[j].weight; ++i){
			field(i*items[j].weight, j) = i * items[j].profit;
		}
	}
	
	//alle weiteren Spalten
	for(unsigned int j = 1; j < items.size(); ++j){
		for(unsigned int i = 0; i <= limit; ++i){
			double maximum = knapsack_field::infty;
			for(unsigned int k = 0; k * items[j].weight <= i && (multi || k <= 1); ++k){
				double& content = field(i - items[j].weight * k, j-1);
				if(content != knapsack_field::infty 
					&& content + k * items[j].profit > maximum)
						maximum = content + k * items[j].profit;
			}
			field(i,j)=maximum;
		} 
	}
	
	int maximum = knapsack_field::infty;
	{
		unsigned int j = field.width-1;
		for(unsigned int i = 0; i < field.height; ++i){
			if(field(i,j) > maximum)
				maximum = field(i,j);
		}	
	}
	
	cerr << field;
	
	return maximum;
}


int main(){
	std::cout << "Solution 1: " 
		<< knapsack(vector<item>{item(1,1), item(4,3), item(3,2)}, 4, false) << "\n";
	std::cout << "Solution 2: "
		<< knapsack(vector<item>{item(.5,1), item(4,3), item(3,2)}, 5, true) << "\n";
	
}
