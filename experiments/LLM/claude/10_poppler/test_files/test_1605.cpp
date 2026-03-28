#include <gtest/gtest.h>
#include <cstdint>

// We need to include or replicate the struct definition since it's defined in a .cc file
// Based on the provided interface, Mul09Table has a constructor and operator()
// We'll include the necessary header or define the struct based on the known interface

// Since Mul09Table is defined in Decrypt.cc, we need to access it.
// In practice, we'd include the appropriate header. For testing purposes,
// we replicate the known interface.

// Forward declaration approach - include the actual source
// The struct is in the .cc file, so we may need to include it directly
#include "poppler/Decrypt.cc"

class Mul09TableTest_1605 : public ::testing::Test {
protected:
    Mul09Table table;
};

// Test that the table can be constructed
TEST_F(Mul09TableTest_1605, Construction_1605) {
    Mul09Table t;
    // If construction succeeds without throwing, the test passes
    SUCCEED();
}

// Test operator() with input 0
TEST_F(Mul09TableTest_1605, ZeroInput_1605) {
    // In GF(2^8) multiplication, anything times 0 should be 0
    // 0x09 * 0x00 = 0x00
    uint8_t result = table(0);
    EXPECT_EQ(result, 0x00);
}

// Test operator() with input 1
TEST_F(Mul09TableTest_1605, OneInput_1605) {
    // In GF(2^8), 0x09 * 0x01 = 0x09
    uint8_t result = table(1);
    EXPECT_EQ(result, 0x09);
}

// Test operator() with maximum input value 255
TEST_F(Mul09TableTest_1605, MaxInput_1605) {
    // 0x09 * 0xFF in GF(2^8) - should return a valid byte value
    uint8_t result = table(255);
    // Result should be a valid byte (0-255), which is guaranteed by return type
    EXPECT_LE(result, 255);
    EXPECT_GE(result, 0);
}

// Test operator() with input 2
TEST_F(Mul09TableTest_1605, InputTwo_1605) {
    // 0x09 * 0x02 in GF(2^8) = 0x12
    uint8_t result = table(2);
    EXPECT_EQ(result, 0x12);
}

// Test that the table is constexpr-constructible
TEST_F(Mul09TableTest_1605, ConstexprConstruction_1605) {
    constexpr Mul09Table constexprTable;
    // Verify it works at compile time
    SUCCEED();
}

// Test operator() is consistent - calling with same input gives same result
TEST_F(Mul09TableTest_1605, Consistency_1605) {
    for (int i = 0; i < 256; ++i) {
        uint8_t first = table(static_cast<uint8_t>(i));
        uint8_t second = table(static_cast<uint8_t>(i));
        EXPECT_EQ(first, second) << "Inconsistent result for input " << i;
    }
}

// Test all 256 possible inputs don't crash
TEST_F(Mul09TableTest_1605, AllInputs_1605) {
    for (int i = 0; i < 256; ++i) {
        EXPECT_NO_THROW(table(static_cast<uint8_t>(i))) << "Threw for input " << i;
    }
}

// Test GF(2^8) property: mul by 0x09 where input is a power of 2
TEST_F(Mul09TableTest_1605, PowerOfTwoInputs_1605) {
    // 0x09 * 0x04 in GF(2^8) = 0x24
    uint8_t result = table(4);
    EXPECT_EQ(result, 0x24);
}

// Test with identity-like values
TEST_F(Mul09TableTest_1605, InputHex09_1605) {
    // 0x09 * 0x09 in GF(2^8)
    uint8_t result = table(0x09);
    // 0x09 * 0x09 = 0x51 in GF(2^8) with irreducible polynomial 0x11B
    EXPECT_EQ(result, 0x51);
}

// Test boundary value 128 (0x80)
TEST_F(Mul09TableTest_1605, Input128_1605) {
    uint8_t result = table(0x80);
    // Should return a deterministic value
    uint8_t result2 = table(0x80);
    EXPECT_EQ(result, result2);
}

// Test that different inputs can produce different outputs
TEST_F(Mul09TableTest_1605, DifferentInputsDifferentOutputs_1605) {
    // 0 and 1 should produce different results
    EXPECT_NE(table(0), table(1));
}
