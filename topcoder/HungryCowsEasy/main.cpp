#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main () {
	string buffer;
	int low, high;

	//vector that holds x coordinates of cows, filled with random numbers for testing
	vector<int> cows;
	//cows.push_back(2);
	//cows.push_back(6);
	//cows.push_back(0);
	cows.push_back(4);
	cows.push_back(4);
	
	//vector that holds x coordinates of barns, filled with random numbers for testing
	vector<int> barns;
	//barns.push_back(3);
	//barns.push_back(-1);
	//barns.push_back(5);
	barns.push_back(4);
	barns.push_back(8);

	//map with x coordinate of barns as key and index in the maps vector as value
	map<int, int> barnsMap;
	map<int, int>::iterator barnsMapIterator;
	
	//vector that holds at the index that the cow in question is at in the cows vector, the index at which the closest barn is at in the barns vectorn
	vector<int> cowsInBarns(cows.size());

	//put the barn coordinates, corresponding vector indexes into a map.
	for(int i = 0; i < barns.size(); i++) {
		barnsMap.insert(pair<int, int>(barns[i], i));
	}
	

	//iterate through cows vector, for every cow coordinate, find the closest barn coordinate stored in the barns map.
	//there are 3 possibilities
	//1 the cow coordinate is a barn coordinate as well, in this case the cowsInBarns vector gets the index of this barns coordinate at the index of the cow in cows
	//2 the cow coordinate is equidistant to or closer to the barn that is less distance along the x axis than the cow, in this case cowsInBarns vector gets the index of this barns coordinate at the index of the cow in cows
	//3  the cow coordinate is closer to the barn that is more distance along the x axis than the cow, in this case cowsInBarns vector gets the index of this barns coordinate at the index of the cow in cows
	for(int i = 0; i < cows.size(); i++) {
		barnsMapIterator = barnsMap.lower_bound(cows[i]);
		if(barnsMapIterator->first == cows[i]) {
			cowsInBarns[i] = barnsMapIterator->second;
		}
		else {
			high = barnsMapIterator->first;
			barnsMapIterator--;
			low = barnsMapIterator->first;
			if(high - cows[i] <= cows[i] - low) {
				cowsInBarns[i] = barnsMapIterator->second;
			}
			else {
				barnsMapIterator++;
				cowsInBarns[i] = barnsMapIterator->second;
			}
		}
	}
	
	//print values to test
	for(int i = 0; i < cowsInBarns.size(); i++) {
		cout << cowsInBarns[i] << endl;
	}


	return 0;
}
