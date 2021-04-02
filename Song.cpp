#include "Song.h"

Song::Song() {}

Song::Song(string title, string artist, string duration, bool Explicit, string timeAdded, string dateAdded) {
    this->title = title;
    this->artist = artist;
    this->duration = duration;
    this->dateAdded = dateAdded;
    this->timeAdded = timeAdded;
    this->Explicit = Explicit;
}

ostream &operator<<(ostream &out, Song &s) {
    out << "Song Title: " << s.title << endl
    << "Artist: " << s.artist << endl
    << "Song Duration: " << s.duration << endl
    << (s.Explicit ? "y" : "n") << endl
    << "Time Added: " << s.timeAdded << endl
    << "Date Added: " << s.dateAdded << endl;
    return out;
}

std::string Song::return_title() { //returns the song name/title for accesibility
    return title;
}

bool Song::operator==(const Song &s) { //overload operator
    if (this->title == s.title) {
        return true;
    } else {
    return false;
    }
}
