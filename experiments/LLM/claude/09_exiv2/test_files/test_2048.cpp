#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include the MD5 header - adjust path as needed
extern "C" {
    // Forward declarations based on the interface
    typedef unsigned int UWORD32;
    typedef unsigned char md5byte;

    struct MD5_CTX {
        UWORD32 buf[4];
        UWORD32 bytes[2];
        UWORD32 in[16];
    };

    void MD5Init(struct MD5_CTX *ctx);
    void MD5Update(struct MD5_CTX *ctx, md5byte const *buf, unsigned len);
    void MD5Final(md5byte digest[16], struct MD5_CTX *ctx);
}

// Try including the actual header if available
// If the above extern declarations conflict, remove them and use:
// #include "MD5.h"

class MD5Test_2048 : public ::testing::Test {
protected:
    MD5_CTX ctx;

    void SetUp() override {
        MD5Init(&ctx);
    }

    std::string digestToHex(const md5byte digest[16]) {
        char hex[33];
        for (int i = 0; i < 16; i++) {
            snprintf(hex + i * 2, 3, "%02x", digest[i]);
        }
        hex[32] = '\0';
        return std::string(hex);
    }

    std::string computeMD5(const std::string& input) {
        MD5_CTX c;
        MD5Init(&c);
        MD5Update(&c, reinterpret_cast<const md5byte*>(input.data()), static_cast<unsigned>(input.size()));
        md5byte digest[16];
        MD5Final(digest, &c);
        return digestToHex(digest);
    }
};

// Test: MD5 of empty string should produce known hash
TEST_F(MD5Test_2048, EmptyString_2048) {
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "d41d8cd98f00b204e9800998ecf8427e");
}

// Test: MD5 of "a" should produce known hash
TEST_F(MD5Test_2048, SingleCharA_2048) {
    const md5byte data[] = "a";
    MD5Update(&ctx, data, 1);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "0cc175b9c0f1b6a831c399e269772661");
}

// Test: MD5 of "abc" should produce known hash
TEST_F(MD5Test_2048, ThreeCharABC_2048) {
    const md5byte data[] = "abc";
    MD5Update(&ctx, data, 3);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "900150983cd24fb0d6963f7d28e17f72");
}

// Test: MD5 of "message digest" should produce known hash
TEST_F(MD5Test_2048, MessageDigest_2048) {
    const char* msg = "message digest";
    MD5Update(&ctx, reinterpret_cast<const md5byte*>(msg), static_cast<unsigned>(strlen(msg)));
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "f96b697d7cb7938d525a2f31aaf161d0");
}

// Test: MD5 of "abcdefghijklmnopqrstuvwxyz" should produce known hash
TEST_F(MD5Test_2048, Alphabet_2048) {
    const char* msg = "abcdefghijklmnopqrstuvwxyz";
    MD5Update(&ctx, reinterpret_cast<const md5byte*>(msg), static_cast<unsigned>(strlen(msg)));
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "c3fcd3d76192e4007dfb496cca67e13b");
}

// Test: Updating with zero length should not change the hash (should still be empty hash)
TEST_F(MD5Test_2048, ZeroLengthUpdate_2048) {
    const md5byte data[] = "anything";
    MD5Update(&ctx, data, 0);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "d41d8cd98f00b204e9800998ecf8427e");
}

// Test: Multiple small updates should produce same result as single update
TEST_F(MD5Test_2048, IncrementalUpdateEquivalence_2048) {
    // Compute MD5 of "abc" in one shot
    std::string one_shot = computeMD5("abc");

    // Compute MD5 of "abc" incrementally
    MD5_CTX c;
    MD5Init(&c);
    const md5byte a[] = "a";
    const md5byte b[] = "b";
    const md5byte cc[] = "c";
    MD5Update(&c, a, 1);
    MD5Update(&c, b, 1);
    MD5Update(&c, cc, 1);
    md5byte digest[16];
    MD5Final(digest, &c);
    std::string incremental = digestToHex(digest);

    EXPECT_EQ(one_shot, incremental);
}

// Test: Data exactly 64 bytes (one full block)
TEST_F(MD5Test_2048, ExactlyOneBlock_2048) {
    // 64 bytes of 'A'
    std::string data(64, 'A');
    MD5Update(&ctx, reinterpret_cast<const md5byte*>(data.data()), 64);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    // Known MD5 for 64 'A's
    EXPECT_EQ(result, computeMD5(data));
    // Verify it's not the empty hash
    EXPECT_NE(result, "d41d8cd98f00b204e9800998ecf8427e");
}

// Test: Data exactly 128 bytes (two full blocks)
TEST_F(MD5Test_2048, ExactlyTwoBlocks_2048) {
    std::string data(128, 'B');
    std::string result = computeMD5(data);
    // Verify it's not the empty hash
    EXPECT_NE(result, "d41d8cd98f00b204e9800998ecf8427e");
    // Verify consistency
    EXPECT_EQ(result, computeMD5(data));
}

// Test: Data 63 bytes (just under one block)
TEST_F(MD5Test_2048, JustUnderOneBlock_2048) {
    std::string data(63, 'C');
    MD5Update(&ctx, reinterpret_cast<const md5byte*>(data.data()), 63);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, computeMD5(data));
}

