//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_DATE_H
#define TRANSAZIONIFINANZIARIE_DATE_H
#include <ctime>
#include <string>

//Defining the format for the date string
#define DATE_HOUR_FORMAT "%d/%m/%Y-%H:%M:%S"

/*
 * Class representing a Date using std library
 */

class Date {
public:
    Date();
    explicit Date(const std::string& date);

    //getters
    unsigned short getDay() const;
    unsigned short getMonth() const;
    unsigned short getYear() const;
    unsigned short getHours() const;
    unsigned short getMinutes() const;
    unsigned short getSeconds() const;

    //format: day/month/year-hour:minute:second
    std::string toString() const;

    bool isLeapYear() const;

private:
    std::tm date;
};


#endif //TRANSAZIONIFINANZIARIE_DATE_H