#include <gtest/gtest.h>
#include <cstdint>

// Reproduce the Mul0eTable struct as defined in the source
struct Mul0eTable {
public:
    constexpr Mul0eTable() : values{}
    {
        for (int s = 0; s < 256; s++) {
            const unsigned char s2 = (s & 0x80) ? ((s << 1) ^ 0x1b) : (s << 1);
            const unsigned char s4 = (s2 & 0x80) ? ((s2 << 1) ^ 0x1b) : (s2 << 1);
            const unsigned char s8 = (s4 & 0x80) ? ((s4 << 1) ^ 0x1b) : (s4 << 1);
            values[s] = s2 ^ s4 ^ s8;
        }
    }

    constexpr unsigned char operator()(uint8_t i) const { return values[i]; }

private:
    unsigned char values[256];
};

// Helper function to compute GF(2^8) multiplication by 0x0e
// 0x0e = 14 = 8 + 4 + 2, so mul_0e(s) = s*2 ^ s*4 ^ s*8 in GF(2^8)
static unsigned char gf_mul(unsigned char a, unsigned char b)
{
    unsigned char result = 0;
    unsigned char temp = a;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= temp;
        }
        bool high_bit = (temp & 0x80) != 0;
        temp <<= 1;
        if (high_bit) {
            temp ^= 0x1b;
        }
        b >>= 1;
    }
    return result;
}

class Mul0eTableTest_2784 : public ::testing::Test {
protected:
    static constexpr Mul0eTable table {};
};

// Test that multiplying 0 by 0x0e gives 0
TEST_F(Mul0eTableTest_2784, ZeroInput_2784)
{
    EXPECT_EQ(table(0), 0);
}

// Test that multiplying 1 by 0x0e gives 0x0e
TEST_F(Mul0eTableTest_2784, OneInput_2784)
{
    EXPECT_EQ(table(1), 0x0e);
}

// Test boundary value: input 0xFF
TEST_F(Mul0eTableTest_2784, MaxInput_2784)
{
    unsigned char expected = gf_mul(0xFF, 0x0e);
    EXPECT_EQ(table(0xFF), expected);
}

// Test boundary value: input 0x80 (high bit set)
TEST_F(Mul0eTableTest_2784, HighBitInput_2784)
{
    unsigned char expected = gf_mul(0x80, 0x0e);
    EXPECT_EQ(table(0x80), expected);
}

// Test boundary value: input 0x7F (just below high bit)
TEST_F(Mul0eTableTest_2784, JustBelowHighBit_2784)
{
    unsigned char expected = gf_mul(0x7F, 0x0e);
    EXPECT_EQ(table(0x7F), expected);
}

// Test input 0x02
TEST_F(Mul0eTableTest_2784, InputTwo_2784)
{
    unsigned char expected = gf_mul(0x02, 0x0e);
    EXPECT_EQ(table(0x02), expected);
}

// Test input 0x53 (known AES S-box related value)
TEST_F(Mul0eTableTest_2784, InputMidRange_2784)
{
    unsigned char expected = gf_mul(0x53, 0x0e);
    EXPECT_EQ(table(0x53), expected);
}

// Test all 256 values match reference GF multiplication by 0x0e
TEST_F(Mul0eTableTest_2784, AllValuesMatchReferenceMul0e_2784)
{
    for (int i = 0; i < 256; i++) {
        unsigned char expected = gf_mul(static_cast<unsigned char>(i), 0x0e);
        EXPECT_EQ(table(static_cast<uint8_t>(i)), expected)
            << "Mismatch at index " << i;
    }
}

// Test that table is constexpr-constructible (compile-time check)
TEST_F(Mul0eTableTest_2784, ConstexprConstruction_2784)
{
    constexpr Mul0eTable constexpr_table {};
    EXPECT_EQ(constexpr_table(0), 0);
    EXPECT_EQ(constexpr_table(1), 0x0e);
}

// Test specific known values for AES InvMixColumns
// For s=0xdb, 0x0e * 0xdb should yield a known result
TEST_F(Mul0eTableTest_2784, KnownAESValue_0xdb_2784)
{
    unsigned char expected = gf_mul(0xdb, 0x0e);
    EXPECT_EQ(table(0xdb), expected);
}

// Test input 0x0e (multiply 0x0e by itself in GF)
TEST_F(Mul0eTableTest_2784, Input0x0e_2784)
{
    unsigned char expected = gf_mul(0x0e, 0x0e);
    EXPECT_EQ(table(0x0e), expected);
}

// Test powers of two
TEST_F(Mul0eTableTest_2784, PowersOfTwo_2784)
{
    for (int bit = 0; bit < 8; bit++) {
        uint8_t val = 1 << bit;
        unsigned char expected = gf_mul(val, 0x0e);
        EXPECT_EQ(table(val), expected) << "Mismatch at power of two: " << (int)val;
    }
}

// Test that two separate table instances produce the same results
TEST_F(Mul0eTableTest_2784, ConsistencyBetweenInstances_2784)
{
    Mul0eTable table2;
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(table(static_cast<uint8_t>(i)), table2(static_cast<uint8_t>(i)))
            << "Inconsistency at index " << i;
    }
}
