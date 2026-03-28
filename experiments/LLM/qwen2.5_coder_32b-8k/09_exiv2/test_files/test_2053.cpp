#include <gtest/gtest.h>

#include "UnicodeConversions.cpp"



// Test Fixture for SwapUTF32 tests

class SwapUTF32Test : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary test data here if needed

    }



    void TearDown() override {

        // Clean up any resources used in the tests if needed

    }

};



// Test case to verify normal operation of SwapUTF32

TEST_F(SwapUTF32Test, NormalOperation_2053) {

    const size_t len = 4;

    UTF32Unit utf32In[len] = {0x12345678, 0x9ABCDEF0, 0x23456789, 0xFEDCBA98};

    UTF32Unit expectedOut[len] = {0x78563412, 0xF0DEBC9A, 0x89674523, 0x98BADCFE};

    UTF32Unit utf32Out[len];



    SwapUTF32(utf32In, utf32Out, len);



    for (size_t i = 0; i < len; ++i) {

        EXPECT_EQ(utf32Out[i], expectedOut[i]);

    }

}



// Test case to verify boundary condition with zero length

TEST_F(SwapUTF32Test, ZeroLength_2053) {

    const size_t len = 0;

    UTF32Unit utf32In[1] = {0x12345678};

    UTF32Unit utf32Out[1];



    SwapUTF32(utf32In, utf32Out, len);



    // Since the length is zero, no changes should occur in utf32Out

    EXPECT_EQ(utf32Out[0], 0);

}



// Test case to verify boundary condition with single element

TEST_F(SwapUTF32Test, SingleElement_2053) {

    const size_t len = 1;

    UTF32Unit utf32In[len] = {0x12345678};

    UTF32Unit expectedOut[len] = {0x78563412};

    UTF32Unit utf32Out[len];



    SwapUTF32(utf32In, utf32Out, len);



    EXPECT_EQ(utf32Out[0], expectedOut[0]);

}



// Test case to verify handling of large values

TEST_F(SwapUTF32Test, LargeValues_2053) {

    const size_t len = 2;

    UTF32Unit utf32In[len] = {0xFFFFFFFF, 0x00000000};

    UTF32Unit expectedOut[len] = {0xFFFFFFFF, 0x00000000}; // Swapping should not change these values

    UTF32Unit utf32Out[len];



    SwapUTF32(utf32In, utf32Out, len);



    for (size_t i = 0; i < len; ++i) {

        EXPECT_EQ(utf32Out[i], expectedOut[i]);

    }

}



// Test case to verify handling of small values

TEST_F(SwapUTF32Test, SmallValues_2053) {

    const size_t len = 2;

    UTF32Unit utf32In[len] = {0x0000001A, 0x0000ABCD};

    UTF32Unit expectedOut[len] = {0x1A000000, 0xCDAB0000};

    UTF32Unit utf32Out[len];



    SwapUTF32(utf32In, utf32Out, len);



    for (size_t i = 0; i < len; ++i) {

        EXPECT_EQ(utf32Out[i], expectedOut[i]);

    }

}
