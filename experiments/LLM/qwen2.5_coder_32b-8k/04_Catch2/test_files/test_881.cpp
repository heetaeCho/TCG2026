#include <gtest/gtest.h>

#include <string>



// Assuming the function starts_with is in a header file named coverage-helper.h

#include "coverage-helper.h"



class StartsWidthTest_881 : public ::testing::Test {

protected:

    // No specific setup or teardown needed for this simple function

};



TEST_F(StartsWithTest_881, NormalOperation_PrefixMatches_881) {

    EXPECT_TRUE(starts_with("hello", "he"));

}



TEST_F(StartsWithTest_881, NormalOperation_PrefixDoesNotMatch_881) {

    EXPECT_FALSE(starts_with("hello", "world"));

}



TEST_F(StartsWithTest_881, BoundaryCondition_EmptyPrefix_881) {

    EXPECT_TRUE(starts_with("hello", ""));

}



TEST_F(StartsWithTest_881, BoundaryCondition_EmptyStringAndPrefix_881) {

    EXPECT_TRUE(starts_with("", ""));

}



TEST_F(StartsWithTest_881, BoundaryCondition_StringShorterThanPrefix_881) {

    EXPECT_FALSE(starts_with("he", "hello"));

}
