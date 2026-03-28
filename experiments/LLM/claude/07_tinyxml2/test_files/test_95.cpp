#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_95 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== QueryAttribute (float overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeFloat_ExistingAttribute_95) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.14f, 0.01f);
}

TEST_F(XMLElementTest_95, QueryAttributeFloat_NonExistingAttribute_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float value = 0.0f;
    XMLError err = elem->QueryAttribute("nonexistent", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_95, QueryAttributeFloat_InvalidValue_95) {
    doc.Parse("<root val=\"notafloat\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLElementTest_95, QueryAttributeFloat_ZeroValue_95) {
    doc.Parse("<root val=\"0.0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float value = 1.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 0.0f);
}

TEST_F(XMLElementTest_95, QueryAttributeFloat_NegativeValue_95) {
    doc.Parse("<root val=\"-2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, -2.5f, 0.001f);
}

// ==================== QueryAttribute (int overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeInt_ExistingAttribute_95) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementTest_95, QueryAttributeInt_NonExistingAttribute_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_95, QueryAttributeInt_InvalidValue_95) {
    doc.Parse("<root val=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryAttribute (unsigned int overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeUnsigned_ExistingAttribute_95) {
    doc.Parse("<root val=\"100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 100u);
}

TEST_F(XMLElementTest_95, QueryAttributeUnsigned_NonExistingAttribute_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// ==================== QueryAttribute (int64_t overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeInt64_ExistingAttribute_95) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLElementTest_95, QueryAttributeInt64_NonExistingAttribute_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// ==================== QueryAttribute (uint64_t overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeUnsigned64_ExistingAttribute_95) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

// ==================== QueryAttribute (bool overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeBool_TrueValue_95) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_95, QueryAttributeBool_FalseValue_95) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool value = true;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_95, QueryAttributeBool_InvalidValue_95) {
    doc.Parse("<root val=\"maybe\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== QueryAttribute (double overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeDouble_ExistingAttribute_95) {
    doc.Parse("<root val=\"3.141592653589793\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    double value = 0.0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.141592653589793, 1e-10);
}

// ==================== QueryAttribute (string overload) ====================

TEST_F(XMLElementTest_95, QueryAttributeString_ExistingAttribute_95) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(value, "hello");
}

TEST_F(XMLElementTest_95, QueryAttributeString_NonExistingAttribute_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// ==================== SetAttribute / Attribute ====================

TEST_F(XMLElementTest_95, SetAttributeString_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("name", "value");
    EXPECT_STREQ(elem->Attribute("name"), "value");
}

TEST_F(XMLElementTest_95, SetAttributeInt_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("num", 123);
    EXPECT_EQ(elem->IntAttribute("num", 0), 123);
}

TEST_F(XMLElementTest_95, SetAttributeUnsigned_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("num", (unsigned)456);
    EXPECT_EQ(elem->UnsignedAttribute("num", 0), 456u);
}

TEST_F(XMLElementTest_95, SetAttributeInt64_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("num", (int64_t)9223372036854775807LL);
    EXPECT_EQ(elem->Int64Attribute("num", 0), 9223372036854775807LL);
}

TEST_F(XMLElementTest_95, SetAttributeUint64_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("num", (uint64_t)18446744073709551615ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("num", 0), 18446744073709551615ULL);
}

TEST_F(XMLElementTest_95, SetAttributeBool_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_95, SetAttributeDouble_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("val", 2.718281828);
    EXPECT_NEAR(elem->DoubleAttribute("val", 0.0), 2.718281828, 1e-6);
}

TEST_F(XMLElementTest_95, SetAttributeFloat_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("val", 1.5f);
    EXPECT_NEAR(elem->FloatAttribute("val", 0.0f), 1.5f, 0.001f);
}

// ==================== Attribute with default values ====================

TEST_F(XMLElementTest_95, IntAttribute_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->IntAttribute("missing", 99), 99);
}

TEST_F(XMLElementTest_95, UnsignedAttribute_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->UnsignedAttribute("missing", 77u), 77u);
}

TEST_F(XMLElementTest_95, Int64Attribute_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Int64Attribute("missing", 12345LL), 12345LL);
}

TEST_F(XMLElementTest_95, Unsigned64Attribute_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Unsigned64Attribute("missing", 67890ULL), 67890ULL);
}

TEST_F(XMLElementTest_95, BoolAttribute_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_TRUE(elem->BoolAttribute("missing", true));
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_95, DoubleAttribute_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 1.23), 1.23);
}

TEST_F(XMLElementTest_95, FloatAttribute_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 4.56f), 4.56f);
}

