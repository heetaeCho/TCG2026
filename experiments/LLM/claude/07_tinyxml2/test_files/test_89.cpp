#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_89 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== QueryAttribute (int) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeInt_ExistingAttribute_89) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(42, value);
}

TEST_F(XMLElementTest_89, QueryAttributeInt_NonExistingAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    int value = -1;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
    EXPECT_EQ(-1, value);
}

TEST_F(XMLElementTest_89, QueryAttributeInt_NonIntegerValue_89) {
    doc.Parse("<root val=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    int value = -1;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementTest_89, QueryAttributeInt_NegativeValue_89) {
    doc.Parse("<root val=\"-100\"/>");
    XMLElement* elem = doc.RootElement();
    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(-100, value);
}

TEST_F(XMLElementTest_89, QueryAttributeInt_ZeroValue_89) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    int value = 99;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(0, value);
}

// ==================== QueryAttribute (unsigned int) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeUnsigned_ExistingAttribute_89) {
    doc.Parse("<root val=\"100\"/>");
    XMLElement* elem = doc.RootElement();
    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(100u, value);
}

TEST_F(XMLElementTest_89, QueryAttributeUnsigned_NonExisting_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (int64_t) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeInt64_ExistingAttribute_89) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(INT64_C(9223372036854775807), value);
}

TEST_F(XMLElementTest_89, QueryAttributeInt64_NonExisting_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (uint64_t) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeUnsigned64_ExistingAttribute_89) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(UINT64_C(18446744073709551615), value);
}

TEST_F(XMLElementTest_89, QueryAttributeUnsigned64_NonExisting_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (bool) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeBool_TrueValue_89) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_89, QueryAttributeBool_FalseValue_89) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    bool value = true;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_89, QueryAttributeBool_NonExisting_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    bool value = true;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (double) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeDouble_ExistingAttribute_89) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* elem = doc.RootElement();
    double value = 0.0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(3.14159, value);
}

TEST_F(XMLElementTest_89, QueryAttributeDouble_NonExisting_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    double value = 0.0;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (float) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeFloat_ExistingAttribute_89) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(2.5f, value);
}

TEST_F(XMLElementTest_89, QueryAttributeFloat_NonExisting_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    float value = 0.0f;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (const char*) Tests ====================

TEST_F(XMLElementTest_89, QueryAttributeString_ExistingAttribute_89) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_STREQ("hello", value);
}

