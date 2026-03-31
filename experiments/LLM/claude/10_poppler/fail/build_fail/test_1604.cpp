#include <gtest/gtest.h>
#include <cstdint>

// We need to include the relevant header or replicate the struct definition
// Based on the partial code, Mul03Table is a lookup table struct with operator()
// Since we're told to treat it as a black box, we include the actual header.

// The Mul03Table is part of Decrypt.cc in poppler. We need to access it.
// Based on the interface, it's a constexpr struct with a lookup table for
// multiplication by 0x03 in GF(2^8) used in AES.

// Reconstruct the minimal interface needed for testing
// Since the struct is defined in Decrypt.cc (not a header), we may need to
// replicate the interface for testing purposes.

// GF(2^8) multiplication by 3: mul(a, 0x03) = a ^ mul(a, 0x02)
// where mul(a, 0x02) = (a << 1) ^ (a & 0x80 ? 0x1b : 0x00)
// So mul(a, 0x03) = a ^ ((a << 1) ^ (a & 0x80 ? 0x1b : 0x00))

// We include the source to get access to the struct
// In practice, this would be exposed via a header
#include "Decrypt.cc"

class Mul03TableTest_1604 : public ::testing::Test {
protected:
    Mul03Table table;
};

// Helper: compute expected GF(2^8) multiplication by 0x03
static unsigned char gf_mul03(uint8_t a) {
    // mul by 2 in GF(2^8)
    unsigned char mul2 = (a << 1) ^ ((a & 0x80) ? 0x1b : 0x00);
    // mul by 3 = mul by 2 XOR original
    return mul2 ^ a;
}

TEST_F(Mul03TableTest_1604, ZeroInput_1604) {
    // 0x03 * 0x00 should be 0x00 in GF(2^8)
    EXPECT_EQ(table(0x00), gf_mul03(0x00));
    EXPECT_EQ(table(0x00), 0x00);
}

TEST_F(Mul03TableTest_1604, OneInput_1604) {
    // 0x03 * 0x01 should be 0x03
    EXPECT_EQ(table(0x01), gf_mul03(0x01));
    EXPECT_EQ(table(0x01), 0x03);
}

TEST_F(Mul03TableTest_1604, InputTwo_1604) {
    // 0x03 * 0x02
    EXPECT_EQ(table(0x02), gf_mul03(0x02));
}

TEST_F(Mul03TableTest_1604, InputThree_1604) {
    // 0x03 * 0x03
    EXPECT_EQ(table(0x03), gf_mul03(0x03));
}

TEST_F(Mul03TableTest_1604, MaxInput_1604) {
    // 0x03 * 0xFF
    EXPECT_EQ(table(0xFF), gf_mul03(0xFF));
}

TEST_F(Mul03TableTest_1604, Input0x80_1604) {
    // Boundary: highest bit set triggers XOR with 0x1b in mul by 2
    EXPECT_EQ(table(0x80), gf_mul03(0x80));
}

TEST_F(Mul03TableTest_1604, Input0x7F_1604) {
    // Boundary: highest bit not set
    EXPECT_EQ(table(0x7F), gf_mul03(0x7F));
}

TEST_F(Mul03TableTest_1604, Input0x40_1604) {
    EXPECT_EQ(table(0x40), gf_mul03(0x40));
}

TEST_F(Mul03TableTest_1604, Input0xC0_1604) {
    EXPECT_EQ(table(0xC0), gf_mul03(0xC0));
}

TEST_F(Mul03TableTest_1604, AllValuesMatchGFMul03_1604) {
    // Exhaustively verify all 256 possible inputs
    for (int i = 0; i < 256; i++) {
        uint8_t input = static_cast<uint8_t>(i);
        EXPECT_EQ(table(input), gf_mul03(input))
            << "Mismatch at input 0x" << std::hex << i;
    }
}

TEST_F(Mul03TableTest_1604, ConsistentResults_1604) {
    // Calling operator() multiple times with the same input should return the same result
    for (int i = 0; i < 256; i++) {
        uint8_t input = static_cast<uint8_t>(i);
        unsigned char first = table(input);
        unsigned char second = table(input);
        EXPECT_EQ(first, second) << "Inconsistent result at input " << i;
    }
}

TEST_F(Mul03TableTest_1604, KnownAESValues_1604) {
    // Some known values from AES GF(2^8) multiplication by 3
    // 0x03 * 0x53 = 0xf5 (well-known AES test vector related)
    EXPECT_EQ(table(0x53), gf_mul03(0x53));
    
    // 0x03 * 0xD4 
    EXPECT_EQ(table(0xD4), gf_mul03(0xD4));
}

TEST_F(Mul03TableTest_1604, ReturnTypeIsUnsignedChar_1604) {
    // Verify the return type is unsigned char (no sign extension issues)
    auto result = table(0xFF);
    static_assert(std::is_same<decltype(result), unsigned char>::value,
                  "Return type should be unsigned char");
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 255);
}

TEST_F(Mul03TableTest_1604, MultipleInstances_1604) {
    // Two instances should produce identical results
    Mul03Table table2;
    for (int i = 0; i < 256; i++) {
        uint8_t input = static_cast<uint8_t>(i);
        EXPECT_EQ(table(input), table2(input))
            << "Different instances disagree at input " << i;
    }
}
