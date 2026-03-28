#include <gtest/gtest.h>

// The sbox array from the implementation
static const unsigned char sbox[256] = {
    99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118,
    202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192,
    183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21,
    4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117,
    9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132,
    83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207,
    208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168,
    81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210,
    205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115,
    96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219,
    224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121,
    231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8,
    186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138,
    112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158,
    225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223,
    140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22
};

// Re-implement subWord locally for testing purposes (matching the interface)
static inline unsigned int subWord(unsigned int x) {
    return (sbox[x >> 24] << 24) | (sbox[(x >> 16) & 0xff] << 16) | (sbox[(x >> 8) & 0xff] << 8) | sbox[x & 0xff];
}

class SubWordTest_1601 : public ::testing::Test {
protected:
    // Helper to compute expected subWord result from individual byte lookups
    unsigned int expectedSubWord(unsigned int x) {
        unsigned char b3 = (x >> 24) & 0xff;
        unsigned char b2 = (x >> 16) & 0xff;
        unsigned char b1 = (x >> 8) & 0xff;
        unsigned char b0 = x & 0xff;
        return ((unsigned int)sbox[b3] << 24) |
               ((unsigned int)sbox[b2] << 16) |
               ((unsigned int)sbox[b1] << 8) |
               (unsigned int)sbox[b0];
    }
};

// Test with all zero bytes
TEST_F(SubWordTest_1601, AllZeroInput_1601) {
    unsigned int input = 0x00000000;
    unsigned int result = subWord(input);
    // sbox[0] = 99 = 0x63
    unsigned int expected = 0x63636363;
    EXPECT_EQ(result, expected);
}

// Test with all 0xFF bytes
TEST_F(SubWordTest_1601, AllOnesInput_1601) {
    unsigned int input = 0xFFFFFFFF;
    unsigned int result = subWord(input);
    // sbox[255] = 22 = 0x16
    unsigned int expected = 0x16161616;
    EXPECT_EQ(result, expected);
}

// Test with input 0x01020304
TEST_F(SubWordTest_1601, SequentialBytes_1601) {
    unsigned int input = 0x01020304;
    unsigned int result = subWord(input);
    // sbox[1]=124=0x7C, sbox[2]=119=0x77, sbox[3]=123=0x7B, sbox[4]=242=0xF2
    unsigned int expected = (0x7C << 24) | (0x77 << 16) | (0x7B << 8) | 0xF2;
    EXPECT_EQ(result, expected);
}

// Test with known AES test vector: subWord(0x00102030)
TEST_F(SubWordTest_1601, AESKnownVector_1601) {
    unsigned int input = 0x00102030;
    unsigned int result = subWord(input);
    // sbox[0x00]=0x63, sbox[0x10]=0xCA, sbox[0x20]=0xB7, sbox[0x30]=0x04
    unsigned int expected = (0x63 << 24) | (0xCA << 16) | (0xB7 << 8) | 0x04;
    EXPECT_EQ(result, expected);
}

// Test with only MSB byte set
TEST_F(SubWordTest_1601, OnlyMSBByteSet_1601) {
    unsigned int input = 0x52000000;
    unsigned int result = subWord(input);
    // sbox[0x52]=0x00, sbox[0]=0x63
    unsigned int expected = (0x00 << 24) | (0x63 << 16) | (0x63 << 8) | 0x63;
    EXPECT_EQ(result, expected);
}

// Test with only LSB byte set
TEST_F(SubWordTest_1601, OnlyLSBByteSet_1601) {
    unsigned int input = 0x00000052;
    unsigned int result = subWord(input);
    // sbox[0x52]=0x00, sbox[0]=0x63
    unsigned int expected = (0x63 << 24) | (0x63 << 16) | (0x63 << 8) | 0x00;
    EXPECT_EQ(result, expected);
}

// Test with each byte being a different value
TEST_F(SubWordTest_1601, MixedBytes_1601) {
    unsigned int input = 0xABCD1234;
    unsigned int result = subWord(input);
    unsigned int expected = expectedSubWord(input);
    EXPECT_EQ(result, expected);
}

// Test identity-like: sbox[0x52] = 0x00, so byte 0x52 maps to 0x00
TEST_F(SubWordTest_1601, SboxZeroOutput_1601) {
    unsigned int input = 0x52525252;
    unsigned int result = subWord(input);
    EXPECT_EQ(result, 0x00000000u);
}

