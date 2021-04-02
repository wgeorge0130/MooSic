import subprocess
import sys
import threading
import time

ALL_TESTS = """
#  **ADD/REMOVE/SHOW SONGS**
#  Add Songs 1-5. Removes Songs 1,3,5. Show Songs.
#  [Output]: Songs 2, 4
add song\nSong 1\nArtist 1\n00:01\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00:02\nn\n00:00:02\n02/02/2000
add song\nSong 3\nArtist 3\n00:03\nn\n00:00:03\n03/03/2000
add song\nSong 4\nArtist 4\n00:04\ny\n00:00:04\n04/04/2000
add song\nSong 5\nArtist 5\n00:05\nn\n00:00:05\n05/05/2000
remove song Song 1
remove song Song 3
remove song Song 5
show songs
exit

%%%
#   **ADD/REMOVE PLAYLISTS**
#   Add Playlists 1-5. Remove Playlists 1,3,5. Show all Playlists.
#   [Output]: Playlists 2, 4.
add playlist Playlist1
add playlist Playlist2
add playlist Playlist3
add playlist Playlist4
add playlist Playlist5
remove playlist Playlist1
remove playlist Playlist3
remove playlist Playlist5
show playlists
exit

%%%
#   **DESCRIPTION**
#   Add Song 1-2 to Library. 
#   Add Playlist 1-2 to Library.
#   Select Playlist 1 and Add Song 2. 
#   Select Playlist 2 and Add Song 1.
#   Select Playlist 1, Remove Song 2, and Add Song 1. 
#   Select Playlist 2, Remove Song 1, and Add Song 2.
#   Show Playlist 1, Show Playlist 2.
#   [Output]: Song 1 in Playlist 1, Song 2 in Playlist 2.
add song\nSong 1\nArtist 1\n00:01\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00:02\nn\n00:00:02\n02/02/2000
add playlist Playlist1
add playlist Playlist2
select playlist Playlist1
add song Song 2
select playlist Playlist2
add song Song 1
select playlist Playlist1
remove song Song 2
add song Song 1
select playlist Playlist2
remove song Song 1
add song Song 2
show playlist Playlist1
show playlist Playlist2
exit

%%%
#   **DESCRIPTION**
#   Add Songs 1-3 to Library
#   Add Playlist1 and Add Songs 1-3 into it.
#   Clone Playlist2 (from Playlist1)
#   Clone Playlist3 (from Playlist2)
#   Remove all Songs from each Playlists, then Add Songs that matches Playlist Number.
#   [Output]: Playlist'x' contains Song 'x'
add song\nSong 1\nArtist 1\n00:01\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00:02\nn\n00:00:02\n02/02/2000
add song\nSong 3\nArtist 3\n00:03\ny\n00:00:03\n03/03/2000
add playlist Playlist1\nadd song Song 1\nadd song Song 2\nadd song Song 3
clone Playlist2
select playlist Playlist2
clone Playlist3
select playlist Playlist1\nremove song Song 1\nremove song Song 2\nremove song Song 3\nadd song Song 1
select playlist Playlist2\nremove song Song 1\nremove song Song 2\nremove song Song 3\nadd song Song 2
select playlist Playlist3\nremove song Song 1\nremove song Song 2\nremove song Song 3\nadd song Song 3
show playlist Playlist1\nshow playlist Playlist2\nshow playlist Playlist3
exit

%%%
#   **DESCRIPTION**
#   Add Songs 1-3 to Library
#   Add Playlist1 and Add Songs 1,2 into it.
#   Add Playlist2 and Add Songs 2,3 into it.
#   Import Playlist2 into Playlist1. 
#   [Output]: Playlist1 containing Songs 1,2,3. 
add song\nSong 1\nArtist 1\n00:01\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00:02\nn\n00:00:02\n02/02/2000
add song\nSong 3\nArtist 3\n00:03\ny\n00:00:03\n03/03/2000
add playlist Playlist1\nadd song Song 1\nadd song Song 2
add playlist Playlist2\nadd song Song 2\nadd song Song 3
select playlist Playlist1
import Playlist2
show playlist Playlist1
exit

%%%
#   **DESCRIPTION**
#   Add Songs 1-3 to library
#   Add Playlist1 and Add Songs 1,2 into it.
#   Add Playlist2 and Add Songs 2,3 into it.
#   Select Playlist1 and Clone it as Playlist3.
#   Select Playlist3 and Import Playlist2.
#   Show Playlist3.
#   [Output]: Playlist3 containing Songs 1,2,3.
add song\nSong 1\nArtist 1\n00:01\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00:02\nn\n00:00:02\n02/02/2000
add song\nSong 3\nArtist 3\n00:03\ny\n00:00:03\n03/03/2000
add playlist Playlist1\nadd song Song 1\nadd song Song 2
add playlist Playlist2\nadd song Song 2\nadd song Song 3
select playlist Playlist1
clone Playlist3
select playlist Playlist3
import Playlist2
show playlist Playlist3
exit

%%%
#   **DESCRIPTION**
#   Add Songs 1-2 to Library
#   Add Playlist1.
#   Add Playlist2 and Add Song 1 into it.
#   Add Playlist3 and Add Song 2 into it.
#   Select Playlist1 and Import both other Playlists.
#   Show Playlist1
#   [OUTPUT]: Playlist1 containing Song 1,2
add song\nSong 1\nArtist 1\n00:01\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00:02\nn\n00:00:02\n02/02/2000
add playlist Playlist1
add playlist Playlist2\nadd song Song 1
add playlist Playlist3\nadd song Song 2
select playlist Playlist1
import Playlist2 Playlist3
show playlist Playlist1
exit

%%%
#   **DESCRIPTION**
#   Add Songs 1-2 to Library
#   Add Playlist 1 and Add Song 1 into it.
#   Add Playlist 2 and Add Song 2 into it.
#
#   [ OUTPUTS for show operations ]
#   'show songs': Outputs Song 1,2 from Library.
#   'show songs Song 2': Outputs Song 2 from Library.
#   'select playlist Playlist1'
#   'show songs Song 2': Outputs that Can't Find Song 2 in Playlist1. 
#   'show playlists': Outputs Playlists 1,2
#   'show playlist Playlist2': Outputs Song 2 from Playlist2
#   'show playlist': Outputs Song 1 from currently selected Playlist1
add song\nSong 1\nArtist 1\n00:01\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00:02\nn\n00:00:02\n02/02/2000
add playlist Playlist1\nadd song Song 1
add playlist Playlist2\nadd song Song 2
show songs
show song Song 2
select playlist Playlist1
show song Song 2
show playlists
show playlist Playlist2
show playlist
exit

%%%
#   **DESCRIPTION**
#   (1) malinformed times and dates
#   (2) creating a playlist that already exists.
#   (3) unknown operations
#   (4) not providing enough parameters.

add song\nSong 1\nArtist 1\n999:999\ny\n00:00:01\n01/01/2000
add song\nSong 2\nArtist 2\n00*01\ny\n00:00:01\n01/01/2000
add song\nSong 3\nArtist 3\n00:01\nn\n000:000:001\n01/01/2000
add song\nSong 4\nArtist 4\n00:01\ny\n00*00*01\n01/01/2000
add song\nSong 5\nArtist 5\n00:01\nn\n00:00:01\n13/13/3000
add song\nSong 6\nArtist 6\n00:01\ny\n00:00:01\n11*11*2000

add playlist Playlist1
add playlist Playlist1
 
delete playlist Playlist1

select playlist Playlist1
show
clone
import

exit


%%%
#   **DESCRIPTION**
#   (1) malinformed times and dates
#   (2) creating a playlist that already exists.
#   (3) unknown operations
#   (4) not providing enough parameters.

add song\nSong 1\nArtist 1\nas:as\ny\nasdasd\n01/01/2000
add song\nSong 2\nasdasdad 2\n00*01\ny\n0asdas\n01/01/2000
add song\nSong 3\nasdasdasd\n00:01\nn\n000:000:001\n01/01/2000
add song\nSong 4\ndasdasd\n00:01\ny\n00*00*01\n01/01/2000
add song\nSong 5\nasdasd 5\n00:01\nn\n00:00:01\n13/13/3000
add song\nSong 6\nArtist 6\n00:01\ny\n00:00:01\n11*11*2000

add playlist Playlist1
add playlist Playlist1

delete playlist Playlist1

select playlist Playlist1
show
clone
import

exit
"""
enable_colors = True

