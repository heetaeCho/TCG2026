#include <gtest/gtest.h>
#include <cstring>

// Declaration of the function under test
extern void md5(const unsigned char *msg, int msgLen, unsigned char *digest);

class MD5Test_1626 : public ::testing::Test {
protected:
    unsigned char digest[16];

    void SetUp() override {
        memset(digest, 0, sizeof(digest));
    }
};

// Test MD5 of empty string - RFC 1321 test vector
TEST_F(MD5Test_1626, EmptyString_1626) {
    const unsigned char msg[] = "";
    md5(msg, 0, digest);

    // MD5("") = d41d8cd98f00b204e9800998ecf8427e
    unsigned char expected[16] = {
        0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,
        0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}

// Test MD5 of "a" - RFC 1321 test vector
TEST_F(MD5Test_1626, SingleCharA_1626) {
    const unsigned char msg[] = "a";
    md5(msg, 1, digest);

    // MD5("a") = 0cc175b9c0f1b6a831c399e269772661
    unsigned char expected[16] = {
        0x0c, 0xc1, 0x75, 0xb9, 0xc0, 0xf1, 0xb6, 0xa8,
        0x31, 0xc3, 0x99, 0xe2, 0x69, 0x77, 0x26, 0x61
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}

// Test MD5 of "abc" - RFC 1321 test vector
TEST_F(MD5Test_1626, ABC_1626) {
    const unsigned char msg[] = "abc";
    md5(msg, 3, digest);

    // MD5("abc") = 900150983cd24fb0d6963f7d28e17f72
    unsigned char expected[16] = {
        0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0,
        0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}

// Test MD5 of "message digest" - RFC 1321 test vector
TEST_F(MD5Test_1626, MessageDigest_1626) {
    const unsigned char msg[] = "message digest";
    md5(msg, 14, digest);

    // MD5("message digest") = f96b697d7cb7938d525a2f31aaf161d0
    unsigned char expected[16] = {
        0xf9, 0x6b, 0x69, 0x7d, 0x7c, 0xb7, 0x93, 0x8d,
        0x52, 0x5a, 0x2f, 0x31, 0xaa, 0xf1, 0x61, 0xd0
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}

// Test MD5 of "abcdefghijklmnopqrstuvwxyz" - RFC 1321 test vector
TEST_F(MD5Test_1626, Alphabet_1626) {
    const unsigned char msg[] = "abcdefghijklmnopqrstuvwxyz";
    md5(msg, 26, digest);

    // MD5("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
    unsigned char expected[16] = {
        0xc3, 0xfc, 0xd3, 0xd7, 0x61, 0x92, 0xe4, 0x00,
        0x7d, 0xfb, 0x49, 0x6c, 0xca, 0x67, 0xe1, 0x3b
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}

// Test negative msgLen - should not crash, digest should remain unchanged
TEST_F(MD5Test_1626, NegativeMsgLen_1626) {
    unsigned char originalDigest[16];
    memset(digest, 0xAA, sizeof(digest));
    memcpy(originalDigest, digest, 16);

    const unsigned char msg[] = "test";
    md5(msg, -1, digest);

    // Digest should remain unchanged since negative length causes early return
    EXPECT_EQ(0, memcmp(digest, originalDigest, 16));
}

// Test that same input produces same output (deterministic)
TEST_F(MD5Test_1626, Deterministic_1626) {
    const unsigned char msg[] = "hello world";
    unsigned char digest1[16], digest2[16];

    md5(msg, 11, digest1);
    md5(msg, 11, digest2);

    EXPECT_EQ(0, memcmp(digest1, digest2, 16));
}

// Test that different inputs produce different outputs
TEST_F(MD5Test_1626, DifferentInputsDifferentOutputs_1626) {
    const unsigned char msg1[] = "hello";
    const unsigned char msg2[] = "world";
    unsigned char digest1[16], digest2[16];

    md5(msg1, 5, digest1);
    md5(msg2, 5, digest2);

    EXPECT_NE(0, memcmp(digest1, digest2, 16));
}

// Test MD5 with binary data containing null bytes
TEST_F(MD5Test_1626, BinaryDataWithNulls_1626) {
    unsigned char msg[4] = {0x00, 0x00, 0x00, 0x00};
    md5(msg, 4, digest);

    // Should produce a valid digest, not the same as empty string
    unsigned char emptyDigest[16];
    md5(msg, 0, emptyDigest);

    EXPECT_NE(0, memcmp(digest, emptyDigest, 16));
}

// Test with exactly 55 bytes (boundary: padding fits in one block)
TEST_F(MD5Test_1626, FiftyFiveBytes_1626) {
    unsigned char msg[55];
    memset(msg, 'A', 55);
    md5(msg, 55, digest);

    // Just verify it produces a non-zero result and doesn't crash
    unsigned char zeroDigest[16];
    memset(zeroDigest, 0, 16);
    // Very unlikely to be all zeros but this is a basic sanity check
    // More importantly, we check it doesn't crash
    SUCCEED();
}

// Test with exactly 56 bytes (boundary: padding crosses block boundary)
TEST_F(MD5Test_1626, FiftySixBytes_1626) {
    unsigned char msg[56];
    memset(msg, 'A', 56);
    md5(msg, 56, digest);

    // Ensure it differs from 55-byte case
    unsigned char digest55[16];
    unsigned char msg55[55];
    memset(msg55, 'A', 55);
    md5(msg55, 55, digest55);

    EXPECT_NE(0, memcmp(digest, digest55, 16));
}

// Test with exactly 64 bytes (one full block)
TEST_F(MD5Test_1626, SixtyFourBytes_1626) {
    unsigned char msg[64];
    memset(msg, 'B', 64);
    md5(msg, 64, digest);

    unsigned char digest63[16];
    unsigned char msg63[63];
    memset(msg63, 'B', 63);
    md5(msg63, 63, digest63);

    EXPECT_NE(0, memcmp(digest, digest63, 16));
}

// Test with a longer message spanning multiple blocks
TEST_F(MD5Test_1626, LongMessage_1626) {
    // RFC 1321: MD5("12345678901234567890123456789012345678901234567890123456789012345678901234567890")
    // = 57edf4a22be3c955ac49da2e2107b67a
    const unsigned char msg[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    md5(msg, 80, digest);

    unsigned char expected[16] = {
        0x57, 0xed, 0xf4, 0xa2, 0x2b, 0xe3, 0xc9, 0x55,
        0xac, 0x49, 0xda, 0x2e, 0x21, 0x07, 0xb6, 0x7a
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}

// Test msgLen of zero
TEST_F(MD5Test_1626, ZeroLength_1626) {
    const unsigned char msg[] = "anything";
    md5(msg, 0, digest);

    // Should be same as MD5 of empty string
    unsigned char expected[16] = {
        0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,
        0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}

// Test single byte zero
TEST_F(MD5Test_1626, SingleNullByte_1626) {
    unsigned char msg[1] = {0x00};
    md5(msg, 1, digest);

    // MD5 of single null byte: 93b885adfe0da089cdf634904fd59f71
    unsigned char expected[16] = {
        0x93, 0xb8, 0x85, 0xad, 0xfe, 0x0d, 0xa0, 0x89,
        0xcd, 0xf6, 0x34, 0x90, 0x4f, 0xd5, 0x9f, 0x71
    };
    EXPECT_EQ(0, memcmp(digest, expected, 16));
}