TEST_F(XMLElementTest_89, QueryAttributeString_NonExisting_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== SetAttribute / QueryAttribute Round-Trip Tests ====================

TEST_F(XMLElementTest_89, SetAndQueryIntAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("myint", 12345);
    int value = 0;
    XMLError err = elem->QueryAttribute("myint", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(12345, value);
}

TEST_F(XMLElementTest_89, SetAndQueryUnsignedAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("myuint", 4294967295u);
    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("myuint", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(4294967295u, value);
}

TEST_F(XMLElementTest_89, SetAndQueryInt64Attribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("myint64", INT64_C(9223372036854775807));
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("myint64", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(INT64_C(9223372036854775807), value);
}

TEST_F(XMLElementTest_89, SetAndQueryBoolAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("mybool", true);
    bool value = false;
    XMLError err = elem->QueryAttribute("mybool", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_89, SetAndQueryDoubleAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("mydouble", 1.23456789);
    double value = 0.0;
    XMLError err = elem->QueryAttribute("mydouble", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(1.23456789, value);
}

TEST_F(XMLElementTest_89, SetAndQueryFloatAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("myfloat", 1.5f);
    float value = 0.0f;
    XMLError err = elem->QueryAttribute("myfloat", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(1.5f, value);
}

TEST_F(XMLElementTest_89, SetAndQueryStringAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("mystr", "world");
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("mystr", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_STREQ("world", value);
}

// ==================== IntAttribute with default value Tests ====================

TEST_F(XMLElementTest_89, IntAttribute_ExistingAttribute_89) {
    doc.Parse("<root val=\"77\"/>");
    XMLElement* elem = doc.RootElement();
    int value = elem->IntAttribute("val", -1);
    EXPECT_EQ(77, value);
}

TEST_F(XMLElementTest_89, IntAttribute_NonExistingReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    int value = elem->IntAttribute("missing", -999);
    EXPECT_EQ(-999, value);
}

// ==================== UnsignedAttribute with default Tests ====================

TEST_F(XMLElementTest_89, UnsignedAttribute_ExistingAttribute_89) {
    doc.Parse("<root val=\"255\"/>");
    XMLElement* elem = doc.RootElement();
    unsigned int value = elem->UnsignedAttribute("val", 0);
    EXPECT_EQ(255u, value);
}

TEST_F(XMLElementTest_89, UnsignedAttribute_NonExistingReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    unsigned int value = elem->UnsignedAttribute("missing", 999);
    EXPECT_EQ(999u, value);
}

// ==================== BoolAttribute with default Tests ====================

TEST_F(XMLElementTest_89, BoolAttribute_ExistingAttribute_89) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    bool value = elem->BoolAttribute("val", false);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_89, BoolAttribute_NonExistingReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    bool value = elem->BoolAttribute("missing", true);
    EXPECT_TRUE(value);
}

// ==================== DoubleAttribute with default Tests ====================

TEST_F(XMLElementTest_89, DoubleAttribute_ExistingAttribute_89) {
    doc.Parse("<root val=\"2.71828\"/>");
    XMLElement* elem = doc.RootElement();
    double value = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(2.71828, value);
}

TEST_F(XMLElementTest_89, DoubleAttribute_NonExistingReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    double value = elem->DoubleAttribute("missing", 1.11);
    EXPECT_DOUBLE_EQ(1.11, value);
}

// ==================== FloatAttribute with default Tests ====================

TEST_F(XMLElementTest_89, FloatAttribute_ExistingAttribute_89) {
    doc.Parse("<root val=\"1.5\"/>");
    XMLElement* elem = doc.RootElement();
    float value = elem->FloatAttribute("val", 0.0f);
    EXPECT_FLOAT_EQ(1.5f, value);
}

TEST_F(XMLElementTest_89, FloatAttribute_NonExistingReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    float value = elem->FloatAttribute("missing", 9.9f);
    EXPECT_FLOAT_EQ(9.9f, value);
}

// ==================== Int64Attribute with default Tests ====================

TEST_F(XMLElementTest_89, Int64Attribute_ExistingAttribute_89) {
    doc.Parse("<root val=\"123456789012345\"/>");
    XMLElement* elem = doc.RootElement();
    int64_t value = elem->Int64Attribute("val", 0);
    EXPECT_EQ(INT64_C(123456789012345), value);
}

TEST_F(XMLElementTest_89, Int64Attribute_NonExistingReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    int64_t value = elem->Int64Attribute("missing", -42);
    EXPECT_EQ(-42, value);
}

// ==================== Unsigned64Attribute with default Tests ====================

TEST_F(XMLElementTest_89, Unsigned64Attribute_ExistingAttribute_89) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    uint64_t value = elem->Unsigned64Attribute("val", 0);
    EXPECT_EQ(UINT64_C(18446744073709551615), value);
}

TEST_F(XMLElementTest_89, Unsigned64Attribute_NonExistingReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    uint64_t value = elem->Unsigned64Attribute("missing", 12345);
    EXPECT_EQ(12345u, value);
}

// ==================== Attribute (string lookup) Tests ====================

TEST_F(XMLElementTest_89, Attribute_ExistingReturnsValue_89) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    const char* val = elem->Attribute("name");
    ASSERT_NE(nullptr, val);
    EXPECT_STREQ("hello", val);
}

TEST_F(XMLElementTest_89, Attribute_NonExistingReturnsNull_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    const char* val = elem->Attribute("missing");
    EXPECT_EQ(nullptr, val);
}

TEST_F(XMLElementTest_89, Attribute_WithExpectedValueMatching_89) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    const char* val = elem->Attribute("name", "hello");
    ASSERT_NE(nullptr, val);
    EXPECT_STREQ("hello", val);
}

TEST_F(XMLElementTest_89, Attribute_WithExpectedValueNotMatching_89) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    const char* val = elem->Attribute("name", "world");
    EXPECT_EQ(nullptr, val);
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_89, FindAttribute_ExistingAttribute_89) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("attr", attr->Name());
    EXPECT_STREQ("value", attr->Value());
}

TEST_F(XMLElementTest_89, FindAttribute_NonExistingAttribute_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    const XMLAttribute* attr = elem->FindAttribute("missing");
    EXPECT_EQ(nullptr, attr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_89, FirstAttribute_NoAttributes_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_EQ(nullptr, attr);
}

TEST_F(XMLElementTest_89, FirstAttribute_WithAttributes_89) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("a", attr->Name());
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_89, DeleteAttribute_ExistingAttribute_89) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    elem->DeleteAttribute("a");
    const XMLAttribute* attr = elem->FindAttribute("a");
    EXPECT_EQ(nullptr, attr);
    // b should still exist
    attr = elem->FindAttribute("b");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("2", attr->Value());
}

TEST_F(XMLElementTest_89, DeleteAttribute_NonExisting_89) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    // Should not crash
    elem->DeleteAttribute("missing");
    const XMLAttribute* attr = elem->FindAttribute("a");
    ASSERT_NE(nullptr, attr);
}

