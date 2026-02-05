//
// Created by samuele on 1/14/26.
//

#include "CheckingAccount.h"

#include <sstream>
#include <utility>

//Resending the exception to the caller
CheckingAccount::CheckingAccount(const std::string &line) {
    //if loadFromString() fails at constructor throws an exception simply stating that there is an error in the input
    if (!CheckingAccount::loadFromString(line))
        throw std::invalid_argument("CheckingAccount::loadFromString() failed");
}

CheckingAccount::CheckingAccount(const float balance, std::string  idUser,std::string  id) : balance(balance), id(std::move(id)), idUser(std::move(idUser)) {
    if (this->id.empty()) {
        this->id = IFileConfig::generateRandomString();
    }else if(this->id.length() != STANDARD_ID_LENGTH) {
        throw std::invalid_argument("Invalid ID length");
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
    }catch (std::invalid_argument &e) {
        return false;
    }
}

void CheckingAccount::init(const int index, const std::string &attribute) {
    switch (index) {
        case 0: id = attribute; break;
        case 1: idUser = attribute; break;
        case 2: balance = std::stof(attribute); break;
            //space to add more
        default: throw std::out_of_range("Index out of range, no more initialization is possible.") ;
    }
}

bool operator==(const CheckingAccount &lhs, const CheckingAccount &rhs) {
    return lhs.id == rhs.id
               && lhs.idUser == rhs.idUser;
}

bool operator!=(const CheckingAccount &lhs, const CheckingAccount &rhs) {
    return !(lhs == rhs);
}
