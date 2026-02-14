//
// Created by samuele on 1/16/26.
//

#include "Date.h"

#include <array>
#include <chrono>
#include <iostream>


Date::Date() {
    // Get current time as a time_point (system_clock)
    auto now = std::chrono::system_clock::now();

    // Convert to time_t (for compatibility with ctime)
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert to tm struct (local time)
    this->date = *std::localtime(&now_time_t);
}

Date::Date(const std::string& date) {

    // Initialize a tm structure to hold the parsed date
    std::tm tm = {};

    // Create a string stream to parse the date string
    std::istringstream ss(date);

    // !!!ATTENTION!!!
    // Even if this piece of code gives error
    // it works, I don't know if it is my IDE the problem
    // >> operator should extract formatted data
    ss >> std::get_time(&tm, DATE_HOUR_FORMAT);

    //If the std::tm object was obtained from std::get_time or the POSIX strptime,
    //the value of tm_isdst is indeterminate, and needs to be set explicitly before calling mktime.
    tm.tm_isdst = 0; // Not daylight saving

    // !!!THE ORDER IS VERY IMPORTANT IN THIS CALL !!!
    // also check if parsing was successful and if date is actually ok
    if (ss.fail() || !Date::isValidDate(tm) || std::mktime(&tm) == -1 ) {
        throw std::invalid_argument("Invalid date '" + date + "'");
    }

    // Convert the parsed date to a time_t value
    this->date = tm;

}

unsigned short Date::getDay() const {
    return date.tm_wday;
}

unsigned short Date::getMonth() const {
    return date.tm_mon + 1;
}

unsigned short Date::getYear() const {
    return date.tm_year + 1900;
}

unsigned short Date::getHours() const {
    return date.tm_hour;
}

unsigned short Date::getMinutes() const {
    return date.tm_min;
}

unsigned short Date::getSeconds() const {
    return date.tm_sec;
}

std::string Date::toString() const {
    std::array<char, 80> buffer{};
    std::strftime(buffer.data(), buffer.size(), DATE_HOUR_FORMAT, &date);
    return buffer.data();
}

bool Date::isLeap(const int year) {
    // Return true if year is a multiple of 4 and not multiple of 100
    // OR year is multiple of 400.
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
             (year % 400 == 0));
}

bool Date::isValidDate(const std::tm &tm) {
    // For comodity and readability
    const int year = 1900 + tm.tm_year;
    const int month = 1 + tm.tm_mon;

    // If year month and day are not in given range
    if (year < 2000 || month < 1 || month > 12 ||
        tm.tm_mday < 1 || tm.tm_mday > 31)
        return false;

    //if hour minute seconds are not in given range
    if (tm.tm_hour < 0 || tm.tm_hour > 23 ||
        tm.tm_min < 0 || tm.tm_min > 59 ||
        tm.tm_sec < 0 || tm.tm_sec > 59)
        return false;

    // Handle February month with leap year
    if (month == 2){
        if (isLeap(year))
            return (tm.tm_mday <= 29);
        //else check 28
        return (tm.tm_mday <= 28);
    }

    // Months of April, June, September and November
    // must have number of days less than or equal to 30.
    if (month == 4 || month == 6 ||
        month == 9 || month == 11)
        return (tm.tm_mday <= 30);

    return true;
}

bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.getYear() == rhs.getYear() && lhs.getMonth() == rhs.getMonth()
        && lhs.getDay() == rhs.getDay() && lhs.getHours() == rhs.getHours()
        &&  lhs.getMinutes() == rhs.getMinutes() &&  lhs.getSeconds() == rhs.getSeconds();
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return !(lhs == rhs);
}
