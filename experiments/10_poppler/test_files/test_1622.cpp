#include <gtest/gtest.h>



// Assuming MD5State is defined in a header file that we include

struct MD5State {

    unsigned long a;

    unsigned long b;

    unsigned long c;

    unsigned long d;

    unsigned char buf[64];

    int msgLen;

    unsigned char digest[16];

};



extern "C" void md5Start(MD5State *state);



TEST(md5StartTest_1622, InitializesStateCorrectly_1622) {

    MD5State state;

    md5Start(&state);

    

    EXPECT_EQ(state.a, 0x67452301);

    EXPECT_EQ(state.b, 0xefcdab89);

    EXPECT_EQ(state.c, 0x98badcfe);

    EXPECT_EQ(state.d, 0x10325476);

    EXPECT_EQ(state.bufLen, 0);

    EXPECT_EQ(state.msgLen, 0);

}



TEST(md5StartTest_1622, ZerosBufferAndDigest_1622) {

    MD5State state;

    // Fill buf and digest with non-zero values to ensure they are zeroed

    for (int i = 0; i < 64; ++i) state.buf[i] = 0xFF;

    for (int i = 0; i < 16; ++i) state.digest[i] = 0xFF;



    md5Start(&state);



    for (int i = 0; i < 64; ++i) EXPECT_EQ(state.buf[i], 0);

    for (int i = 0; i < 16; ++i) EXPECT_EQ(state.digest[i], 0);

}
