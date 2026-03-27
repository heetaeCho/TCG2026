#include <gtest/gtest.h>



// Assuming XMP_Uns32 is defined somewhere in the actual codebase.

typedef unsigned int XMP_Uns32;



extern "C" bool IsOtherChar_NonASCII(XMP_Uns32 cp);



class UnicodeInlinesTest_1878 : public ::testing::Test {

protected:

    // Setup and teardown if needed can be done here

};



TEST_F(UnicodeInlinesTest_1878, TestB7_ReturnsTrue_1878) {

    EXPECT_TRUE(IsOtherChar_NonASCII(0xB7));

}



TEST_F(UnicodeInlinesTest_1878, Test300_ReturnsTrue_1878) {

    EXPECT_TRUE(IsOtherChar_NonASCII(0x300));

}



TEST_F(UnicodeInlinesTest_1878, Test36F_ReturnsTrue_1878) {

    EXPECT_TRUE(IsOtherChar_NonASCII(0x36F));

}



TEST_F(UnicodeInlinesTest_1878, Test203F_ReturnsTrue_1878) {

    EXPECT_TRUE(IsOtherChar_NonASCII(0x203F));

}



TEST_F(UnicodeInlinesTest_1878, Test2040_ReturnsTrue_1878) {

    EXPECT_TRUE(IsOtherChar_NonASCII(0x2040));

}



TEST_F(UnicodeInlinesTest_1878, TestBelowRange300_ReturnsFalse_1878) {

    EXPECT_FALSE(IsOtherChar_NonASCII(0x2FF));

}



TEST_F(UnicodeInlinesTest_1878, TestAboveRange36F_ReturnsFalse_1878) {

    EXPECT_FALSE(IsOtherChar_NonASCII(0x370));

}



TEST_F(UnicodeInlinesTest_1878, TestBelowRange203F_ReturnsFalse_1878) {

    EXPECT_FALSE(IsOtherChar_NonASCII(0x203E));

}



TEST_F(UnicodeInlinesTest_1878, TestAboveRange2040_ReturnsFalse_1878) {

    EXPECT_FALSE(IsOtherChar_NonASCII(0x2041));

}



TEST_F(UnicodeInlinesTest_1878, TestZero_ReturnsFalse_1878) {

    EXPECT_FALSE(IsOtherChar_NonASCII(0x0));

}



TEST_F(UnicodeInlinesTest_1878, TestMaxValue_ReturnsFalse_1878) {

    XMP_Uns32 maxValue = std::numeric_limits<XMP_Uns32>::max();

    EXPECT_FALSE(IsOtherChar_NonASCII(maxValue));

}
