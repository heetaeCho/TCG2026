#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper fixture that creates an XMLDocument and elements with attributes
class XMLAttributeTest_210 : public ::testing::Test {
protected:
    XMLDocument doc;

    // Helper to create an element with an attribute and return the attribute
    const XMLAttribute* CreateAttribute(const char* attrName, const char* attrValue) {
        XMLElement* elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem->FindAttribute(attrName);
    }

    XMLElement* CreateElement() {
        XMLElement* elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        return elem;
    }
};

// Test Value() returns the string value set on the attribute
TEST_F(XMLAttributeTest_210, ValueReturnsSetString_210) {
    const XMLAttribute* attr = CreateAttribute("name", "hello");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");
}

// Test Name() returns the attribute name
TEST_F(XMLAttributeTest_210, NameReturnsAttributeName_210) {
    const XMLAttribute* attr = CreateAttribute("myattr", "myvalue");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value() with empty string
TEST_F(XMLAttributeTest_210, ValueReturnsEmptyString_210) {
    const XMLAttribute* attr = CreateAttribute("name", "");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

// Test SetAttribute with const char* and verify Value()
TEST_F(XMLAttributeTest_210, SetAttributeString_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "value1");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "value1");
}

// Test SetAttribute with int and verify Value and QueryIntValue
TEST_F(XMLAttributeTest_210, SetAttributeInt_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("intattr", 42);
    const XMLAttribute* attr = elem->FindAttribute("intattr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test SetAttribute with negative int
TEST_F(XMLAttributeTest_210, SetAttributeNegativeInt_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("negint", -100);
    const XMLAttribute* attr = elem->FindAttribute("negint");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, -100);
}

// Test SetAttribute with unsigned int
TEST_F(XMLAttributeTest_210, SetAttributeUnsigned_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("uattr", (unsigned)4294967295U);
    const XMLAttribute* attr = elem->FindAttribute("uattr");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 4294967295U);
    EXPECT_EQ(attr->UnsignedValue(), 4294967295U);
}

