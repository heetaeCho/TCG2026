#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryIntAttribute_81 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }
};

// Test QueryIntAttribute with a valid integer attribute
TEST_F(XMLElementQueryIntAttribute_81, ValidIntAttribute_81) {
    doc.Parse("<root value=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 42);
}

// Test QueryIntAttribute with a non-existent attribute
TEST_F(XMLElementQueryIntAttribute_81, NonExistentAttribute_81) {
    doc.Parse("<root value=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = -1;
    XMLError err = root->QueryIntAttribute("nonexistent", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(result, -1); // value should remain unchanged
}

// Test QueryIntAttribute with a non-integer attribute value
TEST_F(XMLElementQueryIntAttribute_81, WrongAttributeType_81) {
    doc.Parse("<root value=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = -1;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryIntAttribute with negative integer
TEST_F(XMLElementQueryIntAttribute_81, NegativeIntAttribute_81) {
    doc.Parse("<root value=\"-100\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, -100);
}

// Test QueryIntAttribute with zero
TEST_F(XMLElementQueryIntAttribute_81, ZeroAttribute_81) {
    doc.Parse("<root value=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 99;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 0);
}

// Test QueryIntAttribute with element that has no attributes at all
TEST_F(XMLElementQueryIntAttribute_81, NoAttributesElement_81) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 55;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(result, 55);
}

// Test QueryIntAttribute with multiple attributes, query specific one
TEST_F(XMLElementQueryIntAttribute_81, MultipleAttributes_81) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("b", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 2);
}

// Test QueryIntAttribute with a floating-point string
TEST_F(XMLElementQueryIntAttribute_81, FloatingPointAttribute_81) {
    doc.Parse("<root value=\"3.14\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("value", &result);
    // Depending on implementation, it might parse as 3 or return wrong type
    // We just check it doesn't return XML_NO_ATTRIBUTE
    EXPECT_NE(err, XML_NO_ATTRIBUTE);
}

// Test QueryIntAttribute with empty string value
TEST_F(XMLElementQueryIntAttribute_81, EmptyStringAttribute_81) {
    doc.Parse("<root value=\"\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = -1;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryIntAttribute with large positive integer
TEST_F(XMLElementQueryIntAttribute_81, LargePositiveInt_81) {
    doc.Parse("<root value=\"2147483647\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 2147483647);
}

// Test QueryIntAttribute with large negative integer
TEST_F(XMLElementQueryIntAttribute_81, LargeNegativeInt_81) {
    doc.Parse("<root value=\"-2147483648\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, -2147483648);
}

// Test QueryIntAttribute with whitespace around number
TEST_F(XMLElementQueryIntAttribute_81, WhitespaceAroundNumber_81) {
    doc.Parse("<root value=\" 42 \"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("value", &result);
    // Implementation may or may not handle leading/trailing whitespace
    // We only check that it doesn't crash and returns some valid error code
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryIntAttribute after setting attribute via SetAttribute
TEST_F(XMLElementQueryIntAttribute_81, SetThenQueryAttribute_81) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("myattr", 123);

    int result = 0;
    XMLError err = root->QueryIntAttribute("myattr", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 123);
}

// Test QueryIntAttribute with attribute name that is a substring of another
TEST_F(XMLElementQueryIntAttribute_81, SubstringAttributeName_81) {
    doc.Parse("<root val=\"10\" value=\"20\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("val", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 10);

    result = 0;
    err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 20);
}

// Test QueryIntAttribute after deleting the attribute
TEST_F(XMLElementQueryIntAttribute_81, QueryAfterDeleteAttribute_81) {
    doc.Parse("<root value=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->DeleteAttribute("value");

    int result = -1;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(result, -1);
}

// Test QueryIntAttribute with boolean-like string
TEST_F(XMLElementQueryIntAttribute_81, BooleanStringAttribute_81) {
    doc.Parse("<root value=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int result = 0;
    XMLError err = root->QueryIntAttribute("value", &result);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test other Query*Attribute methods for completeness

// Test QueryUnsignedAttribute
TEST_F(XMLElementQueryIntAttribute_81, QueryUnsignedAttribute_81) {
    doc.Parse("<root value=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    unsigned int result = 0;
    XMLError err = root->QueryUnsignedAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 42u);
}

// Test QueryUnsignedAttribute non-existent
TEST_F(XMLElementQueryIntAttribute_81, QueryUnsignedAttributeNonExistent_81) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    unsigned int result = 99;
    XMLError err = root->QueryUnsignedAttribute("missing", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(result, 99u);
}

// Test QueryBoolAttribute
TEST_F(XMLElementQueryIntAttribute_81, QueryBoolAttributeTrue_81) {
    doc.Parse("<root value=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool result = false;
    XMLError err = root->QueryBoolAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, true);
}

// Test QueryBoolAttribute with non-existent attribute
TEST_F(XMLElementQueryIntAttribute_81, QueryBoolAttributeNonExistent_81) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool result = true;
    XMLError err = root->QueryBoolAttribute("missing", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(result, true);
}

// Test QueryDoubleAttribute
TEST_F(XMLElementQueryIntAttribute_81, QueryDoubleAttribute_81) {
    doc.Parse("<root value=\"3.14159\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double result = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 3.14159);
}

// Test QueryFloatAttribute
TEST_F(XMLElementQueryIntAttribute_81, QueryFloatAttribute_81) {
    doc.Parse("<root value=\"2.5\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    float result = 0.0f;
    XMLError err = root->QueryFloatAttribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 2.5f);
}

// Test QueryInt64Attribute
TEST_F(XMLElementQueryIntAttribute_81, QueryInt64Attribute_81) {
    doc.Parse("<root value=\"9223372036854775807\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int64_t result = 0;
    XMLError err = root->QueryInt64Attribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, INT64_C(9223372036854775807));
}

// Test QueryUnsigned64Attribute
TEST_F(XMLElementQueryIntAttribute_81, QueryUnsigned64Attribute_81) {
    doc.Parse("<root value=\"18446744073709551615\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    uint64_t result = 0;
    XMLError err = root->QueryUnsigned64Attribute("value", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, UINT64_C(18446744073709551615));
}

// Test QueryStringAttribute
TEST_F(XMLElementQueryIntAttribute_81, QueryStringAttribute_81) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* result = nullptr;
    XMLError err = root->QueryStringAttribute("name", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

// Test QueryStringAttribute non-existent
TEST_F(XMLElementQueryIntAttribute_81, QueryStringAttributeNonExistent_81) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* result = nullptr;
    XMLError err = root->QueryStringAttribute("missing", &result);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test IntAttribute convenience method with default
TEST_F(XMLElementQueryIntAttribute_81, IntAttributeWithDefault_81) {
    doc.Parse("<root value=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->IntAttribute("value", 0), 42);
    EXPECT_EQ(root->IntAttribute("missing", 99), 99);
}

// Test Attribute method
TEST_F(XMLElementQueryIntAttribute_81, AttributeMethod_81) {
    doc.Parse("<root name=\"test\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* val = root->Attribute("name");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "test");

    EXPECT_EQ(root->Attribute("missing"), nullptr);
}

// Test FindAttribute
TEST_F(XMLElementQueryIntAttribute_81, FindAttribute_81) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = root->FindAttribute("a");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
    EXPECT_STREQ(attr->Value(), "1");

    EXPECT_EQ(root->FindAttribute("c"), nullptr);
}

// Test FirstAttribute and Next
TEST_F(XMLElementQueryIntAttribute_81, FirstAttributeAndNext_81) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = root->FirstAttribute();
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
