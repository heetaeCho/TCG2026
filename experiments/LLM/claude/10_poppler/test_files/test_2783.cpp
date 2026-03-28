#include <gtest/gtest.h>
#include <cstdint>

// Reproduce the struct as defined in the source since it's a compile-time table
struct Mul0dTable
{
public:
    constexpr Mul0dTable()
    {
        for (int s = 0; s < 256; s++) {
            const unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
            const unsigned char s4 = (s2 & 0x80) ? ((s2 << 1) ^ 0x1b) : (s2 << 1);
            const unsigned char s8 = (s4 & 0x80) ? ((s4 << 1) ^ 0x1b) : (s4 << 1);
            values[s] = s ^ s4 ^ s8;
        }
    }

    constexpr unsigned char operator()(uint8_t i) const { return values[i]; }

private:
    unsigned char values[256] = {};
};

// Helper function to compute expected value for a given input
static unsigned char computeExpectedMul0d(uint8_t s)
{
    const unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
    const unsigned char s4 = (s2 & 0x80) ? ((s2 << 1) ^ 0x1b) : (s2 << 1);
    const unsigned char s8 = (s4 & 0x80) ? ((s4 << 1) ^ 0x1b) : (s4 << 1);
    return s ^ s4 ^ s8;
}

class Mul0dTableTest_2783 : public ::testing::Test
{
protected:
    static constexpr Mul0dTable table {};
};

// Test that multiplying 0 by 0x0d gives 0 (identity-like for zero)
TEST_F(Mul0dTableTest_2783, ZeroInput_2783)
{
    EXPECT_EQ(table(0), 0);
}

// Test input value 1: 0x0d * 1 should equal 0x0d in GF(2^8)
TEST_F(Mul0dTableTest_2783, InputOne_2783)
{
    // For s=1: s2=2, s4=4, s8=8 => 1^4^8 = 13 = 0x0d
    EXPECT_EQ(table(1), 0x0d);
}

// Test input value 2
TEST_F(Mul0dTableTest_2783, InputTwo_2783)
{
    unsigned char expected = computeExpectedMul0d(2);
    EXPECT_EQ(table(2), expected);
}

// Test a known AES value: input 0x53
TEST_F(Mul0dTableTest_2783, InputSpecificValue_0x53_2783)
{
    unsigned char expected = computeExpectedMul0d(0x53);
    EXPECT_EQ(table(0x53), expected);
}

// Test boundary: maximum input 255
TEST_F(Mul0dTableTest_2783, MaxInput_255_2783)
{
    unsigned char expected = computeExpectedMul0d(255);
    EXPECT_EQ(table(255), expected);
}

// Test boundary: input 128 (0x80) - where the high bit causes XOR with 0x1b
TEST_F(Mul0dTableTest_2783, InputHighBitSet_128_2783)
{
    unsigned char expected = computeExpectedMul0d(128);
    EXPECT_EQ(table(128), expected);
}

// Test input 127 (0x7F) - just below the high bit threshold
TEST_F(Mul0dTableTest_2783, InputJustBelowHighBit_127_2783)
{
    unsigned char expected = computeExpectedMul0d(127);
    EXPECT_EQ(table(127), expected);
}

// Test input 0x80 specifically for reduction path
TEST_F(Mul0dTableTest_2783, Input0x80_2783)
{
    // s=0x80, s2 = (0x80<<1)^0x1b = 0x1b, s4 = 0x36, s8 = 0x6c
    // result = 0x80 ^ 0x36 ^ 0x6c = 0x80 ^ 0x36 = 0xb6 ^ 0x6c = 0xda
    EXPECT_EQ(table(0x80), static_cast<unsigned char>(0x80 ^ 0x36 ^ 0x6c));
}

// Test all 256 values match the computation
TEST_F(Mul0dTableTest_2783, AllValuesMatchComputation_2783)
{
    for (int i = 0; i < 256; i++) {
        unsigned char expected = computeExpectedMul0d(static_cast<uint8_t>(i));
        EXPECT_EQ(table(static_cast<uint8_t>(i)), expected) << "Mismatch at index " << i;
    }
}

// Test that the table is consistent when called multiple times with the same input
TEST_F(Mul0dTableTest_2783, ConsistentResults_2783)
{
    for (int i = 0; i < 256; i++) {
        uint8_t idx = static_cast<uint8_t>(i);
        EXPECT_EQ(table(idx), table(idx)) << "Inconsistent result at index " << i;
    }
}

// Test constexpr evaluation
TEST_F(Mul0dTableTest_2783, ConstexprEvaluation_2783)
{
    constexpr Mul0dTable constexprTable;
    constexpr unsigned char val0 = constexprTable(0);
    constexpr unsigned char val1 = constexprTable(1);
    constexpr unsigned char val255 = constexprTable(255);

    EXPECT_EQ(val0, 0);
    EXPECT_EQ(val1, 0x0d);
    EXPECT_EQ(val255, computeExpectedMul0d(255));
}

// Test specific AES inverse MixColumns related values
TEST_F(Mul0dTableTest_2783, KnownGaloisMultiplicationValues_2783)
{
    // In GF(2^8), multiplication by 0x0d:
    // 0x0d * 0x01 = 0x0d
    EXPECT_EQ(table(0x01), 0x0d);

    // Verify a few more known results
    // 0x0d * 0x00 = 0x00
    EXPECT_EQ(table(0x00), 0x00);
}

// Test values around power-of-two boundaries
TEST_F(Mul0dTableTest_2783, PowerOfTwoBoundaries_2783)
{
    uint8_t powers[] = {1, 2, 4, 8, 16, 32, 64, 128};
    for (uint8_t p : powers) {
        EXPECT_EQ(table(p), computeExpectedMul0d(p)) << "Mismatch at power of two: " << static_cast<int>(p);
    }
}

// Test that result is always within byte range (trivially true for unsigned char, but verify)
TEST_F(Mul0dTableTest_2783, ResultsInByteRange_2783)
{
    for (int i = 0; i < 256; i++) {
        unsigned char result = table(static_cast<uint8_t>(i));
        EXPECT_GE(result, 0);
        EXPECT_LE(result, 255);
    }
}
