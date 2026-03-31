#include <gtest/gtest.h>

// We need to access the static function IsHex from re2 namespace.
// Since it's a static function in a .cc file, we can't directly access it.
// We'll need to either include the source or redeclare it for testing purposes.
// However, following the constraints, we treat it as a black box and test via its interface.

// Since IsHex is a static function in parse.cc (internal linkage), we need to
// include the source file to access it for testing, or use a workaround.
// For unit testing a static function, we include the .cc file directly.

// Forward declare or include to get access to the static function
namespace re2 {
    // We replicate the declaration to test it. In practice, you'd include the source.
    static int IsHex(int c);
}

// Include the actual implementation
#include "re2/parse.cc"

class IsHexTest_517 : public ::testing::Test {
protected:
};

// Test decimal digits 0-9
TEST_F(IsHexTest_517, DecimalDigitsAreHex_517) {
    for (int c = '0'; c <= '9'; ++c) {
        EXPECT_TRUE(re2::IsHex(c)) << "Expected '" << static_cast<char>(c) << "' to be hex";
    }
}

// Test uppercase hex letters A-F
TEST_F(IsHexTest_517, UppercaseHexLettersAreHex_517) {
    for (int c = 'A'; c <= 'F'; ++c) {
        EXPECT_TRUE(re2::IsHex(c)) << "Expected '" << static_cast<char>(c) << "' to be hex";
    }
}

// Test lowercase hex letters a-f
TEST_F(IsHexTest_517, LowercaseHexLettersAreHex_517) {
    for (int c = 'a'; c <= 'f'; ++c) {
        EXPECT_TRUE(re2::IsHex(c)) << "Expected '" << static_cast<char>(c) << "' to be hex";
    }
}

// Test that uppercase letters G-Z are not hex
TEST_F(IsHexTest_517, UppercaseNonHexLettersAreNotHex_517) {
    for (int c = 'G'; c <= 'Z'; ++c) {
        EXPECT_FALSE(re2::IsHex(c)) << "Expected '" << static_cast<char>(c) << "' to NOT be hex";
    }
}

// Test that lowercase letters g-z are not hex
TEST_F(IsHexTest_517, LowercaseNonHexLettersAreNotHex_517) {
    for (int c = 'g'; c <= 'z'; ++c) {
        EXPECT_FALSE(re2::IsHex(c)) << "Expected '" << static_cast<char>(c) << "' to NOT be hex";
    }
}

// Test boundary: character just before '0'
TEST_F(IsHexTest_517, CharBeforeZeroIsNotHex_517) {
    EXPECT_FALSE(re2::IsHex('0' - 1));
}

// Test boundary: character just after '9'
TEST_F(IsHexTest_517, CharAfterNineIsNotHex_517) {
    // ':' is '9' + 1
    EXPECT_FALSE(re2::IsHex('9' + 1));
}

// Test boundary: character just before 'A'
TEST_F(IsHexTest_517, CharBeforeUpperAIsNotHex_517) {
    EXPECT_FALSE(re2::IsHex('A' - 1));
}

// Test boundary: character just after 'F'
TEST_F(IsHexTest_517, CharAfterUpperFIsNotHex_517) {
    EXPECT_FALSE(re2::IsHex('F' + 1));
}

// Test boundary: character just before 'a'
TEST_F(IsHexTest_517, CharBeforeLowerAIsNotHex_517) {
    EXPECT_FALSE(re2::IsHex('a' - 1));
}

// Test boundary: character just after 'f'
TEST_F(IsHexTest_517, CharAfterLowerFIsNotHex_517) {
    EXPECT_FALSE(re2::IsHex('f' + 1));
}

// Test special characters are not hex
TEST_F(IsHexTest_517, SpecialCharactersAreNotHex_517) {
    EXPECT_FALSE(re2::IsHex(' '));
    EXPECT_FALSE(re2::IsHex('\t'));
    EXPECT_FALSE(re2::IsHex('\n'));
    EXPECT_FALSE(re2::IsHex('!'));
    EXPECT_FALSE(re2::IsHex('@'));
    EXPECT_FALSE(re2::IsHex('#'));
    EXPECT_FALSE(re2::IsHex('$'));
    EXPECT_FALSE(re2::IsHex('%'));
    EXPECT_FALSE(re2::IsHex('^'));
    EXPECT_FALSE(re2::IsHex('&'));
    EXPECT_FALSE(re2::IsHex('*'));
    EXPECT_FALSE(re2::IsHex('('));
    EXPECT_FALSE(re2::IsHex(')'));
    EXPECT_FALSE(re2::IsHex('-'));
    EXPECT_FALSE(re2::IsHex('+'));
    EXPECT_FALSE(re2::IsHex('/'));
}

// Test null character is not hex
TEST_F(IsHexTest_517, NullCharIsNotHex_517) {
    EXPECT_FALSE(re2::IsHex(0));
}

// Test negative values are not hex
TEST_F(IsHexTest_517, NegativeValuesAreNotHex_517) {
    EXPECT_FALSE(re2::IsHex(-1));
    EXPECT_FALSE(re2::IsHex(-100));
    EXPECT_FALSE(re2::IsHex(-255));
}

// Test large values are not hex
TEST_F(IsHexTest_517, LargeValuesAreNotHex_517) {
    EXPECT_FALSE(re2::IsHex(256));
    EXPECT_FALSE(re2::IsHex(1000));
    EXPECT_FALSE(re2::IsHex(65535));
}

// Test exact boundary values are hex
TEST_F(IsHexTest_517, ExactBoundaryValuesAreHex_517) {
    EXPECT_TRUE(re2::IsHex('0'));
    EXPECT_TRUE(re2::IsHex('9'));
    EXPECT_TRUE(re2::IsHex('A'));
    EXPECT_TRUE(re2::IsHex('F'));
    EXPECT_TRUE(re2::IsHex('a'));
    EXPECT_TRUE(re2::IsHex('f'));
}

// Test return value is non-zero for hex (truthy)
TEST_F(IsHexTest_517, ReturnValueIsNonZeroForHex_517) {
    EXPECT_NE(0, re2::IsHex('0'));
    EXPECT_NE(0, re2::IsHex('a'));
    EXPECT_NE(0, re2::IsHex('F'));
}

// Test return value is zero for non-hex
TEST_F(IsHexTest_517, ReturnValueIsZeroForNonHex_517) {
    EXPECT_EQ(0, re2::IsHex('g'));
    EXPECT_EQ(0, re2::IsHex('G'));
    EXPECT_EQ(0, re2::IsHex('z'));
    EXPECT_EQ(0, re2::IsHex('Z'));
    EXPECT_EQ(0, re2::IsHex(' '));
}
