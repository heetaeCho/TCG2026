#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeDoubleValueTest_76 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test DoubleValue with a simple integer value
TEST_F(XMLAttributeDoubleValueTest_76, IntegerValueAsDouble_76) {
    doc.Parse("<root attr=\"42\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 42.0);
}

// Test DoubleValue with a floating point value
TEST_F(XMLAttributeDoubleValueTest_76, FloatingPointValue_76) {
    doc.Parse("<root attr=\"3.14159\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test DoubleValue with zero
TEST_F(XMLAttributeDoubleValueTest_76, ZeroValue_76) {
    doc.Parse("<root attr=\"0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 0.0);
}

// Test DoubleValue with negative value
TEST_F(XMLAttributeDoubleValueTest_76, NegativeValue_76) {
    doc.Parse("<root attr=\"-123.456\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), -123.456);
}

// Test DoubleValue with a very large value
TEST_F(XMLAttributeDoubleValueTest_76, LargeValue_76) {
    doc.Parse("<root attr=\"1.7976931348623157e+308\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 1.7976931348623157e+308);
}

// Test DoubleValue with a very small positive value
TEST_F(XMLAttributeDoubleValueTest_76, SmallPositiveValue_76) {
    doc.Parse("<root attr=\"2.2250738585072014e-308\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 2.2250738585072014e-308);
}

// Test DoubleValue with non-numeric string returns 0 (default)
TEST_F(XMLAttributeDoubleValueTest_76, NonNumericValueReturnsDefault_76) {
    doc.Parse("<root attr=\"hello\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // When QueryDoubleValue fails, d should remain 0.0 (the initialized value)
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 0.0);
}

// Test DoubleValue with scientific notation
TEST_F(XMLAttributeDoubleValueTest_76, ScientificNotation_76) {
    doc.Parse("<root attr=\"1.5e10\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 1.5e10);
}

// Test DoubleValue with negative scientific notation
TEST_F(XMLAttributeDoubleValueTest_76, NegativeScientificNotation_76) {
    doc.Parse("<root attr=\"-2.5e-3\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), -2.5e-3);
}

// Test DoubleValue after SetAttribute with double
TEST_F(XMLAttributeDoubleValueTest_76, SetAttributeDouble_76) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 99.99);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 99.99);
}

// Test DoubleValue after SetAttribute with int
TEST_F(XMLAttributeDoubleValueTest_76, SetAttributeInt_76) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 7);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 7.0);
}

// Test DoubleValue with empty string attribute
TEST_F(XMLAttributeDoubleValueTest_76, EmptyStringValue_76) {
    doc.Parse("<root attr=\"\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // Empty string is not a valid double, should return default 0.0
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 0.0);
}

// Test DoubleValue with negative zero
TEST_F(XMLAttributeDoubleValueTest_76, NegativeZero_76) {
    doc.Parse("<root attr=\"-0.0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 0.0);
}

// Test DoubleValue with 0.0
TEST_F(XMLAttributeDoubleValueTest_76, ZeroPointZero_76) {
    doc.Parse("<root attr=\"0.0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 0.0);
}

// Test QueryDoubleValue returns XML_SUCCESS for valid double
TEST_F(XMLAttributeDoubleValueTest_76, QueryDoubleValueSuccess_76) {
    doc.Parse("<root attr=\"3.14\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// Test QueryDoubleValue returns error for non-numeric string
TEST_F(XMLAttributeDoubleValueTest_76, QueryDoubleValueError_76) {
    doc.Parse("<root attr=\"abc\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test DoubleValue with value set via SetAttribute(double)
TEST_F(XMLAttributeDoubleValueTest_76, SetAndGetDoubleAttribute_76) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 1.23456789012345);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // Due to string representation precision, check nearness
    EXPECT_NEAR(attr->DoubleValue(), 1.23456789012345, 1e-10);
}

// Test DoubleValue with value set via SetAttribute(float)
TEST_F(XMLAttributeDoubleValueTest_76, SetFloatGetDouble_76) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 2.5, 1e-6);
}