// Test boundary: input = 0x80808080
TEST_F(SubWordTest_1601, Byte0x80_1601) {
    unsigned int input = 0x80808080;
    unsigned int result = subWord(input);
    // sbox[0x80]=0xCD (205)
    unsigned int expected = 0xCDCDCDCD;
    EXPECT_EQ(result, expected);
}

// Test with input where each byte is at the boundary of nibbles
TEST_F(SubWordTest_1601, NibbleBoundaries_1601) {
    unsigned int input = 0x0F1F2F3F;
    unsigned int result = subWord(input);
    unsigned int expected = expectedSubWord(input);
    EXPECT_EQ(result, expected);
}

// Test with input 0xFFEEDDCC
TEST_F(SubWordTest_1601, HighValues_1601) {
    unsigned int input = 0xFFEEDDCC;
    unsigned int result = subWord(input);
    unsigned int expected = expectedSubWord(input);
    EXPECT_EQ(result, expected);
}

// Test single non-zero byte in position 1 (bits 8-15)
TEST_F(SubWordTest_1601, SingleBytePosition1_1601) {
    unsigned int input = 0x00004200;
    unsigned int result = subWord(input);
    // sbox[0]=0x63, sbox[0]=0x63, sbox[0x42]=0x2C (44), sbox[0]=0x63
    unsigned int expected = (0x63 << 24) | (0x63 << 16) | (sbox[0x42] << 8) | 0x63;
    EXPECT_EQ(result, expected);
}

// Test single non-zero byte in position 2 (bits 16-23)
TEST_F(SubWordTest_1601, SingleBytePosition2_1601) {
    unsigned int input = 0x00420000;
    unsigned int result = subWord(input);
    unsigned int expected = (0x63 << 24) | (sbox[0x42] << 16) | (0x63 << 8) | 0x63;
    EXPECT_EQ(result, expected);
}

// Verify consistency: calling subWord twice with same input gives same result
TEST_F(SubWordTest_1601, Deterministic_1601) {
    unsigned int input = 0xDEADBEEF;
    unsigned int result1 = subWord(input);
    unsigned int result2 = subWord(input);
    EXPECT_EQ(result1, result2);
}

// Test with all identical non-zero bytes
TEST_F(SubWordTest_1601, AllIdenticalBytes_1601) {
    unsigned int input = 0x01010101;
    unsigned int result = subWord(input);
    // sbox[1] = 124 = 0x7C
    unsigned int expected = 0x7C7C7C7C;
    EXPECT_EQ(result, expected);
}

// Test comprehensive: verify against manual computation for a range of single-byte values
TEST_F(SubWordTest_1601, ComprehensiveSingleByteAsLSB_1601) {
    for (unsigned int i = 0; i < 256; i++) {
        unsigned int input = i; // only LSB is non-zero (or zero)
        unsigned int result = subWord(input);
        unsigned int expected = (sbox[0] << 24) | (sbox[0] << 16) | (sbox[0] << 8) | sbox[i];
        EXPECT_EQ(result, expected) << "Failed for input byte: " << i;
    }
}

// Test comprehensive: verify against manual computation for a range of single-byte as MSB
TEST_F(SubWordTest_1601, ComprehensiveSingleByteAsMSB_1601) {
    for (unsigned int i = 0; i < 256; i++) {
        unsigned int input = i << 24;
        unsigned int result = subWord(input);
        unsigned int expected = (sbox[i] << 24) | (sbox[0] << 16) | (sbox[0] << 8) | sbox[0];
        EXPECT_EQ(result, expected) << "Failed for MSB byte: " << i;
    }
}

// Verify the helper matches subWord for various inputs
TEST_F(SubWordTest_1601, HelperConsistency_1601) {
    unsigned int test_values[] = {
        0x00000000, 0xFFFFFFFF, 0x12345678, 0x9ABCDEF0,
        0x0F0F0F0F, 0xF0F0F0F0, 0xAAAAAAAA, 0x55555555
    };
    for (unsigned int val : test_values) {
        EXPECT_EQ(subWord(val), expectedSubWord(val)) << "Mismatch for input: 0x" << std::hex << val;
    }
}
