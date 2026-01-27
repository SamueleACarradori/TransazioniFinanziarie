//
// Created by samuele on 1/14/26.
//

#include "User.h"

#include <iostream>
#include <sstream>
#include <utility>


User::User(std::string  id, std::string  username, const std::vector<CheckingAccount> &accounts) :
    id(std::move(id)),
    username(std::move(username)),
    accounts(accounts){}

CheckingAccount User::getAccount(const std::string& idAccount) {
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

    return accounts[i];
}

void User::addAccount(const CheckingAccount& account) {
    accounts.push_back(account);
}

void User::addAccount(const FileManager& accountManager,const std::string &idAccount) {
    auto account = CheckingAccount();
    if (!accountManager.load(account,idAccount)) {
        //TODO throw exception
    }
    accounts.push_back(account);
}


std::string User::toString() const {
    return id+";"+username+";";
}

bool User::loadFromFile(const std::string &line,const std::string &identifier){
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
    if (split == identifier) {
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


