#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_257 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== FloatText Tests ====================

TEST_F(XMLElementTest_257, FloatText_ReturnsTextAsFloat_257) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(0.0f);
    EXPECT_NEAR(result, 3.14f, 0.001f);
}

TEST_F(XMLElementTest_257, FloatText_ReturnsDefaultWhenNoText_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(42.5f);
    EXPECT_FLOAT_EQ(result, 42.5f);
}

TEST_F(XMLElementTest_257, FloatText_ReturnsDefaultWhenTextIsNotNumeric_257) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(99.9f);
    EXPECT_FLOAT_EQ(result, 99.9f);
}

TEST_F(XMLElementTest_257, FloatText_NegativeFloat_257) {
    doc.Parse("<root>-7.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(result, -7.5f);
}

TEST_F(XMLElementTest_257, FloatText_ZeroValue_257) {
    doc.Parse("<root>0.0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(1.0f);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(XMLElementTest_257, FloatText_LargeFloat_257) {
    doc.Parse("<root>1.0e10</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(0.0f);
    EXPECT_NEAR(result, 1.0e10f, 1.0e5f);
}

TEST_F(XMLElementTest_257, FloatText_SmallFloat_257) {
    doc.Parse("<root>1.0e-10</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(0.0f);
    EXPECT_NEAR(result, 1.0e-10f, 1.0e-15f);
}

TEST_F(XMLElementTest_257, FloatText_IntegerTextParsedAsFloat_257) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(result, 42.0f);
}

// ==================== SetText / GetText Tests ====================

TEST_F(XMLElementTest_257, SetTextFloat_GetText_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(2.718f);
    float result = elem->FloatText(0.0f);
    EXPECT_NEAR(result, 2.718f, 0.01f);
}

TEST_F(XMLElementTest_257, SetTextString_GetText_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("Hello World");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello World");
}

TEST_F(XMLElementTest_257, SetTextInt_GetIntText_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(123);
    int result = elem->IntText(0);
    EXPECT_EQ(result, 123);
}

TEST_F(XMLElementTest_257, SetTextUnsigned_GetUnsignedText_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((unsigned)456u);
    unsigned result = elem->UnsignedText(0u);
    EXPECT_EQ(result, 456u);
}

TEST_F(XMLElementTest_257, SetTextInt64_GetInt64Text_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 9223372036854775807LL;
    elem->SetText(val);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, val);
}

TEST_F(XMLElementTest_257, SetTextUint64_GetUnsigned64Text_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 18446744073709551615ULL;
    elem->SetText(val);
    uint64_t result = elem->Unsigned64Text(0);
    EXPECT_EQ(result, val);
}

TEST_F(XMLElementTest_257, SetTextBool_GetBoolText_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    bool result = elem->BoolText(false);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_257, SetTextDouble_GetDoubleText_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14159265358979);
    double result = elem->DoubleText(0.0);
    EXPECT_NEAR(result, 3.14159265358979, 1.0e-10);
}

// ==================== QueryText Tests ====================

TEST_F(XMLElementTest_257, QueryFloatText_Success_257) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

TEST_F(XMLElementTest_257, QueryFloatText_NoText_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 99.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 99.0f);
}

TEST_F(XMLElementTest_257, QueryIntText_Success_257) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_257, QueryIntText_NonNumeric_257) {
    doc.Parse("<root>hello</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = -1;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(val, -1);
}

TEST_F(XMLElementTest_257, QueryUnsignedText_Success_257) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_257, QueryBoolText_True_257) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_257, QueryBoolText_False_257) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_257, QueryDoubleText_Success_257) {
    doc.Parse("<root>2.71828</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 2.71828, 1e-5);
}

TEST_F(XMLElementTest_257, QueryInt64Text_Success_257) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 9223372036854775807LL);
}

TEST_F(XMLElementTest_257, QueryUnsigned64Text_Success_257) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 18446744073709551615ULL);
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_257, SetAttribute_GetIntAttribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 10);
    int result = elem->IntAttribute("val", 0);
    EXPECT_EQ(result, 10);
}

TEST_F(XMLElementTest_257, SetAttribute_GetUnsignedAttribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", (unsigned)20);
    unsigned result = elem->UnsignedAttribute("val", 0u);
    EXPECT_EQ(result, 20u);
}

TEST_F(XMLElementTest_257, SetAttribute_GetInt64Attribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", (int64_t)123456789012345LL);
    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, 123456789012345LL);
}

TEST_F(XMLElementTest_257, SetAttribute_GetUnsigned64Attribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", (uint64_t)18446744073709551615ULL);
    uint64_t result = elem->Unsigned64Attribute("val", 0);
    EXPECT_EQ(result, 18446744073709551615ULL);
}

TEST_F(XMLElementTest_257, SetAttribute_GetBoolAttribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    bool result = elem->BoolAttribute("flag", false);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_257, SetAttribute_GetDoubleAttribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 1.23456789);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_NEAR(result, 1.23456789, 1e-8);
}

TEST_F(XMLElementTest_257, SetAttribute_GetFloatAttribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 5.5f);
    float result = elem->FloatAttribute("val", 0.0f);
    EXPECT_FLOAT_EQ(result, 5.5f);
}

TEST_F(XMLElementTest_257, SetAttribute_StringValue_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("name", "test");
    const char* result = elem->Attribute("name");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "test");
}

TEST_F(XMLElementTest_257, Attribute_NonExistentReturnsNull_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("nonexistent");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementTest_257, IntAttribute_NonExistentReturnsDefault_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int result = elem->IntAttribute("nonexistent", 77);
    EXPECT_EQ(result, 77);
}

