#include <gtest/gtest.h>

#include "UnicodeConversions.cpp" // Assuming this is how we include the function for testing



TEST(CodePoint_from_UTF16Nat_Surrogate_2068, ValidSurrogatePair_2068) {

    UTF16Unit utf16In[] = {0xD834, 0xDD1E}; // Represents musical symbol G clef in UTF-32: U+1D11E

    size_t utf16Len = 2;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Nat_Surrogate(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0x1D11E);

    EXPECT_EQ(utf16Read, 2);

}



TEST(CodePoint_from_UTF16Nat_Surrogate_2068, LeadingLowSurrogate_2068) {

    UTF16Unit utf16In[] = {0xDC00}; // Invalid leading low surrogate

    size_t utf16Len = 1;

    UTF32Unit cpOut;

    size_t utf16Read;



    EXPECT_THROW({

        CodePoint_from_UTF16Nat_Surrogate(utf16In, utf16Len, &cpOut, &utf16Read);

    }, XMP_Error);



    // Since the function throws an exception, we cannot check the values of cpOut and utf16Read

}



TEST(CodePoint_from_UTF16Nat_Surrogate_2068, MissingLowSurrogate_2068) {

    UTF16Unit utf16In[] = {0xD834}; // Only high surrogate without low surrogate

    size_t utf16Len = 1;

    UTF32Unit cpOut;

    size_t utf16Read;



    EXPECT_THROW({

        CodePoint_from_UTF16Nat_Surrogate(utf16In, utf16Len, &cpOut, &utf16Read);

    }, XMP_Error);



    // Since the function throws an exception, we cannot check the values of cpOut and utf16Read

}



TEST(CodePoint_from_UTF16Nat_Surrogate_2068, InvalidLowSurrogate_2068) {

    UTF16Unit utf16In[] = {0xD834, 0xD7FF}; // High surrogate with invalid low surrogate

    size_t utf16Len = 2;

    UTF32Unit cpOut;

    size_t utf16Read;



    EXPECT_THROW({

        CodePoint_from_UTF16Nat_Surrogate(utf16In, utf16Len, &cpOut, &utf16Read);

    }, XMP_Error);



    // Since the function throws an exception, we cannot check the values of cpOut and utf16Read

}



TEST(CodePoint_from_UTF16Nat_Surrogate_2068, NotEnoughInput_2068) {

    UTF16Unit utf16In[] = {0xD834}; // Only high surrogate without low surrogate

    size_t utf16Len = 1;

    UTF32Unit cpOut;

    size_t utf16Read;



    CodePoint_from_UTF16Nat_Surrogate(utf16In, utf16Len, &cpOut, &utf16Read);



    EXPECT_EQ(cpOut, 0);

    EXPECT_EQ(utf16Read, 0);

}