// ==================== Name ====================

TEST_F(XMLElementTest_95, Name_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_STREQ(elem->Name(), "root");
}

TEST_F(XMLElementTest_95, SetName_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetName("newname");
    EXPECT_STREQ(elem->Name(), "newname");
}

// ==================== FindAttribute ====================

TEST_F(XMLElementTest_95, FindAttribute_Exists_95) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FindAttribute("attr");
    EXPECT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr");
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_95, FindAttribute_NotExists_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FindAttribute("nonexistent");
    EXPECT_EQ(attr, nullptr);
}

// ==================== FirstAttribute ====================

TEST_F(XMLElementTest_95, FirstAttribute_NoAttributes_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

TEST_F(XMLElementTest_95, FirstAttribute_WithAttributes_95) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

// ==================== DeleteAttribute ====================

TEST_F(XMLElementTest_95, DeleteAttribute_95) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->DeleteAttribute("a");
    EXPECT_EQ(elem->FindAttribute("a"), nullptr);
    EXPECT_NE(elem->FindAttribute("b"), nullptr);
}

TEST_F(XMLElementTest_95, DeleteAttribute_NonExisting_95) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_NE(elem->FindAttribute("a"), nullptr);
}

// ==================== SetText / GetText ====================

TEST_F(XMLElementTest_95, SetTextString_GetText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText("hello world");
    EXPECT_STREQ(elem->GetText(), "hello world");
}

TEST_F(XMLElementTest_95, SetTextInt_GetText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_95, SetTextUnsigned_GetText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText((unsigned)100);
    EXPECT_STREQ(elem->GetText(), "100");
}

TEST_F(XMLElementTest_95, SetTextBool_GetText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_95, SetTextFloat_GetText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(1.5f);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    float val = (float)atof(text);
    EXPECT_NEAR(val, 1.5f, 0.01f);
}

TEST_F(XMLElementTest_95, SetTextDouble_GetText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText(2.718);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    double val = atof(text);
    EXPECT_NEAR(val, 2.718, 0.001);
}

TEST_F(XMLElementTest_95, GetText_NoText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_95, GetText_WithExistingText_95) {
    doc.Parse("<root>some text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_STREQ(elem->GetText(), "some text");
}

// ==================== QueryIntText / QueryFloatText etc. ====================

TEST_F(XMLElementTest_95, QueryIntText_Success_95) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_95, QueryIntText_NoText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_95, QueryUnsignedText_Success_95) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    unsigned int val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_95, QueryInt64Text_Success_95) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_MAX);
}

TEST_F(XMLElementTest_95, QueryUnsigned64Text_Success_95) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_MAX);
}

TEST_F(XMLElementTest_95, QueryBoolText_Success_95) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_95, QueryDoubleText_Success_95) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_95, QueryFloatText_Success_95) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 0.01f);
}

TEST_F(XMLElementTest_95, QueryFloatText_InvalidText_95) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ==================== Text with default values ====================

TEST_F(XMLElementTest_95, IntText_WithValue_95) {
    doc.Parse("<root>10</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->IntText(0), 10);
}

TEST_F(XMLElementTest_95, IntText_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->IntText(99), 99);
}

TEST_F(XMLElementTest_95, UnsignedText_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->UnsignedText(55u), 55u);
}

TEST_F(XMLElementTest_95, Int64Text_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Int64Text(123LL), 123LL);
}

TEST_F(XMLElementTest_95, Unsigned64Text_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->Unsigned64Text(456ULL), 456ULL);
}

TEST_F(XMLElementTest_95, BoolText_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_TRUE(elem->BoolText(true));
    EXPECT_FALSE(elem->BoolText(false));
}

TEST_F(XMLElementTest_95, DoubleText_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_DOUBLE_EQ(elem->DoubleText(1.23), 1.23);
}

TEST_F(XMLElementTest_95, FloatText_DefaultValue_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_FLOAT_EQ(elem->FloatText(4.56f), 4.56f);
}

// ==================== InsertNewChildElement ====================

