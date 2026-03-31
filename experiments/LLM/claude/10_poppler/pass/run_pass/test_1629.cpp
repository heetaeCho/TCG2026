#include <gtest/gtest.h>

// Declaration of the function under test
static inline unsigned int sha256Maj(unsigned int x, unsigned int y, unsigned int z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

// Test normal operation with small values
TEST(Sha256MajTest_1629, BasicValues_1629) {
    // Maj(x, y, z) = (x & y) ^ (x & z) ^ (y & z)
    // This is the "majority" function: for each bit position, returns 1 if at least 2 of the 3 inputs have 1
    
    // All zeros
    EXPECT_EQ(sha256Maj(0, 0, 0), 0u);
    
    // All ones (32-bit)
    EXPECT_EQ(sha256Maj(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF), 0xFFFFFFFF);
}

TEST(Sha256MajTest_1629, MajorityBehavior_1629) {
    // When two or more inputs have a bit set, the result should have that bit set
    // When fewer than two inputs have a bit set, the result should not have that bit set
    
    // Only x has bit set -> result 0
    EXPECT_EQ(sha256Maj(1, 0, 0), 0u);
    
    // Only y has bit set -> result 0
    EXPECT_EQ(sha256Maj(0, 1, 0), 0u);
    
    // Only z has bit set -> result 0
    EXPECT_EQ(sha256Maj(0, 0, 1), 0u);
    
    // x and y have bit set -> result 1
    EXPECT_EQ(sha256Maj(1, 1, 0), 1u);
    
    // x and z have bit set -> result 1
    EXPECT_EQ(sha256Maj(1, 0, 1), 1u);
    
    // y and z have bit set -> result 1
    EXPECT_EQ(sha256Maj(0, 1, 1), 1u);
    
    // All three have bit set -> result 1
    EXPECT_EQ(sha256Maj(1, 1, 1), 1u);
}

TEST(Sha256MajTest_1629, MultipleBitPositions_1629) {
    // Test with different bit patterns
    // x = 0b1100, y = 0b1010, z = 0b0110
    // Maj: bit3: 1,1,0 -> 1; bit2: 1,0,1 -> 1; bit1: 0,1,1 -> 1; bit0: 0,0,0 -> 0
    // Result = 0b1110 = 14
    EXPECT_EQ(sha256Maj(0xC, 0xA, 0x6), 0xEu);
}

TEST(Sha256MajTest_1629, SymmetryProperty_1629) {
    // Maj function is symmetric in all three arguments
    unsigned int a = 0xDEADBEEF;
    unsigned int b = 0xCAFEBABE;
    unsigned int c = 0x12345678;
    
    unsigned int result = sha256Maj(a, b, c);
    EXPECT_EQ(sha256Maj(a, c, b), result);
    EXPECT_EQ(sha256Maj(b, a, c), result);
    EXPECT_EQ(sha256Maj(b, c, a), result);
    EXPECT_EQ(sha256Maj(c, a, b), result);
    EXPECT_EQ(sha256Maj(c, b, a), result);
}

TEST(Sha256MajTest_1629, BoundaryValues_1629) {
    // Test with max unsigned int values
    unsigned int maxVal = 0xFFFFFFFF;
    
    EXPECT_EQ(sha256Maj(maxVal, 0, 0), 0u);
    EXPECT_EQ(sha256Maj(0, maxVal, 0), 0u);
    EXPECT_EQ(sha256Maj(0, 0, maxVal), 0u);
    EXPECT_EQ(sha256Maj(maxVal, maxVal, 0), maxVal);
    EXPECT_EQ(sha256Maj(maxVal, 0, maxVal), maxVal);
    EXPECT_EQ(sha256Maj(0, maxVal, maxVal), maxVal);
    EXPECT_EQ(sha256Maj(maxVal, maxVal, maxVal), maxVal);
}

TEST(Sha256MajTest_1629, SingleBitPatterns_1629) {
    // Test each bit position individually
    for (int i = 0; i < 32; i++) {
        unsigned int bit = 1u << i;
        
        // Single input with bit set -> 0
        EXPECT_EQ(sha256Maj(bit, 0, 0), 0u);
        
        // Two inputs with bit set -> bit
        EXPECT_EQ(sha256Maj(bit, bit, 0), bit);
        
        // All three with bit set -> bit
        EXPECT_EQ(sha256Maj(bit, bit, bit), bit);
    }
}

TEST(Sha256MajTest_1629, KnownSHA256Values_1629) {
    // Test with values commonly seen in SHA-256 operations
    unsigned int x = 0x6a09e667;
    unsigned int y = 0xbb67ae85;
    unsigned int z = 0x3c6ef372;
    
    // Compute expected: (x&y) ^ (x&z) ^ (y&z)
    unsigned int expected = (x & y) ^ (x & z) ^ (y & z);
    EXPECT_EQ(sha256Maj(x, y, z), expected);
}

TEST(Sha256MajTest_1629, AlternatingBitPatterns_1629) {
    // 0xAAAAAAAA = 10101010... and 0x55555555 = 01010101...
    unsigned int a = 0xAAAAAAAA;
    unsigned int b = 0x55555555;
    
    // Two complementary values with zero -> should be 0 (no majority)
    EXPECT_EQ(sha256Maj(a, b, 0), 0u);
    
    // Two complementary values with all-ones -> should be all-ones
    EXPECT_EQ(sha256Maj(a, b, 0xFFFFFFFF), 0xFFFFFFFF);
    
    // Same value twice -> that value (majority wins)
    EXPECT_EQ(sha256Maj(a, a, b), a);
    EXPECT_EQ(sha256Maj(b, a, b), b);
}

TEST(Sha256MajTest_1629, IdenticalInputs_1629) {
    // When all three inputs are the same, result should be that value
    unsigned int val = 0xABCD1234;
    EXPECT_EQ(sha256Maj(val, val, val), val);
    
    // When two inputs are the same, result should be determined by the pair
    // Maj(v, v, 0) = v (v has majority in every bit that's set)
    EXPECT_EQ(sha256Maj(val, val, 0), val);
    EXPECT_EQ(sha256Maj(val, 0, val), val);
    EXPECT_EQ(sha256Maj(0, val, val), val);
}
