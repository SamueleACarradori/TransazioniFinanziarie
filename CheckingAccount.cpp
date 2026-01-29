//
// Created by samuele on 1/14/26.
//

#include "CheckingAccount.h"

#include <sstream>
#include <utility>

// Not catching the exception since the problem has to be resolved at
// the level of the caller of the constructor
CheckingAccount::CheckingAccount(const std::string &line) {
    CheckingAccount::loadFromString(line);
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
    IFileConfig::loadFromString(line,';');
}

void CheckingAccount::init(int index, const std::string &attribute) {
    switch (index) {
        case 0: id = attribute; break;
        case 1: idUser = attribute; break;
        case 3: balance = std::stof(attribute); break;
            //space to add more
        default: ;//TODO throw exception
    }
}
