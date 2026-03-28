#include <gtest/gtest.h>
#include <cstdint>

// To access the static inline function, we include the .cc file directly.
// This brings static functions into this translation unit.
// We need to handle any dependencies that Decrypt.cc may have.
#include "config.h"
#include "poppler/Decrypt.cc"

class Sha512Sigma0Test_1639 : public ::testing::Test {
protected:
    // Helper: manually compute rotr for verification
    static uint64_t rotr64(uint64_t x, unsigned int n) {
        return (x >> n) | (x << (64 - n));
    }

    static uint64_t expectedSigma0(uint64_t x) {
        return rotr64(x, 28) ^ rotr64(x, 34) ^ rotr64(x, 39);
    }
};

// Test with zero input
TEST_F(Sha512Sigma0Test_1639, ZeroInput_1639) {
    uint64_t input = 0x0ULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, 0x0ULL);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with all bits set
TEST_F(Sha512Sigma0Test_1639, AllBitsSet_1639) {
    uint64_t input = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t result = sha512Sigma0(input);
    // XOR of three rotations of all-ones is still all-ones XOR all-ones XOR all-ones = all-ones
    EXPECT_EQ(result, 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with single bit set at position 0
TEST_F(Sha512Sigma0Test_1639, SingleBitLSB_1639) {
    uint64_t input = 0x1ULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with single bit set at position 63 (MSB)
TEST_F(Sha512Sigma0Test_1639, SingleBitMSB_1639) {
    uint64_t input = 0x8000000000000000ULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with known SHA-512 initial hash value H0
TEST_F(Sha512Sigma0Test_1639, SHA512InitialH0_1639) {
    uint64_t input = 0x6a09e667f3bcc908ULL; // SHA-512 H0
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with alternating bit pattern 0xAAAA...
TEST_F(Sha512Sigma0Test_1639, AlternatingBitsA_1639) {
    uint64_t input = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with alternating bit pattern 0x5555...
TEST_F(Sha512Sigma0Test_1639, AlternatingBits5_1639) {
    uint64_t input = 0x5555555555555555ULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with a power of two
TEST_F(Sha512Sigma0Test_1639, PowerOfTwo_1639) {
    uint64_t input = 0x0000000100000000ULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with a small value
TEST_F(Sha512Sigma0Test_1639, SmallValue_1639) {
    uint64_t input = 0x00000000000000FFULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with a large arbitrary value
TEST_F(Sha512Sigma0Test_1639, LargeArbitraryValue_1639) {
    uint64_t input = 0xDEADBEEFCAFEBABEULL;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test determinism - same input yields same output
TEST_F(Sha512Sigma0Test_1639, Deterministic_1639) {
    uint64_t input = 0x123456789ABCDEF0ULL;
    uint64_t result1 = sha512Sigma0(input);
    uint64_t result2 = sha512Sigma0(input);
    EXPECT_EQ(result1, result2);
}

// Test with value 1 shifted to bit 28 (relevant to first rotation)
TEST_F(Sha512Sigma0Test_1639, BitAtRotation28_1639) {
    uint64_t input = 1ULL << 28;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with value 1 shifted to bit 34 (relevant to second rotation)
TEST_F(Sha512Sigma0Test_1639, BitAtRotation34_1639) {
    uint64_t input = 1ULL << 34;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}

// Test with value 1 shifted to bit 39 (relevant to third rotation)
TEST_F(Sha512Sigma0Test_1639, BitAtRotation39_1639) {
    uint64_t input = 1ULL << 39;
    uint64_t result = sha512Sigma0(input);
    EXPECT_EQ(result, expectedSigma0(input));
}
