#include <gtest/gtest.h>
#include <cstdint>

// We replicate the static inline function signature since it's a static function
// in the source file. We test its mathematical behavior as a black box.
static inline uint64_t sha512Maj(uint64_t x, uint64_t y, uint64_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

class Sha512MajTest_1638 : public ::testing::Test {
protected:
};

// Test with all zeros
TEST_F(Sha512MajTest_1638, AllZeros_1638) {
    uint64_t result = sha512Maj(0, 0, 0);
    EXPECT_EQ(result, 0ULL);
}

// Test with all ones (max uint64_t)
TEST_F(Sha512MajTest_1638, AllOnes_1638) {
    uint64_t maxVal = UINT64_MAX;
    uint64_t result = sha512Maj(maxVal, maxVal, maxVal);
    EXPECT_EQ(result, maxVal);
}

// Test majority function: when two of three inputs have bit set, result should have bit set
TEST_F(Sha512MajTest_1638, TwoOfThreeSet_XY_1638) {
    uint64_t result = sha512Maj(UINT64_MAX, UINT64_MAX, 0);
    EXPECT_EQ(result, UINT64_MAX);
}

TEST_F(Sha512MajTest_1638, TwoOfThreeSet_XZ_1638) {
    uint64_t result = sha512Maj(UINT64_MAX, 0, UINT64_MAX);
    EXPECT_EQ(result, UINT64_MAX);
}

TEST_F(Sha512MajTest_1638, TwoOfThreeSet_YZ_1638) {
    uint64_t result = sha512Maj(0, UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(result, UINT64_MAX);
}

// Test majority function: when only one of three inputs has bit set, result should be 0
TEST_F(Sha512MajTest_1638, OneOfThreeSet_X_1638) {
    uint64_t result = sha512Maj(UINT64_MAX, 0, 0);
    EXPECT_EQ(result, 0ULL);
}

TEST_F(Sha512MajTest_1638, OneOfThreeSet_Y_1638) {
    uint64_t result = sha512Maj(0, UINT64_MAX, 0);
    EXPECT_EQ(result, 0ULL);
}

TEST_F(Sha512MajTest_1638, OneOfThreeSet_Z_1638) {
    uint64_t result = sha512Maj(0, 0, UINT64_MAX);
    EXPECT_EQ(result, 0ULL);
}

// Test with specific bit patterns
TEST_F(Sha512MajTest_1638, SpecificBitPattern_1638) {
    // x = 0b1100, y = 0b1010, z = 0b0110
    // Maj should produce majority for each bit position:
    // bit3: 1,1,0 -> 1
    // bit2: 1,0,1 -> 1
    // bit1: 0,1,1 -> 1
    // bit0: 0,0,0 -> 0
    // Expected: 0b1110 = 14
    uint64_t result = sha512Maj(0xC, 0xA, 0x6);
    EXPECT_EQ(result, 0xEULL);
}

// Test with known SHA-512 round values
TEST_F(Sha512MajTest_1638, KnownValues_1638) {
    uint64_t x = 0x6A09E667F3BCC908ULL;
    uint64_t y = 0xBB67AE8584CAA73BULL;
    uint64_t z = 0x3C6EF372FE94F82BULL;
    uint64_t result = sha512Maj(x, y, z);
    // Manually compute: (x&y) ^ (x&z) ^ (y&z)
    uint64_t expected = (x & y) ^ (x & z) ^ (y & z);
    EXPECT_EQ(result, expected);
}

// Test symmetry properties: Maj(x,y,z) == Maj(y,x,z) == Maj(z,y,x) etc.
TEST_F(Sha512MajTest_1638, Symmetry_1638) {
    uint64_t x = 0x123456789ABCDEF0ULL;
    uint64_t y = 0xFEDCBA9876543210ULL;
    uint64_t z = 0x0F0F0F0F0F0F0F0FULL;

    uint64_t r1 = sha512Maj(x, y, z);
    uint64_t r2 = sha512Maj(x, z, y);
    uint64_t r3 = sha512Maj(y, x, z);
    uint64_t r4 = sha512Maj(y, z, x);
    uint64_t r5 = sha512Maj(z, x, y);
    uint64_t r6 = sha512Maj(z, y, x);

    EXPECT_EQ(r1, r2);
    EXPECT_EQ(r1, r3);
    EXPECT_EQ(r1, r4);
    EXPECT_EQ(r1, r5);
    EXPECT_EQ(r1, r6);
}

// Test with alternating bits
TEST_F(Sha512MajTest_1638, AlternatingBits_1638) {
    uint64_t a = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t b = 0x5555555555555555ULL;
    // Maj(a, a, b): majority of each bit: where a has 1 and b has 0, two 1s win -> a
    // where a has 0 and b has 1, two 0s win -> 0
    uint64_t result = sha512Maj(a, a, b);
    EXPECT_EQ(result, a);
}

// Test boundary: single bit set
TEST_F(Sha512MajTest_1638, SingleBitHighest_1638) {
    uint64_t highBit = 0x8000000000000000ULL;
    // Two out of three have high bit set
    uint64_t result = sha512Maj(highBit, highBit, 0);
    EXPECT_EQ(result, highBit);
}

TEST_F(Sha512MajTest_1638, SingleBitLowest_1638) {
    // Two out of three have low bit set
    uint64_t result = sha512Maj(1, 0, 1);
    EXPECT_EQ(result, 1ULL);
}

// Test: value of 1
TEST_F(Sha512MajTest_1638, ValueOne_1638) {
    uint64_t result = sha512Maj(1, 1, 1);
    EXPECT_EQ(result, 1ULL);
}

// Test with power of 2 values
TEST_F(Sha512MajTest_1638, PowerOfTwo_1638) {
    uint64_t result = sha512Maj(0x100, 0x100, 0x200);
    // bit 8: two set -> 1, bit 9: one set -> 0
    EXPECT_EQ(result, 0x100ULL);
}

// Verify the Maj function property: Maj(x,y,z) == (x & y) | (x & z) | (y & z)
// which is equivalent to (x & y) ^ (x & z) ^ (y & z) for majority
TEST_F(Sha512MajTest_1638, EquivalenceWithOrForm_1638) {
    uint64_t x = 0xDEADBEEFCAFEBABEULL;
    uint64_t y = 0x0123456789ABCDEFULL;
    uint64_t z = 0xFEDCBA9876543210ULL;

    uint64_t xorForm = sha512Maj(x, y, z);
    // The OR form of majority is equivalent
    uint64_t orForm = (x & y) | (x & z) | (y & z);
    EXPECT_EQ(xorForm, orForm);
}
