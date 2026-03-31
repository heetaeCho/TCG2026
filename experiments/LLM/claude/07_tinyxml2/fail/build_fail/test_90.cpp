#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_90 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== QueryAttribute (unsigned int*) ====================

TEST_F(XMLElementTest_90, QueryAttributeUnsignedInt_ExistingAttribute_90) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42u);
}

TEST_F(XMLElementTest_90, QueryAttributeUnsignedInt_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int value = 99;
    XMLError err = elem->QueryAttribute("nonexistent", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 99u); // value should remain unchanged
}

TEST_F(XMLElementTest_90, QueryAttributeUnsignedInt_InvalidValue_90) {
    doc.Parse("<root val=\"notanumber\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_90, QueryAttributeUnsignedInt_Zero_90) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int value = 99;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0u);
}

TEST_F(XMLElementTest_90, QueryAttributeUnsignedInt_LargeValue_90) {
    doc.Parse("<root val=\"4294967295\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 4294967295u);
}

// ==================== QueryAttribute (int*) ====================

TEST_F(XMLElementTest_90, QueryAttributeInt_ExistingAttribute_90) {
    doc.Parse("<root val=\"-123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -123);
}

TEST_F(XMLElementTest_90, QueryAttributeInt_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int value = 55;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 55);
}

TEST_F(XMLElementTest_90, QueryAttributeInt_InvalidValue_90) {
    doc.Parse("<root val=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (int64_t*) ====================

TEST_F(XMLElementTest_90, QueryAttributeInt64_ExistingAttribute_90) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_90, QueryAttributeInt64_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 42;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 42);
}

// ==================== QueryAttribute (uint64_t*) ====================

TEST_F(XMLElementTest_90, QueryAttributeUint64_ExistingAttribute_90) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_90, QueryAttributeUint64_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    uint64_t value = 100;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 100u);
}

// ==================== QueryAttribute (bool*) ====================

TEST_F(XMLElementTest_90, QueryAttributeBool_True_90) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_90, QueryAttributeBool_False_90) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool value = true;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_90, QueryAttributeBool_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool value = true;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_90, QueryAttributeBool_InvalidValue_90) {
    doc.Parse("<root val=\"maybe\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (double*) ====================

TEST_F(XMLElementTest_90, QueryAttributeDouble_ExistingAttribute_90) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    double value = 0.0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.14159, 1e-5);
}

TEST_F(XMLElementTest_90, QueryAttributeDouble_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    double value = 1.0;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_DOUBLE_EQ(value, 1.0);
}

// ==================== QueryAttribute (float*) ====================

TEST_F(XMLElementTest_90, QueryAttributeFloat_ExistingAttribute_90) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

TEST_F(XMLElementTest_90, QueryAttributeFloat_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float value = 7.7f;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_FLOAT_EQ(value, 7.7f);
}

// ==================== QueryAttribute (const char**) ====================

TEST_F(XMLElementTest_90, QueryAttributeString_ExistingAttribute_90) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "hello");
}

TEST_F(XMLElementTest_90, QueryAttributeString_NonExistingAttribute_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, nullptr);
}

// ==================== SetAttribute / Attribute ====================

TEST_F(XMLElementTest_90, SetAttributeString_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("name", "value");
    const char* attr = elem->Attribute("name");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr, "value");
}

