#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper: We cannot directly construct XMLAttribute (private constructor/destructor),
// so we use XMLDocument to create elements with attributes and test through that.

class XMLAttributeTest_218 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        XMLElement* elem = doc.NewElement("test");
        elem->SetAttribute(attrName, attrValue);
        doc.InsertFirstChild(elem);
        return elem;
    }
};

// Test SetAttribute with a string value and verify via Value()
TEST_F(XMLAttributeTest_218, SetAttributeString_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "hello");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");
}

// Test SetAttribute with an empty string
TEST_F(XMLAttributeTest_218, SetAttributeEmptyString_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

// Test SetAttribute overwriting an existing value
TEST_F(XMLAttributeTest_218, SetAttributeOverwrite_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "first");
    elem->SetAttribute("key", "second");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "second");
}

// Test SetAttribute with int value
TEST_F(XMLAttributeTest_218, SetAttributeInt_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("num", 42);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test SetAttribute with negative int value
TEST_F(XMLAttributeTest_218, SetAttributeNegativeInt_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("num", -100);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, -100);
}

// Test SetAttribute with unsigned int value
TEST_F(XMLAttributeTest_218, SetAttributeUnsigned_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("num", (unsigned)4294967295u);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 4294967295u);
}

// Test SetAttribute with int64_t value
TEST_F(XMLAttributeTest_218, SetAttributeInt64_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t bigVal = 9223372036854775807LL;
    elem->SetAttribute("num", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    EXPECT_EQ(attr->QueryInt64Value(&val), XML_SUCCESS);
    EXPECT_EQ(val, bigVal);
    EXPECT_EQ(attr->Int64Value(), bigVal);
}

// Test SetAttribute with uint64_t value
TEST_F(XMLAttributeTest_218, SetAttributeUnsigned64_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetAttribute("num", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    EXPECT_EQ(attr->QueryUnsigned64Value(&val), XML_SUCCESS);
    EXPECT_EQ(val, bigVal);
    EXPECT_EQ(attr->Unsigned64Value(), bigVal);
}

// Test SetAttribute with bool true
TEST_F(XMLAttributeTest_218, SetAttributeBoolTrue_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("flag", true);
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
    EXPECT_TRUE(attr->BoolValue());
}

// Test SetAttribute with bool false
TEST_F(XMLAttributeTest_218, SetAttributeBoolFalse_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("flag", false);
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
    EXPECT_FALSE(attr->BoolValue());
}

// Test SetAttribute with double value
TEST_F(XMLAttributeTest_218, SetAttributeDouble_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 3.14159);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14159);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test SetAttribute with float value
TEST_F(XMLAttributeTest_218, SetAttributeFloat_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    EXPECT_EQ(attr->QueryFloatValue(&val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// Test Name() returns the attribute name
TEST_F(XMLAttributeTest_218, NameReturnsAttributeName_218) {
    XMLElement* elem = CreateElementWithAttribute("myattr", "myvalue");
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Next() to iterate attributes
TEST_F(XMLAttributeTest_218, NextIteratesAttributes_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
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

// Test QueryIntValue with non-numeric string returns error
TEST_F(XMLAttributeTest_218, QueryIntValueNonNumericReturnsError_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "notanumber");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_NE(attr->QueryIntValue(&val), XML_SUCCESS);
}

// Test QueryBoolValue with non-bool string returns error
TEST_F(XMLAttributeTest_218, QueryBoolValueNonBoolReturnsError_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "notabool");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    EXPECT_NE(attr->QueryBoolValue(&val), XML_SUCCESS);
}

// Test QueryDoubleValue with non-numeric string returns error
TEST_F(XMLAttributeTest_218, QueryDoubleValueNonNumericReturnsError_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "abc");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    EXPECT_NE(attr->QueryDoubleValue(&val), XML_SUCCESS);
}

// Test QueryFloatValue with non-numeric string returns error
TEST_F(XMLAttributeTest_218, QueryFloatValueNonNumericReturnsError_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "xyz");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    EXPECT_NE(attr->QueryFloatValue(&val), XML_SUCCESS);
}

// Test QueryUnsignedValue with non-numeric string returns error
TEST_F(XMLAttributeTest_218, QueryUnsignedValueNonNumericReturnsError_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "abc");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    EXPECT_NE(attr->QueryUnsignedValue(&val), XML_SUCCESS);
}

// Test SetAttribute with a very long string
TEST_F(XMLAttributeTest_218, SetAttributeLongString_218) {
    std::string longStr(10000, 'x');
    XMLElement* elem = CreateElementWithAttribute("key", longStr.c_str());
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), longStr.c_str());
}

// Test SetAttribute with special characters
TEST_F(XMLAttributeTest_218, SetAttributeSpecialCharacters_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "hello&world<>\"'");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello&world<>\"'");
}

// Test SetAttribute with zero int
TEST_F(XMLAttributeTest_218, SetAttributeZeroInt_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("num", 0);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 0);
}

// Test SetAttribute with double zero
TEST_F(XMLAttributeTest_218, SetAttributeDoubleZero_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 0.0);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double val = 1.0;
    EXPECT_EQ(attr->QueryDoubleValue(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 0.0);
}

// Test GetLineNum (for attributes parsed from XML)
TEST_F(XMLAttributeTest_218, GetLineNumFromParsedXML_218) {
    const char* xml = "<root attr=\"value\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 1);
}

// Test parsing attribute from XML and reading value
TEST_F(XMLAttributeTest_218, ParsedAttributeValue_218) {
    const char* xml = "<root name=\"tinyxml2\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("name");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "name");
    EXPECT_STREQ(attr->Value(), "tinyxml2");
}

// Test int value parsed from XML
TEST_F(XMLAttributeTest_218, ParsedIntAttribute_218) {
    const char* xml = "<root count=\"123\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("count");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 123);
}

// Test multiple SetAttribute calls on same attribute
TEST_F(XMLAttributeTest_218, MultipleSetAttributeCalls_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", "first");
    elem->SetAttribute("val", 42);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test SetAttribute with negative int64_t
TEST_F(XMLAttributeTest_218, SetAttributeNegativeInt64_218) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t negVal = -9223372036854775807LL;
    elem->SetAttribute("num", negVal);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    EXPECT_EQ(attr->QueryInt64Value(&val), XML_SUCCESS);
    EXPECT_EQ(val, negVal);
}

// Test QueryInt64Value with non-numeric returns error
TEST_F(XMLAttributeTest_218, QueryInt64ValueNonNumericReturnsError_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "abc");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    EXPECT_NE(attr->QueryInt64Value(&val), XML_SUCCESS);
}

// Test QueryUnsigned64Value with non-numeric returns error
TEST_F(XMLAttributeTest_218, QueryUnsigned64ValueNonNumericReturnsError_218) {
    XMLElement* elem = CreateElementWithAttribute("key", "abc");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    EXPECT_NE(attr->QueryUnsigned64Value(&val), XML_SUCCESS);
}
