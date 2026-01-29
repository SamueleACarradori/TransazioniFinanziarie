//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_TRANSACTION_H
#define TRANSAZIONIFINANZIARIE_TRANSACTION_H
#include <string>

#include "IFileConfig.h"


class Transaction : public IFileConfig{
public:

    explicit Transaction(const std::string &line);

    Transaction(std::string id_sender_account, std::string id_receiver_account,
         float amount, std::string comment = "",std::string id_transaction="");

    //getters

    std::string getIdSenderAccount();

    std::string getIdReceiverAccount();

    std::string getIdTransaction();

    std::string getComment();

    float getAmount();


    //setters

    void setComment(const std::string &comment);

    void setAmount(float amount);


    // Override methods

    std::string toString() const override;

    void loadFromString(const std::string &line) override;

private:
    std::string idSenderAccount;
    std::string idReceiverAccount;
    std::string idTransaction;
    std::string comment;
    float amount;
};


#endif //TRANSAZIONIFINANZIARIE_TRANSACTION_H