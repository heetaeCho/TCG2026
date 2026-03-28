#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_93 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== QueryAttribute (bool overload) ====================

TEST_F(XMLElementTest_93, QueryBoolAttributeTrue_93) {
    doc.Parse("<root attr=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = false;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_93, QueryBoolAttributeFalse_93) {
    doc.Parse("<root attr=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = true;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_93, QueryBoolAttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = true;
    XMLError err = elem->QueryAttribute("nonexistent", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_TRUE(value); // unchanged
}

TEST_F(XMLElementTest_93, QueryBoolAttributeWrongType_93) {
    doc.Parse("<root attr=\"notabool\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = true;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLElementTest_93, QueryBoolAttribute1AsTrue_93) {
    doc.Parse("<root attr=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = false;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_93, QueryBoolAttribute0AsFalse_93) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = true;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// ==================== QueryAttribute (int overload) ====================

TEST_F(XMLElementTest_93, QueryIntAttributeNormal_93) {
    doc.Parse("<root attr=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int value = 0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementTest_93, QueryIntAttributeNegative_93) {
    doc.Parse("<root attr=\"-100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int value = 0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -100);
}

TEST_F(XMLElementTest_93, QueryIntAttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int value = 99;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 99);
}

TEST_F(XMLElementTest_93, QueryIntAttributeWrongType_93) {
    doc.Parse("<root attr=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int value = 0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryAttribute (unsigned int overload) ====================

TEST_F(XMLElementTest_93, QueryUnsignedAttributeNormal_93) {
    doc.Parse("<root attr=\"123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 123u);
}

TEST_F(XMLElementTest_93, QueryUnsignedAttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned int value = 55;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 55u);
}

// ==================== QueryAttribute (int64_t overload) ====================

TEST_F(XMLElementTest_93, QueryInt64AttributeNormal_93) {
    doc.Parse("<root attr=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_93, QueryInt64AttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t value = 77;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 77);
}

// ==================== QueryAttribute (uint64_t overload) ====================

TEST_F(XMLElementTest_93, QueryUnsigned64AttributeNormal_93) {
    doc.Parse("<root attr=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_93, QueryUnsigned64AttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t value = 88;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 88u);
}

// ==================== QueryAttribute (double overload) ====================

TEST_F(XMLElementTest_93, QueryDoubleAttributeNormal_93) {
    doc.Parse("<root attr=\"3.14159\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double value = 0.0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14159);
}

TEST_F(XMLElementTest_93, QueryDoubleAttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double value = 1.5;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_DOUBLE_EQ(value, 1.5);
}

TEST_F(XMLElementTest_93, QueryDoubleAttributeWrongType_93) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double value = 0.0;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryAttribute (float overload) ====================

TEST_F(XMLElementTest_93, QueryFloatAttributeNormal_93) {
    doc.Parse("<root attr=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float value = 0.0f;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

TEST_F(XMLElementTest_93, QueryFloatAttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float value = 7.7f;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_FLOAT_EQ(value, 7.7f);
}

// ==================== QueryAttribute (const char** overload) ====================

TEST_F(XMLElementTest_93, QueryStringAttributeNormal_93) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "hello");
}

TEST_F(XMLElementTest_93, QueryStringAttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, nullptr);
}

// ==================== SetAttribute / Attribute ====================

TEST_F(XMLElementTest_93, SetAndGetStringAttribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("name", "value");
    EXPECT_STREQ(elem->Attribute("name"), "value");
}

TEST_F(XMLElementTest_93, SetAndGetIntAttribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(elem->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_93, SetAndGetUnsignedAttribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("unum", 99u);
    EXPECT_EQ(elem->UnsignedAttribute("unum", 0), 99u);
}

TEST_F(XMLElementTest_93, SetAndGetInt64Attribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t big = INT64_C(9223372036854775807);
    elem->SetAttribute("big", big);
    EXPECT_EQ(elem->Int64Attribute("big", 0), big);
}

TEST_F(XMLElementTest_93, SetAndGetUnsigned64Attribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t ubig = UINT64_C(18446744073709551615);
    elem->SetAttribute("ubig", ubig);
    EXPECT_EQ(elem->Unsigned64Attribute("ubig", 0), ubig);
}

TEST_F(XMLElementTest_93, SetAndGetBoolAttribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_93, SetAndGetDoubleAttribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("dval", 3.14);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("dval", 0.0), 3.14);
}

TEST_F(XMLElementTest_93, SetAndGetFloatAttribute_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("fval", 1.5f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("fval", 0.0f), 1.5f);
}

// ==================== Default attribute values ====================

TEST_F(XMLElementTest_93, IntAttributeDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("missing", 999), 999);
}

TEST_F(XMLElementTest_93, UnsignedAttributeDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("missing", 888u), 888u);
}

TEST_F(XMLElementTest_93, BoolAttributeDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_93, DoubleAttributeDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 2.718), 2.718);
}

TEST_F(XMLElementTest_93, FloatAttributeDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 1.1f), 1.1f);
}

TEST_F(XMLElementTest_93, Int64AttributeDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("missing", 12345), 12345);
}

TEST_F(XMLElementTest_93, Unsigned64AttributeDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("missing", 54321u), 54321u);
}

// ==================== Attribute (string matching) ====================

TEST_F(XMLElementTest_93, AttributeMatchesValue_93) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr", "hello"), "hello");
}

TEST_F(XMLElementTest_93, AttributeDoesNotMatchValue_93) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("attr", "world"), nullptr);
}

