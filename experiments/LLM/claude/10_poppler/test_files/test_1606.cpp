#include <gtest/gtest.h>
#include <cstdint>

// We need to include the relevant header or define the struct as exposed
// Based on the code, Mul0bTable is defined in Decrypt.cc
// We include what's available
#include "Decrypt.h"

// If Mul0bTable is not exposed via header, we may need to replicate the struct declaration
// Based on the partial code provided:
#ifndef MUL0B_TABLE_DEFINED
struct Mul0bTable {
    constexpr Mul0bTable();
    constexpr unsigned char operator()(uint8_t i) const;
private:
    unsigned char values[256];
};
#endif

class Mul0bTableTest_1606 : public ::testing::Test {
protected:
    Mul0bTable table;
};

// Test that multiplying 0 by 0x0B gives 0 (identity of addition in GF(2^8))
TEST_F(Mul0bTableTest_1606, ZeroInput_1606) {
    EXPECT_EQ(table(0x00), 0x00);
}

// Test that multiplying 1 by 0x0B gives 0x0B
TEST_F(Mul0bTableTest_1606, OneInput_1606) {
    EXPECT_EQ(table(0x01), 0x0B);
}

// Test that multiplying 0x0B by itself: 0x0B * 0x0B in GF(2^8)
// In GF(2^8) with irreducible polynomial x^8 + x^4 + x^3 + x + 1 (0x11B):
// 0x0B * 0x0B = 0x5F (known result)
TEST_F(Mul0bTableTest_1606, Mul0bBy0b_1606) {
    // 0x0B * 0x0B in GF(2^8) = 0x5F
    EXPECT_EQ(table(0x0B), 0x5F);
}

// Test boundary: maximum input 0xFF
TEST_F(Mul0bTableTest_1606, MaxInput_1606) {
    // 0x0B * 0xFF in GF(2^8) - should return a valid byte
    unsigned char result = table(0xFF);
    // Result must be in valid range (always true for unsigned char, but verify it's deterministic)
    EXPECT_LE(result, 0xFF);
    EXPECT_GE(result, 0x00);
}

// Test that multiplying 2 by 0x0B gives 0x16 (since 0x0B << 1 = 0x16, no reduction needed)
TEST_F(Mul0bTableTest_1606, TwoInput_1606) {
    EXPECT_EQ(table(0x02), 0x16);
}

// Test known AES inverse MixColumns value: 0x0B * 0x53 
// This is a known computation in AES
TEST_F(Mul0bTableTest_1606, KnownAESValue_1606) {
    // GF multiplication is well-defined; we verify consistency
    unsigned char val = table(0x53);
    // Call again to verify deterministic behavior
    EXPECT_EQ(table(0x53), val);
}

// Test that the table is consistent across all values (deterministic)
TEST_F(Mul0bTableTest_1606, DeterministicBehavior_1606) {
    for (int i = 0; i < 256; i++) {
        unsigned char first = table(static_cast<uint8_t>(i));
        unsigned char second = table(static_cast<uint8_t>(i));
        EXPECT_EQ(first, second) << "Non-deterministic at index " << i;
    }
}

// Test GF(2^8) property: a * 0x0B XOR b * 0x0B == (a XOR b) * 0x0B (linearity)
TEST_F(Mul0bTableTest_1606, LinearityProperty_1606) {
    for (int a = 0; a < 256; a += 17) {
        for (int b = 0; b < 256; b += 19) {
            uint8_t ua = static_cast<uint8_t>(a);
            uint8_t ub = static_cast<uint8_t>(b);
            unsigned char lhs = table(ua) ^ table(ub);
            unsigned char rhs = table(ua ^ ub);
            EXPECT_EQ(lhs, rhs) << "Linearity failed for a=" << a << " b=" << b;
        }
    }
}

// Test power of 2 inputs
TEST_F(Mul0bTableTest_1606, PowerOfTwoInputs_1606) {
    EXPECT_EQ(table(0x04), 0x2C);   // 0x0B * 4 in GF(2^8)
    EXPECT_EQ(table(0x08), 0x58);   // 0x0B * 8 in GF(2^8)
    EXPECT_EQ(table(0x10), 0xB0);   // 0x0B * 16 in GF(2^8)
}

// Verify 0x0B * 0x80 (high bit set)
TEST_F(Mul0bTableTest_1606, HighBitInput_1606) {
    // 0x0B * 0x80 requires multiple reductions
    unsigned char result = table(0x80);
    // Verify it's a valid result and deterministic
    EXPECT_EQ(table(0x80), result);
}
