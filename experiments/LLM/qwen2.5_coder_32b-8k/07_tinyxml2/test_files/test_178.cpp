#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_178 : public ::testing::Test {

protected:

    XMLUtil xmlUtil;

};



TEST_F(XMLUtilTest_178, ToUnsigned64_HexStringValid_178) {

    uint64_t value;

    EXPECT_TRUE(xmlUtil.ToUnsigned64("0xffffffffffffffff", &value));

    EXPECT_EQ(value, 18446744073709551615ull);

}



TEST_F(XMLUtilTest_178, ToUnsigned64_DecimalStringValid_178) {

    uint64_t value;

    EXPECT_TRUE(xmlUtil.ToUnsigned64("123456789", &value));

    EXPECT_EQ(value, 123456789ull);

}



TEST_F(XMLUtilTest_178, ToUnsigned64_StringInvalid_178) {

    uint64_t value;

    EXPECT_FALSE(xmlUtil.ToUnsigned64("invalid", &value));

}



TEST_F(XMLUtilTest_178, ToUnsigned64_StringEmpty_178) {

    uint64_t value;

    EXPECT_FALSE(xmlUtil.ToUnsigned64("", &value));

}



TEST_F(XMLUtilTest_178, ToUnsigned64_StringTooLarge_178) {

    uint64_t value;

    EXPECT_FALSE(xmlUtil.ToUnsigned64("18446744073709551616", &value));

}



TEST_F(XMLUtilTest_178, ToUnsigned64_StringHexTooLarge_178) {

    uint64_t value;

    EXPECT_FALSE(xmlUtil.ToUnsigned64("0x10000000000000000", &value));

}



TEST_F(XMLUtilTest_178, ToUnsigned64_StringNegative_178) {

    uint64_t value;

    EXPECT_FALSE(xmlUtil.ToUnsigned64("-123", &value));

}



TEST_F(XMLUtilTest_178, ToUnsigned64_NullPointer_178) {

    uint64_t* nullValue = nullptr;

    EXPECT_FALSE(xmlUtil.ToUnsigned64("123", nullValue));

}
