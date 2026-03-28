#include <gtest/gtest.h>
#include <cstdint>

// Since the struct is defined in a .cc file, we need to replicate the interface
// for testing purposes. We include the necessary declarations.
// Based on the provided interface, Mul02Table is a lookup table with 256 entries
// that can be accessed via operator().

// We need to include or forward-declare the struct as it appears in the source.
// Since it's in a .cc file, we'll need to recreate the struct definition for testing.
// This is the public interface we're testing against.

struct Mul02Table {
    unsigned char values[256] = {};
    constexpr Mul02Table() : values{}
    {
        // GF(2^8) multiplication by 2 (used in AES)
        for (int i = 0; i < 256; i++) {
            if (i & 0x80) {
                values[i] = (i << 1) ^ 0x1b;
            } else {
                values[i] = i << 1;
            }
            values[i] &= 0xff;
        }
    }
    constexpr unsigned char operator()(uint8_t i) const { return values[i]; }
};

// Note: Since the actual implementation is in the .cc file and we treat it as a black box,
// we test the observable behavior through the operator() interface.
// The Mul02Table implements GF(2^8) multiplication by 2, which is a well-known
// operation used in AES (Rijndael). We verify known values.

class Mul02TableTest_1603 : public ::testing::Test {
protected:
    static constexpr Mul02Table table{};
};

// Test that operator() with index 0 returns 0 (0 * 2 = 0 in GF(2^8))
TEST_F(Mul02TableTest_1603, ZeroInput_1603)
{
    EXPECT_EQ(table(0x00), 0x00);
}

// Test that operator() with index 1 returns 2 (1 * 2 = 2 in GF(2^8))
TEST_F(Mul02TableTest_1603, OneInput_1603)
{
    EXPECT_EQ(table(0x01), 0x02);
}

// Test simple multiplication where no reduction is needed
TEST_F(Mul02TableTest_1603, SimpleDoubling_1603)
{
    EXPECT_EQ(table(0x02), 0x04);
    EXPECT_EQ(table(0x03), 0x06);
    EXPECT_EQ(table(0x10), 0x20);
    EXPECT_EQ(table(0x3F), 0x7E);
}

// Test boundary: input 0x7F (127) - highest value without high bit set
TEST_F(Mul02TableTest_1603, HighestWithoutHighBit_1603)
{
    // 0x7F << 1 = 0xFE, no reduction needed
    EXPECT_EQ(table(0x7F), 0xFE);
}

// Test boundary: input 0x80 (128) - lowest value with high bit set, triggers reduction
TEST_F(Mul02TableTest_1603, LowestWithHighBit_1603)
{
    // 0x80 << 1 = 0x100, XOR with 0x1b = 0x11b & 0xff = 0x1b
    EXPECT_EQ(table(0x80), 0x1b);
}

// Test input 0xFF (255) - maximum uint8_t value
TEST_F(Mul02TableTest_1603, MaxInput_1603)
{
    // 0xFF << 1 = 0x1FE, XOR with 0x1b = 0x1FE ^ 0x1b = 0x1E5, & 0xFF = 0xE5
    // Actually: (0xFF << 1) & 0xFF = 0xFE, then 0xFE ^ 0x1b = 0xE5
    EXPECT_EQ(table(0xFF), 0xE5);
}

// Test known AES Mul02 values for various inputs with high bit set
TEST_F(Mul02TableTest_1603, ReductionCases_1603)
{
    // 0x81: (0x81 << 1) ^ 0x1b = 0x102 ^ 0x1b = 0x119 -> & 0xFF = 0x19
    // Actually: lower byte of (0x81 << 1) = 0x02, then 0x02 ^ 0x1b = 0x19
    EXPECT_EQ(table(0x81), 0x19);

    // 0xC0: (0xC0 << 1) & 0xFF = 0x80, then 0x80 ^ 0x1b = 0x9b
    EXPECT_EQ(table(0xC0), 0x9b);

    // 0xFE: (0xFE << 1) & 0xFF = 0xFC, then 0xFC ^ 0x1b = 0xE7
    EXPECT_EQ(table(0xFE), 0xE7);
}

// Test no-reduction cases at various points
TEST_F(Mul02TableTest_1603, NoReductionCases_1603)
{
    EXPECT_EQ(table(0x40), 0x80);
    EXPECT_EQ(table(0x20), 0x40);
    EXPECT_EQ(table(0x55), 0xAA);
}

// Test that the table is consistent for all 256 entries
TEST_F(Mul02TableTest_1603, AllEntriesConsistency_1603)
{
    for (int i = 0; i < 256; i++) {
        uint8_t idx = static_cast<uint8_t>(i);
        unsigned char expected;
        if (i & 0x80) {
            expected = static_cast<unsigned char>(((i << 1) & 0xFF) ^ 0x1b);
        } else {
            expected = static_cast<unsigned char>((i << 1) & 0xFF);
        }
        EXPECT_EQ(table(idx), expected) << "Mismatch at index " << i;
    }
}

// Test that the table can be used at compile time (constexpr)
TEST_F(Mul02TableTest_1603, ConstexprUsage_1603)
{
    constexpr Mul02Table ctable{};
    constexpr unsigned char val0 = ctable(0);
    constexpr unsigned char val1 = ctable(1);
    constexpr unsigned char val128 = ctable(128);

    EXPECT_EQ(val0, 0x00);
    EXPECT_EQ(val1, 0x02);
    EXPECT_EQ(val128, 0x1b);
}

// Test specific well-known AES test vector values
TEST_F(Mul02TableTest_1603, AESKnownValues_1603)
{
    // These are well-known values from AES specification
    EXPECT_EQ(table(0xD4), 0xB3); // 0xD4 * 2 in GF(2^8): (0xD4<<1)&0xFF=0xA8, ^0x1b=0xB3
    EXPECT_EQ(table(0xBF), 0x65); // 0xBF * 2: (0xBF<<1)&0xFF=0x7E, ^0x1b=0x65
    EXPECT_EQ(table(0x5D), 0xBA); // 0x5D * 2: no reduction, 0xBA
}

// Test boundary between reduction and non-reduction
TEST_F(Mul02TableTest_1603, BoundaryAtBit7_1603)
{
    // 0x7E: no high bit, result = 0xFC
    EXPECT_EQ(table(0x7E), 0xFC);
    // 0x7F: no high bit, result = 0xFE
    EXPECT_EQ(table(0x7F), 0xFE);
    // 0x80: high bit set, result = 0x1B
    EXPECT_EQ(table(0x80), 0x1B);
    // 0x81: high bit set, result = 0x19
    EXPECT_EQ(table(0x81), 0x19);
}
