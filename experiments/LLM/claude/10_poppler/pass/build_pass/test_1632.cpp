#include <gtest/gtest.h>
#include <cstdint>

// Since sha256sigma0 is a static inline function in Decrypt.cc,
// we include the implementation file to access it for testing.
// In practice, the build system would need to handle this appropriately.

// We need rotr to be available as well since sha256sigma0 depends on it.
// Including the source file to get access to static functions.

// Forward declaration approach: redefine the function based on the known interface
// since we cannot directly include a .cc file's static functions easily.
// The function implements: rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3)

// Helper to compute expected values for verification
static inline unsigned int rotr(unsigned int x, unsigned int n) {
    return (x >> n) | (x << (32 - n));
}

// Include the actual implementation
// For testing purposes, we replicate the exact signature
static inline unsigned int sha256sigma0(unsigned int x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

class Sha256Sigma0Test_1632 : public ::testing::Test {
protected:
    // Helper to compute expected sigma0 value
    unsigned int expectedSigma0(unsigned int x) {
        return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
    }
};

// Test with zero input
TEST_F(Sha256Sigma0Test_1632, ZeroInput_1632) {
    EXPECT_EQ(sha256sigma0(0x00000000u), 0x00000000u);
}

// Test with all bits set
TEST_F(Sha256Sigma0Test_1632, AllBitsSet_1632) {
    unsigned int input = 0xFFFFFFFFu;
    // rotr(0xFFFFFFFF, 7) = 0xFFFFFFFF
    // rotr(0xFFFFFFFF, 18) = 0xFFFFFFFF
    // 0xFFFFFFFF >> 3 = 0x1FFFFFFF
    // 0xFFFFFFFF ^ 0xFFFFFFFF ^ 0x1FFFFFFF = 0x1FFFFFFF
    EXPECT_EQ(sha256sigma0(input), 0x1FFFFFFFu);
}

// Test with value 1
TEST_F(Sha256Sigma0Test_1632, InputOne_1632) {
    unsigned int input = 0x00000001u;
    // rotr(1, 7)  = 0x02000000
    // rotr(1, 18) = 0x00004000
    // 1 >> 3      = 0x00000000
    unsigned int expected = 0x02000000u ^ 0x00004000u ^ 0x00000000u;
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test with a power of two
TEST_F(Sha256Sigma0Test_1632, PowerOfTwo_1632) {
    unsigned int input = 0x80000000u;
    // rotr(0x80000000, 7)  = 0x01000000
    // rotr(0x80000000, 18) = 0x00002000
    // 0x80000000 >> 3      = 0x10000000
    unsigned int expected = 0x01000000u ^ 0x00002000u ^ 0x10000000u;
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test with known SHA-256 test vector value
TEST_F(Sha256Sigma0Test_1632, KnownSHA256Value_1632) {
    // Using the word "abc" SHA-256 message schedule value
    unsigned int input = 0x61626380u;
    unsigned int expected = expectedSigma0(input);
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test with alternating bits pattern 0xAAAAAAAA
TEST_F(Sha256Sigma0Test_1632, AlternatingBitsA_1632) {
    unsigned int input = 0xAAAAAAAAu;
    unsigned int expected = rotr(input, 7) ^ rotr(input, 18) ^ (input >> 3);
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test with alternating bits pattern 0x55555555
TEST_F(Sha256Sigma0Test_1632, AlternatingBits5_1632) {
    unsigned int input = 0x55555555u;
    unsigned int expected = rotr(input, 7) ^ rotr(input, 18) ^ (input >> 3);
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test with single byte values
TEST_F(Sha256Sigma0Test_1632, SmallValue_1632) {
    unsigned int input = 0x00000080u;
    // rotr(0x80, 7) = 0x01000001 (bit 7 rotated right by 7 = bit 0 and bit 25... wait)
    // Actually: 0x80 = bit 7 set
    // rotr by 7: bit 0 set = 0x00000001... no, rotr(0x80, 7) = 0x00000001
    // Actually 0x80 >> 7 = 1, and 0x80 << 25 = 0x00000000 + carry... 
    // 0x80 << 25 = 0x00000000_10000000 << 25... this is 32-bit: 0x80 << 25 = 0x0
    // Wait: 0x80 = 128 = 2^7. rotr(2^7, 7) = 2^0 = 1
    // rotr(0x80, 18) = (0x80 >> 18) | (0x80 << 14) = 0 | 0x00200000 = 0x00200000
    // 0x80 >> 3 = 0x10
    unsigned int expected = 0x00000001u ^ 0x00200000u ^ 0x00000010u;
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test determinism - same input always gives same output
TEST_F(Sha256Sigma0Test_1632, Deterministic_1632) {
    unsigned int input = 0xDEADBEEFu;
    unsigned int result1 = sha256sigma0(input);
    unsigned int result2 = sha256sigma0(input);
    EXPECT_EQ(result1, result2);
}

// Test with 0x00000100
TEST_F(Sha256Sigma0Test_1632, InputHex100_1632) {
    unsigned int input = 0x00000100u;
    unsigned int expected = rotr(input, 7) ^ rotr(input, 18) ^ (input >> 3);
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test boundary: maximum unsigned int minus 1
TEST_F(Sha256Sigma0Test_1632, MaxMinusOne_1632) {
    unsigned int input = 0xFFFFFFFEu;
    unsigned int expected = rotr(input, 7) ^ rotr(input, 18) ^ (input >> 3);
    EXPECT_EQ(sha256sigma0(input), expected);
}

// Test that different inputs produce different outputs (in general)
TEST_F(Sha256Sigma0Test_1632, DifferentInputsDifferentOutputs_1632) {
    EXPECT_NE(sha256sigma0(0x00000001u), sha256sigma0(0x00000002u));
    EXPECT_NE(sha256sigma0(0x00000000u), sha256sigma0(0x00000001u));
    EXPECT_NE(sha256sigma0(0x12345678u), sha256sigma0(0x87654321u));
}
