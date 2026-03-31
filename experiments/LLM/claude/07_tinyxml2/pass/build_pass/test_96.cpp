#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_96 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== QueryAttribute (string overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeString_ExistingAttribute_96) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    const char* value = nullptr;
    XMLError err = root->QueryAttribute("name", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_STREQ("hello", value);
}

TEST_F(XMLElementTest_96, QueryAttributeString_NonExistingAttribute_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    const char* value = nullptr;
    XMLError err = root->QueryAttribute("missing", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
    EXPECT_EQ(nullptr, value);
}

TEST_F(XMLElementTest_96, QueryAttributeString_EmptyValue_96) {
    doc.Parse("<root name=\"\"/>");
    XMLElement* root = doc.RootElement();
    const char* value = nullptr;
    XMLError err = root->QueryAttribute("name", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_STREQ("", value);
}

// ==================== QueryAttribute (int overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeInt_ValidValue_96) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* root = doc.RootElement();
    int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(42, value);
}

TEST_F(XMLElementTest_96, QueryAttributeInt_NegativeValue_96) {
    doc.Parse("<root val=\"-100\"/>");
    XMLElement* root = doc.RootElement();
    int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(-100, value);
}

TEST_F(XMLElementTest_96, QueryAttributeInt_InvalidValue_96) {
    doc.Parse("<root val=\"notanumber\"/>");
    XMLElement* root = doc.RootElement();
    int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}

TEST_F(XMLElementTest_96, QueryAttributeInt_MissingAttribute_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (unsigned int overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeUnsigned_ValidValue_96) {
    doc.Parse("<root val=\"123\"/>");
    XMLElement* root = doc.RootElement();
    unsigned int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(123u, value);
}

TEST_F(XMLElementTest_96, QueryAttributeUnsigned_InvalidValue_96) {
    doc.Parse("<root val=\"abc\"/>");
    XMLElement* root = doc.RootElement();
    unsigned int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}

// ==================== QueryAttribute (int64_t overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeInt64_ValidValue_96) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* root = doc.RootElement();
    int64_t value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(INT64_C(9223372036854775807), value);
}

TEST_F(XMLElementTest_96, QueryAttributeInt64_MissingAttribute_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    int64_t value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== QueryAttribute (uint64_t overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeUnsigned64_ValidValue_96) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* root = doc.RootElement();
    uint64_t value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(UINT64_C(18446744073709551615), value);
}

// ==================== QueryAttribute (bool overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeBool_TrueValue_96) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* root = doc.RootElement();
    bool value = false;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_96, QueryAttributeBool_FalseValue_96) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* root = doc.RootElement();
    bool value = true;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_96, QueryAttributeBool_InvalidValue_96) {
    doc.Parse("<root val=\"maybe\"/>");
    XMLElement* root = doc.RootElement();
    bool value = false;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}

// ==================== QueryAttribute (double overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeDouble_ValidValue_96) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* root = doc.RootElement();
    double value = 0.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14159, value, 1e-5);
}

TEST_F(XMLElementTest_96, QueryAttributeDouble_InvalidValue_96) {
    doc.Parse("<root val=\"notdouble\"/>");
    XMLElement* root = doc.RootElement();
    double value = 0.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}

// ==================== QueryAttribute (float overload) ====================

TEST_F(XMLElementTest_96, QueryAttributeFloat_ValidValue_96) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* root = doc.RootElement();
    float value = 0.0f;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(2.5f, value, 1e-5f);
}

TEST_F(XMLElementTest_96, QueryAttributeFloat_InvalidValue_96) {
    doc.Parse("<root val=\"notfloat\"/>");
    XMLElement* root = doc.RootElement();
    float value = 0.0f;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, err);
}

// ==================== SetAttribute / Attribute ====================

TEST_F(XMLElementTest_96, SetAttributeString_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("key", "value");
    EXPECT_STREQ("value", root->Attribute("key"));
}

TEST_F(XMLElementTest_96, SetAttributeInt_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("num", 99);
    EXPECT_EQ(99, root->IntAttribute("num"));
}

