#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
namespace Catch {
    bool endsWith(std::string const& s, char suffix);
}

// Normal operation tests

TEST(EndsWithTest_587, ReturnsTrueWhenStringEndsWithSuffix_587) {
    EXPECT_TRUE(Catch::endsWith("hello", 'o'));
}

TEST(EndsWithTest_587, ReturnsFalseWhenStringDoesNotEndWithSuffix_587) {
    EXPECT_FALSE(Catch::endsWith("hello", 'x'));
}

TEST(EndsWithTest_587, ReturnsTrueForSingleCharacterMatchingSuffix_587) {
    EXPECT_TRUE(Catch::endsWith("a", 'a'));
}

TEST(EndsWithTest_587, ReturnsFalseForSingleCharacterNotMatchingSuffix_587) {
    EXPECT_FALSE(Catch::endsWith("a", 'b'));
}

TEST(EndsWithTest_587, ReturnsTrueWhenLastCharIsSpace_587) {
    EXPECT_TRUE(Catch::endsWith("hello ", ' '));
}

TEST(EndsWithTest_587, ReturnsTrueWhenLastCharIsNewline_587) {
    EXPECT_TRUE(Catch::endsWith("hello\n", '\n'));
}

TEST(EndsWithTest_587, ReturnsTrueWhenLastCharIsNullCharacter_587) {
    std::string s("hello\0", 6);
    EXPECT_TRUE(Catch::endsWith(s, '\0'));
}

TEST(EndsWithTest_587, ReturnsTrueForStringEndingWithSlash_587) {
    EXPECT_TRUE(Catch::endsWith("/path/to/dir/", '/'));
}

TEST(EndsWithTest_587, ReturnsFalseWhenSuffixIsFirstCharButNotLast_587) {
    EXPECT_FALSE(Catch::endsWith("abcdef", 'a'));
}

TEST(EndsWithTest_587, ReturnsTrueForRepeatedCharacters_587) {
    EXPECT_TRUE(Catch::endsWith("aaaa", 'a'));
}

// Boundary condition tests

TEST(EndsWithTest_587, ReturnsFalseForEmptyString_587) {
    EXPECT_FALSE(Catch::endsWith("", 'a'));
}

TEST(EndsWithTest_587, ReturnsFalseForEmptyStringWithNullSuffix_587) {
    EXPECT_FALSE(Catch::endsWith("", '\0'));
}

TEST(EndsWithTest_587, CaseSensitiveCheck_587) {
    EXPECT_FALSE(Catch::endsWith("Hello", 'O'));
    EXPECT_TRUE(Catch::endsWith("Hello", 'o'));
}

TEST(EndsWithTest_587, CaseSensitiveCheckUpperCase_587) {
    EXPECT_TRUE(Catch::endsWith("HellO", 'O'));
    EXPECT_FALSE(Catch::endsWith("HellO", 'o'));
}

TEST(EndsWithTest_587, LongStringEndsWith_587) {
    std::string longStr(10000, 'x');
    longStr.back() = 'z';
    EXPECT_TRUE(Catch::endsWith(longStr, 'z'));
    EXPECT_FALSE(Catch::endsWith(longStr, 'x'));
}

TEST(EndsWithTest_587, StringWithSpecialCharacters_587) {
    EXPECT_TRUE(Catch::endsWith("test!", '!'));
    EXPECT_TRUE(Catch::endsWith("test?", '?'));
    EXPECT_TRUE(Catch::endsWith("test.", '.'));
}

TEST(EndsWithTest_587, NumericSuffix_587) {
    EXPECT_TRUE(Catch::endsWith("test123", '3'));
    EXPECT_FALSE(Catch::endsWith("test123", '1'));
}

TEST(EndsWithTest_587, StringWithEmbeddedNulls_587) {
    std::string s;
    s.push_back('a');
    s.push_back('\0');
    s.push_back('b');
    EXPECT_TRUE(Catch::endsWith(s, 'b'));
    EXPECT_FALSE(Catch::endsWith(s, '\0'));
    EXPECT_FALSE(Catch::endsWith(s, 'a'));
}
