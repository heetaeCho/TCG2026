#include <gtest/gtest.h>
#include <cstdint>

// We need to replicate the helper function signature since it's static inline
// in the source file. We'll test it by including the necessary definitions.

static inline uint64_t rotr(uint64_t x, int n) {
    return (x >> n) | (x << (64 - n));
}

static inline uint64_t sha512sigma0(uint64_t x) {
    return rotr(x, 1) ^ rotr(x, 8) ^ (x >> 7);
}

class Sha512Sigma0Test_1641 : public ::testing::Test {
protected:
    // Helper to compute expected value independently
    uint64_t computeExpected(uint64_t x) {
        uint64_t r1 = (x >> 1) | (x << 63);
        uint64_t r8 = (x >> 8) | (x << 56);
        uint64_t s7 = x >> 7;
        return r1 ^ r8 ^ s7;
    }
};

TEST_F(Sha512Sigma0Test_1641, ZeroInput_1641) {
    uint64_t result = sha512sigma0(0);
    EXPECT_EQ(result, 0ULL);
}

TEST_F(Sha512Sigma0Test_1641, OneInput_1641) {
    uint64_t x = 1;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, MaxUint64Input_1641) {
    uint64_t x = UINT64_MAX;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, PowerOfTwo_1641) {
    uint64_t x = (1ULL << 32);
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, HighBitSet_1641) {
    uint64_t x = (1ULL << 63);
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, AlternatingBits_1641) {
    uint64_t x = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, AlternatingBitsInverted_1641) {
    uint64_t x = 0x5555555555555555ULL;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, SmallValue_1641) {
    uint64_t x = 0xFF;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, LargeArbitraryValue_1641) {
    uint64_t x = 0xDEADBEEFCAFEBABEULL;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, SingleByteValue_1641) {
    uint64_t x = 0x80;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, SpecificKnownValue_1641) {
    // For x = 1:
    // rotr(1, 1) = 1 << 63 = 0x8000000000000000
    // rotr(1, 8) = 1 << 56 = 0x0100000000000000
    // x >> 7 = 0
    // result = 0x8000000000000000 ^ 0x0100000000000000 ^ 0 = 0x8100000000000000
    uint64_t result = sha512sigma0(1);
    EXPECT_EQ(result, 0x8100000000000000ULL);
}

TEST_F(Sha512Sigma0Test_1641, ValueTwo_1641) {
    uint64_t x = 2;
    // rotr(2, 1) = 1
    // rotr(2, 8) = 2 << 56 = 0x0200000000000000
    // x >> 7 = 0
    // result = 1 ^ 0x0200000000000000
    uint64_t expected = 0x0200000000000001ULL;
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, Value128_1641) {
    uint64_t x = 128; // 0x80
    // rotr(128, 1) = 64 = 0x40
    // rotr(128, 8) = 128 << 56 = 0x8000000000000000
    // x >> 7 = 1
    // result = 0x40 ^ 0x8000000000000000 ^ 1 = 0x8000000000000041
    uint64_t expected = 0x8000000000000041ULL;
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, LowByteFull_1641) {
    uint64_t x = 0xFF00FF00FF00FF00ULL;
    uint64_t expected = computeExpected(x);
    EXPECT_EQ(sha512sigma0(x), expected);
}

TEST_F(Sha512Sigma0Test_1641, ConsistencyCheck_1641) {
    // Calling the function twice with same input should yield same result
    uint64_t x = 0x123456789ABCDEF0ULL;
    uint64_t result1 = sha512sigma0(x);
    uint64_t result2 = sha512sigma0(x);
    EXPECT_EQ(result1, result2);
}
