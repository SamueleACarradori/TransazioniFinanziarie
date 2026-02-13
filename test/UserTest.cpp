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

    //adds an account requesting only starting income
    ASSERT_NO_THROW(user.addAccount(990.98));

    //adds account by string
    ASSERT_NO_THROW(user.addAccount("3hJOyC9M;"+user.getId()+";110.23;","3hJOyC9M"));

    // account already exists
    ASSERT_THROW(user.addAccount(first),account_already_exists_error);

    // account does not match user
    ASSERT_THROW(user.addAccount(CheckingAccount()),std::invalid_argument);

    //argument is invalid
    ASSERT_THROW(user.addAccount("3hJOyC9M;"+user.getId()+";invalid value;11290.230469;","3hJOyC9M"),std::invalid_argument);
}

TEST_F(UserFixture, AccountBalanceManagement) {
    //testing add account balance

    //correctly adds
    ASSERT_TRUE(user.addAccountBalance(first.getAccountId(),14.32));

    //Invalid account id
    ASSERT_FALSE(user.addAccountBalance("invalid value", 23));

    //Invalid amount (less than 0)
    ASSERT_FALSE(user.addAccountBalance(first.getAccountId(),0));

    //correctly subtracts
    ASSERT_TRUE(user.subtractAccountBalance(first.getAccountId(),14.32));

    //Invalid account id
    ASSERT_FALSE(user.subtractAccountBalance("invalid value", 23));

    //Invalid amount (less than 0)
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

TEST_F(UserFixture, LoadFromString) {
    //standard use of function
    ASSERT_TRUE(user.loadFromString("XQp6WAW2;Franco;"));

    //too many arguments
    ASSERT_FALSE(user.loadFromString("XQp6WAW2;Franco;invalid argument;"));

    //ID has 9 char instead of standard length of 8
    ASSERT_FALSE(user.loadFromString("XQp6WAW2P;Franco;"));
}


TEST_F(UserFixture, ComparisonMethods) {
    //users are equal
    ASSERT_TRUE(user.isEqual(user));

    //users are not equal
    ASSERT_FALSE(user.isEqual(User("Goku")));

    //throws bad cast exception
    ASSERT_THROW(user.isEqual(CheckingAccount()),std::bad_cast);

    //users are equal
    ASSERT_TRUE(user.isEqual(user.toString()));

    //users are not equal
    ASSERT_FALSE(user.isEqual("12345678;NuGundam;"));

    //everything correct except for final invalid argument
    ASSERT_THROW(user.isEqual("XQp6WAW2;Franco;invalid argument;"),std::invalid_argument);
}