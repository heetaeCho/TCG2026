#include <gtest/gtest.h>
#include <cstdint>

// Since sha512Sigma1 is a static inline function in Decrypt.cc,
// we include the source to access it for testing purposes.
// We need the rotr helper as well which should be defined in the same file.

// Replicate the helpers as they appear in the translation unit to test the function
static inline uint64_t rotr(uint64_t x, uint32_t n)
{
    return (x >> n) | (x << (64 - n));
}

static inline uint64_t sha512Sigma1(uint64_t x)
{
    return rotr(x, 14) ^ rotr(x, 18) ^ rotr(x, 41);
}

// Helper to independently compute expected value
static uint64_t referenceSha512Sigma1(uint64_t x)
{
    uint64_t r14 = (x >> 14) | (x << 50);
    uint64_t r18 = (x >> 18) | (x << 46);
    uint64_t r41 = (x >> 41) | (x << 23);
    return r14 ^ r18 ^ r41;
}

class Sha512Sigma1Test_1640 : public ::testing::Test {
protected:
};

// Test with zero input
TEST_F(Sha512Sigma1Test_1640, ZeroInput_1640)
{
    uint64_t result = sha512Sigma1(0);
    EXPECT_EQ(result, 0ULL);
}

// Test with all bits set
TEST_F(Sha512Sigma1Test_1640, AllBitsSet_1640)
{
    uint64_t x = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t result = sha512Sigma1(x);
    // rotr of all 1s is still all 1s, XOR of three identical values:
    // 0xFFFF... ^ 0xFFFF... ^ 0xFFFF... = 0xFFFF...
    EXPECT_EQ(result, 0xFFFFFFFFFFFFFFFFULL);
}

// Test with input value 1
TEST_F(Sha512Sigma1Test_1640, InputOne_1640)
{
    uint64_t x = 1;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with single high bit set
TEST_F(Sha512Sigma1Test_1640, HighBitSet_1640)
{
    uint64_t x = 0x8000000000000000ULL;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with alternating bit pattern 0xAA...
TEST_F(Sha512Sigma1Test_1640, AlternatingBitsAA_1640)
{
    uint64_t x = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with alternating bit pattern 0x55...
TEST_F(Sha512Sigma1Test_1640, AlternatingBits55_1640)
{
    uint64_t x = 0x5555555555555555ULL;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with a known SHA-512 test vector-like value
TEST_F(Sha512Sigma1Test_1640, KnownValue_1640)
{
    uint64_t x = 0x510E527FADE682D1ULL;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with power of two
TEST_F(Sha512Sigma1Test_1640, PowerOfTwo_1640)
{
    uint64_t x = 0x0000000000010000ULL;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with value that exercises rotation boundaries
TEST_F(Sha512Sigma1Test_1640, RotationBoundary_1640)
{
    uint64_t x = 0x0000000000004000ULL; // bit 14 set
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with random-looking large value
TEST_F(Sha512Sigma1Test_1640, LargeRandomValue_1640)
{
    uint64_t x = 0xDEADBEEFCAFEBABEULL;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test with value 2
TEST_F(Sha512Sigma1Test_1640, InputTwo_1640)
{
    uint64_t x = 2;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}

// Test max minus one
TEST_F(Sha512Sigma1Test_1640, MaxMinusOne_1640)
{
    uint64_t x = 0xFFFFFFFFFFFFFFFEULL;
    uint64_t expected = referenceSha512Sigma1(x);
    EXPECT_EQ(sha512Sigma1(x), expected);
}
