#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_209 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_209, Name_ReturnsEmptyStringByDefault_209) {

    EXPECT_STREQ(attr.Name(), "");

}



TEST_F(XMLAttributeTest_209, Value_ReturnsEmptyStringByDefault_209) {

    EXPECT_STREQ(attr.Value(), "");

}



TEST_F(XMLAttributeTest_209, QueryIntValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_209) {

    int value;

    EXPECT_EQ(attr.QueryIntValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_209, QueryUnsignedValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_209) {

    unsigned int value;

    EXPECT_EQ(attr.QueryUnsignedValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_209, QueryInt64Value_ReturnsXML_WRONG_ATTRIBUTE_TYPE_209) {

    int64_t value;

    EXPECT_EQ(attr.QueryInt64Value(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_209, QueryUnsigned64Value_ReturnsXML_WRONG_ATTRIBUTE_TYPE_209) {

    uint64_t value;

    EXPECT_EQ(attr.QueryUnsigned64Value(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_209, QueryBoolValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_209) {

    bool value;

    EXPECT_EQ(attr.QueryBoolValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_209, QueryDoubleValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_209) {

    double value;

    EXPECT_EQ(attr.QueryDoubleValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_209, QueryFloatValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_209) {

    float value;

    EXPECT_EQ(attr.QueryFloatValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_209, GetLineNum_ReturnsZeroByDefault_209) {

    EXPECT_EQ(attr.GetLineNum(), 0);

}



TEST_F(XMLAttributeTest_209, Next_ReturnsNullPointerByDefault_209) {

    EXPECT_EQ(attr.Next(), nullptr);

}



TEST_F(XMLAttributeTest_209, IntValue_ReturnsZeroByDefault_209) {

    EXPECT_EQ(attr.IntValue(), 0);

}



TEST_F(XMLAttributeTest_209, UnsignedValue_ReturnsZeroByDefault_209) {

    EXPECT_EQ(attr.UnsignedValue(), 0u);

}



TEST_F(XMLAttributeTest_209, Int64Value_ReturnsZeroByDefault_209) {

    EXPECT_EQ(attr.Int64Value(), static_cast<int64_t>(0));

}



TEST_F(XMLAttributeTest_209, Unsigned64Value_ReturnsZeroByDefault_209) {

    EXPECT_EQ(attr.Unsigned64Value(), static_cast<uint64_t>(0u));

}



TEST_F(XMLAttributeTest_209, BoolValue_ReturnsFalseByDefault_209) {

    EXPECT_FALSE(attr.BoolValue());

}



TEST_F(XMLAttributeTest_209, DoubleValue_ReturnsZeroByDefault_209) {

    EXPECT_DOUBLE_EQ(attr.DoubleValue(), 0.0);

}



TEST_F(XMLAttributeTest_209, FloatValue_ReturnsZeroByDefault_209) {

    EXPECT_FLOAT_EQ(attr.FloatValue(), 0.0f);

}
