#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include the MD5 header - adjust path as needed
extern "C" {
    #include "MD5.h"
}

// If MD5.h doesn't provide extern declarations, declare them here
extern void MD5Init(struct MD5_CTX *ctx);
extern void MD5Update(struct MD5_CTX *ctx, const md5byte *buf, unsigned len);
extern void MD5Final(md5byte digest[16], struct MD5_CTX *ctx);

// Helper function to convert digest to hex string
static std::string digestToHex(const md5byte digest[16]) {
    char hex[33];
    for (int i = 0; i < 16; i++) {
        sprintf(hex + i * 2, "%02x", digest[i]);
    }
    hex[32] = '\0';
    return std::string(hex);
}

class MD5FinalTest_2049 : public ::testing::Test {
protected:
    struct MD5_CTX ctx;
    md5byte digest[16];

    void SetUp() override {
        memset(digest, 0, sizeof(digest));
        MD5Init(&ctx);
    }
};

// Test MD5 of empty string - well-known hash: d41d8cd98f00b204e9800998ecf8427e
TEST_F(MD5FinalTest_2049, EmptyString_2049) {
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "d41d8cd98f00b204e9800998ecf8427e");
}

// Test MD5 of "a" - well-known hash: 0cc175b9c0f1b6a831c399e269772661
TEST_F(MD5FinalTest_2049, SingleCharA_2049) {
    const md5byte data[] = "a";
    MD5Update(&ctx, data, 1);
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "0cc175b9c0f1b6a831c399e269772661");
}

// Test MD5 of "abc" - well-known hash: 900150983cd24fb0d6963f7d28e17f72
TEST_F(MD5FinalTest_2049, ThreeCharsAbc_2049) {
    const md5byte data[] = "abc";
    MD5Update(&ctx, data, 3);
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "900150983cd24fb0d6963f7d28e17f72");
}

// Test MD5 of "message digest" - well-known hash: f96b697d7cb7938d525a2f31aaf161d0
TEST_F(MD5FinalTest_2049, MessageDigest_2049) {
    const md5byte data[] = "message digest";
    MD5Update(&ctx, data, 14);
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "f96b697d7cb7938d525a2f31aaf161d0");
}

// Test MD5 of "abcdefghijklmnopqrstuvwxyz" - well-known hash: c3fcd3d76192e4007dfb496cca67e13b
TEST_F(MD5FinalTest_2049, AlphabetLowercase_2049) {
    const md5byte data[] = "abcdefghijklmnopqrstuvwxyz";
    MD5Update(&ctx, data, 26);
    MD5Final(digest, &ctx);
    std::string result = digestToHex(digest);
    EXPECT_EQ(result, "c3fcd3d76192e4007dfb496cca67e13b");
}

// Test that context is zeroed after MD5Final (security measure)
TEST_F(MD5FinalTest_2049, ContextZeroedAfterFinal_2049) {
    const md5byte data[] = "test";
    MD5Update(&ctx, data, 4);
    MD5Final(digest, &ctx);
    
    // Check that context is zeroed out
    md5byte zero_ctx[sizeof(struct MD5_CTX)];
    memset(zero_ctx, 0, sizeof(zero_ctx));
    EXPECT_EQ(memcmp(&ctx, zero_ctx, sizeof(struct MD5_CTX)), 0);
}

