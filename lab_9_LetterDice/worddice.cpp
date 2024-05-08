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
#include <queue>
using namespace std;


class Node {
  public: 
    string name;                    // The node's name
    string val;                    
    vector <class Edge *> adj;      // The node's adjacency list in the residual graph.
    int visited;                    // A visited field for depth-first search.
    int distance;
    Edge *backedge;
};

class Edge {
  public:
    string name;                    // The edge's name (to store in the edge map).
    Node *n1;                       // The "from" node
    Node *n2;                       // The "to" node
    Edge *reverse;                  // The reverse edge, for processing the residual graph
    int original;                   // The original edge capacity.
    int residual;                   // The edge capacity in the residual graph.
    int flow;
};


class Graph {
  public:
    Graph(list<string> die_string, list <string>::iterator die_string_it, string word);
    ~Graph();
    
    void Can_Spell_Word();                 

    bool Find_Shortest_Path(Node *n);                  /* BFS to find an augmenting path - returns success. */
    vector <Edge *> Path;               /* The augmenting path. */

    int MaxCap;                         /* Maximum edge capacity */
    int Cap;

    Node *Source;                       /* Source and sink node. */
    Node *Sink;

    vector <Node *> Nodes;              /* All of the nodes. */
    vector <Edge *> Edges;              /* All of the edges. */
    list<Node*> Die; 
    list <Node*>::iterator Dieit;
    queue <Node*> spqueue;
    vector <Node *> Answer;
    string Word;

};


Graph::Graph(list<string> die_string, list <string>::iterator die_string_it, string word)
{

  Node *n;
  Node *m;
  Edge *e, *g;
  int f = 0;
  int a[256];
  int i, j;
  stringstream ss;
  MaxCap = 4;
  Word = word;

  //create source
  n = new Node;
  n->name = "-1";
  n->val = "SOURCE";
  n->visited = 0;
  Nodes.push_back(n);
  Source = n;



  //create sink
  n = new Node;
  ss << (die_string.size() + word.size());
  n->name = "-2";
  ss.clear();
  ss.str("");
  n->val = "SINK";
  n->visited = 0;
  Sink = n;


  for (die_string_it = die_string.begin(); die_string_it != die_string.end(); die_string_it++) {
    n = new Node;
    ss << f;
    n->name = ss.str();
    ss.clear();
    ss.str("");
    n->val = *die_string_it;
    n->visited = 0;
    f++;
    Die.push_back(n);
    Nodes.push_back(n);

    e = new Edge();
    e->name = Source->name + "->" + n->name;
    e->n1 = Source;
    e->n2 = n;
    e->original = 1;
    e->residual = 1;
    e->flow = 0;
    

    g = new Edge();
    g->name = n->name + "->" + Source->name;
    g->n1 = n;
    g->n2 = Source;
    g->original = 0;
    g->residual = 0;
    g->flow = 0;

    e->reverse = g;
    g->reverse = e;
    

    Source->adj.push_back(e);
    n->adj.push_back(g);

    Edges.push_back(e);
    Edges.push_back(g);

  }


  
  
  for(i = 0; i < word.size(); i++) {
    n = new Node;
    ss << f;
    n->name = ss.str();
    ss.clear();
    ss.str("");
    n->val = word[i];
    n->visited = 0;
    Nodes.push_back(n);
    f++;
    
    //
    for (Dieit = Die.begin(); Dieit != Die.end(); Dieit++) {
      for(j = 0; j < 256; j++) a[j] = 0;
      m = *Dieit;
      if(m->val.find(word[i]) != string::npos && a[word[i]] == 0) {
        e = new Edge();
        e->name = m->name + "->" + n->name;
        e->n1 = m;
        e->n2 = n;
        e->original = 1;
        e->residual = 1;
        e->flow = 0;

        g = new Edge();
        g->name = n->name + "->" + m->name;
        g->n1 = n;
        g->n2 = m;
        g->original = 0;
        g->residual = 0;
        g->flow = 0;

        e->reverse = g;
        g->reverse = e;

        m->adj.push_back(e);
        n->adj.push_back(g);

        Edges.push_back(e);
        Edges.push_back(g);

        a[word[i]] = 1;
      }
    }
      //
      
    e = new Edge();
    e->name = n->name + "->" + Sink->name;
    e->n1 = n;
    e->n2 = Sink;
    e->original = 1;
    e->residual = 1;
    e->flow = 0;

    g = new Edge();
    g->name = Sink->name + "->" + n->name;
    g->n1 = Sink;
    g->n2 = n;
    g->original = 0;
    g->residual = 0;
    g->flow = 0;

    e->reverse = g;
    g->reverse = e;
    
    n->adj.push_back(e);
    Sink->adj.push_back(g);

    Edges.push_back(e);
    Edges.push_back(g);
  }

  
  ss.clear();
  ss.str("");
  Nodes.push_back(Sink);

  //for(int i = 0; i < Nodes.size(); i++) cout << Nodes[i]->name << " " <<  Nodes[i]->val << endl;
}

