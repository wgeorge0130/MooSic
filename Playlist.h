#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "Song.h"
#include "Timestamp.h"

class Playlist {
public:
    Playlist();
    Playlist(const Playlist& source);
    Playlist(std::string plname);
    void add(Song song);
    void showSongsOnly();
    void showSong(std::string);
    void removeSong(std::string inputsong);
    void set_name(std::string name);
    std::string return_name();
    std::string timestamp();
    int plist_n_return() const;
    Song* returnPlaylists() const;
    Playlist& operator+=(const Playlist& source);
    virtual ~Playlist();

private:
    int n;
    int capacity;
    Song* playlist;
    std::string playlistName;
    Timestamp finTime;
};
#endif
