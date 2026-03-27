#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



TEST(IsNameCharTest_38, NormalOperation_Letter_38) {

    EXPECT_TRUE(XMLUtil::IsNameChar('a'));

    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));

}



TEST(IsNameCharTest_38, NormalOperation_Digit_38) {

    EXPECT_TRUE(XMLUtil::IsNameChar('0'));

    EXPECT_TRUE(XMLUtil::IsNameChar('9'));

}



TEST(IsNameCharTest_38, NormalOperation_PeriodAndHyphen_38) {

    EXPECT_TRUE(XMLUtil::IsNameChar('.'));

    EXPECT_TRUE(XMLUtil::IsNameChar('-'));

}



TEST(IsNameCharTest_38, BoundaryCondition_StartChar_38) {

    unsigned char startChar = 0x41; // 'A'

    EXPECT_TRUE(XMLUtil::IsNameChar(startChar));

}



TEST(IsNameCharTest_38, BoundaryCondition_EndChar_38) {

    unsigned char endChar = 0x7A; // 'z'

    EXPECT_TRUE(XMLUtil::IsNameChar(endChar));

}



TEST(IsNameCharTest_38, ExceptionalCase_SpecialCharacter_38) {

    EXPECT_FALSE(XMLUtil::IsNameChar('!'));

    EXPECT_FALSE(XMLUtil::IsNameChar('@'));

    EXPECT_FALSE(XMLUtil::IsNameChar('#'));

}



TEST(ReadBOMTest_38, NormalOperation_UTF8_38) {

    bool hasBOM = false;

    const char* bomStr = "\xEF\xBB\xBFHello";

    const char* result = XMLUtil::ReadBOM(bomStr, &hasBOM);

    EXPECT_TRUE(hasBOM);

    EXPECT_STREQ(result, "Hello");

}



TEST(ReadBOMTest_38, NormalOperation_NoBOM_38) {

    bool hasBOM = false;

    const char* noBOMStr = "Hello";

    const char* result = XMLUtil::ReadBOM(noBOMStr, &hasBOM);

    EXPECT_FALSE(hasBOM);

    EXPECT_STREQ(result, "Hello");

}



TEST(GetCharacterRefTest_38, NormalOperation_ValidReference_38) {

    const char* input = "&#65;";

    char value[10];

    int length;

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_STREQ(value, "A");

    EXPECT_EQ(length, 1);

    EXPECT_STREQ(result, ";");

}



TEST(GetCharacterRefTest_38, NormalOperation_HexReference_38) {

    const char* input = "&#x41;";

    char value[10];

    int length;

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_STREQ(value, "A");

    EXPECT_EQ(length, 1);

    EXPECT_STREQ(result, ";");

}



TEST(GetCharacterRefTest_38, ExceptionalCase_InvalidReference_38) {

    const char* input = "&#65";

    char value[10];

    int length;

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_STREQ(value, "");

    EXPECT_EQ(length, 0);

    EXPECT_STREQ(result, input);

}



TEST(ConvertUTF32ToUTF8Test_38, NormalOperation_SimpleCharacter_38) {

    unsigned long input = 'A';

    char output[5];

    int length;

    XMLUtil::ConvertUTF32ToUTF8(input, output, &length);

    EXPECT_STREQ(output, "A");

    EXPECT_EQ(length, 1);

}



TEST(ConvertUTF32ToUTF8Test_38, NormalOperation_MultiByteCharacter_38) {

    unsigned long input = 0x1F600; // Grinning Face Emoji

    char output[5];

    int length;

    XMLUtil::ConvertUTF32ToUTF8(input, output, &length);

    EXPECT_STREQ(output, "\xF0\x9F\x98\x80");

    EXPECT_EQ(length, 4);

}



TEST(ToIntTest_38, NormalOperation_ValidInteger_38) {

    const char* str = "123";

    int value;

    bool result = XMLUtil::ToInt(str, &value);

    EXPECT_TRUE(result);

    EXPECT_EQ(value, 123);

}



TEST(ToIntTest_38, ExceptionalCase_InvalidInteger_38) {

    const char* str = "abc";

    int value;

    bool result = XMLUtil::ToInt(str, &value);

    EXPECT_FALSE(result);

}



TEST(ToUnsignedTest_38, NormalOperation_ValidUnsigned_38) {

    const char* str = "123";

    unsigned int value;

    bool result = XMLUtil::ToUnsigned(str, &value);

    EXPECT_TRUE(result);

    EXPECT_EQ(value, 123u);

}



TEST(ToUnsignedTest_38, ExceptionalCase_NegativeNumber_38) {

    const char* str = "-123";

    unsigned int value;

    bool result = XMLUtil::ToUnsigned(str, &value);

    EXPECT_FALSE(result);

}



TEST(ToBoolTest_38, NormalOperation_TrueString_38) {

    const char* str = "true";

    bool value;

    bool result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_TRUE(value);

}



TEST(ToBoolTest_38, NormalOperation_FalseString_38) {

    const char* str = "false";

    bool value;

    bool result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_FALSE(value);

}



TEST(ToBoolTest_38, ExceptionalCase_InvalidBoolean_38) {

    const char* str = "unknown";

    bool value;

    bool result = XMLUtil::ToBool(str, &value);

    EXPECT_FALSE(result);

}



TEST(SkipWhiteSpaceTest_38, NormalOperation_LeadingSpaces_38) {

    const char* input = "   Hello";

    int lineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);

    EXPECT_STREQ(result, "Hello");

    EXPECT_EQ(lineNum, 0);

}



TEST(SkipWhiteSpaceTest_38, NormalOperation_NewLines_38) {

    const char* input = "\n\t Hello";

    int lineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);

    EXPECT_STREQ(result, "Hello");

    EXPECT_EQ(lineNum, 1);

}



TEST(IsWhiteSpaceTest_38, NormalOperation_Space_38) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));

}



TEST(IsWhiteSpaceTest_38, NormalOperation_Tab_38) {

    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));

}



TEST(IsWhiteSpaceTest_38, ExceptionalCase_Letter_38) {

    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));

}



TEST(SetBoolSerializationTest_38, NormalOperation_CustomStrings_38) {

    XMLUtil::SetBoolSerialization("yes", "no");

    // This is a void function, so we cannot verify its internal state.

    // However, if the class uses these strings correctly, it should be reflected in other functions like ToBool.

}



TEST(IsPrefixHexTest_38, NormalOperation_ValidHexPrefix_38) {

    const char* input = "x1A";

    EXPECT_TRUE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_38, ExceptionalCase_InvalidPrefix_38) {

    const char* input = "1A";

    EXPECT_FALSE(XMLUtil::IsPrefixHex(input));

}



TEST(StringEqualTest_38, NormalOperation_EqualStrings_38) {

    const char* p = "Hello";

    const char* q = "Hello";

    EXPECT_TRUE(XMLUtil::StringEqual(p, q));

}



TEST(StringEqualTest_38, ExceptionalCase_DifferentStrings_38) {

    const char* p = "Hello";

    const char* q = "World";

    EXPECT_FALSE(XMLUtil::StringEqual(p, q));

}
