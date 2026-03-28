#include <gtest/gtest.h>

#include "Decrypt.h"



// Mocking external collaborators if needed (none required in this case)



class DecryptTest_1614 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize state before each test

        memset(&state, 0, sizeof(DecryptAES256State));

    }



    DecryptAES256State state;

};



TEST_F(DecryptTest_1614, KeyExpansion_NormalOperation_1614) {

    unsigned char objKey[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,

                                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,

                                0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,

                                0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

    aes256KeyExpansion(&state, objKey, false);

    // Verify the first 8 words are correctly set

    for (int i = 0; i < 8; ++i) {

        unsigned int expectedValue = (objKey[4 * i] << 24) + (objKey[4 * i + 1] << 16) +

                                    (objKey[4 * i + 2] << 8) + objKey[4 * i + 3];

        EXPECT_EQ(state.w[i], expectedValue);

    }

}



TEST_F(DecryptTest_1614, KeyExpansion_DecryptFlagSet_1614) {

    unsigned char objKey[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    aes256KeyExpansion(&state, objKey, true);

    // Verify that decryption adjustments are made

    for (int round = 1; round <= 13; ++round) {

        EXPECT_NE(state.w[round * 4], 0);

        EXPECT_NE(state.w[round * 4 + 1], 0);

        EXPECT_NE(state.w[round * 4 + 2], 0);

        EXPECT_NE(state.w[round * 4 + 3], 0);

    }

}



TEST_F(DecryptTest_1614, KeyExpansion_BoundaryCondition_AllZeros_1614) {

    unsigned char objKey[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    aes256KeyExpansion(&state, objKey, false);

    // Verify the first 8 words are correctly set

    for (int i = 0; i < 8; ++i) {

        EXPECT_EQ(state.w[i], 0);

    }

}



TEST_F(DecryptTest_1614, KeyExpansion_BoundaryCondition_AllOnes_1614) {

    unsigned char objKey[32] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

                                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

                                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

                                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    aes256KeyExpansion(&state, objKey, false);

    // Verify the first 8 words are correctly set

    for (int i = 0; i < 8; ++i) {

        EXPECT_EQ(state.w[i], 0xFFFFFFFF);

    }

}
