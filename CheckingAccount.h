//
// Created by samuele on 1/14/26.
//

#ifndef TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H
#define TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H
#include <string>

#include "FileManager.h"
#include "IFileConfig.h"

/**
 * This class could be restructured to be a child of a parent class called "Account"
 * that defines all types of accounts in the banking system (Savings, bonds etc...).
 * For the purposes of this exercise, we will not do such thing,
 * although we acknowledge that in a more complete application
 * it should be the practice to be implemented.
 *
 * Also, this class is not designed for co-signed accounts :)
 */

class CheckingAccount : public IFileConfig{
public:
    //Default constructor used to create empty obj for loading purposes
    CheckingAccount() = default;

    //Constructor by string
    explicit CheckingAccount(const std::string &line);

    //Construct by values, balance < 0 is ok since exists accounts in debt or 'in red'
    CheckingAccount(float balance,std::string  idUser,std::string  id="");

    void addBalance(float change);

    void subtractBalance(float change);

    // I don't know what kind of control I could do here since there is no password nor authentication system
    void transferAccountProperty(const std::string& newUser);

    //getters
    [[nodiscard]] std::string getAccountId() const;

    [[nodiscard]] float getBalance() const;


    // Standard output for saving on .txt file
    [[nodiscard]] std::string toString() const override;

    // Standard input for loading on .txt file
    bool loadFromString(const std::string &line) override;


    ~CheckingAccount() override = default;


    friend bool operator==(const CheckingAccount &lhs, const CheckingAccount &rhs);

    friend bool operator!=(const CheckingAccount &lhs, const CheckingAccount &rhs);

protected:

    void init(int index,const std::string& attribute) override;

private:
    float balance = 0;
    std::string id;
    std::string idUser;
};


#endif //TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H