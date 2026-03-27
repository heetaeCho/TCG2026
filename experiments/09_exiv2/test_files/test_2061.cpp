#include <gtest/gtest.h>

#include <string>

#include "UnicodeConversions.cpp"

#include "XMP_Const.h"



namespace {



class UnicodeConversionsTest : public ::testing::Test {

protected:

    std::string utf8Str;

};



TEST_F(UnicodeConversionsTest_NormalOperation_2061, SimpleUTF32ToUTF8Conversion_2061) {

    const UTF32Unit utf32In[] = {U'A', U'B', U'C'};

    size_t utf32Len = sizeof(utf32In) / sizeof(UTF32Unit);

    FromUTF32Native(utf32In, utf32Len, &utf8Str);

    EXPECT_EQ(utf8Str, "ABC");

}



TEST_F(UnicodeConversionsTest_NormalOperation_2061, MultiByteUTF32ToUTF8Conversion_2061) {

    const UTF32Unit utf32In[] = {U'\u0410', U'\u0411', U'\u0412'}; // Cyrillic 'A', 'B', 'C'

    size_t utf32Len = sizeof(utf32In) / sizeof(UTF32Unit);

    FromUTF32Native(utf32In, utf32Len, &utf8Str);

    EXPECT_EQ(utf8Str, "\xD0\x90\xd0\x91\xd0\x92");

}



TEST_F(UnicodeConversionsTest_BoundaryConditions_2061, EmptyInputString_2061) {

    const UTF32Unit utf32In[] = {};

    size_t utf32Len = 0;

    FromUTF32Native(utf32In, utf32Len, &utf8Str);

    EXPECT_EQ(utf8Str, "");

}



TEST_F(UnicodeConversionsTest_BoundaryConditions_2061, SingleCharacterInputString_2061) {

    const UTF32Unit utf32In[] = {U'A'};

    size_t utf32Len = 1;

    FromUTF32Native(utf32In, utf32Len, &utf8Str);

    EXPECT_EQ(utf8Str, "A");

}



TEST_F(UnicodeConversionsTest_ExceptionalCases_2061, IncompleteUnicodeAtEndOfString_2061) {

    const UTF32Unit utf32In[] = {0xD800}; // High surrogate without low surrogate

    size_t utf32Len = sizeof(utf32In) / sizeof(UTF32Unit);

    EXPECT_THROW({

        FromUTF32Native(utf32In, utf32Len, &utf8Str);

    }, XMP_Error);

}



TEST_F(UnicodeConversionsTest_ExceptionalCases_2061, InvalidUTF32Character_2061) {

    const UTF32Unit utf32In[] = {0x110000}; // Beyond Unicode range

    size_t utf32Len = sizeof(utf32In) / sizeof(UTF32Unit);

    EXPECT_THROW({

        FromUTF32Native(utf32In, utf32Len, &utf8Str);

    }, XMP_Error);

}



}  // namespace
