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

CheckingAccount::CheckingAccount(const float balance, std::string  idUser,std::string  id) : balance(balance), id(std::move(id)), idUser(std::move(idUser)) {
    if (id.empty()) {
        this->id = IFileConfig::generateRandomString();
    }
}

void CheckingAccount::addBalance(const float change) {
    if (change <= 0)
        throw std::invalid_argument("Amount must be greater than 0");
    balance += change;
}

void CheckingAccount::subtractBalance(const float change) {
    if (change <= 0)
        throw std::invalid_argument("Amount must be greater than 0");
    balance -= change;
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

bool CheckingAccount::loadFromString(const std::string &line) {
    try {
        IFileConfig::loadFromString(line,';');
        return true;
    }catch  (std::out_of_range &e) {
        return false;
    }
}

void CheckingAccount::init(const int index, const std::string &attribute) {
    switch (index) {
        case 0: id = attribute; break;
        case 1: idUser = attribute; break;
        case 3: balance = std::stof(attribute); break;
            //space to add more
        default: throw std::out_of_range("Index out of range, no more initialization is possible.") ;
    }
}