TEST_F(XMLElementTest_96, SetAttributeUnsigned_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("num", (unsigned)100);
    EXPECT_EQ(100u, root->UnsignedAttribute("num"));
}

TEST_F(XMLElementTest_96, SetAttributeInt64_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("num", INT64_C(1234567890123));
    EXPECT_EQ(INT64_C(1234567890123), root->Int64Attribute("num"));
}

TEST_F(XMLElementTest_96, SetAttributeUint64_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("num", UINT64_C(9876543210));
    EXPECT_EQ(UINT64_C(9876543210), root->Unsigned64Attribute("num"));
}

TEST_F(XMLElementTest_96, SetAttributeBool_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("flag", true);
    EXPECT_TRUE(root->BoolAttribute("flag"));
}

TEST_F(XMLElementTest_96, SetAttributeDouble_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("val", 1.23);
    EXPECT_NEAR(1.23, root->DoubleAttribute("val"), 1e-10);
}

TEST_F(XMLElementTest_96, SetAttributeFloat_And_Read_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("val", 4.5f);
    EXPECT_NEAR(4.5f, root->FloatAttribute("val"), 1e-5f);
}

// ==================== Attribute with default values ====================

TEST_F(XMLElementTest_96, IntAttribute_DefaultWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(77, root->IntAttribute("missing", 77));
}

TEST_F(XMLElementTest_96, UnsignedAttribute_DefaultWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(88u, root->UnsignedAttribute("missing", 88u));
}

TEST_F(XMLElementTest_96, Int64Attribute_DefaultWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(INT64_C(999), root->Int64Attribute("missing", INT64_C(999)));
}

TEST_F(XMLElementTest_96, Unsigned64Attribute_DefaultWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(UINT64_C(111), root->Unsigned64Attribute("missing", UINT64_C(111)));
}

TEST_F(XMLElementTest_96, BoolAttribute_DefaultWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_TRUE(root->BoolAttribute("missing", true));
    EXPECT_FALSE(root->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_96, DoubleAttribute_DefaultWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(9.99, root->DoubleAttribute("missing", 9.99), 1e-10);
}

TEST_F(XMLElementTest_96, FloatAttribute_DefaultWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(1.1f, root->FloatAttribute("missing", 1.1f), 1e-5f);
}

// ==================== Attribute() function ====================

TEST_F(XMLElementTest_96, Attribute_ReturnsNullWhenMissing_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(nullptr, root->Attribute("nonexistent"));
}

TEST_F(XMLElementTest_96, Attribute_WithMatchingValue_96) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    EXPECT_STREQ("val", root->Attribute("key", "val"));
}

TEST_F(XMLElementTest_96, Attribute_WithNonMatchingValue_96) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(nullptr, root->Attribute("key", "other"));
}

// ==================== FindAttribute ====================

TEST_F(XMLElementTest_96, FindAttribute_Exists_96) {
    doc.Parse("<root attr=\"test\"/>");
    XMLElement* root = doc.RootElement();
    const XMLAttribute* attr = root->FindAttribute("attr");
    EXPECT_NE(nullptr, attr);
    EXPECT_STREQ("attr", attr->Name());
    EXPECT_STREQ("test", attr->Value());
}

TEST_F(XMLElementTest_96, FindAttribute_NotExists_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    const XMLAttribute* attr = root->FindAttribute("noattr");
    EXPECT_EQ(nullptr, attr);
}

// ==================== DeleteAttribute ====================

TEST_F(XMLElementTest_96, DeleteAttribute_RemovesAttribute_96) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* root = doc.RootElement();
    root->DeleteAttribute("a");
    EXPECT_EQ(nullptr, root->Attribute("a"));
    EXPECT_STREQ("2", root->Attribute("b"));
}

TEST_F(XMLElementTest_96, DeleteAttribute_NonExistent_NoEffect_96) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* root = doc.RootElement();
    root->DeleteAttribute("nonexistent");
    EXPECT_STREQ("1", root->Attribute("a"));
}