TEST_F(XMLElementTest_257, FloatAttribute_NonExistentReturnsDefault_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatAttribute("nonexistent", 3.3f);
    EXPECT_FLOAT_EQ(result, 3.3f);
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_257, QueryIntAttribute_Success_257) {
    doc.Parse("<root val=\"55\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntAttribute("val", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 55);
}

TEST_F(XMLElementTest_257, QueryIntAttribute_NoAttribute_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = -1;
    XMLError err = elem->QueryIntAttribute("val", &val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_257, QueryFloatAttribute_Success_257) {
    doc.Parse("<root val=\"1.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    XMLError err = elem->QueryFloatAttribute("val", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

TEST_F(XMLElementTest_257, QueryStringAttribute_Success_257) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("val", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "hello");
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_257, FindAttribute_Exists_257) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_257, FindAttribute_NotExists_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    EXPECT_EQ(attr, nullptr);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_257, DeleteAttribute_RemovesAttribute_257) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_NE(elem->FindAttribute("attr"), nullptr);
    elem->DeleteAttribute("attr");
    EXPECT_EQ(elem->FindAttribute("attr"), nullptr);
}

TEST_F(XMLElementTest_257, DeleteAttribute_NonExistent_NoError_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_EQ(elem->FindAttribute("nonexistent"), nullptr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_257, FirstAttribute_HasAttributes_257) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_257, FirstAttribute_NoAttributes_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_257, Name_ReturnsCorrectName_257) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_257, SetName_ChangesName_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// ==================== InsertNew* Tests ====================

TEST_F(XMLElementTest_257, InsertNewChildElement_CreatesChild_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_NE(elem->FirstChildElement("child"), nullptr);
}

TEST_F(XMLElementTest_257, InsertNewComment_CreatesComment_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("test comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_257, InsertNewText_CreatesText_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    const char* t = elem->GetText();
    ASSERT_NE(t, nullptr);
    EXPECT_STREQ(t, "some text");
}

TEST_F(XMLElementTest_257, InsertNewDeclaration_CreatesDeclaration_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_257, InsertNewUnknown_CreatesUnknown_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST_F(XMLElementTest_257, ShallowClone_ClonesElement_257) {
    doc.Parse("<root attr=\"val\">text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
}

TEST_F(XMLElementTest_257, ShallowEqual_SameElements_257) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_257, ShallowEqual_DifferentElements_257) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_257, ToElement_ReturnsNonNull_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== GetText Tests ====================

TEST_F(XMLElementTest_257, GetText_NoChildren_ReturnsNull_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_257, GetText_WithText_ReturnsText_257) {
    doc.Parse("<root>hello</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello");
}

// ==================== IntText / UnsignedText / etc. Default Values ====================

TEST_F(XMLElementTest_257, IntText_ReturnsDefault_WhenEmpty_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(100), 100);
}

TEST_F(XMLElementTest_257, UnsignedText_ReturnsDefault_WhenEmpty_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(200u), 200u);
}

TEST_F(XMLElementTest_257, Int64Text_ReturnsDefault_WhenEmpty_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(300LL), 300LL);
}

TEST_F(XMLElementTest_257, Unsigned64Text_ReturnsDefault_WhenEmpty_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(400ULL), 400ULL);
}

TEST_F(XMLElementTest_257, BoolText_ReturnsDefault_WhenEmpty_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_257, DoubleText_ReturnsDefault_WhenEmpty_257) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(9.99), 9.99);
}

// ==================== Attribute with value matching ====================

TEST_F(XMLElementTest_257, Attribute_WithValueMatch_ReturnsValue_257) {
    doc.Parse("<root attr=\"expected\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("attr", "expected");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "expected");
}

TEST_F(XMLElementTest_257, Attribute_WithValueMismatch_ReturnsNull_257) {
    doc.Parse("<root attr=\"actual\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("attr", "expected");
    EXPECT_EQ(result, nullptr);
}

// ==================== Multiple Attributes ====================

TEST_F(XMLElementTest_257, MultipleAttributes_SetAndGet_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("a", 1);
    elem->SetAttribute("b", 2);
    elem->SetAttribute("c", 3);
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_EQ(elem->IntAttribute("b", 0), 2);
    EXPECT_EQ(elem->IntAttribute("c", 0), 3);
}

TEST_F(XMLElementTest_257, OverwriteAttribute_257) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", "new");
    EXPECT_STREQ(elem->Attribute("val"), "new");
}

// ==================== Accept / Visitor Tests ====================

TEST_F(XMLElementTest_257, Accept_WithVisitor_257) {
    doc.Parse("<root><child/></root>");
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

// ==================== Complex XML Structure ====================

TEST_F(XMLElementTest_257, ComplexNestedStructure_257) {
    const char* xml = "<root>"
                      "  <child1 a=\"1\">text1</child1>"
                      "  <child2 b=\"2\">text2</child2>"
                      "</root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    EXPECT_EQ(child1->IntAttribute("a", 0), 1);
    EXPECT_STREQ(child1->GetText(), "text1");

    XMLElement* child2 = root->FirstChildElement("child2");
    ASSERT_NE(child2, nullptr);
    EXPECT_EQ(child2->IntAttribute("b", 0), 2);
    EXPECT_STREQ(child2->GetText(), "text2");
}

// ==================== ClosingType Tests ====================

TEST_F(XMLElementTest_257, ClosingType_SelfClosing_257) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Just verify it doesn't crash; the actual value depends on implementation
    elem->ClosingType();
}
