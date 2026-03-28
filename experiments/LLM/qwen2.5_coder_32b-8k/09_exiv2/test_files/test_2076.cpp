#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "UnicodeConversions.cpp"



// Define a fixture for the tests if needed.

class CodePoint_to_UTF16Swp_SurrogateTest_2076 : public ::testing::Test {

protected:

    // No setup or teardown required for this function, but can be added if needed later

};



TEST_F(CodePoint_to_UTF16Swp_SurrogateTest_2076, NormalOperation_2076) {

    UTF32Unit cpIn = 0x10437; // Example code point in the surrogate range

    UTF16Unit utf16Out[2] = {0};

    size_t utf16Len = 2;

    size_t utf16Written = 0;



    CodePoint_to_UTF16Swp_Surrogate(cpIn, utf16Out, utf16Len, &utf16Written);



    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD801); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDC37); // Low surrogate

}



TEST_F(CodePoint_to_UTF16Swp_SurrogateTest_2076, BoundaryCondition_Min_2076) {

    UTF32Unit cpIn = 0x10000; // Minimum code point in the surrogate range

    UTF16Unit utf16Out[2] = {0};

    size_t utf16Len = 2;

    size_t utf16Written = 0;



    CodePoint_to_UTF16Swp_Surrogate(cpIn, utf16Out, utf16Len, &utf16Written);



    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD800); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDC00); // Low surrogate

}



TEST_F(CodePoint_to_UTF16Swp_SurrogateTest_2076, BoundaryCondition_Max_2076) {

    UTF32Unit cpIn = 0x10FFFF; // Maximum code point in the surrogate range

    UTF16Unit utf16Out[2] = {0};

    size_t utf16Len = 2;

    size_t utf16Written = 0;



    CodePoint_to_UTF16Swp_Surrogate(cpIn, utf16Out, utf16Len, &utf16Written);



    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xDBFF); // High surrogate

    EXPECT_EQ(utf16Out[1], 0xDFFF); // Low surrogate

}



TEST_F(CodePoint_to_UTF16Swp_SurrogateTest_2076, ExceptionalCase_OutOfRange_2076) {

    UTF32Unit cpIn = 0x110000; // Out of range code point

    UTF16Unit utf16Out[2] = {0};

    size_t utf16Len = 2;

    size_t utf16Written = 0;



    EXPECT_THROW({

        CodePoint_to_UTF16Swp_Surrogate(cpIn, utf16Out, utf16Len, &utf16Written);

    }, XMP_Error);



    // Assuming UC_Throw throws an XMP_Error exception

}



TEST_F(CodePoint_to_UTF16Swp_SurrogateTest_2076, ExceptionalCase_NotEnoughRoom_2076) {

    UTF32Unit cpIn = 0x10437; // Example code point in the surrogate range

    UTF16Unit utf16Out[2] = {0};

    size_t utf16Len = 1; // Not enough room for the output

    size_t utf16Written = 0;



    CodePoint_to_UTF16Swp_Surrogate(cpIn, utf16Out, utf16Len, &utf16Written);



    EXPECT_EQ(utf16Written, 0);

}
