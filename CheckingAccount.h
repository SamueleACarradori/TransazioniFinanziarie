//
// Created by samuele on 1/14/26.
//

#ifndef TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H
#define TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H
#include <string>


class CheckingAccount {
public:
    explicit CheckingAccount(float balance);
    CheckingAccount(float balance,std::string idUser,std::string name);
    CheckingAccount(float balance,std::string id,std::string idUser,std::string name);

    void addBalance(float add);
    void subtractBalance(float subtract);

    //getters
    std::string getAccountId();
    std::string getAccountName();
    float getBalance();

private:
    float balance = 0;
    std::string id;
    std::string idUser;
    std::string name;
};


#endif //TRANSAZIONIFINANZIARIE_CHECKINGACCOUNT_H