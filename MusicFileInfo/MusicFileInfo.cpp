#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include "MusicFileInfo.h"
using namespace std;

int main() {
	string fileLine;
	char title[100], time[100], name[100], album[100], genre[100], track[100];
	int minutes, seconds;
	ifstream musicFile;
	map <string, Artist> artists;
	map <string, Artist>::iterator artistsIt;

	musicFile.open("music.txt");
	
	while(getline(musicFile, fileLine)) {
		sscanf(fileLine.c_str(), "%s %s %s %s %s %s", title, time, name, album, genre, track);
		artistsIt = artists.find(name);
		if(artistsIt == artists.end()) {
			artistsIt = artists.insert(pair<string, Artist>(name, Artist())).first;
			artistsIt->second.name = name;
			sscanf(time, "%d:%d", &minutes, &seconds);
			artistsIt->second.time = 60 * minutes + seconds;
			cout << artistsIt->second.time << endl;
					
		}
		else {
			sscanf(time, "%d:%d", &minutes, &seconds);
			artistsIt->second.time += 60 * minutes + seconds;

		}
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
