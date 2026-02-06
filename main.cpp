//
// Created by samuele on 2/2/26.
//


#include <filesystem>
#include <fstream>
#include <iostream>
#include "Transaction.h"
#include "User.h"

void deleteAllFiles() {
    auto userFile = FileManager("user.txt");
    auto checkingFile = FileManager("checking.txt");
    auto transactionFile = FileManager("transaction.txt");

    userFile.deleteFile();
    checkingFile.deleteFile();
    transactionFile.deleteFile();
}

int main () {
    deleteAllFiles();
    //Initialize user
    auto pippo = User("Pippo","provaID0");
    auto franco = User("Franco");

    //Initialize accounts
    pippo.addAccount(20.23);
    pippo.addAccount(240.23);
    franco.addAccount(11290.23);

    //try transactions
    auto transaction1 = Transaction(pippo.getAccount()[0],franco.getAccount()[0],20,"Prova 1");
    auto transaction2 = Transaction(pippo.getAccount()[1],franco.getAccount()[0],123.49,"Prova 2");
    auto transaction3 = Transaction(franco.getAccount()[0],pippo.getAccount()[0],5367.93,"Prova 3");

    //try FileManger
    auto userFile = FileManager("user.txt");
    auto checkingFile = FileManager("checking.txt");
    auto transactionFile = FileManager("transaction.txt");

    // try saving all
    userFile.save(pippo);
    userFile.save(franco);

    for (CheckingAccount &i : pippo.getAccount()) {
        checkingFile.save(i);
    }
    for (CheckingAccount &i : franco.getAccount()) {
        checkingFile.save(i);
    }

    transactionFile.save(transaction1);
    transactionFile.save(transaction2);
    transactionFile.save(transaction3);

    // try loading
    User user;
    bool attr = userFile.load(user,"provaID");
    CheckingAccount checking;
    attr = checkingFile.load(checking,pippo.getAccount()[0].getAccountId());
    Transaction transaction;
    attr = transactionFile.load(transaction,transaction1.getIdTransaction());

    std::cout << user.toString() << std::endl;
    std::cout << checking.toString() << std::endl;
    std::cout << transaction.toString() << std::endl;

    std::cout << std::endl << "FINISHED" << std::endl;

    return 0;
}