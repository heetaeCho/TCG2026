// Decrypt_sha512Ch_test_1637.cc
#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

// NOTE:
// sha512Ch() is defined as a static inline function in Decrypt.cc.
// To test it via its real implementation (without re-implementing it),
// we include the implementation unit here so the symbol is available
// in this translation unit.
#include "./TestProjects/poppler/poppler/Decrypt.cc"

namespace {

class Sha512ChTest_1637 : public ::testing::Test {};

// Helper to build an "alternating bits" constant without assuming a compiler literal width.
constexpr uint64_t kAltA = 0xAAAAAAAAAAAAAAAAULL;
constexpr uint64_t kAlt5 = 0x5555555555555555ULL;

} // namespace

TEST_F(Sha512ChTest_1637, XAllZerosReturnsZ_1637)
{
    const uint64_t x = 0ULL;
    const uint64_t y = 0x0123456789ABCDEFULL;
    const uint64_t z = 0xFEDCBA9876543210ULL;

    EXPECT_EQ(sha512Ch(x, y, z), z);
}

TEST_F(Sha512ChTest_1637, XAllOnesReturnsY_1637)
{
    const uint64_t x = std::numeric_limits<uint64_t>::max();
    const uint64_t y = 0x0123456789ABCDEFULL;
    const uint64_t z = 0xFEDCBA9876543210ULL;

    EXPECT_EQ(sha512Ch(x, y, z), y);
}

TEST_F(Sha512ChTest_1637, YEqualsZReturnsThatValue_1637)
{
    const uint64_t x = 0x0F0F0F0F0F0F0F0FULL;
    const uint64_t y = 0x1122334455667788ULL;
    const uint64_t z = y;

    EXPECT_EQ(sha512Ch(x, y, z), y);
}

TEST_F(Sha512ChTest_1637, SingleBitInXSelectsYAtThatBitAndZElsewhere_1637)
{
    const uint64_t bit = 1ULL << 13;
    const uint64_t x = bit;

    // y has 0 at all bits; z has 1 at all bits.
    // Only the selected bit (bit 13) should come from y (i.e., become 0).
    const uint64_t y = 0ULL;
    const uint64_t z = std::numeric_limits<uint64_t>::max();

    const uint64_t expected = z & ~bit;

    EXPECT_EQ(sha512Ch(x, y, z), expected);
}

TEST_F(Sha512ChTest_1637, ComplementYAndZMakesResultFollowX_1637)
{
    // When y=all-ones and z=all-zeros, the output should be 1 where x is 1 and 0 where x is 0.
    const uint64_t x = 0x123456789ABCDEF0ULL;
    const uint64_t y = std::numeric_limits<uint64_t>::max();
    const uint64_t z = 0ULL;

    EXPECT_EQ(sha512Ch(x, y, z), x);
}

TEST_F(Sha512ChTest_1637, AlternatingPatternsBoundaryLikeValues_1637)
{
    const uint64_t x = kAltA;
    const uint64_t y = kAlt5;
    const uint64_t z = std::numeric_limits<uint64_t>::max();

    // Independent selection-form expected value: start from z, and for bits where x=1,
    // replace with y by toggling differences between z and y.
    const uint64_t expected = z ^ ((z ^ y) & x);

    EXPECT_EQ(sha512Ch(x, y, z), expected);
}