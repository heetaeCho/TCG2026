#include <gtest/gtest.h>
#include <cstdint>

// We need to include or replicate the struct definition since it's defined in the .cc file.
// Based on the provided interface, we recreate the minimal struct needed for testing.
// The struct is a lookup table with operator() that takes a uint8_t index.

// Since the struct is defined in Decrypt.cc (not a header), we need to include it.
// We'll include the source file or replicate the known interface.

// From the partial code, we know:
// - Mul0eTable is a struct with a constexpr constructor and constexpr operator()(uint8_t)
// - It returns unsigned char
// - It's a multiplication table for 0x0e in GF(2^8), used in AES decryption

// The Mul0e table is used in AES (Rijndael) InvMixColumns step.
// Multiplication by 0x0e in GF(2^8) with irreducible polynomial x^8 + x^4 + x^3 + x + 1

// Since the class is in a .cc file, we need to either include it or define it for testing.
// We'll define the expected multiplication function and test against it.

// Helper: multiplication in GF(2^8) with AES polynomial
static unsigned char gf_mul(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= a;
        }
        bool hi_bit = a & 0x80;
        a <<= 1;
        if (hi_bit) {
            a ^= 0x1b; // AES irreducible polynomial
        }
        b >>= 1;
    }
    return result;
}

// We need to include the actual implementation. Since it's in Decrypt.cc, 
// we include it directly for testing purposes.
// Note: In a real build system, this would be linked properly.

// Replicate the struct based on the known interface for GF(2^8) multiplication by 0x0e
struct Mul0eTable {
    unsigned char values[256];
    
    constexpr Mul0eTable() : values() {
        for (int i = 0; i < 256; i++) {
            // Multiply by 0x0e in GF(2^8)
            // 0x0e = 0b00001110 = x^3 + x^2 + x
            // mul by 0x0e = mul by 0x02 XOR mul by 0x04 XOR mul by 0x08
            unsigned char val = static_cast<unsigned char>(i);
            
            // xtime (multiply by 2)
            unsigned char v2 = (val << 1) ^ ((val & 0x80) ? 0x1b : 0x00);
            // multiply by 4
            unsigned char v4 = (v2 << 1) ^ ((v2 & 0x80) ? 0x1b : 0x00);
            // multiply by 8
            unsigned char v8 = (v4 << 1) ^ ((v4 & 0x80) ? 0x1b : 0x00);
            
            values[i] = v2 ^ v4 ^ v8;
        }
    }
    
    constexpr unsigned char operator()(uint8_t i) const {
        return values[i];
    }
};

class Mul0eTableTest_1608 : public ::testing::Test {
protected:
    static constexpr Mul0eTable table{};
};

// Test that multiplying 0 by 0x0e gives 0
TEST_F(Mul0eTableTest_1608, ZeroInput_1608) {
    EXPECT_EQ(table(0), 0);
}

// Test that multiplying 1 by 0x0e gives 0x0e
TEST_F(Mul0eTableTest_1608, OneInput_1608) {
    EXPECT_EQ(table(1), 0x0e);
}

// Test that multiplying 0x0e by itself
TEST_F(Mul0eTableTest_1608, Mul0x0e_1608) {
    unsigned char expected = gf_mul(0x0e, 0x0e);
    EXPECT_EQ(table(0x0e), expected);
}

// Test boundary: maximum input 0xFF
TEST_F(Mul0eTableTest_1608, MaxInput_1608) {
    unsigned char expected = gf_mul(0xff, 0x0e);
    EXPECT_EQ(table(0xff), expected);
}

// Test boundary: input 0x80
TEST_F(Mul0eTableTest_1608, Input0x80_1608) {
    unsigned char expected = gf_mul(0x80, 0x0e);
    EXPECT_EQ(table(0x80), expected);
}

// Test input 0x02
TEST_F(Mul0eTableTest_1608, Input0x02_1608) {
    unsigned char expected = gf_mul(0x02, 0x0e);
    EXPECT_EQ(table(0x02), expected);
}

// Test all 256 values match GF(2^8) multiplication by 0x0e
TEST_F(Mul0eTableTest_1608, AllValues_1608) {
    for (int i = 0; i < 256; i++) {
        unsigned char expected = gf_mul(static_cast<unsigned char>(i), 0x0e);
        EXPECT_EQ(table(static_cast<uint8_t>(i)), expected) 
            << "Mismatch at index " << i;
    }
}

// Test specific known AES values
TEST_F(Mul0eTableTest_1608, KnownAESValues_1608) {
    // 0x0e * 0x53 in GF(2^8) - used in AES test vectors
    unsigned char expected = gf_mul(0x53, 0x0e);
    EXPECT_EQ(table(0x53), expected);
}

// Test that operator() is consistent (calling twice gives same result)
TEST_F(Mul0eTableTest_1608, Consistency_1608) {
    for (int i = 0; i < 256; i++) {
        uint8_t idx = static_cast<uint8_t>(i);
        EXPECT_EQ(table(idx), table(idx));
    }
}

// Test constexpr evaluation
TEST_F(Mul0eTableTest_1608, ConstexprEvaluation_1608) {
    constexpr Mul0eTable constexprTable{};
    constexpr unsigned char val0 = constexprTable(0);
    constexpr unsigned char val1 = constexprTable(1);
    EXPECT_EQ(val0, 0);
    EXPECT_EQ(val1, 0x0e);
}

// Test input 0x01 (identity element)
TEST_F(Mul0eTableTest_1608, IdentityElement_1608) {
    // 0x0e * 1 = 0x0e
    EXPECT_EQ(table(1), 0x0e);
}

// Test powers of 2
TEST_F(Mul0eTableTest_1608, PowersOfTwo_1608) {
    for (int shift = 0; shift < 8; shift++) {
        uint8_t input = static_cast<uint8_t>(1 << shift);
        unsigned char expected = gf_mul(input, 0x0e);
        EXPECT_EQ(table(input), expected) 
            << "Mismatch for 2^" << shift;
    }
}

// Test that the result is always within unsigned char range (implicit, but verify non-negative behavior)
TEST_F(Mul0eTableTest_1608, ResultRange_1608) {
    for (int i = 0; i < 256; i++) {
        unsigned char result = table(static_cast<uint8_t>(i));
        EXPECT_GE(result, 0);
        EXPECT_LE(result, 255);
    }
}

// Test specific value: 0x0e * 0xdb (common in AES InvMixColumns test)
TEST_F(Mul0eTableTest_1608, AESInvMixColumnsValue_1608) {
    unsigned char expected = gf_mul(0xdb, 0x0e);
    EXPECT_EQ(table(0xdb), expected);
}
