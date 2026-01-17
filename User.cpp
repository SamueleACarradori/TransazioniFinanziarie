//
// Created by samuele on 1/14/26.
//

#include "User.h"

User::User(std::string username) {
}

User::User(std::string id, std::string username, std::vector<CheckingAccount> accounts) {
}

bool User::addAccount(CheckingAccount account) {
}

bool User::deleteAccount(CheckingAccount account) {
}

bool User::withdraw(std::string idAccount) {
}

bool User::deposit(std::string idAccount) {
}

bool User::send(std::string idSender, std::string idReceiver) {
}

CheckingAccount User::getAccount(std::string idAccount) {
}
