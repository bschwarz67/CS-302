/* This program now creates the list in reverse order by inserting each
   string before the first element in the list.  This is equivalent to
   calling push_front(). */

#include <iostream>
#include <list>
using namespace std;

int main()
{
  list <string> lines;
  list <string>::const_iterator lit;
  string s;

  while (getline(cin, s)) lines.insert(lines.begin(), s);  // This is equivalent to push_front().
 
  for (lit = lines.begin(); lit != lines.end(); lit++) {
    cout << *lit << endl;
  }
  return 0;
}
