#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class IsUtf8WithBomTest_1025 : public ::testing::Test {
protected:
};

// Normal operation: string with valid UTF-8 BOM followed by content
TEST_F(IsUtf8WithBomTest_1025, ValidBomWithContent_1025) {
    std::string str = "\xef\xbb\xbf" "Hello";
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Normal operation: string with valid UTF-8 BOM and exactly 4 characters total
TEST_F(IsUtf8WithBomTest_1025, ValidBomWithOneExtraChar_1025) {
    std::string str = "\xef\xbb\xbf" "X";
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Normal operation: string with valid UTF-8 BOM followed by many characters
TEST_F(IsUtf8WithBomTest_1025, ValidBomWithLongContent_1025) {
    std::string str = "\xef\xbb\xbf" "This is a longer string with UTF-8 BOM";
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Boundary condition: empty string
TEST_F(IsUtf8WithBomTest_1025, EmptyString_1025) {
    std::string str = "";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary condition: string with 1 character
TEST_F(IsUtf8WithBomTest_1025, SingleCharString_1025) {
    std::string str = "\xef";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary condition: string with 2 characters
TEST_F(IsUtf8WithBomTest_1025, TwoCharString_1025) {
    std::string str = "\xef\xbb";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary condition: string with exactly 3 characters (BOM only, but size < 4)
TEST_F(IsUtf8WithBomTest_1025, ExactBomButSizeLessThanFour_1025) {
    std::string str = "\xef\xbb\xbf";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary condition: string with exactly 4 characters but no BOM
TEST_F(IsUtf8WithBomTest_1025, FourCharsNoBom_1025) {
    std::string str = "ABCD";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: string starts with wrong first BOM byte
TEST_F(IsUtf8WithBomTest_1025, WrongFirstByte_1025) {
    std::string str = "\xee\xbb\xbf" "X";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: string starts with wrong second BOM byte
TEST_F(IsUtf8WithBomTest_1025, WrongSecondByte_1025) {
    std::string str = "\xef\xba\xbf" "X";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: string starts with wrong third BOM byte
TEST_F(IsUtf8WithBomTest_1025, WrongThirdByte_1025) {
    std::string str = "\xef\xbb\xbe" "X";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: all BOM bytes wrong
TEST_F(IsUtf8WithBomTest_1025, AllBomBytesWrong_1025) {
    std::string str = "\x00\x00\x00\x00";
    EXPECT_FALSE(isUtf8WithBom(std::string_view(str.data(), 4)));
}

// Normal operation: BOM followed by null bytes
TEST_F(IsUtf8WithBomTest_1025, BomFollowedByNullByte_1025) {
    std::string str = "\xef\xbb\xbf";
    str += '\0';
    EXPECT_TRUE(isUtf8WithBom(std::string_view(str.data(), str.size())));
}

// Error case: BOM bytes present but not at the start
TEST_F(IsUtf8WithBomTest_1025, BomNotAtStart_1025) {
    std::string str = "A\xef\xbb\xbf" "Hello";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Normal operation: UTF-16 LE BOM should not match
TEST_F(IsUtf8WithBomTest_1025, Utf16LeBomDoesNotMatch_1025) {
    std::string str = "\xff\xfe\x00\x00";
    EXPECT_FALSE(isUtf8WithBom(std::string_view(str.data(), 4)));
}

// Normal operation: UTF-16 BE BOM should not match
TEST_F(IsUtf8WithBomTest_1025, Utf16BeBomDoesNotMatch_1025) {
    std::string str = "\xfe\xff\x00\x00";
    EXPECT_FALSE(isUtf8WithBom(std::string_view(str.data(), 4)));
}

// Boundary condition: string_view constructed from larger buffer
TEST_F(IsUtf8WithBomTest_1025, StringViewFromLargerBuffer_1025) {
    std::string str = "\xef\xbb\xbf" "Some longer text here";
    std::string_view sv(str.data(), str.size());
    EXPECT_TRUE(isUtf8WithBom(sv));
}

// Edge case: only first byte matches
TEST_F(IsUtf8WithBomTest_1025, OnlyFirstByteMatches_1025) {
    std::string str = "\xef" "ABC";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Edge case: first two bytes match
TEST_F(IsUtf8WithBomTest_1025, FirstTwoBytesMatch_1025) {
    std::string str = "\xef\xbb" "AB";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: exactly 4 bytes with BOM + one ASCII char
TEST_F(IsUtf8WithBomTest_1025, ExactlyFourBytesWithBom_1025) {
    std::string str = "\xef\xbb\xbf" "A";
    ASSERT_EQ(str.size(), 4u);
    EXPECT_TRUE(isUtf8WithBom(str));
}
