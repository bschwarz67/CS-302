#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include "MusicFileInfo.h"
using namespace std;

int main() {
	string fileLine;
	char title[100], time[100], artist[100], album[100], genre[100], track[100];
	ifstream musicFile;
	map <string, ArtistInfo> artists;
	musicFile.open("music.txt");
	
	while(getline(musicFile, fileLine)) {
		sscanf(fileLine.c_str(), "%s %s %s %s %s %s", title, time, artist, album, genre, track);
		cout << title << endl;
	}
	
	
/*
	for(int i = 0; i < fileLine.length(); i++) {
		if(fileLine[i] == '_') {
			fileLine[i] = ' ';
		}
	}
*/

	return 0;
}
