#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <list>
#include "disjoint_set.hpp"
using plank::Disjoint_Set;
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
    Disjoint_Set d;
    void analyze_superball();
    void analyze_superball_rec(int set, int color, int coord);
};



void Superball::analyze_superball_rec(int set, int color, int coord){
  
  
  //top
  if(coord >= c && board[coord - c] == color && d.Find(coord - c) != d.Find(set)) {
    int new_id = d.Union(d.Find(set), d.Find(coord - c));
    analyze_superball_rec(new_id, color, coord - c);
  }

  //bottom
  if(coord + c <= r*c - 1 && board[coord + c] == color && d.Find(coord + c) != d.Find(set)) {
    int new_id = d.Union(d.Find(set), d.Find(coord + c));
    analyze_superball_rec(new_id, color, coord + c);
  }

  //left
  if(coord % c != 0 && board[coord - 1] == color && d.Find(coord - 1) != d.Find(set)) {
    int new_id = d.Union(d.Find(set), d.Find(coord - 1));
    analyze_superball_rec(new_id, color, coord - 1);
  }

  //right
  if(coord % c != c - 1 && board[coord + 1] == color && d.Find(coord + 1) != d.Find(set)) {
    int new_id = d.Union(d.Find(set), d.Find(coord + 1));
    analyze_superball_rec(new_id, color, coord + 1);
  }
  
}


void Superball::analyze_superball(){

  printf("Scoring sets:\n");
  for(int i = 0; i < goals.size(); i++) {
    if(goals[i] == 1 && board[i] != '*' && d.Get_Sizes()->at(d.Find(i)) == 1) {
      analyze_superball_rec(i, board[i], i);
      if(d.Get_Sizes()->at(d.Find(i)) >= 5){
        printf("Size: %3d  Char:%2c  Scoring Cell: %d,%d\n", d.Get_Sizes()->at(d.Find(i)), board[i], i/c, i%c);
      }  
    }
  }
  d.Print();
  d.Initialize(r*c);
  d.Print();
}


void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if (s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
  d.Initialize(r*c);
}

int main(int argc, char **argv)
{
  Superball *s;
  
 
  s = new Superball(argc, argv);

  
  s->analyze_superball();
  

  exit(0);
}








