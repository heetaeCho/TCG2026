#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLAttributeTest_69 : public ::testing::Test {

protected:

    XMLAttribute* attr;



    void SetUp() override {

        attr = new XMLAttribute();

    }



    void TearDown() override {

        delete attr;

    }

};



TEST_F(XMLAttributeTest_69, GetLineNum_DefaultValue_69) {

    EXPECT_EQ(attr->GetLineNum(), 0);

}



TEST_F(XMLAttributeTest_69, Name_ReturnsEmptyStringByDefault_69) {

    EXPECT_STREQ(attr->Name(), "");

}



TEST_F(XMLAttributeTest_69, Value_ReturnsEmptyStringByDefault_69) {

    EXPECT_STREQ(attr->Value(), "");

}



TEST_F(XMLAttributeTest_69, Next_ReturnsNullptrByDefault_69) {

    EXPECT_EQ(attr->Next(), nullptr);

}



TEST_F(XMLAttributeTest_69, IntValue_DefaultValueIsZero_69) {

    EXPECT_EQ(attr->IntValue(), 0);

}



TEST_F(XMLAttributeTest_69, Int64Value_DefaultValueIsZero_69) {

    EXPECT_EQ(attr->Int64Value(), 0);

}



TEST_F(XMLAttributeTest_69, UnsignedValue_DefaultValueIsZero_69) {

    EXPECT_EQ(attr->UnsignedValue(), 0u);

}



TEST_F(XMLAttributeTest_69, Unsigned64Value_DefaultValueIsZero_69) {

    EXPECT_EQ(attr->Unsigned64Value(), 0ull);

}



TEST_F(XMLAttributeTest_69, BoolValue_DefaultValueIsFalse_69) {

    EXPECT_FALSE(attr->BoolValue());

}



TEST_F(XMLAttributeTest_69, DoubleValue_DefaultValueIsZero_69) {

    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 0.0);

}



TEST_F(XMLAttributeTest_69, FloatValue_DefaultValueIsZero_69) {

    EXPECT_FLOAT_EQ(attr->FloatValue(), 0.0f);

}



TEST_F(XMLAttributeTest_69, QueryIntValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_ForEmptyString_69) {

    int value;

    XMLError result = attr->QueryIntValue(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_69, QueryUnsignedValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_ForEmptyString_69) {

    unsigned value;

    XMLError result = attr->QueryUnsignedValue(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_69, QueryInt64Value_ReturnsXML_WRONG_ATTRIBUTE_TYPE_ForEmptyString_69) {

    int64_t value;

    XMLError result = attr->QueryInt64Value(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_69, QueryUnsigned64Value_ReturnsXML_WRONG_ATTRIBUTE_TYPE_ForEmptyString_69) {

    uint64_t value;

    XMLError result = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_69, QueryBoolValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_ForEmptyString_69) {

    bool value;

    XMLError result = attr->QueryBoolValue(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_69, QueryDoubleValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_ForEmptyString_69) {

    double value;

    XMLError result = attr->QueryDoubleValue(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_69, QueryFloatValue_ReturnsXML_WRONG_ATTRIBUTE_TYPE_ForEmptyString_69) {

    float value;

    XMLError result = attr->QueryFloatValue(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
