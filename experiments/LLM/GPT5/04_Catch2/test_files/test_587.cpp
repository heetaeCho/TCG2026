// ends_with_tests_587.cpp
#include <gtest/gtest.h>
#include <string>

// Production declaration (treat as black box; do not include implementation)
namespace Catch {
    bool endsWith(std::string const& s, char suffix);
}

class EndsWithTest_587 : public ::testing::Test {};

// Normal operation: returns true when last character matches
TEST_F(EndsWithTest_587, ReturnsTrue_WhenStringEndsWithChar_587) {
    EXPECT_TRUE(Catch::endsWith(std::string("hello"), 'o'));
}

// Normal operation: returns false when last character does not match
TEST_F(EndsWithTest_587, ReturnsFalse_WhenStringDoesNotEndWithChar_587) {
    EXPECT_FALSE(Catch::endsWith(std::string("hello"), 'l'));
}

// Boundary: empty string should always return false
TEST_F(EndsWithTest_587, ReturnsFalse_WhenStringIsEmpty_587) {
    EXPECT_FALSE(Catch::endsWith(std::string(), 'x'));
}

// Boundary: single-character string that matches
TEST_F(EndsWithTest_587, ReturnsTrue_ForSingleCharacterStringMatching_587) {
    EXPECT_TRUE(Catch::endsWith(std::string("x"), 'x'));
}

// Boundary: single-character string that does not match
TEST_F(EndsWithTest_587, ReturnsFalse_ForSingleCharacterStringNotMatching_587) {
    EXPECT_FALSE(Catch::endsWith(std::string("x"), 'y'));
}

// Special char: trailing whitespace is a valid character
TEST_F(EndsWithTest_587, WorksWithWhitespaceSuffix_587) {
    EXPECT_TRUE(Catch::endsWith(std::string("trail "), ' '));
    EXPECT_FALSE(Catch::endsWith(std::string("trail\t"), ' '));
}

// Exceptional/edge (observable): string ending with a null byte
TEST_F(EndsWithTest_587, HandlesNullCharacterSuffix_MatchingAtEnd_587) {
    std::string s = {'a','b','c','\0'};
    ASSERT_EQ(s.size(), 4u);  // ensure null is part of the string
    EXPECT_TRUE(Catch::endsWith(s, '\0'));
}

// Edge: embedded nulls should be ignored except for the last character
TEST_F(EndsWithTest_587, IgnoresEmbeddedNulls_OnlyConsidersLastChar_587) {
    std::string s = {'a','\0','b'};
    EXPECT_FALSE(Catch::endsWith(s, '\0'));
    EXPECT_TRUE(Catch::endsWith(s, 'b'));
}

// Normal with UTF-8 content earlier: multi-byte characters before ASCII suffix
TEST_F(EndsWithTest_587, WorksWithMultiByteUtf8EarlierCharacters_587) {
    std::string s = u8"한글!";  // UTF-8 multibyte chars, ASCII '!' at end
    EXPECT_TRUE(Catch::endsWith(s, '!'));
}
