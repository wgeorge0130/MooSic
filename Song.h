#ifndef SONG_H
#define SONG_H
#include <iostream>
#include <string>
using namespace std;

class Song {
public:
    Song();
    Song(string title, string artist, string duration, bool Explicit, string timeAdded, string dateAdded);
    friend ostream &operator<<(ostream &out, Song &s);
    bool operator==(const Song &s);
    std::string return_title();

private:
    string artist;
    string title;
    string duration;
    string dateAdded;
    string timeAdded;
    bool Explicit;
};
#endif