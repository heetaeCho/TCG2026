// File: Decrypt_sha512Sigma0_test_1639.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <vector>

// NOTE:
// sha512Sigma0 is a "static inline" function inside Decrypt.cc. To test it via its
// actual compiled definition (black-box from the public build artifacts), we include
// the .cc directly into this test translation unit.
#include "Decrypt.cc"

namespace {

// Independent rotate-right for expected-value computation in tests (not using Poppler internals).
constexpr uint64_t RotR64(uint64_t x, unsigned int n)
{
    n &= 63U;
    return (n == 0) ? x : ((x >> n) | (x << (64U - n)));
}

constexpr uint64_t ExpectedSha512Sigma0(uint64_t x)
{
    return RotR64(x, 28) ^ RotR64(x, 34) ^ RotR64(x, 39);
}

class Sha512Sigma0Test_1639 : public ::testing::Test
{
};

} // namespace

TEST_F(Sha512Sigma0Test_1639, ReturnsZeroForZeroInput_1639)
{
    const uint64_t x = 0ULL;
    EXPECT_EQ(sha512Sigma0(x), 0ULL);
}

TEST_F(Sha512Sigma0Test_1639, ReturnsZeroForAllOnesInput_1639)
{
    const uint64_t x = std::numeric_limits<uint64_t>::max(); // all ones
    // rotr(all-ones) == all-ones, so XOR of three identical values => 0
    EXPECT_EQ(sha512Sigma0(x), 0ULL);
}

TEST_F(Sha512Sigma0Test_1639, MatchesExpectedForSingleBitPositions_BoundaryAndTypical_1639)
{
    // Boundary-ish bit positions: LSB and MSB, plus a mid bit.
    const std::vector<unsigned> bitPositions = {0U, 1U, 32U, 63U};

    for (unsigned b : bitPositions) {
        const uint64_t x = (b == 63U) ? (1ULL << 63) : (1ULL << b);
        EXPECT_EQ(sha512Sigma0(x), ExpectedSha512Sigma0(x)) << "bit=" << b;
    }
}

TEST_F(Sha512Sigma0Test_1639, MatchesExpectedForPatternValues_1639)
{
    const std::vector<uint64_t> cases = {
        0x0123456789ABCDEFULL,
        0xFEDCBA9876543210ULL,
        0x0F0F0F0F0F0F0F0FULL,
        0xF0F0F0F0F0F0F0F0ULL,
        0x8000000000000000ULL, // MSB set
        0x0000000000000001ULL, // LSB set
    };

    for (uint64_t x : cases) {
        EXPECT_EQ(sha512Sigma0(x), ExpectedSha512Sigma0(x)) << "x=0x" << std::hex << x;
    }
}

TEST_F(Sha512Sigma0Test_1639, MatchesExpectedForVariousFixedValues_1639)
{
    // A small set of deterministic "random-looking" constants to broaden coverage.
    const std::vector<uint64_t> cases = {
        0x243F6A8885A308D3ULL,
        0x13198A2E03707344ULL,
        0xA4093822299F31D0ULL,
        0x082EFA98EC4E6C89ULL,
        0x452821E638D01377ULL,
        0xBE5466CF34E90C6CULL,
    };

    for (uint64_t x : cases) {
        EXPECT_EQ(sha512Sigma0(x), ExpectedSha512Sigma0(x)) << "x=0x" << std::hex << x;
    }
}