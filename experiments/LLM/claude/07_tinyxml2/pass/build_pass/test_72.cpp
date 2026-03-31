#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_72 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        doc.Clear();
        XMLElement* elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem;
    }
};

// Test Int64Value with a normal positive integer
TEST_F(XMLAttributeTest_72, Int64Value_PositiveInteger_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "12345");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 12345);
}

// Test Int64Value with zero
TEST_F(XMLAttributeTest_72, Int64Value_Zero_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 0);
}

// Test Int64Value with a negative integer
TEST_F(XMLAttributeTest_72, Int64Value_NegativeInteger_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "-98765");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), -98765);
}

// Test Int64Value with a large positive int64 value
TEST_F(XMLAttributeTest_72, Int64Value_LargePositive_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "9223372036854775807");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MAX);
}

// Test Int64Value with a large negative int64 value
TEST_F(XMLAttributeTest_72, Int64Value_LargeNegative_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "-9223372036854775808");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MIN);
}

// Test Int64Value with non-numeric value (should return 0 as default)
TEST_F(XMLAttributeTest_72, Int64Value_NonNumeric_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "abc");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 0);
}

// Test IntValue with a normal integer
TEST_F(XMLAttributeTest_72, IntValue_NormalValue_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "42");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test UnsignedValue with a normal unsigned integer
TEST_F(XMLAttributeTest_72, UnsignedValue_NormalValue_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "100");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 100u);
}

// Test Unsigned64Value with a normal value
TEST_F(XMLAttributeTest_72, Unsigned64Value_NormalValue_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "18446744073709551615");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_MAX);
}

// Test BoolValue with true
TEST_F(XMLAttributeTest_72, BoolValue_True_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test BoolValue with false
TEST_F(XMLAttributeTest_72, BoolValue_False_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "false");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), false);
}

// Test DoubleValue with a floating point value
TEST_F(XMLAttributeTest_72, DoubleValue_NormalValue_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "3.14159");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test FloatValue with a floating point value
TEST_F(XMLAttributeTest_72, FloatValue_NormalValue_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "2.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// Test Name returns the correct attribute name
TEST_F(XMLAttributeTest_72, Name_ReturnsCorrectName_72) {
    XMLElement* elem = CreateElementWithAttribute("myattr", "value");
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value returns the correct attribute value
TEST_F(XMLAttributeTest_72, Value_ReturnsCorrectValue_72) {
    XMLElement* elem = CreateElementWithAttribute("key", "hello world");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello world");
}

// Test QueryIntValue returns XML_SUCCESS for valid int
TEST_F(XMLAttributeTest_72, QueryIntValue_ValidInt_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "123");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 123);
}

// Test QueryIntValue returns error for non-integer
TEST_F(XMLAttributeTest_72, QueryIntValue_InvalidInt_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "not_a_number");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryInt64Value returns XML_SUCCESS for valid int64
TEST_F(XMLAttributeTest_72, QueryInt64Value_ValidInt64_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "999999999999");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 999999999999LL);
}

// Test QueryInt64Value returns error for non-numeric
TEST_F(XMLAttributeTest_72, QueryInt64Value_Invalid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "xyz");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryUnsignedValue with valid unsigned value
TEST_F(XMLAttributeTest_72, QueryUnsignedValue_Valid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "500");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 500u);
}

// Test QueryUnsigned64Value with valid value
TEST_F(XMLAttributeTest_72, QueryUnsigned64Value_Valid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "18446744073709551615");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

// Test QueryBoolValue with valid bool
TEST_F(XMLAttributeTest_72, QueryBoolValue_Valid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, true);
}

// Test QueryBoolValue with invalid value
TEST_F(XMLAttributeTest_72, QueryBoolValue_Invalid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "maybe");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryDoubleValue with valid double
TEST_F(XMLAttributeTest_72, QueryDoubleValue_Valid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.618");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 1.618);
}

// Test QueryFloatValue with valid float
TEST_F(XMLAttributeTest_72, QueryFloatValue_Valid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.5f);
}

// Test SetAttribute with int and then read back
TEST_F(XMLAttributeTest_72, SetAttributeInt_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 42);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test SetAttribute with int64_t and read back
TEST_F(XMLAttributeTest_72, SetAttributeInt64_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (int64_t)123456789012345LL);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 123456789012345LL);
}

// Test SetAttribute with uint64_t and read back
TEST_F(XMLAttributeTest_72, SetAttributeUint64_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (uint64_t)18446744073709551615ULL);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_MAX);
}

// Test SetAttribute with bool and read back
TEST_F(XMLAttributeTest_72, SetAttributeBool_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", true);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test SetAttribute with double and read back
TEST_F(XMLAttributeTest_72, SetAttributeDouble_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 2.71828);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 2.71828, 0.0001);
}

// Test SetAttribute with float and read back
TEST_F(XMLAttributeTest_72, SetAttributeFloat_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 1.5f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.5f);
}

// Test SetAttribute with string and read back
TEST_F(XMLAttributeTest_72, SetAttributeString_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", "hello");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");
}

// Test Next returns null when there is only one attribute
TEST_F(XMLAttributeTest_72, Next_SingleAttribute_ReturnsNull_72) {
    XMLElement* elem = CreateElementWithAttribute("only", "one");
    const XMLAttribute* attr = elem->FindAttribute("only");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Next(), nullptr);
}

// Test Next returns next attribute when multiple attributes exist
TEST_F(XMLAttributeTest_72, Next_MultipleAttributes_72) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_EQ(next->Next(), nullptr);
}

// Test GetLineNum
TEST_F(XMLAttributeTest_72, GetLineNum_72) {
    const char* xml = "<root attr=\"value\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // Line number should be >= 1
    EXPECT_GE(attr->GetLineNum(), 1);
}

// Test SetAttribute with unsigned int and read back
TEST_F(XMLAttributeTest_72, SetAttributeUnsigned_ReadBack_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (unsigned int)4294967295u);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 4294967295u);
}

// Test Int64Value with empty string attribute
TEST_F(XMLAttributeTest_72, Int64Value_EmptyString_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    // With an empty string, QueryInt64Value should fail, and Int64Value should return the initialized default (0)
    EXPECT_EQ(attr->Int64Value(), 0);
}

// Test parsing attribute from XML string
TEST_F(XMLAttributeTest_72, ParseFromXML_Int64Value_72) {
    const char* xml = "<root bignum=\"9223372036854775807\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("bignum");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MAX);
}

// Test QueryDoubleValue with invalid string
TEST_F(XMLAttributeTest_72, QueryDoubleValue_Invalid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "not_double");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryFloatValue with invalid string
TEST_F(XMLAttributeTest_72, QueryFloatValue_Invalid_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "not_float");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test negative int via SetAttribute
TEST_F(XMLAttributeTest_72, SetAttributeNegativeInt_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", -999);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -999);
}

// Test negative int64 via SetAttribute
TEST_F(XMLAttributeTest_72, SetAttributeNegativeInt64_72) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (int64_t)-123456789012345LL);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), -123456789012345LL);
}

// Test BoolValue with "1" as true
TEST_F(XMLAttributeTest_72, BoolValue_NumericOne_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "1");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, true);
}

// Test BoolValue with "0" as false
TEST_F(XMLAttributeTest_72, BoolValue_NumericZero_72) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, false);
}