TEST_F(XMLElementTest_90, SetAttributeInt_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("count", 42);
    int value = 0;
    XMLError err = elem->QueryAttribute("count", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementTest_90, SetAttributeUnsigned_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("count", 42u);
    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("count", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42u);
}

TEST_F(XMLElementTest_90, SetAttributeInt64_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t bigVal = INT64_C(9223372036854775807);
    elem->SetAttribute("big", bigVal);
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("big", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, bigVal);
}

TEST_F(XMLElementTest_90, SetAttributeUint64_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    uint64_t bigVal = UINT64_C(18446744073709551615);
    elem->SetAttribute("big", bigVal);
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("big", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, bigVal);
}

TEST_F(XMLElementTest_90, SetAttributeBool_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("flag", true);
    bool value = false;
    XMLError err = elem->QueryAttribute("flag", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_90, SetAttributeDouble_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("pi", 3.14159);
    double value = 0.0;
    XMLError err = elem->QueryAttribute("pi", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.14159, 1e-5);
}

TEST_F(XMLElementTest_90, SetAttributeFloat_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("val", 2.5f);
    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

// ==================== Attribute with value filter ====================

TEST_F(XMLElementTest_90, Attribute_WithMatchingValue_90) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* result = elem->Attribute("val", "hello");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(XMLElementTest_90, Attribute_WithNonMatchingValue_90) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* result = elem->Attribute("val", "world");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementTest_90, Attribute_NonExistingName_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* result = elem->Attribute("missing");
    EXPECT_EQ(result, nullptr);
}

// ==================== DefaultValue Attribute accessors ====================

TEST_F(XMLElementTest_90, IntAttribute_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->IntAttribute("missing", 99), 99);
}

TEST_F(XMLElementTest_90, IntAttribute_Exists_90) {
    doc.Parse("<root val=\"10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->IntAttribute("val", 99), 10);
}

TEST_F(XMLElementTest_90, UnsignedAttribute_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->UnsignedAttribute("missing", 99u), 99u);
}

TEST_F(XMLElementTest_90, BoolAttribute_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->BoolAttribute("missing", true), true);
}

TEST_F(XMLElementTest_90, DoubleAttribute_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 1.5), 1.5);
}

TEST_F(XMLElementTest_90, FloatAttribute_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 1.5f), 1.5f);
}

TEST_F(XMLElementTest_90, Int64Attribute_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Int64Attribute("missing", INT64_C(1234567890123)), INT64_C(1234567890123));
}

TEST_F(XMLElementTest_90, Unsigned64Attribute_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Unsigned64Attribute("missing", UINT64_C(1234567890123)), UINT64_C(1234567890123));
}

// ==================== FindAttribute ====================

TEST_F(XMLElementTest_90, FindAttribute_Exists_90) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "val");
    EXPECT_STREQ(attr->Value(), "hello");
}

TEST_F(XMLElementTest_90, FindAttribute_NotExists_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FindAttribute("missing");
    EXPECT_EQ(attr, nullptr);
}

// ==================== FirstAttribute ====================

TEST_F(XMLElementTest_90, FirstAttribute_Exists_90) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_90, FirstAttribute_None_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// ==================== DeleteAttribute ====================

TEST_F(XMLElementTest_90, DeleteAttribute_Exists_90) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->DeleteAttribute("a");
    EXPECT_EQ(elem->FindAttribute("a"), nullptr);
    EXPECT_NE(elem->FindAttribute("b"), nullptr);
}

TEST_F(XMLElementTest_90, DeleteAttribute_NotExists_90) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_NE(elem->FindAttribute("a"), nullptr);
}

// ==================== SetText / GetText ====================

TEST_F(XMLElementTest_90, SetText_GetText_String_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText("Hello World");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello World");
}

TEST_F(XMLElementTest_90, SetText_Int_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(42);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");
}

TEST_F(XMLElementTest_90, SetText_UnsignedInt_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(42u);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");
}

TEST_F(XMLElementTest_90, SetText_Bool_True_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(true);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "true");
}

TEST_F(XMLElementTest_90, SetText_Bool_False_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(false);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "false");
}

TEST_F(XMLElementTest_90, GetText_NoText_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* text = elem->GetText();
    EXPECT_EQ(text, nullptr);
}

TEST_F(XMLElementTest_90, GetText_Existing_90) {
    doc.Parse("<root>SomeText</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "SomeText");
}

// ==================== QueryIntText / QueryUnsignedText ====================

TEST_F(XMLElementTest_90, QueryIntText_Valid_90) {
    doc.Parse("<root>123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_90, QueryIntText_NoText_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_90, QueryUnsignedText_Valid_90) {
    doc.Parse("<root>456</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 456u);
}

TEST_F(XMLElementTest_90, QueryBoolText_True_90) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_90, QueryDoubleText_Valid_90) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 1e-5);
}

