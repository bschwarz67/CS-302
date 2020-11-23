//TODO change around that location of path maybe?, constructor?
#include <map>
#include <iostream>
#include <vector>
using namespace std;

//object that represents cells in the Maze, id from 0 to r*c -1
class Cell {
	public:
		int id;
		int visited;
		map <int, Cell *> adjacentCells; 
};

class Maze {
	public:
		map <int, Cell *> cells; //hold all the cells with the cell id as the key
		multimap <int, int> walls; //holds all the coordinates of the walls
		vector<int> path;
		int rows;
		int cols;
		bool mazeSolve(Cell * current);
		Maze();
};

Maze::Maze() {
	string s;
	int i, j;
	Cell * c;
	multimap <int, int>::iterator wit;	
	map <int, Cell *>::iterator cit;
	map <int, Cell *>::iterator cit2;
	//read in and output the number of rows and columns in the maze in the format specified
	cin >> s >> rows >> s >> cols; 
	cout << "ROWS " << rows << " COLS " << cols << endl;	
	
	//insert the coordinates of the walls in the specifications file into a multimap
	while(cin >> s >> i >> j) {
		walls.insert(pair<int,int>(i, j));
	}
	
	//print the coordinates of all the walls in the format specified
	for(wit = walls.begin(); wit != walls.end(); wit++) {
		cout << "WALL " << wit->first << " " << wit->second << endl;
	}
	

	//populate the cells data structure of the maze with r*c cells numbered 0 to r*c - 1, set visited to false for each cell
	for(i = 0; i < rows * cols; i++) {
		c = new Cell();
		c->id = i;
		c->visited = 0;
		cells.insert(pair<int, Cell *>(i, c));
	}

	//for every cell in the maze, put into the cells adjacentCells map every cell that should be adjacent to it
	//as specified by the dimensions of the file
	for(cit = cells.begin(); cit != cells.end(); cit++) {
		cit2 = cells.find(cit->first - cols);
		if(cit2 != cells.end()) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
		cit2 = cells.find(cit->first + cols);
		if(cit2 != cells.end()) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
		cit2 = cells.find(cit->first - 1);
		if(cit->first % cols != 0) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
		cit2 = cells.find(cit->first + 1);
		if(cit->first % cols != cols - 1) {
			cit->second->adjacentCells.insert(pair<int, Cell*>(cit2->first, cit2->second));
		}
	}
	
	//delete the links in the maze between cells that have walls between them as described by the wall coordinates we put into the multimap
	for(wit = walls.begin(); wit != walls.end(); wit++) {
		cit = cells.find(wit->first);
		cit->second->adjacentCells.find(wit->second)->second->adjacentCells.erase(wit->first);
		cit->second->adjacentCells.erase(wit->second);
	}



	/*
	for(cit = cells.begin(); cit != cells.end(); cit++) {
		cout << cit->first << endl << endl;
		for(cit2 = cit->second->adjacentCells.begin(); cit2 != cit->second->adjacentCells.end(); cit2++) {
			cout << cit2->first << endl;
		}
		cout << endl << endl;
	}
	*/

}

bool Maze::mazeSolve(Cell * current) {
	map <int, Cell *>::iterator cit;
	
	if(current->id == 0) {
		current->visited = 1;
		path.push_back(0);
	}

	//if we have reached the end of the maze, output the path taken to get here and return true
	if(current->id == (rows * cols) - 1) {
		for(int i = 0; i < path.size(); i++) {
			cout << "PATH " << path[i] << endl;
		}
		return true;
	}

	//for every cell adjacent to the current cell that hasnt been visited yet, try to go through this cell to get to the end of the maze
	for(cit = current->adjacentCells.begin(); cit != current->adjacentCells.end(); cit++) {
		if(cit->second->visited == 0) {
			cit->second->visited = 1;
			path.push_back(cit->second->id);
			
			//if the solving function returns that we reached the end, return true;
			if (mazeSolve(cit->second)) {
				return true;
			}
			
			//if the function did not reach to end of the maze, pretend we havent used this node, take this node out of the path list
			//and keep looping through the adjacent nodes
			else {
				cit->second->visited = 0;
				path.pop_back();
			}
		}	
	}
	//if none of the adjacent cells got us to the end of the maze, go back and try an adjacent cell from the cell we were moving from, or if its the first cell,
	//the maze has no solution
	return false;
}


int main() {
	Maze m = Maze();

	//call the function to test if there is a maze to solve
	if(m.cells.size() > 0) {
		m.cells.find(0)->second->visited = 1;
		bool x = m.mazeSolve(m.cells.find(0)->second);

	}

	return 0;
}
