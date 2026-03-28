#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_164 : public ::testing::Test {

protected:

    char value[5];

    int length;

};



TEST_F(XMLUtilTest_164, NormalOperation_Decimal_164) {

    const char* input = "&#65;";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, input + 5);

    EXPECT_STREQ(value, "A");

    EXPECT_EQ(length, 1);

}



TEST_F(XMLUtilTest_164, NormalOperation_Hexadecimal_164) {

    const char* input = "&#x41;";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, input + 6);

    EXPECT_STREQ(value, "A");

    EXPECT_EQ(length, 1);

}



TEST_F(XMLUtilTest_164, BoundaryCondition_MaxCodePoint_164) {

    const char* input = "&#x10FFFF;";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, input + 11);

    // The UTF-8 representation of U+10FFFF is 0xF4 0x8F 0xBF 0xBF

    EXPECT_STREQ(value, "\xf4\x8f\xbf\xbf");

    EXPECT_EQ(length, 4);

}



TEST_F(XMLUtilTest_164, BoundaryCondition_EmptyString_164) {

    const char* input = "";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



TEST_F(XMLUtilTest_164, BoundaryCondition_NoSemicolon_164) {

    const char* input = "&#x41";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



TEST_F(XMLUtilTest_164, BoundaryCondition_NoHash_164) {

    const char* input = "&65;";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



TEST_F(XMLUtilTest_164, ErrorCase_ExceedMaxCodePoint_164) {

    const char* input = "&#x110000;";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



TEST_F(XMLUtilTest_164, ErrorCase_NonNumericCharacters_164) {

    const char* input = "&#xGHI;";

    const char* result = XMLUtil::GetCharacterRef(input, value, &length);

    EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



TEST_F(XMLUtilTest_164, ErrorCase_EmptyValuePointer_164) {

    const char* input = "&#x41;";

    const char* result = XMLUtil::GetCharacterRef(input, nullptr, &length);

    EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



TEST_F(XMLUtilTest_164, ErrorCase_EmptyLengthPointer_164) {

    const char* input = "&#x41;";

    const char* result = XMLUtil::GetCharacterRef(input, value, nullptr);

    EXPECT_EQ(result, static_cast<const char*>(nullptr));

}
