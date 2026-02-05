//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../Transaction.h"


class TransactionTest : public ::testing::Test {
protected:
    void SetUp() override {
        sender = CheckingAccount(1234.3f,"3hJOyC9M");
        receiver = CheckingAccount(897.31f,"x3DJrs1j");
        transaction = Transaction(sender,receiver,100.f);
    }

    CheckingAccount sender;
    CheckingAccount receiver;
    Transaction transaction;
};

TEST_F(TransactionTest, ConstructorCall) {
    //OK expression
    ASSERT_NO_THROW(Transaction("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;5367.930176;Prova 3;03/02/2026-01:36:28"));

    //One too many arguments
    ASSERT_THROW(Transaction("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;5367.930176;Prova 3;03/02/2026-01:36:28;invalid argument;"),std::invalid_argument);

    //invalid type during convertion
    ASSERT_THROW(Transaction("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;invalid value;Prova 3;03/02/2026-01:36:28"),std::invalid_argument);


    //OK expression
    ASSERT_NO_THROW(Transaction(sender,receiver,100.f,"ti ci compri il gelato"));

    //cannot send negative value money
    ASSERT_THROW(Transaction(sender,receiver,-21,"ti ci compri il gelato"),std::invalid_argument);

    //not testing the third constructor since is called inside the second one

}


TEST_F(TransactionTest, LoadFromString) {
    //OK expression
    ASSERT_TRUE(transaction.loadFromString("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;5367.930176;Prova 3;03/02/2026-01:36:28"));

    //One too many arguments
    ASSERT_FALSE(transaction.loadFromString("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;invalid argument;5367.930176;Prova 3;03/02/2026-01:36:28"));

    //invalid type during convertion
    ASSERT_FALSE(transaction.loadFromString("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;invalid value;Prova 3;03/02/2026-01:36:28"));

}