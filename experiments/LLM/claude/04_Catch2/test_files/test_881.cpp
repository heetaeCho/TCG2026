#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
bool starts_with(std::string const& str, std::string const& pref);

// Normal operation tests

TEST(StartsWithTest_881, ReturnsTrueWhenStringStartsWithPrefix_881) {
    EXPECT_TRUE(starts_with("hello world", "hello"));
}

TEST(StartsWithTest_881, ReturnsTrueWhenPrefixIsEntireString_881) {
    EXPECT_TRUE(starts_with("hello", "hello"));
}

TEST(StartsWithTest_881, ReturnsFalseWhenStringDoesNotStartWithPrefix_881) {
    EXPECT_FALSE(starts_with("hello world", "world"));
}

TEST(StartsWithTest_881, ReturnsTrueWhenPrefixIsEmpty_881) {
    EXPECT_TRUE(starts_with("hello", ""));
}

TEST(StartsWithTest_881, ReturnsTrueWhenBothAreEmpty_881) {
    EXPECT_TRUE(starts_with("", ""));
}

TEST(StartsWithTest_881, ReturnsFalseWhenStringIsEmptyAndPrefixIsNot_881) {
    EXPECT_FALSE(starts_with("", "hello"));
}

TEST(StartsWithTest_881, ReturnsFalseWhenPrefixIsLongerThanString_881) {
    EXPECT_FALSE(starts_with("hi", "hello"));
}

TEST(StartsWithTest_881, ReturnsTrueWithSingleCharacterPrefix_881) {
    EXPECT_TRUE(starts_with("abc", "a"));
}

TEST(StartsWithTest_881, ReturnsFalseWithSingleCharacterPrefixNotMatching_881) {
    EXPECT_FALSE(starts_with("abc", "b"));
}

TEST(StartsWithTest_881, ReturnsTrueWithSingleCharacterStringAndPrefix_881) {
    EXPECT_TRUE(starts_with("a", "a"));
}

TEST(StartsWithTest_881, ReturnsFalseWithSingleCharacterStringAndDifferentPrefix_881) {
    EXPECT_FALSE(starts_with("a", "b"));
}

// Case sensitivity tests

TEST(StartsWithTest_881, IsCaseSensitive_881) {
    EXPECT_FALSE(starts_with("Hello", "hello"));
}

TEST(StartsWithTest_881, IsCaseSensitiveReverse_881) {
    EXPECT_FALSE(starts_with("hello", "Hello"));
}

// Substring presence but not at start

TEST(StartsWithTest_881, ReturnsFalseWhenPrefixExistsButNotAtStart_881) {
    EXPECT_FALSE(starts_with("say hello", "hello"));
}

// Special characters

TEST(StartsWithTest_881, WorksWithSpecialCharacters_881) {
    EXPECT_TRUE(starts_with("!@#$%^&*()", "!@#"));
}

TEST(StartsWithTest_881, WorksWithSpacesAsPrefix_881) {
    EXPECT_TRUE(starts_with("  hello", "  "));
}

TEST(StartsWithTest_881, WorksWithNewlineCharacters_881) {
    EXPECT_TRUE(starts_with("\nhello", "\n"));
}

TEST(StartsWithTest_881, WorksWithNullCharacterInString_881) {
    std::string str("ab\0cd", 5);
    std::string pref("ab\0", 3);
    EXPECT_TRUE(starts_with(str, pref));
}

TEST(StartsWithTest_881, ReturnsFalseWithNullCharacterMismatch_881) {
    std::string str("ab\0cd", 5);
    std::string pref("ab\0ce", 5);
    EXPECT_FALSE(starts_with(str, pref));
}

// Repeated characters

TEST(StartsWithTest_881, WorksWithRepeatedCharacters_881) {
    EXPECT_TRUE(starts_with("aaabbb", "aaa"));
}

TEST(StartsWithTest_881, ReturnsFalseWithPartialRepeatedMatch_881) {
    EXPECT_FALSE(starts_with("aabbb", "aaa"));
}

// Long strings

TEST(StartsWithTest_881, WorksWithLongStrings_881) {
    std::string longStr(10000, 'x');
    std::string longPref(5000, 'x');
    EXPECT_TRUE(starts_with(longStr, longPref));
}

TEST(StartsWithTest_881, ReturnsFalseWithLongStringMismatchAtEnd_881) {
    std::string longStr(10000, 'x');
    std::string longPref(5000, 'x');
    longPref.back() = 'y';
    EXPECT_FALSE(starts_with(longStr, longPref));
}

// Numeric strings

TEST(StartsWithTest_881, WorksWithNumericStrings_881) {
    EXPECT_TRUE(starts_with("12345", "123"));
}

TEST(StartsWithTest_881, ReturnsFalseWithDifferentNumericStrings_881) {
    EXPECT_FALSE(starts_with("12345", "124"));
}
