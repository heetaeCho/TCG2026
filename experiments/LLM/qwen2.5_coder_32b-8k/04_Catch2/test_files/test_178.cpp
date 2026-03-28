#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class NoneMatchMatcherTest_178 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(NoneMatchMatcherTest_178, DescribeReturnsExpectedString_178) {

    NoneMatchMatcher<std::equal_to<int>> matcher(std::equal_to<int>());

    EXPECT_EQ(matcher.describe(), "none match is equal to");

}



TEST_F(NoneMatchMatcherTest_178, MatchEmptyRange_ReturnsTrue_178) {

    NoneMatchMatcher<std::equal_to<int>> matcher(std::equal_to<int>());

    std::vector<int> emptyVector;

    EXPECT_TRUE(matcher.match(emptyVector));

}



TEST_F(NoneMatchMatcherTest_178, MatchNonMatchingElements_ReturnsTrue_178) {

    NoneMatchMatcher<std::equal_to<int>> matcher(5);

    std::vector<int> elements = {1, 2, 3};

    EXPECT_TRUE(matcher.match(elements));

}



TEST_F(NoneMatchMatcherTest_178, MatchWithMatchingElement_ReturnsFalse_178) {

    NoneMatchMatcher<std::equal_to<int>> matcher(2);

    std::vector<int> elements = {1, 2, 3};

    EXPECT_FALSE(matcher.match(elements));

}



TEST_F(NoneMatchMatcherTest_178, MatchSingleNonMatchingElement_ReturnsTrue_178) {

    NoneMatchMatcher<std::equal_to<int>> matcher(5);

    std::vector<int> elements = {4};

    EXPECT_TRUE(matcher.match(elements));

}



TEST_F(NoneMatchMatcherTest_178, MatchSingleMatchingElement_ReturnsFalse_178) {

    NoneMatchMatcher<std::equal_to<int>> matcher(2);

    std::vector<int> elements = {2};

    EXPECT_FALSE(matcher.match(elements));

}
