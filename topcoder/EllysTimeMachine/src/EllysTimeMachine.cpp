#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

string getTime(string time) {
	int n, h, m;
	char buf[100];


	n = sscanf(time.c_str(), "%d:%d", &m, &h); //read the input string into two integers, switching the hours and the minutes
	
	//convert the hours integer to minutes and the minutes integer to hours
	if (h == 0) {
		h = 60 / 5;
	}
	else {
		h = h / 5;
	}	
	m = m * 5;


	sprintf(buf, "%02d:%02d", h, m); //put the converted integers back into a formatted time string
	time = buf;
	
	return time;
}

int main() {
	string time;
	cin >> time;
	time =  getTime(time);
	cout << time;
	return 0;
}
