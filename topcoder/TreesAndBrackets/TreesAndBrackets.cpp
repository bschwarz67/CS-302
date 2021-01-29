#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class TreesAndBrackets {
	public:
		string check(string t1, string t2);
};

string TreesAndBrackets::check(string t1, string t2) {
	string cp = t1;
	string res;
	
	for(int i = 0; i < cp.length() - 1; i++) {
		t1 = cp;
		if(t1[i] == '(' && t1[i+1] == ')') {
			if(t1 == t2) return "Possible";
			else if(t1 == "") return "Impossible";
			else t1.erase(i,2);
			
			if(t1 == t2) return "Possible";
			else if(t1 == "") return "Impossible";
			else {
				res = check(t1, t2);
				if (res == "Possible") return res;
			}
		} 
	}
	return res;
	
}

int main() {
	TreesAndBrackets tab;	
	cout << tab.check("((())((())())())", "(()(())())") << endl;
	cout << tab.check("(()()())", "((()))") << endl;

	return 0;
}
