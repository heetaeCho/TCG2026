#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



class EndsWithMatcherTest : public ::testing::Test {

protected:

    CasedString casedStr;

};



TEST_F(EndsWithMatcherTest, MatchesWhenStringEndsWithCaseSensitive_227) {

    EndsWithMatcher matcher(CasedString("World", CaseSensitive::Yes));

    EXPECT_TRUE(matcher.match("Hello World"));

}



TEST_F(EndsWithMatcherTest, DoesNotMatchWhenStringDoesNotEndWithCaseSensitive_227) {

    EndsWithMatcher matcher(CasedString("world", CaseSensitive::Yes));

    EXPECT_FALSE(matcher.match("Hello World"));

}



TEST_F(EndsWithMatcherTest, MatchesWhenStringEndsWithCaseInsensitive_227) {

    EndsWithMatcher matcher(CasedString("world", CaseSensitive::No));

    EXPECT_TRUE(matcher.match("Hello World"));

}



TEST_F(EndsWithMatcherTest, DoesNotMatchWhenStringDoesNotEndWithCaseInsensitive_227) {

    EndsWithMatcher matcher(CasedString("Earth", CaseSensitive::No));

    EXPECT_FALSE(matcher.match("Hello World"));

}



TEST_F(EndsWithMatcherTest, MatchesEmptyEndingWithAnyStringCaseSensitive_227) {

    EndsWithMatcher matcher(CasedString("", CaseSensitive::Yes));

    EXPECT_TRUE(matcher.match("Hello World"));

}



TEST_F(EndsWithMatcherTest, MatchesEmptyEndingWithAnyStringCaseInsensitive_227) {

    EndsWithMatcher matcher(CasedString("", CaseSensitive::No));

    EXPECT_TRUE(matcher.match("Hello World"));

}



TEST_F(EndsWithMatcherTest, DoesNotMatchNonEmptyEndingWithEmptyStringCaseSensitive_227) {

    EndsWithMatcher matcher(CasedString("World", CaseSensitive::Yes));

    EXPECT_FALSE(matcher.match(""));

}



TEST_F(EndsWithMatcherTest, DoesNotMatchNonEmptyEndingWithEmptyStringCaseInsensitive_227) {

    EndsWithMatcher matcher(CasedString("world", CaseSensitive::No));

    EXPECT_FALSE(matcher.match(""));

}
