#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class AnyMatchMatcherTest_180 : public ::testing::Test {

protected:

    AnyMatchMatcherTest_180() {}

};



TEST_F(AnyMatchMatcherTest_180, DescribeReturnsExpectedString_180) {

    AnyMatchMatcher<AlwaysFalseMatcher> matcher(AlwaysFalseMatcher{});

    EXPECT_EQ(matcher.describe(), "any match always false");

}



TEST_F(AnyMatchMatcherTest_180, MatchEmptyRange_ReturnsFalse_180) {

    AnyMatchMatcher<AlwaysTrueMatcher> matcher(AlwaysTrueMatcher{});

    std::vector<int> emptyVector;

    EXPECT_FALSE(matcher.match(emptyVector));

}



TEST_F(AnyMatchMatcherTest_180, MatchNonEmptyRangeWithNoMatches_ReturnsFalse_180) {

    AnyMatchMatcher<EqualsMatcher<int>> matcher(EqualsMatcher<int>(5));

    std::vector<int> range = {1, 2, 3, 4};

    EXPECT_FALSE(matcher.match(range));

}



TEST_F(AnyMatchMatcherTest_180, MatchNonEmptyRangeWithSomeMatches_ReturnsTrue_180) {

    AnyMatchMatcher<EqualsMatcher<int>> matcher(EqualsMatcher<int>(3));

    std::vector<int> range = {1, 2, 3, 4};

    EXPECT_TRUE(matcher.match(range));

}



TEST_F(AnyMatchMatcherTest_180, MatchNonEmptyRangeWithAllMatches_ReturnsTrue_180) {

    AnyMatchMatcher<AlwaysTrueMatcher> matcher(AlwaysTrueMatcher{});

    std::vector<int> range = {1, 2, 3, 4};

    EXPECT_TRUE(matcher.match(range));

}