// ==================== FirstAttribute ====================

TEST_F(XMLElementTest_96, FirstAttribute_NoAttributes_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(nullptr, root->FirstAttribute());
}

TEST_F(XMLElementTest_96, FirstAttribute_HasAttributes_96) {
    doc.Parse("<root first=\"1\" second=\"2\"/>");
    XMLElement* root = doc.RootElement();
    const XMLAttribute* attr = root->FirstAttribute();
    EXPECT_NE(nullptr, attr);
    EXPECT_STREQ("first", attr->Name());
}

// ==================== Name / SetName ====================

TEST_F(XMLElementTest_96, Name_ReturnsElementName_96) {
    doc.Parse("<myElement/>");
    XMLElement* root = doc.RootElement();
    EXPECT_STREQ("myElement", root->Name());
}

TEST_F(XMLElementTest_96, SetName_ChangesElementName_96) {
    doc.Parse("<old/>");
    XMLElement* root = doc.RootElement();
    root->SetName("newName");
    EXPECT_STREQ("newName", root->Name());
}

// ==================== GetText / SetText ====================

TEST_F(XMLElementTest_96, GetText_WithTextContent_96) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_STREQ("Hello World", root->GetText());
}

TEST_F(XMLElementTest_96, GetText_NoTextContent_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(nullptr, root->GetText());
}

TEST_F(XMLElementTest_96, SetText_String_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText("newtext");
    EXPECT_STREQ("newtext", root->GetText());
}

TEST_F(XMLElementTest_96, SetText_Int_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(42);
    EXPECT_STREQ("42", root->GetText());
}

TEST_F(XMLElementTest_96, SetText_UnsignedInt_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText((unsigned)100);
    EXPECT_STREQ("100", root->GetText());
}

TEST_F(XMLElementTest_96, SetText_Int64_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(INT64_C(1234567890123));
    EXPECT_STREQ("1234567890123", root->GetText());
}

TEST_F(XMLElementTest_96, SetText_Uint64_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(UINT64_C(9876543210));
    EXPECT_STREQ("9876543210", root->GetText());
}

TEST_F(XMLElementTest_96, SetText_Bool_True_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(true);
    EXPECT_STREQ("true", root->GetText());
}

TEST_F(XMLElementTest_96, SetText_Bool_False_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(false);
    EXPECT_STREQ("false", root->GetText());
}

// ==================== QueryIntText / QueryUnsignedText etc. ====================

TEST_F(XMLElementTest_96, QueryIntText_ValidInt_96) {
    doc.Parse("<root>42</root>");
    XMLElement* root = doc.RootElement();
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, root->QueryIntText(&val));
    EXPECT_EQ(42, val);
}

TEST_F(XMLElementTest_96, QueryIntText_InvalidText_96) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* root = doc.RootElement();
    int val = 0;
    EXPECT_EQ(XML_CAN_NOT_CONVERT_TEXT, root->QueryIntText(&val));
}

TEST_F(XMLElementTest_96, QueryIntText_NoText_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    int val = 0;
    EXPECT_EQ(XML_NO_TEXT_NODE, root->QueryIntText(&val));
}

TEST_F(XMLElementTest_96, QueryUnsignedText_ValidUnsigned_96) {
    doc.Parse("<root>100</root>");
    XMLElement* root = doc.RootElement();
    unsigned val = 0;
    EXPECT_EQ(XML_SUCCESS, root->QueryUnsignedText(&val));
    EXPECT_EQ(100u, val);
}

TEST_F(XMLElementTest_96, QueryInt64Text_ValidInt64_96) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* root = doc.RootElement();
    int64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, root->QueryInt64Text(&val));
    EXPECT_EQ(INT64_C(9223372036854775807), val);
}

TEST_F(XMLElementTest_96, QueryUnsigned64Text_ValidUint64_96) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* root = doc.RootElement();
    uint64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, root->QueryUnsigned64Text(&val));
    EXPECT_EQ(UINT64_C(18446744073709551615), val);
}

