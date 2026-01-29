//
// Created by samuele on 1/14/26.
//

#include "CheckingAccount.h"

#include <sstream>
#include <utility>

CheckingAccount::CheckingAccount(const std::string &line, const std::string &identifier) {
    if (!CheckingAccount::loadFromString(line, identifier)) {
    }
    //TODO throw exception
}

CheckingAccount::CheckingAccount(const float balance, std::string  id, std::string  idUser) : balance(balance), id(std::move(id)), idUser(std::move(idUser)) {}

void CheckingAccount::changeBalance(const float change) {
    balance += change;
}

void CheckingAccount::transferAccountProperty(const std::string& newUser) {
    idUser = newUser;
}

std::string CheckingAccount::getAccountId() const {
    return id;
}

float CheckingAccount::getBalance() const {
    return balance;
}

std::string CheckingAccount::toString() const {
    return id+";"+idUser+";"+std::to_string(balance)+";";
}

void CheckingAccount::loadFromString(const std::string &line) {
    //Uses id for identify the user
    std::stringstream ss(line);
    std::string split;

    // Delimiter conform to toString() method
    constexpr char delimiter = ';';

    //only if found we proceed to cicle and load the obj
    short i = 0;
    while (getline(ss, split, delimiter)) {
        switch (i) {
            case 0: id = split; break;
            case 1: idUser = split; break;
            case 3: balance = std::stof(split); break;
                //space to add more
            default: ;//TODO throw exception
        }
        i++;
    }
}
