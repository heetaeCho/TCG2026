#include <gtest/gtest.h>
#include <cstdint>

// We need access to the static inline function.
// Since it's static in the .cc file, we include it to get access.
// The rotr function must also be available; it's likely defined in the same file.

// Helper: replicate the rotr and sha256Sigma1 as reference to define expected values
// But we test the actual function from the source.

// To access the static function, we include the cc file
// First, handle any includes that Decrypt.cc might need
#include "config.h"
#include "poppler/Decrypt.h"

// Include the implementation to access the static inline function
#include "poppler/Decrypt.cc"

class Sha256Sigma1Test_1631 : public ::testing::Test {
protected:
    // Reference implementation of rotr for 32-bit
    static unsigned int ref_rotr(unsigned int x, unsigned int n) {
        return (x >> n) | (x << (32 - n));
    }

    // Reference implementation of sha256Sigma1
    static unsigned int ref_sha256Sigma1(unsigned int x) {
        return ref_rotr(x, 6) ^ ref_rotr(x, 11) ^ ref_rotr(x, 25);
    }
};

TEST_F(Sha256Sigma1Test_1631, ZeroInput_1631) {
    // Sigma1(0) should be 0 since all rotations of 0 are 0
    unsigned int result = sha256Sigma1(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(Sha256Sigma1Test_1631, AllOnesInput_1631) {
    // Sigma1(0xFFFFFFFF) - all bits set, rotations still all ones, XOR of three all-ones = all ones
    // 0xFFFFFFFF ^ 0xFFFFFFFF ^ 0xFFFFFFFF = 0xFFFFFFFF
    unsigned int result = sha256Sigma1(0xFFFFFFFF);
    EXPECT_EQ(result, 0xFFFFFFFF);
}

TEST_F(Sha256Sigma1Test_1631, SingleBitSet_1631) {
    // Test with x = 1
    unsigned int result = sha256Sigma1(1);
    unsigned int expected = ref_sha256Sigma1(1);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, HighBitSet_1631) {
    // Test with x = 0x80000000
    unsigned int result = sha256Sigma1(0x80000000);
    unsigned int expected = ref_sha256Sigma1(0x80000000);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, KnownValue_0x510e527f_1631) {
    // SHA-256 initial hash value H4
    unsigned int x = 0x510e527f;
    unsigned int result = sha256Sigma1(x);
    unsigned int expected = ref_sha256Sigma1(x);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, ArbitraryValue1_1631) {
    unsigned int x = 0xDEADBEEF;
    unsigned int result = sha256Sigma1(x);
    unsigned int expected = ref_sha256Sigma1(x);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, ArbitraryValue2_1631) {
    unsigned int x = 0x12345678;
    unsigned int result = sha256Sigma1(x);
    unsigned int expected = ref_sha256Sigma1(x);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, PowerOfTwo_1631) {
    unsigned int x = 0x00010000;
    unsigned int result = sha256Sigma1(x);
    unsigned int expected = ref_sha256Sigma1(x);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, AlternatingBits_1631) {
    // 0xAAAAAAAA = 10101010...
    unsigned int x = 0xAAAAAAAA;
    unsigned int result = sha256Sigma1(x);
    unsigned int expected = ref_sha256Sigma1(x);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, AlternatingBitsInverse_1631) {
    // 0x55555555 = 01010101...
    unsigned int x = 0x55555555;
    unsigned int result = sha256Sigma1(x);
    unsigned int expected = ref_sha256Sigma1(x);
    EXPECT_EQ(result, expected);
}

TEST_F(Sha256Sigma1Test_1631, SmallValues_1631) {
    for (unsigned int x = 0; x < 256; x++) {
        unsigned int result = sha256Sigma1(x);
        unsigned int expected = ref_sha256Sigma1(x);
        EXPECT_EQ(result, expected) << "Failed for x = " << x;
    }
}

TEST_F(Sha256Sigma1Test_1631, ValueOne_1631) {
    // rotr(1,6)=0x04000000, rotr(1,11)=0x00200000, rotr(1,25)=0x00000040
    // Expected: 0x04000000 ^ 0x00200000 ^ 0x00000040 = 0x04200040
    unsigned int result = sha256Sigma1(1);
    EXPECT_EQ(result, 0x04200040u);
}
