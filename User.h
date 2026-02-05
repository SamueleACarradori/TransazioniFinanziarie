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
 */
class User : public IFileConfig {
public:
    //Default constructor used to create empty obj for loading purposes
    User() = default;


    // Constructor by value
    explicit User(std::string username, std::string id = "",const std::vector<CheckingAccount> &accounts = {});


    // getters
    std::string getUsername() const;

    std::string getId() const;

    std::vector<CheckingAccount> getAccount();

    CheckingAccount getAccount(const std::string& idAccount);

    //generate account on the spot giving the initial balance
    void addAccount(float balance);

    //add account checking if already exists
    void addAccount(const CheckingAccount& account);

    // load account from string ad uses addAccount(account) for checking id already exists
    void addAccount(const std::string& line, const std::string &idAccount);

    //add account balance
    bool addAccountBalance(const std::string& idAccount, float amount);

    bool subtractAccountBalance(const std::string &idAccount, float amount);

    //delete account
    bool deleteAccount(const std::string& idAccount);

    bool deleteAccount(const CheckingAccount& account);


    // Standard output for saving on .txt file
    std::string toString() const override;

    // Standard input method for loading .txt file
    bool loadFromString(const std::string &line) override;

    //void loadFromString(const std::string &line, const char delimiter) override;

    ~User() override = default;

protected:
    // Constructor only used to initialize obj inside
    // the other constructors and hidden for user use.
    //User() = default;

    // Method created for complying with the 'request' for some constructors for a deep copy
    //void init(const IFileConfig* obj) override;

    //initialize object during string loading
    void init(int index, const std::string& attribute) override;

    // Return the index of the correspondent Account
    short findAccountIndexById(const std::string& idAccount) const;

private:

    std::string id;
    std::string username;
    std::vector<CheckingAccount> accounts;
};


#endif //TRANSAZIONIFINANZIARIE_USER_H