#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_213 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    // Helper to create an element with an attribute having a specific value
    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        doc.Clear();
        std::string xml = std::string("<root ") + attrName + "=\"" + attrValue + "\"/>";
        doc.Parse(xml.c_str());
        XMLElement* root = doc.RootElement();
        return root;
    }
};

// Test QueryInt64Value with a valid positive integer
TEST_F(XMLAttributeTest_213, QueryInt64Value_ValidPositiveInteger_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "12345");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 12345);
}

// Test QueryInt64Value with a valid negative integer
TEST_F(XMLAttributeTest_213, QueryInt64Value_ValidNegativeInteger_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "-98765");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -98765);
}

// Test QueryInt64Value with zero
TEST_F(XMLAttributeTest_213, QueryInt64Value_Zero_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = -1;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

// Test QueryInt64Value with a large positive int64 value
TEST_F(XMLAttributeTest_213, QueryInt64Value_LargePositiveValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "9223372036854775807");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_MAX);
}

// Test QueryInt64Value with the most negative int64 value
TEST_F(XMLAttributeTest_213, QueryInt64Value_MostNegativeValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "-9223372036854775808");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    // This may or may not succeed depending on the parser; just check it doesn't crash
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, INT64_MIN);
    }
}

// Test QueryInt64Value with a non-numeric string
TEST_F(XMLAttributeTest_213, QueryInt64Value_NonNumericString_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "hello");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryInt64Value with an empty string
TEST_F(XMLAttributeTest_213, QueryInt64Value_EmptyString_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryInt64Value with a floating point string
TEST_F(XMLAttributeTest_213, QueryInt64Value_FloatingPointString_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "3.14");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    // Floating point is not a valid int64; expect wrong type
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryInt64Value with a string containing leading/trailing spaces around a number
TEST_F(XMLAttributeTest_213, QueryInt64Value_StringWithSpaces_213) {
    XMLElement* elem = CreateElementWithAttribute("val", " 42 ");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    // Behavior may vary; just record what happens
    // Either it succeeds with 42 or fails
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, 42);
    } else {
        EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
    }
}

// Test QueryInt64Value with mixed alphanumeric string
TEST_F(XMLAttributeTest_213, QueryInt64Value_MixedAlphanumeric_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "123abc");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    // Could be WRONG_ATTRIBUTE_TYPE or partial parse; check it doesn't crash
    // Most strict parsers would reject this
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryInt64Value after SetAttribute with int64_t
TEST_F(XMLAttributeTest_213, QueryInt64Value_AfterSetAttributeInt64_213) {
    doc.Clear();
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", static_cast<int64_t>(1234567890123LL));
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 1234567890123LL);
}

// Test QueryInt64Value with boolean-like string "true"
TEST_F(XMLAttributeTest_213, QueryInt64Value_BooleanString_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test Int64Value convenience method returns the value directly
TEST_F(XMLAttributeTest_213, Int64Value_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "42");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_EQ(attr->Int64Value(), 42);
}

// Test QueryIntValue with valid integer
TEST_F(XMLAttributeTest_213, QueryIntValue_ValidInteger_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "999");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 999);
}

// Test QueryIntValue with non-numeric string
TEST_F(XMLAttributeTest_213, QueryIntValue_NonNumeric_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "abc");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryUnsignedValue with valid unsigned integer
TEST_F(XMLAttributeTest_213, QueryUnsignedValue_ValidUnsigned_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "4294967295");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 4294967295U);
}

// Test QueryUnsigned64Value with valid uint64 value
TEST_F(XMLAttributeTest_213, QueryUnsigned64Value_ValidValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "18446744073709551615");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

// Test QueryBoolValue with "true"
TEST_F(XMLAttributeTest_213, QueryBoolValue_True_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test QueryBoolValue with "false"
TEST_F(XMLAttributeTest_213, QueryBoolValue_False_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "false");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test QueryDoubleValue with valid double
TEST_F(XMLAttributeTest_213, QueryDoubleValue_ValidDouble_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "3.14159");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14159);
}

// Test QueryFloatValue with valid float
TEST_F(XMLAttributeTest_213, QueryFloatValue_ValidFloat_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "2.5");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