// ==================== GetText / SetText Tests ====================

TEST_F(XMLElementTest_89, GetText_WithTextContent_89) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* elem = doc.RootElement();
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Hello World", text);
}

TEST_F(XMLElementTest_89, GetText_NoTextContent_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    const char* text = elem->GetText();
    EXPECT_EQ(nullptr, text);
}

TEST_F(XMLElementTest_89, SetText_String_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetText("New Text");
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("New Text", text);
}

TEST_F(XMLElementTest_89, SetText_Int_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetText(42);
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("42", text);
}

TEST_F(XMLElementTest_89, SetText_UnsignedInt_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetText(100u);
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("100", text);
}

TEST_F(XMLElementTest_89, SetText_Bool_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetText(true);
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("true", text);
}

TEST_F(XMLElementTest_89, SetText_Int64_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetText(INT64_C(123456789012345));
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("123456789012345", text);
}

TEST_F(XMLElementTest_89, SetText_Uint64_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetText(UINT64_C(18446744073709551615));
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("18446744073709551615", text);
}

// ==================== QueryIntText Tests ====================

TEST_F(XMLElementTest_89, QueryIntText_ValidInt_89) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(42, value);
}

TEST_F(XMLElementTest_89, QueryIntText_NoText_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    int value = -1;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementTest_89, QueryIntText_InvalidText_89) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    int value = -1;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_NE(XML_SUCCESS, err);
}

// ==================== QueryUnsignedText Tests ====================

TEST_F(XMLElementTest_89, QueryUnsignedText_ValidUnsigned_89) {
    doc.Parse("<root>255</root>");
    XMLElement* elem = doc.RootElement();
    unsigned int value = 0;
    XMLError err = elem->QueryUnsignedText(&value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(255u, value);
}

// ==================== QueryBoolText Tests ====================

TEST_F(XMLElementTest_89, QueryBoolText_True_89) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    bool value = false;
    XMLError err = elem->QueryBoolText(&value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_89, QueryBoolText_False_89) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    bool value = true;
    XMLError err = elem->QueryBoolText(&value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(value);
}

// ==================== QueryDoubleText Tests ====================

TEST_F(XMLElementTest_89, QueryDoubleText_Valid_89) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    double value = 0.0;
    XMLError err = elem->QueryDoubleText(&value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(3.14, value);
}

// ==================== QueryFloatText Tests ====================

TEST_F(XMLElementTest_89, QueryFloatText_Valid_89) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    float value = 0.0f;
    XMLError err = elem->QueryFloatText(&value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(2.5f, value);
}

// ==================== IntText with default Tests ====================

TEST_F(XMLElementTest_89, IntText_ValidText_89) {
    doc.Parse("<root>77</root>");
    XMLElement* elem = doc.RootElement();
    int value = elem->IntText(0);
    EXPECT_EQ(77, value);
}

TEST_F(XMLElementTest_89, IntText_NoTextReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    int value = elem->IntText(-1);
    EXPECT_EQ(-1, value);
}

// ==================== UnsignedText with default Tests ====================

TEST_F(XMLElementTest_89, UnsignedText_ValidText_89) {
    doc.Parse("<root>255</root>");
    XMLElement* elem = doc.RootElement();
    unsigned int value = elem->UnsignedText(0);
    EXPECT_EQ(255u, value);
}

TEST_F(XMLElementTest_89, UnsignedText_NoTextReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    unsigned int value = elem->UnsignedText(999);
    EXPECT_EQ(999u, value);
}

// ==================== BoolText with default Tests ====================

TEST_F(XMLElementTest_89, BoolText_ValidText_89) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    bool value = elem->BoolText(false);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_89, BoolText_NoTextReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    bool value = elem->BoolText(true);
    EXPECT_TRUE(value);
}

// ==================== DoubleText with default Tests ====================

TEST_F(XMLElementTest_89, DoubleText_ValidText_89) {
    doc.Parse("<root>2.71828</root>");
    XMLElement* elem = doc.RootElement();
    double value = elem->DoubleText(0.0);
    EXPECT_DOUBLE_EQ(2.71828, value);
}

TEST_F(XMLElementTest_89, DoubleText_NoTextReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    double value = elem->DoubleText(1.11);
    EXPECT_DOUBLE_EQ(1.11, value);
}

// ==================== FloatText with default Tests ====================

TEST_F(XMLElementTest_89, FloatText_ValidText_89) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    float value = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(1.5f, value);
}

TEST_F(XMLElementTest_89, FloatText_NoTextReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    float value = elem->FloatText(9.9f);
    EXPECT_FLOAT_EQ(9.9f, value);
}

// ==================== Int64Text with default Tests ====================

