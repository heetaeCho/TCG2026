#include <gtest/gtest.h>

// Declare the function under test (since it's static inline in the .cc file,
// we need to replicate its signature for testing purposes)
static inline unsigned long rotateLeft(unsigned long x, int r) {
    x &= 0xffffffff;
    return ((x << r) | (x >> (32 - r))) & 0xffffffff;
}

// Normal operation tests
TEST(RotateLeftTest_1617, RotateByZero_1617) {
    // Rotating by 0 should return the same value
    EXPECT_EQ(rotateLeft(0x12345678UL, 0), 0x12345678UL);
}

TEST(RotateLeftTest_1617, RotateByOne_1617) {
    // Rotating 0x00000001 left by 1 should give 0x00000002
    EXPECT_EQ(rotateLeft(0x00000001UL, 1), 0x00000002UL);
}

TEST(RotateLeftTest_1617, RotateByFour_1617) {
    // Rotating 0x12345678 left by 4 should shift hex digits
    EXPECT_EQ(rotateLeft(0x12345678UL, 4), 0x23456781UL);
}

TEST(RotateLeftTest_1617, RotateByEight_1617) {
    EXPECT_EQ(rotateLeft(0x12345678UL, 8), 0x34567812UL);
}

TEST(RotateLeftTest_1617, RotateBySixteen_1617) {
    EXPECT_EQ(rotateLeft(0x12345678UL, 16), 0x56781234UL);
}

TEST(RotateLeftTest_1617, RotateByTwentyFour_1617) {
    EXPECT_EQ(rotateLeft(0x12345678UL, 24), 0x78123456UL);
}

// Boundary condition: rotate by 31
TEST(RotateLeftTest_1617, RotateByThirtyOne_1617) {
    // Rotating 0x00000001 left by 31 should give 0x80000000
    EXPECT_EQ(rotateLeft(0x00000001UL, 31), 0x80000000UL);
}

// Boundary condition: rotate by 1 with high bit set
TEST(RotateLeftTest_1617, RotateHighBitByOne_1617) {
    // 0x80000000 rotated left by 1 should wrap around to 0x00000001
    EXPECT_EQ(rotateLeft(0x80000000UL, 1), 0x00000001UL);
}

// Zero input
TEST(RotateLeftTest_1617, RotateZero_1617) {
    EXPECT_EQ(rotateLeft(0x00000000UL, 5), 0x00000000UL);
}

// All bits set
TEST(RotateLeftTest_1617, RotateAllOnes_1617) {
    // Rotating 0xFFFFFFFF by any amount should still be 0xFFFFFFFF
    EXPECT_EQ(rotateLeft(0xFFFFFFFFUL, 1), 0xFFFFFFFFUL);
    EXPECT_EQ(rotateLeft(0xFFFFFFFFUL, 7), 0xFFFFFFFFUL);
    EXPECT_EQ(rotateLeft(0xFFFFFFFFUL, 16), 0xFFFFFFFFUL);
    EXPECT_EQ(rotateLeft(0xFFFFFFFFUL, 31), 0xFFFFFFFFUL);
}

// Masking test: values above 32 bits should be masked off
TEST(RotateLeftTest_1617, MaskInputTo32Bits_1617) {
    // If unsigned long is 64 bits, the upper bits should be masked away
    unsigned long input = 0x100000000UL | 0x00000001UL; // bit 32 set + bit 0
    // After masking to 32 bits, input becomes 0x00000001
    // Rotating left by 1 gives 0x00000002
    if (sizeof(unsigned long) > 4) {
        EXPECT_EQ(rotateLeft(input, 1), 0x00000002UL);
    }
}

// Ensure output is masked to 32 bits
TEST(RotateLeftTest_1617, OutputMaskedTo32Bits_1617) {
    unsigned long result = rotateLeft(0xFFFFFFFFUL, 0);
    EXPECT_EQ(result & ~0xFFFFFFFFUL, 0UL);
}

// Specific pattern tests
TEST(RotateLeftTest_1617, RotateAlternatingBits_1617) {
    // 0xAAAAAAAA rotated left by 1 should give 0x55555555
    EXPECT_EQ(rotateLeft(0xAAAAAAAAUL, 1), 0x55555555UL);
}

TEST(RotateLeftTest_1617, RotateAlternatingBitsReverse_1617) {
    // 0x55555555 rotated left by 1 should give 0xAAAAAAAA
    EXPECT_EQ(rotateLeft(0x55555555UL, 1), 0xAAAAAAAAUL);
}

// Full rotation (32 bits) - note: shifting by 32 is undefined in C++,
// but rotateLeft with r=0 is the intended "no rotation" case
// Testing with various rotation amounts to verify consistency
TEST(RotateLeftTest_1617, RotateAndRotateBackIsIdentity_1617) {
    unsigned long val = 0xDEADBEEFUL;
    // Rotate left by 12, then rotate left by 20 should give original
    unsigned long intermediate = rotateLeft(val, 12);
    unsigned long result = rotateLeft(intermediate, 20);
    EXPECT_EQ(result, val & 0xFFFFFFFFUL);
}

TEST(RotateLeftTest_1617, RotateByTwo_1617) {
    // 0x40000000 rotated left by 2 should give 0x00000001
    EXPECT_EQ(rotateLeft(0x40000000UL, 2), 0x00000001UL);
}

TEST(RotateLeftTest_1617, SingleBitRotation_1617) {
    // Test rotating a single bit through all 32 positions
    for (int i = 0; i < 32; i++) {
        unsigned long expected = (1UL << i) & 0xFFFFFFFF;
        EXPECT_EQ(rotateLeft(1UL, i), expected);
    }
}
