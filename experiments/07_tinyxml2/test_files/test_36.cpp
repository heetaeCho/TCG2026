#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



TEST(XMLUtilTests_36, IsWhiteSpace_NormalSpace_36) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));

}



TEST(XMLUtilTests_36, IsWhiteSpace_TabCharacter_36) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));

}



TEST(XMLUtilTests_36, IsWhiteSpace_NewlineCharacter_36) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));

}



TEST(XMLUtilTests_36, IsWhiteSpace_ReturnCharacter_36) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));

}



TEST(XMLUtilTests_36, IsWhiteSpace_FormFeedCharacter_36) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\f'));

}



TEST(XMLUtilTests_36, IsWhiteSpace_VisibleCharacter_36) {

    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));

}



TEST(XMLUtilTests_36, IsWhiteSpace_UTF8Continuation_36) {

    char utf8_continuation = '\x80'; // Example of UTF-8 continuation byte

    EXPECT_FALSE(XMLUtil::IsWhiteSpace(utf8_continuation));

}



TEST(XMLUtilTests_36, ReadBOM_UTF8_36) {

    const char* bom_utf8 = "\xEF\xBB\xBF";

    bool hasBOM;

    const char* result = XMLUtil::ReadBOM(bom_utf8, &hasBOM);

    EXPECT_TRUE(hasBOM);

    EXPECT_EQ(result - bom_utf8, 3); // Check if the pointer advanced by 3 bytes

}



TEST(XMLUtilTests_36, ReadBOM_NoBOM_36) {

    const char* no_bom = "Hello";

    bool hasBOM;

    const char* result = XMLUtil::ReadBOM(no_bom, &hasBOM);

    EXPECT_FALSE(hasBOM);

    EXPECT_EQ(result - no_bom, 0); // Check if the pointer did not advance

}



TEST(XMLUtilTests_36, GetCharacterRef_Normal_36) {

    const char* input = "&#65;";

    char value;

    int length;

    const char* result = XMLUtil::GetCharacterRef(input, &value, &length);

    EXPECT_EQ(value, 'A');

    EXPECT_EQ(length, 1);

    EXPECT_EQ(result - input, 6); // Check if the pointer advanced by 6 bytes

}



TEST(XMLUtilTests_36, GetCharacterRef_Hex_36) {

    const char* input = "&#x41;";

    char value;

    int length;

    const char* result = XMLUtil::GetCharacterRef(input, &value, &length);

    EXPECT_EQ(value, 'A');

    EXPECT_EQ(length, 1);

    EXPECT_EQ(result - input, 7); // Check if the pointer advanced by 7 bytes

}



TEST(XMLUtilTests_36, ConvertUTF32ToUTF8_Normal_36) {

    unsigned long utf32 = 0x41; // 'A'

    char output[5]; // 4 bytes for UTF-8 + 1 for null terminator

    int length;

    XMLUtil::ConvertUTF32ToUTF8(utf32, output, &length);

    EXPECT_STREQ(output, "A");

    EXPECT_EQ(length, 1);

}



TEST(XMLUtilTests_36, ConvertUTF32ToUTF8_SurrogatePair_36) {

    unsigned long utf32 = 0x1F600; // Grinning Face Emoji

    char output[5]; // 4 bytes for UTF-8 + 1 for null terminator

    int length;

    XMLUtil::ConvertUTF32ToUTF8(utf32, output, &length);

    EXPECT_STREQ(output, "\xF0\x9F\x98\x80");

    EXPECT_EQ(length, 4);

}



