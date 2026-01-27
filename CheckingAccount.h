//
// Created by samuele on 1/14/26.
//

#ifndef TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H
#define TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H
#include <string>

#include "IFileConfig.h"

/**
 * This class could be restructured to be a child of a parent class called "Account"
 * that defines all types of accounts in the banking system (Savings, bonds etc...).
 * For the purposes of this exercise, we will not do such thing,
 * although we acknowledge that in a more complete application
 * it should be the practice to be implemented.
 */

class CheckingAccount : public IFileConfig{
public:
    CheckingAccount() = default;

    CheckingAccount(float balance,std::string id,std::string idUser);


    void addBalance(float add);

    void subtractBalance(float subtract);

    //setters
    void setIdUser(std::string idUser);

    //getters
    std::string getAccountId();

    float getBalance();


    // Standard output for saving on .txt file
    std::string toString() const override;

    // Identifier is used as id of the account, so it searches only for the account id
    bool loadFromFile(const std::string &line, const std::string &identifier) override;

    ~CheckingAccount() override = default;

private:
    float balance = 0;
    std::string id;
    std::string idUser;
};


#endif //TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H