//
// Created by samuele on 1/14/26.
//

#include "User.h"

#include <random>
#include <utility>

#include "exceptions/account_already_exists_error.h"
#include "exceptions/account_dont_exists_error.h"


User::User(std::string username, std::string  id, const std::vector<CheckingAccount> &accounts) :
    id(std::move(id)),
    username(std::move(username)),
    accounts(accounts) {

    //checks if id was left empty and populates it
    //else look for irregularities
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

std::vector<CheckingAccount> User::getAccounts() {
    return accounts;
}


CheckingAccount User::getAccount(const std::string& idAccount) {
    //find index
    const short i = findAccountIndexById(idAccount);
    return accounts[i];
}

//does not look if there is already one because if created
//only by balance means id (and eventually other attributes) are generated
//on the spot by the constructor
void User::addAccount(const float balance) {
    User::addAccount(CheckingAccount(balance,id));
}

//I have made my personal exceptions because why not :)
void User::addAccount(const CheckingAccount& account) {
    //checks if account belongs to user
    if (account.getUserId() != id)
        throw std::invalid_argument("Account does not match user ID.");

    //checks if already present
    for(CheckingAccount& currentAccount: accounts) {
        if (currentAccount == account)
            throw account_already_exists_error();
    }

    accounts.push_back(account);
}

void User::addAccount(const std::string& line, const std::string &idAccount) {
    // purposefully letting the exception propagate since at this stage
    // it means that the function was called with improper values
    const auto account = CheckingAccount(line);
    User::addAccount(account);
}

bool User::deleteAccount(const std::string &idAccount) {
    bool deleted = true;
    try {
        //if not found sends exception
        const short index = User::findAccountIndexById(idAccount);
        // being iterator, I'm adding the index
        accounts.erase(accounts.begin()+index);
    }catch (account_dont_exists_error &e) {
        deleted = false;
    }
    return deleted;
}

bool User::deleteAccount(const CheckingAccount& account) {
    return deleteAccount(account.getAccountId());
}

bool User::addAccountBalance(const std::string &idAccount, const float amount) {
    bool success = true;
    try {
        //if not found sends exception
        const short i = User::findAccountIndexById(idAccount);
        //also if amount is not correct send another exception
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
        //if not found sends exception
        const short i = User::findAccountIndexById(idAccount);
        //also if amount is not correct send another exception
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
        //sends this error when init function fails to initialize all
        return false;
    }catch (std::invalid_argument &e) {
        //sends this exception when id length is not correct
        return false;
    }
}

bool User::isEqual(const IFileConfig &obj) const {
    const auto user = dynamic_cast<const User&>(obj);

    //IDs could be equal since random function assigning ids is not perfect but
    //for the purpose of this exercise we leave it at that
    return id == user.getId() && username == user.getUsername();
}

bool User::isEqual(const std::string &line) const {
    User user;
    if (!user.loadFromString(line))
        throw  std::invalid_argument("Invalid input for user: ' "+line+" '");

    return this->isEqual(user);
}

void User::init(const int index, const std::string& attribute) {
    switch (index) {
        case 0:
            if (attribute.empty() || attribute.length() != STANDARD_ID_LENGTH)
                throw std::invalid_argument("Invalid ID length");
            id = attribute;
            break;
        case 1: username = attribute; break;

        //default triggers an error since the format of the saving files is standardized
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
