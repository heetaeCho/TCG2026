#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_251 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== IntText Tests ====================

TEST_F(XMLElementTest_251, IntText_ReturnsTextAsInt_251) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 42);
}

TEST_F(XMLElementTest_251, IntText_ReturnsDefaultWhenNoText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(99), 99);
}

TEST_F(XMLElementTest_251, IntText_ReturnsDefaultWhenTextIsNotInt_251) {
    doc.Parse("<root>hello</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(55), 55);
}

TEST_F(XMLElementTest_251, IntText_NegativeValue_251) {
    doc.Parse("<root>-123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), -123);
}

TEST_F(XMLElementTest_251, IntText_ZeroValue_251) {
    doc.Parse("<root>0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(99), 0);
}

TEST_F(XMLElementTest_251, IntText_NegativeDefault_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(-1), -1);
}

// ==================== UnsignedText Tests ====================

TEST_F(XMLElementTest_251, UnsignedText_ReturnsTextAsUnsigned_251) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(0), 42u);
}

TEST_F(XMLElementTest_251, UnsignedText_ReturnsDefaultWhenNoText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(99u), 99u);
}

TEST_F(XMLElementTest_251, UnsignedText_ReturnsDefaultWhenTextIsNotUnsigned_251) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(77u), 77u);
}

// ==================== Int64Text Tests ====================

TEST_F(XMLElementTest_251, Int64Text_ReturnsTextAsInt64_251) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(0), INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_251, Int64Text_ReturnsDefaultWhenNoText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(INT64_C(-100)), INT64_C(-100));
}

TEST_F(XMLElementTest_251, Int64Text_ReturnsDefaultWhenTextIsNotInt64_251) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(INT64_C(42)), INT64_C(42));
}

// ==================== Unsigned64Text Tests ====================

TEST_F(XMLElementTest_251, Unsigned64Text_ReturnsTextAsUnsigned64_251) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(0), UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_251, Unsigned64Text_ReturnsDefaultWhenNoText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(UINT64_C(100)), UINT64_C(100));
}

// ==================== BoolText Tests ====================

TEST_F(XMLElementTest_251, BoolText_ReturnsTrue_251) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolText(false), true);
}

TEST_F(XMLElementTest_251, BoolText_ReturnsFalse_251) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolText(true), false);
}

TEST_F(XMLElementTest_251, BoolText_ReturnsDefaultWhenNoText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolText(true), true);
}

TEST_F(XMLElementTest_251, BoolText_ReturnsDefaultWhenTextIsNotBool_251) {
    doc.Parse("<root>maybe</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolText(false), false);
}

// ==================== DoubleText Tests ====================

TEST_F(XMLElementTest_251, DoubleText_ReturnsTextAsDouble_251) {
    doc.Parse("<root>3.14159</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), 3.14159);
}

TEST_F(XMLElementTest_251, DoubleText_ReturnsDefaultWhenNoText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(2.718), 2.718);
}

TEST_F(XMLElementTest_251, DoubleText_ReturnsDefaultWhenTextIsNotDouble_251) {
    doc.Parse("<root>notadouble</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.5), 1.5);
}

// ==================== FloatText Tests ====================

TEST_F(XMLElementTest_251, FloatText_ReturnsTextAsFloat_251) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(0.0f), 1.5f);
}

TEST_F(XMLElementTest_251, FloatText_ReturnsDefaultWhenNoText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(9.9f), 9.9f);
}

TEST_F(XMLElementTest_251, FloatText_ReturnsDefaultWhenTextIsNotFloat_251) {
    doc.Parse("<root>xyz</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(7.7f), 7.7f);
}

// ==================== QueryIntText Tests ====================

TEST_F(XMLElementTest_251, QueryIntText_Success_251) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100);
}

TEST_F(XMLElementTest_251, QueryIntText_NoTextReturnsError_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_251, QueryIntText_InvalidTextReturnsError_251) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryUnsignedText Tests ====================

TEST_F(XMLElementTest_251, QueryUnsignedText_Success_251) {
    doc.Parse("<root>200</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 200u);
}

// ==================== QueryInt64Text Tests ====================

TEST_F(XMLElementTest_251, QueryInt64Text_Success_251) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_C(9223372036854775807));
}

