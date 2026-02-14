//
// Created by samuele on 2/5/26.
//


#include <gtest/gtest.h>
#include "../Date.h"

TEST(DateSuite, DateTests){
    //correctly create object with correct date format
    ASSERT_NO_THROW(Date("05/06/2026-22:43:21"));

    //correctly create object with correct date format from leap year
    ASSERT_NO_THROW(Date("29/02/2024-22:43:21"));

    //incorrect date format
    ASSERT_THROW(Date("2011-3-21-11:03:43"),std::invalid_argument);

    //incorrect date (non leap year 29 february)
    ASSERT_THROW(Date("29/02/2011-11:03:43"),std::invalid_argument);

    //incorrect date (32 january does not exist)
    ASSERT_THROW(Date("32/01/2011-11:03:43"),std::invalid_argument);

    //incorrect hours (25 hours)
    ASSERT_THROW(Date("1/02/2011-25:03:43"),std::invalid_argument);

    //incorrect hours (25 hours)
    ASSERT_THROW(Date("9/05/2026-24:41:43"),std::invalid_argument);

}
