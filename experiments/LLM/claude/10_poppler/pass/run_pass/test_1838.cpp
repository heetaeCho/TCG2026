#include <gtest/gtest.h>

// We need to access the static function. Since it's defined as static in a .cc file,
// we either need to include the .cc file or redeclare it. For testing purposes,
// we'll include the .cc file indirectly by declaring the function signature and
// linking against the object, but since it's static, we need to include the source.
// A common approach for testing static functions is to include the .cc file directly
// or use a test helper. Here we'll replicate the function signature for testing
// since we're told to treat it as a black box based on the interface.

// Since the function is static and not accessible outside the translation unit,
// we need to either include the source file or copy the function declaration.
// For this test, we'll include the relevant portion.

// Redefine the constants used by the function
#define jbig2HuffmanOOB 0xfffffffe
#define jbig2HuffmanLOW 0xfffffffd
#define jbig2HuffmanEOT 0xffffffff

// Since the function is static in the .cc file, we need to provide access to it for testing.
// We replicate the exact function here as it would be in the translation unit.
// In a real project, you'd use a test-friend mechanism or make it accessible.
static unsigned int calculateSymCodeLen(const unsigned int numInputSyms, const unsigned int numNewSyms, const unsigned int huff)
{
    unsigned int i = numInputSyms + numNewSyms;
    if (i <= 1) {
        return huff ? 1 : 0;
    }
    --i;
    unsigned int symCodeLen = 0;
    while (i > 0) {
        ++symCodeLen;
        i >>= 1;
    }
    return symCodeLen;
}

class CalculateSymCodeLenTest_1838 : public ::testing::Test {
protected:
};

// Test when total symbols is 0, huff is 0 -> should return 0
TEST_F(CalculateSymCodeLenTest_1838, ZeroSymbolsNoHuff_1838)
{
    EXPECT_EQ(0u, calculateSymCodeLen(0, 0, 0));
}

// Test when total symbols is 0, huff is 1 -> should return 1
TEST_F(CalculateSymCodeLenTest_1838, ZeroSymbolsWithHuff_1838)
{
    EXPECT_EQ(1u, calculateSymCodeLen(0, 0, 1));
}

// Test when total symbols is 1, huff is 0 -> should return 0
TEST_F(CalculateSymCodeLenTest_1838, OneSymbolNoHuff_1838)
{
    EXPECT_EQ(0u, calculateSymCodeLen(1, 0, 0));
}

// Test when total symbols is 1, huff is 1 -> should return 1
TEST_F(CalculateSymCodeLenTest_1838, OneSymbolWithHuff_1838)
{
    EXPECT_EQ(1u, calculateSymCodeLen(0, 1, 1));
}

// Test when total symbols is 2 -> ceil(log2(2)) = 1
TEST_F(CalculateSymCodeLenTest_1838, TwoSymbolsNoHuff_1838)
{
    EXPECT_EQ(1u, calculateSymCodeLen(1, 1, 0));
}

// Test when total symbols is 2, huff is 1
TEST_F(CalculateSymCodeLenTest_1838, TwoSymbolsWithHuff_1838)
{
    EXPECT_EQ(1u, calculateSymCodeLen(2, 0, 1));
}

// Test when total symbols is 3 -> i=2, log2 bits = 2
TEST_F(CalculateSymCodeLenTest_1838, ThreeSymbols_1838)
{
    EXPECT_EQ(2u, calculateSymCodeLen(2, 1, 0));
}

// Test when total symbols is 4 -> i=3, bits needed = 2
TEST_F(CalculateSymCodeLenTest_1838, FourSymbols_1838)
{
    EXPECT_EQ(2u, calculateSymCodeLen(2, 2, 0));
}

// Test when total symbols is 5 -> i=4, bits needed = 3 (since 4 in binary is 100, 3 bits)
// Wait: i = 5-1 = 4, loop: 4>0 -> symCodeLen=1, i=2; 2>0 -> symCodeLen=2, i=1; 1>0 -> symCodeLen=3, i=0
TEST_F(CalculateSymCodeLenTest_1838, FiveSymbols_1838)
{
    EXPECT_EQ(3u, calculateSymCodeLen(3, 2, 0));
}

// Test when total symbols is 8 -> i=7, bits: 7=111, 3 bits
TEST_F(CalculateSymCodeLenTest_1838, EightSymbols_1838)
{
    EXPECT_EQ(3u, calculateSymCodeLen(4, 4, 0));
}

// Test when total symbols is 9 -> i=8=1000, 4 bits
TEST_F(CalculateSymCodeLenTest_1838, NineSymbols_1838)
{
    EXPECT_EQ(4u, calculateSymCodeLen(5, 4, 0));
}

// Test when total symbols is 16 -> i=15=1111, 4 bits
TEST_F(CalculateSymCodeLenTest_1838, SixteenSymbols_1838)
{
    EXPECT_EQ(4u, calculateSymCodeLen(8, 8, 0));
}

// Test when total symbols is 17 -> i=16=10000, 5 bits
TEST_F(CalculateSymCodeLenTest_1838, SeventeenSymbols_1838)
{
    EXPECT_EQ(5u, calculateSymCodeLen(10, 7, 0));
}

