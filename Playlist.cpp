#include "Playlist.h"

Playlist::Playlist() {} //empty constructor to allow main to create type playlist w/o parameters

Playlist::Playlist(const Playlist& source) {
    //cout << "copy constructor baby" << std::endl;
    //for debugging
    capacity = source.capacity;
    n = source.n;
    finTime = source.finTime;
    playlistName = source.playlistName;
    Song* tempArr = new Song[source.capacity];
    for (int i = 0; i < source.n; i++) {
        tempArr[i] = source.playlist[i];
    }
    playlist = tempArr;
}

Playlist::Playlist(std::string plname) {
    capacity = 1; //capacity of playlist (it is dynamic)
    n = 0; //amount of songs currently in playlist
    playlist = new Song[capacity];
    //libarr = other.arrreturn(); //gets the song1 array
    //libsize = other.sizereturn(); //gets the amount of songs a.k.a <n> in Library class
    playlistName = plname; //name of playlist
    finTime = Timestamp();
    //printf("awjgiowagjoi\n");
}

Playlist& Playlist::operator+=(const Playlist& source) {
    Song s;
    bool found;
    for (int i = 0; i < source.n; i++) {
        found = false;
        s = source.playlist[i];
        for (int j = 0; j < this->n; j++) {
            if (s == this->playlist[j]) {
                found = true;
                cout << "Duplicate song found: <" << s << ">. Not added!" << endl;
            }
        }
        if (!found) {
            this->add(s);
        }
    }
    return *this;
}

Playlist::~Playlist() { //destructor for dynamic array
    //delete[] playlist; //BREAKS MY CODE FOR SOME REASON
}

void Playlist::add(Song song) { //adds song into selected playlist
    if (n >= capacity) {
        Song *song2 = new Song[capacity * 2];
        for (int i = 0; i < n; i++) {
            song2[i] = playlist[i];
        }
        delete[] playlist;
        playlist = song2;
        capacity = capacity * 2;
         //n++??????
    }
    playlist[n] = song;
    n = n + 1;
}

void Playlist::showSongsOnly() {
    cout << "Your songs in " << "<" << playlistName << ">:" << endl;
    for (int i = 0; i < n; i++) { //TODO testing
        cout << playlist[i] << endl; //playlist is a song pointer
    }
}

void Playlist::showSong(std::string songName) { //shows singular song
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (songName == playlist[n].return_title()) {
            cout << playlist[n] << endl;
            return;
        }
    }
    if (!found) {
        cout << "There is no song in your selected playlist" << endl;
    }
}

void Playlist::removeSong(std::string inputsong) {
    if (n == 0) {
        cout << "Empty playlist. Nothing to remove!" << endl;
    }
    else {
        Song *temp = new Song[n - 1];
        int index = 0;
        while (index < (n - 1)) {
            if (inputsong == playlist[index].return_title()) {
                break;
            }
            temp[index] = playlist[index];
            index++;
        }
        if (inputsong != playlist[index].return_title()) {
            cout << "Nothing to remove!" << endl;
            return;
        }
        for (int i = index; i < n - 1; i++) {
            temp[i] = playlist[i + 1];
        }
        delete[] playlist;
        playlist = temp;
        n--;
        capacity--;
    }
}
void Playlist::set_name(std::string name) { //sets name used in clone and copy constructor
    playlistName = name;
}

std::string Playlist::return_name() { //returns name of selected playlist
    return playlistName;
}

int Playlist::plist_n_return() const {
    return n;
}

Song* Playlist::returnPlaylists() const { //returns the playlist of songs for accessibility
    return playlist;
}

std::string Playlist::timestamp() {
    return finTime.toString();
}

