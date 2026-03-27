#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest : public ::testing::Test {

protected:

    unsigned result;

};



TEST_F(XMLUtilTest_173, ToUnsigned_ValidDecimalString_ReturnsTrue_173) {

    EXPECT_TRUE(XMLUtil::ToUnsigned("42", &result));

    EXPECT_EQ(result, 42u);

}



TEST_F(XMLUtilTest_173, ToUnsigned_ValidHexString_ReturnsTrue_173) {

    EXPECT_TRUE(XMLUtil::ToUnsigned("0x2A", &result));

    EXPECT_EQ(result, 42u);

}



TEST_F(XMLUtilTest_173, ToUnsigned_ZeroString_ReturnsTrue_173) {

    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &result));

    EXPECT_EQ(result, 0u);

}



TEST_F(XMLUtilTest_173, ToUnsigned_MaxUnsignedInt_ReturnsTrue_173) {

    EXPECT_TRUE(XMLUtil::ToUnsigned("4294967295", &result));

    EXPECT_EQ(result, UINT_MAX);

}



TEST_F(XMLUtilTest_173, ToUnsigned_NegativeString_ReturnsFalse_173) {

    EXPECT_FALSE(XMLUtil::ToUnsigned("-1", &result));

}



TEST_F(XMLUtilTest_173, ToUnsigned_EmptyString_ReturnsFalse_173) {

    EXPECT_FALSE(XMLUtil::ToUnsigned("", &result));

}



TEST_F(XMLUtilTest_173, ToUnsigned_NonNumericString_ReturnsFalse_173) {

    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &result));

}



TEST_F(XMLUtilTest_173, ToUnsigned_StringWithLeadingSpaces_ReturnsTrue_173) {

    EXPECT_TRUE(XMLUtil::ToUnsigned(" 42", &result));

    EXPECT_EQ(result, 42u);

}



TEST_F(XMLUtilTest_173, ToUnsigned_StringWithTrailingSpaces_ReturnsFalse_173) {

    EXPECT_FALSE(XMLUtil::ToUnsigned("42 ", &result));

}



TEST_F(XMLUtilTest_173, ToUnsigned_StringWithInternalSpaces_ReturnsFalse_173) {

    EXPECT_FALSE(XMLUtil::ToUnsigned("4 2", &result));

}
