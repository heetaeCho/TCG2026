#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "MD5.h"



// Mocking external collaborators if any (not required in this case)



class MD5Test : public ::testing::Test {

protected:

    struct MD5_CTX ctx;



    void SetUp() override {

        memset(&ctx, 0, sizeof(ctx));

    }

};



TEST_F(MD5Test_2048, UpdateWithEmptyBuffer_2048) {

    md5byte buf[] = {};

    unsigned len = 0;

    MD5Update(&ctx, buf, len);

    EXPECT_EQ(ctx.bytes[0], 0);

    EXPECT_EQ(ctx.bytes[1], 0);

}



TEST_F(MD5Test_2048, UpdateWithSingleByte_2048) {

    md5byte buf[] = {0x3a};

    unsigned len = 1;

    MD5Update(&ctx, buf, len);

    EXPECT_EQ(ctx.bytes[0], 1);

    EXPECT_EQ(ctx.bytes[1], 0);

}



TEST_F(MD5Test_2048, UpdateWith64Bytes_2048) {

    md5byte buf[64] = {0};

    unsigned len = 64;

    MD5Update(&ctx, buf, len);

    EXPECT_EQ(ctx.bytes[0], 64);

    EXPECT_EQ(ctx.bytes[1], 0);

}



TEST_F(MD5Test_2048, UpdateWithMoreThan64Bytes_2048) {

    md5byte buf[128] = {0};

    unsigned len = 128;

    MD5Update(&ctx, buf, len);

    EXPECT_EQ(ctx.bytes[0], 128);

    EXPECT_EQ(ctx.bytes[1], 0);

}



TEST_F(MD5Test_2048, UpdateWithBoundaryCondition_2048) {

    md5byte buf[63] = {0};

    unsigned len = 63;

    MD5Update(&ctx, buf, len);

    EXPECT_EQ(ctx.bytes[0], 63);

    EXPECT_EQ(ctx.bytes[1], 0);



    md5byte additionalBuf[2] = {0};

    unsigned additionalLen = 2;

    MD5Update(&ctx, additionalBuf, additionalLen);

    EXPECT_EQ(ctx.bytes[0], 65);

    EXPECT_EQ(ctx.bytes[1], 0);

}



TEST_F(MD5Test_2048, UpdateWithCarryOver_2048) {

    md5byte buf[64] = {0};

    unsigned len = 64;

    ctx.bytes[0] = 0xFFFFFFFF;

    MD5Update(&ctx, buf, len);

    EXPECT_EQ(ctx.bytes[0], 63);

    EXPECT_EQ(ctx.bytes[1], 1);

}
