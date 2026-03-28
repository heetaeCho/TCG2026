#include <gtest/gtest.h>
#include <string>

// Forward declaration of the function under test
namespace Exiv2 {
bool isHex(const std::string& str, size_t size, const std::string& prefix);
}

// Test fixture
class IsHexTest_1154 : public ::testing::Test {
protected:
};

// ==================== Normal Operation Tests ====================

TEST_F(IsHexTest_1154, ValidHexWithPrefix0x_1154) {
    EXPECT_TRUE(Exiv2::isHex("0x1A2B3C", 6, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexWithPrefixHash_1154) {
    EXPECT_TRUE(Exiv2::isHex("#FF00FF", 6, "#"));
}

TEST_F(IsHexTest_1154, ValidHexAllDigits_1154) {
    EXPECT_TRUE(Exiv2::isHex("0x123456", 6, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexAllLettersLower_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xabcdef", 6, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexAllLettersUpper_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xABCDEF", 6, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexMixedCase_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xAaBbCc", 6, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexSingleChar_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xF", 1, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexSizeZeroAnyLength_1154) {
    // When size is 0, the size check is skipped
    EXPECT_TRUE(Exiv2::isHex("0xABCDEF", 0, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexSizeZeroShortString_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xA", 0, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexSizeZeroLongString_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xABCDEF0123456789", 0, "0x"));
}

TEST_F(IsHexTest_1154, ValidHexEmptyPrefix_1154) {
    EXPECT_TRUE(Exiv2::isHex("ABCDEF", 6, ""));
}

TEST_F(IsHexTest_1154, ValidHexEmptyPrefixSizeZero_1154) {
    EXPECT_TRUE(Exiv2::isHex("1234", 0, ""));
}

// ==================== Boundary Condition Tests ====================

TEST_F(IsHexTest_1154, EmptyStringEmptyPrefixSizeZero_1154) {
    // Empty string, empty prefix, size 0: no hex digits to check, all_of on empty range is true
    EXPECT_TRUE(Exiv2::isHex("", 0, ""));
}

TEST_F(IsHexTest_1154, EmptyStringWithPrefix_1154) {
    EXPECT_FALSE(Exiv2::isHex("", 0, "0x"));
}

TEST_F(IsHexTest_1154, PrefixOnlyWithSizeZero_1154) {
    // "0x" with prefix "0x", size 0: hex part is empty, all_of on empty range is true
    EXPECT_TRUE(Exiv2::isHex("0x", 0, "0x"));
}

TEST_F(IsHexTest_1154, PrefixOnlyWithSizeNonZero_1154) {
    // "0x" with prefix "0x", size 2: expects total length 4, actual is 2
    EXPECT_FALSE(Exiv2::isHex("0x", 2, "0x"));
}

TEST_F(IsHexTest_1154, SingleHexDigitWithPrefixAndSize1_1154) {
    EXPECT_TRUE(Exiv2::isHex("0x0", 1, "0x"));
}

TEST_F(IsHexTest_1154, EmptyPrefixEmptyStringSizeNonZero_1154) {
    // Empty prefix, empty string, size 1: expects total length 1, actual is 0
    EXPECT_FALSE(Exiv2::isHex("", 1, ""));
}

// ==================== Error/Negative Tests ====================

TEST_F(IsHexTest_1154, WrongPrefix_1154) {
    EXPECT_FALSE(Exiv2::isHex("0xABCD", 4, "0X"));
}

TEST_F(IsHexTest_1154, MissingPrefix_1154) {
    EXPECT_FALSE(Exiv2::isHex("ABCDEF", 6, "0x"));
}

TEST_F(IsHexTest_1154, NonHexCharacterG_1154) {
    EXPECT_FALSE(Exiv2::isHex("0xABCDGH", 6, "0x"));
}

TEST_F(IsHexTest_1154, NonHexCharacterSpace_1154) {
    EXPECT_FALSE(Exiv2::isHex("0xAB CD", 5, "0x"));
}

TEST_F(IsHexTest_1154, NonHexCharacterSpecial_1154) {
    EXPECT_FALSE(Exiv2::isHex("0xAB!D", 4, "0x"));
}

TEST_F(IsHexTest_1154, WrongSizeTooShort_1154) {
    // Actual hex part is 4 chars, but expecting 6
    EXPECT_FALSE(Exiv2::isHex("0xABCD", 6, "0x"));
}

TEST_F(IsHexTest_1154, WrongSizeTooLong_1154) {
    // Actual hex part is 6 chars, but expecting 4
    EXPECT_FALSE(Exiv2::isHex("0xABCDEF", 4, "0x"));
}

TEST_F(IsHexTest_1154, NonHexWithSizeZero_1154) {
    // Size 0 skips size check, but still checks hex digits
    EXPECT_FALSE(Exiv2::isHex("0xGHIJ", 0, "0x"));
}

TEST_F(IsHexTest_1154, PartialPrefixMatch_1154) {
    EXPECT_FALSE(Exiv2::isHex("0ABCDEF", 6, "0x"));
}

TEST_F(IsHexTest_1154, PrefixLongerThanString_1154) {
    EXPECT_FALSE(Exiv2::isHex("0", 0, "0x"));
}

TEST_F(IsHexTest_1154, NonHexCharAtEnd_1154) {
    EXPECT_FALSE(Exiv2::isHex("0xABCDEZ", 6, "0x"));
}

TEST_F(IsHexTest_1154, NonHexCharAtBeginningOfHexPart_1154) {
    EXPECT_FALSE(Exiv2::isHex("0xZBCDEF", 6, "0x"));
}

// ==================== Additional Edge Cases ====================

TEST_F(IsHexTest_1154, LongPrefixValidHex_1154) {
    EXPECT_TRUE(Exiv2::isHex("prefix_AB", 2, "prefix_"));
}

TEST_F(IsHexTest_1154, LongPrefixInvalidHex_1154) {
    EXPECT_FALSE(Exiv2::isHex("prefix_XY", 2, "prefix_"));
}

TEST_F(IsHexTest_1154, PrefixIsEntireString_1154) {
    // Prefix matches the whole string, hex part is empty
    // size=0 => skip size check, all_of on empty range => true
    EXPECT_TRUE(Exiv2::isHex("0x", 0, "0x"));
}

TEST_F(IsHexTest_1154, Size1WithCorrectLength_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xA", 1, "0x"));
}

TEST_F(IsHexTest_1154, AllZeros_1154) {
    EXPECT_TRUE(Exiv2::isHex("0x000000", 6, "0x"));
}

TEST_F(IsHexTest_1154, AllFs_1154) {
    EXPECT_TRUE(Exiv2::isHex("0xFFFFFF", 6, "0x"));
}

TEST_F(IsHexTest_1154, LargeHexString_1154) {
    std::string hexStr = "0x";
    for (int i = 0; i < 1000; i++) {
        hexStr += "A";
    }
    EXPECT_TRUE(Exiv2::isHex(hexStr, 1000, "0x"));
}

TEST_F(IsHexTest_1154, LargeHexStringSizeZero_1154) {
    std::string hexStr = "0x";
    for (int i = 0; i < 1000; i++) {
        hexStr += "B";
    }
    EXPECT_TRUE(Exiv2::isHex(hexStr, 0, "0x"));
}

TEST_F(IsHexTest_1154, LargeHexStringWrongSize_1154) {
    std::string hexStr = "0x";
    for (int i = 0; i < 1000; i++) {
        hexStr += "C";
    }
    EXPECT_FALSE(Exiv2::isHex(hexStr, 999, "0x"));
}
