#ifndef LIBRARY_H
#define LIBRARY_H
#include "Playlist.h"
#include "Song.h"

class Library {
public:
    Library();
    void addSong2Playlist(std::string songName, std::string plistName);
    void addSong2Library(Song s);
    void addPlaylist(Playlist plist);
    void plistSelect(std::string plistName, std::string &selectedName);
    bool plistChecker(std::string);
    bool checkSong(std::string);
    void clone(std::string, std::string);
    void showSongsOnly();
    void show1SongPlaylist(std::string, std::string);
    void showPlaylists();
    void showPlaylistSongs(std::string plistName);
    void showSongInfo(std::string songName);
    void removePlaylist(std::string);
    void removeSongLib(std::string);
    void removeSongPlaylist(std::string, std::string);
    void import(std::string name, bool libSelect, std::string selector);

    virtual ~Library();

    int indexReturn();
private:
    int n;
    int capacity;
    int numPlist;
    int plistCap;
    Playlist* playlists;
    Song* song1;
};
#endif