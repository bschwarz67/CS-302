#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Answer {
  public:
    int length;
    int r;
    int c;
    string key;
    Answer *nexta;
};


class SpellSeeker {
  public:
    vector <string> grid;
    map <string, Answer *> cache;
    int total_r;
    int total_c;
    void DFS(int r, int c, string &key);
    Answer *Solve(int r, int c);
};

//to prove memoization is working you could check every time it is used, print the key and the graph to make sure it matches
//up, for tomorrow..
void SpellSeeker::DFS(int r, int c, string &key) {
    char temp;

    if(r > 0 && grid[r-1][c] != '-' && abs(grid[r-1][c] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        key[(r-1)*total_c + c] = 'O';
        DFS(r-1,c,key);
        grid[r][c] = temp;
        
    }
    if(r < total_r - 1 && grid[r+1][c] != '-' && abs(grid[r+1][c] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        key[(r+1)*total_c + c] = 'O';
        DFS(r+1,c,key);
        grid[r][c] = temp;
    }
    if(c > 0 && grid[r][c-1] != '-' && abs(grid[r][c-1] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        key[(r)*total_c + (c-1)] = 'O';
        DFS(r,c-1,key);
        grid[r][c] = temp;
    }
    if(c < total_c - 1 && grid[r][c+1] != '-' && abs(grid[r][c+1] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        key[(r)*total_c + (c+1)] = 'O';
        DFS(r,c+1,key);
        grid[r][c] = temp;
    }

    if(c%2 == 0) {
        if(r < total_r - 1 && c < total_c - 1 && grid[r+1][c+1] != '-' && abs(grid[r+1][c+1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            key[(r+1)*total_c + (c+1)] = 'O';
            DFS(r+1,c+1,key);
            grid[r][c] = temp;
        }
        if(r < total_r - 1 && c > 0 && grid[r+1][c-1] != '-' && abs(grid[r+1][c-1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            key[(r+1)*total_c + (c-1)] = 'O';
            DFS(r+1,c-1,key);
            grid[r][c] = temp;
        }
    }

    else {
        if(r > 0 && c < total_c - 1 && grid[r-1][c+1] != '-' && abs(grid[r-1][c+1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            key[(r-1)*total_c + (c+1)] = 'O';
            DFS(r-1,c+1,key);
            grid[r][c] = temp;
        }

        if(r > 0 && c > 0 && grid[r-1][c-1] != '-' && abs(grid[r-1][c-1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            key[(r-1)*total_c + (c-1)] = 'O';
            DFS(r-1,c-1,key);
            grid[r][c] = temp;
        }
    }
}


Answer* SpellSeeker::Solve(int r, int c) {

   
    char temp;
    string key(total_r*total_c, '-');
    key[(r)*total_c + c] = 'X';
    DFS(r,c,key);

    if(cache.find(key) != cache.end()) {

        /*
        for(int i = 0; i < key.size(); i++) {
            cout << key[i];
            if(i % (total_c) == total_c - 1) cout << endl;
        }


        cout << endl;


        for(int i = 0; i < total_r; i++) {
            for(int j = 0; j < total_c; j++) {
                cout << grid[i][j];
                if(j == total_c - 1) cout << endl;
            } 
        }
        cout << endl;
        */

        return cache[key]; 
    } 
    Answer *a = new Answer();
    a->r = r;
    a->c = c;
    a->length = 1;
    a->key = key;
    a->nexta = NULL;

    Answer *a_2 = NULL;

    if(r > 0 && grid[r-1][c] != '-' && abs(grid[r-1][c] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        a_2 = Solve(r-1,c);
        grid[r][c] = temp;
        if(a->nexta == NULL || a_2->length > a->nexta->length) {
            a->nexta = a_2;
        }
    }
    if(r < total_r - 1 && grid[r+1][c] != '-' && abs(grid[r+1][c] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        a_2 = Solve(r+1,c);
        grid[r][c] = temp;
        if(a->nexta == NULL || a_2->length > a->nexta->length) {
            a->nexta = a_2;
        }
    }
    if(c > 0 && grid[r][c-1] != '-' && abs(grid[r][c-1] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        a_2 = Solve(r,c-1);
        grid[r][c] = temp;
        if(a->nexta == NULL || a_2->length > a->nexta->length) {
            a->nexta = a_2;
        }
    }
    if(c < total_c - 1 && grid[r][c+1] != '-' && abs(grid[r][c+1] - grid[r][c]) == 1) {
        temp = grid[r][c];
        grid[r][c] = '-';
        a_2 = Solve(r,c+1);
        grid[r][c] = temp;
        if(a->nexta == NULL || a_2->length > a->nexta->length) {
            a->nexta = a_2;
        }
    }

    if(c%2 == 0) {
        if(r < total_r - 1 && c < total_c - 1 && grid[r+1][c+1] != '-' && abs(grid[r+1][c+1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            a_2 = Solve(r+1,c+1);
            grid[r][c] = temp;
            if(a->nexta == NULL || a_2->length > a->nexta->length) {
                a->nexta = a_2;
            }
        }
        if(r < total_r - 1 && c > 0 && grid[r+1][c-1] != '-' && abs(grid[r+1][c-1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            a_2 = Solve(r+1,c-1);
            grid[r][c] = temp;
            if(a->nexta == NULL || a_2->length > a->nexta->length) {
                a->nexta = a_2;
            }
        }
    }

    else {
        if(r > 0 && c < total_c - 1 && grid[r-1][c+1] != '-' && abs(grid[r-1][c+1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            a_2 = Solve(r-1,c+1);
            grid[r][c] = temp;
            if(a->nexta == NULL || a_2->length > a->nexta->length) {
                a->nexta = a_2;
            }
        }

        if(r > 0 && c > 0 && grid[r-1][c-1] != '-' && abs(grid[r-1][c-1] - grid[r][c]) == 1) {
            temp = grid[r][c];
            grid[r][c] = '-';
            a_2 = Solve(r-1,c-1);
            grid[r][c] = temp;
            if(a->nexta == NULL || a_2->length > a->nexta->length) {
                a->nexta = a_2;
            }
        }

    }

    if(a->nexta != NULL) a->length = a->nexta->length + 1;
    cache[key] = a;
    return a;
}


int main() {
    string l;
    SpellSeeker s;
    Answer *a = NULL;
    Answer *a_2;


    while (getline(cin, l)) {
        s.grid.push_back(l);
    }

    s.total_c = s.grid[0].size();
    s.total_r = s.grid.size();
    for(int i = 0; i < s.total_r; i++) {
        for(int j = 0; j < s.total_c; j++) {
            a_2 = s.Solve(i,j);
            if(a == NULL || a_2->length > a->length) a = a_2;
        }

    }

    for(int i = 0; i < s.total_r; i++) {
        for(int j = 0; j < s.total_c; j++) {
            cout << s.grid[i][j];
            if(j == s.total_c - 1) cout << endl;
        } 

    }
    cout << a->length << endl;
    cout << "PATH" << endl;
    while(a != NULL) {
        cout << a->r << " " << a->c << endl;
        a = a->nexta;
    }

    return 1;

}