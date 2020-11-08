#include <vector>
#include <set>
#include <map>
#include <iostream>
using namespace std;

class Ball {
	public:
    	int val;
    	int matched;
    	Ball *low;
    	Ball *high;
};

class OneDimensionalBalls {
  public:
    long long countValidGuesses(vector <int> firstPicture, vector <int> secondPicture);
    long long cvg(int v);
  	map <int, Ball *> FBMAP;
  	map <int, Ball *>::iterator FBMIT;
  	map <int, Ball *> SBMAP;
  	map <int, Ball *>::iterator SBMIT;
};


long long OneDimensionalBalls::cvg(int v)
{
	long long rv;
	int i;
	Ball *matchedBall;
	bool remainingSingleMatch = false;
  	rv = 0;
  	for (i = -1; i <= 1; i += 2) {		
  		for(FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
			SBMIT = SBMAP.find(FBMIT->first + v*i);
			if(SBMIT != SBMAP.end()) {
				if( i == -1) {
					FBMIT->second->low = SBMIT->second;
					SBMIT->second->high = FBMIT->second;
				}
				else {
					FBMIT->second->high = SBMIT->second;
					SBMIT->second->low = FBMIT->second;
				}
			}
		}	
	}
	cout << "velocity: " << v << endl;
	for (FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
		cout << FBMIT->first << endl;
		if(FBMIT->second->low != NULL) {
			cout << FBMIT->second->low->val << endl; 
		}
		if(FBMIT->second->high != NULL) {
			cout << FBMIT->second->high->val << endl; 
		}
		cout << endl;
	}

	for(FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
		if(FBMIT->second->low == NULL && FBMIT->second->high == NULL) {
			return 0;
		}
	}
	do {
		remainingSingleMatch = false;
		for(FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
			if(FBMIT->second->low != NULL && FBMIT->second->high == NULL) {
				matchedBall = FBMIT->second->low;
				FBMIT->second->matched = 1;
				FBMIT->second->low = NULL;
				matchedBall->matched = 1;
				matchedBall->high = NULL;
				if(matchedBall->low != NULL) {
					remainingSingleMatch = true;
					matchedBall->low->high = NULL;
					matchedBall->low = NULL;
				}
			}
			if(FBMIT->second->low == NULL && FBMIT->second->high != NULL) {
				matchedBall = FBMIT->second->high;
				FBMIT->second->matched = 1;
				FBMIT->second->high = NULL;
				matchedBall->matched = 1;
				matchedBall->low = NULL;
				if(matchedBall->high != NULL) {
					matchedBall->high->low = NULL;
					matchedBall->high = NULL;
				}
			}
		}
	}
	while (remainingSingleMatch == true);
	


	cout << "velocity: " << v << endl;
	for (FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
		cout << FBMIT->first << endl;
		if(FBMIT->second->low != NULL) {
			cout << FBMIT->second->low->val << endl; 
		}
		if(FBMIT->second->high != NULL) {
			cout << FBMIT->second->high->val << endl; 
		}
		cout << endl;
	}
	for (FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
		FBMIT->second->low = NULL;
		FBMIT->second->high = NULL;
		FBMIT->second->matched = 0;
	}
	for (SBMIT = SBMAP.begin(); SBMIT != SBMAP.end(); SBMIT++) {
		SBMIT->second->low = NULL;
		SBMIT->second->high = NULL;
		SBMIT->second->matched = 0;
	}

  	return rv;
}

long long OneDimensionalBalls::countValidGuesses(vector <int> firstPicture, vector <int> secondPicture)
{
	int i, d;
	set <int> velocities;
	set <int>::iterator vit;
	long long rv;
	
	for(i = 0; i < firstPicture.size(); i++) {
		FBMIT = FBMAP.insert(pair<int, Ball *>(firstPicture[i], new Ball())).first;		
		FBMIT->second->val = firstPicture[i];
		FBMIT->second->low = NULL;
		FBMIT->second->high = NULL;
		FBMIT->second->matched = 0;
	}
	for(i = 0; i < secondPicture.size(); i++) {
		SBMIT = SBMAP.insert(pair<int, Ball *>(secondPicture[i], new Ball())).first;		
		SBMIT->second->val = secondPicture[i];
		SBMIT->second->low = NULL;
		SBMIT->second->high = NULL;
		SBMIT->second->matched = 0;
	}

  	for (i = 0; i < secondPicture.size(); i++) {
    	d = secondPicture[i] - firstPicture[0];
    	if (d < 0) d = -d;
    	if (d != 0) velocities.insert(d);
  	}


  	rv = 0;
  	for (vit = velocities.begin(); vit != velocities.end(); vit++) {
		rv += cvg(*vit);
  	}
  	return rv;
}
