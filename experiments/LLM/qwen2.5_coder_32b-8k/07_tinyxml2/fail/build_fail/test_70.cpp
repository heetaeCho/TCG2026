#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_70 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_70, NextReturnsNullptrInitially_70) {

    EXPECT_EQ(attr.Next(), nullptr);

}



TEST_F(XMLAttributeTest_70, NameReturnsEmptyStringByDefault_70) {

    EXPECT_STREQ(attr.Name(), "");

}



TEST_F(XMLAttributeTest_70, ValueReturnsEmptyStringByDefault_70) {

    EXPECT_STREQ(attr.Value(), "");

}



TEST_F(XMLAttributeTest_70, GetLineNumReturnsZeroByDefault_70) {

    EXPECT_EQ(attr.GetLineNum(), 0);

}



TEST_F(XMLAttributeTest_70, QueryIntValueWithNullptr_70) {

    int value;

    EXPECT_NE(attr.QueryIntValue(nullptr), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_70, QueryUnsignedValueWithNullptr_70) {

    unsigned int value;

    EXPECT_NE(attr.QueryUnsignedValue(nullptr), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_70, QueryInt64ValueWithNullptr_70) {

    int64_t value;

    EXPECT_NE(attr.QueryInt64Value(nullptr), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_70, QueryUnsigned64ValueWithNullptr_70) {

    uint64_t value;

    EXPECT_NE(attr.QueryUnsigned64Value(nullptr), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_70, QueryBoolValueWithNullptr_70) {

    bool value;

    EXPECT_NE(attr.QueryBoolValue(nullptr), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_70, QueryFloatValueWithNullptr_70) {

    float value;

    EXPECT_NE(attr.QueryFloatValue(nullptr), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_70, QueryDoubleValueWithNullptr_70) {

    double value;

    EXPECT_NE(attr.QueryDoubleValue(nullptr), XML_SUCCESS);

}



TEST_F(XMLAttributeTest_70, SetAttributeWithString_70) {

    attr.SetAttribute("test");

    EXPECT_STREQ(attr.Value(), "test");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithInt_70) {

    attr.SetAttribute(123);

    EXPECT_STREQ(attr.Value(), "123");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithUnsigned_70) {

    attr.SetAttribute(static_cast<unsigned>(123));

    EXPECT_STREQ(attr.Value(), "123");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithInt64_70) {

    attr.SetAttribute(static_cast<int64_t>(123456789012345LL));

    EXPECT_STREQ(attr.Value(), "123456789012345");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithUnsigned64_70) {

    attr.SetAttribute(static_cast<uint64_t>(123456789012345ULL));

    EXPECT_STREQ(attr.Value(), "123456789012345");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithBoolTrue_70) {

    attr.SetAttribute(true);

    EXPECT_STREQ(attr.Value(), "true");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithBoolFalse_70) {

    attr.SetAttribute(false);

    EXPECT_STREQ(attr.Value(), "false");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithDouble_70) {

    attr.SetAttribute(123.456);

    EXPECT_STREQ(attr.Value(), "123.456");

}



TEST_F(XMLAttributeTest_70, SetAttributeWithFloat_70) {

    attr.SetAttribute(static_cast<float>(123.456));

    EXPECT_STREQ(attr.Value(), "123.456");

}



TEST_F(XMLAttributeTest_70, IntValueReturnsZeroByDefault_70) {

    EXPECT_EQ(attr.IntValue(), 0);

}



TEST_F(XMLAttributeTest_70, Int64ValueReturnsZeroByDefault_70) {

    EXPECT_EQ(attr.Int64Value(), 0);

}



TEST_F(XMLAttributeTest_70, UnsignedValueReturnsZeroByDefault_70) {

    EXPECT_EQ(attr.UnsignedValue(), 0U);

}



TEST_F(XMLAttributeTest_70, Unsigned64ValueReturnsZeroByDefault_70) {

    EXPECT_EQ(attr.Unsigned64Value(), 0ULL);

}



TEST_F(XMLAttributeTest_70, BoolValueReturnsFalseByDefault_70) {

    EXPECT_FALSE(attr.BoolValue());

}



TEST_F(XMLAttributeTest_70, DoubleValueReturnsZeroByDefault_70) {

    EXPECT_DOUBLE_EQ(attr.DoubleValue(), 0.0);

}



TEST_F(XMLAttributeTest_70, FloatValueReturnsZeroByDefault_70) {

    EXPECT_FLOAT_EQ(attr.FloatValue(), 0.0f);

}
