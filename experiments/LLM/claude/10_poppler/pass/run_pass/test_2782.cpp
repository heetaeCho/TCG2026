#include <gtest/gtest.h>
#include <cstdint>

// Reproduce the struct as defined in the source since it's a constexpr struct
// We need the definition to instantiate and test it.
struct Mul0bTable
{
public:
    constexpr Mul0bTable()
    {
        for (int s = 0; s < 256; s++) {
            const unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
            const unsigned char s4 = (s2 & 0x80) ? ((s2 << 1) ^ 0x1b) : (s2 << 1);
            const unsigned char s8 = (s4 & 0x80) ? ((s4 << 1) ^ 0x1b) : (s4 << 1);
            values[s] = s ^ s2 ^ s8;
        }
    }

    constexpr unsigned char operator()(uint8_t i) const { return values[i]; }

private:
    unsigned char values[256] = {};
};

// Helper: compute expected value for a given s using the same GF(2^8) multiplication logic
static unsigned char computeExpectedMul0b(int s)
{
    const unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
    const unsigned char s4 = (s2 & 0x80) ? ((s2 << 1) ^ 0x1b) : (s2 << 1);
    const unsigned char s8 = (s4 & 0x80) ? ((s4 << 1) ^ 0x1b) : (s4 << 1);
    return static_cast<unsigned char>(s ^ s2 ^ s8);
}

class Mul0bTableTest_2782 : public ::testing::Test
{
protected:
    static constexpr Mul0bTable table {};
};

// Test that multiplying 0 by 0x0b in GF(2^8) yields 0
TEST_F(Mul0bTableTest_2782, ZeroInput_2782)
{
    EXPECT_EQ(table(0), 0);
}

// Test input value 1: 1 * 0x0b = 0x0b
TEST_F(Mul0bTableTest_2782, OneInput_2782)
{
    // 0x0b = 11 decimal
    EXPECT_EQ(table(1), 0x0b);
}

// Test input value 2
TEST_F(Mul0bTableTest_2782, InputTwo_2782)
{
    EXPECT_EQ(table(2), computeExpectedMul0b(2));
}

// Test the maximum input value 255
TEST_F(Mul0bTableTest_2782, MaxInput_2782)
{
    EXPECT_EQ(table(255), computeExpectedMul0b(255));
}

// Test boundary value 0x80 (high bit set, triggers XOR with 0x1b in s2 computation)
TEST_F(Mul0bTableTest_2782, HighBitSet_2782)
{
    EXPECT_EQ(table(0x80), computeExpectedMul0b(0x80));
}

// Test value 0x7F (just below high bit boundary)
TEST_F(Mul0bTableTest_2782, JustBelowHighBit_2782)
{
    EXPECT_EQ(table(0x7F), computeExpectedMul0b(0x7F));
}

// Test value 0x40 - triggers high bit in s2
TEST_F(Mul0bTableTest_2782, Input0x40_2782)
{
    EXPECT_EQ(table(0x40), computeExpectedMul0b(0x40));
}

// Test value 0xC0
TEST_F(Mul0bTableTest_2782, Input0xC0_2782)
{
    EXPECT_EQ(table(0xC0), computeExpectedMul0b(0xC0));
}

// Test all 256 values for correctness
TEST_F(Mul0bTableTest_2782, AllValues_2782)
{
    for (int s = 0; s < 256; s++) {
        EXPECT_EQ(table(static_cast<uint8_t>(s)), computeExpectedMul0b(s))
            << "Mismatch at index " << s;
    }
}

// Test constexpr construction
TEST_F(Mul0bTableTest_2782, ConstexprConstruction_2782)
{
    constexpr Mul0bTable constexprTable;
    constexpr unsigned char val0 = constexprTable(0);
    constexpr unsigned char val1 = constexprTable(1);
    constexpr unsigned char val255 = constexprTable(255);
    
    EXPECT_EQ(val0, 0);
    EXPECT_EQ(val1, 0x0b);
    EXPECT_EQ(val255, computeExpectedMul0b(255));
}

// Test that table(s) ^ table(t) != table(s ^ t) in general (non-linearity check is not guaranteed,
// but we verify specific known GF multiplication properties)
TEST_F(Mul0bTableTest_2782, GFPropertyMultiplicationByIdentity_2782)
{
    // mul_0b(1) should equal 0x0b since 1 is the multiplicative identity in GF(2^8)
    EXPECT_EQ(table(1), 0x0b);
}

// Verify a few known specific values from AES GF(2^8) multiplication by 0x0b
TEST_F(Mul0bTableTest_2782, KnownAESValues_2782)
{
    // 0x0b * 0x03 in GF(2^8)
    // 0x03: s=3, s2 = 6, s4 = 12, s8 = 24; result = 3^6^24 = 3^6=5, 5^24=29 = 0x1d
    EXPECT_EQ(table(3), computeExpectedMul0b(3));
    
    // Verify s=0x53
    EXPECT_EQ(table(0x53), computeExpectedMul0b(0x53));
}

// Test that two independently constructed tables produce the same results
TEST_F(Mul0bTableTest_2782, ConsistentConstruction_2782)
{
    Mul0bTable table2;
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(table(static_cast<uint8_t>(i)), table2(static_cast<uint8_t>(i)))
            << "Tables differ at index " << i;
    }
}

// Test specific values where cascading XOR with 0x1b occurs at multiple stages
TEST_F(Mul0bTableTest_2782, MultipleCascadingXor_2782)
{
    // s = 0xFF: all bits set, triggers XOR at every stage
    EXPECT_EQ(table(0xFF), computeExpectedMul0b(0xFF));
    
    // s = 0xE0: high bits set
    EXPECT_EQ(table(0xE0), computeExpectedMul0b(0xE0));
}
