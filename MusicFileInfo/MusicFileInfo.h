#include <string>
#include <map>
#include <vector>
using namespace std;


class Song {
	public:
		string name;
		int time;
		
};

class Album {
	public: 
		string name;
		int time;
		vector <Song> songs;
		int nsongs;
};

class Artist {
	public:
		string name;
		int time;
		map <string, Album> albums;
	private:
};
