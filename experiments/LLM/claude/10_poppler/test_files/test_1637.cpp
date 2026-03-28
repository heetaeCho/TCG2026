#include <gtest/gtest.h>
#include <cstdint>

// We test the sha512Ch function as a black box based on its signature:
// static inline uint64_t sha512Ch(uint64_t x, uint64_t y, uint64_t z)
// The function computes: (x & y) ^ (~x & z)
// Since it's a static inline function in a .cc file, we replicate its signature
// here for testing purposes. We treat the formula as the interface contract.

// Replicating the function signature as it appears in the interface
static inline uint64_t sha512Ch(uint64_t x, uint64_t y, uint64_t z)
{
    return (x & y) ^ (~x & z);
}

class Sha512ChTest_1637 : public ::testing::Test {
protected:
};

// Test with all zeros
TEST_F(Sha512ChTest_1637, AllZeros_1637)
{
    uint64_t result = sha512Ch(0, 0, 0);
    EXPECT_EQ(result, 0ULL);
}

// Test with all ones
TEST_F(Sha512ChTest_1637, AllOnes_1637)
{
    uint64_t result = sha512Ch(UINT64_MAX, UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(result, UINT64_MAX);
}

// When x is all ones, result should be y (since ~x = 0, so (x&y)^(0&z) = y)
TEST_F(Sha512ChTest_1637, XAllOnes_ReturnsY_1637)
{
    uint64_t x = UINT64_MAX;
    uint64_t y = 0x123456789ABCDEF0ULL;
    uint64_t z = 0xFEDCBA9876543210ULL;
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, y);
}

// When x is all zeros, result should be z (since x&y = 0, ~x = all ones, so (~x&z) = z)
TEST_F(Sha512ChTest_1637, XAllZeros_ReturnsZ_1637)
{
    uint64_t x = 0;
    uint64_t y = 0x123456789ABCDEF0ULL;
    uint64_t z = 0xFEDCBA9876543210ULL;
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, z);
}

// When y equals z, result should be y (or z) regardless of x
// Because (x & y) ^ (~x & y) = (x ^ ~x) & y = all_ones & y = y
TEST_F(Sha512ChTest_1637, YEqualsZ_ReturnsY_1637)
{
    uint64_t x = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t y = 0x123456789ABCDEF0ULL;
    uint64_t z = y;
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, y);
}

// Test with alternating bit pattern for x
TEST_F(Sha512ChTest_1637, AlternatingBitsX_1637)
{
    uint64_t x = 0xAAAAAAAAAAAAAAAAULL; // 1010...
    uint64_t y = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t z = 0x0000000000000000ULL;
    // (x & y) = 0xAAAA..., (~x & z) = 0
    // result = 0xAAAA...
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, 0xAAAAAAAAAAAAAAAAULL);
}

// Test with alternating bit pattern for x, reversed y and z
TEST_F(Sha512ChTest_1637, AlternatingBitsX_ReversedYZ_1637)
{
    uint64_t x = 0xAAAAAAAAAAAAAAAAULL; // 1010...
    uint64_t y = 0x0000000000000000ULL;
    uint64_t z = 0xFFFFFFFFFFFFFFFFULL;
    // (x & y) = 0, (~x & z) = 0x5555...
    // result = 0x5555...
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, 0x5555555555555555ULL);
}

// Test with a single bit set in x
TEST_F(Sha512ChTest_1637, SingleBitX_1637)
{
    uint64_t x = 1ULL;
    uint64_t y = UINT64_MAX;
    uint64_t z = 0ULL;
    // (x & y) = 1, (~x & z) = 0
    // result = 1
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, 1ULL);
}

// Test with highest bit set in x
TEST_F(Sha512ChTest_1637, HighestBitX_1637)
{
    uint64_t x = 0x8000000000000000ULL;
    uint64_t y = UINT64_MAX;
    uint64_t z = 0ULL;
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, 0x8000000000000000ULL);
}

// General case with known values
TEST_F(Sha512ChTest_1637, GeneralCase_1637)
{
    uint64_t x = 0x0F0F0F0F0F0F0F0FULL;
    uint64_t y = 0xFF00FF00FF00FF00ULL;
    uint64_t z = 0x00FF00FF00FF00FFULL;
    // (x & y) = 0x0F000F000F000F00
    // ~x = 0xF0F0F0F0F0F0F0F0
    // (~x & z) = 0x00F000F000F000F0
    // result = 0x0F000F000F000F00 ^ 0x00F000F000F000F0 = 0x0FF00FF00FF00FF0
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, 0x0FF00FF00FF00FF0ULL);
}

// Test commutativity does NOT hold (Ch is not symmetric in y, z)
TEST_F(Sha512ChTest_1637, NotCommutativeYZ_1637)
{
    uint64_t x = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t y = 0x1234567890ABCDEFULL;
    uint64_t z = 0xFEDCBA0987654321ULL;
    uint64_t result1 = sha512Ch(x, y, z);
    uint64_t result2 = sha512Ch(x, z, y);
    // These should generally differ unless y == z
    EXPECT_NE(result1, result2);
}

// Boundary: x = 1, y = 0, z = 1 => (1&0) ^ (~1 & 1) = 0 ^ (0xFFF...E & 1) = 0
TEST_F(Sha512ChTest_1637, SmallValues_1637)
{
    uint64_t x = 1;
    uint64_t y = 0;
    uint64_t z = 1;
    // (1 & 0) = 0, ~1 = 0xFFFFFFFFFFFFFFFE, (0xFFFFFFFFFFFFFFFE & 1) = 0
    // result = 0 ^ 0 = 0
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, 0ULL);
}

// Ch function selects: for each bit position, if x_i=1 pick y_i, if x_i=0 pick z_i
TEST_F(Sha512ChTest_1637, SelectionProperty_1637)
{
    uint64_t x = 0xF0F0F0F0F0F0F0F0ULL;
    uint64_t y = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t z = 0x5555555555555555ULL;
    // Where x has 1s (upper nibbles): pick y bits = 0xA
    // Where x has 0s (lower nibbles): pick z bits = 0x5
    // result = 0xA5A5A5A5A5A5A5A5
    uint64_t result = sha512Ch(x, y, z);
    EXPECT_EQ(result, 0xA5A5A5A5A5A5A5A5ULL);
}
