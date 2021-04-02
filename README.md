# MooSic (Music App)
### By: George Wang
Music application is a C++ database of playlist and song ADTs which allows user-based commands to initiate storage-management algorithms. 

## Installation

Use the included makefile to compile and run the main executable

Simply run the following commands in terminal:

```terminal
make all
./main.exe
```
Once done, to delete main.exe and the .o files, run:
```
make clean
```
CMake can be used on IDE or Windows/Mac environment.

## Usage
### Multiple commands can be run in the interface
#### [Add Features]
Add song to library:
```terminal
add song
```
Add song to currently selected playlist:

```
add song <song title>
```
Add playlist:
```
add playlist <playlist name>
```
#### [Show Features]

Show all songs in library:
```
show songs
```
Show all songs in selected playlist:
```
show playlist //if selected
show playlist <playlist name>
```
Show all playlists:
```
show playlists
```
Show song information of selected playlist (if no playlist selected, it will show song information from the library):
```
show song <song title>
```
#### [Select Feature]
Select a playlist:
```
select playlist <playlist name>
```
Deselects current selected playlist:
```
select library
```
#### [Remove Features]
Remove song from currently selected playlist (if no playlist selected, song will be removed from library):
```
remove song <song title>
```
Remove playlist:
```
remove playlist <playlist name>
```
#### [Clone Feature]
Clone the currently selected playlist and names it <clone playlist name> :
```
clone <clone playlist name>
```
#### [Import Feature]
Import all the songs from all of the inputted playlist names into the currently selected playlist name (if no playlist is selected, all songs will be added to the library; duplicates will not be added):
```
clone <playlist name> [<playlist name> <playlist name> ... ]
``` 


## Testing
Application was tested in both Linux and Windows environments.

Python tester file included can be run to test the different algorithm functionality. 
To run tester file, simply run make to compile:
```
python3 WangTester.py ./main.exe t<n>
```
Replace n with a number from 0-9 to access any of the 10 available tests.

Python 3 must be installed prior to running tester. 

Valgrind was used to test for memory leaks. 
 



## TODO
GUI design

Real music file (i.e. mp3) management implementation

Different data structures...