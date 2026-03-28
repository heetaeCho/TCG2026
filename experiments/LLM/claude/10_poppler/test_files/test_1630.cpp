#include <gtest/gtest.h>
#include <cstdint>

// Since sha256Sigma0 is a static inline function in a .cc file,
// we need to include the implementation or replicate the helper it depends on.
// We include the .cc file to access the static function.
// First, we need rotr which sha256Sigma0 depends on.

// Include the source file to get access to the static inline functions
// This is necessary because static functions are file-scoped.
#include "poppler/Decrypt.cc"

class Sha256Sigma0Test_1630 : public ::testing::Test {
protected:
    unsigned int computeSigma0(unsigned int x) {
        return sha256Sigma0(x);
    }
};

// Test with zero input
TEST_F(Sha256Sigma0Test_1630, ZeroInput_1630) {
    // rotr(0, 2) ^ rotr(0, 13) ^ rotr(0, 22) = 0 ^ 0 ^ 0 = 0
    EXPECT_EQ(computeSigma0(0x00000000u), 0x00000000u);
}

// Test with all bits set
TEST_F(Sha256Sigma0Test_1630, AllBitsSet_1630) {
    // rotr(0xFFFFFFFF, n) = 0xFFFFFFFF for any n
    // 0xFFFFFFFF ^ 0xFFFFFFFF ^ 0xFFFFFFFF = 0xFFFFFFFF
    EXPECT_EQ(computeSigma0(0xFFFFFFFFu), 0xFFFFFFFFu);
}

// Test with input value 1
TEST_F(Sha256Sigma0Test_1630, InputOne_1630) {
    // rotr(1, 2) = 0x40000000
    // rotr(1, 13) = 0x00080000
    // rotr(1, 22) = 0x00000400
    // XOR: 0x40000000 ^ 0x00080000 ^ 0x00000400 = 0x40080400
    EXPECT_EQ(computeSigma0(0x00000001u), 0x40080400u);
}

// Test with a known SHA-256 value
// Using the first round constant-related value: 0x6a09e667
TEST_F(Sha256Sigma0Test_1630, KnownSHA256Value_1630) {
    unsigned int x = 0x6a09e667u;
    // rotr(x, 2) = (x >> 2) | (x << 30)
    unsigned int r2 = (x >> 2) | (x << 30);
    // rotr(x, 13) = (x >> 13) | (x << 19)
    unsigned int r13 = (x >> 13) | (x << 19);
    // rotr(x, 22) = (x >> 22) | (x << 10)
    unsigned int r22 = (x >> 22) | (x << 10);
    unsigned int expected = r2 ^ r13 ^ r22;
    EXPECT_EQ(computeSigma0(x), expected);
}

// Test with power of two input
TEST_F(Sha256Sigma0Test_1630, PowerOfTwo_1630) {
    unsigned int x = 0x80000000u;
    // rotr(0x80000000, 2) = 0x20000000
    // rotr(0x80000000, 13) = 0x00040000
    // rotr(0x80000000, 22) = 0x00000200
    unsigned int expected = 0x20000000u ^ 0x00040000u ^ 0x00000200u;
    EXPECT_EQ(computeSigma0(x), expected);
}

// Test with alternating bits pattern 0xAAAAAAAA
TEST_F(Sha256Sigma0Test_1630, AlternatingBitsA_1630) {
    unsigned int x = 0xAAAAAAAAu;
    unsigned int r2 = (x >> 2) | (x << 30);
    unsigned int r13 = (x >> 13) | (x << 19);
    unsigned int r22 = (x >> 22) | (x << 10);
    unsigned int expected = r2 ^ r13 ^ r22;
    EXPECT_EQ(computeSigma0(x), expected);
}

// Test with alternating bits pattern 0x55555555
TEST_F(Sha256Sigma0Test_1630, AlternatingBits5_1630) {
    unsigned int x = 0x55555555u;
    unsigned int r2 = (x >> 2) | (x << 30);
    unsigned int r13 = (x >> 13) | (x << 19);
    unsigned int r22 = (x >> 22) | (x << 10);
    unsigned int expected = r2 ^ r13 ^ r22;
    EXPECT_EQ(computeSigma0(x), expected);
}

// Test with single high bit
TEST_F(Sha256Sigma0Test_1630, SingleBitPosition16_1630) {
    unsigned int x = 0x00010000u;
    unsigned int r2 = (x >> 2) | (x << 30);
    unsigned int r13 = (x >> 13) | (x << 19);
    unsigned int r22 = (x >> 22) | (x << 10);
    unsigned int expected = r2 ^ r13 ^ r22;
    EXPECT_EQ(computeSigma0(x), expected);
}

// Test with value 0xDEADBEEF
TEST_F(Sha256Sigma0Test_1630, DeadBeef_1630) {
    unsigned int x = 0xDEADBEEFu;
    unsigned int r2 = (x >> 2) | (x << 30);
    unsigned int r13 = (x >> 13) | (x << 19);
    unsigned int r22 = (x >> 22) | (x << 10);
    unsigned int expected = r2 ^ r13 ^ r22;
    EXPECT_EQ(computeSigma0(x), expected);
}

// Test with small value
TEST_F(Sha256Sigma0Test_1630, SmallValue_1630) {
    unsigned int x = 0x00000002u;
    // rotr(2, 2) = 0x80000000
    // rotr(2, 13) = 0x00100000
    // rotr(2, 22) = 0x00000800
    unsigned int expected = 0x80000000u ^ 0x00100000u ^ 0x00000800u;
    EXPECT_EQ(computeSigma0(x), expected);
}
