#include <gtest/gtest.h>
#include <cstdint>

// Replicate the struct as defined in the partial code to test it
struct Mul03Table {
public:
    constexpr Mul03Table() {
        for (int s = 0; s < 256; s++) {
            const unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
            values[s] = s ^ s2;
        }
    }

    constexpr unsigned char operator()(uint8_t i) const {
        return values[i];
    }

private:
    unsigned char values[256] = {};
};

class Mul03TableTest_2780 : public ::testing::Test {
protected:
    static constexpr Mul03Table table{};
};

// Test that multiplying 0 by 0x03 in GF(2^8) yields 0
TEST_F(Mul03TableTest_2780, ZeroInput_2780) {
    EXPECT_EQ(table(0x00), 0x00);
}

// Test input 0x01: 0x03 * 0x01 = 0x03
// s=1: s2 = (1<<1) = 2, result = 1 ^ 2 = 3
TEST_F(Mul03TableTest_2780, OneInput_2780) {
    EXPECT_EQ(table(0x01), 0x03);
}

// Test input 0x02: s=2, s2 = 4, result = 2 ^ 4 = 6
TEST_F(Mul03TableTest_2780, TwoInput_2780) {
    EXPECT_EQ(table(0x02), 0x06);
}

// Test a value where the high bit is NOT set (s < 0x80)
// s=0x57: s2 = 0x57 << 1 = 0xAE, result = 0x57 ^ 0xAE = 0xF9
TEST_F(Mul03TableTest_2780, NormalValueNoHighBit_2780) {
    EXPECT_EQ(table(0x57), static_cast<unsigned char>(0x57 ^ 0xAE));
}

// Test boundary at 0x7F (highest value without high bit set)
// s=0x7F: s2 = 0x7F << 1 = 0xFE, result = 0x7F ^ 0xFE = 0x81
TEST_F(Mul03TableTest_2780, BoundaryBeforeHighBit_2780) {
    EXPECT_EQ(table(0x7F), static_cast<unsigned char>(0x7F ^ 0xFE));
}

// Test boundary at 0x80 (lowest value with high bit set)
// s=0x80: s2 = (0x80 << 1) ^ 0x1b = 0x100 ^ 0x1b = 0x1b (truncated to 8 bits: 0x1b)
// result = 0x80 ^ 0x1b = 0x9b
TEST_F(Mul03TableTest_2780, BoundaryAtHighBit_2780) {
    unsigned char s2 = static_cast<unsigned char>((0x80 << 1) ^ 0x1b);
    EXPECT_EQ(table(0x80), static_cast<unsigned char>(0x80 ^ s2));
}

// Test maximum value 0xFF
// s=0xFF: s2 = (0xFF << 1) ^ 0x1b = 0x1FE ^ 0x1b = 0x1E5, truncated = 0xE5
// But wait, s << 1 is done on unsigned char cast? Let's compute carefully.
// Actually the code uses (s << 1) where s is int, then XOR with 0x1b, then assigned to unsigned char.
// s=255: s << 1 = 510, 510 ^ 0x1b = 0x1FE ^ 0x1b = 0x1E5, as unsigned char = 0xE5
// result = 0xFF ^ 0xE5 = 0x1A
TEST_F(Mul03TableTest_2780, MaxInput_2780) {
    unsigned char s2 = static_cast<unsigned char>((0xFF << 1) ^ 0x1b);
    EXPECT_EQ(table(0xFF), static_cast<unsigned char>(0xFF ^ s2));
}

// Test input 0x81
// s=0x81: s2 = (0x81 << 1) ^ 0x1b = 0x102 ^ 0x1b = 0x119, truncated = 0x19
// result = 0x81 ^ 0x19 = 0x98
TEST_F(Mul03TableTest_2780, HighBitSetValue_2780) {
    unsigned char s2 = static_cast<unsigned char>((0x81 << 1) ^ 0x1b);
    EXPECT_EQ(table(0x81), static_cast<unsigned char>(0x81 ^ s2));
}

// Verify known AES multiplication by 3 result:
// In AES, 0x03 * 0x63 should give a specific value
// s=0x63: high bit not set (0x63 = 0110 0011), s2 = 0xC6, result = 0x63 ^ 0xC6 = 0xA5
TEST_F(Mul03TableTest_2780, KnownAESValue_2780) {
    EXPECT_EQ(table(0x63), static_cast<unsigned char>(0x63 ^ 0xC6));
}

// Test that the table is consistent: verify all 256 entries match the formula
TEST_F(Mul03TableTest_2780, AllEntriesConsistent_2780) {
    for (int s = 0; s < 256; s++) {
        unsigned char s2 = (s & 0x80) ? static_cast<unsigned char>((s << 1) ^ 0x1b) : static_cast<unsigned char>(s << 1);
        unsigned char expected = static_cast<unsigned char>(s ^ s2);
        EXPECT_EQ(table(static_cast<uint8_t>(s)), expected) << "Mismatch at index " << s;
    }
}

// Test that table can be used at compile time (constexpr)
TEST_F(Mul03TableTest_2780, ConstexprUsage_2780) {
    constexpr Mul03Table ct;
    constexpr unsigned char val = ct(0x01);
    EXPECT_EQ(val, 0x03);
}

// Test a few more specific small values
TEST_F(Mul03TableTest_2780, SmallValues_2780) {
    // s=3: s2 = 6, result = 3 ^ 6 = 5
    EXPECT_EQ(table(0x03), 0x05);
    // s=4: s2 = 8, result = 4 ^ 8 = 12
    EXPECT_EQ(table(0x04), 0x0C);
    // s=10: s2 = 20, result = 10 ^ 20 = 30
    EXPECT_EQ(table(0x0A), 0x1E);
}

// Test a value in the middle range without high bit
// s=0x40: s2 = 0x80, result = 0x40 ^ 0x80 = 0xC0
TEST_F(Mul03TableTest_2780, MidRangeNoHighBit_2780) {
    EXPECT_EQ(table(0x40), 0xC0);
}

// Test value 0xC0 (high bit set)
// s=0xC0: s2 = (0x180) ^ 0x1b = 0x19B, truncated = 0x9B
// result = 0xC0 ^ 0x9B = 0x5B
TEST_F(Mul03TableTest_2780, HighBitSetC0_2780) {
    unsigned char s2 = static_cast<unsigned char>((0xC0 << 1) ^ 0x1b);
    EXPECT_EQ(table(0xC0), static_cast<unsigned char>(0xC0 ^ s2));
}
