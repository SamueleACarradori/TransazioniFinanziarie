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
        this->id = User::generateRandomString();
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

std::string User::generateRandomString(const int length, const bool specialChar) {
    std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    if (specialChar)
        characters = characters + "!@#$%^&*-+";

    // Generating true random using entropy on the system. Could be slow and expensive so we made it static
    static std::random_device random_device;

    /*
     * Mersenne Twister pseudo-random number generator, 19937 = period length (2¹⁹⁹³⁷ - 1)
     * We seed it with a true random number to get a more pure-random-like result
     */
    std::mt19937 generator(random_device());

    // Produces random integers uniformly distributed across a range
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    // Generating the actual string
    std::string random_string;
    random_string.reserve(length); //optimization pre allocating

    /**
     * distribution(generator) generates a random index (int type)
     * Then we select from the characters the one with the correspondent index
     * and we put it inside result string
    */
    for (size_t i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}


