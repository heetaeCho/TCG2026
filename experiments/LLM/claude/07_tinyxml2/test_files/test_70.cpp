#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper class to create XML documents with attributes for testing
class XMLAttributeTest_70 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that Name() returns the correct attribute name
TEST_F(XMLAttributeTest_70, NameReturnsAttributeName_70) {
    doc.Parse("<root attr1=\"value1\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr1");
}

// Test that Value() returns the correct attribute value
TEST_F(XMLAttributeTest_70, ValueReturnsAttributeValue_70) {
    doc.Parse("<root attr1=\"hello\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");
}

// Test Next() returns nullptr when there is only one attribute
TEST_F(XMLAttributeTest_70, NextReturnsNullWhenSingleAttribute_70) {
    doc.Parse("<root attr1=\"value1\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Next(), nullptr);
}

// Test Next() returns the next attribute when multiple attributes exist
TEST_F(XMLAttributeTest_70, NextReturnsNextAttribute_70) {
    doc.Parse("<root attr1=\"value1\" attr2=\"value2\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr1");
    
    const XMLAttribute* nextAttr = attr->Next();
    ASSERT_NE(nextAttr, nullptr);
    EXPECT_STREQ(nextAttr->Name(), "attr2");
}

// Test Next() chain terminates correctly with three attributes
TEST_F(XMLAttributeTest_70, NextChainTerminatesCorrectly_70) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
    
    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "b");
    
    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "c");
    
    attr = attr->Next();
    EXPECT_EQ(attr, nullptr);
}

