#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper fixture that provides an XMLDocument for creating elements/attributes
class XMLAttributeTest_69 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an element with a given attribute
    XMLElement* CreateElementWithAttribute(const char* elemName, const char* attrName, const char* attrValue) {
        doc.Clear();
        XMLElement* elem = doc.NewElement(elemName);
        doc.InsertEndChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem;
    }
};

// Test that Name() returns the correct attribute name
TEST_F(XMLAttributeTest_69, Name_ReturnsCorrectName_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "myattr", "value");
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("myattr", attr->Name());
}

// Test that Value() returns the correct attribute value
TEST_F(XMLAttributeTest_69, Value_ReturnsCorrectValue_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "attr", "hello");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("hello", attr->Value());
}

// Test SetAttribute with a string value
TEST_F(XMLAttributeTest_69, SetAttributeString_ChangesValue_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "attr", "old");
    elem->SetAttribute("attr", "new");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("new", attr->Value());
}

// Test IntValue() with a valid integer attribute
TEST_F(XMLAttributeTest_69, IntValue_ReturnsCorrectInt_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "42");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(42, attr->IntValue());
}

// Test IntValue() with negative integer
TEST_F(XMLAttributeTest_69, IntValue_NegativeNumber_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "-100");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(-100, attr->IntValue());
}

// Test UnsignedValue() with a valid unsigned attribute
TEST_F(XMLAttributeTest_69, UnsignedValue_ReturnsCorrectUnsigned_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "4294967295");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(4294967295U, attr->UnsignedValue());
}

// Test Int64Value() with a large int64 value
TEST_F(XMLAttributeTest_69, Int64Value_ReturnsCorrectInt64_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "9223372036854775807");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(INT64_MAX, attr->Int64Value());
}

// Test Unsigned64Value()
TEST_F(XMLAttributeTest_69, Unsigned64Value_ReturnsCorrectUint64_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "18446744073709551615");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(UINT64_MAX, attr->Unsigned64Value());
}

// Test BoolValue() with "true"
TEST_F(XMLAttributeTest_69, BoolValue_TrueString_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "true");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(nullptr, attr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test BoolValue() with "false"
TEST_F(XMLAttributeTest_69, BoolValue_FalseString_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "false");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(nullptr, attr);
    EXPECT_FALSE(attr->BoolValue());
}

// Test DoubleValue()
TEST_F(XMLAttributeTest_69, DoubleValue_ReturnsCorrectDouble_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "3.14159");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    EXPECT_DOUBLE_EQ(3.14159, attr->DoubleValue());
}

// Test FloatValue()
TEST_F(XMLAttributeTest_69, FloatValue_ReturnsCorrectFloat_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "2.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    EXPECT_FLOAT_EQ(2.5f, attr->FloatValue());
}

// Test QueryIntValue with valid integer
TEST_F(XMLAttributeTest_69, QueryIntValue_ValidInt_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "123");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, attr->QueryIntValue(&val));
    EXPECT_EQ(123, val);
}

// Test QueryIntValue with non-integer string
TEST_F(XMLAttributeTest_69, QueryIntValue_InvalidString_ReturnsError_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "abc");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    int val = 0;
    EXPECT_NE(XML_SUCCESS, attr->QueryIntValue(&val));
}

// Test QueryUnsignedValue with valid value
TEST_F(XMLAttributeTest_69, QueryUnsignedValue_Valid_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "456");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    unsigned int val = 0;
    EXPECT_EQ(XML_SUCCESS, attr->QueryUnsignedValue(&val));
    EXPECT_EQ(456U, val);
}

// Test QueryUnsignedValue with invalid string
TEST_F(XMLAttributeTest_69, QueryUnsignedValue_Invalid_ReturnsError_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "xyz");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    unsigned int val = 0;
    EXPECT_NE(XML_SUCCESS, attr->QueryUnsignedValue(&val));
}

// Test QueryInt64Value with valid value
TEST_F(XMLAttributeTest_69, QueryInt64Value_Valid_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "123456789012345");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    int64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, attr->QueryInt64Value(&val));
    EXPECT_EQ(123456789012345LL, val);
}

