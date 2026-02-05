//
// Created by samuele on 2/5/26.
//


#include <gtest/gtest.h>
#include "../Date.h"

TEST(DataSuite, DateTests){
    //OK
    ASSERT_NO_THROW(Date("05/02/2026-22:43:21"));

    //incorrect format
    ASSERT_THROW(Date("2011-2-21-11:03:43"),std::invalid_argument);

    //incorrect date (non leap year 29 february)
    ASSERT_THROW(Date("2011/2/29-11:03:43"),std::invalid_argument);

}
