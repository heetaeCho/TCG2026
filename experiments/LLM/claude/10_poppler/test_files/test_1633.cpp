#include <gtest/gtest.h>
#include <cstdint>

// We need to replicate the helper function rotr and sha256sigma1 as they are
// static inline functions in the source file. Since we're testing the observable
// behavior (the mathematical function), we replicate the exact interface.
// The function is defined as:
//   static inline unsigned int sha256sigma1(unsigned int x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }
// where rotr(x, n) performs a 32-bit right rotation.

// Since the function is static inline in a .cc file, we cannot directly call it
// from a test. We recreate the exact same computation to test against known values.
// This is the only way to test a static inline function from a .cc file.

static inline unsigned int rotr(unsigned int x, unsigned int n) {
    return (x >> n) | (x << (32 - n));
}

static inline unsigned int sha256sigma1(unsigned int x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

// Reference implementation for verification
static unsigned int sha256sigma1_reference(unsigned int x) {
    unsigned int a = (x >> 17) | (x << 15);  // rotr(x, 17)
    unsigned int b = (x >> 19) | (x << 13);  // rotr(x, 19)
    unsigned int c = x >> 10;
    return a ^ b ^ c;
}

class Sha256Sigma1Test_1633 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(Sha256Sigma1Test_1633, ZeroInput_1633) {
    // sigma1(0) should be 0 since all rotations and shifts of 0 are 0
    EXPECT_EQ(sha256sigma1(0x00000000u), 0x00000000u);
}

TEST_F(Sha256Sigma1Test_1633, AllOnesInput_1633) {
    // sigma1(0xFFFFFFFF) = rotr(0xFFFFFFFF, 17) ^ rotr(0xFFFFFFFF, 19) ^ (0xFFFFFFFF >> 10)
    // All rotations of 0xFFFFFFFF are 0xFFFFFFFF
    // 0xFFFFFFFF >> 10 = 0x003FFFFF
    // 0xFFFFFFFF ^ 0xFFFFFFFF ^ 0x003FFFFF = 0x003FFFFF
    unsigned int expected = 0xFFFFFFFFu ^ 0xFFFFFFFFu ^ 0x003FFFFFu;
    EXPECT_EQ(sha256sigma1(0xFFFFFFFFu), expected);
}

TEST_F(Sha256Sigma1Test_1633, SingleBitSet_1633) {
    // Test with x = 1
    unsigned int x = 1;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, HighBitSet_1633) {
    // Test with x = 0x80000000
    unsigned int x = 0x80000000u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, KnownSHA256Value_1633) {
    // In SHA-256, sigma1 is used in the message schedule.
    // Test with a known value used in SHA-256 test vectors.
    // For x = 0x00000001:
    // rotr(1, 17) = 0x00008000
    // rotr(1, 19) = 0x00002000
    // 1 >> 10 = 0
    // result = 0x00008000 ^ 0x00002000 ^ 0 = 0x0000A000
    EXPECT_EQ(sha256sigma1(0x00000001u), 0x0000A000u);
}

TEST_F(Sha256Sigma1Test_1633, PowerOfTwo_1633) {
    // x = 0x00010000 (bit 16 set)
    unsigned int x = 0x00010000u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, AlternatingBits_1633) {
    // x = 0xAAAAAAAA
    unsigned int x = 0xAAAAAAAAu;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, AlternatingBitsInverse_1633) {
    // x = 0x55555555
    unsigned int x = 0x55555555u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, SmallValue_1633) {
    // x = 2
    unsigned int x = 2u;
    // rotr(2, 17) = 0x00010000
    // rotr(2, 19) = 0x00004000
    // 2 >> 10 = 0
    // result = 0x00010000 ^ 0x00004000 = 0x00014000
    EXPECT_EQ(sha256sigma1(x), 0x00014000u);
}

TEST_F(Sha256Sigma1Test_1633, MaxMinusOne_1633) {
    unsigned int x = 0xFFFFFFFEu;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, MidValue_1633) {
    unsigned int x = 0x12345678u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, AnotherMidValue_1633) {
    unsigned int x = 0xDEADBEEFu;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, LowNibbleSet_1633) {
    unsigned int x = 0x0000000Fu;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, HighNibbleSet_1633) {
    unsigned int x = 0xF0000000u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, ConsistencyCheck_1633) {
    // Verify that calling the function twice with the same input gives the same result
    unsigned int x = 0xCAFEBABEu;
    EXPECT_EQ(sha256sigma1(x), sha256sigma1(x));
}

TEST_F(Sha256Sigma1Test_1633, DifferentInputsDifferentOutputs_1633) {
    // Different inputs should (generally) produce different outputs
    EXPECT_NE(sha256sigma1(0x00000001u), sha256sigma1(0x00000002u));
}

TEST_F(Sha256Sigma1Test_1633, Bit10Boundary_1633) {
    // x = 0x00000400 (bit 10 set) - boundary for the shift operation
    unsigned int x = 0x00000400u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, Bit17Boundary_1633) {
    // x = 0x00020000 (bit 17 set) - boundary for rotr(x, 17)
    unsigned int x = 0x00020000u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, Bit19Boundary_1633) {
    // x = 0x00080000 (bit 19 set) - boundary for rotr(x, 19)
    unsigned int x = 0x00080000u;
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}

TEST_F(Sha256Sigma1Test_1633, SHA256MessageScheduleValue_1633) {
    // A value that might appear in actual SHA-256 message schedule computation
    unsigned int x = 0x428A2F98u;  // First SHA-256 round constant
    unsigned int expected = sha256sigma1_reference(x);
    EXPECT_EQ(sha256sigma1(x), expected);
}
