#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_container_properties.hpp"



using namespace Catch::Matchers;

using ::testing::_;

using ::testing::Return;



class IsEmptyMatcherTest_236 : public ::testing::Test {

protected:

    IsEmptyMatcher matcher;

};



TEST_F(IsEmptyMatcherTest_236, DescribeReturnsCorrectString_236) {

    EXPECT_EQ(matcher.describe(), "is empty");

}



TEST_F(IsEmptyMatcherTest_236, MatchReturnsTrueForEmptyContainer_236) {

    std::vector<int> emptyVector;

    EXPECT_TRUE(matcher.match(emptyVector));

}



TEST_F(IsEmptyMatcherTest_236, MatchReturnsFalseForNonEmptyContainer_236) {

    std::vector<int> nonEmptyVector = {1, 2, 3};

    EXPECT_FALSE(matcher.match(nonEmptyVector));

}



TEST_F(IsEmptyMatcherTest_236, MatchWithEmptyStringReturnsTrue_236) {

    std::string emptyString;

    EXPECT_TRUE(matcher.match(emptyString));

}



TEST_F(IsEmptyMatcherTest_236, MatchWithNonEmptyStringReturnsFalse_236) {

    std::string nonEmptyString = "Hello";

    EXPECT_FALSE(matcher.match(nonEmptyString));

}
