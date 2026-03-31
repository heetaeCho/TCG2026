#include <gtest/gtest.h>
#include <cstring>

// Include the .cc file to access the static inline function and its dependencies
#include "poppler/Decrypt.cc"

class InvMixColumnsWTest_1611 : public ::testing::Test {
protected:
    void SetUp() override {}
};

// Test that all-zero input produces all-zero output
TEST_F(InvMixColumnsWTest_1611, AllZerosRemainZero_1611) {
    unsigned int w[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0x00000000u);
    EXPECT_EQ(w[1], 0x00000000u);
    EXPECT_EQ(w[2], 0x00000000u);
    EXPECT_EQ(w[3], 0x00000000u);
}

// Test known AES inverse MixColumns vector
// The AES MixColumns operation on a column [0xdb, 0x13, 0x53, 0x45] gives [0x8e, 0x4d, 0xa1, 0xbc]
// So inverse MixColumns on [0x8e, 0x4d, 0xa1, 0xbc] should give [0xdb, 0x13, 0x53, 0x45]
TEST_F(InvMixColumnsWTest_1611, KnownAESVector_1611) {
    // invMixColumnsW operates on w[0..3] where each w[c] holds a column
    // Column bytes are packed as: s0=MSB(byte0), s1, s2, s3=LSB
    // After MixColumns: [db,13,53,45] -> [8e,4d,a1,bc]
    // So InvMixColumns: [8e,4d,a1,bc] -> [db,13,53,45]
    unsigned int w[4] = {0x8e4da1bc, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0xdb135345u);
}

// Another known AES test vector
// MixColumns: [d4,bf,5d,30] -> [04,66,81,e5]
// InvMixColumns: [04,66,81,e5] -> [d4,bf,5d,30]
TEST_F(InvMixColumnsWTest_1611, KnownAESVector2_1611) {
    unsigned int w[4] = {0x046681e5, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0xd4bf5d30u);
}

// Test that each column in the array is processed independently
TEST_F(InvMixColumnsWTest_1611, AllFourColumnsProcessed_1611) {
    unsigned int w[4] = {0x8e4da1bc, 0x046681e5, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0xdb135345u);
    EXPECT_EQ(w[1], 0xd4bf5d30u);
    EXPECT_EQ(w[2], 0x00000000u);
    EXPECT_EQ(w[3], 0x00000000u);
}

// Test with all 0xFF bytes
TEST_F(InvMixColumnsWTest_1611, AllOnesInput_1611) {
    // InvMixColumns on [ff,ff,ff,ff]: each byte goes through
    // 0e^ff XOR 0b^ff XOR 0d^ff XOR 09^ff
    // Since GF multiplication is linear and ff XOR ff XOR ff XOR ff in the matrix...
    // For identical bytes x: result = (0e XOR 09 XOR 0d XOR 0b) * x = (0e^09^0d^0b)*x
    // 0e XOR 09 = 07, 07 XOR 0d = 0a, 0a XOR 0b = 01
    // So result is 01 * ff = ff for each byte
    unsigned int w[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0xFFFFFFFFu);
    EXPECT_EQ(w[1], 0xFFFFFFFFu);
    EXPECT_EQ(w[2], 0xFFFFFFFFu);
    EXPECT_EQ(w[3], 0xFFFFFFFFu);
}

// Test identity-like: column with single byte set
TEST_F(InvMixColumnsWTest_1611, SingleByteTopSet_1611) {
    // Input column [0x01, 0x00, 0x00, 0x00]
    // Result should be [0e*01, 09*01, 0d*01, 0b*01] = [0e, 09, 0d, 0b]
    unsigned int w[4] = {0x01000000, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0x0e090d0bu);
}

// Test with single byte in second position
TEST_F(InvMixColumnsWTest_1611, SingleByteSecondSet_1611) {
    // Input column [0x00, 0x01, 0x00, 0x00]
    // Result: [0b*01, 0e*01, 09*01, 0d*01] = [0b, 0e, 09, 0d]
    unsigned int w[4] = {0x00010000, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0x0b0e090du);
}

// Test with single byte in third position
TEST_F(InvMixColumnsWTest_1611, SingleByteThirdSet_1611) {
    // Input column [0x00, 0x00, 0x01, 0x00]
    // Result: [0d*01, 0b*01, 0e*01, 09*01] = [0d, 0b, 0e, 09]
    unsigned int w[4] = {0x00000100, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0x0d0b0e09u);
}

// Test with single byte in fourth position
TEST_F(InvMixColumnsWTest_1611, SingleByteFourthSet_1611) {
    // Input column [0x00, 0x00, 0x00, 0x01]
    // Result: [09*01, 0d*01, 0b*01, 0e*01] = [09, 0d, 0b, 0e]
    unsigned int w[4] = {0x00000001, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0x090d0b0eu);
}

// Known test vector: MixColumns [e5,09,98,6a] -> [d4,e0,b8,1e]
// So InvMixColumns [d4,e0,b8,1e] -> [e5,09,98,6a]
TEST_F(InvMixColumnsWTest_1611, KnownAESVector3_1611) {
    unsigned int w[4] = {0xd4e0b81e, 0x00000000, 0x00000000, 0x00000000};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0xe509986au);
}

// Test that applying invMixColumns twice is NOT identity (it's not an involution)
TEST_F(InvMixColumnsWTest_1611, DoubleApplicationNotIdentity_1611) {
    unsigned int original[4] = {0x12345678, 0x9abcdef0, 0x11223344, 0x55667788};
    unsigned int w[4];
    std::memcpy(w, original, sizeof(w));
    invMixColumnsW(w);
    invMixColumnsW(w);
    // After two applications, we should generally NOT get back the original
    bool allSame = (w[0] == original[0]) && (w[1] == original[1]) &&
                   (w[2] == original[2]) && (w[3] == original[3]);
    // This is a sanity check - double invMixColumns is not identity
    // (unless the input happens to be a fixed point, which is extremely unlikely for arbitrary input)
    EXPECT_FALSE(allSame);
}

// Test uniform byte columns: [x,x,x,x] should map to [x,x,x,x]
// because (0e XOR 0b XOR 0d XOR 09) = 01, so each output byte = 01*x = x
TEST_F(InvMixColumnsWTest_1611, UniformByteColumn_1611) {
    unsigned int w[4] = {0xABABABAB, 0x37373737, 0xCDCDCDCD, 0x01010101};
    invMixColumnsW(w);
    EXPECT_EQ(w[0], 0xABABABABu);
    EXPECT_EQ(w[1], 0x37373737u);
    EXPECT_EQ(w[2], 0xCDCDCDCDu);
    EXPECT_EQ(w[3], 0x01010101u);
}
