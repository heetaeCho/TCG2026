#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"

#include "catch2/catch_case_sensitive.hpp"



using namespace Catch;

using namespace Matchers;



class RegexMatcherTest_223 : public ::testing::Test {

protected:

    void SetUp() override {}



    void TearDown() override {}

};



TEST_F(RegexMatcherTest_223, Match_CaseSensitiveMatch_223) {

    RegexMatcher matcher("hello", CaseSensitive::Yes);

    EXPECT_TRUE(matcher.match("hello"));

}



TEST_F(RegexMatcherTest_223, Match_CaseInsensitiveMatch_223) {

    RegexMatcher matcher("hello", CaseSensitive::No);

    EXPECT_TRUE(matcher.match("HELLO"));

}



TEST_F(RegexMatcherTest_223, Match_PartialMatch_ReturnsFalse_223) {

    RegexMatcher matcher("^hello$", CaseSensitive::Yes);

    EXPECT_FALSE(matcher.match("hello world"));

}



TEST_F(RegexMatcherTest_223, Match_EmptyString_223) {

    RegexMatcher matcher("", CaseSensitive::Yes);

    EXPECT_TRUE(matcher.match(""));

}



TEST_F(RegexMatcherTest_223, Match_EmptyPattern_NonEmptyString_ReturnsFalse_223) {

    RegexMatcher matcher("", CaseSensitive::Yes);

    EXPECT_FALSE(matcher.match("non-empty"));

}



TEST_F(RegexMatcherTest_223, Match_ComplexPattern_CaseInsensitive_223) {

    RegexMatcher matcher("[a-z]+", CaseSensitive::No);

    EXPECT_TRUE(matcher.match("HELLOworld"));

}



TEST_F(RegexMatcherTest_223, Match_SpecialCharactersInPattern_223) {

    RegexMatcher matcher(R"(\d+)", CaseSensitive::Yes);

    EXPECT_TRUE(matcher.match("12345"));

}
