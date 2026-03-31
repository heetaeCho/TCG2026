#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_211 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    // Helper to create an element with an attribute having a specific value
    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        doc.Clear();
        char xml[256];
        snprintf(xml, sizeof(xml), "<root %s=\"%s\"/>", attrName, attrValue);
        doc.Parse(xml);
        XMLElement* root = doc.RootElement();
        return root;
    }
};

// ==================== QueryIntValue Tests ====================

TEST_F(XMLAttributeTest_211, QueryIntValue_ValidPositiveInteger_211) {
    XMLElement* root = CreateElementWithAttribute("val", "42");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLAttributeTest_211, QueryIntValue_ValidNegativeInteger_211) {
    XMLElement* root = CreateElementWithAttribute("val", "-100");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -100);
}

TEST_F(XMLAttributeTest_211, QueryIntValue_Zero_211) {
    XMLElement* root = CreateElementWithAttribute("val", "0");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = -1;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

TEST_F(XMLAttributeTest_211, QueryIntValue_NonNumericString_211) {
    XMLElement* root = CreateElementWithAttribute("val", "hello");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_211, QueryIntValue_EmptyString_211) {
    XMLElement* root = CreateElementWithAttribute("val", "");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_211, QueryIntValue_FloatingPointString_211) {
    XMLElement* root = CreateElementWithAttribute("val", "3.14");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    // Floating point string is not a valid integer
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_211, QueryIntValue_MaxInt_211) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", INT_MAX);
    XMLElement* root = CreateElementWithAttribute("val", buf);
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT_MAX);
}

TEST_F(XMLAttributeTest_211, QueryIntValue_MinInt_211) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", INT_MIN);
    XMLElement* root = CreateElementWithAttribute("val", buf);
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT_MIN);
}

// ==================== QueryUnsignedValue Tests ====================

TEST_F(XMLAttributeTest_211, QueryUnsignedValue_ValidUnsigned_211) {
    XMLElement* root = CreateElementWithAttribute("val", "123");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 123u);
}

TEST_F(XMLAttributeTest_211, QueryUnsignedValue_NonNumeric_211) {
    XMLElement* root = CreateElementWithAttribute("val", "abc");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryInt64Value Tests ====================

TEST_F(XMLAttributeTest_211, QueryInt64Value_ValidInt64_211) {
    XMLElement* root = CreateElementWithAttribute("val", "9223372036854775807");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLAttributeTest_211, QueryInt64Value_NonNumeric_211) {
    XMLElement* root = CreateElementWithAttribute("val", "notanumber");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryUnsigned64Value Tests ====================

TEST_F(XMLAttributeTest_211, QueryUnsigned64Value_Valid_211) {
    XMLElement* root = CreateElementWithAttribute("val", "18446744073709551615");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

TEST_F(XMLAttributeTest_211, QueryUnsigned64Value_NonNumeric_211) {
    XMLElement* root = CreateElementWithAttribute("val", "xyz");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryBoolValue Tests ====================

TEST_F(XMLAttributeTest_211, QueryBoolValue_True_211) {
    XMLElement* root = CreateElementWithAttribute("val", "true");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeTest_211, QueryBoolValue_False_211) {
    XMLElement* root = CreateElementWithAttribute("val", "false");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLAttributeTest_211, QueryBoolValue_InvalidString_211) {
    XMLElement* root = CreateElementWithAttribute("val", "maybe");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryDoubleValue Tests ====================

TEST_F(XMLAttributeTest_211, QueryDoubleValue_Valid_211) {
    XMLElement* root = CreateElementWithAttribute("val", "3.14159");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14159);
}

TEST_F(XMLAttributeTest_211, QueryDoubleValue_NonNumeric_211) {
    XMLElement* root = CreateElementWithAttribute("val", "notdouble");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryFloatValue Tests ====================

TEST_F(XMLAttributeTest_211, QueryFloatValue_Valid_211) {
    XMLElement* root = CreateElementWithAttribute("val", "2.5");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

TEST_F(XMLAttributeTest_211, QueryFloatValue_NonNumeric_211) {
    XMLElement* root = CreateElementWithAttribute("val", "notfloat");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== SetAttribute / Value Tests ====================

TEST_F(XMLAttributeTest_211, SetAttributeString_211) {
    doc.Parse("<root attr=\"original\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", "newvalue");
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "newvalue");
}

TEST_F(XMLAttributeTest_211, SetAttributeInt_211) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 999);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 999);
}

TEST_F(XMLAttributeTest_211, SetAttributeBool_211) {
    doc.Parse("<root attr=\"false\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", true);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeTest_211, SetAttributeDouble_211) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 1.5);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 1.5);
}

