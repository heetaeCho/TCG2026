#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Matchers;

using ::testing::Eq;



class RangeEqualsMatcherTest_956 : public ::testing::Test {

protected:

    std::vector<int> expectedRange = {1, 2, 3, 4, 5};

};



TEST_F(RangeEqualsMatcherTest_956, MatchIdenticalRanges_956) {

    std::vector<int> testRange = {1, 2, 3, 4, 5};

    RangeEqualsMatcher<std::vector<int>, std::equal_to<int>> matcher(expectedRange, Eq());

    EXPECT_TRUE(matcher.match(testRange));

}



TEST_F(RangeEqualsMatcherTest_956, MatchDifferentRanges_956) {

    std::vector<int> testRange = {1, 2, 3, 4, 6};

    RangeEqualsMatcher<std::vector<int>, std::equal_to<int>> matcher(expectedRange, Eq());

    EXPECT_FALSE(matcher.match(testRange));

}



TEST_F(RangeEqualsMatcherTest_956, MatchEmptyRanges_956) {

    std::vector<int> testRange = {};

    std::vector<int> emptyExpectedRange = {};

    RangeEqualsMatcher<std::vector<int>, std::equal_to<int>> matcher(emptyExpectedRange, Eq());

    EXPECT_TRUE(matcher.match(testRange));

}



TEST_F(RangeEqualsMatcherTest_956, MatchDifferentSizeRanges_956) {

    std::vector<int> testRange = {1, 2, 3};

    RangeEqualsMatcher<std::vector<int>, std::equal_to<int>> matcher(expectedRange, Eq());

    EXPECT_FALSE(matcher.match(testRange));

}



TEST_F(RangeEqualsMatcherTest_956, MatchWithCustomPredicate_956) {

    std::vector<int> testRange = {2, 3, 4, 5, 6};

    RangeEqualsMatcher<std::vector<int>, std::less_equal<int>> matcher(expectedRange, std::less_equal<int>());

    EXPECT_TRUE(matcher.match(testRange));

}



TEST_F(RangeEqualsMatcherTest_956, MatchWithCustomPredicateFailure_956) {

    std::vector<int> testRange = {2, 3, 4, 5, 0};

    RangeEqualsMatcher<std::vector<int>, std::less_equal<int>> matcher(expectedRange, std::less_equal<int>());

    EXPECT_FALSE(matcher.match(testRange));

}
