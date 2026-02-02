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

Transaction::Transaction(CheckingAccount &sender, CheckingAccount &receiver, const float amount,
    std::string comment,const std::string& id_transaction) :
    Transaction(sender.getAccountId(),receiver.getAccountId(),amount,std::move(comment),id_transaction){

    sender.subtractBalance(amount);
    receiver.addBalance(amount);
}

// in this case amount must be positive since it's a transaction between parts and the sender cannot send negative money
Transaction::Transaction(std::string id_sender_account, std::string id_receiver_account,
    const float amount, std::string comment,std::string id_transaction) :
    idSenderAccount(std::move(id_sender_account)),idReceiverAccount(std::move(id_receiver_account)),
    idTransaction(std::move(id_transaction)), amount(amount){
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be greater than 0");
    }
    // Maximum characters allowed in a comment //TODO test if correct
    this->comment.reserve(20);
    this->comment = std::move(comment);

    if (idTransaction.empty()) {
        idTransaction = IFileConfig::generateRandomString(16);
    }
    this->date = Date();
}

std::string Transaction::getIdSenderAccount() const{
    return idSenderAccount;
}

std::string Transaction::getIdReceiverAccount() const{
    return idReceiverAccount;
}

std::string Transaction::getIdTransaction() const{
    return idTransaction;
}

std::string Transaction::getComment() const{
    return comment;
}

float Transaction::getAmount() const {
    return amount;
}

void Transaction::setComment(const std::string &comment) {
    this->comment = comment;
}

std::string Transaction::toString() const {
    return idTransaction+";"+idSenderAccount+";"+idReceiverAccount+";"+std::to_string(amount)+";"+comment+";"+date.toString();
}

bool Transaction::loadFromString(const std::string &line) {
    try {
        IFileConfig::loadFromString(line,';');
        return true;
    }catch  (std::out_of_range &e) {
        return false;
    }
}


void Transaction::init(int index, const std::string &attribute) {
    switch (index) {
        case 0:
        case 1:
        default: throw std::out_of_range("Index out of range, no more initialization is possible.");
    }
}


