#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <vector>

// We need to access the static sha256 function. Since it's static in the .cc file,
// we include it directly. We also need to handle any dependencies.
// First, let's provide necessary includes that Decrypt.cc might need.

#include "config.h"
#include "Decrypt.h"

// Since sha256 is static, we need to access it by including the .cc file
// or by using a test-specific approach. We'll define a wrapper.
// Including the cc file to access static functions:
namespace {
    // Re-declare sha256 signature to match the static function
    // We'll test through the public API that uses sha256 if available,
    // or include the source directly.
}

// If we can't access static function directly, we test through public API.
// However, based on the task, let's include the source file.
#define static
#include "Decrypt.cc"
#undef static

class Sha256Test_1635 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
    
    std::string hashToHex(const unsigned char* hash, int len) {
        std::string result;
        char buf[3];
        for (int i = 0; i < len; i++) {
            snprintf(buf, sizeof(buf), "%02x", hash[i]);
            result += buf;
        }
        return result;
    }
};

// NIST test vector: SHA-256 of empty string
TEST_F(Sha256Test_1635, EmptyMessage_1635) {
    unsigned char hash[32];
    unsigned char msg[1] = {};
    sha256(msg, 0, hash);
    std::string hexHash = hashToHex(hash, 32);
    EXPECT_EQ(hexHash, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

// NIST test vector: SHA-256 of "abc"
TEST_F(Sha256Test_1635, ThreeByteMessage_1635) {
    unsigned char msg[] = "abc";
    unsigned char hash[32];
    sha256(msg, 3, hash);
    std::string hexHash = hashToHex(hash, 32);
    EXPECT_EQ(hexHash, "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
}

// NIST test vector: SHA-256 of "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" (56 bytes - boundary)
TEST_F(Sha256Test_1635, TwoBlockMessage_1635) {
    unsigned char msg[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    unsigned char hash[32];
    sha256(msg, 56, hash);
    std::string hexHash = hashToHex(hash, 32);
    EXPECT_EQ(hexHash, "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
}

// Single byte message
TEST_F(Sha256Test_1635, SingleByteMessage_1635) {
    unsigned char msg[] = {0x00};
    unsigned char hash[32];
    sha256(msg, 1, hash);
    std::string hexHash = hashToHex(hash, 32);
    // SHA-256 of single zero byte
    EXPECT_EQ(hexHash, "6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d");
}

// Exactly 64 bytes (one full block before padding)
TEST_F(Sha256Test_1635, ExactlyOneBlock_1635) {
    unsigned char msg[64];
    memset(msg, 'a', 64);
    unsigned char hash[32];
    sha256(msg, 64, hash);
    std::string hexHash = hashToHex(hash, 32);
    // SHA-256 of 64 'a' characters
    EXPECT_EQ(hexHash, "ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb");
}

// 55 bytes - boundary: padding fits in one block
TEST_F(Sha256Test_1635, FiftyFiveBytes_1635) {
    unsigned char msg[55];
    memset(msg, 'b', 55);
    unsigned char hash[32];
    sha256(msg, 55, hash);
    // Just verify it produces a 32-byte output without crashing
    // and is deterministic
    unsigned char hash2[32];
    sha256(msg, 55, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 32), 0);
}

// 56 bytes - boundary: padding requires extra block
TEST_F(Sha256Test_1635, FiftySixBytes_1635) {
    unsigned char msg[56];
    memset(msg, 'c', 56);
    unsigned char hash[32];
    sha256(msg, 56, hash);
    unsigned char hash2[32];
    sha256(msg, 56, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 32), 0);
}

// 63 bytes - boundary near block size
TEST_F(Sha256Test_1635, SixtyThreeBytes_1635) {
    unsigned char msg[63];
    memset(msg, 'd', 63);
    unsigned char hash[32];
    sha256(msg, 63, hash);
    unsigned char hash2[32];
    sha256(msg, 63, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 32), 0);
}

// 128 bytes - exactly two blocks
TEST_F(Sha256Test_1635, TwoFullBlocks_1635) {
    unsigned char msg[128];
    memset(msg, 'e', 128);
    unsigned char hash[32];
    sha256(msg, 128, hash);
    unsigned char hash2[32];
    sha256(msg, 128, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 32), 0);
}

// Different messages produce different hashes
TEST_F(Sha256Test_1635, DifferentMessagesProduceDifferentHashes_1635) {
    unsigned char msg1[] = "hello";
    unsigned char msg2[] = "world";
    unsigned char hash1[32], hash2[32];
    sha256(msg1, 5, hash1);
    sha256(msg2, 5, hash2);
    EXPECT_NE(memcmp(hash1, hash2, 32), 0);
}

// Determinism: same input always produces same output
TEST_F(Sha256Test_1635, Deterministic_1635) {
    unsigned char msg[] = "deterministic test";
    unsigned char hash1[32], hash2[32];
    sha256(msg, strlen((const char*)msg), hash1);
    sha256(msg, strlen((const char*)msg), hash2);
    EXPECT_EQ(memcmp(hash1, hash2, 32), 0);
}

// Large message (multiple blocks)
TEST_F(Sha256Test_1635, LargeMessage_1635) {
    std::vector<unsigned char> msg(1000, 'x');
    unsigned char hash[32];
    sha256(msg.data(), 1000, hash);
    unsigned char hash2[32];
    sha256(msg.data(), 1000, hash2);
    EXPECT_EQ(memcmp(hash, hash2, 32), 0);
}

// Known vector: SHA-256("") verified
TEST_F(Sha256Test_1635, OutputLength32Bytes_1635) {
    unsigned char msg[] = "test";
    unsigned char hash[32];
    memset(hash, 0xff, 32);
    sha256(msg, 4, hash);
    // Verify that hash was actually written (not all 0xff anymore)
    bool allFF = true;
    for (int i = 0; i < 32; i++) {
        if (hash[i] != 0xff) {
            allFF = false;
            break;
        }
    }
    EXPECT_FALSE(allFF);
}