TEST_F(XMLElementTest_93, AttributeNoValueFilter_93) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr"), "hello");
}

TEST_F(XMLElementTest_93, AttributeNotFound_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("missing"), nullptr);
}

// ==================== FindAttribute ====================

TEST_F(XMLElementTest_93, FindAttributeExists_93) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr");
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_93, FindAttributeNotExists_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("missing");
    EXPECT_EQ(attr, nullptr);
}

// ==================== FirstAttribute ====================

TEST_F(XMLElementTest_93, FirstAttributeExists_93) {
    doc.Parse("<root first=\"1\" second=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
}

TEST_F(XMLElementTest_93, FirstAttributeEmpty_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

// ==================== DeleteAttribute ====================

TEST_F(XMLElementTest_93, DeleteAttributeExisting_93) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("attr");
    EXPECT_EQ(elem->FindAttribute("attr"), nullptr);
}

TEST_F(XMLElementTest_93, DeleteAttributeNonExisting_93) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_NE(elem->FindAttribute("attr"), nullptr);
}

// ==================== Name / SetName ====================

TEST_F(XMLElementTest_93, GetName_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "root");
}

TEST_F(XMLElementTest_93, SetName_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newname");
    EXPECT_STREQ(elem->Name(), "newname");
}

// ==================== GetText / SetText ====================

TEST_F(XMLElementTest_93, GetTextNormal_93) {
    doc.Parse("<root>Hello</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Hello");
}

TEST_F(XMLElementTest_93, GetTextEmpty_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_93, SetTextString_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("World");
    EXPECT_STREQ(elem->GetText(), "World");
}

TEST_F(XMLElementTest_93, SetTextInt_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_93, SetTextUnsigned_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(99u);
    EXPECT_STREQ(elem->GetText(), "99");
}

TEST_F(XMLElementTest_93, SetTextBoolTrue_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_93, SetTextBoolFalse_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(false);
    EXPECT_STREQ(elem->GetText(), "false");
}

TEST_F(XMLElementTest_93, SetTextInt64_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(INT64_C(9223372036854775807));
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_93, SetTextUint64_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(UINT64_C(18446744073709551615));
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_93, SetTextDouble_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(XMLElementTest_93, SetTextFloat_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

// ==================== QueryIntText / QueryUnsignedText etc. ====================

TEST_F(XMLElementTest_93, QueryIntTextNormal_93) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_93, QueryIntTextNoText_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_NO_TEXT_NODE);
}