// Test Name returns the attribute name
TEST_F(XMLAttributeTest_213, Name_ReturnsCorrectName_213) {
    XMLElement* elem = CreateElementWithAttribute("myattr", "100");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value returns the attribute value as string
TEST_F(XMLAttributeTest_213, Value_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "sometext");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_STREQ(attr->Value(), "sometext");
}

// Test SetAttribute with string and then query
TEST_F(XMLAttributeTest_213, SetAttributeString_ThenQuery_213) {
    doc.Clear();
    doc.Parse("<root val=\"initial\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", "42");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

// Test Next returns the next attribute or nullptr
TEST_F(XMLAttributeTest_213, Next_ReturnsNextAttributeOrNull_213) {
    doc.Clear();
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const XMLAttribute* attr = elem->FindAttribute("a");
    ASSERT_NE(attr, nullptr);
    
    const XMLAttribute* nextAttr = attr->Next();
    ASSERT_NE(nextAttr, nullptr);
    EXPECT_STREQ(nextAttr->Name(), "b");
    
    // Next of the last attribute should be nullptr
    EXPECT_EQ(nextAttr->Next(), nullptr);
}

// Test IntValue convenience method
TEST_F(XMLAttributeTest_213, IntValue_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "777");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_EQ(attr->IntValue(), 777);
}

// Test UnsignedValue convenience method
TEST_F(XMLAttributeTest_213, UnsignedValue_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "12345");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_EQ(attr->UnsignedValue(), 12345u);
}

// Test BoolValue convenience method
TEST_F(XMLAttributeTest_213, BoolValue_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_TRUE(attr->BoolValue());
}

// Test DoubleValue convenience method
TEST_F(XMLAttributeTest_213, DoubleValue_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.23");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 1.23);
}

// Test FloatValue convenience method
TEST_F(XMLAttributeTest_213, FloatValue_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "4.5");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_FLOAT_EQ(attr->FloatValue(), 4.5f);
}

// Test Unsigned64Value convenience method
TEST_F(XMLAttributeTest_213, Unsigned64Value_ReturnsCorrectValue_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "9999999999999");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_EQ(attr->Unsigned64Value(), 9999999999999ULL);
}

// Test QueryInt64Value with only a minus sign
TEST_F(XMLAttributeTest_213, QueryInt64Value_OnlyMinusSign_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "-");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryInt64Value with a plus sign prefix
TEST_F(XMLAttributeTest_213, QueryInt64Value_PlusSign_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "+100");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    // strtoll typically accepts +100
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, 100);
    }
}

// Test SetAttribute with different types and verify round-trip
TEST_F(XMLAttributeTest_213, SetAttributeInt_RoundTrip_213) {
    doc.Clear();
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", 42);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    EXPECT_EQ(attr->QueryIntValue(&value), XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLAttributeTest_213, SetAttributeBool_RoundTrip_213) {
    doc.Clear();
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", true);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    EXPECT_EQ(attr->QueryBoolValue(&value), XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeTest_213, SetAttributeDouble_RoundTrip_213) {
    doc.Clear();
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", 2.718);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&value), XML_SUCCESS);
    EXPECT_NEAR(value, 2.718, 0.001);
}

TEST_F(XMLAttributeTest_213, SetAttributeUnsigned_RoundTrip_213) {
    doc.Clear();
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", 3000000000U);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&value), XML_SUCCESS);
    EXPECT_EQ(value, 3000000000U);
}

TEST_F(XMLAttributeTest_213, SetAttributeUnsigned64_RoundTrip_213) {
    doc.Clear();
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", static_cast<uint64_t>(18446744073709551600ULL));
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    EXPECT_EQ(attr->QueryUnsigned64Value(&value), XML_SUCCESS);
    EXPECT_EQ(value, 18446744073709551600ULL);
}

TEST_F(XMLAttributeTest_213, SetAttributeFloat_RoundTrip_213) {
    doc.Clear();
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", 1.5f);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    EXPECT_EQ(attr->QueryFloatValue(&value), XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.5f);
}

// Test GetLineNum returns a non-negative line number
TEST_F(XMLAttributeTest_213, GetLineNum_ReturnsNonNegative_213) {
    XMLElement* elem = CreateElementWithAttribute("val", "1");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_GE(attr->GetLineNum(), 0);
}
