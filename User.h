//
// Created by samuele on 1/14/26.
//

#ifndef TRANSAZIONIFINANZIARIE_USER_H
#define TRANSAZIONIFINANZIARIE_USER_H
#include <vector>
#include "CheckingAccount.h"
#include "IFileConfig.h"


class User : public IFileConfig {
public:
    explicit User(std::string id);

    User(std::string  id,std::string  username, std::vector<CheckingAccount>& accounts);


    //getters
    CheckingAccount getAccount(std::string idAccount);


    //setters
    void setUsername(std::string username);


    bool addAccount(CheckingAccount account);

    bool deleteAccount(CheckingAccount account);

    bool withdraw(std::string idAccount);

    bool deposit(std::string idAccount);

    bool send(std::string idSender,std::string idReceiver);


    //Override methods
    std::string toString() const override;

    bool loadFromFile(const std::string &line) override;

    ~User() override = default;


private:

    std::string id;
    std::string username;
    std::vector<CheckingAccount> accounts;
};


#endif //TRANSAZIONIFINANZIARIE_USER_H