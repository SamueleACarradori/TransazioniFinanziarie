//
// Created by samuele on 1/16/26.
//

#include "Transaction.h"

Transaction::Transaction(const std::string &id_sender_account, const std::string &id_receiver_account,
    const std::string &id_transaction, float amount) {
}

Transaction::Transaction(const std::string &id_sender_account, const std::string &id_receiver_account,
    const std::string &id_transaction, const std::string &comment, float amount) {
}

std::string Transaction::getIdSenderAccount() {
}

std::string Transaction::getIdReceiverAccount() {
}

std::string Transaction::getIdTransaction() {
}

std::string Transaction::getComment() {
}

float Transaction::getAmount() {
}

void Transaction::setComment(const std::string &comment) {
}

void Transaction::setAmount(float amount) {
}
