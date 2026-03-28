#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF16Unit and UTF32Unit are defined somewhere in the codebase

using UTF16Unit = uint16_t;

using UTF32Unit = uint32_t;



extern "C" void CodePoint_from_UTF16Swp_Surrogate(const UTF16Unit* utf16In, const size_t utf16Len, UTF32Unit* cpOut, size_t* utf16Read);



TEST(CodePointFromUTF16SwpSurrogateTest_2078, ValidSurrogatePair_2078) {

    UTF16Unit input[] = {0xD834, 0xDD1E}; // Represents the musical symbol G clef (U+1D11E)

    size_t utf16Len = 2;

    UTF32Unit cpOut = 0;

    size_t utf16Read = 0;



    CodePoint_from_UTF16Swp_Surrogate(input, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0x1D11E);

    EXPECT_EQ(utf16Read, 2);

}



TEST(CodePointFromUTF16SwpSurrogateTest_2078, LeadingLowSurrogate_2078) {

    UTF16Unit input[] = {0xDC00}; // Invalid leading low surrogate

    size_t utf16Len = 1;

    UTF32Unit cpOut = 0;

    size_t utf16Read = 0;



    EXPECT_THROW(CodePoint_from_UTF16Swp_Surrogate(input, utf16Len, &cpOut, &utf16Read), std::exception);

}



TEST(CodePointFromUTF16SwpSurrogateTest_2078, MissingLowSurrogate_2078) {

    UTF16Unit input[] = {0xD834}; // Valid leading surrogate but no following low surrogate

    size_t utf16Len = 1;

    UTF32Unit cpOut = 0;

    size_t utf16Read = 0;



    EXPECT_THROW(CodePoint_from_UTF16Swp_Surrogate(input, utf16Len, &cpOut, &utf16Read), std::exception);

}



TEST(CodePointFromUTF16SwpSurrogateTest_2078, InsufficientInputLength_2078) {

    UTF16Unit input[] = {0xD834}; // Valid leading surrogate but no following low surrogate

    size_t utf16Len = 0; // Insufficient length to read any data

    UTF32Unit cpOut = 0;

    size_t utf16Read = 0;



    CodePoint_from_UTF16Swp_Surrogate(input, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(utf16Read, 0);

}



TEST(CodePointFromUTF16SwpSurrogateTest_2078, InvalidLowSurrogate_2078) {

    UTF16Unit input[] = {0xD834, 0xD834}; // Valid leading surrogate but invalid low surrogate

    size_t utf16Len = 2;

    UTF32Unit cpOut = 0;

    size_t utf16Read = 0;



    EXPECT_THROW(CodePoint_from_UTF16Swp_Surrogate(input, utf16Len, &cpOut, &utf16Read), std::exception);

}