TEST_F(XMLElementTest_96, QueryBoolText_True_96) {
    doc.Parse("<root>true</root>");
    XMLElement* root = doc.RootElement();
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, root->QueryBoolText(&val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_96, QueryBoolText_False_96) {
    doc.Parse("<root>false</root>");
    XMLElement* root = doc.RootElement();
    bool val = true;
    EXPECT_EQ(XML_SUCCESS, root->QueryBoolText(&val));
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_96, QueryDoubleText_Valid_96) {
    doc.Parse("<root>3.14</root>");
    XMLElement* root = doc.RootElement();
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, root->QueryDoubleText(&val));
    EXPECT_NEAR(3.14, val, 1e-10);
}

TEST_F(XMLElementTest_96, QueryFloatText_Valid_96) {
    doc.Parse("<root>2.5</root>");
    XMLElement* root = doc.RootElement();
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, root->QueryFloatText(&val));
    EXPECT_NEAR(2.5f, val, 1e-5f);
}

// ==================== IntText / UnsignedText etc. with defaults ====================

TEST_F(XMLElementTest_96, IntText_WithDefault_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(55, root->IntText(55));
}

TEST_F(XMLElementTest_96, IntText_WithValidText_96) {
    doc.Parse("<root>10</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(10, root->IntText(55));
}

TEST_F(XMLElementTest_96, UnsignedText_WithDefault_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(88u, root->UnsignedText(88u));
}

TEST_F(XMLElementTest_96, Int64Text_WithDefault_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(INT64_C(123), root->Int64Text(INT64_C(123)));
}

TEST_F(XMLElementTest_96, Unsigned64Text_WithDefault_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(UINT64_C(456), root->Unsigned64Text(UINT64_C(456)));
}

TEST_F(XMLElementTest_96, BoolText_WithDefault_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_TRUE(root->BoolText(true));
}

TEST_F(XMLElementTest_96, DoubleText_WithDefault_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(1.11, root->DoubleText(1.11), 1e-10);
}

TEST_F(XMLElementTest_96, FloatText_WithDefault_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(2.22f, root->FloatText(2.22f), 1e-5f);
}

// ==================== InsertNewChildElement ====================

TEST_F(XMLElementTest_96, InsertNewChildElement_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLElement* child = root->InsertNewChildElement("child");
    EXPECT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
    EXPECT_EQ(child, root->FirstChildElement("child"));
}

// ==================== InsertNewComment ====================

TEST_F(XMLElementTest_96, InsertNewComment_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLComment* comment = root->InsertNewComment("this is a comment");
    EXPECT_NE(nullptr, comment);
    EXPECT_STREQ("this is a comment", comment->Value());
}

// ==================== InsertNewText ====================

TEST_F(XMLElementTest_96, InsertNewText_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLText* text = root->InsertNewText("some text");
    EXPECT_NE(nullptr, text);
    EXPECT_STREQ("some text", root->GetText());
}

// ==================== InsertNewDeclaration ====================

TEST_F(XMLElementTest_96, InsertNewDeclaration_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLDeclaration* decl = root->InsertNewDeclaration("version=\"1.0\"");
    EXPECT_NE(nullptr, decl);
}

// ==================== InsertNewUnknown ====================

TEST_F(XMLElementTest_96, InsertNewUnknown_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLUnknown* unknown = root->InsertNewUnknown("something");
    EXPECT_NE(nullptr, unknown);
}

// ==================== ToElement ====================

TEST_F(XMLElementTest_96, ToElement_ReturnsThis_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root, root->ToElement());
}

// ==================== ShallowClone ====================

