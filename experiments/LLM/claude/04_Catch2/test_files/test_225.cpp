#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_string.hpp"

// Helper function to check if a matcher matches a given string
// We use the Catch2 matcher interface which provides a `match` method
// and a `describe` method.

class StringEqualsMatcherTest_225 : public ::testing::Test {
protected:
    // Helper to test matching
    bool matches(const Catch::Matchers::StringEqualsMatcher& matcher, const std::string& input) {
        return matcher.match(input);
    }
};

// Test: Exact match with case-sensitive (default)
TEST_F(StringEqualsMatcherTest_225, ExactMatchCaseSensitive_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(matches(matcher, "hello"));
}

// Test: Case mismatch with case-sensitive comparison should fail
TEST_F(StringEqualsMatcherTest_225, CaseMismatchCaseSensitive_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matches(matcher, "Hello"));
}

// Test: Case mismatch with case-insensitive comparison should succeed
TEST_F(StringEqualsMatcherTest_225, CaseMismatchCaseInsensitive_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::No);
    EXPECT_TRUE(matches(matcher, "Hello"));
}

// Test: Completely different strings should not match
TEST_F(StringEqualsMatcherTest_225, DifferentStringsCaseSensitive_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matches(matcher, "world"));
}

// Test: Completely different strings should not match even case-insensitive
TEST_F(StringEqualsMatcherTest_225, DifferentStringsCaseInsensitive_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::No);
    EXPECT_FALSE(matches(matcher, "world"));
}

// Test: Empty string matches empty string
TEST_F(StringEqualsMatcherTest_225, EmptyStringMatchesEmpty_225) {
    auto matcher = Catch::Matchers::Equals("", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(matches(matcher, ""));
}

// Test: Empty string does not match non-empty string
TEST_F(StringEqualsMatcherTest_225, EmptyStringDoesNotMatchNonEmpty_225) {
    auto matcher = Catch::Matchers::Equals("", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matches(matcher, "hello"));
}

// Test: Non-empty string does not match empty string
TEST_F(StringEqualsMatcherTest_225, NonEmptyStringDoesNotMatchEmpty_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matches(matcher, ""));
}

// Test: Case insensitive with all uppercase vs all lowercase
TEST_F(StringEqualsMatcherTest_225, AllUpperVsAllLowerCaseInsensitive_225) {
    auto matcher = Catch::Matchers::Equals("HELLO", Catch::CaseSensitive::No);
    EXPECT_TRUE(matches(matcher, "hello"));
}

// Test: Case insensitive with mixed case
TEST_F(StringEqualsMatcherTest_225, MixedCaseCaseInsensitive_225) {
    auto matcher = Catch::Matchers::Equals("HeLLo", Catch::CaseSensitive::No);
    EXPECT_TRUE(matches(matcher, "hEllO"));
}

// Test: Substring should not match (shorter input)
TEST_F(StringEqualsMatcherTest_225, SubstringDoesNotMatch_225) {
    auto matcher = Catch::Matchers::Equals("hello world", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matches(matcher, "hello"));
}

// Test: Superstring should not match (longer input)
TEST_F(StringEqualsMatcherTest_225, SuperstringDoesNotMatch_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matches(matcher, "hello world"));
}

// Test: String with special characters
TEST_F(StringEqualsMatcherTest_225, SpecialCharacters_225) {
    auto matcher = Catch::Matchers::Equals("hello\nworld\t!", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(matches(matcher, "hello\nworld\t!"));
}

// Test: String with spaces
TEST_F(StringEqualsMatcherTest_225, StringWithSpaces_225) {
    auto matcher = Catch::Matchers::Equals("  hello  ", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(matches(matcher, "  hello  "));
    EXPECT_FALSE(matches(matcher, "hello"));
}

// Test: describe method returns a non-empty description
TEST_F(StringEqualsMatcherTest_225, DescribeReturnsNonEmpty_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::Yes);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: describe method for case-insensitive returns a non-empty description
TEST_F(StringEqualsMatcherTest_225, DescribeCaseInsensitiveReturnsNonEmpty_225) {
    auto matcher = Catch::Matchers::Equals("hello", Catch::CaseSensitive::No);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test: Default case sensitivity (should be CaseSensitive::Yes based on typical Catch2 behavior)
TEST_F(StringEqualsMatcherTest_225, DefaultCaseSensitivity_225) {
    auto matcher = Catch::Matchers::Equals("hello");
    EXPECT_TRUE(matches(matcher, "hello"));
    EXPECT_FALSE(matches(matcher, "Hello"));
}

// Test: Single character strings
TEST_F(StringEqualsMatcherTest_225, SingleCharacterMatch_225) {
    auto matcher = Catch::Matchers::Equals("a", Catch::CaseSensitive::Yes);
    EXPECT_TRUE(matches(matcher, "a"));
    EXPECT_FALSE(matches(matcher, "A"));
}

// Test: Single character case insensitive
TEST_F(StringEqualsMatcherTest_225, SingleCharacterCaseInsensitive_225) {
    auto matcher = Catch::Matchers::Equals("a", Catch::CaseSensitive::No);
    EXPECT_TRUE(matches(matcher, "A"));
    EXPECT_TRUE(matches(matcher, "a"));
}

// Test: Strings with numbers (case sensitivity shouldn't affect digits)
TEST_F(StringEqualsMatcherTest_225, StringWithDigitsCaseInsensitive_225) {
    auto matcher = Catch::Matchers::Equals("abc123", Catch::CaseSensitive::No);
    EXPECT_TRUE(matches(matcher, "ABC123"));
    EXPECT_TRUE(matches(matcher, "abc123"));
}

// Test: Same string reference scenario
TEST_F(StringEqualsMatcherTest_225, SameStringExactMatch_225) {
    std::string str = "test string";
    auto matcher = Catch::Matchers::Equals(str, Catch::CaseSensitive::Yes);
    EXPECT_TRUE(matches(matcher, str));
}
