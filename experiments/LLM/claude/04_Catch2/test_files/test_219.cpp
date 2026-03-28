#include <gtest/gtest.h>
#include <string>
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

// Helper to create CaseSensitive enum values
// Based on the interface, CaseSensitive likely has Yes and No values

class StringEqualsMatcherTest_219 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test exact match with case-sensitive comparison
TEST_F(StringEqualsMatcherTest_219, ExactMatchCaseSensitive_219) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello"));
}

// Test mismatch with case-sensitive comparison
TEST_F(StringEqualsMatcherTest_219, MismatchCaseSensitive_219) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("world"));
}

// Test case-sensitive comparison fails on different case
TEST_F(StringEqualsMatcherTest_219, CaseSensitiveDifferentCase_219) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("Hello"));
}

// Test case-sensitive comparison fails on all upper
TEST_F(StringEqualsMatcherTest_219, CaseSensitiveAllUpper_219) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("HELLO"));
}

// Test case-insensitive comparison matches same case
TEST_F(StringEqualsMatcherTest_219, CaseInsensitiveSameCase_219) {
    CasedString comparator("hello", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello"));
}

// Test case-insensitive comparison matches different case
TEST_F(StringEqualsMatcherTest_219, CaseInsensitiveDifferentCase_219) {
    CasedString comparator("hello", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("Hello"));
}

// Test case-insensitive comparison matches all upper
TEST_F(StringEqualsMatcherTest_219, CaseInsensitiveAllUpper_219) {
    CasedString comparator("hello", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("HELLO"));
}

// Test case-insensitive comparison fails on mismatch
TEST_F(StringEqualsMatcherTest_219, CaseInsensitiveMismatch_219) {
    CasedString comparator("hello", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("world"));
}

// Test empty string matches empty string (case-sensitive)
TEST_F(StringEqualsMatcherTest_219, EmptyStringMatchesCaseSensitive_219) {
    CasedString comparator("", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match(""));
}

// Test empty string matches empty string (case-insensitive)
TEST_F(StringEqualsMatcherTest_219, EmptyStringMatchesCaseInsensitive_219) {
    CasedString comparator("", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match(""));
}

// Test empty comparator does not match non-empty source
TEST_F(StringEqualsMatcherTest_219, EmptyComparatorNonEmptySource_219) {
    CasedString comparator("", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello"));
}

// Test non-empty comparator does not match empty source
TEST_F(StringEqualsMatcherTest_219, NonEmptyComparatorEmptySource_219) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match(""));
}

// Test with special characters
TEST_F(StringEqualsMatcherTest_219, SpecialCharactersCaseSensitive_219) {
    CasedString comparator("hello!@#$%^&*()", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello!@#$%^&*()"));
}

// Test with whitespace
TEST_F(StringEqualsMatcherTest_219, WhitespaceMatters_219) {
    CasedString comparator("hello ", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello"));
}

// Test with leading whitespace
TEST_F(StringEqualsMatcherTest_219, LeadingWhitespace_219) {
    CasedString comparator(" hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello"));
}

// Test substring is not equal
TEST_F(StringEqualsMatcherTest_219, SubstringNotEqual_219) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello world"));
}

// Test superstring is not equal
TEST_F(StringEqualsMatcherTest_219, SuperstringNotEqual_219) {
    CasedString comparator("hello world", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_FALSE(matcher.match("hello"));
}

// Test describe method contains relevant info
TEST_F(StringEqualsMatcherTest_219, DescribeCaseSensitive_219) {
    CasedString comparator("hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    // The description should contain "equals" as the operation
    EXPECT_NE(description.find("equals"), std::string::npos);
    // Should contain the target string
    EXPECT_NE(description.find("hello"), std::string::npos);
}

// Test describe method for case-insensitive
TEST_F(StringEqualsMatcherTest_219, DescribeCaseInsensitive_219) {
    CasedString comparator("hello", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    EXPECT_NE(description.find("equals"), std::string::npos);
}

// Test mixed case string case-insensitive
TEST_F(StringEqualsMatcherTest_219, MixedCaseInsensitive_219) {
    CasedString comparator("HeLLo WoRLd", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello world"));
    EXPECT_TRUE(matcher.match("HELLO WORLD"));
    EXPECT_TRUE(matcher.match("HeLLo WoRLd"));
}

// Test single character match
TEST_F(StringEqualsMatcherTest_219, SingleCharMatch_219) {
    CasedString comparator("a", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("a"));
    EXPECT_FALSE(matcher.match("A"));
    EXPECT_FALSE(matcher.match("b"));
    EXPECT_FALSE(matcher.match(""));
}

// Test single character case-insensitive
TEST_F(StringEqualsMatcherTest_219, SingleCharCaseInsensitive_219) {
    CasedString comparator("a", CaseSensitive::No);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("a"));
    EXPECT_TRUE(matcher.match("A"));
    EXPECT_FALSE(matcher.match("b"));
}

// Test with numeric string
TEST_F(StringEqualsMatcherTest_219, NumericString_219) {
    CasedString comparator("12345", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("12345"));
    EXPECT_FALSE(matcher.match("123456"));
    EXPECT_FALSE(matcher.match("1234"));
}

// Test with newline characters
TEST_F(StringEqualsMatcherTest_219, NewlineCharacters_219) {
    CasedString comparator("hello\nworld", CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match("hello\nworld"));
    EXPECT_FALSE(matcher.match("hello world"));
}

// Test with null character embedded in string
TEST_F(StringEqualsMatcherTest_219, EmbeddedNullCharacter_219) {
    std::string withNull("hello\0world", 11);
    CasedString comparator(withNull, CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match(withNull));
    EXPECT_FALSE(matcher.match("hello"));
}

// Test long string
TEST_F(StringEqualsMatcherTest_219, LongStringMatch_219) {
    std::string longStr(10000, 'a');
    CasedString comparator(longStr, CaseSensitive::Yes);
    StringEqualsMatcher matcher(comparator);
    EXPECT_TRUE(matcher.match(longStr));
    
    std::string almostSame(9999, 'a');
    EXPECT_FALSE(matcher.match(almostSame));
}
