// File: case_insensitive_equal_to_tests_465.cpp

#include <gtest/gtest.h>

#include "Catch2/src/catch2/internal/catch_case_insensitive_comparisons.hpp"
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using Catch::Detail::CaseInsensitiveEqualTo;
using Catch::StringRef;

class CaseInsensitiveEqualToTest_465 : public ::testing::Test {
protected:
    CaseInsensitiveEqualTo cmp{};
};

// Normal operation: identical strings (same case) compare equal
TEST_F(CaseInsensitiveEqualToTest_465, Equal_SameCase_465) {
    EXPECT_TRUE(cmp(StringRef("alpha"), StringRef("alpha")));
    EXPECT_TRUE(cmp(StringRef(""), StringRef("")));
}

// Normal operation: identical letters with different case compare equal
TEST_F(CaseInsensitiveEqualToTest_465, Equal_DifferentCase_465) {
    EXPECT_TRUE(cmp(StringRef("AlphaBravo"), StringRef("alphabravo")));
    EXPECT_TRUE(cmp(StringRef("TeSt"), StringRef("tEsT")));
}

// Boundary: different lengths with same prefix are not equal
TEST_F(CaseInsensitiveEqualToTest_465, NotEqual_DifferentLengths_465) {
    EXPECT_FALSE(cmp(StringRef("abc"), StringRef("ab")));
    EXPECT_FALSE(cmp(StringRef("ABC"), StringRef("ABCD")));
}

// Error/negative path: different letters (ignoring case) are not equal
TEST_F(CaseInsensitiveEqualToTest_465, NotEqual_DifferentLetters_465) {
    EXPECT_FALSE(cmp(StringRef("alpha"), StringRef("alpHaX")));
    EXPECT_FALSE(cmp(StringRef("x"), StringRef("y")));
}

// Boundary: one empty, one non-empty -> not equal
TEST_F(CaseInsensitiveEqualToTest_465, OneEmpty_OneNonEmpty_NotEqual_465) {
    EXPECT_FALSE(cmp(StringRef(""), StringRef("a")));
    EXPECT_FALSE(cmp(StringRef("Z"), StringRef("")));
}

// Normal + punctuation/digits: non-alpha characters compare literally,
// letters compare case-insensitively
TEST_F(CaseInsensitiveEqualToTest_465, NonAlphaCharacters_LiteralMatch_465) {
    EXPECT_TRUE(cmp(StringRef("a-b_c.123"), StringRef("A-B_C.123")));
    EXPECT_FALSE(cmp(StringRef("a-b_c.123"), StringRef("A-B_c.123"))); // hyphen vs underscore differs
}

// Construction variety: works with std::string and const char*
TEST_F(CaseInsensitiveEqualToTest_465, WorksWithStdStringAndCharPtr_465) {
    std::string s1 = "MiXeD";
    const char* s2 = "mixed";
    EXPECT_TRUE(cmp(StringRef(s1), StringRef(s2)));

    std::string s3 = "data-42";
    const char* s4 = "DATA-43";
    EXPECT_FALSE(cmp(StringRef(s3), StringRef(s4)));
}
