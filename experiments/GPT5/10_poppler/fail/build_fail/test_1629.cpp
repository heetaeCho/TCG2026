// Decrypt_sha256Maj_test_1629.cc
// Unit tests for sha256Maj() in Decrypt.cc
//
// Notes / constraints compliance:
// - Treat sha256Maj as a black box: only verify observable return values for chosen inputs.
// - No reliance on any internal state.
// - No mocks needed (pure function).
//
// Build assumption: this test TU can include the .cc to access the internal static inline.
// If your build already compiles Decrypt.cc separately and forbids including .cc files,
// you can instead expose the function via a small test-only wrapper in the build system.

#include <gtest/gtest.h>
#include <cstdint>

namespace {
// Include the implementation to make the internal static inline visible in this TU.
#include "./TestProjects/poppler/poppler/Decrypt.cc"
} // namespace

class Sha256MajTest_1629 : public ::testing::Test {};

TEST_F(Sha256MajTest_1629, MajorityTruthTable_AllZeros_1629)
{
    EXPECT_EQ(0u, sha256Maj(0u, 0u, 0u));
}

TEST_F(Sha256MajTest_1629, MajorityTruthTable_AllOnes_1629)
{
    EXPECT_EQ(0xFFFFFFFFu, sha256Maj(0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu));
}

TEST_F(Sha256MajTest_1629, MajorityTruthTable_TwoOnesOneZero_1629)
{
    // Majority(1,1,0) = 1, check using 1-bit values.
    EXPECT_EQ(1u, sha256Maj(1u, 1u, 0u));
}

TEST_F(Sha256MajTest_1629, MajorityTruthTable_TwoZerosOneOne_1629)
{
    // Majority(0,0,1) = 0, check using 1-bit values.
    EXPECT_EQ(0u, sha256Maj(0u, 0u, 1u));
}

TEST_F(Sha256MajTest_1629, Boundary_OneBitPatterns_1629)
{
    // Per-bit majority: for each bit position, output bit is 1 if at least two inputs have 1.
    // Choose patterns where majority is predictable:
    // x=0b1010, y=0b1100, z=0b1001
    // bit3: (1,1,1)->1
    // bit2: (0,1,0)->0
    // bit1: (1,0,0)->0
    // bit0: (0,0,1)->0
    // expected=0b1000 (8)
    EXPECT_EQ(8u, sha256Maj(0b1010u, 0b1100u, 0b1001u));
}

TEST_F(Sha256MajTest_1629, NormalOperation_TwoInputsEqual_ReturnsThatInput_1629)
{
    // If y == z, then majority(x,y,z) must be y (per-bit, two votes from y/z).
    const unsigned int x = 0x12345678u;
    const unsigned int y = 0xA5A5A5A5u;
    EXPECT_EQ(y, sha256Maj(x, y, y));
}

TEST_F(Sha256MajTest_1629, NormalOperation_AllInputsPairwiseDifferent_KnownExpected_1629)
{
    const unsigned int x = 0x0F0F0F0Fu;
    const unsigned int y = 0x00FF00FFu;
    const unsigned int z = 0x33333333u;

    // Compute expected from the *definition* of majority per-bit without relying on any private state.
    // Here we assert a concrete expected constant to keep the test purely black-box at runtime.
    // expected = (x&y) ^ (x&z) ^ (y&z)
    const unsigned int expected = (x & y) ^ (x & z) ^ (y & z);

    EXPECT_EQ(expected, sha256Maj(x, y, z));
}

TEST_F(Sha256MajTest_1629, Boundary_AlternatingBits_1629)
{
    const unsigned int x = 0xAAAAAAAAu; // 1010...
    const unsigned int y = 0x55555555u; // 0101...
    const unsigned int z = 0xFFFFFFFFu; // all ones

    // With z all ones, output bit is 1 iff either x or y has 1 in that bit (since z provides one vote).
    // For alternating x/y, (x|y) == all ones => expected all ones.
    EXPECT_EQ(0xFFFFFFFFu, sha256Maj(x, y, z));
}

TEST_F(Sha256MajTest_1629, Boundary_ZeroAndOnesMix_1629)
{
    const unsigned int x = 0u;
    const unsigned int y = 0xFFFFFFFFu;
    const unsigned int z = 0xFFFFFFFFu;

    // Two all-ones inputs dominate => all ones.
    EXPECT_EQ(0xFFFFFFFFu, sha256Maj(x, y, z));
}

TEST_F(Sha256MajTest_1629, ExceptionalInputs_None_FunctionIsTotalForUnsigned_1629)
{
    // "Exceptional" here means values at unsigned extremes; function should still return a value.
    const unsigned int x = 0u;
    const unsigned int y = 1u;
    const unsigned int z = 0xFFFFFFFFu;

    const unsigned int out = sha256Maj(x, y, z);
    // Sanity: result must be within unsigned range; additionally check against expected formula.
    const unsigned int expected = (x & y) ^ (x & z) ^ (y & z);
    EXPECT_EQ(expected, out);
}