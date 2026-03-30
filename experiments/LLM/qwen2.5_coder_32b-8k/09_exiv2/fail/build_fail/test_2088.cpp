#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF32Unit and UTF16Unit are defined somewhere in the codebase.

typedef uint32_t UTF32Unit;

typedef uint16_t UTF16Unit;



extern "C" {

    void UTF32Nat_to_UTF16Swp(const UTF32Unit * utf32In, const size_t utf32Len, UTF16Unit * utf16Out, const size_t utf16Len, size_t * utf32Read, size_t * utf16Written);

}



TEST(UTF32Nat_to_UTF16SwpTest_2088, BasicConversion_2088) {

    UTF32Unit utf32In[] = { 0x0041, 0x0042 };

    UTF16Unit utf16Out[2];

    size_t utf32Read, utf16Written;



    UTF32Nat_to_UTF16Swp(utf32In, 2, utf16Out, 2, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 2);

    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0x41);

    EXPECT_EQ(utf16Out[1], 0x42);

}



TEST(UTF32Nat_to_UTF16SwpTest_2088, SurrogatePairConversion_2088) {

    UTF32Unit utf32In[] = { 0x10000 };

    UTF16Unit utf16Out[2];

    size_t utf32Read, utf16Written;



    UTF32Nat_to_UTF16Swp(utf32In, 1, utf16Out, 2, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 1);

    EXPECT_EQ(utf16Written, 2);

    EXPECT_EQ(utf16Out[0], 0xD800);

    EXPECT_EQ(utf16Out[1], 0xDC00);

}



TEST(UTF32Nat_to_UTF16SwpTest_2088, InsufficientOutputBuffer_2088) {

    UTF32Unit utf32In[] = { 0x10000 };

    UTF16Unit utf16Out[1];

    size_t utf32Read, utf16Written;



    UTF32Nat_to_UTF16Swp(utf32In, 1, utf16Out, 1, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST(UTF32Nat_to_UTF16SwpTest_2088, EmptyInput_2088) {

    UTF32Unit utf32In[] = {};

    UTF16Unit utf16Out[2];

    size_t utf32Read, utf16Written;



    UTF32Nat_to_UTF16Swp(utf32In, 0, utf16Out, 2, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST(UTF32Nat_to_UTF16SwpTest_2088, PartialConversion_2088) {

    UTF32Unit utf32In[] = { 0x0041, 0x10000 };

    UTF16Unit utf16Out[1];

    size_t utf32Read, utf16Written;



    UTF32Nat_to_UTF16Swp(utf32In, 2, utf16Out, 1, &utf32Read, &utf16Written);



    EXPECT_EQ(utf32Read, 1);

    EXPECT_EQ(utf16Written, 1);

    EXPECT_EQ(utf16Out[0], 0x41);

}
