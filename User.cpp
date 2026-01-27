//
// Created by samuele on 1/14/26.
//

#include "User.h"

#include <iostream>
#include <sstream>
#include <utility>

User::User(std::string  id) : id(std::move(id)){}

std::string User::toString() const {
    return id+";"+username+";";
}

bool User::loadFromFile(const std::string &line){
    //Uses id for identify the user
    std::stringstream ss(line);
    std::string split;
    bool found = false;

    // Delimiter
    constexpr char del = ';';

    /*id should be in the first position of the string
     *there is no need to cicle it first
     *see toString() implemented method */
    getline(ss, split, del);
    if (split == id)
        found = true;

    //only if found we proceed to cicle and load the obj
    short i = 0;
    while (getline(ss, split, del) && found) {
       switch (i) {
           case 0: username = split; break;
               //space to add more
       }
        i++;
    }
    //TODO load CheckingAccount
    return found;
}


