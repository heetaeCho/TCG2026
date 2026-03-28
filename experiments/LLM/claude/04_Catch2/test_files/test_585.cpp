#include <gtest/gtest.h>
#include "catch2/internal/catch_string_manip.hpp"
#include "catch2/internal/catch_stringref.hpp"

class StartsWithCharTest_585 : public ::testing::Test {
protected:
    // Setup if needed
};

// Test that startsWith returns true when the string starts with the given prefix character
TEST_F(StartsWithCharTest_585, ReturnsTrueWhenFirstCharMatchesPrefix_585) {
    Catch::StringRef s("hello");
    EXPECT_TRUE(Catch::startsWith(s, 'h'));
}

// Test that startsWith returns false when the string starts with a different character
TEST_F(StartsWithCharTest_585, ReturnsFalseWhenFirstCharDoesNotMatchPrefix_585) {
    Catch::StringRef s("hello");
    EXPECT_FALSE(Catch::startsWith(s, 'x'));
}

// Test that startsWith returns false for an empty string
TEST_F(StartsWithCharTest_585, ReturnsFalseForEmptyString_585) {
    Catch::StringRef s("");
    EXPECT_FALSE(Catch::startsWith(s, 'a'));
}

// Test that startsWith returns false for a default-constructed (empty) StringRef
TEST_F(StartsWithCharTest_585, ReturnsFalseForDefaultConstructedStringRef_585) {
    Catch::StringRef s;
    EXPECT_FALSE(Catch::startsWith(s, 'a'));
}

// Test that startsWith works with a single-character string that matches the prefix
TEST_F(StartsWithCharTest_585, ReturnsTrueForSingleCharStringMatchingPrefix_585) {
    Catch::StringRef s("a");
    EXPECT_TRUE(Catch::startsWith(s, 'a'));
}

// Test that startsWith works with a single-character string that does not match the prefix
TEST_F(StartsWithCharTest_585, ReturnsFalseForSingleCharStringNotMatchingPrefix_585) {
    Catch::StringRef s("b");
    EXPECT_FALSE(Catch::startsWith(s, 'a'));
}

// Test that startsWith is case-sensitive
TEST_F(StartsWithCharTest_585, IsCaseSensitive_585) {
    Catch::StringRef s("Hello");
    EXPECT_TRUE(Catch::startsWith(s, 'H'));
    EXPECT_FALSE(Catch::startsWith(s, 'h'));
}

// Test that startsWith works with special characters
TEST_F(StartsWithCharTest_585, WorksWithSpecialCharacters_585) {
    Catch::StringRef s("!special");
    EXPECT_TRUE(Catch::startsWith(s, '!'));
    EXPECT_FALSE(Catch::startsWith(s, 's'));
}

// Test that startsWith works with a space character as prefix
TEST_F(StartsWithCharTest_585, WorksWithSpaceCharacter_585) {
    Catch::StringRef s(" leading space");
    EXPECT_TRUE(Catch::startsWith(s, ' '));
}

// Test that startsWith works with null character as prefix on non-empty string
TEST_F(StartsWithCharTest_585, ReturnsFalseForNullCharPrefixOnNonEmptyString_585) {
    Catch::StringRef s("hello");
    EXPECT_FALSE(Catch::startsWith(s, '\0'));
}

// Test with a numeric character prefix
TEST_F(StartsWithCharTest_585, WorksWithNumericCharacter_585) {
    Catch::StringRef s("123abc");
    EXPECT_TRUE(Catch::startsWith(s, '1'));
    EXPECT_FALSE(Catch::startsWith(s, '2'));
}

// Test startsWith with a string constructed from std::string
TEST_F(StartsWithCharTest_585, WorksWithStdStringConstructedStringRef_585) {
    std::string str = "test";
    Catch::StringRef s(str);
    EXPECT_TRUE(Catch::startsWith(s, 't'));
    EXPECT_FALSE(Catch::startsWith(s, 'T'));
}

// Test with newline character
TEST_F(StartsWithCharTest_585, WorksWithNewlineCharacter_585) {
    Catch::StringRef s("\nline");
    EXPECT_TRUE(Catch::startsWith(s, '\n'));
    EXPECT_FALSE(Catch::startsWith(s, 'l'));
}

// Test with tab character
TEST_F(StartsWithCharTest_585, WorksWithTabCharacter_585) {
    Catch::StringRef s("\ttabbed");
    EXPECT_TRUE(Catch::startsWith(s, '\t'));
}

// Test empty prefix character (null char) on empty string
TEST_F(StartsWithCharTest_585, ReturnsFalseForNullCharOnEmptyString_585) {
    Catch::StringRef s("");
    EXPECT_FALSE(Catch::startsWith(s, '\0'));
}
