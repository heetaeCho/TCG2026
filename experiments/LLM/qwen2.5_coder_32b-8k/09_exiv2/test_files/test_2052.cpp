#include <gtest/gtest.h>

#include "UnicodeConversions.cpp" // Assuming this file contains the function to be tested



// Test fixture for SwapUTF16 tests

class SwapUTF16Test_2052 : public ::testing::Test {

protected:

    static const size_t kBufferSize = 10;

    UTF16Unit utf16In[kBufferSize];

    UTF16Unit utf16Out[kBufferSize];



    void SetUp() override {

        // Initialize the input buffer with some values

        for (size_t i = 0; i < kBufferSize; ++i) {

            utf16In[i] = static_cast<UTF16Unit>(0x1234 + i);

            utf16Out[i] = 0;

        }

    }

};



// Test normal operation

TEST_F(SwapUTF16Test_2052, NormalOperation_2052) {

    SwapUTF16(utf16In, utf16Out, kBufferSize);



    for (size_t i = 0; i < kBufferSize; ++i) {

        EXPECT_EQ(utf16Out[i], static_cast<UTF16Unit>(SwapBytes16(0x1234 + i)));

    }

}



// Test boundary condition with zero length

TEST_F(SwapUTF16Test_2052, ZeroLength_2052) {

    SwapUTF16(utf16In, utf16Out, 0);



    for (size_t i = 0; i < kBufferSize; ++i) {

        EXPECT_EQ(utf16Out[i], static_cast<UTF16Unit>(0));

    }

}



// Test boundary condition with maximum length

TEST_F(SwapUTF16Test_2052, MaxLength_2052) {

    SwapUTF16(utf16In, utf16Out, kBufferSize);



    for (size_t i = 0; i < kBufferSize; ++i) {

        EXPECT_EQ(utf16Out[i], static_cast<UTF16Unit>(SwapBytes16(0x1234 + i)));

    }

}



// Test with single element

TEST_F(SwapUTF16Test_2052, SingleElement_2052) {

    SwapUTF16(utf16In, utf16Out, 1);



    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(SwapBytes16(0x1234)));

}



// Helper function to swap bytes in a 16-bit value

inline uint16_t SwapBytes16(uint16_t val) {

    return (val << 8) | (val >> 8);

}
