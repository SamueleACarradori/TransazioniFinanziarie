//
// Created by samuele on 1/14/26.
//

#ifndef TRANSAZIONIFINANZIARIE_USER_H
#define TRANSAZIONIFINANZIARIE_USER_H
#include <string>
#include <vector>
#include "CheckingAccount.h"


class User {
public:
    explicit User(std::string username);
    User(std::string id,std::string username,std::vector<CheckingAccount> accounts);

    //getters
    CheckingAccount getAccount(std::string idAccount);

    //setters
    void setUsername(std::string username);

    bool addAccount(CheckingAccount account);
    bool deleteAccount(CheckingAccount account);
    bool withdraw(std::string idAccount);
    bool deposit(std::string idAccount);
    bool send(std::string idSender,std::string idReceiver);

private:
    std::string id;
    std::string username;
    std::vector<CheckingAccount> accounts;
};


#endif //TRANSAZIONIFINANZIARIE_USER_H