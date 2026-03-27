#include <gtest/gtest.h>

#include "tinyxml2.h"



class XMLUtilTest_172 : public ::testing::Test {

protected:

    int value;

};



TEST_F(XMLUtilTest_172, ToInt_ValidDecimalString_ReturnsTrueAndCorrectValue_172) {

    const char* str = "123";

    EXPECT_TRUE(tinyxml2::XMLUtil::ToInt(str, &value));

    EXPECT_EQ(value, 123);

}



TEST_F(XMLUtilTest_172, ToInt_ValidHexString_ReturnsTrueAndCorrectValue_172) {

    const char* str = "0x1A";

    EXPECT_TRUE(tinyxml2::XMLUtil::ToInt(str, &value));

    EXPECT_EQ(value, 26);

}



TEST_F(XMLUtilTest_172, ToInt_EmptyString_ReturnsFalse_172) {

    const char* str = "";

    EXPECT_FALSE(tinyxml2::XMLUtil::ToInt(str, &value));

}



TEST_F(XMLUtilTest_172, ToInt_NonNumericString_ReturnsFalse_172) {

    const char* str = "abc";

    EXPECT_FALSE(tinyxml2::XMLUtil::ToInt(str, &value));

}



TEST_F(XMLUtilTest_172, ToInt_StringWithLeadingSpaces_ReturnsTrueAndCorrectValue_172) {

    const char* str = "  456";

    EXPECT_TRUE(tinyxml2::XMLUtil::ToInt(str, &value));

    EXPECT_EQ(value, 456);

}



TEST_F(XMLUtilTest_172, ToInt_StringWithTrailingSpaces_ReturnsTrueAndCorrectValue_172) {

    const char* str = "789   ";

    EXPECT_TRUE(tinyxml2::XMLUtil::ToInt(str, &value));

    EXPECT_EQ(value, 789);

}



TEST_F(XMLUtilTest_172, ToInt_StringWithSpaces_ReturnsFalse_172) {

    const char* str = "10 11";

    EXPECT_FALSE(tinyxml2::XMLUtil::ToInt(str, &value));

}



TEST_F(XMLUtilTest_172, ToInt_StringWithNegativeDecimal_ReturnsTrueAndCorrectValue_172) {

    const char* str = "-123";

    EXPECT_TRUE(tinyxml2::XMLUtil::ToInt(str, &value));

    EXPECT_EQ(value, -123);

}



TEST_F(XMLUtilTest_172, ToInt_StringWithNegativeHex_ReturnsFalse_172) {

    const char* str = "-0x1A";

    EXPECT_FALSE(tinyxml2::XMLUtil::ToInt(str, &value));

}