// ==================== QueryUnsigned64Text Tests ====================

TEST_F(XMLElementTest_251, QueryUnsigned64Text_Success_251) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_C(18446744073709551615));
}

// ==================== QueryBoolText Tests ====================

TEST_F(XMLElementTest_251, QueryBoolText_True_251) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_251, QueryBoolText_False_251) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

// ==================== QueryDoubleText Tests ====================

TEST_F(XMLElementTest_251, QueryDoubleText_Success_251) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ==================== QueryFloatText Tests ====================

TEST_F(XMLElementTest_251, QueryFloatText_Success_251) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

// ==================== SetText / GetText Tests ====================

TEST_F(XMLElementTest_251, SetTextString_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("hello world");
    EXPECT_STREQ(elem->GetText(), "hello world");
}

TEST_F(XMLElementTest_251, SetTextInt_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_251, SetTextUnsigned_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(100u);
    EXPECT_STREQ(elem->GetText(), "100");
}

TEST_F(XMLElementTest_251, SetTextInt64_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(INT64_C(9223372036854775807));
    EXPECT_STREQ(elem->GetText(), "9223372036854775807");
}

TEST_F(XMLElementTest_251, SetTextBoolTrue_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_251, SetTextBoolFalse_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(false);
    EXPECT_STREQ(elem->GetText(), "false");
}

