//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../Transaction.h"
#include "../User.h"


class TransactionFixture : public ::testing::Test {
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

TEST_F(TransactionFixture, ConstructorCall) {
    //Correctly construct obj
    ASSERT_NO_THROW(Transaction("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;5367.930176;Prova 3;03/02/2026-01:36:28"));

    //One too many arguments
    ASSERT_THROW(Transaction("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;5367.930176;Prova 3;03/02/2026-01:36:28;invalid argument;"),std::invalid_argument);

    //invalid type during convertion
    ASSERT_THROW(Transaction("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;invalid value;Prova 3;03/02/2026-01:36:28"),std::invalid_argument);


    //Correctly construct obj
    ASSERT_NO_THROW(Transaction(sender,receiver,100.f,"ti ci compri il gelato"));

    //cannot send negative value money
    ASSERT_THROW(Transaction(sender,receiver,-21,"ti ci compri il gelato"),std::invalid_argument);

    //not testing the third constructor since is called inside the second one

}


TEST_F(TransactionFixture, LoadFromString) {
    //correctly loads transaction
    ASSERT_TRUE(transaction.loadFromString("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;5367.930176;Prova 3;03/02/2026-01:36:28"));

    //One too many arguments
    ASSERT_FALSE(transaction.loadFromString("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;invalid argument;5367.930176;Prova 3;03/02/2026-01:36:28"));

    //invalid type during convertion
    ASSERT_FALSE(transaction.loadFromString("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;invalid value;Prova 3;03/02/2026-01:36:28"));

}

TEST_F(TransactionFixture, ComparisonMethods) {
    //users are equal
    ASSERT_TRUE(transaction.isEqual(transaction));

    //users are not equal
    ASSERT_FALSE(transaction.isEqual(Transaction("EGPLbEI0BBvC4Qi4;K7dOYRf4;5xRqvIl4;123.489998;Prova 2;12/02/2026-22:16:10;")));

    //throws bad cast exception
    ASSERT_THROW(transaction.isEqual(User()),std::bad_cast);

    //users are equal
    ASSERT_TRUE(transaction.isEqual(transaction.toString()));

    //users are not equal
    ASSERT_FALSE(transaction.isEqual("EGPLbEI0BBvC4Qi4;K7dOYRf4;5xRqvIl4;123.489998;Prova 2;12/02/2026-22:16:10;"));

    //everything correct except for final invalid argument
    ASSERT_THROW(transaction.isEqual("N208QcjYdCI73GiS;3hJOyC9M;x3DJrs1j;invalid argument;5367.930176;Prova 3;03/02/2026-01:36:28"),std::invalid_argument);

}