TEST_F(XMLElementTest_95, InsertNewChildElement_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(child->Parent(), elem);
}

// ==================== InsertNewComment ====================

TEST_F(XMLElementTest_95, InsertNewComment_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLComment* comment = elem->InsertNewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
}

// ==================== InsertNewText ====================

TEST_F(XMLElementTest_95, InsertNewText_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "some text");
}

// ==================== InsertNewDeclaration ====================

TEST_F(XMLElementTest_95, InsertNewDeclaration_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

// ==================== InsertNewUnknown ====================

TEST_F(XMLElementTest_95, InsertNewUnknown_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ToElement ====================

TEST_F(XMLElementTest_95, ToElement_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== ShallowClone / ShallowEqual ====================

TEST_F(XMLElementTest_95, ShallowClone_95) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "value");
}

TEST_F(XMLElementTest_95, ShallowEqual_Same_95) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"value\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_95, ShallowEqual_Different_95) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other attr=\"value\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== Attribute (with matching value) ====================

TEST_F(XMLElementTest_95, Attribute_WithMatchingValue_95) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_STREQ(elem->Attribute("attr", "hello"), "hello");
    EXPECT_EQ(elem->Attribute("attr", "world"), nullptr);
}

TEST_F(XMLElementTest_95, Attribute_NullValue_95) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_STREQ(elem->Attribute("attr"), "hello");
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

// ==================== Multiple attributes ====================

TEST_F(XMLElementTest_95, MultipleAttributes_95) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_STREQ(elem->Attribute("a"), "1");
    EXPECT_STREQ(elem->Attribute("b"), "2");
    EXPECT_STREQ(elem->Attribute("c"), "3");
}

// ==================== Overwrite attribute ====================

TEST_F(XMLElementTest_95, OverwriteAttribute_95) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetAttribute("val", "new");
    EXPECT_STREQ(elem->Attribute("val"), "new");
}

// ==================== SetText Int64 / Uint64 ====================

TEST_F(XMLElementTest_95, SetTextInt64_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText((int64_t)123456789012345LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123456789012345LL);
}

TEST_F(XMLElementTest_95, SetTextUint64_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText((uint64_t)18446744073709551615ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 18446744073709551615ULL);
}

// ==================== Accept ====================

TEST_F(XMLElementTest_95, Accept_Printer_95) {
    doc.Parse("<root><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLPrinter printer;
    bool result = elem->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    // The output should contain root and child
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
    EXPECT_NE(std::string(output).find("child"), std::string::npos);
}

// ==================== Boundary: Large number of attributes ====================

TEST_F(XMLElementTest_95, ManyAttributes_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    for (int i = 0; i < 100; ++i) {
        std::string name = "attr" + std::to_string(i);
        elem->SetAttribute(name.c_str(), i);
    }

    for (int i = 0; i < 100; ++i) {
        std::string name = "attr" + std::to_string(i);
        EXPECT_EQ(elem->IntAttribute(name.c_str(), -1), i);
    }
}

// ==================== Empty string attribute ====================

TEST_F(XMLElementTest_95, EmptyStringAttribute_95) {
    doc.Parse("<root attr=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    EXPECT_STREQ(elem->Attribute("attr"), "");
}

// ==================== SetText replaces existing text ====================

TEST_F(XMLElementTest_95, SetTextReplacesExisting_95) {
    doc.Parse("<root>old text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    elem->SetText("new text");
    EXPECT_STREQ(elem->GetText(), "new text");
}

// ==================== QueryFloatAttribute vs QueryAttribute(float) consistency ====================

TEST_F(XMLElementTest_95, QueryFloatAttribute_ConsistencyWithQueryAttribute_95) {
    doc.Parse("<root val=\"7.77\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    float val1 = 0.0f;
    float val2 = 0.0f;
    XMLError err1 = elem->QueryFloatAttribute("val", &val1);
    XMLError err2 = elem->QueryAttribute("val", &val2);
    EXPECT_EQ(err1, err2);
    EXPECT_FLOAT_EQ(val1, val2);
}

// ==================== ClosingType ====================

TEST_F(XMLElementTest_95, ClosingType_SelfClosing_95) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    // Just verify it's callable and returns something valid
    XMLElement::ElementClosingType ct = elem->ClosingType();
    // Self-closing or open are valid
    (void)ct;
}
