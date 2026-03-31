#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_256 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== DoubleText Tests ====================

TEST_F(XMLElementTest_256, DoubleText_ReturnsTextAsDouble_256) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), 3.14);
}

TEST_F(XMLElementTest_256, DoubleText_ReturnsDefaultWhenNoText_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(99.9), 99.9);
}

TEST_F(XMLElementTest_256, DoubleText_ReturnsDefaultWhenTextIsNotNumber_256) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(42.0), 42.0);
}

TEST_F(XMLElementTest_256, DoubleText_NegativeValue_256) {
    doc.Parse("<root>-2.718</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), -2.718);
}

TEST_F(XMLElementTest_256, DoubleText_ZeroValue_256) {
    doc.Parse("<root>0.0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(55.5), 0.0);
}

TEST_F(XMLElementTest_256, DoubleText_LargeValue_256) {
    doc.Parse("<root>1.7976931348623157e+308</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), 1.7976931348623157e+308);
}

TEST_F(XMLElementTest_256, DoubleText_SmallValue_256) {
    doc.Parse("<root>2.2250738585072014e-308</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), 2.2250738585072014e-308);
}

TEST_F(XMLElementTest_256, DoubleText_IntegerTextAsDouble_256) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), 42.0);
}

// ==================== QueryDoubleText Tests ====================

TEST_F(XMLElementTest_256, QueryDoubleText_SuccessfulParse_256) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 1.5);
}

TEST_F(XMLElementTest_256, QueryDoubleText_NoTextReturnsError_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_256, QueryDoubleText_InvalidTextReturnsError_256) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 123.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== SetText / GetText Tests ====================

TEST_F(XMLElementTest_256, SetTextDouble_GetText_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    // The text should represent 3.14
    double val = elem->DoubleText(0.0);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_256, SetTextInt_IntText_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    EXPECT_EQ(elem->IntText(0), 42);
}

TEST_F(XMLElementTest_256, SetTextUnsigned_UnsignedText_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((unsigned)100);
    EXPECT_EQ(elem->UnsignedText(0), 100u);
}

TEST_F(XMLElementTest_256, SetTextBool_BoolText_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_EQ(elem->BoolText(false), true);
}

TEST_F(XMLElementTest_256, SetTextFloat_FloatText_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(2.5f);
    EXPECT_NEAR(elem->FloatText(0.0f), 2.5f, 0.001f);
}

TEST_F(XMLElementTest_256, SetTextInt64_Int64Text_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t bigVal = 9223372036854775807LL;
    elem->SetText(bigVal);
    EXPECT_EQ(elem->Int64Text(0), bigVal);
}

TEST_F(XMLElementTest_256, SetTextUint64_Unsigned64Text_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetText(bigVal);
    EXPECT_EQ(elem->Unsigned64Text(0), bigVal);
}

TEST_F(XMLElementTest_256, SetTextString_GetText_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("Hello World");
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_256, SetAttribute_Attribute_String_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("name", "value");
    EXPECT_STREQ(elem->Attribute("name"), "value");
}

TEST_F(XMLElementTest_256, Attribute_NonExistent_ReturnsNull_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_256, SetAttribute_IntAttribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 10);
    EXPECT_EQ(elem->IntAttribute("val", 0), 10);
}

TEST_F(XMLElementTest_256, IntAttribute_DefaultWhenMissing_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("missing", 77), 77);
}

TEST_F(XMLElementTest_256, SetAttribute_UnsignedAttribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", (unsigned)255);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0), 255u);
}

TEST_F(XMLElementTest_256, SetAttribute_BoolAttribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    EXPECT_EQ(elem->BoolAttribute("flag", false), true);
}

TEST_F(XMLElementTest_256, SetAttribute_DoubleAttribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("pi", 3.14159);
    EXPECT_NEAR(elem->DoubleAttribute("pi", 0.0), 3.14159, 0.0001);
}

TEST_F(XMLElementTest_256, SetAttribute_FloatAttribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("f", 1.5f);
    EXPECT_NEAR(elem->FloatAttribute("f", 0.0f), 1.5f, 0.001f);
}

TEST_F(XMLElementTest_256, SetAttribute_Int64Attribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 123456789012345LL;
    elem->SetAttribute("big", val);
    EXPECT_EQ(elem->Int64Attribute("big", 0), val);
}

TEST_F(XMLElementTest_256, SetAttribute_Uint64Attribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 18446744073709551615ULL;
    elem->SetAttribute("ubig", val);
    EXPECT_EQ(elem->Unsigned64Attribute("ubig", 0), val);
}

TEST_F(XMLElementTest_256, DoubleAttribute_DefaultWhenMissing_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 1.23), 1.23);
}

TEST_F(XMLElementTest_256, FloatAttribute_DefaultWhenMissing_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 4.56f), 4.56f);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_256, DeleteAttribute_RemovesAttribute_256) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_NE(elem->Attribute("attr"), nullptr);
    elem->DeleteAttribute("attr");
    EXPECT_EQ(elem->Attribute("attr"), nullptr);
}

TEST_F(XMLElementTest_256, DeleteAttribute_NonExistent_NoError_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_256, FindAttribute_Exists_256) {
    doc.Parse("<root attr=\"123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr");
    EXPECT_STREQ(attr->Value(), "123");
}

TEST_F(XMLElementTest_256, FindAttribute_NotExists_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("nope");
    EXPECT_EQ(attr, nullptr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_256, FirstAttribute_Exists_256) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* first = elem->FirstAttribute();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "a");
}

