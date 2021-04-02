#include "SongChecker.h"

SongChecker::SongChecker() {}

bool SongChecker::isDuration(string duration) {
    bool isError = false;
    if (duration.length() != 5 || duration.at(2) != ':') {
        isError = true;
    }
    try {
        if (stoi(duration.substr(3, 5)) >= 60 || stoi(duration.substr(0, 2)) >= 60) {
            isError = true;
        }
    }
    catch (invalid_argument const &e) { isError = true; }
    if (isError) {
        cout << "Your duration is wrong format" << endl;
        return false;
    } else {
        return true;
    }
}

bool SongChecker::validExplicit(string isExplicit) { //checks if isExplicit is in valid format
    if (isExplicit != "y" && isExplicit != "n") {
        //cout << "Your explicit is wrong format" << endl;
        return false;
    } else {
        return true;
    }
}

bool SongChecker::checkExplicit(string isExplicit) { //checks whether or not song is explicit
    if (isExplicit == "y") { return true; }
    else {
        return false;
    }
}

bool SongChecker::isTimeAdded(string timeAdded) {
    bool isError = false;
    if (timeAdded.length() != 8 || timeAdded.at(2) != ':' || timeAdded.at(5) != ':') {
        isError = true;
        cout << timeAdded.length() << timeAdded.substr(2, 3) << timeAdded.substr(5, 6) << endl;
    }
    try {
        if (stoi(timeAdded.substr(6, 8)) >= 60 || stoi(timeAdded.substr(3, 5)) >= 60 || stoi(timeAdded.substr(0, 2)) >= 25) {
            isError = true;
        }
    }
    catch (invalid_argument const &e) {
        isError = true;
    }
    if (isError) {
        cout << "Your time wrong format" << endl;
        return false;
    } else {
        return true;
    }
}

bool SongChecker::isDateAdded(string dateAdded) {
    bool isError = false;
    if (dateAdded.length() != 10 || dateAdded.at(2) != '/' || dateAdded.at(5) != '/') {
        isError = true;
    }
    try {
        if ( stoi(dateAdded.substr(6,10)) <= 0 || stoi(dateAdded.substr(0,2)) >= 13 || stoi(dateAdded.substr(3,5)) >= 33) {
            isError = true;
        }
    }
    catch (invalid_argument const &e) {
        isError = true;
    }
    if (isError) { cout << "Your date is wrong format" << endl;
        return false;
    } else {
        return true;
    }
}
