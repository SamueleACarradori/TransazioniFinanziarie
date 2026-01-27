//
// Created by samuele on 1/14/26.
//

#ifndef TRANSAZIONIFINANZIARIE_USER_H
#define TRANSAZIONIFINANZIARIE_USER_H
#include <vector>
#include "CheckingAccount.h"
#include "FileManager.h"
#include "IFileConfig.h"

/**
 * This class is designed to be initialized by file or by constructor in full.
 * Once initialized it cannot be modified due to security reasons.
 *
 */
class User : public IFileConfig {
public:
    User() = default;

    User(std::string id,std::string username, const std::vector<CheckingAccount>& accounts);


    //getters
    CheckingAccount getAccount(const std::string& idAccount);


    //setters

    void addAccount(const CheckingAccount& account);

    void addAccount(const FileManager& accountManager, const std::string& idAccount);

    bool deleteAccount(CheckingAccount account);

    bool withdraw(std::string idAccount);

    bool deposit(std::string idAccount);

    bool send(std::string idSender,std::string idReceiver);


    // Standard output for saving on .txt file
    std::string toString() const override;

    // Identifier is used as id of the user, so it searches only for the user id
    bool loadFromFile(const std::string &line, const std::string &identifier) override;

    ~User() override = default;


private:

    std::string id;
    std::string username;
    std::vector<CheckingAccount> accounts;
};


#endif //TRANSAZIONIFINANZIARIE_USER_H