TEST_F(XMLElementTest_89, Int64Text_ValidText_89) {
    doc.Parse("<root>123456789012345</root>");
    XMLElement* elem = doc.RootElement();
    int64_t value = elem->Int64Text(0);
    EXPECT_EQ(INT64_C(123456789012345), value);
}

TEST_F(XMLElementTest_89, Int64Text_NoTextReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    int64_t value = elem->Int64Text(-42);
    EXPECT_EQ(-42, value);
}

// ==================== Unsigned64Text with default Tests ====================

TEST_F(XMLElementTest_89, Unsigned64Text_ValidText_89) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    uint64_t value = elem->Unsigned64Text(0);
    EXPECT_EQ(UINT64_C(18446744073709551615), value);
}

TEST_F(XMLElementTest_89, Unsigned64Text_NoTextReturnsDefault_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    uint64_t value = elem->Unsigned64Text(12345);
    EXPECT_EQ(12345u, value);
}

// ==================== Name / SetName Tests ====================

TEST_F(XMLElementTest_89, Name_ReturnsElementName_89) {
    doc.Parse("<myelem/>");
    XMLElement* elem = doc.RootElement();
    EXPECT_STREQ("myelem", elem->Name());
}

TEST_F(XMLElementTest_89, SetName_ChangesElementName_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    elem->SetName("newname");
    EXPECT_STREQ("newname", elem->Name());
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_89, ToElement_ReturnsSelf_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    EXPECT_EQ(elem, elem->ToElement());
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_89, InsertNewChildElement_CreatesChild_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
    EXPECT_EQ(child, elem->FirstChildElement("child"));
}

// ==================== InsertNewComment Tests ====================

TEST_F(XMLElementTest_89, InsertNewComment_CreatesComment_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    XMLComment* comment = elem->InsertNewComment("This is a comment");
    ASSERT_NE(nullptr, comment);
}

// ==================== InsertNewText Tests ====================

TEST_F(XMLElementTest_89, InsertNewText_CreatesTextNode_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    XMLText* text = elem->InsertNewText("Some text");
    ASSERT_NE(nullptr, text);
    const char* got = elem->GetText();
    ASSERT_NE(nullptr, got);
    EXPECT_STREQ("Some text", got);
}

// ==================== InsertNewDeclaration Tests ====================

TEST_F(XMLElementTest_89, InsertNewDeclaration_CreatesDeclaration_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    XMLDeclaration* decl = elem->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(nullptr, decl);
}

// ==================== InsertNewUnknown Tests ====================

TEST_F(XMLElementTest_89, InsertNewUnknown_CreatesUnknown_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(nullptr, unknown);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_89, ShallowClone_ClonesElement_89) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(nullptr, clone);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(nullptr, cloneElem);
    EXPECT_STREQ("root", cloneElem->Name());
    EXPECT_STREQ("1", cloneElem->Attribute("a"));
    EXPECT_STREQ("2", cloneElem->Attribute("b"));
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_89, ShallowEqual_SameElement_89) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    
    XMLDocument doc2;
    doc2.Parse("<root a=\"1\"/>");
    XMLElement* elem2 = doc2.RootElement();
    
    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_89, ShallowEqual_DifferentAttributes_89) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    
    XMLDocument doc2;
    doc2.Parse("<root a=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_89, ShallowEqual_DifferentName_89) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    
    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== Multiple Attributes Tests ====================

TEST_F(XMLElementTest_89, MultipleAttributes_QueryEach_89) {
    doc.Parse("<root int=\"10\" float=\"1.5\" str=\"hello\" bool=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    
    int ival = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("int", &ival));
    EXPECT_EQ(10, ival);
    
    float fval = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("float", &fval));
    EXPECT_FLOAT_EQ(1.5f, fval);
    
    const char* sval = nullptr;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("str", &sval));
    EXPECT_STREQ("hello", sval);
    
    bool bval = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("bool", &bval));
    EXPECT_TRUE(bval);
}

// ==================== OverwriteAttribute Tests ====================

TEST_F(XMLElementTest_89, SetAttribute_OverwriteExisting_89) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    elem->SetAttribute("val", "new");
    const char* val = elem->Attribute("val");
    ASSERT_NE(nullptr, val);
    EXPECT_STREQ("new", val);
}

// ==================== SetText overwrites existing text Tests ====================

TEST_F(XMLElementTest_89, SetText_OverwritesExistingText_89) {
    doc.Parse("<root>old text</root>");
    XMLElement* elem = doc.RootElement();
    elem->SetText("new text");
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("new text", text);
}

// ==================== QueryInt64Text Tests ====================

TEST_F(XMLElementTest_89, QueryInt64Text_Valid_89) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    int64_t value = 0;
    XMLError err = elem->QueryInt64Text(&value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(