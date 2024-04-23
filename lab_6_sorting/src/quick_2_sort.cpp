#include <iostream>
#include <vector>
#include <cstdio>
#include "sorting.hpp"
using namespace std;
void recursive_sort(vector <double> &v, int start, int size, int print)
{
	int i = start + 1;
	int j = start + size - 1;
	double temp;
	if(print == 1) {
			printf("S:%6d%6d      ", start, size);
			for(int x = 0; x < v.size(); x++) {
				if(x == v.size() - 1) printf("%6.2f\n", v[x]);
				else printf("%6.2f", v[x]);
			}
	}
	if(size <= 1) {
		return;
	}
	if(size == 2) {
		if(v[start] > v[start + 1]) {
			temp = v[start];
			v[start] = v[start+1];
			v[start+1] = temp;
			
		}
		return;
	}

	while(i < j) {
		while(i < start + size && v[i] < v[start]) i++;
		while(j > start && v[j] > v[start]) j--;
		if(i < j) { //in this case the two indexes havent passed each other which means that we mustve found two elements from each side to swap
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;

			i++;
			j--;
		}
	}
	
	if(i == start + size) {
		temp = v[start];
		v[start] = v[start + size - 1];
		v[start + size - 1] = temp;
		if(print == 1) {
			printf("P:%6d%6d%6d", start, size, i - 1);
			for(int x = 0; x < v.size(); x++) {
				if(x == v.size() - 1) printf("%6.2f\n", v[x]);
				else printf("%6.2f", v[x]);
			}
		}
		recursive_sort(v, start, size - 1, print);
		recursive_sort(v, start + size, 0, print);
	}
	else if(j == start) {
		if(print == 1) {
			printf("P:%6d%6d%6d", start, size, start);
			for(int x = 0; x < v.size(); x++) {
				if(x == v.size() - 1) printf("%6.2f\n", v[x]);
				else printf("%6.2f", v[x]);
			}
		}
		recursive_sort(v, start, 0, print);
		recursive_sort(v, start + 1, size - 1, print);
	}

	else if(i == j) {
    	if(v[start] >= v[i]) {
        	temp = v[i];
        	v[i] = v[start];
            v[start] = temp;
			recursive_sort(v, start, i - start, print);
			recursive_sort(v, i+1, start + size - 1 - (i), print);
		}
		else {
        	temp = v[i - 1];
        	v[i - 1] = v[start];
            v[start] = temp;
			recursive_sort(v, start, i - 1 - start, print);
			recursive_sort(v, i, start + size - 1 - (i - 1), print);
		}
		if(print == 1) {
        	printf("P:%6d%6d%6d", start, size, i);
            for(int x = 0; x < v.size(); x++) {
            	if(x == v.size() - 1) printf("%6.2f\n", v[x]);
                else printf("%6.2f", v[x]);
            }
        }	
   	}
	else {
		i = i - 1;
		j = j + 1;
		temp = v[start];
		v[start] = v[i];
		v[i] = temp;

		if(print == 1) {
			printf("P:%6d%6d%6d", start, size, i);
			for(int x = 0; x < v.size(); x++) {
				if(x == v.size() - 1) printf("%6.2f\n", v[x]);
				else printf("%6.2f", v[x]);
			}
		}
		recursive_sort(v, start, i - start, print);
		recursive_sort(v, i+1, start + size - 1 - (i), print);
	}
}
void sort_doubles(vector <double> &v, bool print) {
	int recursive_print;
    if(print) recursive_print = 1;
    else recursive_print = 0;
    recursive_sort(v, 0, v.size(), recursive_print);
	printf("                    ");
  	for(int x = 0; x < v.size(); x++) {
    	printf("%6.2f", v[x]);
    }
	printf("\n");
  }

