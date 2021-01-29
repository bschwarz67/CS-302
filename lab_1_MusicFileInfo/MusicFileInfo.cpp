#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include "MusicFileInfo.h"
using namespace std;

int main() {
	string fileLine;
	char title[100], name[100], album[100], genre[100];
	int minutes, seconds;
	int track;
	ifstream musicFile;
	map <string, Artist> artists;
	map <string, Artist>::iterator artistsIt;
	map <string, Album>::iterator albumsIt;
	map <int, Song>::iterator songsIt;

	musicFile.open("music.txt");
	
	while(getline(musicFile, fileLine)) {
		//put data from each line into variables as predetermined by data format
		sscanf(fileLine.c_str(), "%s %d:%d %s %s %s %d", title, &minutes, &seconds, name, album, genre, &track);
		
		//clean artist name to not have any '_', only spaces
		for(int i = 0; name[i] != '\0'; i++) {
			if(name[i] == '_') {
				name[i] = ' ';
			}
		}
		artistsIt = artists.find(name);

		//if the artist doesnt exist in the map, add the artist to the map and input the time and nsong data from the first song in the Artist object
		if(artistsIt == artists.end()) {
			artistsIt = artists.insert(pair<string, Artist>(name, Artist())).first;
			artistsIt->second.name = name;
			artistsIt->second.time = 60 * minutes + seconds;
			artistsIt->second.nsongs = 1;				
		}
		//if artist already exists, update the time and nsong data from the next song by the artist in the Artist object
		else {
			artistsIt->second.time += 60 * minutes + seconds;
			artistsIt->second.nsongs += 1;				
		}

		//clean album to not have any '_', only spaces
		for(int i = 0; album[i] != '\0'; i++) {
			if(album[i] == '_') {
				album[i] = ' ';
			}
		}

		albumsIt = artistsIt->second.albums.find(album);

		//if album doesnt already exist in the albums map of artist, add the album to the map and input the time and nsongs data in the ALbum object.
		if(albumsIt == artistsIt->second.albums.end()) {
			albumsIt = artistsIt->second.albums.insert(pair<string, Album>(album, Album())).first;
			albumsIt->second.name = album;
			albumsIt->second.time = 60 * minutes + seconds;
			albumsIt->second.nsongs = 1;
						
		}
		//if album already exists in teh albums map of artist, update the time and nsongs data in the Album object
		else {
			albumsIt->second.time += 60 * minutes + seconds;
			albumsIt->second.nsongs += 1;

		}
		//clean title to not have any '_' only spaces
		for(int i = 0; title[i] != '\0'; i++) {
			if(title[i] == '_') {
				title[i] = ' ';
			}
		}
		//input Song to Album map of Song objects, input the title, track#, time data for the Song object
		songsIt = albumsIt->second.songs.insert(pair<int, Song>(track, Song())).first;
		songsIt->second.title = title;
		songsIt->second.track = track;
		songsIt->second.time = 60 * minutes + seconds;
	}


	//print the data lexicographically in the format designated by the lab.
	for(artistsIt = artists.begin(); artistsIt != artists.end(); ++artistsIt) {
		printf("%s: %d, %02d:%02d\n", artistsIt->second.name.c_str(), artistsIt->second.nsongs, artistsIt->second.time / 60, artistsIt->second.time % 60);
		for(albumsIt = artistsIt->second.albums.begin(); albumsIt != artistsIt->second.albums.end(); albumsIt++) {
			printf("        %s: %d, %02d:%02d\n", albumsIt->second.name.c_str(), albumsIt->second.nsongs, albumsIt->second.time / 60, albumsIt->second.time % 60);
			for(songsIt = albumsIt->second.songs.begin(); songsIt != albumsIt->second.songs.end(); songsIt++) {
				printf("                %d. %s: %02d:%02d\n", songsIt->first, songsIt->second.title.c_str(), songsIt->second.time / 60, songsIt->second.time % 60);
			}
		}
	}


	return 0;
}
