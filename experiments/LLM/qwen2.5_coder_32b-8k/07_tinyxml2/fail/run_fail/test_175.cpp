#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_175 : public ::testing::Test {

protected:

    XMLUtil util;

};



TEST_F(XMLUtilTest_175, ToFloat_ValidInput_ReturnsTrueAndSetsValue_175) {

    float value = 0.0f;

    EXPECT_TRUE(util.ToFloat("123.45", &value));

    EXPECT_FLOAT_EQ(value, 123.45f);

}



TEST_F(XMLUtilTest_175, ToFloat_ZeroInput_ReturnsTrueAndSetsValueToZero_175) {

    float value = 0.0f;

    EXPECT_TRUE(util.ToFloat("0", &value));

    EXPECT_FLOAT_EQ(value, 0.0f);

}



TEST_F(XMLUtilTest_175, ToFloat_NegativeInput_ReturnsTrueAndSetsNegativeValue_175) {

    float value = 0.0f;

    EXPECT_TRUE(util.ToFloat("-987.65", &value));

    EXPECT_FLOAT_EQ(value, -987.65f);

}



TEST_F(XMLUtilTest_175, ToFloat_EmptyString_ReturnsFalseAndDoesNotModifyValue_175) {

    float value = 42.0f;

    EXPECT_FALSE(util.ToFloat("", &value));

    EXPECT_FLOAT_EQ(value, 42.0f);

}



TEST_F(XMLUtilTest_175, ToFloat_AlphaInput_ReturnsFalseAndDoesNotModifyValue_175) {

    float value = 42.0f;

    EXPECT_FALSE(util.ToFloat("abc", &value));

    EXPECT_FLOAT_EQ(value, 42.0f);

}



TEST_F(XMLUtilTest_175, ToFloat_MixedAlphaNumeric_ReturnsFalseAndDoesNotModifyValue_175) {

    float value = 42.0f;

    EXPECT_FALSE(util.ToFloat("a1b2c3", &value));

    EXPECT_FLOAT_EQ(value, 42.0f);

}



TEST_F(XMLUtilTest_175, ToFloat_NullPointer_ReturnsFalseAndDoesNotModifyValue_175) {

    float value = 42.0f;

    EXPECT_FALSE(util.ToFloat(nullptr, &value));

    EXPECT_FLOAT_EQ(value, 42.0f);

}



TEST_F(XMLUtilTest_175, ToFloat_ValuePointerNull_ReturnsFalse_175) {

    EXPECT_FALSE(util.ToFloat("123.45", nullptr));

}
