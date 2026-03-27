#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_71 : public ::testing::Test {

protected:

    void SetUp() override {

        xmlAttribute = new XMLAttribute();

    }



    void TearDown() override {

        delete xmlAttribute;

    }



    XMLAttribute* xmlAttribute;

};



TEST_F(XMLAttributeTest_71, IntValue_ReturnsZeroWhenUninitialized_71) {

    EXPECT_EQ(xmlAttribute->IntValue(), 0);

}



TEST_F(XMLAttributeTest_71, QueryIntValue_ReturnsXML_SUCCESS_ForValidIntegerString_71) {

    xmlAttribute->SetAttribute("123");

    int value = 0;

    EXPECT_EQ(xmlAttribute->QueryIntValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, 123);

}



TEST_F(XMLAttributeTest_71, QueryIntValue_ReturnsXML_ERROR_PARSING_TEXT_ForInvalidIntegerString_71) {

    xmlAttribute->SetAttribute("invalid");

    int value = 0;

    EXPECT_EQ(xmlAttribute->QueryIntValue(&value), XML_ERROR_PARSING_TEXT);

}



TEST_F(XMLAttributeTest_71, QueryUnsignedValue_ReturnsXML_SUCCESS_ForValidUnsignedIntegerString_71) {

    xmlAttribute->SetAttribute("456");

    unsigned int value = 0;

    EXPECT_EQ(xmlAttribute->QueryUnsignedValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, 456u);

}



TEST_F(XMLAttributeTest_71, QueryUnsignedValue_ReturnsXML_ERROR_PARSING_TEXT_ForNegativeIntegerString_71) {

    xmlAttribute->SetAttribute("-123");

    unsigned int value = 0;

    EXPECT_EQ(xmlAttribute->QueryUnsignedValue(&value), XML_ERROR_PARSING_TEXT);

}



TEST_F(XMLAttributeTest_71, QueryInt64Value_ReturnsXML_SUCCESS_ForValidInt64String_71) {

    xmlAttribute->SetAttribute("9223372036854775807");

    int64_t value = 0;

    EXPECT_EQ(xmlAttribute->QueryInt64Value(&value), XML_SUCCESS);

    EXPECT_EQ(value, 9223372036854775807ll);

}



TEST_F(XMLAttributeTest_71, QueryUnsigned64Value_ReturnsXML_SUCCESS_ForValidUInt64String_71) {

    xmlAttribute->SetAttribute("18446744073709551615");

    uint64_t value = 0;

    EXPECT_EQ(xmlAttribute->QueryUnsigned64Value(&value), XML_SUCCESS);

    EXPECT_EQ(value, 18446744073709551615ull);

}



TEST_F(XMLAttributeTest_71, QueryBoolValue_ReturnsXML_SUCCESS_ForTrueString_71) {

    xmlAttribute->SetAttribute("true");

    bool value = false;

    EXPECT_EQ(xmlAttribute->QueryBoolValue(&value), XML_SUCCESS);

    EXPECT_TRUE(value);

}



TEST_F(XMLAttributeTest_71, QueryFloatValue_ReturnsXML_SUCCESS_ForValidFloatString_71) {

    xmlAttribute->SetAttribute("3.14");

    float value = 0.0f;

    EXPECT_EQ(xmlAttribute->QueryFloatValue(&value), XML_SUCCESS);

    EXPECT_FLOAT_EQ(value, 3.14f);

}



TEST_F(XMLAttributeTest_71, QueryDoubleValue_ReturnsXML_SUCCESS_ForValidDoubleString_71) {

    xmlAttribute->SetAttribute("2.718");

    double value = 0.0;

    EXPECT_EQ(xmlAttribute->QueryDoubleValue(&value), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 2.718);

}



TEST_F(XMLAttributeTest_71, SetAttribute_String_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute("testValue");

    EXPECT_STREQ(xmlAttribute->Value(), "testValue");

}



TEST_F(XMLAttributeTest_71, SetAttribute_Integer_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute(42);

    EXPECT_EQ(xmlAttribute->IntValue(), 42);

}



TEST_F(XMLAttributeTest_71, SetAttribute_UnsignedInteger_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute(987u);

    unsigned int value = 0;

    EXPECT_EQ(xmlAttribute->QueryUnsignedValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, 987u);

}



TEST_F(XMLAttributeTest_71, SetAttribute_Int64_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute(9223372036854775807ll);

    int64_t value = 0;

    EXPECT_EQ(xmlAttribute->QueryInt64Value(&value), XML_SUCCESS);

    EXPECT_EQ(value, 9223372036854775807ll);

}



TEST_F(XMLAttributeTest_71, SetAttribute_UnsignedInt64_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute(18446744073709551615ull);

    uint64_t value = 0;

    EXPECT_EQ(xmlAttribute->QueryUnsigned64Value(&value), XML_SUCCESS);

    EXPECT_EQ(value, 18446744073709551615ull);

}



TEST_F(XMLAttributeTest_71, SetAttribute_Bool_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute(true);

    bool value = false;

    EXPECT_EQ(xmlAttribute->QueryBoolValue(&value), XML_SUCCESS);

    EXPECT_TRUE(value);

}



TEST_F(XMLAttributeTest_71, SetAttribute_Float_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute(3.14f);

    float value = 0.0f;

    EXPECT_EQ(xmlAttribute->QueryFloatValue(&value), XML_SUCCESS);

    EXPECT_FLOAT_EQ(value, 3.14f);

}



TEST_F(XMLAttributeTest_71, SetAttribute_Double_SetsCorrectValue_71) {

    xmlAttribute->SetAttribute(2.718);

    double value = 0.0;

    EXPECT_EQ(xmlAttribute->QueryDoubleValue(&value), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 2.718);

}



TEST_F(XMLAttributeTest_71, GetLineNum_ReturnsZeroByDefault_71) {

    EXPECT_EQ(xmlAttribute->GetLineNum(), 0);

}
