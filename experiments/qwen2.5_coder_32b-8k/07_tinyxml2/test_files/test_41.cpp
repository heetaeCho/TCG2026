#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_41 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(XMLUtilTest_41, IsUTF8Continuation_NormalOperation_41) {

    EXPECT_TRUE(IsUTF8Continuation('\x80'));

    EXPECT_TRUE(IsUTF8Continuation('\xBF'));

    EXPECT_FALSE(IsUTF8Continuation('\x7F'));

}



TEST_F(XMLUtilTest_41, IsUTF8Continuation_BoundaryConditions_41) {

    EXPECT_FALSE(IsUTF8Continuation('\x00'));

    EXPECT_TRUE(IsUTF8Continuation('\xC0'));

    EXPECT_TRUE(IsUTF8Continuation('\xFF'));

}



TEST_F(XMLUtilTest_41, ReadBOM_NormalOperation_41) {

    bool hasBOM = false;

    const char* bomString = "\xEF\xBB\xBFHello";

    const char* result = XMLUtil::ReadBOM(bomString, &hasBOM);

    EXPECT_TRUE(hasBOM);

    EXPECT_STREQ(result, "Hello");

}



TEST_F(XMLUtilTest_41, ReadBOM_NoBOM_41) {

    bool hasBOM = true;

    const char* noBOMString = "Hello";

    const char* result = XMLUtil::ReadBOM(noBOMString, &hasBOM);

    EXPECT_FALSE(hasBOM);

    EXPECT_STREQ(result, "Hello");

}



TEST_F(XMLUtilTest_41, ConvertUTF32ToUTF8_NormalOperation_41) {

    unsigned long input = 0x1F600; // Grinning Face Emoji

    char output[5] = {0};

    int length = sizeof(output);

    XMLUtil::ConvertUTF32ToUTF8(input, output, &length);

    EXPECT_EQ(length, 4);

    EXPECT_STREQ(output, "\xF0\x9F\x98\x80");

}



TEST_F(XMLUtilTest_41, ToStr_NormalOperation_41) {

    char buffer[20];

    XMLUtil::ToStr(123, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123");



    XMLUtil::ToStr(true, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "true");



    XMLUtil::ToStr(123.456f, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "123.456");



    XMLUtil::ToStr(7890123456LL, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "7890123456");

}



TEST_F(XMLUtilTest_41, ToInt_NormalOperation_41) {

    int value = 0;

    EXPECT_TRUE(XMLUtil::ToInt("123", &value));

    EXPECT_EQ(value, 123);



    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));

}



TEST_F(XMLUtilTest_41, ToBool_NormalOperation_41) {

    bool value = false;

    EXPECT_TRUE(XMLUtil::ToBool("true", &value));

    EXPECT_TRUE(value);



    EXPECT_TRUE(XMLUtil::ToBool("false", &value));

    EXPECT_FALSE(value);



    EXPECT_FALSE(XMLUtil::ToBool("yes", &value));

}



TEST_F(XMLUtilTest_41, ToFloat_NormalOperation_41) {

    float value = 0.0f;

    EXPECT_TRUE(XMLUtil::ToFloat("123.456", &value));

    EXPECT_FLOAT_EQ(value, 123.456f);



    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));

}



TEST_F(XMLUtilTest_41, ToDouble_NormalOperation_41) {

    double value = 0.0;

    EXPECT_TRUE(XMLUtil::ToDouble("123.456", &value));

    EXPECT_DOUBLE_EQ(value, 123.456);



    EXPECT_FALSE(XMLUtil::ToDouble("abc", &value));

}



TEST_F(XMLUtilTest_41, ToInt64_NormalOperation_41) {

    int64_t value = 0;

    EXPECT_TRUE(XMLUtil::ToInt64("123456789012345", &value));

    EXPECT_EQ(value, 123456789012345LL);



    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));

}



TEST_F(XMLUtilTest_41, ToUnsigned64_NormalOperation_41) {

    uint64_t value = 0;

    EXPECT_TRUE(XMLUtil::ToUnsigned64("123456789012345", &value));

    EXPECT_EQ(value, 123456789012345ULL);



    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));

}



TEST_F(XMLUtilTest_41, SetBoolSerialization_NormalOperation_41) {

    XMLUtil::SetBoolSerialization("yes", "no");

    // No observable behavior to verify directly

}



TEST_F(XMLUtilTest_41, SkipWhiteSpace_NormalOperation_41) {

    const char* input = "\n \t Hello";

    int lineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);

    EXPECT_STREQ(result, "Hello");

    EXPECT_EQ(lineNum, 2);



    lineNum = 0;

    char mutableInput[] = "\n \t Hello";

    char* mutableResult = XMLUtil::SkipWhiteSpace(mutableInput, &lineNum);

    EXPECT_STREQ(mutableResult, "Hello");

    EXPECT_EQ(lineNum, 2);

}



TEST_F(XMLUtilTest_41, IsWhiteSpace_NormalOperation_41) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));

    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));

    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));

    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));

}



TEST_F(XMLUtilTest_41, IsNameStartChar_NormalOperation_41) {

    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));

    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));

    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));

    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));

}



TEST_F(XMLUtilTest_41, IsNameChar_NormalOperation_41) {

    EXPECT_TRUE(XMLUtil::IsNameChar(':'));

    EXPECT_TRUE(XMLUtil::IsNameChar('_'));

    EXPECT_TRUE(XMLUtil::IsNameChar('A'));

    EXPECT_TRUE(XMLUtil::IsNameChar('-'));

    EXPECT_TRUE(XMLUtil::IsNameChar('.'));

    EXPECT_TRUE(XMLUtil::IsNameChar('9'));

    EXPECT_FALSE(XMLUtil::IsNameChar(' '));

}



TEST_F(XMLUtilTest_41, IsPrefixHex_NormalOperation_41) {

    const char* hexString = "x1A";

    EXPECT_TRUE(XMLUtil::IsPrefixHex(hexString));



    const char* nonHexString = "abc";

    EXPECT_FALSE(XMLUtil::IsPrefixHex(nonHexString));

}



TEST_F(XMLUtilTest_41, StringEqual_NormalOperation_41) {

    EXPECT_TRUE(XMLUtil::StringEqual("Hello", "Hello"));

    EXPECT_FALSE(XMLUtil::StringEqual("Hello", "World"));



    EXPECT_TRUE(XMLUtil::StringEqual("Hello", "HelloWorld", 5));

}



TEST_F(XMLUtilTest_41, GetCharacterRef_NormalOperation_41) {

    char value[20];

    int length = sizeof(value);

    const char* input = "&#65;";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_STREQ(result, ";");

    EXPECT_STREQ(value, "A");



    input = "&amp;";

    result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_STREQ(result, ";");

    EXPECT_STREQ(value, "&");

}
