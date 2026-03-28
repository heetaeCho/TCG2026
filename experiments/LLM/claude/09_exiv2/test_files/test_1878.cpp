#include <gtest/gtest.h>

// Define XMP_Uns32 as used in the codebase
typedef unsigned int XMP_Uns32;

// Include the inline function
#define BanAllEntityUsage 0
static inline bool IsOtherChar_NonASCII(XMP_Uns32 cp) {
    if ((cp == 0xB7) || ((0x300 <= cp) && (cp <= 0x36F)) || ((0x203F <= cp) && (cp <= 0x2040)))
        return true;
    return false;
}

class IsOtherCharNonASCIITest_1878 : public ::testing::Test {};

// Test that 0xB7 (middle dot) returns true
TEST_F(IsOtherCharNonASCIITest_1878, MiddleDotReturnsTrue_1878) {
    EXPECT_TRUE(IsOtherChar_NonASCII(0xB7));
}

// Test values just below and above 0xB7
TEST_F(IsOtherCharNonASCIITest_1878, JustBelowMiddleDotReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0xB6));
}

TEST_F(IsOtherCharNonASCIITest_1878, JustAboveMiddleDotReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0xB8));
}

// Test the lower boundary of the 0x300-0x36F range
TEST_F(IsOtherCharNonASCIITest_1878, LowerBoundOfCombiningRange_1878) {
    EXPECT_TRUE(IsOtherChar_NonASCII(0x300));
}

TEST_F(IsOtherCharNonASCIITest_1878, BelowCombiningRangeReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x2FF));
}

// Test the upper boundary of the 0x300-0x36F range
TEST_F(IsOtherCharNonASCIITest_1878, UpperBoundOfCombiningRange_1878) {
    EXPECT_TRUE(IsOtherChar_NonASCII(0x36F));
}

TEST_F(IsOtherCharNonASCIITest_1878, AboveCombiningRangeReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x370));
}

// Test a value in the middle of the 0x300-0x36F range
TEST_F(IsOtherCharNonASCIITest_1878, MiddleOfCombiningRangeReturnsTrue_1878) {
    EXPECT_TRUE(IsOtherChar_NonASCII(0x330));
}

// Test the lower boundary of the 0x203F-0x2040 range
TEST_F(IsOtherCharNonASCIITest_1878, LowerBoundOfUndertieRange_1878) {
    EXPECT_TRUE(IsOtherChar_NonASCII(0x203F));
}

TEST_F(IsOtherCharNonASCIITest_1878, BelowUndertieRangeReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x203E));
}

// Test the upper boundary of the 0x203F-0x2040 range
TEST_F(IsOtherCharNonASCIITest_1878, UpperBoundOfUndertieRange_1878) {
    EXPECT_TRUE(IsOtherChar_NonASCII(0x2040));
}

TEST_F(IsOtherCharNonASCIITest_1878, AboveUndertieRangeReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x2041));
}

// Test zero returns false
TEST_F(IsOtherCharNonASCIITest_1878, ZeroReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0));
}

// Test ASCII range values return false (except 0xB7 is non-ASCII range actually)
TEST_F(IsOtherCharNonASCIITest_1878, ASCIIValueReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x41)); // 'A'
}

TEST_F(IsOtherCharNonASCIITest_1878, AnotherASCIIValueReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x7F));
}

// Test a large value outside all ranges
TEST_F(IsOtherCharNonASCIITest_1878, LargeValueReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0xFFFF));
}

// Test maximum XMP_Uns32 value
TEST_F(IsOtherCharNonASCIITest_1878, MaxUns32ReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0xFFFFFFFF));
}

// Test values between the valid ranges that should return false
TEST_F(IsOtherCharNonASCIITest_1878, GapBetweenRangesReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x1000));
}

TEST_F(IsOtherCharNonASCIITest_1878, ValueBetweenB7And300ReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x100));
}

TEST_F(IsOtherCharNonASCIITest_1878, ValueBetween36FAnd203FReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(0x500));
}

// Test value 1 returns false
TEST_F(IsOtherCharNonASCIITest_1878, OneReturnsFalse_1878) {
    EXPECT_FALSE(IsOtherChar_NonASCII(1));
}

// Comprehensive test iterating through the combining diacritical marks range
TEST_F(IsOtherCharNonASCIITest_1878, AllCombiningDiacriticalMarksReturnTrue_1878) {
    for (XMP_Uns32 cp = 0x300; cp <= 0x36F; ++cp) {
        EXPECT_TRUE(IsOtherChar_NonASCII(cp)) << "Failed for code point: 0x" << std::hex << cp;
    }
}

// Both values in the undertie range return true
TEST_F(IsOtherCharNonASCIITest_1878, BothUndertieValuesReturnTrue_1878) {
    EXPECT_TRUE(IsOtherChar_NonASCII(0x203F));
    EXPECT_TRUE(IsOtherChar_NonASCII(0x2040));
}
