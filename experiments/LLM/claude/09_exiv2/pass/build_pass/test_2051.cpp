#include <gtest/gtest.h>
#include <cstdint>

// We need to replicate the type and function signature since it's a static inline
// in the source file. We test the same logic as a black-box based on the interface.
typedef uint32_t UTF32Unit;

static inline UTF32Unit UTF32InSwap(const UTF32Unit* inPtr) {
    UTF32Unit inUnit = *inPtr;
    return (inUnit << 24) | ((inUnit << 8) & 0x00FF0000) | ((inUnit >> 8) & 0x0000FF00) | (inUnit >> 24);
}

class UTF32InSwapTest_2051 : public ::testing::Test {
protected:
};

// Test that swapping zero returns zero
TEST_F(UTF32InSwapTest_2051, SwapZeroReturnsZero_2051) {
    UTF32Unit value = 0x00000000;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x00000000u);
}

// Test that swapping 0x01020304 gives 0x04030201 (standard byte reversal)
TEST_F(UTF32InSwapTest_2051, SwapSequentialBytes_2051) {
    UTF32Unit value = 0x01020304;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x04030201u);
}

// Test that swapping 0x04030201 gives 0x01020304 (inverse of above)
TEST_F(UTF32InSwapTest_2051, SwapInverseSequentialBytes_2051) {
    UTF32Unit value = 0x04030201;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x01020304u);
}

// Test double swap returns original value (swap is its own inverse)
TEST_F(UTF32InSwapTest_2051, DoubleSwapReturnsOriginal_2051) {
    UTF32Unit value = 0xDEADBEEF;
    UTF32Unit swapped = UTF32InSwap(&value);
    UTF32Unit doubleSwapped = UTF32InSwap(&swapped);
    EXPECT_EQ(doubleSwapped, value);
}

// Test swapping 0xFFFFFFFF returns 0xFFFFFFFF (all bits set)
TEST_F(UTF32InSwapTest_2051, SwapAllOnesReturnsAllOnes_2051) {
    UTF32Unit value = 0xFFFFFFFF;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0xFFFFFFFF);
}

// Test swapping a value with only the highest byte set
TEST_F(UTF32InSwapTest_2051, SwapHighByteOnly_2051) {
    UTF32Unit value = 0xAB000000;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x000000ABu);
}

// Test swapping a value with only the lowest byte set
TEST_F(UTF32InSwapTest_2051, SwapLowByteOnly_2051) {
    UTF32Unit value = 0x000000CD;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0xCD000000u);
}

// Test swapping a value with only the second byte set
TEST_F(UTF32InSwapTest_2051, SwapSecondByteOnly_2051) {
    UTF32Unit value = 0x00EF0000;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x0000EF00u);
}

// Test swapping a value with only the third byte set
TEST_F(UTF32InSwapTest_2051, SwapThirdByteOnly_2051) {
    UTF32Unit value = 0x0000FF00;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x00FF0000u);
}

// Test swapping 0x00000001 gives 0x01000000
TEST_F(UTF32InSwapTest_2051, SwapOne_2051) {
    UTF32Unit value = 0x00000001;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x01000000u);
}

// Test swapping a BOM-like value (UTF-32 BE BOM: 0x0000FEFF)
TEST_F(UTF32InSwapTest_2051, SwapUTF32BOM_2051) {
    UTF32Unit value = 0x0000FEFF;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0xFFFE0000u);
}

// Test swapping 0xDEADBEEF
TEST_F(UTF32InSwapTest_2051, SwapDeadBeef_2051) {
    UTF32Unit value = 0xDEADBEEF;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0xEFBEADDEu);
}

// Test swapping a palindromic byte pattern
TEST_F(UTF32InSwapTest_2051, SwapPalindromicPattern_2051) {
    UTF32Unit value = 0xABCDCDAB;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0xABCDCDABu);
}

// Test swapping alternating bytes pattern 0xFF00FF00
TEST_F(UTF32InSwapTest_2051, SwapAlternatingBytesFF00_2051) {
    UTF32Unit value = 0xFF00FF00;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x00FF00FFu);
}

// Test swapping alternating bytes pattern 0x00FF00FF
TEST_F(UTF32InSwapTest_2051, SwapAlternatingBytes00FF_2051) {
    UTF32Unit value = 0x00FF00FF;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0xFF00FF00u);
}

// Test swapping max uint32 minus one
TEST_F(UTF32InSwapTest_2051, SwapMaxMinusOne_2051) {
    UTF32Unit value = 0xFFFFFFFE;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0xFEFFFFFFu);
}

// Test with a typical Unicode code point in UTF-32 (e.g., U+1F600 = 0x0001F600)
TEST_F(UTF32InSwapTest_2051, SwapUnicodeCodePoint_2051) {
    UTF32Unit value = 0x0001F600;
    UTF32Unit result = UTF32InSwap(&value);
    EXPECT_EQ(result, 0x00F60100u);
}
