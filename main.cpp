#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include "Song.h"
#include "Library.h"
#include "Parser.h"
#include "SongChecker.h"

using namespace std;

int main() {
    //TODO deconstructor, remove, and timestamp
    std::string line = ""; //the input of the user
    Library music; //object of Library type to access Library class methods
    bool libSelect = false; //false if no playlist selected, true if it is selected
    Playlist selector;//current selected playlist
    std::string selectName; //name of the selected playlist
    SongChecker formatChecker; //checks song for correct format
    //procedure
    cout << "Welcome to your music app!" << endl;
    while (line != "exit") {
        std::cout << "Enter add, show, select, remove, clone, import, or exit: " << endl;
        getline(std::cin, line);
        Parser command(line); //creates object command with parameter line of object Parser type
        //Create string variables of the first, second, and 3rd operations divided by whitespace
        std::string option = command.getOperation();
        std::string type = command.getArg1();
        std::string name = command.getArg2();
        std::string name2 = command.getArg3();
        //deploys options using if statements depending on user input
        //add command can do the following:
        //(1) adds songs to library -done
        //(2) adds existing songs in the library to the playlist -done
        //(3) adds new playlists -done
        if (option == "add") { //cmd: add
            if (type == "song") { //cmd: add song
                if (name.empty()) {
                    while (true) {//if just add song, then will prompt CA1
                        bool isError = false;
                        std::string artist, title, duration, isExplicit, timeAdded, dateAdded;
                        bool Explicit = false;
                        cout << "Enter song title: " << endl;
                        getline(cin, title);
                        if (music.checkSong(title)) {
                            isError = true;
                            cout << "There exists a song already with that name!" << endl;
                            break;
                        }
                        cout << "Enter artist: " << endl;
                        getline(cin, artist);
                        cout << "Enter song duration (MM:SS format only!): " << endl;
                        getline(cin, duration);
                        cout << "Is the song explicit? (Enter y for true, n for false): " << endl;
                        getline(cin, isExplicit);
                        if (formatChecker.validExplicit(isExplicit)) {
                            if (formatChecker.checkExplicit(isExplicit)) {
                                Explicit = true;
                            }
                            else { Explicit = false; }
                        }
                        else {
                            cout << "Invalid choice for explicit. Restarting!" << endl;
                            isError = true;
                            break;
                        }
                        cout << "Enter the time right now (HH:MM:SS format only!): " << endl;
                        getline(cin, timeAdded);
                        cout << "Enter today's date (MM/DD/YYYY format only!): " << endl;
                        getline(cin, dateAdded);

                        //newasd = formatChecker.validExplicit(isExplicit);
                        if ( !formatChecker.isDuration(duration) || !formatChecker.isTimeAdded(timeAdded) || !formatChecker.isDateAdded(dateAdded) ) {
                            cout << "Wrong format. Please use correct format for song!" << endl;
                            isError = true;
                            break;
                        }

                        Song newSong = Song(title, artist, duration, Explicit, timeAdded, dateAdded);
                        music.addSong2Library(newSong);
                        cout << "The song: <" << newSong.return_title() << "> has been added!" << endl;
                        break;
                    }
                }
                else { //if there is a 3rd argument will add from lib to a selected playlist
                    if (!libSelect) { //checking if there is a selected playlist; there should be
                        cout << "You didn't select a playlist. Please select a playlist!" << std::endl;
                    }
                    else {
                        if (name2.empty()) {
                            music.addSong2Playlist(name, selectName);
                            //music.plistSelect(name, selectName); //updates selector to have the added song in it
                        }
                        else {
                            music.addSong2Playlist(name + " " + name2, selectName);
                            //music.plistSelect(name + " " + name2, selectName);
                        }
                    }
                }
            }
            else if (type == "playlist") {
                if (name.empty()) {
                    cout << "No name for the playlist has been entered. Enter here: " << std::endl;
                    getline(std::cin, line);
                    Playlist newPlaylist2(line);
                    //selector = newPlaylist2; //sets the selected playlist as the added one
                    music.addPlaylist(newPlaylist2);
                    selectName = line;
                    music.plistSelect(line, selectName);
                    libSelect = true; //boolean confirming that a playlist has been selected
                } else {
                    Playlist newPlaylist(name);
                    //selector = newPlaylist; //sets the selected playlist as the added one
                    music.addPlaylist(newPlaylist);
                    selectName = name;
                    music.plistSelect(name, selectName);
                    libSelect = true; //boolean confirming a playlist has been selected
                }
            }
            else {
                cout << "Need to enter <song> or <playlist> after as valid command." << std::endl;
            }
        }
        else if (option == "select") {
            if (type == "playlist") {
                if (name.empty()) {
                    std::cout << "Invalid command. Use: select playlist <name>" << std::endl;
                }
                else {
                    if (music.plistChecker(name)) {
                        music.plistSelect(name, selectName);
                        libSelect = true;
                    }
                    else {
                        std::cout << "No playlists exist of that name!" << std::endl;
                    }
                }
            }
            else if (type == "library") {
                libSelect = false;
                std::cout << "You have deselected the current playlist" << std::endl;
            }
            else {
                cout << "Please select playlist <playlist name> or library (to deselect)." << std::endl;
            }
        }
        else if (option == "clone") {
            if (libSelect) {
                if (type.empty()) {
                    cout << "Please enter a name for the clone!" << std::endl;
                }
                else {
                    music.clone(type, selectName);
                }
            }
            else {
                cout << "Please select a playlist before cloning!" << std::endl;
            }
        }
        else if (option == "show") {
            if (type == "playlist") {
                if (name.empty()) { //cmd: show playlist
                    //shows currently selected playlist
                    if (libSelect) { //if a playlist is selected
                        music.showPlaylistSongs(selectName);
                        //runs the selected playlist
                    }
                    else { //no playlist selected
                        cout << "Please select a playlist before showing!" << std::endl;
                    }
                }
                else { //cmd: show playlist <name>; checks playlist name matching other whise return error
                    music.showPlaylistSongs(name);
                }
            }
            else if (type == "playlists") {//cmd: show playlists
                music.showPlaylists();

            }
            else if (type == "songs") {//cmd: show songs
                music.showSongsOnly();
            }
            else if (type == "song") {// cmd: show song
                if (name.empty()) {
                    cout << "No song has been chosen!" << endl;
                }
                /*else if (libSelect) {
                    if (name2.empty()) { // cmd: show song <name>
                        music.show1SongPlaylist(name, selectName); //runs the library function that shows song info of identical name
                    }
                    else {
                        music.show1SongPlaylist(name + " " + name2, selectName);
                    }*/
                else { //nothing is selected check library
                    if (name2.empty()) { // cmd: show song <name>
                        music.showSongInfo(name); //runs the library function that shows song info of identical name
                    }
                    else {
                        music.showSongInfo(name + " " + name2);
                    }
                }
            }
            else {
                cout << "Invalid command. Need a second argument!" << endl;
            }
        }
        else if (option == "import") {
            if (type.empty()){
                cout << "Error! Nothing inputted to import!" << endl;
            }
            else {
                stringstream streamy(line);
                for (auto plist = istream_iterator<string>(streamy); plist != istream_iterator<string>(); plist++) {
                    if (*(plist) == "import") {
                        continue;
                    }
                    music.import(*(plist), libSelect, selectName);
                }
            }
        }
        else if (option == "remove") {
            if (type == "song") {
                if (name2.empty()) {
                    if (libSelect) { music.removeSongPlaylist(name, selectName); } ///TODO
                    else { music.removeSongLib(name); }
                }
                else {
                    if (libSelect) { music.removeSongPlaylist(name + " " + name2, selectName); }
                    else { music.removeSongLib(name + " " + name2); }
                }
            }
            else if (type == "playlist") {
                if (libSelect) {
                    if (name.empty()) {
                        music.removePlaylist(selectName);
                    }
                    else { music.removePlaylist(name); }
                }
                else { music.removePlaylist(name); }
            }
            else { cout << "Invalid command!" << endl; }
        }
    }
    return 0;
}