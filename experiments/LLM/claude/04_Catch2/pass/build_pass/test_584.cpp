#include <gtest/gtest.h>
#include <string>

// Declare the function under test
namespace Catch {
    bool startsWith(std::string const& s, std::string const& prefix);
}

// Normal operation tests

TEST(StartsWithTest_584, ReturnsTrueWhenStringStartsWithPrefix_584) {
    EXPECT_TRUE(Catch::startsWith("Hello, World!", "Hello"));
}

TEST(StartsWithTest_584, ReturnsFalseWhenStringDoesNotStartWithPrefix_584) {
    EXPECT_FALSE(Catch::startsWith("Hello, World!", "World"));
}

TEST(StartsWithTest_584, ReturnsTrueWhenPrefixIsEmpty_584) {
    EXPECT_TRUE(Catch::startsWith("Hello", ""));
}

TEST(StartsWithTest_584, ReturnsTrueWhenBothAreEmpty_584) {
    EXPECT_TRUE(Catch::startsWith("", ""));
}

TEST(StartsWithTest_584, ReturnsFalseWhenStringIsEmptyAndPrefixIsNot_584) {
    EXPECT_FALSE(Catch::startsWith("", "prefix"));
}

TEST(StartsWithTest_584, ReturnsTrueWhenStringEqualsPrefix_584) {
    EXPECT_TRUE(Catch::startsWith("exact", "exact"));
}

TEST(StartsWithTest_584, ReturnsFalseWhenPrefixIsLongerThanString_584) {
    EXPECT_FALSE(Catch::startsWith("short", "shortprefix"));
}

// Boundary conditions

TEST(StartsWithTest_584, SingleCharacterStringMatchesSingleCharacterPrefix_584) {
    EXPECT_TRUE(Catch::startsWith("a", "a"));
}

TEST(StartsWithTest_584, SingleCharacterStringDoesNotMatchDifferentPrefix_584) {
    EXPECT_FALSE(Catch::startsWith("a", "b"));
}

TEST(StartsWithTest_584, PrefixOfLengthOneMatchesFirstCharacter_584) {
    EXPECT_TRUE(Catch::startsWith("abc", "a"));
}

TEST(StartsWithTest_584, PrefixOfLengthOneDoesNotMatchIfDifferent_584) {
    EXPECT_FALSE(Catch::startsWith("abc", "b"));
}

TEST(StartsWithTest_584, CaseSensitiveComparison_584) {
    EXPECT_FALSE(Catch::startsWith("Hello", "hello"));
}

TEST(StartsWithTest_584, CaseSensitiveComparisonUpperCase_584) {
    EXPECT_FALSE(Catch::startsWith("hello", "Hello"));
}

TEST(StartsWithTest_584, StringWithSpacesPrefix_584) {
    EXPECT_TRUE(Catch::startsWith("  hello", "  "));
}

TEST(StartsWithTest_584, PrefixWithSpecialCharacters_584) {
    EXPECT_TRUE(Catch::startsWith("!@#$%^&*()", "!@#"));
}

TEST(StartsWithTest_584, PrefixDiffersAtLastCharacter_584) {
    EXPECT_FALSE(Catch::startsWith("abcde", "abcdf"));
}

TEST(StartsWithTest_584, LongStringWithShortPrefix_584) {
    std::string longStr(10000, 'x');
    EXPECT_TRUE(Catch::startsWith(longStr, "x"));
}

TEST(StartsWithTest_584, LongStringWithLongMatchingPrefix_584) {
    std::string longStr(10000, 'x');
    std::string prefix(5000, 'x');
    EXPECT_TRUE(Catch::startsWith(longStr, prefix));
}

TEST(StartsWithTest_584, LongStringWithLongNonMatchingPrefix_584) {
    std::string longStr(10000, 'x');
    std::string prefix(5000, 'x');
    prefix.back() = 'y';
    EXPECT_FALSE(Catch::startsWith(longStr, prefix));
}

TEST(StartsWithTest_584, NullCharacterInString_584) {
    std::string s("ab\0cd", 5);
    std::string prefix("ab\0", 3);
    EXPECT_TRUE(Catch::startsWith(s, prefix));
}

TEST(StartsWithTest_584, PrefixExactlySameLengthButDifferent_584) {
    EXPECT_FALSE(Catch::startsWith("abcd", "abce"));
}

TEST(StartsWithTest_584, PrefixOneLongerThanString_584) {
    EXPECT_FALSE(Catch::startsWith("abc", "abcd"));
}
