//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_DATE_H
#define TRANSAZIONIFINANZIARIE_DATE_H
#include <ctime>
#include <string>

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

    std::string toString() const;

private:
    std::tm date;
};


#endif //TRANSAZIONIFINANZIARIE_DATE_H