TEST_F(XMLElementTest_90, QueryFloatText_Valid_90) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLElementTest_90, QueryInt64Text_Valid_90) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_90, QueryUnsigned64Text_Valid_90) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_C(18446744073709551615));
}

// ==================== Default Text accessors ====================

TEST_F(XMLElementTest_90, IntText_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->IntText(77), 77);
}

TEST_F(XMLElementTest_90, IntText_Existing_90) {
    doc.Parse("<root>10</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->IntText(77), 10);
}

TEST_F(XMLElementTest_90, UnsignedText_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->UnsignedText(77u), 77u);
}

TEST_F(XMLElementTest_90, BoolText_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->BoolText(true), true);
}

TEST_F(XMLElementTest_90, DoubleText_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_DOUBLE_EQ(elem->DoubleText(1.5), 1.5);
}

TEST_F(XMLElementTest_90, FloatText_Default_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_FLOAT_EQ(elem->FloatText(1.5f), 1.5f);
}

// ==================== Name / SetName ====================

TEST_F(XMLElementTest_90, Name_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_STREQ(elem->Name(), "root");
}

TEST_F(XMLElementTest_90, SetName_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetName("newname");
    EXPECT_STREQ(elem->Name(), "newname");
}

// ==================== ToElement ====================

TEST_F(XMLElementTest_90, ToElement_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== InsertNewChildElement ====================

TEST_F(XMLElementTest_90, InsertNewChildElement_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(elem->FirstChildElement("child"), child);
}

// ==================== InsertNewComment ====================

TEST_F(XMLElementTest_90, InsertNewComment_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
}

// ==================== InsertNewText ====================

TEST_F(XMLElementTest_90, InsertNewText_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    const char* result = elem->GetText();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "some text");
}

// ==================== InsertNewDeclaration ====================

TEST_F(XMLElementTest_90, InsertNewDeclaration_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

// ==================== InsertNewUnknown ====================

TEST_F(XMLElementTest_90, InsertNewUnknown_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ShallowClone ====================

TEST_F(XMLElementTest_90, ShallowClone_90) {
    doc.Parse("<root attr=\"val\"><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);

    XMLElement* clonedElem = clone->ToElement();
    ASSERT_NE(clonedElem, nullptr);
    EXPECT_STREQ(clonedElem->Name(), "root");
    EXPECT_STREQ(clonedElem->Attribute("attr"), "val");
    // Shallow clone should not copy children
    EXPECT_EQ(clonedElem->FirstChild(), nullptr);
}

// ==================== ShallowEqual ====================

TEST_F(XMLElementTest_90, ShallowEqual_SameElement_90) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_90, ShallowEqual_DifferentName_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_90, ShallowEqual_DifferentAttribute_90) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root a=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== Multiple attributes ====================

TEST_F(XMLElementTest_90, MultipleAttributes_90) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int a = 0, b = 0, c = 0;
    EXPECT_EQ(elem->QueryAttribute("a", &a), XML_SUCCESS);
    EXPECT_EQ(elem->QueryAttribute("b", &b), XML_SUCCESS);
    EXPECT_EQ(elem->QueryAttribute("c", &c), XML_SUCCESS);
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 2);
    EXPECT_EQ(c, 3);
}

// ==================== Overwrite attribute ====================

TEST_F(XMLElementTest_90, OverwriteAttribute_90) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("val", "new");
    EXPECT_STREQ(elem->Attribute("val"), "new");
}

// ==================== SetText overwrites existing text ====================

TEST_F(XMLElementTest_90, SetText_OverwriteExisting_90) {
    doc.Parse("<root>OldText</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText("NewText");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "NewText");
}

// ==================== SetText with int64 and uint64 ====================

TEST_F(XMLElementTest_90, SetText_Int64_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(INT64_C(9223372036854775807));
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_90, SetText_Uint64_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(UINT64_C(18446744073709551615));
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_90, SetText_Double_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(3.14);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 1e-5);
}

TEST_F(XMLElementTest_90, SetText_Float_90) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

// ==================== Negative int attribute ====================

TEST_F