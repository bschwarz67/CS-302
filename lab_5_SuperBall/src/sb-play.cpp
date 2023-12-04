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
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
    Disjoint_Set d;
    void play_superball();
    void analyze_superball_rec(int set, int color, int coord);
    void swap(int i, int j);
    int number_of_empty_cells();
    int can_score();
};

int Superball::number_of_empty_cells() {
  int empty = 0;
  for(int i = 0; i < r*c; i++) {
      
      if(board[i] == '.') empty++;
      if(board[i] == '*') empty++;
      
    }
    return empty;
}

int Superball::can_score() {
  for(int i = 0; i < goals.size(); i++) {
    if(goals[i] == 1 && d.Get_Sizes()->at(d.Find(i)) >= 5) return 1;
  }
  return 0;
}

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


void Superball::play_superball(){
  long double best_swap_score = 0;
  long double swap_score;
  int c1 = 0;
  int c2 = 0;

  //analyse the board that is piped into the program
  for(int i = 0; i < board.size(); i++) {
    if(board[i] != '.' && board[i] != '*') analyze_superball_rec(i, board[i], i);
  }

  //check for fewer than 5 places and unable to score
  if(number_of_empty_cells() < 5 && can_score() == 0) {
    int i = 0;
    int j = 0;
    int a = 0;
    while(board[a] == '*' || board[a] == '.') a++;
    i = a;
    a++;
    while(board[a] == '*' || board[a] == '.') a++;
    j = a;
    
    printf("SWAP %d %d %d %d\n", i/c, i%c, j/c, j%c);

  }

  else if(number_of_empty_cells() < 5 && can_score() == 1) {
    int biggest_score = 0;
    int score = 0;
    int scored_cell = 0;
    for(int i = 0; i < goals.size(); i++) {
      if(goals[i] == 1 && d.Get_Sizes()->at(d.Find(i)) >= 5) {
        score = d.Get_Sizes()->at(d.Find(i)) * colors[board[i]];
        if(score > biggest_score) {
          biggest_score = score;
          scored_cell = i;
        }
      }
    }
    printf("SCORE %d %d\n", scored_cell/c, scored_cell%c);
    d.Print();
  }

  
  else {
    for(int i = 0; i < goals.size(); i++) {
      for(int j = i + 1; j < goals.size(); j++) {
        if(board[i] != '.' && board[i] != '*' && board[j] != '.' && board[j] != '*') {
          d.Initialize(r*c);
          swap(i,j);
          swap_score = 0;
          for(int k = 0; k < goals.size(); k++) {
            if(goals[k] == 1 && board[k] != '*' && d.Get_Sizes()->at(d.Find(k)) == 1) {
              analyze_superball_rec(k, board[k], k);
              swap_score += colors[board[k]] * d.Get_Sizes()->at(d.Find(k)) * 2;
            }
            if(goals[k] == 0 && board[k] != '.' && d.Get_Sizes()->at(d.Find(k)) == 1) {
              analyze_superball_rec(k, board[k], k);
              swap_score += colors[board[k]] * d.Get_Sizes()->at(d.Find(k)) * 1;
            }
          }
          swap_score /= d.Get_Set_Ids()->size();
          //swap_score -= d.Get_Set_Ids()->size();
          if(swap_score > best_swap_score) {
            best_swap_score = swap_score;
            c1 = i;
            c2 = j;
          }
          swap(i,j);
        }
      }
    }
    printf("SWAP %d %d %d %d\n", c1/c, c1%c, c2/c, c2%c);
  }    
}

void Superball::swap(int i, int j) {
  int temp = board[i];
      board[i] = board[j];
      board[j] = temp;
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

  
  s->play_superball();

  exit(0);
}