// Test IntValue() returns correct integer value
TEST_F(XMLAttributeTest_70, IntValueReturnsCorrectValue_70) {
    doc.Parse("<root num=\"42\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test IntValue() with negative number
TEST_F(XMLAttributeTest_70, IntValueNegative_70) {
    doc.Parse("<root num=\"-100\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -100);
}

// Test UnsignedValue() returns correct value
TEST_F(XMLAttributeTest_70, UnsignedValueReturnsCorrectValue_70) {
    doc.Parse("<root num=\"123\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 123u);
}

// Test Int64Value() returns correct value
TEST_F(XMLAttributeTest_70, Int64ValueReturnsCorrectValue_70) {
    doc.Parse("<root num=\"9223372036854775807\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MAX);
}

// Test Unsigned64Value() returns correct value
TEST_F(XMLAttributeTest_70, Unsigned64ValueReturnsCorrectValue_70) {
    doc.Parse("<root num=\"18446744073709551615\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_MAX);
}

// Test BoolValue() returns true
TEST_F(XMLAttributeTest_70, BoolValueTrue_70) {
    doc.Parse("<root flag=\"true\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test BoolValue() returns false
TEST_F(XMLAttributeTest_70, BoolValueFalse_70) {
    doc.Parse("<root flag=\"false\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

// Test DoubleValue() returns correct value
TEST_F(XMLAttributeTest_70, DoubleValueReturnsCorrectValue_70) {
    doc.Parse("<root val=\"3.14159\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test FloatValue() returns correct value
TEST_F(XMLAttributeTest_70, FloatValueReturnsCorrectValue_70) {
    doc.Parse("<root val=\"2.5\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// Test QueryIntValue with valid integer
TEST_F(XMLAttributeTest_70, QueryIntValueSuccess_70) {
    doc.Parse("<root num=\"42\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    int value = 0;
    EXPECT_EQ(attr->QueryIntValue(&value), XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

// Test QueryIntValue with non-integer value
TEST_F(XMLAttributeTest_70, QueryIntValueFailure_70) {
    doc.Parse("<root num=\"notanumber\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    int value = 0;
    EXPECT_NE(attr->QueryIntValue(&value), XML_SUCCESS);
}

// Test QueryUnsignedValue with valid unsigned integer
TEST_F(XMLAttributeTest_70, QueryUnsignedValueSuccess_70) {
    doc.Parse("<root num=\"100\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    unsigned int value = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&value), XML_SUCCESS);
    EXPECT_EQ(value, 100u);
}

// Test QueryUnsignedValue with non-numeric value
TEST_F(XMLAttributeTest_70, QueryUnsignedValueFailure_70) {
    doc.Parse("<root num=\"abc\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    unsigned int value = 0;
    EXPECT_NE(attr->QueryUnsignedValue(&value), XML_SUCCESS);
}

// Test QueryInt64Value with valid int64 value
TEST_F(XMLAttributeTest_70, QueryInt64ValueSuccess_70) {
    doc.Parse("<root num=\"9223372036854775807\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    int64_t value = 0;
    EXPECT_EQ(attr->QueryInt64Value(&value), XML_SUCCESS);
    EXPECT_EQ(value, INT64_MAX);
}

// Test QueryUnsigned64Value with valid uint64 value
TEST_F(XMLAttributeTest_70, QueryUnsigned64ValueSuccess_70) {
    doc.Parse("<root num=\"18446744073709551615\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    EXPECT_EQ(attr->QueryUnsigned64Value(&value), XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

// Test QueryBoolValue with valid bool
TEST_F(XMLAttributeTest_70, QueryBoolValueSuccess_70) {
    doc.Parse("<root flag=\"true\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    bool value = false;
    EXPECT_EQ(attr->QueryBoolValue(&value), XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test QueryBoolValue with non-bool value
TEST_F(XMLAttributeTest_70, QueryBoolValueFailure_70) {
    doc.Parse("<root flag=\"maybe\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    bool value = false;
    EXPECT_NE(attr->QueryBoolValue(&value), XML_SUCCESS);
}

// Test QueryDoubleValue with valid double
TEST_F(XMLAttributeTest_70, QueryDoubleValueSuccess_70) {
    doc.Parse("<root val=\"3.14\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    double value = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&value), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14);
}

// Test QueryDoubleValue with non-numeric value
TEST_F(XMLAttributeTest_70, QueryDoubleValueFailure_70) {
    doc.Parse("<root val=\"notdouble\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    double value = 0.0;
    EXPECT_NE(attr->QueryDoubleValue(&value), XML_SUCCESS);
}

// Test QueryFloatValue with valid float
TEST_F(XMLAttributeTest_70, QueryFloatValueSuccess_70) {
    doc.Parse("<root val=\"1.5\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    EXPECT_EQ(attr->QueryFloatValue(&value), XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.5f);
}

// Test QueryFloatValue with non-numeric value
TEST_F(XMLAttributeTest_70, QueryFloatValueFailure_70) {
    doc.Parse("<root val=\"notfloat\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    EXPECT_NE(attr->QueryFloatValue(&value), XML_SUCCESS);
}

// Test SetAttribute with const char*
TEST_F(XMLAttributeTest_70, SetAttributeString_70) {
    doc.Parse("<root attr=\"old\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", "new");
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "new");
}

// Test SetAttribute with int
TEST_F(XMLAttributeTest_70, SetAttributeInt_70) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 99);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 99);
}

// Test SetAttribute with unsigned int
TEST_F(XMLAttributeTest_70, SetAttributeUnsigned_70) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 200u);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 200u);
}

// Test SetAttribute with int64_t
TEST_F(XMLAttributeTest_70, SetAttributeInt64_70) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    int64_t bigVal = 9223372036854775807LL;
    elem->SetAttribute("attr", bigVal);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), bigVal);
}

// Test SetAttribute with uint64_t
TEST_F(XMLAttributeTest_70, SetAttributeUnsigned64_70) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetAttribute("attr", bigVal);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), bigVal);
}

// Test SetAttribute with bool
TEST_F(XMLAttributeTest_70, SetAttributeBool_70) {
    doc.Parse("<root attr=\"false\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test SetAttribute with double
TEST_F(XMLAttributeTest_70, SetAttributeDouble_70) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 2.718281828);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 2.718281828, 1e-6);
}

// Test SetAttribute with float
TEST_F(XMLAttributeTest_70, SetAttributeFloat_70) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 1.5f);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.5f);
}

// Test GetLineNum returns a positive line number
TEST_F(XMLAttributeTest_70, GetLineNumReturnsPositiveValue_70) {
    doc.Parse("<root attr=\"value\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_GT(attr->GetLineNum(), 0);
}

// Test empty attribute value
TEST_F(XMLAttributeTest_70, EmptyAttributeValue_70) {
    doc.Parse("<root attr=\"\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

// Test attribute with special characters in value
TEST_F(XMLAttributeTest_70, AttributeWithSpecialChars_70) {
    doc.Parse("<root attr=\"hello &amp; world\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello & world");
}

// Test IntValue() with zero
TEST_F(XMLAttributeTest_70, IntValueZero_70) {
    doc.Parse("<root num=\"0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 0);
}

// Test BoolValue with "1" as true
TEST_F(XMLAttributeTest_70, BoolValue1AsTrue_70) {
    doc.Parse("<root flag=\"1\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test BoolValue with "0" as false
TEST_F(XMLAttributeTest_70, BoolValue0AsFalse_70) {
    doc.Parse("<root flag=\"0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test multiple attributes traversal
TEST_F(XMLAttributeTest_70, MultipleAttributesTraversal_70) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\" d=\"4\" e=\"5\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    int count = 0;
    while (attr) {
        count++;
        attr = attr->Next();
    }
    EXPECT_EQ(count, 5);
}

// Test that no attributes returns nullptr from FirstAttribute
TEST_F(XMLAttributeTest_70, NoAttributesReturnsNull_70) {
    doc.Parse("<root/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// Test QueryIntValue with zero value
TEST_F(XMLAttributeTest_70, QueryIntValueZero_70) {
    doc.Parse("<root num=\"0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    int value = 999;
    EXPECT_EQ(attr->QueryIntValue(&value), XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

// Test DoubleValue with integer string
TEST_F(XMLAttributeTest_70, DoubleValueFromIntegerString_70) {
    doc.Parse("<root val=\"42\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 42.0);
}

// Test FloatValue with negative float
TEST_F(XMLAttributeTest_70, FloatValueNegative_70) {
    doc.Parse("<root val=\"-3.14\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), -3.14f);
}
