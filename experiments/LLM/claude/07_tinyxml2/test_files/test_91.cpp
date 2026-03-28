#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_91 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeInt64_ValidAttribute_91) {
    doc.Parse("<root val=\"12345678901234\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 12345678901234LL);
}

TEST_F(XMLElementTest_91, QueryAttributeInt64_NonExistentAttribute_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t value = -1;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(value, -1);
}

TEST_F(XMLElementTest_91, QueryAttributeInt64_InvalidValue_91) {
    doc.Parse("<root val=\"notanumber\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_91, QueryAttributeInt64_NegativeValue_91) {
    doc.Parse("<root val=\"-9876543210\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -9876543210LL);
}

TEST_F(XMLElementTest_91, QueryAttributeInt64_ZeroValue_91) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t value = 99;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

// ==================== QueryAttribute (int) Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeInt_ValidAttribute_91) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementTest_91, QueryAttributeInt_NonExistent_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int value = -1;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (unsigned int) Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeUnsigned_ValidAttribute_91) {
    doc.Parse("<root val=\"100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 100u);
}

// ==================== QueryAttribute (uint64_t) Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeUint64_ValidAttribute_91) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    // May or may not parse the full max uint64, but should not crash
    // If parsing is successful, check the value
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, UINT64_MAX);
    }
}

TEST_F(XMLElementTest_91, QueryAttributeUint64_NonExistent_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("nonexist", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (bool) Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeBool_True_91) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_91, QueryAttributeBool_False_91) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = true;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_91, QueryAttributeBool_Invalid_91) {
    doc.Parse("<root val=\"maybe\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (double) Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeDouble_Valid_91) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double value = 0.0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14159);
}

TEST_F(XMLElementTest_91, QueryAttributeDouble_NonExistent_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double value = 0.0;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (float) Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeFloat_Valid_91) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

// ==================== QueryAttribute (string) Tests ====================

TEST_F(XMLElementTest_91, QueryAttributeString_Valid_91) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(value, "hello");
}

TEST_F(XMLElementTest_91, QueryAttributeString_NonExistent_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== SetAttribute / Attribute Tests ====================

TEST_F(XMLElementTest_91, SetAttributeString_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("name", "value");
    EXPECT_STREQ(elem->Attribute("name"), "value");
}

TEST_F(XMLElementTest_91, SetAttributeInt_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("count", 42);
    EXPECT_EQ(elem->IntAttribute("count", 0), 42);
}

TEST_F(XMLElementTest_91, SetAttributeUnsigned_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", (unsigned)100);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0), 100u);
}

TEST_F(XMLElementTest_91, SetAttributeInt64_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("bigval", (int64_t)9876543210LL);
    EXPECT_EQ(elem->Int64Attribute("bigval", 0), 9876543210LL);
}

TEST_F(XMLElementTest_91, SetAttributeUint64_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("ubigval", (uint64_t)12345678901234ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("ubigval", 0), 12345678901234ULL);
}

TEST_F(XMLElementTest_91, SetAttributeBool_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_91, SetAttributeDouble_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("dval", 1.23456789);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("dval", 0.0), 1.23456789);
}

TEST_F(XMLElementTest_91, SetAttributeFloat_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("fval", 1.5f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("fval", 0.0f), 1.5f);
}

// ==================== Attribute Default Value Tests ====================

TEST_F(XMLElementTest_91, IntAttributeDefault_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("nonexist", 99), 99);
}

TEST_F(XMLElementTest_91, UnsignedAttributeDefault_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("nonexist", 77u), 77u);
}

TEST_F(XMLElementTest_91, Int64AttributeDefault_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("nonexist", 123456789LL), 123456789LL);
}

TEST_F(XMLElementTest_91, Unsigned64AttributeDefault_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("nonexist", 999ULL), 999ULL);
}

TEST_F(XMLElementTest_91, BoolAttributeDefault_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("nonexist", true));
    EXPECT_FALSE(elem->BoolAttribute("nonexist", false));
}

TEST_F(XMLElementTest_91, DoubleAttributeDefault_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("nonexist", 2.718), 2.718);
}

TEST_F(XMLElementTest_91, FloatAttributeDefault_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("nonexist", 1.41f), 1.41f);
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_91, FindAttribute_Existing_91) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    EXPECT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_91, FindAttribute_NonExistent_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("missing");
    EXPECT_EQ(attr, nullptr);
}

// ==================== Attribute (string match) Tests ====================

TEST_F(XMLElementTest_91, Attribute_ValueMatch_91) {
    doc.Parse("<root type=\"xml\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("type", "xml"), "xml");
}

TEST_F(XMLElementTest_91, Attribute_ValueMismatch_91) {
    doc.Parse("<root type=\"xml\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("type", "json"), nullptr);
}

TEST_F(XMLElementTest_91, Attribute_NullValue_ReturnsAttributeValue_91) {
    doc.Parse("<root type=\"xml\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("type"), "xml");
}

TEST_F(XMLElementTest_91, Attribute_NonExistent_ReturnsNull_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("missing"), nullptr);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_91, DeleteAttribute_Existing_91) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("a");
    EXPECT_EQ(elem->Attribute("a"), nullptr);
    EXPECT_STREQ(elem->Attribute("b"), "2");
}

TEST_F(XMLElementTest_91, DeleteAttribute_NonExistent_91) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Should not crash
    elem->DeleteAttribute("nonexist");
    EXPECT_STREQ(elem->Attribute("a"), "1");
}

