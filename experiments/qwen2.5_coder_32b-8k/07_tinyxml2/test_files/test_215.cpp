#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_215, QueryBoolValue_ValidTrue_215) {

    bool value = false;

    EXPECT_EQ(attr.QueryBoolValue(&value), XML_SUCCESS);

    EXPECT_TRUE(value);

}



TEST_F(XMLAttributeTest_215, QueryBoolValue_ValidFalse_215) {

    attr.SetValue("false");

    bool value = true;

    EXPECT_EQ(attr.QueryBoolValue(&value), XML_SUCCESS);

    EXPECT_FALSE(value);

}



TEST_F(XMLAttributeTest_215, QueryBoolValue_InvalidString_215) {

    attr.SetValue("invalid");

    bool value = false;

    EXPECT_EQ(attr.QueryBoolValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_215, QueryBoolValue_EmptyString_215) {

    attr.SetValue("");

    bool value = true;

    EXPECT_EQ(attr.QueryBoolValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_215, QueryBoolValue_ZeroString_215) {

    attr.SetValue("0");

    bool value = true;

    EXPECT_EQ(attr.QueryBoolValue(&value), XML_SUCCESS);

    EXPECT_FALSE(value);

}



TEST_F(XMLAttributeTest_215, QueryBoolValue_OneString_215) {

    attr.SetValue("1");

    bool value = false;

    EXPECT_EQ(attr.QueryBoolValue(&value), XML_SUCCESS);

    EXPECT_TRUE(value);

}
