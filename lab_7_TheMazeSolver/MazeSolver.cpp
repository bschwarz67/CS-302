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
		map <int, Cell *> cells;
		multimap <int, int> walls;
		int rows;
		int cols;
		bool mazeSolve(Cell * current);
};

bool Maze::mazeSolve(Cell * current) {
	cout << " test" << endl;
	map <int, Cell *>:: iterator cit;
	if(current-> id == (rows * cols) - 1) return true;
	for(cit = current->adjacentCells.begin(); cit != current->adjacentCells.end(); cit++) {
		if(cit->second->visited == 0) {
			cit->second->visited = 1;
			if (mazeSolve(cit->second)) {
				cout << cit->second->id << endl;
				return true;
			}
			else {
				cit->second->visited = 0;
			}
		}	
	}
	return false;
}


int main() {
	string s;
	int i, j;
	Maze m = Maze();
	Cell * c;
	multimap <int, int>::iterator wit;	
	map <int, Cell *>::iterator cit;
	map <int, Cell *>::iterator cit2;
	cin >> s >> m.rows >> s >> m.cols;
	
	while(cin >> s >> i >> j) {
		m.walls.insert(pair<int,int>(i, j));
	}
	/*
	for(wit = m.walls.begin(); wit != m.walls.end(); wit++) {
		cout << wit->first << " " << wit->second << endl;
	}
	*/

	for(i = 0; i < m.rows * m.cols; i++) {
		c = new Cell();
		c->id = i;
		c->visited = 0;
		m.cells.insert(pair<int, Cell *>(i, c));
	}

	for(cit = m.cells.begin(); cit != m.cells.end(); cit++) {
		cit2 = m.cells.find(cit->first - m.cols);
		if(cit2 != m.cells.end()) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
		cit2 = m.cells.find(cit->first + m.cols);
		if(cit2 != m.cells.end()) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
		cit2 = m.cells.find(cit->first - 1);
		if(cit->first % m.cols != 0) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
		cit2 = m.cells.find(cit->first + 1);
		if(cit->first % m.cols != m.cols - 1) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
	}
	
	for(wit = m.walls.begin(); wit != m.walls.end(); wit++) {
		cit = m.cells.find(wit->first);
		cit->second->adjacentCells.find(wit->second)->second->adjacentCells.erase(wit->first);
		cit->second->adjacentCells.erase(wit->second);
	}



	/*
	for(cit = m.cells.begin(); cit != m.cells.end(); cit++) {
		cout << cit->first << endl << endl;
		for(cit2 = cit->second->adjacentCells.begin(); cit2 != cit->second->adjacentCells.end(); cit2++) {
			cout << cit2->first << endl;
		}
		cout << endl << endl;
	}
	*/
	bool x = m.mazeSolve(m.cells.find(0)->second);


















	return 0;
}
