#include <gtest/gtest.h>

#include "UnicodeConversions.hpp"

#include <string>



class UnicodeConversionsTest_2060 : public ::testing::Test {

protected:

    std::string utf8Str;

};



TEST_F(UnicodeConversionsTest_2060, SimpleConversionLittleEndian_2060) {

    UTF32Unit utf32In[] = { 0x41 }; // 'A'

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    FromUTF32(utf32In, utf32Len, &utf8Str, false);

    EXPECT_EQ(utf8Str, "A");

}



TEST_F(UnicodeConversionsTest_2060, SimpleConversionBigEndian_2060) {

    UTF32Unit utf32In[] = { 0x41 }; // 'A'

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    FromUTF32(utf32In, utf32Len, &utf8Str, true);

    EXPECT_EQ(utf8Str, "A");

}



TEST_F(UnicodeConversionsTest_2060, MultibyteCharacterConversionLittleEndian_2060) {

    UTF32Unit utf32In[] = { 0x1F600 }; // Grinning Face emoji

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    FromUTF32(utf32In, utf32Len, &utf8Str, false);

    EXPECT_EQ(utf8Str, "\xF0\x9F\x98\x80");

}



TEST_F(UnicodeConversionsTest_2060, MultibyteCharacterConversionBigEndian_2060) {

    UTF32Unit utf32In[] = { 0x1F600 }; // Grinning Face emoji

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    FromUTF32(utf32In, utf32Len, &utf8Str, true);

    EXPECT_EQ(utf8Str, "\xF0\x9F\x98\x80");

}



TEST_F(UnicodeConversionsTest_2060, MultipleCharactersConversionLittleEndian_2060) {

    UTF32Unit utf32In[] = { 0x41, 0x42, 0x43 }; // "ABC"

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    FromUTF32(utf32In, utf32Len, &utf8Str, false);

    EXPECT_EQ(utf8Str, "ABC");

}



TEST_F(UnicodeConversionsTest_2060, MultipleCharactersConversionBigEndian_2060) {

    UTF32Unit utf32In[] = { 0x41, 0x42, 0x43 }; // "ABC"

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    FromUTF32(utf32In, utf32Len, &utf8Str, true);

    EXPECT_EQ(utf8Str, "ABC");

}



TEST_F(UnicodeConversionsTest_2060, EmptyInput_2060) {

    UTF32Unit utf32In[] = {};

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    FromUTF32(utf32In, utf32Len, &utf8Str, false);

    EXPECT_EQ(utf8Str, "");

}



TEST_F(UnicodeConversionsTest_2060, IncompleteUnicodeLittleEndian_2060) {

    UTF32Unit utf32In[] = { 0x1F60 }; // Truncated Grinning Face emoji

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    EXPECT_THROW(FromUTF32(utf32In, utf32Len, &utf8Str, false), XMP_Error);

}



TEST_F(UnicodeConversionsTest_2060, IncompleteUnicodeBigEndian_2060) {

    UTF32Unit utf32In[] = { 0x1F60 }; // Truncated Grinning Face emoji

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    EXPECT_THROW(FromUTF32(utf32In, utf32Len, &utf8Str, true), XMP_Error);

}
