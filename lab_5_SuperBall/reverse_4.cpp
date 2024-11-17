/* This code inserts each string at the front of a vector, instead of a list.
   What this does is resize the vector at every insert() call, move each element
   over one, and put the new string at element 0.  Thus, it is *really* 
   inefficient code.  Its performance will scale quadratically with the
   size of the input. */

#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector <string> lines;
  vector <string>::const_iterator lit;
  string s;

  while (getline(cin, s)) lines.insert(lines.begin(), s);
 
  for (lit = lines.begin(); lit != lines.end(); lit++) {
    cout << *lit << endl;
  }

  return 0;
}