TEST_F(XMLElementTest_93, QueryIntTextWrongType_93) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(XMLElementTest_93, QueryUnsignedTextNormal_93) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    EXPECT_EQ(elem->QueryUnsignedText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_93, QueryBoolTextTrue_93) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_93, QueryBoolTextFalse_93) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_93, QueryDoubleTextNormal_93) {
    doc.Parse("<root>2.718</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    EXPECT_EQ(elem->QueryDoubleText(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 2.718);
}

TEST_F(XMLElementTest_93, QueryFloatTextNormal_93) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    EXPECT_EQ(elem->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

// ==================== IntText / UnsignedText / BoolText etc. (with defaults) ====================

TEST_F(XMLElementTest_93, IntTextWithValue_93) {
    doc.Parse("<root>50</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 50);
}

TEST_F(XMLElementTest_93, IntTextDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(999), 999);
}

TEST_F(XMLElementTest_93, UnsignedTextWithValue_93) {
    doc.Parse("<root>200</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(0), 200u);
}

TEST_F(XMLElementTest_93, UnsignedTextDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(777u), 777u);
}

TEST_F(XMLElementTest_93, BoolTextWithValue_93) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_93, BoolTextDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_93, DoubleTextWithValue_93) {
    doc.Parse("<root>1.23</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), 1.23);
}

TEST_F(XMLElementTest_93, DoubleTextDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(9.99), 9.99);
}

TEST_F(XMLElementTest_93, FloatTextWithValue_93) {
    doc.Parse("<root>4.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(0.0f), 4.5f);
}

TEST_F(XMLElementTest_93, FloatTextDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(8.8f), 8.8f);
}

TEST_F(XMLElementTest_93, Int64TextWithValue_93) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(0), INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_93, Int64TextDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(12345), 12345);
}

TEST_F(XMLElementTest_93, Unsigned64TextWithValue_93) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(0), UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_93, Unsigned64TextDefault_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(54321u), 54321u);
}

// ==================== InsertNewChildElement ====================

TEST_F(XMLElementTest_93, InsertNewChildElement_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(child->Parent(), elem);
}

// ==================== InsertNewComment ====================

TEST_F(XMLElementTest_93, InsertNewComment_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "a comment");
}

// ==================== InsertNewText ====================

TEST_F(XMLElementTest_93, InsertNewText_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

// ==================== InsertNewDeclaration ====================

TEST_F(XMLElementTest_93, InsertNewDeclaration_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

// ==================== InsertNewUnknown ====================

TEST_F(XMLElementTest_93, InsertNewUnknown_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ToElement ====================

TEST_F(XMLElementTest_93, ToElement_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== ShallowClone / ShallowEqual ====================

TEST_F(XMLElementTest_93, ShallowClone_93) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);
    XMLElement* clonedElem = clone->ToElement();
    ASSERT_NE(clonedElem, nullptr);
    EXPECT_STREQ(clonedElem->Name(), "root");
    EXPECT_STREQ(clonedElem->Attribute("attr"), "val");
}

TEST_F(XMLElementTest_93, ShallowEqualSame_93) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_93, ShallowEqualDifferentName_93) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_93, ShallowEqualDifferentAttribute_93) {
    doc.Parse("<root attr=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== Multiple attributes ====================

TEST_F(XMLElementTest_93, MultipleAttributes_93) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_EQ(elem->IntAttribute("b", 0), 2);
    EXPECT_EQ(elem->IntAttribute("c", 0), 3);
}

TEST_F(XMLElementTest_93, OverwriteAttribute_93) {
    doc.Parse("<root attr=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("attr", "new");
    EXPECT_STREQ(elem->Attribute("attr"), "new");
}

// ==================== ClosingType ====================

TEST_F(XMLElementTest_93, ClosingTypeOpen_93) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // OPEN is 0
    EXPECT_EQ(elem->ClosingType(), XMLElement::OPEN);
}

// ==================== Edge cases ====================

TEST_F(XMLElementTest_93