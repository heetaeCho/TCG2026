#include <gtest/gtest.h>

#include "MD5.h"



// Assuming MD5Init is part of a class or can be tested directly

class MD5Test_2047 : public ::testing::Test {

protected:

    struct MD5_CTX ctx;

};



TEST_F(MD5Test_2047, InitializationSetsBufCorrectly_2047) {

    MD5Init(&ctx);

    EXPECT_EQ(ctx.buf[0], 0x67452301);

    EXPECT_EQ(ctx.buf[1], 0xefcdab89);

    EXPECT_EQ(ctx.buf[2], 0x98badcfe);

    EXPECT_EQ(ctx.buf[3], 0x10325476);

}



TEST_F(MD5Test_2047, InitializationSetsBytesToZero_2047) {

    MD5Init(&ctx);

    EXPECT_EQ(ctx.bytes[0], 0);

    EXPECT_EQ(ctx.bytes[1], 0);

}
