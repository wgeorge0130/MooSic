#ifndef CA2_SONGCHECKER_H
#define CA2_SONGCHECKER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Library.h"

using namespace std;

class SongChecker {
public:
    SongChecker();
    bool validExplicit(string);
    bool checkExplicit(string);
    bool isDuration(string);
    bool isTimeAdded(string);
    bool isDateAdded(string);
private:

};
#endif //CA2_SONGCHECKER_H
