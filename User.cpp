//
// Created by samuele on 1/14/26.
//

#include "User.h"

#include <utility>

User::User(std::string  id) : id(std::move(id)){
}

std::string User::toString() const {
    return "";
}

bool User::loadFromFile(const std::string &line) const{
    return false;
}