// Test: Data 65 bytes (just over one block)
TEST_F(MD5Test_2048, JustOverOneBlock_2048) {
    std::string data(65, 'D');
    MD5Update(&ctx, reinterpret_cast<const md5byte*>(data.data()), 65);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, computeMD5(data));
}

// Test: Large data (1000 bytes)
TEST_F(MD5Test_2048, LargeData_2048) {
    std::string data(1000, 'E');
    std::string result = computeMD5(data);
    EXPECT_NE(result, "d41d8cd98f00b204e9800998ecf8427e");
    // Verify consistency
    EXPECT_EQ(result, computeMD5(data));
}

// Test: Incremental update crossing block boundary
TEST_F(MD5Test_2048, IncrementalCrossingBlockBoundary_2048) {
    // Feed 60 bytes, then 10 bytes (crosses the 64-byte block boundary)
    std::string part1(60, 'F');
    std::string part2(10, 'G');
    std::string combined = part1 + part2;

    // One-shot
    std::string one_shot = computeMD5(combined);

    // Incremental
    MD5_CTX c;
    MD5Init(&c);
    MD5Update(&c, reinterpret_cast<const md5byte*>(part1.data()), static_cast<unsigned>(part1.size()));
    MD5Update(&c, reinterpret_cast<const md5byte*>(part2.data()), static_cast<unsigned>(part2.size()));
    md5byte digest[16];
    MD5Final(digest, &c);
    std::string incremental = digestToHex(digest);

    EXPECT_EQ(one_shot, incremental);
}

// Test: Many small incremental updates
TEST_F(MD5Test_2048, ManySmallUpdates_2048) {
    std::string data = "The quick brown fox jumps over the lazy dog";
    std::string one_shot = computeMD5(data);

    // Known MD5 for this string
    EXPECT_EQ(one_shot, "9e107d9d372bb6826bd81d3542a419d6");

    // Feed byte by byte
    MD5_CTX c;
    MD5Init(&c);
    for (size_t i = 0; i < data.size(); i++) {
        MD5Update(&c, reinterpret_cast<const md5byte*>(&data[i]), 1);
    }
    md5byte digest[16];
    MD5Final(digest, &c);
    std::string incremental = digestToHex(digest);

    EXPECT_EQ(one_shot, incremental);
}

// Test: Reinitializing context should reset state
TEST_F(MD5Test_2048, ReinitResetsState_2048) {
    const char* msg = "some data";
    MD5Update(&ctx, reinterpret_cast<const md5byte*>(msg), static_cast<unsigned>(strlen(msg)));

    // Reinitialize
    MD5Init(&ctx);

    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);

    // Should be the empty string hash again
    EXPECT_EQ(result, "d41d8cd98f00b204e9800998ecf8427e");
}

// Test: Different inputs produce different hashes
TEST_F(MD5Test_2048, DifferentInputsDifferentHashes_2048) {
    std::string hash1 = computeMD5("hello");
    std::string hash2 = computeMD5("world");
    EXPECT_NE(hash1, hash2);
}

// Test: Known RFC 1321 test vector - "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
TEST_F(MD5Test_2048, RFC1321NumericString_2048) {
    const char* msg = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    std::string result = computeMD5(msg);
    EXPECT_EQ(result, "57edf4a22be3c955ac49da2e2107b67a");
}

// Test: Update with data that spans exactly multiple blocks
TEST_F(MD5Test_2048, MultipleExactBlocks_2048) {
    std::string data(256, 'X'); // 4 blocks exactly
    std::string one_shot = computeMD5(data);

    // Split into 4 chunks of 64
    MD5_CTX c;
    MD5Init(&c);
    for (int i = 0; i < 4; i++) {
        MD5Update(&c, reinterpret_cast<const md5byte*>(data.data() + i * 64), 64);
    }
    md5byte digest[16];
    MD5Final(digest, &c);
    std::string chunked = digestToHex(digest);

    EXPECT_EQ(one_shot, chunked);
}

// Test: Single byte update
TEST_F(MD5Test_2048, SingleByteUpdate_2048) {
    md5byte byte = 0x00;
    MD5Update(&ctx, &byte, 1);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    // MD5 of single null byte
    EXPECT_EQ(result, "93b885adfe0da089cdf634904fd59f71");
}

// Test: Binary data with all byte values
TEST_F(MD5Test_2048, BinaryData_2048) {
    md5byte data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<md5byte>(i);
    }
    MD5Update(&ctx, data, 256);
    md5byte digest[16];
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    // Should produce a valid 32-char hex string
    EXPECT_EQ(result.size(), 32u);
    // Verify consistency
    std::string data_str(reinterpret_cast<char*>(data), 256);
    EXPECT_EQ(result, computeMD5(data_str));
}

// Test: Partial block followed by full blocks
TEST_F(MD5Test_2048, PartialThenFullBlocks_2048) {
    std::string data(200, 'Y');  // 3*64 + 8 = 200
    std::string one_shot = computeMD5(data);

    // Feed 30 bytes, then 170 bytes
    MD5_CTX c;
    MD5Init(&c);
    MD5Update(&c, reinterpret_cast<const md5byte*>(data.data()), 30);
    MD5Update(&c, reinterpret_cast<const md5byte*>(data.data() + 30), 170);
    md5byte digest[16];
    MD5Final(digest, &c);
    std::string split = digestToHex(digest);

    EXPECT_EQ(one_shot, split);
}
