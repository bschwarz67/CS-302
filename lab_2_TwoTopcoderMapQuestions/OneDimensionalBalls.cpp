#include <vector>
#include <set>
#include <map>
#include <iostream>
using namespace std;

//Ball object represents a ball at a coordinate in either picture. val represents the coordinate. low, high are pointers to balls that connect
//balls that could possibly by the same ball.
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
  	map <int, Ball *> FBMAP; //holds Ball objects that represent balls from firstPicture
  	map <int, Ball *>::iterator FBMIT;
  	map <int, Ball *> SBMAP; //holds Ball objects that represent balls from secondPicture
  	map <int, Ball *>::iterator SBMIT;
};


long long OneDimensionalBalls::cvg(int v)
{
	long long rv;
	int i;
	Ball *matchedBall;
	bool remainingUnmatched = false;
  	rv = 0;

	//for a velocity v, connect every pair of balls between the first map and the second map that could be the same ball if the balls in the first map moved at velocity v in either direction
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

	//if there is a ball in the first map that could not be any ball in the second map, return 0, there are no possible guesses.
	for(FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
		if(FBMIT->second->low == NULL && FBMIT->second->high == NULL) {
			return 0;
		}
	}

	//while there are balls in the first map that are only connected to one ball in the second map, loop over the first map and remove the connections between these balls
	//mark these balls as matched.
	do {
		remainingUnmatched = false;
		for(FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
			if(FBMIT->second->low != NULL && FBMIT->second->high == NULL) {
				matchedBall = FBMIT->second->low;
				FBMIT->second->matched = 1;
				FBMIT->second->low = NULL;
				matchedBall->matched = 1;
				matchedBall->high = NULL;
				if(matchedBall->low != NULL) {
					remainingUnmatched = true;
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
					if(matchedBall->high->high == NULL) {
						matchedBall->high->matched = 1;
					}
					matchedBall->high = NULL;
				}
			}
		}
	}
	while (remainingUnmatched == true);
	
	//check to see if every ball in the first map has been matched.
	remainingUnmatched = false;
	for(FBMIT = FBMAP.begin(); FBMIT != FBMAP.end(); FBMIT++) {
		if (FBMIT->second->matched == 0) {
			remainingUnmatched = true;
		}
	}
	//if every ball in the first map has been matched, reset both first, second map to their state before the cvg  was called, return 1 as there is only one valid guess
	if(remainingUnmatched == false) {
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
		return 1;
	}

	
	//if there are still unmatched balls, some balls in first map could be two different balls in second map.
	
	//find every chain of balls in first map where every ball in the chain could be two balls in second map, 
	//and shares atleast one ball in the second map with another ball in the chain. add one to the number of balls in an individual chain.
	//multiply together these individual values found from all of the chains to get the number of valid guesses for a velocity.
	rv = 1;
	FBMIT = FBMAP.begin();
	while(FBMIT != FBMAP.end()) {
		i = 0;
		while(FBMIT != FBMAP.end() && FBMIT->second->low == NULL && FBMIT->second->high == NULL) {
			FBMIT++;
		}
		if(FBMIT != FBMAP.end() && FBMIT->second->low != NULL && FBMIT->second->high != NULL) {
			while(FBMIT != FBMAP.end() && FBMIT->second->low != NULL && FBMIT->second->high != NULL) {
				i++;
				FBMIT++;
			}
			i++;
			rv *= i;
		}
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

	//put the ball coordinates from firstPicture, secondpicture into maps, with the key being the coordinate of the ball.
	//intitialize the balls in the maps to be unconnected to ather balls, have their unmatched value be 0.
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

	//find a set of velocities that will contain all of the velocities that will compute all valid guesses
  	for (i = 0; i < secondPicture.size(); i++) {
    	d = secondPicture[i] - firstPicture[0];
    	if (d < 0) d = -d;
    	if (d != 0) velocities.insert(d);
  	}

	//call our algorithm to calculate the number of valid guesses for each possible velocity, sum up the valid guesses for each velocity.
  	rv = 0;
  	for (vit = velocities.begin(); vit != velocities.end(); vit++) {
		rv += cvg(*vit);
  	}
  	return rv;
}
