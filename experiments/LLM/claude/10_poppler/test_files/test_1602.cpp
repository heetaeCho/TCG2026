#include <gtest/gtest.h>

// We need to test the rotWord function which is static inline in Decrypt.cc
// Since it's a static function in a .cc file, we need to either include the source
// or redefine the function signature for testing purposes.
// Given the constraint that we treat implementation as a black box but need to test
// the interface, we'll include the function definition as it's provided.

// Reproducing the function signature exactly as given for testing
static inline unsigned int rotWord(unsigned int x) { return ((x << 8) & 0xffffffff) | (x >> 24); }

class RotWordTest_1602 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: rotating a known value
TEST_F(RotWordTest_1602, RotatesKnownValue_1602) {
    // Input: 0x01020304
    // Expected: bytes rotate left by one byte position
    // 0x01020304 -> 0x02030401
    unsigned int input = 0x01020304;
    unsigned int expected = 0x02030401;
    EXPECT_EQ(rotWord(input), expected);
}

// Test with zero input
TEST_F(RotWordTest_1602, RotatesZero_1602) {
    EXPECT_EQ(rotWord(0x00000000), 0x00000000u);
}

// Test with all bits set (0xFFFFFFFF)
TEST_F(RotWordTest_1602, RotatesAllOnes_1602) {
    EXPECT_EQ(rotWord(0xFFFFFFFF), 0xFFFFFFFFu);
}

// Test with only the most significant byte set
TEST_F(RotWordTest_1602, RotatesMSBByteOnly_1602) {
    // 0xAB000000 -> shift left 8: 0x00000000 (with masking) | (0xAB000000 >> 24 = 0xAB)
    // = 0x000000AB
    unsigned int input = 0xAB000000;
    unsigned int expected = 0x000000AB;
    EXPECT_EQ(rotWord(input), expected);
}

// Test with only the least significant byte set
TEST_F(RotWordTest_1602, RotatesLSBByteOnly_1602) {
    // 0x000000CD -> shift left 8: 0x0000CD00 | (0x000000CD >> 24 = 0x00)
    // = 0x0000CD00
    unsigned int input = 0x000000CD;
    unsigned int expected = 0x0000CD00;
    EXPECT_EQ(rotWord(input), expected);
}

// Test with second byte set
TEST_F(RotWordTest_1602, RotatesSecondByteOnly_1602) {
    // 0x00EF0000 -> shift left 8: 0xEF000000 | (0x00EF0000 >> 24 = 0x00)
    // = 0xEF000000
    unsigned int input = 0x00EF0000;
    unsigned int expected = 0xEF000000;
    EXPECT_EQ(rotWord(input), expected);
}

// Test with third byte set
TEST_F(RotWordTest_1602, RotatesThirdByteOnly_1602) {
    // 0x0000AB00 -> shift left 8: 0x00AB0000 | (0x0000AB00 >> 24 = 0x00)
    // = 0x00AB0000
    unsigned int input = 0x0000AB00;
    unsigned int expected = 0x00AB0000;
    EXPECT_EQ(rotWord(input), expected);
}

// Test rotation is equivalent to rotating bytes left by one position
TEST_F(RotWordTest_1602, EquivalentToByteRotation_1602) {
    unsigned int input = 0xDEADBEEF;
    // Bytes: DE AD BE EF -> rotated left by one byte: AD BE EF DE
    unsigned int expected = 0xADBEEFDE;
    EXPECT_EQ(rotWord(input), expected);
}

// Test that applying rotWord four times returns the original value
TEST_F(RotWordTest_1602, FourRotationsReturnOriginal_1602) {
    unsigned int original = 0x12345678;
    unsigned int result = original;
    result = rotWord(result);
    result = rotWord(result);
    result = rotWord(result);
    result = rotWord(result);
    EXPECT_EQ(result, original);
}

// Test with value 1
TEST_F(RotWordTest_1602, RotatesOne_1602) {
    // 0x00000001 -> shift left 8: 0x00000100 | (0x00000001 >> 24 = 0x00)
    // = 0x00000100
    EXPECT_EQ(rotWord(0x00000001), 0x00000100u);
}

// Test with alternating bit pattern
TEST_F(RotWordTest_1602, RotatesAlternatingBits_1602) {
    // 0xAA55AA55 -> shift left 8: 0x55AA5500 | (0xAA55AA55 >> 24 = 0xAA)
    // = 0x55AA55AA
    unsigned int input = 0xAA55AA55;
    unsigned int expected = 0x55AA55AA;
    EXPECT_EQ(rotWord(input), expected);
}

// Test with value where high bit of MSB is set (potential sign issues)
TEST_F(RotWordTest_1602, RotatesHighBitSet_1602) {
    // 0x80000000 -> shift left 8: 0x00000000 | (0x80000000 >> 24 = 0x80)
    // = 0x00000080
    unsigned int input = 0x80000000;
    unsigned int expected = 0x00000080;
    EXPECT_EQ(rotWord(input), expected);
}

// Test two consecutive rotations
TEST_F(RotWordTest_1602, TwoRotationsCorrect_1602) {
    unsigned int input = 0x11223344;
    // First rotation: 0x22334411
    // Second rotation: 0x33441122
    unsigned int result = rotWord(rotWord(input));
    EXPECT_EQ(result, 0x33441122u);
}

// Test with 0x01000000
TEST_F(RotWordTest_1602, RotatesOnlyHighByte_1602) {
    // 0x01000000 -> shift left 8: 0x00000000 | (0x01000000 >> 24 = 0x01)
    // = 0x00000001
    EXPECT_EQ(rotWord(0x01000000), 0x00000001u);
}

// Test maximum unsigned int minus one
TEST_F(RotWordTest_1602, RotatesMaxMinusOne_1602) {
    // 0xFFFFFFFE -> shift left 8: 0xFFFFFE00 | (0xFFFFFFFE >> 24 = 0xFF)
    // = 0xFFFFFEFF
    unsigned int input = 0xFFFFFFFE;
    unsigned int expected = 0xFFFFFEFF;
    EXPECT_EQ(rotWord(input), expected);
}
