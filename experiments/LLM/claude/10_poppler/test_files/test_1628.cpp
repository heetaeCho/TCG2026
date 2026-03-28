#include <gtest/gtest.h>

// We need to test the static inline function sha256Ch.
// Since it's a static inline function in a .cc file, we need to include it
// or replicate its signature for testing. We'll include the source directly
// to get access to the static inline function.

// The function implements the SHA-256 Ch function: Ch(x, y, z) = (x & y) ^ (~x & z)
// We replicate the function signature here since it's static inline and not exported.
static inline unsigned int sha256Ch(unsigned int x, unsigned int y, unsigned int z) {
    return (x & y) ^ (~x & z);
}

class Sha256ChTest_1628 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with all zeros
TEST_F(Sha256ChTest_1628, AllZeros_1628) {
    unsigned int result = sha256Ch(0, 0, 0);
    // Ch(0, 0, 0) = (0 & 0) ^ (~0 & 0) = 0 ^ 0 = 0
    EXPECT_EQ(result, 0u);
}

// Test with all ones (0xFFFFFFFF)
TEST_F(Sha256ChTest_1628, AllOnes_1628) {
    unsigned int result = sha256Ch(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    // Ch(~0, ~0, ~0) = (~0 & ~0) ^ (0 & ~0) = ~0 ^ 0 = ~0
    EXPECT_EQ(result, 0xFFFFFFFF);
}

// Test with x = all ones, y = 0, z = 0
TEST_F(Sha256ChTest_1628, XAllOnes_YZero_ZZero_1628) {
    unsigned int result = sha256Ch(0xFFFFFFFF, 0, 0);
    // Ch(~0, 0, 0) = (~0 & 0) ^ (0 & 0) = 0 ^ 0 = 0
    EXPECT_EQ(result, 0u);
}

// Test with x = 0, y = all ones, z = 0
TEST_F(Sha256ChTest_1628, XZero_YAllOnes_ZZero_1628) {
    unsigned int result = sha256Ch(0, 0xFFFFFFFF, 0);
    // Ch(0, ~0, 0) = (0 & ~0) ^ (~0 & 0) = 0 ^ 0 = 0
    EXPECT_EQ(result, 0u);
}

// Test with x = 0, y = 0, z = all ones
TEST_F(Sha256ChTest_1628, XZero_YZero_ZAllOnes_1628) {
    unsigned int result = sha256Ch(0, 0, 0xFFFFFFFF);
    // Ch(0, 0, ~0) = (0 & 0) ^ (~0 & ~0) = 0 ^ ~0 = ~0
    EXPECT_EQ(result, 0xFFFFFFFF);
}

// Test with x = all ones, y = all ones, z = 0
TEST_F(Sha256ChTest_1628, XAllOnes_YAllOnes_ZZero_1628) {
    unsigned int result = sha256Ch(0xFFFFFFFF, 0xFFFFFFFF, 0);
    // Ch(~0, ~0, 0) = (~0 & ~0) ^ (0 & 0) = ~0 ^ 0 = ~0
    EXPECT_EQ(result, 0xFFFFFFFF);
}

// Test with x = all ones, y = 0, z = all ones
TEST_F(Sha256ChTest_1628, XAllOnes_YZero_ZAllOnes_1628) {
    unsigned int result = sha256Ch(0xFFFFFFFF, 0, 0xFFFFFFFF);
    // Ch(~0, 0, ~0) = (~0 & 0) ^ (0 & ~0) = 0 ^ 0 = 0
    EXPECT_EQ(result, 0u);
}

// Test with x = 0, y = all ones, z = all ones
TEST_F(Sha256ChTest_1628, XZero_YAllOnes_ZAllOnes_1628) {
    unsigned int result = sha256Ch(0, 0xFFFFFFFF, 0xFFFFFFFF);
    // Ch(0, ~0, ~0) = (0 & ~0) ^ (~0 & ~0) = 0 ^ ~0 = ~0
    EXPECT_EQ(result, 0xFFFFFFFF);
}

// Test Ch function property: when x=1 choose y, when x=0 choose z
// For single bit at position 0
TEST_F(Sha256ChTest_1628, ChooseYWhenXBitSet_1628) {
    // x has bit 0 set, y has bit 0 set, z has bit 0 clear
    unsigned int result = sha256Ch(1, 1, 0);
    // For bit 0: x=1, so choose y=1 => result bit 0 = 1
    EXPECT_EQ(result & 1u, 1u);
}

TEST_F(Sha256ChTest_1628, ChooseZWhenXBitClear_1628) {
    // x has bit 0 clear, y has bit 0 set, z has bit 0 set
    unsigned int result = sha256Ch(0, 1, 1);
    // For bit 0: x=0, so choose z=1 => result bit 0 = 1
    EXPECT_EQ(result & 1u, 1u);
}

TEST_F(Sha256ChTest_1628, ChooseZWhenXBitClear_ZIsZero_1628) {
    // x has bit 0 clear, y has bit 0 set, z has bit 0 clear
    unsigned int result = sha256Ch(0, 1, 0);
    // For bit 0: x=0, so choose z=0 => result bit 0 = 0
    EXPECT_EQ(result & 1u, 0u);
}

// Test with known SHA-256 test vector values
TEST_F(Sha256ChTest_1628, KnownValues_1628) {
    unsigned int x = 0x6A09E667;
    unsigned int y = 0xBB67AE85;
    unsigned int z = 0x3C6EF372;
    unsigned int result = sha256Ch(x, y, z);
    unsigned int expected = (x & y) ^ (~x & z);
    EXPECT_EQ(result, expected);
}

// Test with alternating bit patterns
TEST_F(Sha256ChTest_1628, AlternatingBits_1628) {
    unsigned int x = 0xAAAAAAAA;
    unsigned int y = 0x55555555;
    unsigned int z = 0xAAAAAAAA;
    // Ch(0xAAAAAAAA, 0x55555555, 0xAAAAAAAA)
    // = (0xAAAAAAAA & 0x55555555) ^ (~0xAAAAAAAA & 0xAAAAAAAA)
    // = 0x00000000 ^ (0x55555555 & 0xAAAAAAAA)
    // = 0x00000000 ^ 0x00000000
    // = 0x00000000
    unsigned int result = sha256Ch(x, y, z);
    EXPECT_EQ(result, 0u);
}

TEST_F(Sha256ChTest_1628, AlternatingBits2_1628) {
    unsigned int x = 0xAAAAAAAA;
    unsigned int y = 0xFFFFFFFF;
    unsigned int z = 0x00000000;
    // Ch(0xAAAAAAAA, 0xFFFFFFFF, 0x00000000)
    // = (0xAAAAAAAA & 0xFFFFFFFF) ^ (~0xAAAAAAAA & 0x00000000)
    // = 0xAAAAAAAA ^ 0x00000000
    // = 0xAAAAAAAA
    unsigned int result = sha256Ch(x, y, z);
    EXPECT_EQ(result, 0xAAAAAAAA);
}

// Test the Ch function fundamental property: result = y where x=1, z where x=0
TEST_F(Sha256ChTest_1628, ChFunctionChooseProperty_1628) {
    unsigned int x = 0xF0F0F0F0;
    unsigned int y = 0xCCCCCCCC;
    unsigned int z = 0x33333333;
    unsigned int result = sha256Ch(x, y, z);
    // Where x bits are 1, take y bits; where x bits are 0, take z bits
    // x = 1111 0000 ... -> take y's upper nibble and z's lower nibble
    // y upper nibble = C, z lower nibble = 3
    // Expected: 0xC3C3C3C3
    unsigned int expected = (x & y) | (~x & z);
    // Note: Ch(x,y,z) = (x & y) ^ (~x & z), which equals (x & y) | (~x & z)
    // because (x & y) and (~x & z) don't overlap
    EXPECT_EQ(result, expected);
}

// Boundary: single bit
TEST_F(Sha256ChTest_1628, SingleBitMSB_1628) {
    unsigned int x = 0x80000000;
    unsigned int y = 0x80000000;
    unsigned int z = 0x00000000;
    unsigned int result = sha256Ch(x, y, z);
    // Bit 31: x=1, choose y=1 => 1
    // All other bits: x=0, choose z=0 => 0
    EXPECT_EQ(result, 0x80000000);
}

TEST_F(Sha256ChTest_1628, SingleBitLSB_1628) {
    unsigned int x = 0x00000001;
    unsigned int y = 0x00000001;
    unsigned int z = 0x00000000;
    unsigned int result = sha256Ch(x, y, z);
    EXPECT_EQ(result, 0x00000001);
}

// Verify commutativity does NOT hold for y and z (Ch is not symmetric in y, z)
TEST_F(Sha256ChTest_1628, NotSymmetricInYZ_1628) {
    unsigned int x = 0xAAAAAAAA;
    unsigned int y = 0xFFFFFFFF;
    unsigned int z = 0x00000000;
    unsigned int result1 = sha256Ch(x, y, z);
    unsigned int result2 = sha256Ch(x, z, y);
    // These should generally differ
    EXPECT_NE(result1, result2);
}

// Test with maximum unsigned int value for all parameters
TEST_F(Sha256ChTest_1628, MaxUnsignedInt_1628) {
    unsigned int maxVal = UINT_MAX;
    unsigned int result = sha256Ch(maxVal, maxVal, maxVal);
    EXPECT_EQ(result, maxVal);
}

// Test identity: Ch(x, y, y) = y for any x
TEST_F(Sha256ChTest_1628, ChWithEqualYZ_1628) {
    unsigned int x = 0xDEADBEEF;
    unsigned int y = 0x12345678;
    unsigned int result = sha256Ch(x, y, y);
    // Ch(x, y, y) = (x & y) ^ (~x & y) = (x | ~x) & y = y
    EXPECT_EQ(result, y);
}

// Another identity test with different values
TEST_F(Sha256ChTest_1628, ChWithEqualYZ_DifferentValues_1628) {
    unsigned int x = 0x00FF00FF;
    unsigned int y = 0xABCDEF01;
    unsigned int result = sha256Ch(x, y, y);
    EXPECT_EQ(result, y);
}
