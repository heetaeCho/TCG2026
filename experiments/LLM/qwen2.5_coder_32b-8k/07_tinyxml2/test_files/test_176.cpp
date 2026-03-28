#include <gtest/gtest.h>

#include "tinyxml2.h"



namespace tinyxml2 {



class XMLUtilTest : public ::testing::Test {

protected:

    double value;

};



TEST_F(XMLUtilTest_176, ToDouble_ValidString_ReturnsTrue_176) {

    const char* str = "123.45";

    EXPECT_TRUE(XMLUtil::ToDouble(str, &value));

    EXPECT_DOUBLE_EQ(123.45, value);

}



TEST_F(XMLUtilTest_176, ToDouble_InvalidString_ReturnsFalse_176) {

    const char* str = "abc";

    EXPECT_FALSE(XMLUtil::ToDouble(str, &value));

}



TEST_F(XMLUtilTest_176, ToDouble_EmptyString_ReturnsFalse_176) {

    const char* str = "";

    EXPECT_FALSE(XMLUtil::ToDouble(str, &value));

}



TEST_F(XMLUtilTest_176, ToDouble_StringWithSpaces_ReturnsTrue_176) {

    const char* str = "  123.45  ";

    EXPECT_TRUE(XMLUtil::ToDouble(str, &value));

    EXPECT_DOUBLE_EQ(123.45, value);

}



TEST_F(XMLUtilTest_176, ToDouble_StringWithLeadingPlus_ReturnsTrue_176) {

    const char* str = "+123.45";

    EXPECT_TRUE(XMLUtil::ToDouble(str, &value));

    EXPECT_DOUBLE_EQ(123.45, value);

}



TEST_F(XMLUtilTest_176, ToDouble_StringWithTrailingPlus_ReturnsFalse_176) {

    const char* str = "123.45+";

    EXPECT_FALSE(XMLUtil::ToDouble(str, &value));

}



TEST_F(XMLUtilTest_176, ToDouble_StringWithLeadingMinus_ReturnsTrue_176) {

    const char* str = "-123.45";

    EXPECT_TRUE(XMLUtil::ToDouble(str, &value));

    EXPECT_DOUBLE_EQ(-123.45, value);

}



TEST_F(XMLUtilTest_176, ToDouble_StringWithTrailingMinus_ReturnsFalse_176) {

    const char* str = "123.45-";

    EXPECT_FALSE(XMLUtil::ToDouble(str, &value));

}



TEST_F(XMLUtilTest_176, ToDouble_StringWithExponent_ReturnsTrue_176) {

    const char* str = "1.23e+02";

    EXPECT_TRUE(XMLUtil::ToDouble(str, &value));

    EXPECT_DOUBLE_EQ(123.0, value);

}



TEST_F(XMLUtilTest_176, ToDouble_StringWithInvalidExponent_ReturnsFalse_176) {

    const char* str = "1.23e+abc";

    EXPECT_FALSE(XMLUtil::ToDouble(str, &value));

}



}  // namespace tinyxml2
