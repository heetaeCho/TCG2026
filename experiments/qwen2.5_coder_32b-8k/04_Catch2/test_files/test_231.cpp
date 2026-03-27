#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_container_properties.hpp"

#include <vector>

#include <string>



using namespace Catch::Matchers;



class IsEmptyMatcherTest : public ::testing::Test {

protected:

    IsEmptyMatcher matcher;

};



TEST_F(IsEmptyMatcherTest_231, Match_EmptyVector_ReturnsTrue_231) {

    std::vector<int> empty_vector;

    EXPECT_TRUE(matcher.match(empty_vector));

}



TEST_F(IsEmptyMatcherTest_231, Match_NonEmptyVector_ReturnsFalse_231) {

    std::vector<int> non_empty_vector = {1, 2, 3};

    EXPECT_FALSE(matcher.match(non_empty_vector));

}



TEST_F(IsEmptyMatcherTest_231, Match_EmptyString_ReturnsTrue_231) {

    std::string empty_string;

    EXPECT_TRUE(matcher.match(empty_string));

}



TEST_F(IsEmptyMatcherTest_231, Match_NonEmptyString_ReturnsFalse_231) {

    std::string non_empty_string = "Hello";

    EXPECT_FALSE(matcher.match(non_empty_string));

}



TEST_F(IsEmptyMatcherTest_231, Describe_ReturnsExpectedDescription_231) {

    EXPECT_EQ(matcher.describe(), "is empty");

}
