#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class IncrementAndDoubling {
	public:
		int getMin(vector<int> desiredArray);
};

int IncrementAndDoubling::getMin(vector<int> desiredArray) {
	int m = 0; //index of the largest value in desiredArray
	int rv = 0;

	//find the largest value in desiredArray
	for(int i = 0; i < desiredArray.size(); i++) {
		if(desiredArray[i] > desiredArray[m]) m = i;
	}
	
	//perform, when needed, decrement then halving operations on elements in the desiredArray until the largest element, and thus all other elements, is 0.
	while(desiredArray[m] > 0) {
		//if there are any odd numbers in desiredArray, subtract one from each of them, each time this happens, count the subtraction as 1 increment
		for(int i = 0; i < desiredArray.size(); i++) {
			if(desiredArray[i] & 1) {
				desiredArray[i] &= (~(1));
				rv++;
			}
		}
		//now that all numbers in desiredArray are even or 0, if there is a number greater or equal to 2, this means that we can divide every element in the array by 2
		//in order to reach a version of desiredArray that would be doubled in order to get to the final desiredArray, count the halving of every element in the array as
		//one doubling operation
		if(desiredArray[m] >= 2) {
			for(int i = 0; i < desiredArray.size(); i++) {
				desiredArray[i] = desiredArray[i] >> 1;
			}	
			rv++;
		}
	}
	return rv; //return the number of operations performed
}



int main() {
	IncrementAndDoubling X = IncrementAndDoubling();
	
	//test cases from the topcoder website
	vector<int> test1;
	test1.push_back(2);
	test1.push_back(1);

	vector<int> test2;
	test2.push_back(16);
	test2.push_back(16);
	test2.push_back(16);
	
	vector<int> test3;
	test3.push_back(100);

	vector<int> test4;
	test4.push_back(0);
	test4.push_back(0);
	test4.push_back(1);
	test4.push_back(0);
	test4.push_back(1);

	vector<int> test5;
	test5.push_back(123);
	test5.push_back(234);
	test5.push_back(345);
	test5.push_back(456);
	test5.push_back(567);
	test5.push_back(789);

	vector<int> test6;
	test6.push_back(7);
	test6.push_back(5);
	test6.push_back(8);
	test6.push_back(1);
	test6.push_back(8);
	test6.push_back(6);
	test6.push_back(6);
	test6.push_back(5);
	test6.push_back(3);
	test6.push_back(5);
	test6.push_back(5);
	test6.push_back(2);
	test6.push_back(8);
	test6.push_back(9);
	test6.push_back(9);
	test6.push_back(4);
	test6.push_back(6);
	test6.push_back(9);
	test6.push_back(4);
	test6.push_back(4);
	test6.push_back(1);
	test6.push_back(9);
	test6.push_back(9);
	test6.push_back(2);
	test6.push_back(8);
	test6.push_back(4);
	test6.push_back(7);
	test6.push_back(4);
	test6.push_back(8);
	test6.push_back(8);
	test6.push_back(6);
	test6.push_back(3);
	test6.push_back(9);
	test6.push_back(4);
	test6.push_back(3);
	test6.push_back(4);
	test6.push_back(5);
	test6.push_back(1);
	test6.push_back(9);
	test6.push_back(8);
	test6.push_back(3);
	test6.push_back(8);
	test6.push_back(3);
	test6.push_back(7);
	test6.push_back(9);
	test6.push_back(3);
	test6.push_back(8);
	test6.push_back(4);
	test6.push_back(4);
	test6.push_back(7);

	cout << X.getMin(test1) << endl;
	cout << X.getMin(test2) << endl;
	cout << X.getMin(test3) << endl;
	cout << X.getMin(test4) << endl;
	cout << X.getMin(test5) << endl;
	cout << X.getMin(test6) << endl;
	return 0;
}

