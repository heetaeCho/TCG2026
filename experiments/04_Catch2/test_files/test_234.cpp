#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_container_properties.hpp"



using namespace Catch::Matchers;



class SizeMatchesMatcherTest_234 : public ::testing::Test {

protected:

    SizeMatchesMatcher<std::equal_to<size_t>> matcher;



    SizeMatchesMatcherTest_234() : matcher(std::equal_to<size_t>()) {}

};



TEST_F(SizeMatchesMatcherTest_234, Match_ReturnsTrueForEqualSizes_234) {

    std::vector<int> vec = {1, 2, 3};

    EXPECT_TRUE(matcher.match(vec));

}



TEST_F(SizeMatchesMatcherTest_234, Match_ReturnsFalseForNonEqualSizes_234) {

    std::vector<int> vec = {1, 2};

    EXPECT_FALSE(matcher.match(vec));

}



TEST_F(SizeMatchesMatcherTest_234, Describe_ReturnsCorrectDescription_234) {

    EXPECT_EQ(matcher.describe(), "size matches is equal to");

}



TEST_F(SizeMatchesMatcherTest_234, Match_EmptyContainer_ReturnsFalseWithNonZeroSizeMatcher_234) {

    std::vector<int> vec;

    SizeMatchesMatcher<std::equal_to<size_t>> non_zero_matcher(std::equal_to<size_t>(1));

    EXPECT_FALSE(non_zero_matcher.match(vec));

}



TEST_F(SizeMatchesMatcherTest_234, Match_EmptyContainer_ReturnsTrueWithZeroSizeMatcher_234) {

    std::vector<int> vec;

    SizeMatchesMatcher<std::equal_to<size_t>> zero_matcher(std::equal_to<size_t>(0));

    EXPECT_TRUE(zero_matcher.match(vec));

}
