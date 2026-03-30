#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Decrypt.cc"



TEST(rc4DecryptByteTest_1599, NormalOperation_1599) {

    unsigned char state[256] = {0}; // Initialize state with zeros for simplicity

    unsigned char x = 0;

    unsigned char y = 0;

    unsigned char c = 10;



    unsigned char result = rc4DecryptByte(state, &x, &y, c);



    EXPECT_NE(result, c); // The output should be different from the input byte due to XOR operation

}



TEST(rc4DecryptByteTest_1599, BoundaryCondition_XWraparound_1599) {

    unsigned char state[256] = {0}; // Initialize state with zeros for simplicity

    unsigned char x = 255;

    unsigned char y = 0;

    unsigned char c = 20;



    unsigned char result = rc4DecryptByte(state, &x, &y, c);



    EXPECT_EQ(x, 0); // x should wrap around to 0 after increment

}



TEST(rc4DecryptByteTest_1599, BoundaryCondition_YWraparound_1599) {

    unsigned char state[256] = {0}; // Initialize state with zeros for simplicity

    unsigned char x = 1;

    unsigned char y = 255;

    unsigned char c = 30;



    unsigned char result = rc4DecryptByte(state, &x, &y, c);



    EXPECT_EQ(y, 0); // y should wrap around to 0 after addition with state[x]

}



TEST(rc4DecryptByteTest_1599, BoundaryCondition_XYWraparound_1599) {

    unsigned char state[256] = {0}; // Initialize state with zeros for simplicity

    unsigned char x = 255;

    unsigned char y = 255;

    unsigned char c = 40;



    unsigned char result = rc4DecryptByte(state, &x, &y, c);



    EXPECT_EQ(x, 0); // x should wrap around to 0 after increment

    EXPECT_EQ(y, 0); // y should wrap around to 0 after addition with state[x]

}



TEST(rc4DecryptByteTest_1599, StateModification_1599) {

    unsigned char state[256] = {0}; // Initialize state with zeros for simplicity

    unsigned char x = 1;

    unsigned char y = 2;

    unsigned char c = 50;



    unsigned char originalStateX = state[x];

    unsigned char originalStateY = state[y];



    rc4DecryptByte(state, &x, &y, c);



    EXPECT_NE(state[x], originalStateX); // State at index x should be modified

    EXPECT_NE(state[y], originalStateY); // State at index y should be modified

}
