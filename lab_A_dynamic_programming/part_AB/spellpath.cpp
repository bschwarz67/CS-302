#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;


int MaxPathLen(int r, int c, vector<vector<char>> &g) {
    int max = 1;
    int max_2 = 0;
    char temp;

    //cout << r << " " << c << endl;
    if(r > 0 && g[r-1][c] != '-' && abs(g[r-1][c] - g[r][c]) == 1) {
        temp = g[r][c];
        g[r][c] = '-';
        max = MaxPathLen(r-1,c,g) + 1;
        g[r][c] = temp;
        if(max_2 > max) max = max_2;
    }
    if(r < g.size() - 1 && g[r+1][c] != '-' && abs(g[r+1][c] - g[r][c]) == 1) {
        temp = g[r][c];
        g[r][c] = '-';
        max_2 = MaxPathLen(r+1,c,g) + 1;
        g[r][c] = temp;
        if(max_2 > max) max = max_2;
    }
    if(c > 0 && g[r][c-1] != '-' && abs(g[r][c-1] - g[r][c]) == 1) {
        temp = g[r][c];
        g[r][c] = '-';
        max_2 = MaxPathLen(r,c-1,g) + 1;
        g[r][c] = temp;
        if(max_2 > max) max = max_2;
    }
    if(c < g[r].size() - 1 && g[r][c+1] != '-' && abs(g[r][c+1] - g[r][c]) == 1) {
        temp = g[r][c];
        g[r][c] = '-';
        max_2 = MaxPathLen(r,c+1,g) + 1;
        g[r][c] = temp;
        if(max_2 > max) max = max_2;
    }

    if(c%2 == 0) {
        if(r < g.size() - 1 && c < g[r].size() - 1 && g[r+1][c+1] != '-' && abs(g[r+1][c+1] - g[r][c]) == 1) {
            temp = g[r][c];
            g[r][c] = '-';
            max_2 = MaxPathLen(r+1,c+1,g) + 1;
            g[r][c] = temp;
            if(max_2 > max) max = max_2;
        }
        if(r < g.size() - 1 && c > 0 && g[r+1][c-1] != '-' && abs(g[r+1][c-1] - g[r][c]) == 1) {
            temp = g[r][c];
            g[r][c] = '-';
            max_2 = MaxPathLen(r+1,c-1,g) + 1;
            g[r][c] = temp;
            if(max_2 > max) max = max_2;
        }
    }

    else {
        if(r > 0 && c < g[r].size() - 1 && g[r-1][c+1] != '-' && abs(g[r-1][c+1] - g[r][c]) == 1) {
            temp = g[r][c];
            g[r][c] = '-';
            max_2 = MaxPathLen(r-1,c+1,g) + 1;
            g[r][c] = temp;
            if(max_2 > max) max = max_2;
        }

        if(r > 0 && c > 0 && g[r-1][c-1] != '-' && abs(g[r-1][c-1] - g[r][c]) == 1) {
            temp = g[r][c];
            g[r][c] = '-';
            max_2 = MaxPathLen(r-1,c-1,g) + 1;
            g[r][c] = temp;
            if(max_2 > max) max = max_2;
        }

    }

    return max;
}


int main() {
    vector<vector<char>> g;
    string l;
    int max = 0;
    int max_2;

    while (getline(cin, l)) {
        vector<char> row;
        for(int i = 0; i < l.size(); i++) {
            row.push_back(l[i]);
        }
        g.push_back(row);
        
    }

    for(int i = 0; i < g.size(); i++) {
        for(int j = 0; j < g[i].size(); j++) {
            max_2 = MaxPathLen(i,j,g);
            if(max_2 > max) max = max_2;
        } 

    }
    cout << max << endl;

}