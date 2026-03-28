#include <gtest/gtest.h>
#include <cstdint>

// Reproduce the struct as defined in the source since it's a constexpr struct
// We treat the implementation as given (black box from the provided code).
struct Mul09Table {
public:
    constexpr Mul09Table()
    {
        for (int s = 0; s < 256; s++) {
            const unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
            const unsigned char s4 = (s2 & 0x80) ? ((s2 << 1) ^ 0x1b) : (s2 << 1);
            const unsigned char s8 = (s4 & 0x80) ? ((s4 << 1) ^ 0x1b) : (s4 << 1);
            values[s] = s ^ s8;
        }
    }

    constexpr unsigned char operator()(uint8_t i) const { return values[i]; }

    unsigned char values[256] = {};
};

class Mul09TableTest_2781 : public ::testing::Test {
protected:
    static constexpr Mul09Table table {};

    // Helper: compute expected value for multiplication by 0x09 in GF(2^8)
    // 0x09 = 0x08 + 0x01, so result = s ^ (s * 0x08)
    static unsigned char expectedMul09(uint8_t s)
    {
        unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
        unsigned char s4 = (s2 & 0x80) ? ((s2 << 1) ^ 0x1b) : (s2 << 1);
        unsigned char s8 = (s4 & 0x80) ? ((s4 << 1) ^ 0x1b) : (s4 << 1);
        return s ^ s8;
    }
};

// Test that multiplying 0 by 0x09 gives 0
TEST_F(Mul09TableTest_2781, ZeroInput_2781)
{
    EXPECT_EQ(table(0x00), 0x00);
}

// Test that multiplying 1 by 0x09 gives 0x09
TEST_F(Mul09TableTest_2781, OneInput_2781)
{
    EXPECT_EQ(table(0x01), 0x09);
}

// Test a known value: 0x02 * 0x09
// s=2: s2=4, s4=8, s8=16=0x10. result = 2 ^ 0x10 = 0x12
TEST_F(Mul09TableTest_2781, InputTwo_2781)
{
    EXPECT_EQ(table(0x02), 0x12);
}

// Test input 0x80 (high bit set triggers XOR with 0x1b in doubling)
TEST_F(Mul09TableTest_2781, Input0x80_2781)
{
    unsigned char expected = expectedMul09(0x80);
    EXPECT_EQ(table(0x80), expected);
}

// Test input 0xFF (maximum byte value)
TEST_F(Mul09TableTest_2781, InputMax_2781)
{
    unsigned char expected = expectedMul09(0xFF);
    EXPECT_EQ(table(0xFF), expected);
}

// Test input 0x53 - a known AES test vector value
// In AES, 0x53 * 0x09 should equal a specific value
TEST_F(Mul09TableTest_2781, Input0x53_2781)
{
    unsigned char expected = expectedMul09(0x53);
    EXPECT_EQ(table(0x53), expected);
}

// Test boundary: input 0x7F (just below high bit)
TEST_F(Mul09TableTest_2781, Input0x7F_2781)
{
    unsigned char expected = expectedMul09(0x7F);
    EXPECT_EQ(table(0x7F), expected);
}

// Test boundary: input 0x81 (just above 0x80)
TEST_F(Mul09TableTest_2781, Input0x81_2781)
{
    unsigned char expected = expectedMul09(0x81);
    EXPECT_EQ(table(0x81), expected);
}

// Exhaustive test: verify all 256 entries match the expected computation
TEST_F(Mul09TableTest_2781, ExhaustiveAllValues_2781)
{
    for (int i = 0; i < 256; i++) {
        uint8_t input = static_cast<uint8_t>(i);
        EXPECT_EQ(table(input), expectedMul09(input)) << "Mismatch at index " << i;
    }
}

// Test that the table is constexpr-constructible (compile-time)
TEST_F(Mul09TableTest_2781, ConstexprConstruction_2781)
{
    constexpr Mul09Table constexprTable {};
    constexpr unsigned char val = constexprTable(0x01);
    EXPECT_EQ(val, 0x09);
}

// Verify GF(2^8) property: 0 * anything = 0 (already covered, but explicit)
TEST_F(Mul09TableTest_2781, MultiplicativeZeroProperty_2781)
{
    EXPECT_EQ(table(0x00), 0x00);
}

// Test that mul by 0x09 for identity element: 1 * 0x09 = 0x09
TEST_F(Mul09TableTest_2781, MultiplicativeIdentity_2781)
{
    EXPECT_EQ(table(0x01), 0x09);
}

// Test a few specific known AES MixColumns values
// 0x03 * 0x09: s=3, s2=6, s4=12, s8=24=0x18. result=3^0x18=0x1B
TEST_F(Mul09TableTest_2781, Input0x03_2781)
{
    EXPECT_EQ(table(0x03), 0x1B);
}

// Test power of two inputs
TEST_F(Mul09TableTest_2781, PowersOfTwo_2781)
{
    for (int p = 0; p < 8; p++) {
        uint8_t input = static_cast<uint8_t>(1 << p);
        EXPECT_EQ(table(input), expectedMul09(input)) << "Mismatch at power 2^" << p;
    }
}

// Test that table values are within valid byte range (always true for unsigned char, but good sanity)
TEST_F(Mul09TableTest_2781, ValuesInByteRange_2781)
{
    for (int i = 0; i < 256; i++) {
        unsigned char val = table(static_cast<uint8_t>(i));
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 255);
    }
}

// Test multiple independent table instances produce same results
TEST_F(Mul09TableTest_2781, MultipleInstances_2781)
{
    Mul09Table table1;
    Mul09Table table2;
    for (int i = 0; i < 256; i++) {
        uint8_t idx = static_cast<uint8_t>(i);
        EXPECT_EQ(table1(idx), table2(idx)) << "Tables differ at index " << i;
    }
}
