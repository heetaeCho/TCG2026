#include <gtest/gtest.h>
#include <string>
#include <utility>

// Include the header under test
#include "PageLabelInfo_p.h"

// We need to figure out how to call fromDecimal. Based on the code snippet,
// it appears to be a static function, likely in a namespace or class.
// Let's try to call it directly. If it's in a header, we may need to
// wrap it or call it via whatever scope it's in.

// Since the function is declared as static in the header, we can call it directly
// if we include the header. Let's create a simple wrapper to test it.

class FromDecimalTest_1932 : public ::testing::Test {
protected:
    // Helper to call the function
    static std::pair<int, bool> callFromDecimal(const std::string &str, bool unicode) {
        return fromDecimal(str, unicode);
    }
};

// Normal operation - simple decimal number, non-unicode
TEST_F(FromDecimalTest_1932, SimpleDecimalNumber_1932) {
    auto result = callFromDecimal("123", false);
    EXPECT_EQ(result.first, 123);
    EXPECT_TRUE(result.second);
}

// Normal operation - single digit
TEST_F(FromDecimalTest_1932, SingleDigit_1932) {
    auto result = callFromDecimal("5", false);
    EXPECT_EQ(result.first, 5);
    EXPECT_TRUE(result.second);
}

// Normal operation - zero
TEST_F(FromDecimalTest_1932, ZeroValue_1932) {
    auto result = callFromDecimal("0", false);
    EXPECT_EQ(result.first, 0);
    EXPECT_TRUE(result.second);
}

// Normal operation - negative number
TEST_F(FromDecimalTest_1932, NegativeNumber_1932) {
    auto result = callFromDecimal("-42", false);
    EXPECT_EQ(result.first, -42);
    EXPECT_TRUE(result.second);
}

// Boundary - empty string, non-unicode
TEST_F(FromDecimalTest_1932, EmptyStringNonUnicode_1932) {
    auto result = callFromDecimal("", false);
    // strtol on empty string returns 0, parsed == begin == end (both point to same location)
    EXPECT_EQ(result.first, 0);
    EXPECT_TRUE(result.second);
}

// Error case - non-numeric string
TEST_F(FromDecimalTest_1932, NonNumericString_1932) {
    auto result = callFromDecimal("abc", false);
    EXPECT_EQ(result.first, 0);
    EXPECT_FALSE(result.second);
}

// Partial parse - number followed by text
TEST_F(FromDecimalTest_1932, NumberFollowedByText_1932) {
    auto result = callFromDecimal("123abc", false);
    EXPECT_EQ(result.first, 123);
    EXPECT_FALSE(result.second);
}

// Leading whitespace - strtol skips whitespace
TEST_F(FromDecimalTest_1932, LeadingWhitespace_1932) {
    auto result = callFromDecimal("  456", false);
    EXPECT_EQ(result.first, 456);
    EXPECT_TRUE(result.second);
}

// Unicode mode - even length string with null high bytes (simulated ASCII in UTF-16BE without BOM)
TEST_F(FromDecimalTest_1932, UnicodeSimpleNumber_1932) {
    // UTF-16BE encoding of "42" without BOM: \x00\x34\x00\x32
    std::string unicodeStr;
    unicodeStr += '\0'; unicodeStr += '4';
    unicodeStr += '\0'; unicodeStr += '2';
    auto result = callFromDecimal(unicodeStr, true);
    EXPECT_EQ(result.first, 42);
    EXPECT_TRUE(result.second);
}

// Unicode mode - with BOM (U+FEFF in UTF-16BE: 0xFE 0xFF)
TEST_F(FromDecimalTest_1932, UnicodeWithBOM_1932) {
    // BOM: \xFE\xFF, then "42" in UTF-16BE: \x00\x34\x00\x32
    std::string unicodeStr;
    unicodeStr += '\xFE'; unicodeStr += '\xFF';
    unicodeStr += '\0'; unicodeStr += '4';
    unicodeStr += '\0'; unicodeStr += '2';
    auto result = callFromDecimal(unicodeStr, true);
    EXPECT_EQ(result.first, 42);
    EXPECT_TRUE(result.second);
}

