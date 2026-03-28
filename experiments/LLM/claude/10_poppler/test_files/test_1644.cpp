#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <vector>

// Include the implementation file to access the static function
// We need to provide/include dependencies first
#include "poppler/Decrypt.cc"

// Helper to convert hash bytes to hex string
static std::string toHexString(const unsigned char *data, int len) {
    std::string result;
    result.reserve(len * 2);
    const char hex[] = "0123456789abcdef";
    for (int i = 0; i < len; i++) {
        result += hex[(data[i] >> 4) & 0x0f];
        result += hex[data[i] & 0x0f];
    }
    return result;
}

class SHA512Test_1644 : public ::testing::Test {
protected:
    unsigned char hash[64];
};

// Test SHA-512 with empty message
// NIST test vector: SHA-512("")
TEST_F(SHA512Test_1644, EmptyMessage_1644) {
    unsigned char msg[] = {};
    sha512(msg, 0, hash);
    std::string result = toHexString(hash, 64);
    EXPECT_EQ(result, "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
}

// Test SHA-512 with "abc" (short message, single block)
// NIST test vector
TEST_F(SHA512Test_1644, ShortMessageABC_1644) {
    unsigned char msg[] = "abc";
    sha512(msg, 3, hash);
    std::string result = toHexString(hash, 64);
    EXPECT_EQ(result, "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f");
}

// Test SHA-512 with two-block message (448-bit message)
// NIST test vector: "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
TEST_F(SHA512Test_1644, TwoBlockMessage_1644) {
    const char *input = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    int len = strlen(input);
    sha512((unsigned char *)input, len, hash);
    std::string result = toHexString(hash, 64);
    EXPECT_EQ(result, "204a8fc6dda82f0a0ced7beb8e08a41657c16ef468b228a8279be331a703c33596fd15c13b1b07f9aa1d3bea57789ca031ad85c7a71dd70354ec631238ca3445");
}

// Test SHA-512 with a longer message (896 bits / 112 bytes) - boundary case
// This tests the boundary where blkLen == 112 after padding
TEST_F(SHA512Test_1644, BoundaryMessage112Bytes_1644) {
    // 112 bytes message - after adding 0x80, blkLen = 113 > 112, triggers extra block
    unsigned char msg[112];
    memset(msg, 'a', 112);
    sha512(msg, 112, hash);
    // Just verify it doesn't crash and produces a 64-byte hash
    // The hash should be deterministic
    unsigned char hash2[64];
    sha512(msg, 112, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}

// Test SHA-512 with 111 bytes - boundary: blkLen after padding = 112 exactly
TEST_F(SHA512Test_1644, BoundaryMessage111Bytes_1644) {
    unsigned char msg[111];
    memset(msg, 'b', 111);
    sha512(msg, 111, hash);
    unsigned char hash2[64];
    sha512(msg, 111, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}

// Test SHA-512 with exactly 128 bytes (one full block before padding)
TEST_F(SHA512Test_1644, ExactOneBlock128Bytes_1644) {
    unsigned char msg[128];
    memset(msg, 'c', 128);
    sha512(msg, 128, hash);
    unsigned char hash2[64];
    sha512(msg, 128, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}

// Test SHA-512 with 1 byte message
TEST_F(SHA512Test_1644, SingleByteMessage_1644) {
    unsigned char msg[] = { 0x00 };
    sha512(msg, 1, hash);
    // SHA-512 of a single zero byte
    unsigned char hash2[64];
    sha512(msg, 1, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}

// Test SHA-512 determinism - same input always produces same output
TEST_F(SHA512Test_1644, Determinism_1644) {
    unsigned char msg[] = "Hello, World!";
    int len = strlen((const char *)msg);
    sha512(msg, len, hash);
    unsigned char hash2[64];
    sha512(msg, len, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}

// Test SHA-512 different inputs produce different hashes
TEST_F(SHA512Test_1644, DifferentInputsDifferentHashes_1644) {
    unsigned char msg1[] = "test1";
    unsigned char msg2[] = "test2";
    unsigned char hash2[64];
    sha512(msg1, 5, hash);
    sha512(msg2, 5, hash2);
    EXPECT_NE(memcmp(hash, hash2, 64), 0);
}

// Test SHA-512 with message longer than one block (> 128 bytes)
TEST_F(SHA512Test_1644, MultiBlockMessage_1644) {
    unsigned char msg[256];
    memset(msg, 'd', 256);
    sha512(msg, 256, hash);
    unsigned char hash2[64];
    sha512(msg, 256, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}

// Test SHA-512 with message of length 127 (just under one block)
TEST_F(SHA512Test_1644, Message127Bytes_1644) {
    unsigned char msg[127];
    memset(msg, 'e', 127);
    sha512(msg, 127, hash);
    unsigned char hash2[64];
    sha512(msg, 127, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}

// Test the well-known NIST vector for longer input
// "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"
TEST_F(SHA512Test_1644, NISTLongVector_1644) {
    const char *input = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    int len = strlen(input);
    sha512((unsigned char *)input, len, hash);
    std::string result = toHexString(hash, 64);
    EXPECT_EQ(result, "8e959b75dae313da8cf4f72814fc143f8f7779c6eb9f7fa17299aeadb6889018501d289e4900f7e4331b99dec4b5433ac7d329eeb6dd26545e96e55b874be909");
}

// Test SHA-512 with 113 bytes - boundary between needing extra block or not
TEST_F(SHA512Test_1644, BoundaryMessage113Bytes_1644) {
    unsigned char msg[113];
    memset(msg, 'f', 113);
    sha512(msg, 113, hash);
    unsigned char hash2[64];
    sha512(msg, 113, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 64), 0);
}
