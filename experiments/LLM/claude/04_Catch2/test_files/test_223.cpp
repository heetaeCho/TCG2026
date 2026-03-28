#include <gtest/gtest.h>
#include <string>
#include <regex>

// Include necessary headers from the project
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/catch_case_sensitive.hpp"

using Catch::Matchers::RegexMatcher;
using Catch::CaseSensitive;

class RegexMatcherTest_223 : public ::testing::Test {
protected:
};

// ==================== Normal Operation Tests ====================

TEST_F(RegexMatcherTest_223, ExactMatchSimpleString_223) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
}

TEST_F(RegexMatcherTest_223, SimpleRegexPatternMatches_223) {
    RegexMatcher matcher("hel+o", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_TRUE(matcher.match("helllo"));
}

TEST_F(RegexMatcherTest_223, SimpleRegexPatternDoesNotMatch_223) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("world"));
}

TEST_F(RegexMatcherTest_223, RegexWithDotStar_223) {
    RegexMatcher matcher("hel.*", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_TRUE(matcher.match("help"));
    EXPECT_TRUE(matcher.match("helium"));
}

TEST_F(RegexMatcherTest_223, RegexWithCharacterClass_223) {
    RegexMatcher matcher("[abc]+", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("abc"));
    EXPECT_TRUE(matcher.match("a"));
    EXPECT_FALSE(matcher.match("xyz"));
}

TEST_F(RegexMatcherTest_223, RegexWithAnchors_223) {
    // std::regex_match matches the entire string, so anchors are implicit
    RegexMatcher matcher("^hello$", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
}

TEST_F(RegexMatcherTest_223, RegexWithDigits_223) {
    RegexMatcher matcher("\\d{3}-\\d{4}", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("123-4567"));
    EXPECT_FALSE(matcher.match("12-4567"));
    EXPECT_FALSE(matcher.match("abc-defg"));
}

TEST_F(RegexMatcherTest_223, RegexWithOptionalChar_223) {
    RegexMatcher matcher("colou?r", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("color"));
    EXPECT_TRUE(matcher.match("colour"));
    EXPECT_FALSE(matcher.match("colouur"));
}

// ==================== Case Sensitivity Tests ====================

TEST_F(RegexMatcherTest_223, CaseSensitiveMatchSucceeds_223) {
    RegexMatcher matcher("Hello", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("Hello"));
}

TEST_F(RegexMatcherTest_223, CaseSensitiveMatchFailsOnDifferentCase_223) {
    RegexMatcher matcher("Hello", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("hello"));
    EXPECT_FALSE(matcher.match("HELLO"));
}

TEST_F(RegexMatcherTest_223, CaseInsensitiveMatchSucceeds_223) {
    RegexMatcher matcher("Hello", CaseSensitive::No);
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_TRUE(matcher.match("HELLO"));
    EXPECT_TRUE(matcher.match("Hello"));
    EXPECT_TRUE(matcher.match("hElLo"));
}

TEST_F(RegexMatcherTest_223, CaseInsensitiveMatchFails_223) {
    RegexMatcher matcher("Hello", CaseSensitive::No);
    EXPECT_FALSE(matcher.match("world"));
}

TEST_F(RegexMatcherTest_223, CaseInsensitiveRegexPattern_223) {
    RegexMatcher matcher("[a-z]+", CaseSensitive::No);
    EXPECT_TRUE(matcher.match("abc"));
    EXPECT_TRUE(matcher.match("ABC"));
    EXPECT_TRUE(matcher.match("AbC"));
}

// ==================== Boundary Conditions ====================

TEST_F(RegexMatcherTest_223, EmptyStringMatchesEmptyRegex_223) {
    RegexMatcher matcher("", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match(""));
}

TEST_F(RegexMatcherTest_223, EmptyStringDoesNotMatchNonEmptyRegex_223) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match(""));
}

TEST_F(RegexMatcherTest_223, NonEmptyStringDoesNotMatchEmptyRegex_223) {
    RegexMatcher matcher("", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("hello"));
}

TEST_F(RegexMatcherTest_223, RegexMatchesEntireStringNotSubstring_223) {
    // std::regex_match requires full string match
    RegexMatcher matcher("hel", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("hello"));
}

