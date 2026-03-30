#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_174 : public ::testing::Test {

protected:

    bool result;

    bool value;

};



TEST_F(XMLUtilTest_174, ToBool_ValidTrueString_ReturnsTrueAndSetsValueToTrue_174) {

    const char* str = "true";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_TRUE(value);

}



TEST_F(XMLUtilTest_174, ToBool_ValidFalseString_ReturnsTrueAndSetsValueToFalse_174) {

    const char* str = "false";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_FALSE(value);

}



TEST_F(XMLUtilTest_174, ToBool_CaseInsensitiveTrue_ReturnsTrueAndSetsValueToTrue_174) {

    const char* str = "TRUE";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_TRUE(value);



    str = "True";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_TRUE(value);

}



TEST_F(XMLUtilTest_174, ToBool_CaseInsensitiveFalse_ReturnsTrueAndSetsValueToFalse_174) {

    const char* str = "FALSE";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_FALSE(value);



    str = "False";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_FALSE(value);

}



TEST_F(XMLUtilTest_174, ToBool_ValidNumericZero_ReturnsTrueAndSetsValueToFalse_174) {

    const char* str = "0";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_FALSE(value);

}



TEST_F(XMLUtilTest_174, ToBool_ValidNonzeroInteger_ReturnsTrueAndSetsValueToTrue_174) {

    const char* str = "123";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_TRUE(result);

    EXPECT_TRUE(value);

}



TEST_F(XMLUtilTest_174, ToBool_InvalidString_ReturnsFalseAndDoesNotModifyValue_174) {

    bool initialValue = value;

    const char* str = "invalid";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_FALSE(result);

    EXPECT_EQ(value, initialValue); // Ensure value is not modified

}



TEST_F(XMLUtilTest_174, ToBool_EmptyString_ReturnsFalseAndDoesNotModifyValue_174) {

    bool initialValue = value;

    const char* str = "";

    result = XMLUtil::ToBool(str, &value);

    EXPECT_FALSE(result);

    EXPECT_EQ(value, initialValue); // Ensure value is not modified

}



TEST_F(XMLUtilTest_174, ToBool_NullString_ReturnsFalseAndDoesNotModifyValue_174) {

    bool initialValue = value;

    const char* str = nullptr;

    result = XMLUtil::ToBool(str, &value);

    EXPECT_FALSE(result);

    EXPECT_EQ(value, initialValue); // Ensure value is not modified

}
