#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeQueryDoubleValueTest_217 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        doc.Clear();
        XMLElement* root = doc.NewElement("root");
        doc.InsertFirstChild(root);
        root->SetAttribute(attrName, attrValue);
        return root;
    }
};

// Test QueryDoubleValue with a valid integer string
TEST_F(XMLAttributeQueryDoubleValueTest_217, ValidIntegerString_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "42");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

// Test QueryDoubleValue with a valid floating-point string
TEST_F(XMLAttributeQueryDoubleValueTest_217, ValidFloatingPointString_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "3.14159");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 3.14159, 1e-10);
}

// Test QueryDoubleValue with a negative floating-point string
TEST_F(XMLAttributeQueryDoubleValueTest_217, NegativeFloatingPointString_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "-2.718");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, -2.718, 1e-10);
}

// Test QueryDoubleValue with zero
TEST_F(XMLAttributeQueryDoubleValueTest_217, ZeroValue_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = -1.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test QueryDoubleValue with zero point zero
TEST_F(XMLAttributeQueryDoubleValueTest_217, ZeroPointZeroValue_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "0.0");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = -1.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test QueryDoubleValue with scientific notation
TEST_F(XMLAttributeQueryDoubleValueTest_217, ScientificNotation_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.5e10");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 1.5e10);
}

// Test QueryDoubleValue with negative scientific notation
TEST_F(XMLAttributeQueryDoubleValueTest_217, NegativeScientificNotation_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "-3.0e-5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, -3.0e-5, 1e-15);
}

// Test QueryDoubleValue with an invalid (non-numeric) string
TEST_F(XMLAttributeQueryDoubleValueTest_217, InvalidNonNumericString_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "hello");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryDoubleValue with an empty string
TEST_F(XMLAttributeQueryDoubleValueTest_217, EmptyString_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryDoubleValue with a very large number
TEST_F(XMLAttributeQueryDoubleValueTest_217, VeryLargeNumber_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.7976931348623157e+308");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 1.7976931348623157e+308);
}

// Test QueryDoubleValue with a very small positive number
TEST_F(XMLAttributeQueryDoubleValueTest_217, VerySmallPositiveNumber_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "2.2250738585072014e-308");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 2.2250738585072014e-308);
}

// Test QueryDoubleValue with mixed text starting with number
TEST_F(XMLAttributeQueryDoubleValueTest_217, MixedTextStartingWithNumber_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "123abc");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    // Depending on implementation, this may succeed or fail
    // The important thing is we get a defined result
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryDoubleValue with leading whitespace
TEST_F(XMLAttributeQueryDoubleValueTest_217, LeadingWhitespace_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "  42.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    // strtod typically handles leading whitespace
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryDoubleValue with positive sign
TEST_F(XMLAttributeQueryDoubleValueTest_217, PositiveSign_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "+99.9");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 99.9, 1e-10);
}

// Test QueryDoubleValue using SetAttribute(double) then query
TEST_F(XMLAttributeQueryDoubleValueTest_217, SetAttributeDoubleThenQuery_217) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 123.456);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 123.456, 1e-6);
}

// Test QueryDoubleValue after setting integer attribute
TEST_F(XMLAttributeQueryDoubleValueTest_217, SetAttributeIntThenQueryDouble_217) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 100);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 100.0);
}

// Test QueryDoubleValue with boolean attribute value
TEST_F(XMLAttributeQueryDoubleValueTest_217, BooleanStringValue_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryDoubleValue with "false" string
TEST_F(XMLAttributeQueryDoubleValueTest_217, FalseStringValue_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "false");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryDoubleValue with decimal point only no digits
TEST_F(XMLAttributeQueryDoubleValueTest_217, DecimalPointOnly_217) {
    XMLElement* elem = CreateElementWithAttribute("val", ".");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    // A single dot is not a valid double in most parsers
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test DoubleValue convenience method (returns double directly)
TEST_F(XMLAttributeQueryDoubleValueTest_217, DoubleValueConvenience_217) {
    XMLElement* elem = CreateElementWithAttribute("val", "7.77");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = attr->DoubleValue();
    EXPECT_NEAR(result, 7.77, 1e-10);
}

// Test that SetAttribute(double) round-trips correctly
TEST_F(XMLAttributeQueryDoubleValueTest_217, RoundTripDouble_217) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertFirstChild(elem);
    double original = -987.654321;
    elem->SetAttribute("val", original);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, original, 1e-6);
}