// Unicode mode - odd length string falls through to strtol
TEST_F(FromDecimalTest_1932, UnicodeOddLength_1932) {
    auto result = callFromDecimal("123", true);
    EXPECT_EQ(result.first, 123);
    EXPECT_TRUE(result.second);
}

// Unicode mode - non-zero high byte (non-ASCII unicode char)
TEST_F(FromDecimalTest_1932, UnicodeNonAsciiHighByte_1932) {
    // A character with non-zero high byte should cause allGood to be false
    // Then it falls through to strtol on the original string
    std::string unicodeStr;
    unicodeStr += '\x01'; unicodeStr += '4';
    unicodeStr += '\x00'; unicodeStr += '2';
    auto result = callFromDecimal(unicodeStr, true);
    // allGood becomes false at first char, falls through to strtol on the raw string
    // strtol will try to parse the raw bytes, likely fail or get 0
    // The raw string starts with \x01 which is not a digit
    EXPECT_EQ(result.first, 0);
    EXPECT_FALSE(result.second);
}

// Unicode mode - empty string
TEST_F(FromDecimalTest_1932, UnicodeEmptyString_1932) {
    auto result = callFromDecimal("", true);
    // Even length (0), no BOM detected, empty newString, allGood stays true
    // Then calls fromDecimal("", false) which returns (0, true)
    EXPECT_EQ(result.first, 0);
    EXPECT_TRUE(result.second);
}

// Unicode mode - just a BOM, no actual content
TEST_F(FromDecimalTest_1932, UnicodeOnlyBOM_1932) {
    std::string unicodeStr;
    unicodeStr += '\xFE'; unicodeStr += '\xFF';
    auto result = callFromDecimal(unicodeStr, true);
    // Has BOM, substr(2) is empty, calls fromDecimal("", true)
    // Which then processes empty string in unicode mode -> calls fromDecimal("", false) -> (0, true)
    EXPECT_EQ(result.first, 0);
    EXPECT_TRUE(result.second);
}

// Large number
TEST_F(FromDecimalTest_1932, LargeNumber_1932) {
    auto result = callFromDecimal("999999", false);
    EXPECT_EQ(result.first, 999999);
    EXPECT_TRUE(result.second);
}

// Number with leading zeros
TEST_F(FromDecimalTest_1932, LeadingZeros_1932) {
    auto result = callFromDecimal("007", false);
    EXPECT_EQ(result.first, 7);
    EXPECT_TRUE(result.second);
}

// Plus sign prefix
TEST_F(FromDecimalTest_1932, PlusSign_1932) {
    auto result = callFromDecimal("+99", false);
    EXPECT_EQ(result.first, 99);
    EXPECT_TRUE(result.second);
}

// Unicode single digit
TEST_F(FromDecimalTest_1932, UnicodeSingleDigit_1932) {
    std::string unicodeStr;
    unicodeStr += '\0'; unicodeStr += '7';
    auto result = callFromDecimal(unicodeStr, true);
    EXPECT_EQ(result.first, 7);
    EXPECT_TRUE(result.second);
}

// Non-unicode mode with string that looks like unicode (contains nulls)
TEST_F(FromDecimalTest_1932, NonUnicodeWithNulls_1932) {
    std::string str;
    str += '\0'; str += '4';
    auto result = callFromDecimal(str, false);
    // strtol starts at \0, which terminates parsing immediately
    EXPECT_EQ(result.first, 0);
    EXPECT_FALSE(result.second);
}

// Unicode mode with zero value
TEST_F(FromDecimalTest_1932, UnicodeZeroValue_1932) {
    std::string unicodeStr;
    unicodeStr += '\0'; unicodeStr += '0';
    auto result = callFromDecimal(unicodeStr, true);
    EXPECT_EQ(result.first, 0);
    EXPECT_TRUE(result.second);
}

// Unicode negative number
TEST_F(FromDecimalTest_1932, UnicodeNegativeNumber_1932) {
    std::string unicodeStr;
    unicodeStr += '\0'; unicodeStr += '-';
    unicodeStr += '\0'; unicodeStr += '5';
    auto result = callFromDecimal(unicodeStr, true);
    EXPECT_EQ(result.first, -5);
    EXPECT_TRUE(result.second);
}
