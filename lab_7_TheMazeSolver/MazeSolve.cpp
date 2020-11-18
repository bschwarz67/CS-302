#include <map>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Cell {
	public:
		int id;
		int visited;
		map <int, Cell *> adjacentCells; 
};


class Maze {
	public:
		vector <Cell *> cells;
		multimap <int, int> walls;
		int rows;
		int cols;
		void mazeSolve();
};


int main() {
	string s;
	int i, j;
	Maze m = Maze();
	multimap <int, int>::iterator wit;	
	cin >> s >> m.rows >> s >> m.cols;
	
	while(cin >> s >> i >> j) {
		m.walls.insert(pair<int,int>(i, j));
	}
	for(wit = m.walls.begin(); wit != m.walls.end(); wit++) {
		cout << wit->first << " " << wit->second << endl;
	}




















	return 0;
}