// Test digest output is 16 bytes (not null-terminated or anything weird)
TEST_F(MD5FinalTest_2049, DigestIs16Bytes_2049) {
    MD5Final(digest, &ctx);
    // Just verify we get a known 16-byte result for empty input
    // The digest should not be all zeros for the empty string
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Boundary: input exactly 55 bytes (padding fits in one block, count = 55, so 56-1-55=0)
TEST_F(MD5FinalTest_2049, Input55Bytes_2049) {
    md5byte data[55];
    memset(data, 'A', 55);
    MD5Update(&ctx, data, 55);
    MD5Final(digest, &ctx);
    // Just verify it produces a result without crashing
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Boundary: input exactly 56 bytes (padding forces extra block, count = 56 & 0x3f = 56, 56-1-56=-1 < 0)
TEST_F(MD5FinalTest_2049, Input56Bytes_2049) {
    md5byte data[56];
    memset(data, 'B', 56);
    MD5Update(&ctx, data, 56);
    MD5Final(digest, &ctx);
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Boundary: input exactly 64 bytes (one full block, count in padding = 0)
TEST_F(MD5FinalTest_2049, Input64Bytes_2049) {
    md5byte data[64];
    memset(data, 'C', 64);
    MD5Update(&ctx, data, 64);
    MD5Final(digest, &ctx);
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Boundary: input exactly 63 bytes (count = 63, 56-1-63 = -8 < 0, forces extra block)
TEST_F(MD5FinalTest_2049, Input63Bytes_2049) {
    md5byte data[63];
    memset(data, 'D', 63);
    MD5Update(&ctx, data, 63);
    MD5Final(digest, &ctx);
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Test incremental updates produce same result as single update
TEST_F(MD5FinalTest_2049, IncrementalUpdateConsistency_2049) {
    // Compute MD5 of "Hello, World!" in one shot
    struct MD5_CTX ctx1;
    md5byte digest1[16];
    MD5Init(&ctx1);
    const md5byte data[] = "Hello, World!";
    MD5Update(&ctx1, data, 13);
    MD5Final(digest1, &ctx1);

    // Compute MD5 of "Hello, World!" incrementally
    struct MD5_CTX ctx2;
    md5byte digest2[16];
    MD5Init(&ctx2);
    MD5Update(&ctx2, (const md5byte*)"Hello, ", 7);
    MD5Update(&ctx2, (const md5byte*)"World!", 6);
    MD5Final(digest2, &ctx2);

    EXPECT_EQ(memcmp(digest1, digest2, 16), 0);
}

// Test large input (multiple blocks)
TEST_F(MD5FinalTest_2049, LargeInput_2049) {
    md5byte data[1000];
    memset(data, 'X', 1000);
    MD5Update(&ctx, data, 1000);
    MD5Final(digest, &ctx);
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Test that different inputs produce different digests
TEST_F(MD5FinalTest_2049, DifferentInputsDifferentDigests_2049) {
    struct MD5_CTX ctx1, ctx2;
    md5byte digest1[16], digest2[16];

    MD5Init(&ctx1);
    MD5Update(&ctx1, (const md5byte*)"input1", 6);
    MD5Final(digest1, &ctx1);

    MD5Init(&ctx2);
    MD5Update(&ctx2, (const md5byte*)"input2", 6);
    MD5Final(digest2, &ctx2);

    EXPECT_NE(memcmp(digest1, digest2, 16), 0);
}

// Test RFC 1321 test vector: MD5("") = d41d8cd98f00b204e9800998ecf8427e
TEST_F(MD5FinalTest_2049, RFC1321_Empty_2049) {
    MD5Final(digest, &ctx);
    EXPECT_EQ(digestToHex(digest), "d41d8cd98f00b204e9800998ecf8427e");
}

// Test RFC 1321 test vector: MD5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789")
// = d174ab98d277d9f5a5611c2c9f419d9f
TEST_F(MD5FinalTest_2049, RFC1321_AlphanumericMixed_2049) {
    const md5byte data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    MD5Update(&ctx, data, 62);
    MD5Final(digest, &ctx);
    EXPECT_EQ(digestToHex(digest), "d174ab98d277d9f5a5611c2c9f419d9f");
}

// Test with binary data containing null bytes
TEST_F(MD5FinalTest_2049, BinaryDataWithNulls_2049) {
    md5byte data[8] = {0x00, 0x01, 0x02, 0x00, 0x04, 0x00, 0x06, 0x07};
    MD5Update(&ctx, data, 8);
    MD5Final(digest, &ctx);
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Test calling MD5Final twice (after first call, ctx is zeroed - effectively computing MD5 of empty from zeroed state)
TEST_F(MD5FinalTest_2049, DoubleFinal_2049) {
    const md5byte data[] = "test";
    MD5Update(&ctx, data, 4);
    md5byte digest1[16];
    MD5Final(digest1, &ctx);
    
    // ctx is now zeroed. Calling MD5Final again on zeroed ctx should not crash.
    // The result is undefined but it should not segfault.
    md5byte digest2[16];
    MD5Final(digest2, &ctx);
    
    // The two digests should be different since the state was different
    // (though technically after zeroing, the second call operates on a zeroed ctx)
    EXPECT_NE(memcmp(digest1, digest2, 16), 0);
}

// Boundary: input exactly 57 bytes
TEST_F(MD5FinalTest_2049, Input57Bytes_2049) {
    md5byte data[57];
    memset(data, 'E', 57);
    MD5Update(&ctx, data, 57);
    MD5Final(digest, &ctx);
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}

// Test very large input to ensure no overflow issues
TEST_F(MD5FinalTest_2049, VeryLargeInput_2049) {
    md5byte data[4096];
    memset(data, 'Z', 4096);
    for (int i = 0; i < 10; i++) {
        MD5Update(&ctx, data, 4096);
    }
    MD5Final(digest, &ctx);
    md5byte allZero[16];
    memset(allZero, 0, 16);
    EXPECT_NE(memcmp(digest, allZero, 16), 0);
}
