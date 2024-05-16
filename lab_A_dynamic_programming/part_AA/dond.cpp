#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <math.h>
#include <vector>
#include <sstream>
using namespace std;


class Dond {
	public:
		double dond(int count, int prev);
		int s;
		int t;
		int last_roll;
		map<string, double> cache;
};



double Dond::dond(int count, int prev) {
	double ret = 0;
	double val;
	string key;
	stringstream ss;
	if(count == 1 && prev == -1) return 1;
	else if(count == 1) {
		for(int i = 0; i < s; i++) {
			if(i < prev - 1 || i > prev + 1) ret += 1;
		}
		return ret / s;
	}
	else {
		if(prev == -1) {
			for(int i = 0; i < s; i++) {
				ss << (count - 1);
				ss << i;
				key = ss.str();
				if(cache.find(key) != cache.end()) ret += cache[key];
				else {
					val = dond(count - 1, i);
					ret += val;
					cache.insert(pair<string,double>(key,val));
				}
				ss.clear();
				ss.str("");
					
			}
			return ret / s;
		}
		else {
			for(int i = 0; i < s; i++) {
				if(i < prev - 1 || i > prev + 1) {
					ss << (count - 1);
					ss << i;
					key = ss.str();
					if(cache.find(key) != cache.end()) ret += cache[key];
					else {
						val = dond(count - 1, i);
						ret += val;
						cache.insert(pair<string,double>(key,val));
					}
					ss.clear();
					ss.str("");
				}
			}
			return ret / s;

		}
	}

	
	
	
}


int main(int argc, char **argv) {

	stringstream ss;

	if (argc > 4) {
    	cerr << "dond s t last-roll\n";
		exit(1);
  	}
	Dond d;	
	
	ss << argv[1];
	ss >> d.s;

  	if(ss.fail()) {
		cerr << "dond s t last-roll\n";
		exit(1);
	}
	ss.clear();
	ss.str("");

	ss << argv[2];
	ss >> d.t;

	if(ss.fail()) {
		cerr << "dond s t last-roll\n";
		exit(1);
	}

	ss.clear();
	ss.str("");

	ss << argv[3];
	ss >> d.last_roll;

	if(ss.fail()) {
		cerr << "dond s t last-roll\n";
		exit(1);
	}

	if(d.s == 1) {
		cout << 0.0 << endl; 
		return 0;
	}
	if(d.s == 2) {
		cout << 0.0 << endl; 
		return 0;
	} 
	cout << d.dond(d.t, d.last_roll) << endl;


	return 0;
}
