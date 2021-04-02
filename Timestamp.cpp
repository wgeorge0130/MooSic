#include "Timestamp.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
void Timestamp::init(struct tm *tm_time) {
    secs = (unsigned int) tm_time->tm_sec;
    mins = (unsigned int) tm_time->tm_min;
    hours = (unsigned int) tm_time->tm_hour;
    month = (unsigned int) tm_time->tm_mon + 1;
    day = (unsigned int) tm_time->tm_mday;
    year = (unsigned int) tm_time->tm_year + 1900;
}

Timestamp::Timestamp(const Timestamp& other) {
    // copy values of data members from other to the current timestamp object.
    // example:
    // 		secs = other.secs;
    year = other.year;
    month = other.month;
    day = other.day;
    hours = other.hours;
    mins = other.mins;
    secs = other.secs;
}

Timestamp::Timestamp() {
    now();
}

void Timestamp::now() {
    time_t rightnow = time(0);
    struct tm *tm_time = localtime(&rightnow);
    init(tm_time);
}

string Timestamp::toString() {
    stringstream stream;
    stream << setfill('0') << setw(4) << year << "/" << setfill('0') << setw(2) << month << "/" << setfill('0') << setw(2) << day << " " << setfill('0') << setw(2) << hours << ":" << setfill('0') << setw(2) << mins << ":" << setfill('0') << setw(2) << secs;
    return stream.str();
}