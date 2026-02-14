//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_DATE_H
#define TRANSAZIONIFINANZIARIE_DATE_H
#include <ctime>
#include <ostream>
#include <string>

//Defining the format for the date string
#define DATE_HOUR_FORMAT "%d/%m/%Y-%H:%M:%S"

/*
 * Class representing a Date using std library
 */

class Date {
public:
    //base constructor
    Date();

    //load from string constructor
    explicit Date(const std::string& date);

    //getters
    unsigned short getDay() const;
    unsigned short getMonth() const;
    unsigned short getYear() const;
    unsigned short getHours() const;
    unsigned short getMinutes() const;
    unsigned short getSeconds() const;

    [[nodiscard]] std::string toString() const;

    static bool isLeap(int year) ;

    static bool isValidDate(const std::tm& tm) ;

    friend bool operator==(const Date &lhs, const Date &rhs);

    friend bool operator!=(const Date &lhs, const Date &rhs);


private:
    std::tm date;
};


#endif //TRANSAZIONIFINANZIARIE_DATE_H