// Test power of 2: total symbols = 256 -> i=255, 8 bits
TEST_F(CalculateSymCodeLenTest_1838, PowerOfTwo256_1838)
{
    EXPECT_EQ(8u, calculateSymCodeLen(128, 128, 0));
}

// Test power of 2: total symbols = 257 -> i=256=2^8, 9 bits
TEST_F(CalculateSymCodeLenTest_1838, PowerOfTwoPlus1_257_1838)
{
    EXPECT_EQ(9u, calculateSymCodeLen(200, 57, 0));
}

// Test with huff parameter being non-zero but > 1
TEST_F(CalculateSymCodeLenTest_1838, HuffNonZeroGreaterThanOne_1838)
{
    // When total symbols is 0 and huff is 5 (truthy), should return 1
    EXPECT_EQ(1u, calculateSymCodeLen(0, 0, 5));
}

// Test with only numInputSyms contributing
TEST_F(CalculateSymCodeLenTest_1838, OnlyInputSyms_1838)
{
    EXPECT_EQ(4u, calculateSymCodeLen(10, 0, 0));
    // i = 10 - 1 = 9 = 1001, 4 bits
}

// Test with only numNewSyms contributing
TEST_F(CalculateSymCodeLenTest_1838, OnlyNewSyms_1838)
{
    EXPECT_EQ(4u, calculateSymCodeLen(0, 10, 0));
}

// Test large values
TEST_F(CalculateSymCodeLenTest_1838, LargeValues_1838)
{
    // total = 1024 -> i = 1023 = 0x3FF, 10 bits
    EXPECT_EQ(10u, calculateSymCodeLen(512, 512, 0));
}

// Test total = 1025 -> i = 1024 = 2^10, 11 bits
TEST_F(CalculateSymCodeLenTest_1838, LargeValuesPowerOfTwoPlusOne_1838)
{
    EXPECT_EQ(11u, calculateSymCodeLen(512, 513, 0));
}

// Test total symbols = 2 with huff
TEST_F(CalculateSymCodeLenTest_1838, TwoSymbolsHuffEnabled_1838)
{
    EXPECT_EQ(1u, calculateSymCodeLen(1, 1, 1));
}

// Test boundary: total symbols = 1 with both input and new syms
TEST_F(CalculateSymCodeLenTest_1838, TotalOneFromBothInputs_1838)
{
    EXPECT_EQ(0u, calculateSymCodeLen(0, 1, 0));
    EXPECT_EQ(0u, calculateSymCodeLen(1, 0, 0));
}

// Test very large number close to UINT_MAX / 2 to avoid overflow
TEST_F(CalculateSymCodeLenTest_1838, VeryLargeSymbolCount_1838)
{
    // total = 65536 -> i = 65535 = 0xFFFF, 16 bits
    EXPECT_EQ(16u, calculateSymCodeLen(32768, 32768, 0));
}

// Test total = 65537 -> i = 65536 = 2^16, 17 bits
TEST_F(CalculateSymCodeLenTest_1838, VeryLargeSymbolCountPlusOne_1838)
{
    EXPECT_EQ(17u, calculateSymCodeLen(32768, 32769, 0));
}

// Huff flag doesn't matter when total > 1
TEST_F(CalculateSymCodeLenTest_1838, HuffFlagIrrelevantForLargerTotals_1838)
{
    EXPECT_EQ(calculateSymCodeLen(5, 5, 0), calculateSymCodeLen(5, 5, 1));
    EXPECT_EQ(calculateSymCodeLen(100, 100, 0), calculateSymCodeLen(100, 100, 1));
}

// Test exact powers of 2 totals
TEST_F(CalculateSymCodeLenTest_1838, ExactPowersOfTwo_1838)
{
    // total=2: i=1 -> 1 bit
    EXPECT_EQ(1u, calculateSymCodeLen(2, 0, 0));
    // total=4: i=3 -> 2 bits
    EXPECT_EQ(2u, calculateSymCodeLen(4, 0, 0));
    // total=8: i=7 -> 3 bits
    EXPECT_EQ(3u, calculateSymCodeLen(8, 0, 0));
    // total=16: i=15 -> 4 bits
    EXPECT_EQ(4u, calculateSymCodeLen(16, 0, 0));
    // total=32: i=31 -> 5 bits
    EXPECT_EQ(5u, calculateSymCodeLen(32, 0, 0));
    // total=64: i=63 -> 6 bits
    EXPECT_EQ(6u, calculateSymCodeLen(64, 0, 0));
}

// Test exact powers of 2 + 1
TEST_F(CalculateSymCodeLenTest_1838, PowersOfTwoPlusOne_1838)
{
    // total=3: i=2 -> 2 bits
    EXPECT_EQ(2u, calculateSymCodeLen(3, 0, 0));
    // total=5: i=4 -> 3 bits
    EXPECT_EQ(3u, calculateSymCodeLen(5, 0, 0));
    // total=9: i=8 -> 4 bits
    EXPECT_EQ(4u, calculateSymCodeLen(9, 0, 0));
    // total=17: i=16 -> 5 bits
    EXPECT_EQ(5u, calculateSymCodeLen(17, 0, 0));
    // total=33: i=32 -> 6 bits
    EXPECT_EQ(6u, calculateSymCodeLen(33, 0, 0));
}
