#include <gtest/gtest.h>

#include "UnicodeConversions.cpp" // Assuming the function is in this file for testing



// Mocking external collaborators (if any) would go here, but none are needed in this case.



TEST(CodePoint_from_UTF16SwpTest_2079, NormalOperation_SingleBMPCodePoint_2079) {

    UTF16Unit utf16In[] = { 0x41 }; // 'A'

    size_t utf16Len = 1;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Swp(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0x41);

    EXPECT_EQ(utf16Read, 1);

}



TEST(CodePoint_from_UTF16SwpTest_2079, NormalOperation_SurrogatePair_2079) {

    UTF16Unit utf16In[] = { 0xD835, 0xDD46 }; // Mathematical bold capital F

    size_t utf16Len = 2;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Swp(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0x1D546);

    EXPECT_EQ(utf16Read, 2);

}



TEST(CodePoint_from_UTF16SwpTest_2079, BoundaryCondition_EmptyInput_2079) {

    UTF16Unit utf16In[] = {};

    size_t utf16Len = 0;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Swp(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0);

    EXPECT_EQ(utf16Read, 0);

}



TEST(CodePoint_from_UTF16SwpTest_2079, BoundaryCondition_SingleSurrogateStart_2079) {

    UTF16Unit utf16In[] = { 0xD835 };

    size_t utf16Len = 1;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Swp(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0xD835);

    EXPECT_EQ(utf16Read, 1);

}



TEST(CodePoint_from_UTF16SwpTest_2079, BoundaryCondition_SingleSurrogateEnd_2079) {

    UTF16Unit utf16In[] = { 0xDD46 };

    size_t utf16Len = 1;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Swp(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0xDD46);

    EXPECT_EQ(utf16Read, 1);

}



TEST(CodePoint_from_UTF16SwpTest_2079, ExceptionalCase_InvalidSurrogatePair_2079) {

    UTF16Unit utf16In[] = { 0xD835, 0x41 }; // Invalid surrogate pair

    size_t utf16Len = 2;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Swp(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0xD835);

    EXPECT_EQ(utf16Read, 1); // Only the first surrogate is read

}
