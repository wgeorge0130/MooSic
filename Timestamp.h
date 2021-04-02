
#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <string>

class Timestamp {
public:
    Timestamp();
    Timestamp(const Timestamp& other);
    void init(struct tm*);
    // print timestamp in yyyy/mm/dd hh:mm:ss format.
    std::string toString();
private:
    void now();
    int secs;
    int mins;
    int hours;
    int day;
    int month;
    int year;
    // data members for secs, mins, hours, day, month and year.
};

#endif