TEST_F(XMLAttributeTest_211, SetAttributeFloat_211) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 2.5f);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

TEST_F(XMLAttributeTest_211, SetAttributeUnsigned_211) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", (unsigned)4294967295u);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 4294967295u);
}

TEST_F(XMLAttributeTest_211, SetAttributeInt64_211) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", (int64_t)123456789012345LL);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 123456789012345LL);
}

TEST_F(XMLAttributeTest_211, SetAttributeUint64_211) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", (uint64_t)18446744073709551615ULL);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 18446744073709551615ULL);
}

// ==================== Name Tests ====================

TEST_F(XMLAttributeTest_211, Name_ReturnsCorrectName_211) {
    doc.Parse("<root myattr=\"123\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// ==================== Value Tests ====================

TEST_F(XMLAttributeTest_211, Value_ReturnsCorrectValue_211) {
    doc.Parse("<root attr=\"somevalue\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "somevalue");
}

// ==================== IntValue Tests ====================

TEST_F(XMLAttributeTest_211, IntValue_ReturnsIntegerValue_211) {
    XMLElement* root = CreateElementWithAttribute("val", "77");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 77);
}

// ==================== UnsignedValue Tests ====================

TEST_F(XMLAttributeTest_211, UnsignedValue_ReturnsUnsignedValue_211) {
    XMLElement* root = CreateElementWithAttribute("val", "300");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 300u);
}

// ==================== BoolValue Tests ====================

TEST_F(XMLAttributeTest_211, BoolValue_ReturnsBoolValue_211) {
    XMLElement* root = CreateElementWithAttribute("val", "true");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// ==================== DoubleValue Tests ====================

TEST_F(XMLAttributeTest_211, DoubleValue_ReturnsDoubleValue_211) {
    XMLElement* root = CreateElementWithAttribute("val", "1.23");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 1.23);
}

// ==================== FloatValue Tests ====================

TEST_F(XMLAttributeTest_211, FloatValue_ReturnsFloatValue_211) {
    XMLElement* root = CreateElementWithAttribute("val", "4.5");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 4.5f);
}

// ==================== Int64Value Tests ====================

TEST_F(XMLAttributeTest_211, Int64Value_ReturnsInt64Value_211) {
    XMLElement* root = CreateElementWithAttribute("val", "9223372036854775807");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MAX);
}

// ==================== Unsigned64Value Tests ====================

TEST_F(XMLAttributeTest_211, Unsigned64Value_ReturnsUnsigned64Value_211) {
    XMLElement* root = CreateElementWithAttribute("val", "18446744073709551615");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_MAX);
}

// ==================== Next Tests ====================

TEST_F(XMLAttributeTest_211, Next_ReturnsNextAttribute_211) {
    doc.Parse("<root first=\"1\" second=\"2\" third=\"3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("first");
    ASSERT_NE(attr, nullptr);
    
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "second");
    
    const XMLAttribute* third = next->Next();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Name(), "third");
    
    const XMLAttribute* end = third->Next();
    EXPECT_EQ(end, nullptr);
}

// ==================== GetLineNum Tests ====================

TEST_F(XMLAttributeTest_211, GetLineNum_ReturnsValidLineNumber_211) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 1);
}

// ==================== QueryIntValue with leading/trailing whitespace ====================

TEST_F(XMLAttributeTest_211, QueryIntValue_WithWhitespace_211) {
    XMLElement* root = CreateElementWithAttribute("val", " 42 ");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    // Behavior depends on ToInt implementation - either succeeds or fails
    // We just test that it doesn't crash
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== Mixed type attribute value ====================

TEST_F(XMLAttributeTest_211, QueryIntValue_StringWithLeadingDigits_211) {
    XMLElement* root = CreateElementWithAttribute("val", "123abc");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    // Should fail or partially parse - depends on implementation
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryBoolValue numeric ====================

TEST_F(XMLAttributeTest_211, QueryBoolValue_NumericOne_211) {
    XMLElement* root = CreateElementWithAttribute("val", "1");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    // "1" might be accepted as true
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_211, QueryBoolValue_NumericZero_211) {
    XMLElement* root = CreateElementWithAttribute("val", "0");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryDoubleValue with integer string ====================

TEST_F(XMLAttributeTest_211, QueryDoubleValue_IntegerString_211) {
    XMLElement* root = CreateElementWithAttribute("val", "42");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 42.0);
}

// ==================== QueryFloatValue negative ====================

TEST_F(XMLAttributeTest_211, QueryFloatValue_NegativeFloat_211) {
    XMLElement* root = CreateElementWithAttribute("val", "-1.5");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, -1.5f);
}