TEST_F(XMLElementTest_256, FirstAttribute_NoAttributes_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* first = elem->FirstAttribute();
    EXPECT_EQ(first, nullptr);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_256, Name_ReturnsElementName_256) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_256, SetName_ChangesName_256) {
    doc.Parse("<old/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// ==================== InsertNew* Tests ====================

TEST_F(XMLElementTest_256, InsertNewChildElement_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(elem->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_256, InsertNewComment_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_256, InsertNewText_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

TEST_F(XMLElementTest_256, InsertNewDeclaration_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_256, InsertNewUnknown_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_256, ToElement_ReturnsSelf_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_256, ShallowClone_ClonesElement_256) {
    doc.Parse("<root attr=\"val\">text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
    // ShallowClone does not clone children
    EXPECT_EQ(cloneElem->GetText(), nullptr);
    doc.DeleteNode(clone);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_256, ShallowEqual_SameElementsAreEqual_256) {
    doc.Parse("<root attr=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"1\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_256, ShallowEqual_DifferentAttributes_256) {
    doc.Parse("<root attr=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_256, ShallowEqual_DifferentNames_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_256, QueryIntAttribute_Success_256) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    EXPECT_EQ(elem->QueryIntAttribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 42);
}

TEST_F(XMLElementTest_256, QueryIntAttribute_NoAttribute_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    EXPECT_NE(elem->QueryIntAttribute("val", &v), XML_SUCCESS);
}

TEST_F(XMLElementTest_256, QueryDoubleAttribute_Success_256) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double v = 0.0;
    EXPECT_EQ(elem->QueryDoubleAttribute("val", &v), XML_SUCCESS);
    EXPECT_NEAR(v, 3.14, 0.001);
}

TEST_F(XMLElementTest_256, QueryBoolAttribute_Success_256) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool v = false;
    EXPECT_EQ(elem->QueryBoolAttribute("val", &v), XML_SUCCESS);
    EXPECT_TRUE(v);
}

TEST_F(XMLElementTest_256, QueryStringAttribute_Success_256) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* v = nullptr;
    EXPECT_EQ(elem->QueryStringAttribute("val", &v), XML_SUCCESS);
    EXPECT_STREQ(v, "hello");
}

// ==================== QueryIntText / QueryUnsignedText etc ====================

TEST_F(XMLElementTest_256, QueryIntText_Success_256) {
    doc.Parse("<root>123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_256, QueryUnsignedText_Success_256) {
    doc.Parse("<root>456</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    EXPECT_EQ(elem->QueryUnsignedText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 456u);
}

TEST_F(XMLElementTest_256, QueryInt64Text_Success_256) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 0;
    EXPECT_EQ(elem->QueryInt64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 9223372036854775807LL);
}

TEST_F(XMLElementTest_256, QueryUnsigned64Text_Success_256) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 0;
    EXPECT_EQ(elem->QueryUnsigned64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 18446744073709551615ULL);
}

TEST_F(XMLElementTest_256, QueryBoolText_True_256) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_256, QueryBoolText_False_256) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_256, QueryFloatText_Success_256) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    EXPECT_EQ(elem->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 1.5f, 0.001f);
}

// ==================== Default text accessors ====================

TEST_F(XMLElementTest_256, IntText_Default_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(999), 999);
}

TEST_F(XMLElementTest_256, UnsignedText_Default_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(888u), 888u);
}

TEST_F(XMLElementTest_256, Int64Text_Default_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(777LL), 777LL);
}

TEST_F(XMLElementTest_256, Unsigned64Text_Default_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(666ULL), 666ULL);
}

TEST_F(XMLElementTest_256, BoolText_Default_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolText(true), true);
}

TEST_F(XMLElementTest_256, FloatText_Default_256) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(5.5f), 5.5f);
}

// ==================== GetText on various content ====================

TEST_F(XMLElementTest_256, GetText_NoChildren_ReturnsNull_256) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_256, GetText_WithText_ReturnsText_256) {
    doc.Parse("<root>Hello</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Hello");
}

TEST_F(XMLElementTest_256, GetText_ChildElementOnly_ReturnsNull_256) {
    doc.Parse("<root><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // First child is an element, not text
    EXPECT_EQ(elem->GetText(), nullptr);
}

// ==================== Attribute with value filter ====================

TEST_F(XMLElementTest_256, Attribute_WithValueMatch_256) {
    doc.Parse("<root attr=\"match\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr", "match"), "match");
}

TEST_F(XMLElementTest_256, Attribute_WithValueMismatch_256) {
    doc.Parse("<root attr=\"actual\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("attr", "expected"), nullptr);
}

// ==================== Multiple attributes ====================

TEST_F(XMLElementTest_256, MultipleAttributes_256) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_EQ(elem->IntAttribute("b", 0), 2);
    EXPECT_EQ(elem->IntAttribute("c", 0), 3);
}

TEST_F(XMLElementTest_256, OverwriteAttribute_256) {
    doc.Parse("<root attr=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("attr", "new");
    EXPECT_STREQ(elem->Attribute("attr"), "new");
}

// ==================== Accept Visitor ====================

TEST_F(XMLElementTest_256, Accept_PrinterVisitor_256) {
    doc.Parse("<root><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLPrinter printer;
    bool result = elem->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // Output should contain root and child
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
    EXPECT_NE(std::string(output).find("child"), std::string::npos);
}

// ==================== SetText overwrites ====================

TEST_F(XMLElementTest_256, SetTextString_OverwritesExistingText_256) {
    doc.Parse("<root>old</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("new");
    EXPECT_STREQ(elem->GetText(), "new");
}

TEST_F(XMLElementTest_256, SetTextInt_OverwritesExistingText_256) {
    doc.Parse("<root>old</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(99);
    EXPECT_EQ(elem->IntText(0), 99);
}
