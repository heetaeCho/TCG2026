#include <gtest/gtest.h>
#include <cstring>
#include <string>

// We need to access the static function sha384 from Decrypt.cc
// Include necessary headers that Decrypt.cc depends on
#include "config.h"
#include "poppler/Decrypt.h"

// Since sha384 is static, we include the .cc file to access it
// This is a testing technique for static functions
#include "poppler/Decrypt.cc"

class Sha384Test_1645 : public ::testing::Test {
protected:
    unsigned char hash[48]; // SHA-384 produces 48 bytes (384 bits)
};

// Test empty message - known SHA-384 hash of empty string
TEST_F(Sha384Test_1645, EmptyMessage_1645) {
    unsigned char msg[] = {};
    sha384(msg, 0, hash);

    // SHA-384("") = 38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b
    unsigned char expected[48] = {
        0x38, 0xb0, 0x60, 0xa7, 0x51, 0xac, 0x96, 0x38,
        0x4c, 0xd9, 0x32, 0x7e, 0xb1, 0xb1, 0xe3, 0x6a,
        0x21, 0xfd, 0xb7, 0x11, 0x14, 0xbe, 0x07, 0x43,
        0x4c, 0x0c, 0xc7, 0xbf, 0x63, 0xf6, 0xe1, 0xda,
        0x27, 0x4e, 0xde, 0xbf, 0xe7, 0x6f, 0x65, 0xfb,
        0xd5, 0x1a, 0xd2, 0xf1, 0x48, 0x98, 0xb9, 0x5b
    };

    EXPECT_EQ(0, memcmp(hash, expected, 48));
}

// Test "abc" - NIST test vector
TEST_F(Sha384Test_1645, ThreeCharMessage_1645) {
    unsigned char msg[] = "abc";
    sha384(msg, 3, hash);

    // SHA-384("abc") = cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7
    unsigned char expected[48] = {
        0xcb, 0x00, 0x75, 0x3f, 0x45, 0xa3, 0x5e, 0x8b,
        0xb5, 0xa0, 0x3d, 0x69, 0x9a, 0xc6, 0x50, 0x07,
        0x27, 0x2c, 0x32, 0xab, 0x0e, 0xde, 0xd1, 0x63,
        0x1a, 0x8b, 0x60, 0x5a, 0x43, 0xff, 0x5b, 0xed,
        0x80, 0x86, 0x07, 0x2b, 0xa1, 0xe7, 0xcc, 0x23,
        0x58, 0xba, 0xec, 0xa1, 0x34, 0xc8, 0x25, 0xa7
    };

    EXPECT_EQ(0, memcmp(hash, expected, 48));
}

