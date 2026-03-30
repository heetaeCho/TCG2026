#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



TEST(StringContainsMatcherTest_220, MatchReturnsTrueWhenSubstringPresent_220) {

    CasedString comparator("hello", CaseSensitive::Yes);

    StringContainsMatcher matcher(comparator);



    EXPECT_TRUE(matcher.match("hello world"));

}



TEST(StringContainsMatcherTest_220, MatchReturnsFalseWhenSubstringAbsent_220) {

    CasedString comparator("hello", CaseSensitive::Yes);

    StringContainsMatcher matcher(comparator);



    EXPECT_FALSE(matcher.match("world"));

}



TEST(StringContainsMatcherTest_220, MatchCaseInsensitiveSubstringPresent_220) {

    CasedString comparator("hello", CaseSensitive::No);

    StringContainsMatcher matcher(comparator);



    EXPECT_TRUE(matcher.match("HELLO world"));

}



TEST(StringContainsMatcherTest_220, MatchCaseInsensitiveSubstringAbsent_220) {

    CasedString comparator("hello", CaseSensitive::No);

    StringContainsMatcher matcher(comparator);



    EXPECT_FALSE(matcher.match("world HELLO"));

}



TEST(StringContainsMatcherTest_220, MatchEmptySourceString_220) {

    CasedString comparator("hello", CaseSensitive::Yes);

    StringContainsMatcher matcher(comparator);



    EXPECT_FALSE(matcher.match(""));

}



TEST(StringContainsMatcherTest_220, MatchEmptyComparatorString_220) {

    CasedString comparator("", CaseSensitive::Yes);

    StringContainsMatcher matcher(comparator);



    EXPECT_TRUE(matcher.match("hello world"));

}
