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
    date = *std::localtime(&now_time_t);
}

Date::Date(const std::string& date) {

    // Initialize a tm structure to hold the parsed date
    std::tm tm = {};

    // Create a string stream to parse the date string
    std::istringstream ss(date);

    // Even if this piece of code gives error
    // it works, I don't know if it is my IDE the problem
    ss >> std::get_time(&tm, DATE_HOUR_FORMAT);


    // Check if parsing was successful
    if (ss.fail()) {
        throw std::invalid_argument("Invalid date");
    }

    // Convert the parsed date to a time_t value
    this->date = tm;
}

unsigned short Date::getDay() const {
    return date.tm_wday;
}

unsigned short Date::getMonth() const {
    return date.tm_mon;
}

unsigned short Date::getYear() const {
    return date.tm_year;
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
    std::array<char, 80> buffer;
    std::strftime(buffer.data(), buffer.size(), DATE_HOUR_FORMAT, &date);
    return buffer.data();
}
