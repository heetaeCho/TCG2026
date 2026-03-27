#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the MD5State struct and md5ProcessBlock function are declared in a header file.

extern "C" {

    void md5ProcessBlock(MD5State *state);

}



struct MD5State {

    unsigned long a;

    unsigned long b;

    unsigned long c;

    unsigned long d;

    unsigned char buf[64];

    int msgLen;

    unsigned char digest[16];

};



// Test fixture for MD5State tests

class MD5StateTest_1623 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the state before each test

        state.a = 0x67452301;

        state.b = 0xefcdab89;

        state.c = 0x98badcfe;

        state.d = 0x10325476;

        state.msgLen = 0;

        for (int i = 0; i < 64; ++i) {

            state.buf[i] = 0;

        }

    }



    MD5State state;

};



TEST_F(MD5StateTest_1623, ProcessBlockWithZeroBuffer_1623) {

    // Arrange

    memset(state.buf, 0, sizeof(state.buf));



    // Act

    md5ProcessBlock(&state);



    // Assert

    EXPECT_EQ(state.a, 0xd76aa478);

    EXPECT_EQ(state.b, 0xe8c7b756);

    EXPECT_EQ(state.c, 0x242070db);

    EXPECT_EQ(state.d, 0xc1bdceee);

}



TEST_F(MD5StateTest_1623, ProcessBlockWithFullBuffer_1623) {

    // Arrange

    memset(state.buf, 0xFF, sizeof(state.buf));



    // Act

    md5ProcessBlock(&state);



    // Assert

    EXPECT_EQ(state.a, 0x740c89d1);

    EXPECT_EQ(state.b, 0xc62b35ee);

    EXPECT_EQ(state.c, 0xe91242fa);

    EXPECT_EQ(state.d, 0xf35b8a9e);

}



TEST_F(MD5StateTest_1623, ProcessBlockWithPartialBuffer_1623) {

    // Arrange

    for (int i = 0; i < 32; ++i) {

        state.buf[i] = 0xFF;

    }

    for (int i = 32; i < 64; ++i) {

        state.buf[i] = 0x00;

    }



    // Act

    md5ProcessBlock(&state);



    // Assert

    EXPECT_EQ(state.a, 0xc7b1f9db);

    EXPECT_EQ(state.b, 0x3d26a4fc);

    EXPECT_EQ(state.c, 0xa9ec38e7);

    EXPECT_EQ(state.d, 0x5deceee4);

}



TEST_F(MD5StateTest_1623, ProcessBlockWithIncrementalBuffer_1623) {

    // Arrange

    for (int i = 0; i < 64; ++i) {

        state.buf[i] = static_cast<unsigned char>(i);

    }



    // Act

    md5ProcessBlock(&state);



    // Assert

    EXPECT_EQ(state.a, 0x32d9a8b1);

    EXPECT_EQ(state.b, 0xff04d6c9);

    EXPECT_EQ(state.c, 0xfdb7c4e3);

    EXPECT_EQ(state.d, 0x53f3f5fb);

}



TEST_F(MD5StateTest_1623, ProcessBlockWithNegativeValuesInBuffer_1623) {

    // Arrange

    for (int i = 0; i < 64; ++i) {

        state.buf[i] = static_cast<unsigned char>(-i); // This will wrap around to positive values

    }



    // Act

    md5ProcessBlock(&state);



    // Assert

    EXPECT_EQ(state.a, 0x7834c2df);

    EXPECT_EQ(state.b, 0xf9c6b1e1);

    EXPECT_EQ(state.c, 0x9a5f6d1c);

    EXPECT_EQ(state.d, 0xe1b68c32);

}



TEST_F(MD5StateTest_1623, ProcessBlockWithMessageLengthOverflow_1623) {

    // Arrange

    memset(state.buf, 0xFF, sizeof(state.buf));

    state.msgLen = INT_MAX;



    // Act

    md5ProcessBlock(&state);



    // Assert

    EXPECT_EQ(state.a, 0x740c89d1);

    EXPECT_EQ(state.b, 0xc62b35ee);

    EXPECT_EQ(state.c, 0xe91242fa);

    EXPECT_EQ(state.d, 0xf35b8a9e);

}
