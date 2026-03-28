// starts_with_tests_584.cpp
#include <gtest/gtest.h>
#include <string>

// Pull in the implementation so we can call Catch::startsWith.
// (If your project exposes a header for this, prefer including that header.)
#include "Catch2/src/catch2/internal/catch_string_manip.cpp"

using Catch::startsWith;

namespace {

// ----------------------------
// Normal behavior
// ----------------------------

TEST(StartsWithTest_584, ReturnsTrueWhenPrefixMatchesAtStart_584) {
    EXPECT_TRUE(startsWith(std::string("Hello, world!"), std::string("Hello")));
}

TEST(StartsWithTest_584, ReturnsFalseWhenPrefixDoesNotMatchAtStart_584) {
    EXPECT_FALSE(startsWith(std::string("Hello, world!"), std::string("world")));
}

TEST(StartsWithTest_584, CaseSensitivityIsEnforced_584) {
    EXPECT_FALSE(startsWith(std::string("Hello"), std::string("hello")));
    EXPECT_TRUE(startsWith(std::string("Hello"), std::string("He")));
}

// ----------------------------
// Boundary conditions
// ----------------------------

TEST(StartsWithTest_584, EmptyPrefixAlwaysMatches_584) {
    EXPECT_TRUE(startsWith(std::string(""), std::string("")));
    EXPECT_TRUE(startsWith(std::string("abc"), std::string("")));
}

TEST(StartsWithTest_584, EmptyStringWithNonEmptyPrefixDoesNotMatch_584) {
    EXPECT_FALSE(startsWith(std::string(""), std::string("a")));
}

TEST(StartsWithTest_584, PrefixEqualToWholeStringMatches_584) {
    EXPECT_TRUE(startsWith(std::string("abc"), std::string("abc")));
}

TEST(StartsWithTest_584, PrefixLongerThanStringDoesNotMatch_584) {
    EXPECT_FALSE(startsWith(std::string("ab"), std::string("abc")));
}

TEST(StartsWithTest_584, MismatchAfterInitialCharactersDoesNotMatch_584) {
    EXPECT_FALSE(startsWith(std::string("abcd"), std::string("abX")));
}

// ----------------------------
// Special characters / whitespace
// ----------------------------

TEST(StartsWithTest_584, WhitespaceAndSymbolsHandledCorrectly_584) {
    EXPECT_TRUE(startsWith(std::string("  \t#tag"), std::string("  \t")));
    EXPECT_TRUE(startsWith(std::string("!@#$%^&*()"), std::string("!@#")));
    EXPECT_FALSE(startsWith(std::string("  abc"), std::string(" abc"))); // leading counts
}

// ----------------------------
// UTF-8 (byte-wise) behavior
// ----------------------------

TEST(StartsWithTest_584, Utf8PrefixMatch_584) {
    // UTF-8 Korean: "안녕하세요" starts with "안녕"
    const std::string s = u8"안녕하세요";
    const std::string prefix = u8"안녕";
    EXPECT_TRUE(startsWith(s, prefix));
}

TEST(StartsWithTest_584, Utf8PrefixMismatch_584) {
    // Similar-looking but different bytes: "안녕하세요" does NOT start with "안뇽"
    const std::string s = u8"안녕하세요";
    const std::string prefix = u8"안뇽";
    EXPECT_FALSE(startsWith(s, prefix));
}

// ----------------------------
// Larger inputs
// ----------------------------

TEST(StartsWithTest_584, LargeStringWithShortPrefix_584) {
    std::string large(10000, 'a');
    EXPECT_TRUE(startsWith(large, std::string("aaa")));
    EXPECT_FALSE(startsWith(large, std::string("aab")));
}

} // namespace
