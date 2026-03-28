#include <gtest/gtest.h>
#include <cstdint>

// UTF16Unit is typically uint16_t in the XMP SDK
typedef uint16_t UTF16Unit;

// Replicate the static inline function signature for testing purposes.
// Since the function is static inline in the source, we need to define it here
// exactly as it appears in the source to test it.
static inline UTF16Unit UTF16InSwap(const UTF16Unit* inPtr) {
    UTF16Unit inUnit = *inPtr;
    return (inUnit << 8) | (inUnit >> 8);
}

class UTF16InSwapTest_2050 : public ::testing::Test {
protected:
    UTF16Unit value;
};

// Test that swapping bytes of 0x0000 returns 0x0000
TEST_F(UTF16InSwapTest_2050, ZeroValue_2050) {
    value = 0x0000;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x0000);
}

// Test that swapping bytes of 0x0102 returns 0x0201
TEST_F(UTF16InSwapTest_2050, SimpleSwap_2050) {
    value = 0x0102;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x0201);
}

// Test that swapping bytes of 0xFF00 returns 0x00FF
TEST_F(UTF16InSwapTest_2050, HighByteOnly_2050) {
    value = 0xFF00;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x00FF);
}

// Test that swapping bytes of 0x00FF returns 0xFF00
TEST_F(UTF16InSwapTest_2050, LowByteOnly_2050) {
    value = 0x00FF;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0xFF00);
}

// Test that swapping bytes of 0xFFFF returns 0xFFFF
TEST_F(UTF16InSwapTest_2050, AllOnes_2050) {
    value = 0xFFFF;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0xFFFF);
}

// Test that swapping bytes of 0x1234 returns 0x3412
TEST_F(UTF16InSwapTest_2050, ArbitraryValue_2050) {
    value = 0x1234;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x3412);
}

// Test that swapping bytes of 0xABCD returns 0xCDAB
TEST_F(UTF16InSwapTest_2050, AnotherArbitraryValue_2050) {
    value = 0xABCD;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0xCDAB);
}

// Test that double swap returns the original value
TEST_F(UTF16InSwapTest_2050, DoubleSwapReturnsOriginal_2050) {
    value = 0x5A3C;
    UTF16Unit swapped = UTF16InSwap(&value);
    UTF16Unit doubleSwapped = UTF16InSwap(&swapped);
    EXPECT_EQ(doubleSwapped, value);
}

// Test byte swap of 0x0001 (smallest non-zero value)
TEST_F(UTF16InSwapTest_2050, SmallestNonZero_2050) {
    value = 0x0001;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x0100);
}

// Test byte swap of 0x0100
TEST_F(UTF16InSwapTest_2050, ValueOf0x0100_2050) {
    value = 0x0100;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x0001);
}

// Test byte swap of 0x8000 (highest bit set)
TEST_F(UTF16InSwapTest_2050, HighestBitSet_2050) {
    value = 0x8000;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x0080);
}

// Test byte swap of 0x0080
TEST_F(UTF16InSwapTest_2050, ValueOf0x0080_2050) {
    value = 0x0080;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x8000);
}

// Test with BOM marker (UTF-16 BE BOM)
TEST_F(UTF16InSwapTest_2050, BOMSwap_2050) {
    value = 0xFEFF;  // UTF-16 BE BOM
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0xFFFE);  // UTF-16 LE BOM
}

// Test with a typical ASCII character in UTF-16 (e.g., 'A' = 0x0041)
TEST_F(UTF16InSwapTest_2050, ASCIICharSwap_2050) {
    value = 0x0041;  // 'A'
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, 0x4100);
}

// Test symmetry: swap(a) != a for non-palindromic byte values
TEST_F(UTF16InSwapTest_2050, SwapIsNotIdentityForAsymmetric_2050) {
    value = 0x1200;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_NE(result, value);
    EXPECT_EQ(result, 0x0012);
}

// Test that swap is identity for palindromic byte patterns
TEST_F(UTF16InSwapTest_2050, PalindromicBytePattern_2050) {
    value = 0x7777;
    UTF16Unit result = UTF16InSwap(&value);
    EXPECT_EQ(result, value);
}

// Test with pointer to element in array
TEST_F(UTF16InSwapTest_2050, ArrayElement_2050) {
    UTF16Unit arr[] = {0x1234, 0x5678, 0x9ABC};
    EXPECT_EQ(UTF16InSwap(&arr[0]), 0x3412);
    EXPECT_EQ(UTF16InSwap(&arr[1]), 0x7856);
    EXPECT_EQ(UTF16InSwap(&arr[2]), 0xBC9A);
}
