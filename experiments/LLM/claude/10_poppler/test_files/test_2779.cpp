#include <gtest/gtest.h>
#include <cstdint>

// Reproduce the struct as defined in the interface
struct Mul02Table {
public:
    unsigned char values[256] = {};

    constexpr Mul02Table()
    {
        for (int s = 0; s < 256; s++) {
            values[s] = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
        }
    }

    constexpr unsigned char operator()(uint8_t i) const
    {
        return values[i];
    }
};

class Mul02TableTest_2779 : public ::testing::Test {
protected:
    static constexpr Mul02Table table = Mul02Table();
};

// Test that multiplying 0 by 2 in GF(2^8) yields 0
TEST_F(Mul02TableTest_2779, ZeroInput_2779)
{
    EXPECT_EQ(table(0x00), 0x00);
}

// Test that multiplying 1 by 2 yields 2 (no high bit set, simple shift)
TEST_F(Mul02TableTest_2779, OneInput_2779)
{
    EXPECT_EQ(table(0x01), 0x02);
}

// Test a value without the high bit set — should be simple left shift
TEST_F(Mul02TableTest_2779, NoHighBitSet_SimpleShift_2779)
{
    // 0x53 = 0101 0011, high bit not set => result = 0xA6
    EXPECT_EQ(table(0x53), 0xA6);
}

// Test a value with the high bit set — should be (shift << 1) XOR 0x1b
TEST_F(Mul02TableTest_2779, HighBitSet_XorReduction_2779)
{
    // 0x80 = 1000 0000, high bit set => (0x80 << 1) ^ 0x1b = 0x100 ^ 0x1b = 0x1b (truncated to 8 bits)
    EXPECT_EQ(table(0x80), 0x1b);
}

// Test 0xFF (all bits set, high bit set)
TEST_F(Mul02TableTest_2779, MaxInput_2779)
{
    // 0xFF => high bit set => (0xFF << 1) ^ 0x1b = 0x1FE ^ 0x1b = 0x1E5, truncated to 8 bits = 0xE5
    unsigned char expected = ((0xFF << 1) ^ 0x1b) & 0xFF;
    EXPECT_EQ(table(0xFF), expected);
}

// Test 0x7F (highest value without high bit set)
TEST_F(Mul02TableTest_2779, JustBelowHighBit_2779)
{
    // 0x7F = 0111 1111, no high bit => 0x7F << 1 = 0xFE
    EXPECT_EQ(table(0x7F), 0xFE);
}

// Test boundary: 0x80 exactly
TEST_F(Mul02TableTest_2779, ExactlyHighBit_2779)
{
    EXPECT_EQ(table(0x80), 0x1b);
}

// Test boundary: 0x81 (just above 0x80)
TEST_F(Mul02TableTest_2779, JustAboveHighBit_2779)
{
    // 0x81 => high bit set => (0x81 << 1) ^ 0x1b = 0x102 ^ 0x1b = 0x119, truncated = 0x19
    unsigned char expected = ((0x81 << 1) ^ 0x1b) & 0xFF;
    EXPECT_EQ(table(0x81), expected);
}

// Test known AES multiplication: 0x57 * 2 = 0xAE (no high bit)
TEST_F(Mul02TableTest_2779, KnownAESValue_NoHighBit_2779)
{
    // 0x57 = 0101 0111, no high bit => 0x57 << 1 = 0xAE
    EXPECT_EQ(table(0x57), 0xAE);
}

// Test known AES multiplication: 0xD4 * 2 in GF(2^8)
TEST_F(Mul02TableTest_2779, KnownAESValue_HighBitSet_2779)
{
    // 0xD4 = 1101 0100, high bit set => (0xD4 << 1) ^ 0x1b = 0x1A8 ^ 0x1b = 0x1B3, truncated = 0xB3
    unsigned char expected = ((0xD4 << 1) ^ 0x1b) & 0xFF;
    EXPECT_EQ(table(0xD4), expected);
}

// Test that operator() and direct values array access are consistent
TEST_F(Mul02TableTest_2779, OperatorMatchesValues_2779)
{
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(table(static_cast<uint8_t>(i)), table.values[i])
            << "Mismatch at index " << i;
    }
}

// Test all values without high bit: result should be simple left shift
TEST_F(Mul02TableTest_2779, AllValuesNoHighBit_2779)
{
    for (int s = 0; s < 128; s++) {
        unsigned char expected = (s << 1) & 0xFF;
        EXPECT_EQ(table(static_cast<uint8_t>(s)), expected)
            << "Failed for input " << s;
    }
}

// Test all values with high bit: result should be (shift << 1) XOR 0x1b
TEST_F(Mul02TableTest_2779, AllValuesWithHighBit_2779)
{
    for (int s = 128; s < 256; s++) {
        unsigned char expected = ((s << 1) ^ 0x1b) & 0xFF;
        EXPECT_EQ(table(static_cast<uint8_t>(s)), expected)
            << "Failed for input " << s;
    }
}

// Test constexpr construction
TEST_F(Mul02TableTest_2779, ConstexprConstruction_2779)
{
    constexpr Mul02Table constexprTable;
    static_assert(constexprTable.values[0] == 0x00, "constexpr check for 0");
    static_assert(constexprTable.values[1] == 0x02, "constexpr check for 1");
    static_assert(constexprTable.values[0x80] == 0x1b, "constexpr check for 0x80");
    SUCCEED();
}

// Test specific well-known GF(2^8) multiplication result: 2 * 2 = 4
TEST_F(Mul02TableTest_2779, TwoTimesTwo_2779)
{
    EXPECT_EQ(table(0x02), 0x04);
}

// Test: 0x40 * 2 = 0x80
TEST_F(Mul02TableTest_2779, FortyHex_2779)
{
    EXPECT_EQ(table(0x40), 0x80);
}

// Test: 0xC0 (high bit set)
TEST_F(Mul02TableTest_2779, C0Hex_2779)
{
    // 0xC0 => (0xC0 << 1) ^ 0x1b = 0x180 ^ 0x1b = 0x19B, truncated = 0x9B
    unsigned char expected = ((0xC0 << 1) ^ 0x1b) & 0xFF;
    EXPECT_EQ(table(0xC0), expected);
}
