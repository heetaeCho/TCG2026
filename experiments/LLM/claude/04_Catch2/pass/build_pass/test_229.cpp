#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/catch_tostring.hpp"
#include <string>

// Test RegexMatcher created via Matches factory function
class MatchesTest_229 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: simple regex match
TEST_F(MatchesTest_229, SimpleRegexMatchesString_229) {
    auto matcher = Catch::Matchers::Matches("hello");
    EXPECT_TRUE(matcher.match("hello"));
}

// Normal operation: regex with wildcard
TEST_F(MatchesTest_229, RegexWithWildcardMatches_229) {
    auto matcher = Catch::Matchers::Matches("hel.*");
    EXPECT_TRUE(matcher.match("hello world"));
}

// Normal operation: regex does not match
TEST_F(MatchesTest_229, RegexDoesNotMatch_229) {
    auto matcher = Catch::Matchers::Matches("^hello$");
    EXPECT_FALSE(matcher.match("hello world"));
}

// Normal operation: exact match with anchors
TEST_F(MatchesTest_229, ExactMatchWithAnchors_229) {
    auto matcher = Catch::Matchers::Matches("^hello$");
    EXPECT_TRUE(matcher.match("hello"));
}

// Case sensitivity: case sensitive by default
TEST_F(MatchesTest_229, CaseSensitiveByDefault_229) {
    auto matcher = Catch::Matchers::Matches("hello");
    EXPECT_FALSE(matcher.match("HELLO"));
}

// Case sensitivity: case insensitive matching
TEST_F(MatchesTest_229, CaseInsensitiveMatch_229) {
    auto matcher = Catch::Matchers::Matches("hello", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("HELLO"));
}

// Case sensitivity: case insensitive with mixed case
TEST_F(MatchesTest_229, CaseInsensitiveMixedCase_229) {
    auto matcher = Catch::Matchers::Matches("hello", Catch::CaseSensitive::No);
    EXPECT_TRUE(matcher.match("HeLlO"));
}

// Case sensitivity: explicit case sensitive
TEST_F(MatchesTest_229, ExplicitCaseSensitive_229) {
    auto matcher = Catch::Matchers::Matches("hello", Catch::CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match("HELLO"));
}

// Boundary: empty string with matching regex
TEST_F(MatchesTest_229, EmptyStringMatchesEmptyRegex_229) {
    auto matcher = Catch::Matchers::Matches("^$");
    EXPECT_TRUE(matcher.match(""));
}

// Boundary: empty string with non-matching regex
TEST_F(MatchesTest_229, EmptyStringDoesNotMatchNonEmptyRegex_229) {
    auto matcher = Catch::Matchers::Matches("hello");
    EXPECT_FALSE(matcher.match(""));
}

// Boundary: regex matching any string
TEST_F(MatchesTest_229, RegexMatchesAnyString_229) {
    auto matcher = Catch::Matchers::Matches(".*");
    EXPECT_TRUE(matcher.match("anything goes here"));
}

// Boundary: empty regex matches empty string
TEST_F(MatchesTest_229, EmptyRegexMatchesEmptyString_229) {
    auto matcher = Catch::Matchers::Matches("");
    EXPECT_TRUE(matcher.match(""));
}

// Normal operation: regex with character classes
TEST_F(MatchesTest_229, RegexWithCharacterClasses_229) {
    auto matcher = Catch::Matchers::Matches("[0-9]+");
    EXPECT_TRUE(matcher.match("12345"));
}

// Normal operation: regex with character classes doesn't match letters
TEST_F(MatchesTest_229, RegexWithCharacterClassesNoMatch_229) {
    auto matcher = Catch::Matchers::Matches("^[0-9]+$");
    EXPECT_FALSE(matcher.match("abc"));
}

// Normal operation: complex regex
TEST_F(MatchesTest_229, ComplexRegexMatch_229) {
    auto matcher = Catch::Matchers::Matches("^[a-z]+@[a-z]+\\.[a-z]+$");
    EXPECT_TRUE(matcher.match("test@example.com"));
}

// Normal operation: regex with alternation
TEST_F(MatchesTest_229, RegexWithAlternation_229) {
    auto matcher = Catch::Matchers::Matches("cat|dog");
    EXPECT_TRUE(matcher.match("cat"));
    EXPECT_TRUE(matcher.match("dog"));
}

// Verify describe() returns a meaningful string
TEST_F(MatchesTest_229, DescribeReturnsMeaningfulString_229) {
    auto matcher = Catch::Matchers::Matches("hello");
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
    // The description should contain the regex pattern
    EXPECT_NE(description.find("hello"), std::string::npos);
}

// Case insensitive describe mentions case
TEST_F(MatchesTest_229, CaseInsensitiveDescribeMentionsCase_229) {
    auto matcher = Catch::Matchers::Matches("hello", Catch::CaseSensitive::No);
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Normal operation: partial match (regex not anchored)
TEST_F(MatchesTest_229, PartialMatchBehavior_229) {
    auto matcher = Catch::Matchers::Matches("hello");
    // Depending on implementation, unanchored regex may or may not match substrings
    // We test that "hello" matches "hello"
    EXPECT_TRUE(matcher.match("hello"));
}

// Boundary: special characters in input string
TEST_F(MatchesTest_229, SpecialCharsInInput_229) {
    auto matcher = Catch::Matchers::Matches("\\$\\d+\\.\\d+");
    EXPECT_TRUE(matcher.match("$10.99"));
}

// Boundary: regex with quantifiers
TEST_F(MatchesTest_229, RegexWithQuantifiers_229) {
    auto matcher = Catch::Matchers::Matches("^a{3}$");
    EXPECT_TRUE(matcher.match("aaa"));
    EXPECT_FALSE(matcher.match("aa"));
    EXPECT_FALSE(matcher.match("aaaa"));
}

// Normal: regex with groups
TEST_F(MatchesTest_229, RegexWithGroups_229) {
    auto matcher = Catch::Matchers::Matches("^(ab)+$");
    EXPECT_TRUE(matcher.match("ababab"));
    EXPECT_FALSE(matcher.match("abc"));
}
