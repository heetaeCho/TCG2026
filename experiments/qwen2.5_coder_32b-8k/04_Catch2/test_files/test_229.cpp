#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



class RegexMatcherTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RegexMatcherTest_229, Matches_CaseSensitive_229) {

    std::string regex = "hello";

    CaseSensitive caseSensitivity = CaseSensitive::Yes;

    RegexMatcher matcher(regex, caseSensitivity);

    EXPECT_TRUE(matcher.match("hello"));

    EXPECT_FALSE(matcher.match("Hello"));

}



TEST_F(RegexMatcherTest_229, Matches_CaseInsensitive_229) {

    std::string regex = "hello";

    CaseSensitive caseSensitivity = CaseSensitive::No;

    RegexMatcher matcher(regex, caseSensitivity);

    EXPECT_TRUE(matcher.match("hello"));

    EXPECT_TRUE(matcher.match("Hello"));

}



TEST_F(RegexMatcherTest_229, Matches_BoundaryCase_EmptyString_229) {

    std::string regex = "";

    CaseSensitive caseSensitivity = CaseSensitive::Yes;

    RegexMatcher matcher(regex, caseSensitivity);

    EXPECT_TRUE(matcher.match(""));

    EXPECT_FALSE(matcher.match("nonempty"));

}



TEST_F(RegexMatcherTest_229, Matches_BoundaryCase_EmptyPattern_NonEmptyString_229) {

    std::string regex = "";

    CaseSensitive caseSensitivity = CaseSensitive::Yes;

    RegexMatcher matcher(regex, caseSensitivity);

    EXPECT_TRUE(matcher.match("anystring"));

}



TEST_F(RegexMatcherTest_229, Matches_SpecialCharacters_229) {

    std::string regex = "h.*o";

    CaseSensitive caseSensitivity = CaseSensitive::Yes;

    RegexMatcher matcher(regex, caseSensitivity);

    EXPECT_TRUE(matcher.match("hello"));

    EXPECT_FALSE(matcher.match("hallo"));

}



TEST_F(RegexMatcherTest_229, Matches_ExceptionalCase_InvalidPattern_229) {

    std::string regex = "(*";

    CaseSensitive caseSensitivity = CaseSensitive::Yes;

    try {

        RegexMatcher matcher(regex, caseSensitivity);

        EXPECT_TRUE(false); // Should not reach here

    } catch (...) {

        EXPECT_TRUE(true); // Expected exception

    }

}
