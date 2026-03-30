#include <gtest/gtest.h>



// Assuming XMP_Uns32 is a typedef for an unsigned 32-bit integer

typedef uint32_t XMP_Uns32;



extern "C" bool IsOtherChar_ASCII(XMP_Uns32 cp);



class UnicodeInlinesTest_1877 : public ::testing::Test {

protected:

    // Any setup or teardown code can go here if needed

};



TEST_F(UnicodeInlinesTest_1877, NormalOperation_Digits_1877) {

    EXPECT_TRUE(IsOtherChar_ASCII('0'));

    EXPECT_TRUE(IsOtherChar_ASCII('5'));

    EXPECT_TRUE(IsOtherChar_ASCII('9'));

}



TEST_F(UnicodeInlinesTest_1877, NormalOperation_SpecialCharacters_1877) {

    EXPECT_TRUE(IsOtherChar_ASCII('-'));

    EXPECT_TRUE(IsOtherChar_ASCII('.'));

}



TEST_F(UnicodeInlinesTest_1877, BoundaryConditions_OutsideRange_1877) {

    EXPECT_FALSE(IsOtherChar_ASCII(' '));

    EXPECT_FALSE(IsOtherChar_ASCII('/'));

    EXPECT_FALSE(IsOtherChar_ASCII(':'));

    EXPECT_FALSE(IsOtherChar_ASCII('@'));

}



TEST_F(UnicodeInlinesTest_1877, BoundaryConditions_MaxValue_1877) {

    XMP_Uns32 max_value = std::numeric_limits<XMP_Uns32>::max();

    EXPECT_FALSE(IsOtherChar_ASCII(max_value));

}



TEST_F(UnicodeInlinesTest_1877, BoundaryConditions_Zero_1877) {

    EXPECT_TRUE(IsOtherChar_ASCII(0)); // Assuming 0 is not a valid ASCII character in this context

}



TEST_F(UnicodeInlinesTest_1877, ExceptionalCases_NonPrintableCharacters_1877) {

    EXPECT_FALSE(IsOtherChar_ASCII('\n'));

    EXPECT_FALSE(IsOtherChar_ASCII('\t'));

    EXPECT_FALSE(IsOtherChar_ASCII('\r'));

}
