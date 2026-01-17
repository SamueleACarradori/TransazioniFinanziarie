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
    //TODO
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
    std::strftime(buffer.data(), buffer.size(), "%d-%m-%Y;%H:%M:%S;", &date);
    return buffer.data();
}
