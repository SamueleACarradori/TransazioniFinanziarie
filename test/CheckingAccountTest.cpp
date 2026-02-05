//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../CheckingAccount.h"

class CheckingAccountFixture : public ::testing::Test {
protected:
    void SetUp() override {
        account = CheckingAccount(123.45,"XQp6WAW2");
    }

    CheckingAccount account;
};

TEST_F(CheckingAccountFixture, ConstructorCall) {
    //OK expression
    ASSERT_NO_THROW(CheckingAccount("3hJOyC9M;XQp6WAW2;190.29;"));

    //One too many arguments
    ASSERT_THROW(CheckingAccount("3hJOyC9M;invalid argument;XQp6WAW2;190.29;"),std::invalid_argument);

    //invalid type during convertion
    ASSERT_THROW(CheckingAccount("3hJOyC9M;XQp6WAW2;invalid argument;"),std::invalid_argument);
}

TEST_F(CheckingAccountFixture, BalanceManaging) {

    ASSERT_NO_THROW(account.addBalance(12));
    ASSERT_THROW(account.addBalance(-3),std::invalid_argument);

    ASSERT_NO_THROW(account.subtractBalance(12));
    ASSERT_THROW(account.subtractBalance(-3),std::invalid_argument);
}

TEST_F(CheckingAccountFixture, LoadFromString) {

    ASSERT_TRUE(account.loadFromString("3hJOyC9M;XQp6WAW2;190.29;"));

    ASSERT_FALSE(account.loadFromString("3hJOyC9M;XQp6WAW2;invalid argument;"));

    ASSERT_FALSE(account.loadFromString("3hJOyC9M;XQp6WAW2;190.29;invalid argument;"));

}