// Test SetAttribute with int64_t
TEST_F(XMLAttributeTest_210, SetAttributeInt64_210) {
    XMLElement* elem = CreateElement();
    int64_t bigVal = 9223372036854775807LL;
    elem->SetAttribute("i64attr", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("i64attr");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    EXPECT_EQ(attr->QueryInt64Value(&val), XML_SUCCESS);
    EXPECT_EQ(val, bigVal);
    EXPECT_EQ(attr->Int64Value(), bigVal);
}

// Test SetAttribute with uint64_t
TEST_F(XMLAttributeTest_210, SetAttributeUnsigned64_210) {
    XMLElement* elem = CreateElement();
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetAttribute("u64attr", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("u64attr");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    EXPECT_EQ(attr->QueryUnsigned64Value(&val), XML_SUCCESS);
    EXPECT_EQ(val, bigVal);
    EXPECT_EQ(attr->Unsigned64Value(), bigVal);
}

// Test SetAttribute with bool true
TEST_F(XMLAttributeTest_210, SetAttributeBoolTrue_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("boolattr", true);
    const XMLAttribute* attr = elem->FindAttribute("boolattr");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
    EXPECT_TRUE(attr->BoolValue());
}

// Test SetAttribute with bool false
TEST_F(XMLAttributeTest_210, SetAttributeBoolFalse_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("boolattr", false);
    const XMLAttribute* attr = elem->FindAttribute("boolattr");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
    EXPECT_FALSE(attr->BoolValue());
}

// Test SetAttribute with double
TEST_F(XMLAttributeTest_210, SetAttributeDouble_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("dblattr", 3.14159);
    const XMLAttribute* attr = elem->FindAttribute("dblattr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14159);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test SetAttribute with float
TEST_F(XMLAttributeTest_210, SetAttributeFloat_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("fltattr", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("fltattr");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    EXPECT_EQ(attr->QueryFloatValue(&val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// Test QueryIntValue with non-numeric string returns error
TEST_F(XMLAttributeTest_210, QueryIntValueNonNumericReturnsError_210) {
    const XMLAttribute* attr = CreateAttribute("name", "notanumber");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_NE(attr->QueryIntValue(&val), XML_SUCCESS);
}

// Test QueryUnsignedValue with non-numeric string returns error
TEST_F(XMLAttributeTest_210, QueryUnsignedValueNonNumericReturnsError_210) {
    const XMLAttribute* attr = CreateAttribute("name", "abc");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    EXPECT_NE(attr->QueryUnsignedValue(&val), XML_SUCCESS);
}

// Test QueryBoolValue with non-boolean string returns error
TEST_F(XMLAttributeTest_210, QueryBoolValueNonBoolReturnsError_210) {
    const XMLAttribute* attr = CreateAttribute("name", "notbool");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    EXPECT_NE(attr->QueryBoolValue(&val), XML_SUCCESS);
}

// Test QueryDoubleValue with non-numeric string returns error
TEST_F(XMLAttributeTest_210, QueryDoubleValueNonNumericReturnsError_210) {
    const XMLAttribute* attr = CreateAttribute("name", "xyz");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    EXPECT_NE(attr->QueryDoubleValue(&val), XML_SUCCESS);
}

// Test QueryFloatValue with non-numeric string returns error
TEST_F(XMLAttributeTest_210, QueryFloatValueNonNumericReturnsError_210) {
    const XMLAttribute* attr = CreateAttribute("name", "xyz");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    EXPECT_NE(attr->QueryFloatValue(&val), XML_SUCCESS);
}

// Test Next() returns next attribute
TEST_F(XMLAttributeTest_210, NextReturnsNextAttribute_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");
    const XMLAttribute* attr = elem->FindAttribute("first");
    ASSERT_NE(attr, nullptr);
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "second");
    EXPECT_STREQ(next->Value(), "2");
}

// Test Next() returns nullptr when no more attributes
TEST_F(XMLAttributeTest_210, NextReturnsNullWhenLast_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("only", "1");
    const XMLAttribute* attr = elem->FindAttribute("only");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Next(), nullptr);
}

// Test Value with special characters
TEST_F(XMLAttributeTest_210, ValueWithSpecialChars_210) {
    const XMLAttribute* attr = CreateAttribute("name", "hello&world<>");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello&world<>");
}

// Test overwriting attribute value
TEST_F(XMLAttributeTest_210, OverwriteAttributeValue_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "original");
    elem->SetAttribute("key", "updated");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "updated");
}

// Test SetAttribute with zero int
TEST_F(XMLAttributeTest_210, SetAttributeIntZero_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("zero", 0);
    const XMLAttribute* attr = elem->FindAttribute("zero");
    ASSERT_NE(attr, nullptr);
    int val = -1;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 0);
}

// Test parsing an XML with attributes and reading them
TEST_F(XMLAttributeTest_210, ParseXMLAndReadAttributes_210) {
    const char* xml = "<root attr1=\"value1\" attr2=\"42\" attr3=\"true\" attr4=\"3.14\"/>";
    XMLDocument doc;
    ASSERT_EQ(doc.Parse(xml), XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* a1 = root->FindAttribute("attr1");
    ASSERT_NE(a1, nullptr);
    EXPECT_STREQ(a1->Value(), "value1");

    const XMLAttribute* a2 = root->FindAttribute("attr2");
    ASSERT_NE(a2, nullptr);
    EXPECT_EQ(a2->IntValue(), 42);

    const XMLAttribute* a3 = root->FindAttribute("attr3");
    ASSERT_NE(a3, nullptr);
    EXPECT_TRUE(a3->BoolValue());

    const XMLAttribute* a4 = root->FindAttribute("attr4");
    ASSERT_NE(a4, nullptr);
    EXPECT_NEAR(a4->DoubleValue(), 3.14, 0.001);
}

// Test GetLineNum returns a non-negative value for parsed attributes
TEST_F(XMLAttributeTest_210, GetLineNumReturnsNonNegative_210) {
    const char* xml = "<root attr=\"val\"/>";
    XMLDocument doc;
    ASSERT_EQ(doc.Parse(xml), XML_SUCCESS);
    const XMLAttribute* attr = doc.RootElement()->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 0);
}

// Test QueryInt64Value with non-numeric returns error
TEST_F(XMLAttributeTest_210, QueryInt64ValueNonNumericReturnsError_210) {
    const XMLAttribute* attr = CreateAttribute("name", "notnum");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    EXPECT_NE(attr->QueryInt64Value(&val), XML_SUCCESS);
}

// Test QueryUnsigned64Value with non-numeric returns error
TEST_F(XMLAttributeTest_210, QueryUnsigned64ValueNonNumericReturnsError_210) {
    const XMLAttribute* attr = CreateAttribute("name", "notnum");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    EXPECT_NE(attr->QueryUnsigned64Value(&val), XML_SUCCESS);
}

// Test SetAttribute with double zero
TEST_F(XMLAttributeTest_210, SetAttributeDoubleZero_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("dzero", 0.0);
    const XMLAttribute* attr = elem->FindAttribute("dzero");
    ASSERT_NE(attr, nullptr);
    double val = -1.0;
    EXPECT_EQ(attr->QueryDoubleValue(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 0.0);
}

// Test SetAttribute with very long string value
TEST_F(XMLAttributeTest_210, SetAttributeLongString_210) {
    std::string longStr(1000, 'x');
    XMLElement* elem = CreateElement();
    elem->SetAttribute("longattr", longStr.c_str());
    const XMLAttribute* attr = elem->FindAttribute("longattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), longStr.c_str());
}

// Test multiple attributes iteration
TEST_F(XMLAttributeTest_210, IterateMultipleAttributes_210) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    elem->SetAttribute("c", "3");

    const XMLAttribute* attr = elem->FirstAttribute();
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

// Test QueryIntValue with valid integer string
TEST_F(XMLAttributeTest_210, QueryIntValueWithValidString_210) {
    const XMLAttribute* attr = CreateAttribute("num", "12345");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 12345);
}

// Test QueryBoolValue with "true" string
TEST_F(XMLAttributeTest_210, QueryBoolValueWithTrueString_210) {
    const XMLAttribute* attr = CreateAttribute("b", "true");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

// Test QueryBoolValue with "false" string
TEST_F(XMLAttributeTest_210, QueryBoolValueWithFalseString_210) {
    const XMLAttribute* attr = CreateAttribute("b", "false");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}