Graph::~Graph()
{
  int i;
  for (i = 0; i < Nodes.size(); i++) delete Nodes[i];
  for (i = 0; i < Edges.size(); i++) delete Edges[i];
  
}

void Graph::Can_Spell_Word() {
  stringstream ss;
  int j;
  int k;


  while(Find_Shortest_Path(Source)) {
    for(int i = 0; i < Path.size(); i++) {
      if(Path[i]->reverse->flow > 0) {
        if(Path[i]->reverse->flow >= Cap) {
          Path[i]->reverse->flow -= Cap;
        }
        else {
          Path[i]->flow += Cap - Path[i]->reverse->flow;
          Path[i]->reverse->flow = 0;
        }
      }
      else {
        Path[i]->flow += Cap;
      }
      Path[i]->residual -= Cap;
      Path[i]->reverse->residual += Cap;
    }

  }
  for(int i = 0; i < Edges.size(); i++) {
    if(Edges[i]->n2->val == "SINK" && Edges[i]->flow == 0){
      cout << "Cannot spell " << Word << endl;
      return;
    } 
  }

  
  vector<int> answer (Nodes.size() - Die.size() - 2, -2);
  for(int i = 0; i < Edges.size(); i++) {
    
    ss << Edges[i]->n1->name;
    ss >> j;
    ss.clear();
    ss.str("");
    ss << Edges[i]->n2->name;
    ss >> k;
    ss.clear();
    ss.str("");
    if(Edges[i]->n1->val != "SOURCE" && Edges[i]->n2->val != "SINK" && Edges[i]->flow > 0 && j < k){
      answer[k - Die.size()] = j;
    } 
  }
  
  for(int i = 0; i < answer.size(); i++) {
    if(i != answer.size() - 1) cout << answer[i] << ",";
    else cout << answer[i] << ": ";
  }
  
  cout << Word << endl;
  return;
}

bool Graph::Find_Shortest_Path(Node *n) {

  Nodes[0]->distance = 0;
  Nodes[0]->backedge = NULL;
  for(int i = 1; i < Nodes.size(); i++) {
    Nodes[i]->distance = -1;
    Nodes[i]->backedge = NULL;
  }
  spqueue.push(n);
  while(!spqueue.empty()) {
    n = spqueue.front();
    spqueue.pop();


    for(int i = 0; i < n->adj.size(); i++) {
      if(n->adj[i]->n2->distance == -1 && n->adj[i]->residual > 0) {
        n->adj[i]->n2->distance = n->distance + 1;
        n->adj[i]->n2->backedge = n->adj[i];
        spqueue.push(n->adj[i]->n2);
      }
    }
  }

  
  if(Sink->distance != -1) {
    Path.clear();
    n = Sink;
    Cap = MaxCap;
    while(n->backedge != NULL) {
      Path.push_back(n->backedge);
      if(Cap > n->backedge->residual) Cap = n->backedge->residual;
      n = n->backedge->n1;
    }
    return true; 
  }
  return false;
}


int main(int argc, char **argv)
{
  Graph *G;
  
  list<string> die_string; 
  list <string>::iterator die_string_it;
  string l;
  

  if (argc > 3) {
    cerr << "usage: worddice dice-file word-list\n";
    exit(1);
  }

  fstream fs (argv[1], fstream::in);
  while (getline(fs, l)) {
    die_string.push_back(l);
  }
  fs.close();
  fstream fs2 (argv[2], fstream::in);

  while (getline(fs2, l)) {
    G = new Graph(die_string, die_string_it, l);
    G->Can_Spell_Word();
    delete G;
  }
  fs2.close();
  return 0;
}
