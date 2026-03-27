#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_210, ValueReturnsNullByDefault_210) {

    EXPECT_STREQ(attr.Value(), nullptr);

}



TEST_F(XMLAttributeTest_210, SetAttributeWithStringChangesValue_210) {

    const char* testValue = "test_value";

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), testValue);

}



TEST_F(XMLAttributeTest_210, SetAttributeWithIntChangesValue_210) {

    int intValue = 42;

    attr.SetAttribute(intValue);

    EXPECT_EQ(std::stoi(attr.Value()), intValue);

}



TEST_F(XMLAttributeTest_210, SetAttributeWithUnsignedIntChangesValue_210) {

    unsigned int uintValue = 100u;

    attr.SetAttribute(uintValue);

    EXPECT_EQ(std::stoul(attr.Value()), uintValue);

}



TEST_F(XMLAttributeTest_210, SetAttributeWithInt64ChangesValue_210) {

    int64_t int64Value = 9223372036854775807LL;

    attr.SetAttribute(int64Value);

    EXPECT_EQ(std::stoll(attr.Value()), int64Value);

}



TEST_F(XMLAttributeTest_210, SetAttributeWithUnsigned64ChangesValue_210) {

    uint64_t uint64Value = 18446744073709551615ULL;

    attr.SetAttribute(uint64Value);

    EXPECT_EQ(std::stoull(attr.Value()), uint64Value);

}



TEST_F(XMLAttributeTest_210, SetAttributeWithBoolChangesValue_210) {

    bool boolValue = true;

    attr.SetAttribute(boolValue);

    EXPECT_STREQ(attr.Value(), "true");

    

    boolValue = false;

    attr.SetAttribute(boolValue);

    EXPECT_STREQ(attr.Value(), "false");

}



TEST_F(XMLAttributeTest_210, SetAttributeWithDoubleChangesValue_210) {

    double doubleValue = 3.14159;

    attr.SetAttribute(doubleValue);

    EXPECT_DOUBLE_EQ(std::stod(attr.Value()), doubleValue);

}



TEST_F(XMLAttributeTest_210, SetAttributeWithFloatChangesValue_210) {

    float floatValue = 3.14f;

    attr.SetAttribute(floatValue);

    EXPECT_FLOAT_EQ(std::stof(attr.Value()), floatValue);

}



TEST_F(XMLAttributeTest_210, QueryIntValueReturnsSuccessForValidInt_210) {

    int expectedValue = 42;

    attr.SetAttribute(expectedValue);

    int actualValue = 0;

    XMLError result = attr.QueryIntValue(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(actualValue, expectedValue);

}



TEST_F(XMLAttributeTest_210, QueryUnsignedValueReturnsSuccessForValidUnsigned_210) {

    unsigned int expectedValue = 100u;

    attr.SetAttribute(expectedValue);

    unsigned int actualValue = 0;

    XMLError result = attr.QueryUnsignedValue(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(actualValue, expectedValue);

}



TEST_F(XMLAttributeTest_210, QueryInt64ValueReturnsSuccessForValidInt64_210) {

    int64_t expectedValue = 9223372036854775807LL;

    attr.SetAttribute(expectedValue);

    int64_t actualValue = 0;

    XMLError result = attr.QueryInt64Value(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(actualValue, expectedValue);

}



TEST_F(XMLAttributeTest_210, QueryUnsigned64ValueReturnsSuccessForValidUnsigned64_210) {

    uint64_t expectedValue = 18446744073709551615ULL;

    attr.SetAttribute(expectedValue);

    uint64_t actualValue = 0;

    XMLError result = attr.QueryUnsigned64Value(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(actualValue, expectedValue);

}



TEST_F(XMLAttributeTest_210, QueryBoolValueReturnsSuccessForValidBool_210) {

    bool expectedValue = true;

    attr.SetAttribute(expectedValue);

    bool actualValue = false;

    XMLError result = attr.QueryBoolValue(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(actualValue, expectedValue);



    expectedValue = false;

    attr.SetAttribute(expectedValue);

    result = attr.QueryBoolValue(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(actualValue, expectedValue);

}



TEST_F(XMLAttributeTest_210, QueryDoubleValueReturnsSuccessForValidDouble_210) {

    double expectedValue = 3.14159;

    attr.SetAttribute(expectedValue);

    double actualValue = 0.0;

    XMLError result = attr.QueryDoubleValue(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(actualValue, expectedValue);

}



TEST_F(XMLAttributeTest_210, QueryFloatValueReturnsSuccessForValidFloat_210) {

    float expectedValue = 3.14f;

    attr.SetAttribute(expectedValue);

    float actualValue = 0.0f;

    XMLError result = attr.QueryFloatValue(&actualValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_FLOAT_EQ(actualValue, expectedValue);

}



TEST_F(XMLAttributeTest_210, QueryIntValueReturnsErrorForInvalidInput_210) {

    const char* invalidValue = "not_an_int";

    attr.SetAttribute(invalidValue);

    int actualValue = 0;

    XMLError result = attr.QueryIntValue(&actualValue);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_210, QueryUnsignedValueReturnsErrorForInvalidInput_210) {

    const char* invalidValue = "not_an_unsigned";

    attr.SetAttribute(invalidValue);

    unsigned int actualValue = 0;

    XMLError result = attr.QueryUnsignedValue(&actualValue);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_210, QueryInt64ValueReturnsErrorForInvalidInput_210) {

    const char* invalidValue = "not_an_int64";

    attr.SetAttribute(invalidValue);

    int64_t actualValue = 0;

    XMLError result = attr.QueryInt64Value(&actualValue);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_210, QueryUnsigned64ValueReturnsErrorForInvalidInput_210) {

    const char* invalidValue = "not_an_unsigned64";

    attr.SetAttribute(invalidValue);

    uint64_t actualValue = 0;

    XMLError result = attr.QueryUnsigned64Value(&actualValue);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_210, QueryBoolValueReturnsErrorForInvalidInput_210) {

    const char* invalidValue = "not_a_bool";

    attr.SetAttribute(invalidValue);

    bool actualValue = false;

    XMLError result = attr.QueryBoolValue(&actualValue);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_210, QueryDoubleValueReturnsErrorForInvalidInput_210) {

    const char* invalidValue = "not_a_double";

    attr.SetAttribute(invalidValue);

    double actualValue = 0.0;

    XMLError result = attr.QueryDoubleValue(&actualValue);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_210, QueryFloatValueReturnsErrorForInvalidInput_210) {

    const char* invalidValue = "not_a_float";

    attr.SetAttribute(invalidValue);

    float actualValue = 0.0f;

    XMLError result = attr.QueryFloatValue(&actualValue);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
