//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../CheckingAccount.h"

class CheckingAccountFixture : public ::testing::Test {
protected:
    void SetUp() override {

    }

    CheckingAccount account;
};
