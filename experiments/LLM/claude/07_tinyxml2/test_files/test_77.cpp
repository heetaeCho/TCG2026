#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeFloatValueTest_77 : public ::testing::Test {
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

// Test FloatValue with a simple integer value
TEST_F(XMLAttributeFloatValueTest_77, FloatValueReturnsCorrectIntegerValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "42");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 42.0f);
}

// Test FloatValue with a decimal float value
TEST_F(XMLAttributeFloatValueTest_77, FloatValueReturnsCorrectDecimalValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "3.14");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 3.14f, 0.001f);
}

// Test FloatValue with zero
TEST_F(XMLAttributeFloatValueTest_77, FloatValueReturnsZero_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 0.0f);
}

// Test FloatValue with negative value
TEST_F(XMLAttributeFloatValueTest_77, FloatValueReturnsNegativeValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "-2.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), -2.5f);
}

// Test FloatValue with a non-numeric string returns 0.0f (default)
TEST_F(XMLAttributeFloatValueTest_77, FloatValueReturnsDefaultForNonNumericString_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "hello");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 0.0f);
}

// Test FloatValue with empty string returns 0.0f (default)
TEST_F(XMLAttributeFloatValueTest_77, FloatValueReturnsDefaultForEmptyString_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 0.0f);
}

// Test FloatValue with very large float value
TEST_F(XMLAttributeFloatValueTest_77, FloatValueWithLargeValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.0e10");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.0e10f);
}

// Test FloatValue with very small float value
TEST_F(XMLAttributeFloatValueTest_77, FloatValueWithSmallValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.0e-10");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 1.0e-10f, 1.0e-15f);
}

// Test FloatValue set via SetAttribute(float)
TEST_F(XMLAttributeFloatValueTest_77, FloatValueAfterSetAttributeFloat_77) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 7.5f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 7.5f);
}

// Test FloatValue with negative zero
TEST_F(XMLAttributeFloatValueTest_77, FloatValueWithNegativeZero_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "-0.0");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 0.0f);
}

// Test QueryFloatValue returns XML_SUCCESS for valid float
TEST_F(XMLAttributeFloatValueTest_77, QueryFloatValueReturnsSuccessForValidFloat_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.23");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float f = 0.0f;
    XMLError err = attr->QueryFloatValue(&f);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(f, 1.23f, 0.001f);
}

// Test QueryFloatValue returns error for non-numeric string
TEST_F(XMLAttributeFloatValueTest_77, QueryFloatValueReturnsErrorForNonNumeric_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "notanumber");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float f = 0.0f;
    XMLError err = attr->QueryFloatValue(&f);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test other Value functions for completeness of the XMLAttribute interface

// Test IntValue
TEST_F(XMLAttributeFloatValueTest_77, IntValueReturnsCorrectValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "123");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 123);
}

// Test UnsignedValue
TEST_F(XMLAttributeFloatValueTest_77, UnsignedValueReturnsCorrectValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "456");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 456u);
}

// Test Int64Value
TEST_F(XMLAttributeFloatValueTest_77, Int64ValueReturnsCorrectValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "9876543210");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 9876543210LL);
}

// Test Unsigned64Value
TEST_F(XMLAttributeFloatValueTest_77, Unsigned64ValueReturnsCorrectValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "9876543210");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 9876543210ULL);
}

// Test BoolValue with true
TEST_F(XMLAttributeFloatValueTest_77, BoolValueReturnsTrueForTrue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test BoolValue with false
TEST_F(XMLAttributeFloatValueTest_77, BoolValueReturnsFalseForFalse_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "false");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), false);
}

// Test DoubleValue
TEST_F(XMLAttributeFloatValueTest_77, DoubleValueReturnsCorrectValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "3.141592653589793");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 3.141592653589793, 1e-12);
}

// Test Name returns the attribute name
TEST_F(XMLAttributeFloatValueTest_77, NameReturnsCorrectName_77) {
    XMLElement* elem = CreateElementWithAttribute("myattr", "100");
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value returns the string value
TEST_F(XMLAttributeFloatValueTest_77, ValueReturnsCorrectStringValue_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "sometext");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "sometext");
}

// Test SetAttribute updates the value and FloatValue reflects the change
TEST_F(XMLAttributeFloatValueTest_77, SetAttributeUpdatesFloatValue_77) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 1.0f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.0f);
    
    // Now update via the element
    elem->SetAttribute("val", 99.9f);
    attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 99.9f, 0.01f);
}

// Test Next returns nullptr when there's only one attribute
TEST_F(XMLAttributeFloatValueTest_77, NextReturnsNullForSingleAttribute_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "1");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Next(), nullptr);
}

// Test Next returns the next attribute when multiple attributes exist
TEST_F(XMLAttributeFloatValueTest_77, NextReturnsNextAttribute_77) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");
    
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "second");
    
    EXPECT_EQ(next->Next(), nullptr);
}

// Test GetLineNum
TEST_F(XMLAttributeFloatValueTest_77, GetLineNumReturnsNonNegative_77) {
    const char* xml = "<root attr=\"5\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 0);
}

// Test FloatValue with scientific notation (negative exponent)
TEST_F(XMLAttributeFloatValueTest_77, FloatValueScientificNotationNegativeExponent_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "2.5e-3");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 0.0025f, 1e-6f);
}

// Test FloatValue with scientific notation (positive exponent)
TEST_F(XMLAttributeFloatValueTest_77, FloatValueScientificNotationPositiveExponent_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "2.5e3");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2500.0f);
}

// Test SetAttribute with various types and verify through Value()
TEST_F(XMLAttributeFloatValueTest_77, SetAttributeIntUpdatesValue_77) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 42);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 42.0f);
}

TEST_F(XMLAttributeFloatValueTest_77, SetAttributeDoubleUpdatesValue_77) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 3.14);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 3.14, 0.001);
}

TEST_F(XMLAttributeFloatValueTest_77, SetAttributeBoolUpdatesValue_77) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", true);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

TEST_F(XMLAttributeFloatValueTest_77, SetAttributeStringUpdatesValue_77) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", "hello");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");
}

// Test QueryIntValue error for non-integer string
TEST_F(XMLAttributeFloatValueTest_77, QueryIntValueReturnsErrorForNonInteger_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "abc");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int v = 0;
    XMLError err = attr->QueryIntValue(&v);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryBoolValue error for non-boolean string
TEST_F(XMLAttributeFloatValueTest_77, QueryBoolValueReturnsErrorForNonBool_77) {
    XMLElement* elem = CreateElementWithAttribute("val", "notabool");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool v = false;
    XMLError err = attr->QueryBoolValue(&v);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test parsing from XML string
TEST_F(XMLAttributeFloatValueTest_77, FloatValueFromParsedXML_77) {
    const char* xml = "<root pi=\"3.14159\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("pi");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 3.14159f, 0.0001f);
}
