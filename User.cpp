//
// Created by samuele on 1/14/26.
//

#include "User.h"

#include <random>
#include <utility>

#include "exceptions/account_dont_exists_error.h"


User::User(std::string username, std::string  id, const std::vector<CheckingAccount> &accounts) :
    id(std::move(id)),
    username(std::move(username)),
    accounts(accounts) {
    if (this->id.empty()) {
        this->id = IFileConfig::generateRandomString();
    }else if(this->id.length() != STANDARD_ID_LENGTH) {
        throw std::invalid_argument("Invalid ID length");
    }
}

std::string User::getUsername() const {
    return username;
}

std::string User::getId() const {
    return id;
}

std::vector<CheckingAccount> User::getAccount() {
    return accounts;
}


CheckingAccount User::getAccount(const std::string& idAccount) {
    //find index
    const short i = findAccountIndexById(idAccount);
    return accounts[i];
}

void User::addAccount(const float balance) {
    User::addAccount(CheckingAccount(balance,id));
}

void User::addAccount(const CheckingAccount& account) {
    accounts.push_back(account);
}

void User::addAccount(const std::string& line, const std::string &idAccount) {
    // purposefully letting the exception propagate since at this stage
    // it means that the function was called with improper values
    auto account = CheckingAccount(line);
    User::addAccount(account);
}

bool User::deleteAccount(const std::string &idAccount) {
    bool deleted = true;
    try {
        const short i = User::findAccountIndexById(idAccount);
        accounts.erase(accounts.begin()+i);
        //TODO verify if this is correct
    }catch (std::exception &e) {
        deleted = false;
    }
    return deleted;
}

bool User::deleteAccount(const CheckingAccount& account) {
    return deleteAccount(account.getAccountId());
}

bool User::addAccountBalance(const std::string &idAccount, float amount) {
    bool success = true;
    try {
        const short i = User::findAccountIndexById(idAccount);
        accounts[i].addBalance(amount);
    }catch (account_dont_exists_error &e) {
        success = false;
    }catch (std::invalid_argument &e) {
        success = false;
    }
    return success;
}

bool User::subtractAccountBalance(const std::string& idAccount, const float amount) {
    bool success = true;
    try {
        const short i = User::findAccountIndexById(idAccount);
        accounts[i].subtractBalance(amount);
    }catch (account_dont_exists_error &e) {
        success = false;
    }catch (std::invalid_argument &e) {
        success = false;
    }
    return success;
}


std::string User::toString() const {
    return id+";"+username+";";
}

bool User::loadFromString(const std::string &line) {
    try {
        IFileConfig::loadFromString(line,';');
        return true;
    }catch  (std::out_of_range &e) {
        return false;
    }
}

/*
void User::init(const IFileConfig* obj) {
    // dynamic cast the parent class to the child class
    const auto user = dynamic_cast<const User*>(obj);

    id = user->id;
    username = user->username;
    accounts = user->accounts;
}
*/

void User::init(const int index, const std::string& attribute) {
    switch (index) {
        case 0: id = attribute; break;
        case 1: username = attribute; break;

        default: throw std::out_of_range("Index out of range, no more initialization is possible.");
    }
}

short User::findAccountIndexById(const std::string &idAccount) const {
    //vector index
    short i = 0;

    //putting a bool variable to make it more readable
    bool found = false;

    //find the index inside the vector
    while (!found && i < accounts.size()) {
        if (accounts[i].getAccountId() == idAccount)
            found = true;
        else
            i++;
    }

    if (!found) {
        throw account_dont_exists_error();
    }
    return i;
}