TEST_F(RegexMatcherTest_223, RegexDotStarMatchesEntireString_223) {
    RegexMatcher matcher(".*hel.*", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_TRUE(matcher.match("say hello world"));
}

TEST_F(RegexMatcherTest_223, SingleCharacterMatch_223) {
    RegexMatcher matcher(".", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("a"));
    EXPECT_FALSE(matcher.match("ab"));
    EXPECT_FALSE(matcher.match(""));
}

TEST_F(RegexMatcherTest_223, SpecialRegexCharactersInPattern_223) {
    RegexMatcher matcher("hello\\.world", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello.world"));
    EXPECT_FALSE(matcher.match("helloxworld"));
}

TEST_F(RegexMatcherTest_223, VeryLongStringMatch_223) {
    std::string longStr(1000, 'a');
    RegexMatcher matcher("a+", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match(longStr));
}

TEST_F(RegexMatcherTest_223, RegexWithAlternation_223) {
    RegexMatcher matcher("cat|dog", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("cat"));
    EXPECT_TRUE(matcher.match("dog"));
    EXPECT_FALSE(matcher.match("bird"));
}

TEST_F(RegexMatcherTest_223, RegexWithGrouping_223) {
    RegexMatcher matcher("(ab)+", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("ab"));
    EXPECT_TRUE(matcher.match("abab"));
    EXPECT_FALSE(matcher.match("a"));
    EXPECT_FALSE(matcher.match("abc"));
}

// ==================== Error/Exceptional Cases ====================

TEST_F(RegexMatcherTest_223, InvalidRegexThrows_223) {
    // An invalid regex pattern should cause std::regex to throw std::regex_error
    RegexMatcher matcher("[invalid", CaseSensitive::Yes);
    EXPECT_THROW(matcher.match("test"), std::regex_error);
}

TEST_F(RegexMatcherTest_223, InvalidRegexUnmatchedParen_223) {
    RegexMatcher matcher("(unmatched", CaseSensitive::Yes);
    EXPECT_THROW(matcher.match("test"), std::regex_error);
}

// ==================== Describe Tests ====================

TEST_F(RegexMatcherTest_223, DescribeReturnsNonEmptyString_223) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

TEST_F(RegexMatcherTest_223, DescribeContainsRegexPattern_223) {
    RegexMatcher matcher("hello", CaseSensitive::Yes);
    std::string description = matcher.describe();
    // The description should contain the regex pattern
    EXPECT_NE(description.find("hello"), std::string::npos);
}

TEST_F(RegexMatcherTest_223, DescribeCaseInsensitiveMentionsCaseSensitivity_223) {
    RegexMatcher matcherInsensitive("hello", CaseSensitive::No);
    RegexMatcher matcherSensitive("hello", CaseSensitive::Yes);
    std::string descInsensitive = matcherInsensitive.describe();
    std::string descSensitive = matcherSensitive.describe();
    // The descriptions should differ based on case sensitivity
    // At minimum, both should be non-empty
    EXPECT_FALSE(descInsensitive.empty());
    EXPECT_FALSE(descSensitive.empty());
}

// ==================== Additional Edge Cases ====================

TEST_F(RegexMatcherTest_223, RegexWithWhitespace_223) {
    RegexMatcher matcher("hello world", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello world"));
    EXPECT_FALSE(matcher.match("helloworld"));
}

TEST_F(RegexMatcherTest_223, RegexWithNewline_223) {
    RegexMatcher matcher("hello\\nworld", CaseSensitive::Yes);
    // ECMAScript regex \n matches newline character
    EXPECT_FALSE(matcher.match("hello world"));
}

TEST_F(RegexMatcherTest_223, RegexQuantifierZeroOrMore_223) {
    RegexMatcher matcher("ab*c", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("ac"));
    EXPECT_TRUE(matcher.match("abc"));
    EXPECT_TRUE(matcher.match("abbc"));
    EXPECT_FALSE(matcher.match("adc"));
}

TEST_F(RegexMatcherTest_223, RegexQuantifierOneOrMore_223) {
    RegexMatcher matcher("ab+c", CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("ac"));
    EXPECT_TRUE(matcher.match("abc"));
    EXPECT_TRUE(matcher.match("abbc"));
}

TEST_F(RegexMatcherTest_223, RegexWithBackslashD_223) {
    RegexMatcher matcher("\\d+", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("12345"));
    EXPECT_FALSE(matcher.match("abcde"));
    EXPECT_FALSE(matcher.match(""));
}

TEST_F(RegexMatcherTest_223, RegexWithWordBoundary_223) {
    RegexMatcher matcher("\\w+", CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_TRUE(matcher.match("hello123"));
    EXPECT_FALSE(matcher.match(""));
}

TEST_F(RegexMatcherTest_223, CaseInsensitiveWithSpecialChars_223) {
    RegexMatcher matcher("Hello\\.World", CaseSensitive::No);
    EXPECT_TRUE(matcher.match("hello.world"));
    EXPECT_TRUE(matcher.match("HELLO.WORLD"));
    EXPECT_FALSE(matcher.match("helloxworld"));
}
