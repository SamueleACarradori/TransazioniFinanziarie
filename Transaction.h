//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_TRANSACTION_H
#define TRANSAZIONIFINANZIARIE_TRANSACTION_H
#include <string>

#include "CheckingAccount.h"
#include "Date.h"
#include "IFileConfig.h"


class Transaction : public IFileConfig{
public:

    explicit Transaction(const std::string &line);

    Transaction(CheckingAccount& sender, CheckingAccount& receiver,
        float amount, std::string comment = "",const std::string& id_transaction="");

    //this constructor could be made protected in order to avoid a security gap of
    //phantom transaction never occurred inside the actual checking account
    Transaction(std::string id_sender_account, std::string id_receiver_account,
        float amount, std::string comment = "",std::string id_transaction="");

    //getters

    std::string getIdSenderAccount() const;

    std::string getIdReceiverAccount() const;

    std::string getIdTransaction() const;

    std::string getComment() const;

    float getAmount() const;


    //setters

    void setComment(const std::string &comment);

    /* No setter for amount since the amount is supposed to be set
     * once at constructor, and then no more.
     * If users, what to change the amount they have to delete the transaction with the
     * wrong amount and generate a new one with the correct amount
    */

    // Override methods

    [[nodiscard]] std::string toString() const override;

    bool loadFromString(const std::string &line) override;

protected:

    void init(int index,const std::string& attribute) override;

private:
    std::string idSenderAccount;
    std::string idReceiverAccount;
    // standard length is 16 since there are far more transactions than anything else
    std::string idTransaction;
    std::string comment;
    float amount;
    Date date;
};


#endif //TRANSAZIONIFINANZIARIE_TRANSACTION_H