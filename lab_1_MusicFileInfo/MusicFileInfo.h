#include <string>
#include <map>
#include <vector>
using namespace std;


class Song {
	public:
		string title;
		int time;
		int track;
};

class Album {
	public: 
		string name;
		int time;
		map <int, Song> songs;
		int nsongs;
};

class Artist {
	public:
		string name;
		int time;
		map <string, Album> albums;
		int nsongs;
	private:
};
