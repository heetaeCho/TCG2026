#include <gtest/gtest.h>



// Mocking the subWord function for testing purposes

unsigned int subWord(unsigned int x);



TEST(subWordTest_1601, NormalOperation_1601) {

    EXPECT_EQ(subWord(0x00000000), 99);

    EXPECT_EQ(subWord(0xFFFFFFFF), 230);

    EXPECT_EQ(subWord(0x12345678), 136);

}



TEST(subWordTest_1601, BoundaryConditions_1601) {

    EXPECT_EQ(subWord(0x000000FF), 252);

    EXPECT_EQ(subWord(0x0000FF00), 194);

    EXPECT_EQ(subWord(0x00FF0000), 176);

    EXPECT_EQ(subWord(0xFF000000), 83);

}



TEST(subWordTest_1601, ExceptionalCases_1601) {

    // Since subWord is a deterministic function and does not throw exceptions,

    // we test with values that might be edge cases but should not cause errors.

    EXPECT_EQ(subWord(0xABCDEF01), 235);

    EXPECT_EQ(subWord(0xDEADBEEF), 148);

}



// If there were any external interactions, we would mock them here using Google Mock,

// but since subWord is a standalone function with no dependencies, this is not necessary.
