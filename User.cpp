//
// Created by samuele on 1/14/26.
//

#include "User.h"

#include <random>
#include <sstream>
#include <utility>


User::User(const std::string &line, const std::string &idUser){
    //Specifying user class to force the compiler on using the redefined function
    if (!User::loadFromString(line, idUser)) {
    }
    //TODO throw exception
}

User::User(std::string username, std::string  id, const std::vector<CheckingAccount> &accounts) :
    id(std::move(id)),
    username(std::move(username)),
    accounts(accounts) {
    if (id.empty()) {
        this->id = IFileConfig::generateRandomString();
    }
}

User::User(const User &user) {
    User::init(&user);
}

CheckingAccount User::getAccount(const std::string& idAccount) {
    //find index
    const short i = findAccountIndexById(idAccount);
    return accounts[i];
}

void User::addAccount(const CheckingAccount& account) {
    accounts.push_back(account);
}

void User::addAccount(const std::string& line, const std::string &idAccount) {
    // purposefully letting the exception propagate since at this stage
    // it means that the function was called with improper values
    auto account = CheckingAccount(line,idAccount);
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

bool User::changeAccountBalance(const std::string& idAccount, const float amount) {
    bool success = true;
    //TODO catch multiple exceptions
    try {
        const short i = User::findAccountIndexById(idAccount);
        accounts[i].changeBalance(amount);
    }catch (std::exception &e) {
        success = false;
    }
    return success;
}


std::string User::toString() const {
    return id+";"+username+";";
}

void User::loadFromString(const std::string &line) {
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
            case 1: username = split; break;
                //space to add more
            default: ;//TODO throw exception
        }
        i++;
    }
}

void User::init(const IFileConfig* obj) {
    // dynamic cast the parent class to the child class
    const auto user = dynamic_cast<const User*>(obj);

    id = user->id;
    username = user->username;
    accounts = user->accounts;
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
        //TODO throw exception
    }
    return i;
}
