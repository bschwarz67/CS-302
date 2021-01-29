#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;
class BuildingAdvertise {
	public:
		long getMaxArea(vector<int> h, int n);
};


long BuildingAdvertise::getMaxArea(vector<int> h, int n) {
	vector<int> R; //vector will hold the computed heights of the buildings
	int j = 0;
	int s;
	long long l, r, height, length;
	long rv, nv;
	int m = h.size();
	multimap <int, int> B;	//will store a pair with the height of the building as the key and the index of the building as the value
	multimap <int, int>::iterator BIT;
	set <int> X;	//stores the indexes of the buildings that have already been processed
	set <int>::iterator XIT;


	R.push_back(0); //add the first sentinel at index 0

	//compute R as described in the topcoder problem statement
	for(int i = 0; i < n; i++) {
		R.push_back(h[j]);
		s = (j+1) % m;
		h[j] = ( (h[j] ^ h[s] ) + 13 ) % 835454957;
		j = s;
	}
	R.push_back(0); //add the second sentinel at index n + 1

	//store information for every 'building' in R in B with the key being the height of the building and the value being the index of the building
	for(int i = 0; i < R.size(); i++) {
		B.insert(pair<int, int>(R[i], i));
	}
	
	rv = 0;
	
	//for every building x in B, calculate the maximum area of a sign that would cover x with the height of the building as the height of the sign
	//the max of the areas for every building in B will be the max area possible of the sign
	for(BIT = B.begin(); BIT != B.end(); BIT++) {
		if(BIT->second == 0 || BIT->second == R.size() - 1) { //put the two sentinels into the set without calculating as they are not buildings
			X.insert(BIT->second);
		}
		else { //for every building x, every building in R that is between the lower and upper bound of x in X will be atleast as tall as this building
				//thus the maximum area of a sign that will include this building is the number of buildings in B between these upper and lower bounds * the height of the building
			XIT = X.lower_bound(BIT->second);
			r = *XIT;
			XIT--;
			l = *XIT;
			length = r - l - 1;
			height = BIT->first;
			nv = length * height;
			//cout << length << " * " <<  height  << " = " << nv <<  endl;
			X.insert(BIT->second); //put the processed building into the set of processed buildings
			if(nv > rv) rv = nv; //if a new maximum height is found, replace the return value with this height
		}
	}

	return rv;
}

