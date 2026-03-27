#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"

#include "catch2/catch_case_sensitive.hpp"



using namespace Catch;

using namespace Matchers;



class RegexMatcherTest_224 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(RegexMatcherTest_224, DescribeReturnsCorrectString_CaseSensitive_224) {

    RegexMatcher matcher("abc", CaseSensitive::Yes);

    EXPECT_EQ(matcher.describe(), "matches abc case sensitively");

}



TEST_F(RegexMatcherTest_224, DescribeReturnsCorrectString_CaseInsensitive_224) {

    RegexMatcher matcher("abc", CaseSensitive::No);

    EXPECT_EQ(matcher.describe(), "matches abc case insensitively");

}



TEST_F(RegexMatcherTest_224, MatchReturnsTrueForExactMatch_CaseSensitive_224) {

    RegexMatcher matcher("abc", CaseSensitive::Yes);

    EXPECT_TRUE(matcher.match("abc"));

}



TEST_F(RegexMatcherTest_224, MatchReturnsFalseForNonExactMatch_CaseSensitive_224) {

    RegexMatcher matcher("abc", CaseSensitive::Yes);

    EXPECT_FALSE(matcher.match("abcd"));

}



TEST_F(RegexMatcherTest_224, MatchReturnsTrueForCaseInsensitiveMatch_224) {

    RegexMatcher matcher("abc", CaseSensitive::No);

    EXPECT_TRUE(matcher.match("ABC"));

}



TEST_F(RegexMatcherTest_224, MatchReturnsFalseForNonMatchingString_CaseInsensitive_224) {

    RegexMatcher matcher("abc", CaseSensitive::No);

    EXPECT_FALSE(matcher.match("def"));

}
