#include <gtest/gtest.h>
#include <string>

// Declare the function under test
namespace Catch {
    bool endsWith(std::string const& s, std::string const& suffix);
}

// Normal operation tests

TEST(EndsWithTest_586, ReturnsTrueWhenStringEndsWithSuffix_586) {
    EXPECT_TRUE(Catch::endsWith("hello world", "world"));
}

TEST(EndsWithTest_586, ReturnsTrueWhenStringEndsWithSingleChar_586) {
    EXPECT_TRUE(Catch::endsWith("hello", "o"));
}

TEST(EndsWithTest_586, ReturnsFalseWhenStringDoesNotEndWithSuffix_586) {
    EXPECT_FALSE(Catch::endsWith("hello world", "hello"));
}

TEST(EndsWithTest_586, ReturnsTrueWhenSuffixEqualsString_586) {
    EXPECT_TRUE(Catch::endsWith("exact", "exact"));
}

TEST(EndsWithTest_586, ReturnsTrueWhenSuffixIsEmpty_586) {
    EXPECT_TRUE(Catch::endsWith("hello", ""));
}

TEST(EndsWithTest_586, ReturnsTrueWhenBothAreEmpty_586) {
    EXPECT_TRUE(Catch::endsWith("", ""));
}

TEST(EndsWithTest_586, ReturnsFalseWhenStringIsEmptyAndSuffixIsNot_586) {
    EXPECT_FALSE(Catch::endsWith("", "suffix"));
}

// Boundary conditions

TEST(EndsWithTest_586, ReturnsFalseWhenSuffixIsLongerThanString_586) {
    EXPECT_FALSE(Catch::endsWith("hi", "hello"));
}

TEST(EndsWithTest_586, ReturnsTrueForSingleCharMatchingString_586) {
    EXPECT_TRUE(Catch::endsWith("a", "a"));
}

TEST(EndsWithTest_586, ReturnsFalseForSingleCharNonMatchingString_586) {
    EXPECT_FALSE(Catch::endsWith("a", "b"));
}

TEST(EndsWithTest_586, ReturnsFalseWhenSuffixAppearsInMiddleOnly_586) {
    EXPECT_FALSE(Catch::endsWith("abcdef", "bcd"));
}

TEST(EndsWithTest_586, ReturnsTrueForRepeatedPattern_586) {
    EXPECT_TRUE(Catch::endsWith("aaaa", "aa"));
}

TEST(EndsWithTest_586, CaseSensitiveCheck_586) {
    EXPECT_FALSE(Catch::endsWith("Hello World", "world"));
}

TEST(EndsWithTest_586, ReturnsTrueWithSpecialCharacters_586) {
    EXPECT_TRUE(Catch::endsWith("path/to/file.txt", ".txt"));
}

TEST(EndsWithTest_586, ReturnsFalseWithPartialSuffixMatch_586) {
    EXPECT_FALSE(Catch::endsWith("abcxyz", "wxyz"));
}

TEST(EndsWithTest_586, WorksWithSpaces_586) {
    EXPECT_TRUE(Catch::endsWith("hello ", " "));
}

TEST(EndsWithTest_586, ReturnsTrueEmptySuffixOnNonEmptyString_586) {
    EXPECT_TRUE(Catch::endsWith("nonempty", ""));
}

TEST(EndsWithTest_586, SuffixExactlyOneLonger_586) {
    EXPECT_FALSE(Catch::endsWith("abc", "xabc"));
}

TEST(EndsWithTest_586, WorksWithNewlineCharacters_586) {
    EXPECT_TRUE(Catch::endsWith("line\n", "\n"));
}

TEST(EndsWithTest_586, WorksWithNullCharactersInString_586) {
    std::string s("abc\0def", 7);
    std::string suffix("def", 3);
    EXPECT_TRUE(Catch::endsWith(s, suffix));
}

TEST(EndsWithTest_586, NullCharSuffixMismatch_586) {
    std::string s("abc\0def", 7);
    std::string suffix("xyz", 3);
    EXPECT_FALSE(Catch::endsWith(s, suffix));
}
