#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <sstream>
using namespace std;


class Node {
  public: 
    string name;                    // The node's name
    string val;                    
    vector <class Edge *> adj;      // The node's adjacency list in the residual graph.
    int visited;                    // A visited field for depth-first search.
};

class Edge {
  public:
    string name;                    // The edge's name (to store in the edge map).
    Node *n1;                       // The "from" node
    Node *n2;                       // The "to" node
    Edge *reverse;                  // The reverse edge, for processing the residual graph
    int original;                   // The original edge capacity.
    int residual;                   // The edge capacity in the residual graph.
};


class Graph {
  public:
     Graph(string word);
     ~Graph();
     string Verbose;                     /* G = print graph at each step.
                                            P = print augmenting paths at each step.
                                            B = Basic: print graph at beginning and end. */
     //int MaxFlow();                      /* Do the max flow calculation for the graph. */
     //int Find_Augmenting_Path();         /* Find and process an augmenting path. */

     //bool DFS(Node *n);                  /* DFS to find an augmenting path - returns success. */
     vector <Edge *> Path;               /* The augmenting path. */

     int NPaths;                         /* Number of paths for the calculation. */
     int MaxCap;                         /* Maximum edge capacity */

     Node *Source;                       /* Source and sink node. */
     Node *Sink;

     vector <Node *> Nodes;              /* All of the nodes. */
     vector <Edge *> Edges;              /* All of the edges. */
};


Graph::Graph(string word)
{

}

Graph::~Graph()
{
  int i;

  
}

int main(int argc, char **argv)
{
  Graph *G;
  Node *n;
  Node *m;
  Edge *e, *g;
  int f = 0;
  int a[256];
  int i, j;
  string l;
  string c;
  ostringstream ss;
  list<Node*> die; 
  list <Node*>::iterator dieit;
  

  if (argc > 3) {
    cerr << "usage: worddice dice-file word-list\n";
    exit(1);
  }

  fstream fs (argv[1], fstream::in);
  ss.clear();
  ss.str("");

  n = new Node;
  n->name = "0";
  n->val = "SOURCE";
  n->visited = 0;
  die.push_back(n);
  f++;


  
  while (getline(fs, l)) {
    n = new Node;
    ss << f;
    n->name = ss.str();
    ss.clear();
    ss.str("");
    n->val = l;
    n->visited = 0;
    f++;
    die.push_back(n);
  }
  fs.close();

  fstream fs2 (argv[2], fstream::in);

  while (getline(fs2, l)) {
    G = new Graph(l);
    
    for (dieit = die.begin(); dieit != die.end(); dieit++) {
      n = *dieit;
      G->Nodes.push_back(n);
    }

    f = G->Nodes.size();
    
    for(i = 0; i < l.size(); i++) {
      n = new Node;
      ss << f;
      n->name = ss.str();
      ss.clear();
      ss.str("");
      n->val = l[i];
      n->visited = 0;
      G->Nodes.push_back(n);
      f++;
      
       //
      for (dieit = die.begin(); dieit != die.end(); dieit++) {
        for(j = 0; j < 256; j++) a[j] = 0;
        m = *dieit;
        if(m->name != "0" && m->val.find(l[i]) != string::npos && a[l[i]] == 0) {


          e = new Edge();
          e->name = m->name + "->" + n->name;
          e->n1 = m;
          e->n2 = n;
          e->original = 1;
          e->residual = 1;
          m->adj.push_back(e);

          g = new Edge();
          g->name = n->name + "->" + m->name;
          g->n1 = n;
          g->n2 = m;
          g->original = 0;
          g->residual = 0;
          e->reverse = g;

          a[l[i]] = 1;
        }
      }
       //
    }
    

    n = new Node;
    ss << f;
    n->name = ss.str();
    ss.clear();
    ss.str("");
    n->val = "SINK";
    n->visited = 0;
    G->Nodes.push_back(n);



    for(i = 0; i < G->Nodes.size(); i++) {
      cout << G->Nodes[i]->name << " " << G->Nodes[i]->val << endl;
      for(j = 0; j < G->Nodes[i]->adj.size(); j++) cout << G->Nodes[i]->adj[j]->n1->val << " " << G->Nodes[i]->adj[j]->name << " " << G->Nodes[i]->adj[j]->n2->val << " ";
      cout << endl;
    }
    cout << "--" << endl;
    for (i = 0; i < G->Nodes.size(); i++)  G->Nodes[i]->adj.clear();
    for (i = die.size(); i < G->Nodes.size(); i++) delete G->Nodes[i];
    for (i = 0; i < G->Edges.size(); i++) delete G->Edges[i];
    delete G;

  }
  fs2.close();

  


  return 0;
}
