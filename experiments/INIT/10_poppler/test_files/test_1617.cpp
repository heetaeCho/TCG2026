// Decrypt_rotateLeft_ut_1617.cpp
#include <gtest/gtest.h>

#include <bit>
#include <cstdint>
#include <limits>

// Include the implementation file to access the internal-linkage helper.
// This keeps the test black-box with respect to other code while still
// exercising the real function implementation.
#include "Decrypt.cc"

namespace {

class RotateLeftTest_1617 : public ::testing::Test {};

static uint32_t Rotl32Ref(uint64_t x, int r)
{
    // Reference behavior: rotate within 32-bit lane.
    // std::rotl is well-defined for unsigned integer types.
    const uint32_t v = static_cast<uint32_t>(x & 0xffffffffu);
    const unsigned int rr = static_cast<unsigned int>(r) & 31u;
    return std::rotl(v, static_cast<int>(rr));
}

} // namespace

TEST_F(RotateLeftTest_1617, RotateByZeroPreservesLow32Bits_1617)
{
    const unsigned long x = 0xDEADBEEFul;
    const unsigned long out = rotateLeft(x, 0);

    EXPECT_EQ(out, static_cast<unsigned long>(Rotl32Ref(x, 0)));
}

TEST_F(RotateLeftTest_1617, RotateByOneMatchesReference_1617)
{
    const unsigned long x = 0x80000001ul; // exercises carry from MSB to LSB
    const unsigned long out = rotateLeft(x, 1);

    EXPECT_EQ(out, static_cast<unsigned long>(Rotl32Ref(x, 1)));
}

TEST_F(RotateLeftTest_1617, RotateBy31MatchesReference_1617)
{
    const unsigned long x = 0x12345678ul;
    const unsigned long out = rotateLeft(x, 31);

    EXPECT_EQ(out, static_cast<unsigned long>(Rotl32Ref(x, 31)));
}

TEST_F(RotateLeftTest_1617, OutputIsConstrainedTo32Bits_1617)
{
    const unsigned long x = 0xFFFFFFFFul;
    const unsigned long out = rotateLeft(x, 13);

    // Must never set bits above 32.
    EXPECT_EQ(out & ~0xfffffffful, 0ul);
    EXPECT_EQ(out, static_cast<unsigned long>(Rotl32Ref(x, 13)));
}

TEST_F(RotateLeftTest_1617, HighBitsInInputAreIgnored_1617)
{
    // Construct a value with bits above 32 set (on platforms where unsigned long is > 32 bits).
    // Regardless of platform, the reference masks to 32 bits.
    const uint64_t wide = 0x1'0000'0000ull | 0x89ABCDEFu; // high bit beyond 32 + low pattern
    const unsigned long x = static_cast<unsigned long>(wide);

    const unsigned long out = rotateLeft(x, 7);

    EXPECT_EQ(out, static_cast<unsigned long>(Rotl32Ref(wide, 7)));
    EXPECT_EQ(out & ~0xfffffffful, 0ul);
}

TEST_F(RotateLeftTest_1617, MultipleRotationsAreConsistent_1617)
{
    const unsigned long x = 0x0F0F0F0Ful;

    const unsigned long r4_then_5 = rotateLeft(rotateLeft(x, 4), 5);
    const unsigned long r9 = rotateLeft(x, 9);

    EXPECT_EQ(r4_then_5, r9);
    EXPECT_EQ(r9, static_cast<unsigned long>(Rotl32Ref(x, 9)));
}