TEST(XMLUtilTests_36, ToStr_IntPositive_36) {

    char buffer[12];

    XMLUtil::ToStr(123, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123");

}



TEST(XMLUtilTests_36, ToStr_IntNegative_36) {

    char buffer[12];

    XMLUtil::ToStr(-123, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "-123");

}



TEST(XMLUtilTests_36, ToStr_UnsignedInt_36) {

    char buffer[12];

    XMLUtil::ToStr(123U, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123");

}



TEST(XMLUtilTests_36, ToStr_BoolTrue_36) {

    char buffer[6]; // "true" + null terminator

    XMLUtil::SetBoolSerialization("true", "false");

    XMLUtil::ToStr(true, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "true");

}



TEST(XMLUtilTests_36, ToStr_BoolFalse_36) {

    char buffer[7]; // "false" + null terminator

    XMLUtil::SetBoolSerialization("true", "false");

    XMLUtil::ToStr(false, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "false");

}



TEST(XMLUtilTests_36, ToStr_Float_36) {

    char buffer[12];

    XMLUtil::ToStr(123.45f, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123.45");

}



TEST(XMLUtilTests_36, ToStr_Double_36) {

    char buffer[12];

    XMLUtil::ToStr(123.456, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123.456");

}



TEST(XMLUtilTests_36, ToStr_Int64Positive_36) {

    char buffer[24];

    XMLUtil::ToStr(123LL, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123");

}



TEST(XMLUtilTests_36, ToStr_Int64Negative_36) {

    char buffer[24];

    XMLUtil::ToStr(-123LL, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "-123");

}



TEST(XMLUtilTests_36, ToStr_UInt64_36) {

    char buffer[24];

    XMLUtil::ToStr(123ULL, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123");

}



TEST(XMLUtilTests_36, ToInt_ValidNumber_36) {

    int value;

    EXPECT_TRUE(XMLUtil::ToInt("123", &value));

    EXPECT_EQ(value, 123);

}



TEST(XMLUtilTests_36, ToInt_NegativeNumber_36) {

    int value;

    EXPECT_TRUE(XMLUtil::ToInt("-123", &value));

    EXPECT_EQ(value, -123);

}



TEST(XMLUtilTests_36, ToInt_InvalidNumber_36) {

    int value;

    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));

}



TEST(XMLUtilTests_36, ToUnsigned_ValidNumber_36) {

    unsigned value;

    EXPECT_TRUE(XMLUtil::ToUnsigned("123", &value));

    EXPECT_EQ(value, 123U);

}



TEST(XMLUtilTests_36, ToUnsigned_NegativeNumber_36) {

    unsigned value;

    EXPECT_FALSE(XMLUtil::ToUnsigned("-123", &value));

}



TEST(XMLUtilTests_36, ToUnsigned_InvalidNumber_36) {

    unsigned value;

    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));

}



TEST(XMLUtilTests_36, ToBool_TrueString_36) {

    bool value;

    XMLUtil::SetBoolSerialization("true", "false");

    EXPECT_TRUE(XMLUtil::ToBool("true", &value));

    EXPECT_TRUE(value);

}



TEST(XMLUtilTests_36, ToBool_FalseString_36) {

    bool value;

    XMLUtil::SetBoolSerialization("true", "false");

    EXPECT_TRUE(XMLUtil::ToBool("false", &value));

    EXPECT_FALSE(value);

}



TEST(XMLUtilTests_36, ToBool_InvalidString_36) {

    bool value;

    EXPECT_FALSE(XMLUtil::ToBool("abc", &value));

}



TEST(XMLUtilTests_36, ToFloat_ValidNumber_36) {

    float value;

    EXPECT_TRUE(XMLUtil::ToFloat("123.45", &value));

    EXPECT_FLOAT_EQ(value, 123.45f);

}



TEST(XMLUtilTests_36, ToFloat_NegativeNumber_36) {

    float value;

    EXPECT_TRUE(XMLUtil::ToFloat("-123.45", &value));

    EXPECT_FLOAT_EQ(value, -123.45f);

}



TEST(XMLUtilTests_36, ToFloat_InvalidNumber_36) {

    float value;

    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));

}



TEST(XMLUtilTests_36, ToDouble_ValidNumber_36) {

    double value;

    EXPECT_TRUE(XMLUtil::ToDouble("123.456", &value));

    EXPECT_DOUBLE_EQ(value, 123.456);

}



TEST(XMLUtilTests_36, ToDouble_NegativeNumber_36) {

    double value;

    EXPECT_TRUE(XMLUtil::ToDouble("-123.456", &value));

    EXPECT_DOUBLE_EQ(value, -123.456);

}



TEST(XMLUtilTests_36, ToDouble_InvalidNumber_36) {

    double value;

    EXPECT_FALSE(XMLUtil::ToDouble("abc", &value));

}



TEST(XMLUtilTests_36, ToInt64_ValidNumber_36) {

    int64_t value;

    EXPECT_TRUE(XMLUtil::ToInt64("123456789012345", &value));

    EXPECT_EQ(value, 123456789012345LL);

}



TEST(XMLUtilTests_36, ToInt64_NegativeNumber_36) {

    int64_t value;

    EXPECT_TRUE(XMLUtil::ToInt64("-123456789012345", &value));

    EXPECT_EQ(value, -123456789012345LL);

}



TEST(XMLUtilTests_36, ToInt64_InvalidNumber_36) {

    int64_t value;

    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));

}



TEST(XMLUtilTests_36, ToUnsigned64_ValidNumber_36) {

    uint64_t value;

    EXPECT_TRUE(XMLUtil::ToUnsigned64("123456789012345", &value));

    EXPECT_EQ(value, 123456789012345ULL);

}



TEST(XMLUtilTests_36, ToUnsigned64_NegativeNumber_36) {

    uint64_t value;

    EXPECT_FALSE(XMLUtil::ToUnsigned64("-123456789012345", &value));

}



TEST(XMLUtilTests_36, ToUnsigned64_InvalidNumber_36) {

    uint64_t value;

    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));

}
