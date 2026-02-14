//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../CheckingAccount.h"
#include "../Transaction.h"

class CheckingAccountFixture : public ::testing::Test {
protected:
    void SetUp() override {
        account = CheckingAccount(123.45,"XQp6WAW2");
    }

    CheckingAccount account;
};

TEST_F(CheckingAccountFixture, ConstructorCall) {

    //correctly construct obj
    ASSERT_NO_THROW(CheckingAccount("3hJOyC9M;XQp6WAW2;190.29;"));

    //One too many arguments
    ASSERT_THROW(CheckingAccount("3hJOyC9M;invalid argument;XQp6WAW2;190.29;"),std::invalid_argument);

    //invalid type during convertion
    ASSERT_THROW(CheckingAccount("3hJOyC9M;XQp6WAW2;invalid argument;"),std::invalid_argument);
}

TEST_F(CheckingAccountFixture, BalanceManaging) {

    //correctly add to balance
    ASSERT_NO_THROW(account.addBalance(12));

    //number is not positive
    ASSERT_THROW(account.addBalance(-3),std::invalid_argument);

    //correctly subtract to balance
    ASSERT_NO_THROW(account.subtractBalance(12));

    //number is not positive
    ASSERT_THROW(account.subtractBalance(-3),std::invalid_argument);
}

TEST_F(CheckingAccountFixture, LoadFromString) {

    //correctly load from string
    ASSERT_TRUE(account.loadFromString("3hJOyC9M;XQp6WAW2;190.29;"));

    //invalid type during convertion
    ASSERT_FALSE(account.loadFromString("3hJOyC9M;XQp6WAW2;invalid argument;"));

    //One too many arguments
    ASSERT_FALSE(account.loadFromString("3hJOyC9M;XQp6WAW2;190.29;invalid argument;"));

}

TEST_F(CheckingAccountFixture, ComparisonMethods) {

    //correctly spots that accounts are equal
    ASSERT_TRUE(account.isEqual(account));

    //users are not equal
    ASSERT_FALSE(account.isEqual(CheckingAccount("3hJOAA9M;XQp601W2;190.29;")));

    //checking account cannot be equal to transaction or user
    ASSERT_THROW(account.isEqual(Transaction()),std::bad_cast);

    //account is equal to string account
    ASSERT_TRUE(account.isEqual(account.toString()));

    //accounts are not equal
    ASSERT_FALSE(account.isEqual("3hJOAA9M;XQp601W2;190.29;"));

    //everything correct except for final invalid argument
    ASSERT_THROW(account.isEqual("3hJOAA9M;XQp601W2;190.29;invalid argument;"),std::invalid_argument);

    //the == and != operators are not tested since it just uses isEqual()
}