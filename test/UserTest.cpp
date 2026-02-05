//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>

#include "../User.h"
#include "../exceptions/account_already_exists_error.h"

class UserFixture : public ::testing::Test {
protected:
    void SetUp() override {
        user = User("Paolo","XQp6WAW2");
        first = CheckingAccount(2309.43,user.getId(),"1xJZnMN4");
        second = CheckingAccount(90.43,user.getId());
        user.addAccount(first);
        user.addAccount(second);
    }

    CheckingAccount first;
    CheckingAccount second;
    User user;
};

TEST_F(UserFixture, AccountManagment) {

    ASSERT_NO_THROW(user.addAccount(990.98));

    ASSERT_NO_THROW(user.addAccount("3hJOyC9M;"+user.getId()+";110.23;","3hJOyC9M"));

    //If account already exists
    EXPECT_THROW(user.addAccount(first),account_already_exists_error);

    //if argument is invalid
    EXPECT_THROW(user.addAccount("3hJOyC9M;"+user.getId()+";invalid value;11290.230469;","3hJOyC9M"),std::invalid_argument);
}

TEST_F(UserFixture, AccountBalanceManagement) {

    ASSERT_TRUE(user.addAccountBalance(first.getAccountId(),14.32));
    ASSERT_FALSE(user.addAccountBalance("invalid value", 23));
    ASSERT_FALSE(user.addAccountBalance(first.getAccountId(),-3));

    ASSERT_TRUE(user.subtractAccountBalance(first.getAccountId(),14.32));
    ASSERT_FALSE(user.subtractAccountBalance("invalid value", 23));
    ASSERT_FALSE(user.subtractAccountBalance(first.getAccountId(),-3));
}

TEST_F(UserFixture, AccountDeletion) {

    //delete by id
    ASSERT_TRUE(user.deleteAccount(first.getAccountId()));

    //delete by account
    ASSERT_TRUE(user.deleteAccount(second));

    //try invalid value
    ASSERT_FALSE(user.deleteAccount("invalid value"));

    //try to delete member already deleted
    ASSERT_FALSE(user.deleteAccount(first));
}

TEST_F(UserFixture, OverrideMethods) {

    ASSERT_TRUE(user.loadFromString("XQp6WAW2;Franco;"));

    ASSERT_FALSE(user.loadFromString("XQp6WAW2;Franco;invalid argument"));

}