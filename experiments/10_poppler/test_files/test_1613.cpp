#include <gtest/gtest.h>

#include "Decrypt.h"



// Mocking any external dependencies if needed (none in this case)



TEST_F(AesDecryptBlockTest_1613, NormalOperation_1613) {

    DecryptAESState s;

    unsigned char in[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

    unsigned char expectedOut[16] = {0}; // Expected output should be filled with actual expected result



    aesDecryptBlock(&s, in, false);



    for (int i = 0; i < 16; ++i) {

        EXPECT_EQ(s.buf[i], expectedOut[i]) << "Mismatch at index " << i;

    }

}



TEST_F(AesDecryptBlockTest_1613, LastBlockNormalOperation_1613) {

    DecryptAESState s;

    unsigned char in[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf1}; // f1 for padding length

    unsigned char expectedOut[15] = {0}; // Expected output should be filled with actual expected result



    aesDecryptBlock(&s, in, true);



    for (int i = 0; i < 15; ++i) {

        EXPECT_EQ(s.buf[i], expectedOut[i]) << "Mismatch at index " << i;

    }

}



TEST_F(AesDecryptBlockTest_1613, LastBlockPaddingTooLarge_1613) {

    DecryptAESState s;

    unsigned char in[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0x20}; // 20 for padding length (invalid)

    unsigned char expectedOut[15] = {0}; // Expected output should be filled with actual expected result



    aesDecryptBlock(&s, in, true);



    for (int i = 0; i < 15; ++i) {

        EXPECT_EQ(s.buf[i], expectedOut[i]) << "Mismatch at index " << i;

    }

}



TEST_F(AesDecryptBlockTest_1613, LastBlockPaddingZero_1613) {

    DecryptAESState s;

    unsigned char in[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0x00}; // 00 for padding length (invalid)

    unsigned char expectedOut[15] = {0}; // Expected output should be filled with actual expected result



    aesDecryptBlock(&s, in, true);



    for (int i = 0; i < 15; ++i) {

        EXPECT_EQ(s.buf[i], expectedOut[i]) << "Mismatch at index " << i;

    }

}
