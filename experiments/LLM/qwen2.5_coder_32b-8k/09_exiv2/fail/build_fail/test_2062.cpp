#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

#include "./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"



using namespace testing;



TEST(UnicodeConversionsTest_2062, NormalOperation_SingleByte_2062) {

    UTF32Unit cpIn = 0x41; // 'A'

    UTF8Unit utf8Out[4];

    size_t utf8Len = 4;

    size_t utf8Written = 0;



    CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 1);

    EXPECT_EQ(utf8Out[0], cpIn);

}



TEST(UnicodeConversionsTest_2062, NormalOperation_TwoBytes_2062) {

    UTF32Unit cpIn = 0x453; // 'С'

    UTF8Unit utf8Out[4];

    size_t utf8Len = 4;

    size_t utf8Written = 0;



    CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 2);

    EXPECT_EQ(utf8Out[0], 0xD1);

    EXPECT_EQ(utf8Out[1], 0x93);

}



TEST(UnicodeConversionsTest_2062, NormalOperation_ThreeBytes_2062) {

    UTF32Unit cpIn = 0x20AC; // '€'

    UTF8Unit utf8Out[4];

    size_t utf8Len = 4;

    size_t utf8Written = 0;



    CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 3);

    EXPECT_EQ(utf8Out[0], 0xE2);

    EXPECT_EQ(utf8Out[1], 0x82);

    EXPECT_EQ(utf8Out[2], 0xAC);

}



TEST(UnicodeConversionsTest_2062, NormalOperation_FourBytes_2062) {

    UTF32Unit cpIn = 0x1F600; // '😀'

    UTF8Unit utf8Out[4];

    size_t utf8Len = 4;

    size_t utf8Written = 0;



    CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 4);

    EXPECT_EQ(utf8Out[0], 0xF0);

    EXPECT_EQ(utf8Out[1], 0x9F);

    EXPECT_EQ(utf8Out[2], 0x98);

    EXPECT_EQ(utf8Out[3], 0x80);

}



TEST(UnicodeConversionsTest_2062, BoundaryCondition_MaxValidCodePoint_2062) {

    UTF32Unit cpIn = 0x10FFFF;

    UTF8Unit utf8Out[4];

    size_t utf8Len = 4;

    size_t utf8Written = 0;



    CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 4);

    EXPECT_EQ(utf8Out[0], 0xF4);

    EXPECT_EQ(utf8Out[1], 0x8F);

    EXPECT_EQ(utf8Out[2], 0xBF);

    EXPECT_EQ(utf8Out[3], 0xBF);

}



TEST(UnicodeConversionsTest_2062, BoundaryCondition_OutOfRangeCodePoint_2062) {

    UTF32Unit cpIn = 0x110000;

    UTF8Unit utf8Out[4];

    size_t utf8Len = 4;

    size_t utf8Written = 0;



    EXPECT_THROW(CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written), XMP_Error);

}



TEST(UnicodeConversionsTest_2062, BoundaryCondition_SurrogateCodePoint_2062) {

    UTF32Unit cpIn = 0xD800;

    UTF8Unit utf8Out[4];

    size_t utf8Len = 4;

    size_t utf8Written = 0;



    EXPECT_THROW(CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written), XMP_Error);

}



TEST(UnicodeConversionsTest_2062, BoundaryCondition_NotEnoughSpaceForOutput_2062) {

    UTF32Unit cpIn = 0x1F600; // '😀'

    UTF8Unit utf8Out[3];

    size_t utf8Len = 3;

    size_t utf8Written = 0;



    CodePoint_to_UTF8_Multi(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 0);

}
