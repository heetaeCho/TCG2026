#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



class StartsWithMatcherTest : public ::testing::Test {

protected:

    CasedString caseSensitiveComparator{"hello", CaseSensitive::Yes};

    CasedString caseInsensitiveComparator{"hello", CaseSensitive::No};

};



TEST_F(StartsWithMatcherTest, Match_ReturnsTrueForExactMatch_221) {

    StartsWithMatcher matcher{caseSensitiveComparator};

    EXPECT_TRUE(matcher.match("hello world"));

}



TEST_F(StartsWithMatcherTest, Match_ReturnsFalseForNonMatchingString_221) {

    StartsWithMatcher matcher{caseSensitiveComparator};

    EXPECT_FALSE(matcher.match("world hello"));

}



TEST_F(StartsWithMatcherTest, Match_CaseInsensitiveMatch_221) {

    StartsWithMatcher matcher{caseInsensitiveComparator};

    EXPECT_TRUE(matcher.match("Hello world"));

}



TEST_F(StartsWithMatcherTest, Match_ReturnsFalseForShorterStringThanPattern_221) {

    StartsWithMatcher matcher{caseSensitiveComparator};

    EXPECT_FALSE(matcher.match("hell"));

}



TEST_F(StartsWithMatcherTest, Match_EmptySourceString_221) {

    StartsWithMatcher matcher{caseSensitiveComparator};

    EXPECT_FALSE(matcher.match(""));

}



TEST_F(StartsWithMatcherTest, Match_EmptyPatternString_221) {

    CasedString emptyComparator{"", CaseSensitive::Yes};

    StartsWithMatcher matcher{emptyComparator};

    EXPECT_TRUE(matcher.match("hello world"));

}
