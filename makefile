# Use the first FLAGS definition for debugging, the 2nd for optimizing your code
FLAGS = -Wall -Wextra -g

NAME = MooSic
GITHUB_USERID = wgeorge0130
EXECUTABLE = main.exe

all:	main

replaceme:
	echo "Did you remember to set the variables in the makefile?! Oh yes I did!"

tar: clean
	cd .. && tar -cvzf CA$(CA)_$(LASTNAME)_$(BU_USERID).tar.gz $(NAME)-$(GITHUB_USERID) && cd -

scrub: clean
	rm ~* *.swp *\#

run: $(EXECUTABLE)
	./$(EXECUTABLE)

main:	main.o Library.o Song.o SongChecker.o Playlist.o Timestamp.o
	g++  main.o Library.o Song.o SongChecker.o Playlist.o Timestamp.o -o main.exe

# Specify how the object files should be created from source files
main.o:	main.cpp
	g++ -c main.cpp

Library.o:	Library.cpp
	g++ -c Library.cpp

Song.o:	Song.cpp
	g++ -c Song.cpp

SongChecker.o: SongChecker.cpp
	g++ -c SongChecker.cpp

Playlist.o:	Playlist.cpp
	g++ -c Playlist.cpp

Timestamp.o:	Timestamp.cpp
	g++ -c Timestamp.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o $(EXECUTABLE)