RED = "\033[91m"
GREEN = "\033[92m"
BLUE = "\033[94m"
AQUA = "\033[0;36m"
ENDC = "\033[0m"


def reader(stream):
    while True:
        c = stream.read(1)
        print(c, end="", flush=True)


def run(program, test_choice: int, speed: float):
    p = subprocess.Popen(program, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    t = threading.Thread(target=reader, args=[p.stdout], daemon=True)
    t.start()

    tests = ALL_TESTS.split("%%%")
    if test_choice < 0 or test_choice >= len(tests):
        print(f"Invalid test: f{test_choice}")
        exit(1)
    test = tests[test_choice]
    lines = [x for x in test.splitlines() if x.strip()]

    start = 0
    while start < len(lines):
        line = lines[start]
        if line.startswith('#'):
            print(BLUE + line + ENDC, flush=True)
            start += 1
        else:
            break

    time.sleep(5 * speed)
    for i in range(start, len(lines)):
        line = lines[i]
        print(GREEN + line + ENDC if enable_colors else line, flush=True)
        p.stdin.write(line + "\n")
        p.stdin.flush()
        time.sleep(speed)
    p.wait()


def main():
    args = sys.argv[1:]
    if 2 <= len(args) <= 3:
        program = args[0]
        test_choice = args[1]
        test_choice = int(test_choice[1:] if test_choice.startswith('t') else test_choice)
        speed = 0.1 if len(args) < 3 else (1 / (10 * float(args[2])))
        run(['./' + program], test_choice, speed)
        # loop.run_until_complete(run(['stdbuf', '-i0', ' -o0', '-e0', f'./{args[0]}']))
    else:
        print(f"Usage: python3 tester.py <executable> <test> [speed]")


if __name__ == '__main__':
    main()

"""
Notes:
Playlists won't contain whitespaces
"""