TEST_F(XMLElementTest_251, SetTextDouble_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    // Verify it parses back correctly
    double val = 0.0;
    elem->QueryDoubleText(&val);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(XMLElementTest_251, SetTextFloat_GetText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(1.5f);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    float val = 0.0f;
    elem->QueryFloatText(&val);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

TEST_F(XMLElementTest_251, GetText_ReturnsNullWhenEmpty_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_251, GetText_ReturnsTextContent_251) {
    doc.Parse("<root>sample text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "sample text");
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_251, SetAttribute_GetAttribute_String_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("name", "value");
    EXPECT_STREQ(elem->Attribute("name"), "value");
}

TEST_F(XMLElementTest_251, Attribute_ReturnsNullWhenNotFound_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_251, IntAttribute_ReturnsDefault_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("missing", 42), 42);
}

TEST_F(XMLElementTest_251, IntAttribute_ReturnsValue_251) {
    doc.Parse("<root val=\"123\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), 123);
}

TEST_F(XMLElementTest_251, UnsignedAttribute_ReturnsValue_251) {
    doc.Parse("<root val=\"456\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0u), 456u);
}

TEST_F(XMLElementTest_251, BoolAttribute_ReturnsTrue_251) {
    doc.Parse("<root flag=\"true\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_251, DoubleAttribute_ReturnsValue_251) {
    doc.Parse("<root val=\"2.718\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("val", 0.0), 2.718);
}

TEST_F(XMLElementTest_251, FloatAttribute_ReturnsValue_251) {
    doc.Parse("<root val=\"1.5\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 1.5f);
}

TEST_F(XMLElementTest_251, Int64Attribute_ReturnsValue_251) {
    doc.Parse("<root val=\"9223372036854775807\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("val", 0), INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_251, Unsigned64Attribute_ReturnsValue_251) {
    doc.Parse("<root val=\"18446744073709551615\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("val", 0), UINT64_C(18446744073709551615));
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_251, DeleteAttribute_RemovesAttribute_251) {
    doc.Parse("<root attr=\"val\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_NE(elem->Attribute("attr"), nullptr);
    elem->DeleteAttribute("attr");
    EXPECT_EQ(elem->Attribute("attr"), nullptr);
}

TEST_F(XMLElementTest_251, DeleteAttribute_NonExistentDoesNotCrash_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("nonexistent"); // Should not crash
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_251, FindAttribute_ReturnsAttribute_251) {
    doc.Parse("<root attr=\"value\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "value");
}

TEST_F(XMLElementTest_251, FindAttribute_ReturnsNullWhenNotFound_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FindAttribute("missing"), nullptr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_251, FirstAttribute_ReturnsFirstWhenExists_251) {
    doc.Parse("<root a=\"1\" b=\"2\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_251, FirstAttribute_ReturnsNullWhenNoAttributes_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_251, Name_ReturnsElementName_251) {
    doc.Parse("<myElement></myElement>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_251, SetName_ChangesElementName_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_251, InsertNewChildElement_CreatesChild_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(elem->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_251, InsertNewComment_CreatesComment_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("test comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_251, InsertNewText_CreatesText_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

TEST_F(XMLElementTest_251, InsertNewDeclaration_CreatesDeclaration_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("test");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_251, InsertNewUnknown_CreatesUnknown_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("test");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_251, ToElement_ReturnsSelf_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_251, ShallowClone_CreatesClone_251) {
    doc.Parse("<root attr=\"val\">text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
    // ShallowClone should not copy children
    EXPECT_EQ(cloneElem->FirstChild(), nullptr);
    doc.DeleteNode(clone);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_251, ShallowEqual_SameElement_251) {
    doc.Parse("<root attr=\"val\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"></root>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_251, ShallowEqual_DifferentName_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDocument doc2;
    doc2.Parse("<other></other>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_251, ShallowEqual_DifferentAttributes_251) {
    doc.Parse("<root attr=\"val1\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDocument doc2;
    doc2.Parse("<root attr=\"val2\"></root>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_251, QueryIntAttribute_Success_251) {
    doc.Parse("<root val=\"10\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    XMLError err = elem->QueryIntAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, 10);
}

TEST_F(XMLElementTest_251, QueryIntAttribute_NotFound_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    XMLError err = elem->QueryIntAttribute("missing", &v);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_251, QueryStringAttribute_Success_251) {
    doc.Parse("<root val=\"hello\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* v = nullptr;
    XMLError err = elem->QueryStringAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(v, "hello");
}

// ==================== Boundary / Edge Cases ====================

TEST_F(XMLElementTest_251, IntText_LargePositiveValue_251) {
    doc.Parse("<root>2147483647</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 2147483647);
}

TEST_F(XMLElementTest_251, IntText_LargeNegativeValue_251) {
    doc.Parse("<root>-2147483648</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = elem->IntText(0);
    EXPECT_EQ(val, -2147483648);
}

TEST_F(XMLElementTest_251, SetText_OverwriteExistingText_251) {
    doc.Parse("<root>old text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("new text");
    EXPECT_STREQ(elem->GetText(), "new text");
}

TEST_F(XMLElementTest_251, SetAttribute_OverwriteExisting_251) {
    doc.Parse("<root attr=\"old\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("attr", "new");
    EXPECT_STREQ(elem->Attribute("attr"), "new");
}

TEST_F(XMLElementTest_251, MultipleAttributes_251) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("a"), "1");
    EXPECT_STREQ(elem->Attribute("b"), "2");
    EXPECT_STREQ(elem->Attribute("c"), "3");
}

TEST_F(XMLElementTest_251, SetTextUint64_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(UINT64_C(18446744073709551615));
    EXPECT_EQ(elem->Unsigned64Text(0), UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_251, Attribute_WithValueMatch_251) {
    doc.Parse("<root attr=\"match\"></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr", "match"), "match");
    EXPECT_EQ(elem->Attribute("attr", "nomatch"), nullptr);
}

TEST_F(XMLElementTest_251, ClosingType_251) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // For a normal element, closing type should be OPEN (0)
    // This tests the getter exists and returns a value
    auto ct = elem->ClosingType();
    (void)ct; // Just verify it doesn't crash
}

// ==================== Accept Visitor Tests ====================

TEST_F(XMLElementTest_251, Accept_WithPrinter_251) {
    doc.Parse("<root><child>text</child></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLPrinter printer;
    bool result = elem->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // The output should contain the element
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// ==================== GetText with child element ====================

TEST_F(XMLElementTest_251, GetText_ReturnsNullWhenFirstChildIsNotText_251) {
    doc.Parse("<root><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // First child is an element, not text
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_251, GetText_ReturnsTextWhenMixedContent_251) {
    doc.Parse("<root>text<child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "text");
}
