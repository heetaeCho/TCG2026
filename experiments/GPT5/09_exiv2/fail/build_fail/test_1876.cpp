#include <gtest/gtest.h>

extern "C" {
    #include "./TestProjects/exiv2/xmpsdk/src/UnicodeInlines.incl_cpp"
}

// TEST_ID: 1876

// Test normal operation for different non-ASCII start characters
TEST_F(UnicodeInlinesTest_1876, NonASCIIStartCharTest_1876) {
    // Test valid Unicode code points that should return true
    EXPECT_TRUE(IsStartChar_NonASCII(0xC0));  // First valid code point in the range
    EXPECT_TRUE(IsStartChar_NonASCII(0xD6));  // Last valid code point in the range
    EXPECT_TRUE(IsStartChar_NonASCII(0xF8));  // First valid code point in another range
    EXPECT_TRUE(IsStartChar_NonASCII(0x2FF)); // Last valid code point in that range
    EXPECT_TRUE(IsStartChar_NonASCII(0x370)); // First valid code point
    EXPECT_TRUE(IsStartChar_NonASCII(0x37D)); // Last valid code point in that range
    EXPECT_TRUE(IsStartChar_NonASCII(0x200C)); // Code point that should return true
    EXPECT_TRUE(IsStartChar_NonASCII(0x200D)); // Another valid code point
    EXPECT_TRUE(IsStartChar_NonASCII(0x218F)); // Upper bound of a valid range
    EXPECT_TRUE(IsStartChar_NonASCII(0x2FEF)); // Last valid code point in that range
    EXPECT_TRUE(IsStartChar_NonASCII(0x3001)); // First valid code point in another range
    EXPECT_TRUE(IsStartChar_NonASCII(0xD7FF)); // Upper bound of a valid range
    EXPECT_TRUE(IsStartChar_NonASCII(0xF900)); // First valid code point in another range
    EXPECT_TRUE(IsStartChar_NonASCII(0xFDCF)); // Upper bound of the range
    EXPECT_TRUE(IsStartChar_NonASCII(0xFDF0)); // First valid code point in that range
    EXPECT_TRUE(IsStartChar_NonASCII(0xFFFD)); // Last valid code point in the range
    EXPECT_TRUE(IsStartChar_NonASCII(0x10000)); // First valid code point above 0xFFFF
    EXPECT_TRUE(IsStartChar_NonASCII(0xEFFFF)); // Last valid code point in this range
}

// Test boundary conditions for the edge values
TEST_F(UnicodeInlinesTest_1876, BoundaryConditionTest_1876) {
    // Test the boundary between ranges, should return false for values outside the valid ranges
    EXPECT_FALSE(IsStartChar_NonASCII(0x3F));   // Below valid start
    EXPECT_FALSE(IsStartChar_NonASCII(0xC0 - 1)); // Just before a valid range
    EXPECT_FALSE(IsStartChar_NonASCII(0xD7 + 1)); // Just after the last valid code point
    EXPECT_FALSE(IsStartChar_NonASCII(0x2FF + 1)); // Just outside the upper bound
    EXPECT_FALSE(IsStartChar_NonASCII(0x370 - 1)); // Just before a valid range
    EXPECT_FALSE(IsStartChar_NonASCII(0x37F + 1)); // Just outside the range
    EXPECT_FALSE(IsStartChar_NonASCII(0x200C - 1)); // Boundary below valid range
    EXPECT_FALSE(IsStartChar_NonASCII(0x218F + 1)); // Boundary just after valid range
    EXPECT_FALSE(IsStartChar_NonASCII(0x2FEF + 1)); // Upper boundary check
    EXPECT_FALSE(IsStartChar_NonASCII(0x3001 - 1)); // Boundary check before valid range
    EXPECT_FALSE(IsStartChar_NonASCII(0xD7FF + 1)); // Upper boundary for the range
    EXPECT_FALSE(IsStartChar_NonASCII(0xF900 - 1)); // Just before a valid range
    EXPECT_FALSE(IsStartChar_NonASCII(0xFDCF + 1)); // Upper boundary check for this range
    EXPECT_FALSE(IsStartChar_NonASCII(0xFDF0 - 1)); // Boundary just before
    EXPECT_FALSE(IsStartChar_NonASCII(0xFFFD + 1)); // Upper limit check
    EXPECT_FALSE(IsStartChar_NonASCII(0x10000 - 1)); // Just before valid code point
    EXPECT_FALSE(IsStartChar_NonASCII(0xEFFFF + 1)); // Beyond the last valid code point
}

// Test for exceptional cases
TEST_F(UnicodeInlinesTest_1876, ExceptionalCases_1876) {
    // Since the function only checks a code point, exceptional cases like null or invalid types are not applicable.
    // The behavior should handle the whole range correctly without additional exceptions
}