#include <gtest/gtest.h>

#include "MD5.h"

#include <cstring>



class MD5Test_2049 : public ::testing::Test {

protected:

    MD5_CTX ctx;



    void SetUp() override {

        memset(&ctx, 0, sizeof(ctx));

    }

};



TEST_F(MD5Test_2049, FinalizeEmptyMessage_2049) {

    md5byte digest[16];

    MD5Final(digest, &ctx);

    const md5byte expectedDigest[] = {0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04, 0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e};

    EXPECT_EQ(memcmp(digest, expectedDigest, sizeof(expectedDigest)), 0);

}



TEST_F(MD5Test_2049, FinalizeSingleByteMessage_2049) {

    ctx.bytes[0] = 1;

    ctx.in[0] = 'a';

    md5byte digest[16];

    MD5Final(digest, &ctx);

    const md5byte expectedDigest[] = {0x0c, 0xc1, 0x75, 0xb9, 0xc0, 0xf1, 0xb6, 0xa8, 0x31, 0xc3, 0x99, 0xe2, 0x6e, 0x7d, 0xfb, 0xa0};

    EXPECT_EQ(memcmp(digest, expectedDigest, sizeof(expectedDigest)), 0);

}



TEST_F(MD5Test_2049, FinalizeBoundaryMessage_2049) {

    // Test with a message that is exactly 63 bytes long

    memset(ctx.in, 'a', 63);

    ctx.bytes[0] = 63;

    md5byte digest[16];

    MD5Final(digest, &ctx);

    const md5byte expectedDigest[] = {0x78, 0xd6, 0xb9, 0xea, 0xf4, 0xa2, 0x3e, 0xc9, 0xf1, 0x5b, 0x6f, 0xe5, 0xcb, 0x7d, 0x9a, 0xc4};

    EXPECT_EQ(memcmp(digest, expectedDigest, sizeof(expectedDigest)), 0);

}



TEST_F(MD5Test_2049, FinalizeLargeMessage_2049) {

    // Test with a message that is exactly 64 bytes long (boundary condition)

    memset(ctx.in, 'a', 64);

    ctx.bytes[0] = 64;

    md5byte digest[16];

    MD5Final(digest, &ctx);

    const md5byte expectedDigest[] = {0x9e, 0xe2, 0xf3, 0x1d, 0xc8, 0xa7, 0xb2, 0x36, 0xea, 0x4b, 0xbe, 0xd4, 0xb5, 0xef, 0x9a, 0x9a};

    EXPECT_EQ(memcmp(digest, expectedDigest, sizeof(expectedDigest)), 0);

}



TEST_F(MD5Test_2049, FinalizeLargeBoundaryMessage_2049) {

    // Test with a message that is exactly 127 bytes long (boundary condition)

    memset(ctx.in, 'a', 64);

    ctx.bytes[0] = 127;

    md5byte digest[16];

    MD5Final(digest, &ctx);

    const md5byte expectedDigest[] = {0x3c, 0xf8, 0xc6, 0xa5, 0x94, 0x2b, 0xd4, 0xe1, 0xb1, 0x7a, 0x5f, 0x13, 0x11, 0xfd, 0xf3, 0xa6};

    EXPECT_EQ(memcmp(digest, expectedDigest, sizeof(expectedDigest)), 0);

}



TEST_F(MD5Test_2049, FinalizeMaxBytesMessage_2049) {

    // Test with a message that is exactly the max bytes representable by lower 32 bits

    memset(ctx.in, 'a', 64);

    ctx.bytes[0] = 0xFFFFFFFF;

    ctx.bytes[1] = 0x7FFFFFFF; // Simulate very large message size (less than 2^63)

    md5byte digest[16];

    MD5Final(digest, &ctx);

    const md5byte expectedDigest[] = {0xf9, 0xe5, 0xd4, 0x7b, 0x6a, 0xa4, 0x4a, 0x8e, 0xb2, 0x1d, 0x3a, 0xc5, 0x9f, 0xd5, 0x64, 0xe3};

    EXPECT_EQ(memcmp(digest, expectedDigest, sizeof(expectedDigest)), 0);

}
