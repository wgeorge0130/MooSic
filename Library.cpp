#include "Library.h"

Library::Library() {
    n = 0; //song amount
    capacity = 1; //capacity of songs
    numPlist = 0; //playlist amount
    plistCap = 1; //capacity of playlists
    song1 = new Song[capacity]; //array or list of songs
    playlists = new Playlist[plistCap]; //array or list of playlists
}

Library::~Library() { //destructor for dynamic arrays
    delete[] song1;
    delete[] playlists; //BREAKS MY CODE FOR SOME REASON
}

bool Library::checkSong(std::string songName) {
    for (int i = 0; i < n; i++) {
        if (songName == song1[i].return_title()) {
            return true;
        }
    }
    return false;
}

void Library::addSong2Playlist(std::string songName, std::string plistName) {
    int index;
    for (int j = 0; j < numPlist; j++) {
        if (plistName == playlists[j].return_name()) {
            index = j;
        }
    }
    bool pLocated = false;
    for (int i = 0; i < n; i++) {
        if (songName == song1[i].return_title()) {
            playlists[index].add(song1[i]);
            pLocated = true;
            cout << "The song called <" << song1[i].return_title() << "> has been added to the playlist <" <<
                 playlists[index].return_name() << ">" << std::endl;
            return;
        }
    }
    if (!pLocated) { //if pLocated still didn't turn true, then there exists no song in the library
        cout << "No such song exists. Please enter an existing song." << std::endl;
    }
}

void Library::addSong2Library(Song s) { //only used in import
    if (n >= capacity) {
        Song *song2 = new Song[capacity * 2];
        for (int i = 0; i < n; i++) {
            song2[i] = song1[i];
        }
        delete[] song1;
        song1 = song2;
        capacity = capacity * 2;
    }
    song1[n] = s;
    n++;
}

void Library::addPlaylist(Playlist plist) { //adds playlist to library when called from main
    bool fileConflict = false; //checking if there is a file conflict, meaning same name playlist existing
    for (int i = 0; i < numPlist; i++) {
        if (plist.return_name() == playlists[i].return_name()) {
            fileConflict = true;
        }
    }
    if (!fileConflict) {//if there isn't a file conflict
        cout << "The playlist called <" << plist.return_name() << "> was made." << std::endl;
        if (numPlist >= plistCap) {
            Playlist *plist2 = new Playlist[plistCap * 2];
            for (int i = 0; i < numPlist; i++) {
                plist2[i] = playlists[i];
            }
            delete[] playlists;
            playlists = plist2;
            plistCap = plistCap * 2;
        }
        playlists[numPlist] = plist;
        numPlist++;
    } else {
        cout << "You already have a file of that name! File conflict!" << std::endl;
    }
}

//bool Library::plistSelect(std::string plistName, Playlist &selector) {
//    for (int i = 0; i < numPlist; i++) { //runs through playlist to check if there exists a name equivalent to the user inputed one
//        if (plistName == playlists[i].return_name()) { //if found
//            selector = playlists[i];
//            return true;//runs the return of correct playlist to be selected
//        }
//    }
//    std::cout << "No playlists exist of that name!" << std::endl; //error message
//    return false;
//}

void Library::plistSelect(std::string inputName, std::string &selectName) {
   for (int i = 0; i < numPlist; i++) {
       if (inputName == playlists[i].return_name()) {
           selectName = playlists[i].return_name();
           cout << "Playlist: <" << selectName << "> was selected!" << endl;
           return;
       }
   }
}
bool Library::plistChecker(std::string inputName) {
    for (int i = 0; i < numPlist; i++) {
        if (inputName == playlists[i].return_name()) {
            return true;
        }
    }
    return false;
}
//int Library::indexReturn(std::string plistName, int index) { //returns the index of playlist in the list of playlists
//    for (int i = 0; i < numPlist; i++) {
//        if (plistName == playlists[i].return_name())
//           return i;
//    }
//}

//std::string Library::findName(int index) {
//    if (index <= numPlist) {
//        return playlists[index].return_name();
//    } else { cout << "Wrong index. Error!" << endl; } //for debugging purposes
//}

void Library::clone(std::string playlistName, std::string selectedName) {//clones playlist and runs the above add playlist function
    for (int i = 0; i < numPlist; i++) {
        if (selectedName == playlists[i].return_name()) {
            Playlist clonePlaylist = playlists[i];
            clonePlaylist.set_name(playlistName);
            addPlaylist(clonePlaylist);
            cout << "Clone of playlist <" << selectedName << "> called <" << playlistName << "> was created!" << endl;
            return;
        }
    }
    /*if (playlists[n].plist_n_return() >= playlists[n].pCap_return()) {
        playlists[n].setCapAmnt(playlists[n].pCap_return() + 1, playlists[0].plist_n_return() + 1);
    }*/
    //playlists[clone.plist_n_return()].add()
}