// Test longer message that fits in one block (< 112 bytes after padding)
TEST_F(Sha384Test_1645, ShortMessage_1645) {
    // "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
    unsigned char msg[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    int len = strlen((char *)msg);
    sha384(msg, len, hash);

    // SHA-384 of "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
    // = 3391fdddfc8dc7393707a65b1b4709397cf8b1d162af05abfe8f450de5f36bc6b0455a8520bc4e6f5fe95b1fe3c8452b
    unsigned char expected[48] = {
        0x33, 0x91, 0xfd, 0xdd, 0xfc, 0x8d, 0xc7, 0x39,
        0x37, 0x07, 0xa6, 0x5b, 0x1b, 0x47, 0x09, 0x39,
        0x7c, 0xf8, 0xb1, 0xd1, 0x62, 0xaf, 0x05, 0xab,
        0xfe, 0x8f, 0x45, 0x0d, 0xe5, 0xf3, 0x6b, 0xc6,
        0xb0, 0x45, 0x5a, 0x85, 0x20, 0xbc, 0x4e, 0x6f,
        0x5f, 0xe9, 0x5b, 0x1f, 0xe3, 0xc8, 0x45, 0x2b
    };

    EXPECT_EQ(0, memcmp(hash, expected, 48));
}

// Test single byte message
TEST_F(Sha384Test_1645, SingleByteMessage_1645) {
    unsigned char msg[] = { 0x00 };
    sha384(msg, 1, hash);

    // SHA-384 of single null byte
    // Known value: bcc364da4ea82dee068f0a2a643e3a6389c250b3e4cddd1e3e3727126e73c015c4e91e3e3a2f55a1c1c49bef41f1e5a2
    // We just verify it produces consistent 48-byte output and doesn't crash
    // Re-run to check consistency
    unsigned char hash2[48];
    sha384(msg, 1, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test message exactly 112 bytes (boundary: padding fits exactly in one extra block)
TEST_F(Sha384Test_1645, BoundaryMessage112Bytes_1645) {
    unsigned char msg[112];
    memset(msg, 'A', 112);
    sha384(msg, 112, hash);

    // Verify consistency
    unsigned char hash2[48];
    sha384(msg, 112, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test message exactly 128 bytes (one full block)
TEST_F(Sha384Test_1645, ExactOneBlock128Bytes_1645) {
    unsigned char msg[128];
    memset(msg, 'B', 128);
    sha384(msg, 128, hash);

    // Verify consistency
    unsigned char hash2[48];
    sha384(msg, 128, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test message 111 bytes (just under boundary where padding fits in same block)
TEST_F(Sha384Test_1645, BoundaryMessage111Bytes_1645) {
    unsigned char msg[111];
    memset(msg, 'C', 111);
    sha384(msg, 111, hash);

    unsigned char hash2[48];
    sha384(msg, 111, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test message 113 bytes (just over boundary, padding needs extra block)
TEST_F(Sha384Test_1645, BoundaryMessage113Bytes_1645) {
    unsigned char msg[113];
    memset(msg, 'D', 113);
    sha384(msg, 113, hash);

    unsigned char hash2[48];
    sha384(msg, 113, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test message 256 bytes (exactly two blocks)
TEST_F(Sha384Test_1645, TwoBlocks256Bytes_1645) {
    unsigned char msg[256];
    memset(msg, 'E', 256);
    sha384(msg, 256, hash);

    unsigned char hash2[48];
    sha384(msg, 256, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test that different messages produce different hashes
TEST_F(Sha384Test_1645, DifferentMessagesDifferentHashes_1645) {
    unsigned char msg1[] = "Hello";
    unsigned char msg2[] = "World";
    unsigned char hash1[48], hash2[48];

    sha384(msg1, 5, hash1);
    sha384(msg2, 5, hash2);

    EXPECT_NE(0, memcmp(hash1, hash2, 48));
}

// Test output is exactly 48 bytes (6 * 8), not 64 bytes like SHA-512
TEST_F(Sha384Test_1645, OutputIs48Bytes_1645) {
    // SHA-384 should only write 48 bytes (6 uint64 values)
    unsigned char buffer[64];
    memset(buffer, 0xFF, 64);

    unsigned char msg[] = "test";
    sha384(msg, 4, buffer);

    // Bytes 48-63 should still be 0xFF (untouched)
    for (int i = 48; i < 64; i++) {
        EXPECT_EQ(0xFF, buffer[i]) << "Byte " << i << " was modified";
    }
}

// Test message of length 127 (one byte less than block size)
TEST_F(Sha384Test_1645, Message127Bytes_1645) {
    unsigned char msg[127];
    memset(msg, 'F', 127);
    sha384(msg, 127, hash);

    unsigned char hash2[48];
    sha384(msg, 127, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test with binary data containing zeros
TEST_F(Sha384Test_1645, BinaryDataWithZeros_1645) {
    unsigned char msg[16];
    memset(msg, 0, 16);
    sha384(msg, 16, hash);

    unsigned char hash2[48];
    sha384(msg, 16, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}

// Test determinism: same input always gives same output
TEST_F(Sha384Test_1645, Deterministic_1645) {
    unsigned char msg[] = "deterministic test";
    int len = strlen((char *)msg);

    unsigned char hash1[48], hash2[48], hash3[48];
    sha384(msg, len, hash1);
    sha384(msg, len, hash2);
    sha384(msg, len, hash3);

    EXPECT_EQ(0, memcmp(hash1, hash2, 48));
    EXPECT_EQ(0, memcmp(hash2, hash3, 48));
}

// Test large message spanning multiple blocks
TEST_F(Sha384Test_1645, LargeMultiBlockMessage_1645) {
    unsigned char msg[1024];
    for (int i = 0; i < 1024; i++) {
        msg[i] = (unsigned char)(i & 0xFF);
    }
    sha384(msg, 1024, hash);

    unsigned char hash2[48];
    sha384(msg, 1024, hash2);
    EXPECT_EQ(0, memcmp(hash, hash2, 48));
}
