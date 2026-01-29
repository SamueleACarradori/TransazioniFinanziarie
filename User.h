//
// Created by samuele on 1/14/26.
//

#ifndef TRANSAZIONIFINANZIARIE_USER_H
#define TRANSAZIONIFINANZIARIE_USER_H

#include <vector>
#include "CheckingAccount.h"
#include "IFileConfig.h"

/**
 * This class is designed to be initialized by file or by constructor in full.
 * Once initialized it cannot be modified due to security reasons.
 *
 */
class User : public IFileConfig {
public:
    //Constructor by string
    User(const std::string &line, const std::string &idUser);

    // Constructor by value
    explicit User(std::string username, std::string id = "",const std::vector<CheckingAccount> &accounts = {});

    // Copy Constructor
    User(const User &user);


    // getters
    CheckingAccount getAccount(const std::string& idAccount);


    // setters
    void addAccount(const CheckingAccount& account);

    // add account searching in the filesystem
    void addAccount(const std::string& line, const std::string &idAccount);

    bool deleteAccount(const std::string& idAccount);

    bool deleteAccount(const CheckingAccount& account);

    bool changeAccountBalance(const std::string& idAccount, float amount);


    // Standard output for saving on .txt file
    std::string toString() const override;

    // Standard input method for loading .txt file
    void loadFromString(const std::string &line) override;

    //void loadFromString(const std::string &line) override;

    ~User() override = default;

protected:
    // Constructor only used to initialize obj inside
    // the other constructors and hidden for user use.
    User() = default;

    // Method created for complying with the 'request' for some constructors for a deep copy
    void init(const IFileConfig* obj) override;

    // Return the index of the correspondent Account
    short findAccountIndexById(const std::string& idAccount) const;

private:

    std::string id;
    std::string username;
    std::vector<CheckingAccount> accounts;
};


#endif //TRANSAZIONIFINANZIARIE_USER_H