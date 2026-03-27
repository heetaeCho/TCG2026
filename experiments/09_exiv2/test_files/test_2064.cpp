#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "UnicodeConversions.cpp"

#include "XMP_Const.h"



using namespace ::testing;



class UnicodeConversionsTest_2064 : public ::testing::Test {

protected:

    UTF8Unit utf8In[10];

    size_t utf8Len;

    UTF32Unit cpOut;

    size_t utf8Read;



    void SetUp() override {

        memset(utf8In, 0, sizeof(utf8In));

        utf8Len = 0;

        cpOut = 0;

        utf8Read = 0;

    }

};



TEST_F(UnicodeConversionsTest_2064, SingleByteUTF8_2064) {

    utf8In[0] = 0x61; // 'a'

    utf8Len = 1;



    CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read);



    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x61));

    EXPECT_EQ(utf8Read, 1);

}



TEST_F(UnicodeConversionsTest_2064, TwoByteUTF8_2064) {

    utf8In[0] = 0xC3; // 'é' (C3 A9)

    utf8In[1] = 0xA9;

    utf8Len = 2;



    CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read);



    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xE9));

    EXPECT_EQ(utf8Read, 2);

}



TEST_F(UnicodeConversionsTest_2064, ThreeByteUTF8_2064) {

    utf8In[0] = 0xE0; // '€' (E2 82 AC)

    utf8In[1] = 0xA2;

    utf8In[2] = 0xAC;

    utf8Len = 3;



    CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read);



    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x20AC));

    EXPECT_EQ(utf8Read, 3);

}



TEST_F(UnicodeConversionsTest_2064, FourByteUTF8_2064) {

    utf8In[0] = 0xF0; // '𐍈' (F0 90 8C B8)

    utf8In[1] = 0x90;

    utf8In[2] = 0x8C;

    utf8In[3] = 0xB8;

    utf8Len = 4;



    CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read);



    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x10198));

    EXPECT_EQ(utf8Read, 4);

}



TEST_F(UnicodeConversionsTest_2064, InvalidSingleByteUTF8_2064) {

    utf8In[0] = 0x80; // Invalid single byte UTF-8

    utf8Len = 1;



    EXPECT_THROW(CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2064, InvalidTwoByteUTF8_2064) {

    utf8In[0] = 0xC3; // 'é' (C3 A9)

    utf8In[1] = 0xFF; // Invalid second byte

    utf8Len = 2;



    EXPECT_THROW(CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2064, InvalidThreeByteUTF8_2064) {

    utf8In[0] = 0xE0; // '€' (E2 82 AC)

    utf8In[1] = 0x9F; // Invalid second byte

    utf8In[2] = 0xAC;

    utf8Len = 3;



    EXPECT_THROW(CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2064, InvalidFourByteUTF8_2064) {

    utf8In[0] = 0xF1; // '𐍈' (F0 90 8C B8)

    utf8In[1] = 0x90;

    utf8In[2] = 0xFF; // Invalid third byte

    utf8In[3] = 0xB8;

    utf8Len = 4;



    EXPECT_THROW(CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2064, SurrogateCodePoint_2064) {

    utf8In[0] = 0xED; // Invalid surrogate code point (ED A0 80)

    utf8In[1] = 0xA0;

    utf8In[2] = 0x80;

    utf8Len = 3;



    EXPECT_THROW(CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2064, OutOfRangeCodePoint_2064) {

    utf8In[0] = 0xF4; // Invalid out of range code point (F4 91 A9 BF)

    utf8In[1] = 0x91;

    utf8In[2] = 0xA9;

    utf8In[3] = 0xBF;

    utf8Len = 4;



    EXPECT_THROW(CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2064, InsufficientBytes_2064) {

    utf8In[0] = 0xF0; // '𐍈' (F0 90 8C B8)

    utf8In[1] = 0x90;

    utf8Len = 2;



    CodePoint_from_UTF8_Multi(utf8In, utf8Len, &cpOut, &utf8Read);



    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0));

    EXPECT_EQ(utf8Read, 0);

}
