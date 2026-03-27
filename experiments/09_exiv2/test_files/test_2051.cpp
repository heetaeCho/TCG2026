#include <gtest/gtest.h>

#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"



// Test fixture for UTF32InSwap function

class UTF32InSwapTest_2051 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



TEST_F(UTF32InSwapTest_2051, NormalOperation_2051) {

    UTF32Unit input = 0x12345678;

    UTF32Unit expectedOutput = 0x78563412;

    EXPECT_EQ(UTF32InSwap(&input), expectedOutput);

}



TEST_F(UTF32InSwapTest_2051, ZeroValue_2051) {

    UTF32Unit input = 0x00000000;

    UTF32Unit expectedOutput = 0x00000000;

    EXPECT_EQ(UTF32InSwap(&input), expectedOutput);

}



TEST_F(UTF32InSwapTest_2051, AllOnesValue_2051) {

    UTF32Unit input = 0xFFFFFFFF;

    UTF32Unit expectedOutput = 0xFFFFFFFF;

    EXPECT_EQ(UTF32InSwap(&input), expectedOutput);

}



TEST_F(UTF32InSwapTest_2051, MaxValue_2051) {

    UTF32Unit input = 0x7FFFFFFF;

    UTF32Unit expectedOutput = 0xFFFFFF7F;

    EXPECT_EQ(UTF32InSwap(&input), expectedOutput);

}



TEST_F(UTF32InSwapTest_2051, MinValue_2051) {

    UTF32Unit input = 0x80000000;

    UTF32Unit expectedOutput = 0x00000080;

    EXPECT_EQ(UTF32InSwap(&input), expectedOutput);

}



TEST_F(UTF32InSwapTest_2051, SingleByteValue_2051) {

    UTF32Unit input = 0x000000FF;

    UTF32Unit expectedOutput = 0xFF000000;

    EXPECT_EQ(UTF32InSwap(&input), expectedOutput);

}



TEST_F(UTF32InSwapTest_2051, SingleByteNonZero_2051) {

    UTF32Unit input = 0x0000007F;

    UTF32Unit expectedOutput = 0x7F000000;

    EXPECT_EQ(UTF32InSwap(&input), expectedOutput);

}