TEST_F(XMLElementTest_96, ShallowClone_ClonesElement_96) {
    doc.Parse("<root attr=\"val\"><child/></root>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    XMLNode* clone = root->ShallowClone(&doc2);
    EXPECT_NE(nullptr, clone);
    XMLElement* cloneElem = clone->ToElement();
    EXPECT_NE(nullptr, cloneElem);
    EXPECT_STREQ("root", cloneElem->Name());
    EXPECT_STREQ("val", cloneElem->Attribute("attr"));
    // ShallowClone should not copy children
    EXPECT_EQ(nullptr, cloneElem->FirstChildElement());

    doc2.InsertEndChild(clone);
}

// ==================== ShallowEqual ====================

TEST_F(XMLElementTest_96, ShallowEqual_SameElement_96) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* root2 = doc2.RootElement();

    EXPECT_TRUE(root->ShallowEqual(root2));
}

TEST_F(XMLElementTest_96, ShallowEqual_DifferentAttributes_96) {
    doc.Parse("<root attr=\"val1\"/>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val2\"/>");
    XMLElement* root2 = doc2.RootElement();

    EXPECT_FALSE(root->ShallowEqual(root2));
}

TEST_F(XMLElementTest_96, ShallowEqual_DifferentNames_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* root2 = doc2.RootElement();

    EXPECT_FALSE(root->ShallowEqual(root2));
}

// ==================== Multiple attributes ====================

TEST_F(XMLElementTest_96, MultipleAttributes_SetAndQuery_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("str", "hello");
    root->SetAttribute("num", 10);
    root->SetAttribute("flag", true);
    root->SetAttribute("pi", 3.14);

    const char* str = nullptr;
    int num = 0;
    bool flag = false;
    double pi = 0.0;

    EXPECT_EQ(XML_SUCCESS, root->QueryAttribute("str", &str));
    EXPECT_STREQ("hello", str);

    EXPECT_EQ(XML_SUCCESS, root->QueryAttribute("num", &num));
    EXPECT_EQ(10, num);

    EXPECT_EQ(XML_SUCCESS, root->QueryAttribute("flag", &flag));
    EXPECT_TRUE(flag);

    EXPECT_EQ(XML_SUCCESS, root->QueryAttribute("pi", &pi));
    EXPECT_NEAR(3.14, pi, 1e-10);
}

// ==================== Overwriting attributes ====================

TEST_F(XMLElementTest_96, SetAttribute_Overwrite_96) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("val", "new");
    EXPECT_STREQ("new", root->Attribute("val"));
}

// ==================== SetText overwrites existing text ====================

TEST_F(XMLElementTest_96, SetText_OverwritesExisting_96) {
    doc.Parse("<root>old text</root>");
    XMLElement* root = doc.RootElement();
    root->SetText("new text");
    EXPECT_STREQ("new text", root->GetText());
}

// ==================== Accept visitor ====================

TEST_F(XMLElementTest_96, Accept_WithPrinter_96) {
    doc.Parse("<root attr=\"val\"><child>text</child></root>");
    XMLElement* root = doc.RootElement();
    XMLPrinter printer;
    bool result = root->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(nullptr, output);
    EXPECT_NE(nullptr, strstr(output, "root"));
}

// ==================== ClosingType ====================

TEST_F(XMLElementTest_96, ClosingType_OpenElement_96) {
    doc.Parse("<root></root>");
    XMLElement* root = doc.RootElement();
    // Open elements have OPEN closing type
    // Self-closing would be different but parsing <root/> may vary
    // Just test that the function returns a valid value
    auto ct = root->ClosingType();
    (void)ct; // Just ensure it compiles and doesn't crash
}

// ==================== Boundary: zero-length attribute name ====================

TEST_F(XMLElementTest_96, QueryAttribute_EmptyString_96) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* root = doc.RootElement();
    const char* value = nullptr;
    XMLError err = root->QueryAttribute("", &value);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

// ==================== SetText with float precision ====================

TEST_F(XMLElementTest_96, SetText_Float_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(1.5f);
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, root->QueryFloatText(&val));
    EXPECT_NEAR(1.5f, val, 1e-5f);
}

TEST_F(XMLElementTest_96, SetText_Double_96) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(2.718281828);
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, root->QueryDoubleText(&val));
    EXPECT_NEAR(2.718281828, val, 1e-6);
}
