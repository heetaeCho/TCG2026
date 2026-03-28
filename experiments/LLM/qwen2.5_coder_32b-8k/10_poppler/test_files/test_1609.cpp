#include <gtest/gtest.h>

#include "Decrypt.cc"  // Assuming the file containing mixColumns and tables



class MixColumnsTest_1609 : public ::testing::Test {

protected:

    unsigned char state[16];



    void SetUp() override {

        for (int i = 0; i < 16; ++i) {

            state[i] = static_cast<unsigned char>(i);

        }

    }



    void TearDown() override {

        // No specific cleanup needed

    }

};



TEST_F(MixColumnsTest_1609, NormalOperation_1609) {

    mixColumns(state);



    // Expected results based on the mixColumns logic and provided state initialization

    unsigned char expected[16] = {0x9b, 0x5f, 0xd2, 0xf3, 

                                  0x7c, 0xb2, 0x4e, 0x8f, 

                                  0xfa, 0xe7, 0xa6, 0xc5, 

                                  0x19, 0x5d, 0xf8, 0x3a};

    

    for (int i = 0; i < 16; ++i) {

        EXPECT_EQ(state[i], expected[i]);

    }

}



TEST_F(MixColumnsTest_1609, ZeroState_1609) {

    for (int i = 0; i < 16; ++i) {

        state[i] = 0x00;

    }



    mixColumns(state);



    // Expected results with all zeros

    unsigned char expected[16] = {0x00, 0x00, 0x00, 0x00,

                                  0x00, 0x00, 0x00, 0x00,

                                  0x00, 0x00, 0x00, 0x00,

                                  0x00, 0x00, 0x00, 0x00};



    for (int i = 0; i < 16; ++i) {

        EXPECT_EQ(state[i], expected[i]);

    }

}



TEST_F(MixColumnsTest_1609, AllSameBytes_1609) {

    unsigned char byte_value = 0xff;

    for (int i = 0; i < 16; ++i) {

        state[i] = byte_value;

    }



    mixColumns(state);



    // Expected results with all same bytes

    unsigned char expected[16] = {0xe3, 0x57, 0xfb, 0xa2,

                                  0xe3, 0x57, 0xfb, 0xa2,

                                  0xe3, 0x57, 0xfb, 0xa2,

                                  0xe3, 0x57, 0xfb, 0xa2};



    for (int i = 0; i < 16; ++i) {

        EXPECT_EQ(state[i], expected[i]);

    }

}



TEST_F(MixColumnsTest_1609, BoundaryCondition_1609) {

    // Set boundary values

    state[0] = 0x00;

    state[4] = 0xff;

    state[8] = 0x7f;

    state[12] = 0x80;



    mixColumns(state);



    // Expected results with specific boundary condition

    unsigned char expected[16] = {0x75, 0x9e, 0xe3, 0x1c,

                                  0x00, 0xff, 0x7f, 0x80,

                                  0x00, 0xff, 0x7f, 0x80,

                                  0x00, 0xff, 0x7f, 0x80};



    for (int i = 0; i < 16; ++i) {

        EXPECT_EQ(state[i], expected[i]);

    }

}

```