// Test QueryInt64Value with invalid string
TEST_F(XMLAttributeTest_69, QueryInt64Value_Invalid_ReturnsError_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "notanumber");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    int64_t val = 0;
    EXPECT_NE(XML_SUCCESS, attr->QueryInt64Value(&val));
}

// Test QueryUnsigned64Value with valid value
TEST_F(XMLAttributeTest_69, QueryUnsigned64Value_Valid_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "18446744073709551615");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    uint64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, attr->QueryUnsigned64Value(&val));
    EXPECT_EQ(UINT64_MAX, val);
}

// Test QueryBoolValue with "true"
TEST_F(XMLAttributeTest_69, QueryBoolValue_True_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "true");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(nullptr, attr);
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, attr->QueryBoolValue(&val));
    EXPECT_TRUE(val);
}

// Test QueryBoolValue with "false"
TEST_F(XMLAttributeTest_69, QueryBoolValue_False_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "false");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(nullptr, attr);
    bool val = true;
    EXPECT_EQ(XML_SUCCESS, attr->QueryBoolValue(&val));
    EXPECT_FALSE(val);
}

// Test QueryBoolValue with invalid string
TEST_F(XMLAttributeTest_69, QueryBoolValue_Invalid_ReturnsError_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "maybe");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(nullptr, attr);
    bool val = false;
    EXPECT_NE(XML_SUCCESS, attr->QueryBoolValue(&val));
}

// Test QueryDoubleValue with valid value
TEST_F(XMLAttributeTest_69, QueryDoubleValue_Valid_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "1.23456789");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, attr->QueryDoubleValue(&val));
    EXPECT_DOUBLE_EQ(1.23456789, val);
}

// Test QueryDoubleValue with invalid string
TEST_F(XMLAttributeTest_69, QueryDoubleValue_Invalid_ReturnsError_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "notadouble");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    double val = 0.0;
    EXPECT_NE(XML_SUCCESS, attr->QueryDoubleValue(&val));
}

// Test QueryFloatValue with valid value
TEST_F(XMLAttributeTest_69, QueryFloatValue_Valid_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "9.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, attr->QueryFloatValue(&val));
    EXPECT_FLOAT_EQ(9.5f, val);
}

// Test QueryFloatValue with invalid string
TEST_F(XMLAttributeTest_69, QueryFloatValue_Invalid_ReturnsError_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "notafloat");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    float val = 0.0f;
    EXPECT_NE(XML_SUCCESS, attr->QueryFloatValue(&val));
}

// Test Next() returns the next attribute
TEST_F(XMLAttributeTest_69, Next_ReturnsNextAttribute_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("first", attr->Name());

    const XMLAttribute* next = attr->Next();
    ASSERT_NE(nullptr, next);
    EXPECT_STREQ("second", next->Name());
}

// Test Next() returns nullptr when there is no next attribute
TEST_F(XMLAttributeTest_69, Next_ReturnsNullWhenNoNext_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "only", "1");
    const XMLAttribute* attr = elem->FindAttribute("only");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(nullptr, attr->Next());
}

// Test SetAttribute with int value
TEST_F(XMLAttributeTest_69, SetAttributeInt_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", 99);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(99, attr->IntValue());
}

// Test SetAttribute with unsigned int value
TEST_F(XMLAttributeTest_69, SetAttributeUnsigned_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", 4000000000U);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(4000000000U, attr->UnsignedValue());
}

// Test SetAttribute with int64_t value
TEST_F(XMLAttributeTest_69, SetAttributeInt64_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", (int64_t)123456789012345LL);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(123456789012345LL, attr->Int64Value());
}

// Test SetAttribute with uint64_t value
TEST_F(XMLAttributeTest_69, SetAttributeUint64_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", (uint64_t)18446744073709551615ULL);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(UINT64_MAX, attr->Unsigned64Value());
}

