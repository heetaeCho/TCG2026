#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_213 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_213, QueryInt64Value_ValidInteger_213) {

    int64_t value = 0;

    attr.SetAttribute("9223372036854775807"); // Maximum int64_t

    EXPECT_EQ(XML_SUCCESS, attr.QueryInt64Value(&value));

    EXPECT_EQ(9223372036854775807, value);

}



TEST_F(XMLAttributeTest_213, QueryInt64Value_MinInteger_213) {

    int64_t value = 0;

    attr.SetAttribute("-9223372036854775808"); // Minimum int64_t

    EXPECT_EQ(XML_SUCCESS, attr.QueryInt64Value(&value));

    EXPECT_EQ(-9223372036854775808, value);

}



TEST_F(XMLAttributeTest_213, QueryInt64Value_Zero_213) {

    int64_t value = 0;

    attr.SetAttribute("0");

    EXPECT_EQ(XML_SUCCESS, attr.QueryInt64Value(&value));

    EXPECT_EQ(0, value);

}



TEST_F(XMLAttributeTest_213, QueryInt64Value_NonIntegerString_213) {

    int64_t value = 0;

    attr.SetAttribute("not_an_integer");

    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, attr.QueryInt64Value(&value));

}



TEST_F(XMLAttributeTest_213, QueryInt64Value_EmptyString_213) {

    int64_t value = 0;

    attr.SetAttribute("");

    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, attr.QueryInt64Value(&value));

}