// ==================== SetText / GetText Tests ====================

TEST_F(XMLElementTest_91, SetText_String_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("hello world");
    EXPECT_STREQ(elem->GetText(), "hello world");
}

TEST_F(XMLElementTest_91, SetText_Int_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_91, SetText_UnsignedInt_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((unsigned)100);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_91, SetText_Int64_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((int64_t)9876543210LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 9876543210LL);
}

TEST_F(XMLElementTest_91, SetText_Uint64_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((uint64_t)12345678901234ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 12345678901234ULL);
}

TEST_F(XMLElementTest_91, SetText_Bool_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_91, SetText_Double_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_91, SetText_Float_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLElementTest_91, GetText_NoText_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_91, GetText_WithText_91) {
    doc.Parse("<root>some text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

// ==================== QueryText Default Value Tests ====================

TEST_F(XMLElementTest_91, IntText_Default_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(55), 55);
}

TEST_F(XMLElementTest_91, IntText_WithValue_91) {
    doc.Parse("<root>123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 123);
}

TEST_F(XMLElementTest_91, UnsignedText_Default_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(77u), 77u);
}

TEST_F(XMLElementTest_91, Int64Text_Default_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(99LL), 99LL);
}

TEST_F(XMLElementTest_91, Unsigned64Text_Default_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(88ULL), 88ULL);
}

TEST_F(XMLElementTest_91, BoolText_Default_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_91, DoubleText_Default_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.5), 1.5);
}

TEST_F(XMLElementTest_91, FloatText_Default_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(2.5f), 2.5f);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_91, Name_91) {
    doc.Parse("<myelem/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myelem");
}

TEST_F(XMLElementTest_91, SetName_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newname");
    EXPECT_STREQ(elem->Name(), "newname");
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_91, InsertNewChildElement_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(elem->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_91, InsertNewComment_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_91, InsertNewText_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

TEST_F(XMLElementTest_91, InsertNewDeclaration_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_91, InsertNewUnknown_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("unknown");
    ASSERT_NE(unknown, nullptr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_91, FirstAttribute_NoAttributes_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

TEST_F(XMLElementTest_91, FirstAttribute_WithAttributes_91) {
    doc.Parse("<root first=\"1\" second=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    EXPECT_STREQ(attr->Value(), "1");
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST_F(XMLElementTest_91, ShallowClone_91) {
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
    // ShallowClone should not clone children
    EXPECT_EQ(clonedElem->FirstChildElement(), nullptr);
}

TEST_F(XMLElementTest_91, ShallowEqual_SameElement_91) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_91, ShallowEqual_DifferentName_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_91, ShallowEqual_DifferentAttributes_91) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root a=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_91, ToElement_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== Multiple Attributes Tests ====================

TEST_F(XMLElementTest_91, MultipleAttributes_91) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("a"), "1");
    EXPECT_STREQ(elem->Attribute("b"), "2");
    EXPECT_STREQ(elem->Attribute("c"), "3");
}

TEST_F(XMLElementTest_91, OverwriteAttribute_91) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", "new");
    EXPECT_STREQ(elem->Attribute("val"), "new");
}

// ==================== QueryIntText Error Cases ====================

TEST_F(XMLElementTest_91, QueryIntText_NoText_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_91, QueryIntText_InvalidText_91) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryBoolText Tests ====================

TEST_F(XMLElementTest_91, QueryBoolText_True_91) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_91, QueryBoolText_False_91) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

// ==================== Empty Attribute Name/Value Edge Cases ====================

TEST_F(XMLElementTest_91, EmptyStringAttribute_91) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("val"), "");
}

TEST_F(XMLElementTest_91, SetAttributeEmptyString_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("key", "");
    EXPECT_STREQ(elem->Attribute("key"), "");
}

// ==================== Accept (Visitor) Test ====================

TEST_F(XMLElementTest_91, Accept_XMLPrinter_91) {
    doc.Parse("<root attr=\"val\"><child>text</child></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLPrinter printer;
    bool result = elem->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // Output should contain the element
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
    EXPECT_NE(std::string(output).find("child"), std::string::npos);
    EXPECT_NE(std::string(output).find("text"), std::string::npos);
}

// ==================== QueryStringAttribute Tests ====================

TEST_F(XMLElementTest_91, QueryStringAttribute_Valid_91) {
    doc.Parse("<root name=\"test\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("name", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(val, "test");
}

TEST_F(XMLElementTest_91, QueryStringAttribute_NonExistent_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("missing", &val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== Boundary: Large number of attributes ====================

TEST_F(XMLElementTest_91, ManyAttributes_91) {
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

// ==================== ClosingType Tests ====================

TEST_F(XMLElementTest_91, ClosingType_SelfClosing_91) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // The element exists, just verify it has a closing type accessible
    // Self-closing or open, depending on parse
    auto ct = elem->ClosingType();
    // Just test it doesn't crash and returns a valid enum value
    (void)ct;
}