// Test SetAttribute with bool value true
TEST_F(XMLAttributeTest_69, SetAttributeBoolTrue_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("flag", true);
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(nullptr, attr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test SetAttribute with bool value false
TEST_F(XMLAttributeTest_69, SetAttributeBoolFalse_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("flag", false);
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(nullptr, attr);
    EXPECT_FALSE(attr->BoolValue());
}

// Test SetAttribute with double value
TEST_F(XMLAttributeTest_69, SetAttributeDouble_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("val", 3.14);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    EXPECT_NEAR(3.14, attr->DoubleValue(), 0.001);
}

// Test SetAttribute with float value
TEST_F(XMLAttributeTest_69, SetAttributeFloat_SetsCorrectValue_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("val", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    EXPECT_FLOAT_EQ(2.5f, attr->FloatValue());
}

// Test GetLineNum() on a parsed document
TEST_F(XMLAttributeTest_69, GetLineNum_ReturnsLineNumber_69) {
    const char* xml = "<root attr=\"value\"/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(nullptr, attr);
    // For a single-line document, the line number should be 1
    EXPECT_EQ(1, attr->GetLineNum());
}

// Test GetLineNum with multiline XML
TEST_F(XMLAttributeTest_69, GetLineNum_MultiLine_69) {
    const char* xml =
        "<root\n"
        "  attr1=\"val1\"\n"
        "  attr2=\"val2\"\n"
        "/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);

    const XMLAttribute* attr1 = root->FindAttribute("attr1");
    ASSERT_NE(nullptr, attr1);
    EXPECT_EQ(2, attr1->GetLineNum());

    const XMLAttribute* attr2 = root->FindAttribute("attr2");
    ASSERT_NE(nullptr, attr2);
    EXPECT_EQ(3, attr2->GetLineNum());
}

// Test empty string attribute value
TEST_F(XMLAttributeTest_69, EmptyStringValue_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "empty", "");
    const XMLAttribute* attr = elem->FindAttribute("empty");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("", attr->Value());
}

// Test attribute value with zero integer
TEST_F(XMLAttributeTest_69, IntValue_Zero_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "0");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(0, attr->IntValue());
}

// Test QueryIntValue with zero
TEST_F(XMLAttributeTest_69, QueryIntValue_Zero_ReturnsSuccess_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "0");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    int val = -1;
    EXPECT_EQ(XML_SUCCESS, attr->QueryIntValue(&val));
    EXPECT_EQ(0, val);
}

// Test multiple attributes on one element and iteration
TEST_F(XMLAttributeTest_69, MultipleAttributes_Iteration_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    elem->SetAttribute("c", "3");

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("a", attr->Name());

    attr = attr->Next();
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("b", attr->Name());

    attr = attr->Next();
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("c", attr->Name());

    attr = attr->Next();
    EXPECT_EQ(nullptr, attr);
}

// Test parsing attributes from XML string
TEST_F(XMLAttributeTest_69, ParsedAttributes_CorrectValues_69) {
    const char* xml = R"(<item name="widget" count="5" enabled="true" ratio="0.75"/>)";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLElement* elem = doc.RootElement();
    ASSERT_NE(nullptr, elem);

    const XMLAttribute* nameAttr = elem->FindAttribute("name");
    ASSERT_NE(nullptr, nameAttr);
    EXPECT_STREQ("widget", nameAttr->Value());

    const XMLAttribute* countAttr = elem->FindAttribute("count");
    ASSERT_NE(nullptr, countAttr);
    EXPECT_EQ(5, countAttr->IntValue());

    const XMLAttribute* enabledAttr = elem->FindAttribute("enabled");
    ASSERT_NE(nullptr, enabledAttr);
    EXPECT_TRUE(enabledAttr->BoolValue());

    const XMLAttribute* ratioAttr = elem->FindAttribute("ratio");
    ASSERT_NE(nullptr, ratioAttr);
    EXPECT_DOUBLE_EQ(0.75, ratioAttr->DoubleValue());
}

// Test that overwriting an attribute value preserves the attribute name
TEST_F(XMLAttributeTest_69, OverwriteAttribute_PreservesName_69) {
    doc.Clear();
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "oldval");
    elem->SetAttribute("key", "newval");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("key", attr->Name());
    EXPECT_STREQ("newval", attr->Value());
}

// Test negative int64 value
TEST_F(XMLAttributeTest_69, Int64Value_Negative_69) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "-9223372036854775808");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(INT64_MIN, attr->Int64Value());
}

// Test special characters in attribute value
TEST_F(XMLAttributeTest_69, SpecialCharsInValue_69) {
    const char* xml = R"(<item desc="Hello &amp; World"/>)";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(nullptr, elem);
    const XMLAttribute* attr = elem->FindAttribute("desc");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("Hello & World", attr->Value());
}
