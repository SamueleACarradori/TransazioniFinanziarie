//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../User.h"

class UserFixture : public ::testing::Test {
protected:
    void SetUp() override {
        user = User("Paolo");
        first = CheckingAccount(2309.43,user.getId());
    }

    CheckingAccount first;
    User user;
};

TEST_F(UserFixture, AccountManagment) {

    ASSERT_ANY_THROW(user.addAccount(first));
    ASSERT_ANY_THROW(user.addAccount(990.98));
    ASSERT_THROW(user.addAccount("3hJOyC9M;"+user.getId()+";11290.230469;","3hJOyC9M"),std::out_of_range);
    EXPECT_THROW(user.addAccount("3hJOyC9M;"+user.getId()+"invalid value"+";11290.230469;","3hJOyC9M"),std::out_of_range);
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

    ASSERT_TRUE(user.deleteAccount(user.getAccount()[1]));
    ASSERT_TRUE(user.deleteAccount(first));
    ASSERT_FALSE(user.deleteAccount("invalid value"));
}

TEST_F(UserFixture, OverrideMethods) {

    ASSERT_TRUE(user.loadFromString("XQp6WAW2;Franco;"));
    ASSERT_FALSE(user.deleteAccount("XQp6WAW2;Franco;invalid argument"));

}