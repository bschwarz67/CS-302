#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
using namespace std;

class HungryCowsEasy {
	public:
		vector<int> findFood(vector <int> &cows, vector <int> &barns);
};

vector<int> HungryCowsEasy::findFood(vector <int> &cows, vector <int> &barns) {
	string buffer;
	int low, high;

	//map with x coordinate of barns as key and index in the maps vector as value
	map<long long, int> barnsMap;
	map<long long, int>::iterator barnsMapIterator;
	
	//vector that holds at the index that the cow in question is at in the cows vector: the index at which the closest barn is at in the barns vectorn
	vector<int> cowsInBarns(cows.size());

	//put the barn coordinates, corresponding vector indexes into a map.
	for(int i = 0; i < barns.size(); i++) {
		barnsMap.insert(pair<long long, int>(barns[i], i));
	}

	//sentinelize nodes for cases when there are cows that are a lower distance from zero or a higher distance from zero than any of the barns.
	long long bignum = 1000000000;
	bignum *= 1000;
	barnsMap.insert(pair<long long, int>(bignum, -1));
	bignum *= -1;
	barnsMap.insert(pair<long long, int>(bignum, -1));
	

	//iterate through cows vector, for every cow coordinate, find the closest barn coordinate stored in the barns map.
	//there are 3 possibilities
	//1 the cow coordinate is a barn coordinate as well, in this case the cowsInBarns vector gets the index of this barns coordinate at the index of the cow in cows
	//2 the cow coordinate is equidistant to or closer to the barn that is less distance along the x axis than the cow, in this case cowsInBarns
	//vector gets the index of this barns coordinate at the index of the cow in cows
	//3  the cow coordinate is closer to the barn that is more distance along the x axis than the cow, in this case cowsInBarns vector gets the
	//index of this barns coordinate at the index of the cow in cows
	
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
	
	return cowsInBarns;	
}

int main () {
	HungryCowsEasy hce = HungryCowsEasy();
	vector <int> cows;
	vector <int> barns;
	vector <int> cowsInBarns;


	//test various input parameters to our function
	cows.push_back(0);
	barns.push_back(-5);
	barns.push_back(5);

	cowsInBarns = hce.findFood(cows, barns);
	for(int i = 0; i < cowsInBarns.size(); i++) {
		if(i == cowsInBarns.size() - 1) cout << cowsInBarns[i] << endl;
		else cout << cowsInBarns[i] << ' ';
	}
		
	cows.clear();
	barns.clear();
	cowsInBarns.clear();

	cows.push_back(7);
	cows.push_back(7);
	barns.push_back(7);
	barns.push_back(10000);

	cowsInBarns = hce.findFood(cows, barns);
	for(int i = 0; i < cowsInBarns.size(); i++) {
		if(i == cowsInBarns.size() - 1) cout << cowsInBarns[i] << endl;
		else cout << cowsInBarns[i] << ' ';
	}

	cows.clear();
	barns.clear();
	cowsInBarns.clear();

	cows.push_back(2);
	cows.push_back(6);
	cows.push_back(0);
	cows.push_back(4);
	cows.push_back(8);
	barns.push_back(3);
	barns.push_back(-1);
	barns.push_back(5);
	barns.push_back(1);
	barns.push_back(7);

	cowsInBarns = hce.findFood(cows, barns);
	for(int i = 0; i < cowsInBarns.size(); i++) {
		if(i == cowsInBarns.size() - 1) cout << cowsInBarns[i] << endl;
		else cout << cowsInBarns[i] << ' ';
	}
	return 0;
}
