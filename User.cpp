//
// Created by samuele on 1/14/26.
//

#include "User.h"

#include <iostream>
#include <sstream>
#include <utility>


User::User(const std::string &line, const std::string &idUser){
    //Specifying user class to force the compiler on using the redefined function
    if (!User::loadFromString(line, idUser)) {
    }
    //TODO throw exception
}

User::User(const FileManager &userManager, const std::string &idUser) {
    auto user = User();
    if (!userManager.load(user,idUser)) {
        //TODO throw exception
    }

    // call copy constructor init for deep copy
    this->init(user);
}

User::User(std::string  id,std::string  username, const std::vector<CheckingAccount> &accounts) :
    id(std::move(id)),
    username(std::move(username)),
    accounts(accounts) {}

User::User(const User &user) {
    this->init(user);
}

CheckingAccount User::getAccount(const std::string& idAccount) {
    //find index
    const short i = findAccountIndexById(idAccount);
    return accounts[i];
}

void User::addAccount(const CheckingAccount& account) {
    accounts.push_back(account);
}

void User::addAccount(const FileManager& accountManager,const std::string &idAccount) {
    auto account = CheckingAccount(accountManager,idAccount);
    if (!accountManager.load(account,idAccount)) {
        //TODO throw exception
    }
    accounts.push_back(account);
}

bool User::deleteAccount(const CheckingAccount& account) {
    bool deleted = false;
    this->getAccount(account.getAccountId());

    return deleted;
}


std::string User::toString() const {
    return id+";"+username+";";
}

bool User::loadFromString(const std::string &line,const std::string &identifier){
    //Uses id for identify the user
    std::stringstream ss(line);
    std::string split;
    bool found = false;

    // Delimiter
    constexpr char del = ';';

    /*id should be in the first position of the string
     *there is no need to cicle it first
     *see toString() implemented method */
    if (getline(ss, split, del) && split == identifier) {
        //using split or identifier is the same
        id = split;
        found = true;
    }

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

void User::init(const User &user) {
    id = user.id;
    username = user.username;
    accounts = user.accounts;
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