void Library::removePlaylist(/*const string&*/std::string inputsong) {
    //TODO remove function breaks code: Process finished with exit code -1073740940 (0xC0000374)
    if (numPlist == 0) {
        cout << "No playlist. Nothing to remove!" << endl;
    } else {
        Playlist *temp = new Playlist[numPlist - 1];
        int index = 0;
        while (index < (numPlist - 1)) {
            if (inputsong == playlists[index].return_name()) {
                break;
            }
            temp[index] = playlists[index];
            index++;
        }
        if (inputsong != playlists[index].return_name()) {
            cout << "Nothing to remove!" << endl;
            return;
        }
        for (int i = index; i < numPlist - 1; i++) {
            temp[i] = playlists[i + 1];
        }
        delete[] playlists;
        playlists = temp;
        numPlist--;
        plistCap--;
    }
}

void Library::removeSongLib(std::string inputsong) {
    if (n == 0) {
        cout << "Empty library. Nothing to remove!" << endl;
    }
    else {
        Song *temp = new Song[n - 1];
        int index = 0;
        while (index < (n - 1)) {
            if (inputsong == song1[index].return_title()) {
                break;
            }
            temp[index] = song1[index];
            index++;
        }
        if (inputsong != song1[index].return_title()) {
            cout << "Nothing to remove!" << endl;
            return;
        }
        for (int i = index; i < n - 1; i++) {
            temp[i] = song1[i + 1];
        }
        delete[] song1;
        song1 = temp;
        n--;
        capacity--;
    }
}

void Library::removeSongPlaylist(std::string songName, std::string selectedPlaylist) {
    for (int i = 0; i < numPlist; i++) {
        if (selectedPlaylist == playlists[i].return_name())
            playlists[i].removeSong(songName);
            cout << "The song <" << songName << "> was removed from playlist <" << selectedPlaylist << "> !" << endl;
            return;
    }
}

//}


void Library::showSongsOnly() { //shows songs and all info like CA1
    for (int i = 0; i < n; i++) {
        cout << song1[i] << endl;
    }
}

void Library::show1SongPlaylist(string songName, string pListName) {
    for (int i = 0; i < numPlist; i++) {
        if (pListName == playlists[i].return_name()) {
            playlists[i].showSong(songName);
            return;
        }
    }
}

void Library::showPlaylists() {
    //Shows the playlists that are part of the library,
    // including the dates and times they were created,
    // but not including the songs they contain.
    cout << "All of your playlists in the music app: " << endl;
    for (int i = 0; i < numPlist; i++) {
        cout << playlists[i].return_name() << endl;
        cout << "The above playlist was created at: " << playlists[i].timestamp() << endl;
    }
}

void Library::showPlaylistSongs(std::string plistName) { //shows all songs in a specific/selected playlist
    bool found = false; //checking if there is a playlist of such name
    for (int i = 0; i < numPlist; i++) {
        if (plistName == playlists[i].return_name()) {
            playlists[i].showSongsOnly();
            found = true;
            return;
        }
    }
    if (!found) {
        cout << "No playlist exists of this name." << endl;
    }
}

void Library::showSongInfo(std::string songName) { //shows singular song info from library
    bool found = false; //checking if there is a song of such name
    for (int i = 0; i < n; i++) {
        if (songName == song1[i].return_title()) {
            cout << song1[i] << endl;
            found = true;
            return;
        }
    }
    if (!found) {
        cout << "No song exists of this name in library." << endl;
    }
}

void Library::import(std::string name, bool libSelect, std::string selector) {
    int index;
    int windex;
    for (int i = 0; i < numPlist; i++) { //finding matching playlist for name
        if (name == playlists[i].return_name()) { index = i; }
    }
    for (int j = 0; j < numPlist; j++) { //finding matching playlist for selector
        if (selector == playlists[j].return_name()) { windex = j; }
    }
    Playlist newP = playlists[index];
    if (libSelect) {
        playlists[windex] += newP; //override operator for playlists
    }
    else {
        Song s;
        bool found;
        for (int i = 0; i < newP.plist_n_return(); i++) {
            found = false;
            s = newP.returnPlaylists()[i];
            for (int j = 0; j < n; j++) {
                if (s == song1[j]) {
                    found = true;
                    cout << "Duplicate song found: <" << s << ">. Not added!" << endl;
                }
            }
            if (!found) {
                addSong2Library(s);
            }
        }
    }
}
