#include <iostream>
#include <vector>
#include <cstdio>
#include "sorting.hpp"
using namespace std;


void recursive_sort(vector <double> &v, vector <double> &temp, int start, int size, int print) {
    double temp_double;
    int i , j, k;


    
    if(size <= 1) return;

    if(print == 1) {
			printf("B:%6d%6d      ", start, size);
			for(int x = 0; x < v.size(); x++) {
				if(x == v.size() - 1) printf("%6.2f\n", v[x]);
				else printf("%6.2f", v[x]);
			}
	}


    
    if(size == 2) {
        if(v[start] >= v[start+1]) {
            temp_double = v[start];
            v[start] = v[start+1];
            v[start+1] = temp_double;
        }
        if(print == 1) {
			printf("E:%6d%6d      ", start, size);
			for(int x = 0; x < v.size(); x++) {
				if(x == v.size() - 1) printf("%6.2f\n", v[x]);
				else printf("%6.2f", v[x]);
			}
	}
        return;
    }

    recursive_sort(v, temp, start, size/2, print);
    recursive_sort(v, temp, start + size/2, size - size/2, print);

    i = start;

    j = start;
    k = start + size/2;

    while(j < start + size/2 || k < start + size) {
        if(j < start + size/2 && k < start + size) {
            if(v[j] <= v[k]) {
                temp[i] = v[j];
                i += 1;
                j += 1;
            }
            else {
                temp[i] = v[k];
                i += 1;
                k += 1;
            }
        }
        else if(j < start + size/2) {
            temp[i] = v[j];
            i += 1;
            j += 1;
        }
        else {
            temp[i] = v[k];
            i += 1;
            k += 1;
        }
    }

    for(i = start; i < start + size; i++) {
        v[i] = temp[i];
    }

    if(print == 1) {
			printf("E:%6d%6d      ", start, size);
			for(int x = 0; x < v.size(); x++) {
				if(x == v.size() - 1) printf("%6.2f\n", v[x]);
				else printf("%6.2f", v[x]);
			}
	}

    return;

}

void sort_doubles(vector <double> &v, bool print)
{
    vector <double> temp;
    temp.resize(v.size());
    if(print) {
        recursive_sort(v, temp, 0, v.size(), 1);
    }
    else {
        recursive_sort(v, temp, 0, v.size(), 0);
    }
    printf("                    ");
  	for(int x = 0; x < v.size(); x++) {
    	printf("%6.2f", v[x]);
    }
	printf("\n");
}