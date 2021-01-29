#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

class PowerOfThreeEasy {
    public:
        string ableToGet(int x, int y); //main wrapper function that iteratively calls recursive function
    private:
        int checkAllPoss(int index, int n); //recursive function that genreates subsets of steps and checks to see if 
                                                    //the subset and its inverse correspond to x, y or vice-versa
        vector<int> steps; //holds sequential values for each step where step[k] = k^3
        vector<int> stepsSubset; //bit string that represents a subset and its inverse of steps
        int classX; //global x
        int classY; //global y
};

string PowerOfThreeEasy::ableToGet(int x, int y) {
    int tot = x + y;
    int counter = 0;
    int stepLength, i;

    classX = x;
    classY = y;

    //check to see if the total of x and y is equal to a sequence of steps, non skipped, where step k = k^3 
    //if not, a solution to the problem is impossible so return Impossible

    //in doing this, we generate a vector of the sequence to check for solutions later on
    while(tot > 0) {
        if(counter == 0) stepLength = 1;
        else if(counter == 1) stepLength = 3;
        else {
            stepLength = 3;
            for(i = 0; i < counter - 1; i++) stepLength *= 3;
        }
        tot -= stepLength;
        if(stepLength < 0) {
            steps.clear(); //if a solution is impossible, our sequence to this point is useless, so we delete it
            return "Impossible";
        }
        else steps.push_back(stepLength);
        counter++;
    }

    //a problem where no steps are taken is possible, because no steps being taken is a valid solution
    if(steps.size() == 0) return "Possible";


    //create the bitstring that will represent a subset of steps
    for(i = 0; i < steps.size(); i++) {
        stepsSubset.push_back(0);
    }

    //sequentially generate subsets and their inverses to check for solutions using the recursive function
    for(i = 0; i < steps.size(); i++) {
        if(checkAllPoss(0, i)) {
            steps.clear();
            stepsSubset.clear();
            return "Possible";
        }
    }

    //if no solutions were found, clear out the data structures to be reused by the class, return Impossible
    steps.clear();
    stepsSubset.clear();
    return "Impossible";
}

int PowerOfThreeEasy::checkAllPoss(int index, int n) {
    int i, testX, testY;

    //if the number of positive bits to allot has run out, check so see if the totals of the subset, inverse generated of steps
    //correspond to x, y or y, x
    if(n == 0) {

        testX = classX;
        testY = classY;
        for(i = 0; i < stepsSubset.size(); i++) {
            if(stepsSubset[i] == 1) testX -= steps[i];
            else testY -= steps[i];
        }
        
        /*
        for(i = 0; i < stepsSubset.size(); i++) cout << stepsSubset[i];
        cout << endl;
        cout << testX << endl;
        cout << testY << endl;
        */
        if(testX == 0 && testY == 0) return 1;

        testX = classX;
        testY = classY;
        for(i = 0; i < stepsSubset.size(); i++) {
            if(stepsSubset[i] == 1) testY -= steps[i];
            else testX -= steps[i];

        }
        /*
        for(i = 0; i < stepsSubset.size(); i++) cout << stepsSubset[i];
        cout << endl;
        cout << testX << endl;
        cout << testY << endl;
        */

        if(testX == 0 && testY == 0) return 1;

        return 0;


    }
    //if there are more positive bits left than indexes, quit making recursive calls and go back
    else if (n > steps.size() - index) {
        return 0;
    }
    //recursively call, check the solution of the function with and without the positive bit set at the current index.
    else {
        stepsSubset[index] = 1;
        if (checkAllPoss(index + 1, n - 1)) return 1;
        stepsSubset[index] = 0;
        if(checkAllPoss(index + 1, n)) return 1;
    }
    return 0;
}


int main() {

    //test cases given by topcoder
    PowerOfThreeEasy p;
    cout << p.ableToGet(4, 9) << endl;
    cout << p.ableToGet(1, 3) << endl;
    cout << p.ableToGet(1, 1) << endl;
    cout << p.ableToGet(3, 0) << endl;
    cout << p.ableToGet(1, 9) << endl;
    cout << p.ableToGet(3, 10) << endl;
    cout << p.ableToGet(1093, 2187) << endl;
    cout << p.ableToGet(0, 0) << endl;
    return 0;
}
