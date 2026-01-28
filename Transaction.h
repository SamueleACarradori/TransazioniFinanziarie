//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_TRANSACTION_H
#define TRANSAZIONIFINANZIARIE_TRANSACTION_H
#include <string>


class Transaction {
public:
    Transaction(const std::string &line);
    Transaction(User , const std::string &id_receiver_account,
        const std::string &id_transaction, float amount);

    Transaction(const std::string &id_sender_account, const std::string &id_receiver_account,
        const std::string &id_transaction, float amount, const std::string &comment = "");


    //getters
    std::string getIdSenderAccount();

    std::string getIdReceiverAccount();

    std::string getIdTransaction();

    std::string getComment();

    float getAmount();


    //setters
    void setComment(const std::string &comment);

    void setAmount(float amount);

private:
    std::string idSenderAccount;
    std::string idReceiverAccount;
    std::string idTransaction;
    std::string comment;
    float amount;
};


#endif //TRANSAZIONIFINANZIARIE_TRANSACTION_H