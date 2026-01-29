//
// Created by samuele on 1/16/26.
//

#include "Transaction.h"

#include <utility>


// Not catching the exception since the problem has to be resolved at
// the level of the caller of the constructor
Transaction::Transaction(const std::string &line) {
    Transaction::loadFromString(line);
}
// in this case amount must be positive since it's a transaction between parts and the sender cannot send negative money
Transaction::Transaction(std::string id_sender_account, std::string id_receiver_account,
    const float amount, std::string comment,std::string id_transaction) :
    idSenderAccount(std::move(id_sender_account)),idReceiverAccount(std::move(id_receiver_account)),
    idTransaction(std::move(id_transaction)), comment(std::move(comment)), amount(amount){
    if (amount <= 0) {
        //TODO throw exception
    }
    if (idTransaction.empty()) {
        idTransaction = IFileConfig::generateRandomString(16);
    }
}

std::string Transaction::getIdSenderAccount() {
    return idSenderAccount;
}

std::string Transaction::getIdReceiverAccount() {
    return idReceiverAccount;
}


