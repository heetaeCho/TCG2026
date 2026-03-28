#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_106 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// --- ClosingType Tests ---

TEST_F(XMLElementTest_106, ClosingType_DefaultIsOpen_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // A self-closing element like <root/> should have CLOSED closing type
    EXPECT_EQ(elem->ClosingType(), CLOSED);
}

TEST_F(XMLElementTest_106, ClosingType_OpenElement_106) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ClosingType(), OPEN);
}

// --- Name Tests ---

TEST_F(XMLElementTest_106, Name_ReturnsCorrectName_106) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_106, SetName_ChangesName_106) {
    doc.Parse("<old/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// --- Attribute Tests ---

TEST_F(XMLElementTest_106, Attribute_ReturnsValue_106) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr"), "hello");
}

TEST_F(XMLElementTest_106, Attribute_ReturnsNullForMissing_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_106, Attribute_WithValueMatch_106) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr", "hello"), "hello");
    EXPECT_EQ(elem->Attribute("attr", "world"), nullptr);
}

// --- FindAttribute Tests ---

TEST_F(XMLElementTest_106, FindAttribute_ReturnsAttribute_106) {
    doc.Parse("<root x=\"10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("x");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "x");
    EXPECT_STREQ(attr->Value(), "10");
}

TEST_F(XMLElementTest_106, FindAttribute_ReturnsNullForMissing_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FindAttribute("missing"), nullptr);
}

// --- FirstAttribute Tests ---

TEST_F(XMLElementTest_106, FirstAttribute_ReturnsFirst_106) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_106, FirstAttribute_NullWhenNoAttributes_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

// --- SetAttribute / QueryAttribute Tests ---

TEST_F(XMLElementTest_106, SetAttribute_String_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("key", "value");
    EXPECT_STREQ(elem->Attribute("key"), "value");
}

TEST_F(XMLElementTest_106, SetAttribute_Int_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(elem->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_106, SetAttribute_Unsigned_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", (unsigned)100);
    EXPECT_EQ(elem->UnsignedAttribute("num", 0), 100u);
}

TEST_F(XMLElementTest_106, SetAttribute_Int64_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 9223372036854775807LL;
    elem->SetAttribute("num", val);
    EXPECT_EQ(elem->Int64Attribute("num", 0), val);
}

TEST_F(XMLElementTest_106, SetAttribute_Uint64_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 18446744073709551615ULL;
    elem->SetAttribute("num", val);
    EXPECT_EQ(elem->Unsigned64Attribute("num", 0), val);
}

TEST_F(XMLElementTest_106, SetAttribute_Bool_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    EXPECT_EQ(elem->BoolAttribute("flag", false), true);
}

TEST_F(XMLElementTest_106, SetAttribute_Double_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 3.14);
    EXPECT_NEAR(elem->DoubleAttribute("val", 0.0), 3.14, 0.001);
}

TEST_F(XMLElementTest_106, SetAttribute_Float_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 2.5f);
    EXPECT_NEAR(elem->FloatAttribute("val", 0.0f), 2.5f, 0.001f);
}

// --- Attribute default value tests ---

TEST_F(XMLElementTest_106, IntAttribute_DefaultValue_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("missing", 99), 99);
}

TEST_F(XMLElementTest_106, UnsignedAttribute_DefaultValue_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("missing", 55u), 55u);
}

TEST_F(XMLElementTest_106, Int64Attribute_DefaultValue_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("missing", 123456789LL), 123456789LL);
}

TEST_F(XMLElementTest_106, Unsigned64Attribute_DefaultValue_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("missing", 999ULL), 999ULL);
}

TEST_F(XMLElementTest_106, BoolAttribute_DefaultValue_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolAttribute("missing", true), true);
    EXPECT_EQ(elem->BoolAttribute("missing", false), false);
}

TEST_F(XMLElementTest_106, DoubleAttribute_DefaultValue_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 1.5), 1.5);
}

TEST_F(XMLElementTest_106, FloatAttribute_DefaultValue_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 1.5f), 1.5f);
}

// --- QueryIntAttribute Tests ---

TEST_F(XMLElementTest_106, QueryIntAttribute_Success_106) {
    doc.Parse("<root num=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntAttribute("num", &val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_106, QueryIntAttribute_NoAttribute_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntAttribute("num", &val), XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_106, QueryIntAttribute_WrongType_106) {
    doc.Parse("<root num=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntAttribute("num", &val), XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLElementTest_106, QueryUnsignedAttribute_Success_106) {
    doc.Parse("<root num=\"100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    EXPECT_EQ(elem->QueryUnsignedAttribute("num", &val), XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_106, QueryBoolAttribute_True_106) {
    doc.Parse("<root flag=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolAttribute("flag", &val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_106, QueryBoolAttribute_False_106) {
    doc.Parse("<root flag=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    EXPECT_EQ(elem->QueryBoolAttribute("flag", &val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_106, QueryDoubleAttribute_Success_106) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0;
    EXPECT_EQ(elem->QueryDoubleAttribute("val", &val), XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_106, QueryFloatAttribute_Success_106) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0;
    EXPECT_EQ(elem->QueryFloatAttribute("val", &val), XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 0.001f);
}

TEST_F(XMLElementTest_106, QueryStringAttribute_Success_106) {
    doc.Parse("<root str=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    EXPECT_EQ(elem->QueryStringAttribute("str", &val), XML_SUCCESS);
    EXPECT_STREQ(val, "hello");
}

TEST_F(XMLElementTest_106, QueryStringAttribute_NoAttribute_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    EXPECT_EQ(elem->QueryStringAttribute("str", &val), XML_NO_ATTRIBUTE);
}

// --- DeleteAttribute Tests ---

TEST_F(XMLElementTest_106, DeleteAttribute_RemovesAttribute_106) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("a");
    EXPECT_EQ(elem->Attribute("a"), nullptr);
    EXPECT_STREQ(elem->Attribute("b"), "2");
}

TEST_F(XMLElementTest_106, DeleteAttribute_NonExistent_106) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_STREQ(elem->Attribute("a"), "1");
}

// --- GetText / SetText Tests ---

TEST_F(XMLElementTest_106, GetText_ReturnsTextContent_106) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

TEST_F(XMLElementTest_106, GetText_ReturnsNullWhenNoText_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_106, SetText_String_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("TestText");
    EXPECT_STREQ(elem->GetText(), "TestText");
}

TEST_F(XMLElementTest_106, SetText_Int_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_106, SetText_Unsigned_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((unsigned)100);
    EXPECT_STREQ(elem->GetText(), "100");
}

TEST_F(XMLElementTest_106, SetText_Int64_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((int64_t)9876543210LL);
    EXPECT_STREQ(elem->GetText(), "9876543210");
}

TEST_F(XMLElementTest_106, SetText_Uint64_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((uint64_t)12345678901ULL);
    EXPECT_STREQ(elem->GetText(), "12345678901");
}

TEST_F(XMLElementTest_106, SetText_Bool_True_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_106, SetText_Bool_False_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(false);
    EXPECT_STREQ(elem->GetText(), "false");
}

TEST_F(XMLElementTest_106, SetText_Double_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    // Just check that GetText returns something parseable
    ASSERT_NE(elem->GetText(), nullptr);
    double parsed = atof(elem->GetText());
    EXPECT_NEAR(parsed, 3.14, 0.001);
}

TEST_F(XMLElementTest_106, SetText_Float_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(2.5f);
    ASSERT_NE(elem->GetText(), nullptr);
    float parsed = (float)atof(elem->GetText());
    EXPECT_NEAR(parsed, 2.5f, 0.001f);
}

TEST_F(XMLElementTest_106, SetText_OverwritesExisting_106) {
    doc.Parse("<root>Old</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("New");
    EXPECT_STREQ(elem->GetText(), "New");
}

// --- QueryIntText / QueryUnsignedText etc. ---

TEST_F(XMLElementTest_106, QueryIntText_Success_106) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_106, QueryIntText_NoText_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_NE(elem->QueryIntText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_106, QueryIntText_WrongType_106) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_NE(elem->QueryIntText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_106, QueryUnsignedText_Success_106) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    EXPECT_EQ(elem->QueryUnsignedText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_106, QueryInt64Text_Success_106) {
    doc.Parse("<root>9876543210</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 0;
    EXPECT_EQ(elem->QueryInt64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 9876543210LL);
}

TEST_F(XMLElementTest_106, QueryUnsigned64Text_Success_106) {
    doc.Parse("<root>12345678901</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 0;
    EXPECT_EQ(elem->QueryUnsigned64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 12345678901ULL);
}

TEST_F(XMLElementTest_106, QueryBoolText_True_106) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_106, QueryBoolText_False_106) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_106, QueryDoubleText_Success_106) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0;
    EXPECT_EQ(elem->QueryDoubleText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_106, QueryFloatText_Success_106) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0;
    EXPECT_EQ(elem->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 0.001f);
}

// --- IntText / UnsignedText etc. (with defaults) ---

TEST_F(XMLElementTest_106, IntText_ReturnsValue_106) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 42);
}

TEST_F(XMLElementTest_106, IntText_ReturnsDefault_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(99), 99);
}

TEST_F(XMLElementTest_106, UnsignedText_ReturnsValue_106) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(0), 100u);
}

TEST_F(XMLElementTest_106, UnsignedText_ReturnsDefault_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(55u), 55u);
}

TEST_F(XMLElementTest_106, Int64Text_ReturnsValue_106) {
    doc.Parse("<root>9876543210</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(0), 9876543210LL);
}

TEST_F(XMLElementTest_106, Int64Text_ReturnsDefault_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(77LL), 77LL);
}

TEST_F(XMLElementTest_106, Unsigned64Text_ReturnsValue_106) {
    doc.Parse("<root>12345678901</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(0), 12345678901ULL);
}

TEST_F(XMLElementTest_106, Unsigned64Text_ReturnsDefault_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(88ULL), 88ULL);
}

TEST_F(XMLElementTest_106, BoolText_ReturnsValue_106) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_106, BoolText_ReturnsDefault_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(true));
    EXPECT_FALSE(elem->BoolText(false));
}

TEST_F(XMLElementTest_106, DoubleText_ReturnsValue_106) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_NEAR(elem->DoubleText(0.0), 3.14, 0.001);
}

TEST_F(XMLElementTest_106, DoubleText_ReturnsDefault_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.5), 1.5);
}

TEST_F(XMLElementTest_106, FloatText_ReturnsValue_106) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_NEAR(elem->FloatText(0.0f), 2.5f, 0.001f);
}

TEST_F(XMLElementTest_106, FloatText_ReturnsDefault_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(1.5f), 1.5f);
}

// --- InsertNewChildElement / InsertNewComment / InsertNewText / InsertNewDeclaration / InsertNewUnknown ---

TEST_F(XMLElementTest_106, InsertNewChildElement_CreatesChild_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(elem->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_106, InsertNewComment_CreatesComment_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("my comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "my comment");
}

TEST_F(XMLElementTest_106, InsertNewText_CreatesText_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

TEST_F(XMLElementTest_106, InsertNewDeclaration_CreatesDeclaration_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_106, InsertNewUnknown_CreatesUnknown_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unk = elem->InsertNewUnknown("something");
    ASSERT_NE(unk, nullptr);
}

// --- ToElement Tests ---

TEST_F(XMLElementTest_106, ToElement_ReturnsSelf_106) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// --- ShallowClone / ShallowEqual Tests ---

TEST_F(XMLElementTest_106, ShallowClone_ClonesElement_106) {
    doc.Parse("<root attr=\"val\"/>");
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

TEST_F(XMLElementTest_106, ShallowEqual_SameElement_106) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_106, ShallowEqual_DifferentElement_106) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_106, ShallowEqual_DifferentAttributes_106) {
    doc.Parse("<root attr=\"val1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// --- QueryAttribute overload tests ---

TEST_F(XMLElementTest_106, QueryAttribute_Int_106) {
    doc.Parse("<root x=\"10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 10);
}

TEST_F(XMLElementTest_106, QueryAttribute_Unsigned_106) {
    doc.Parse("<root x=\"10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 10u);
}

TEST_F(XMLElementTest_106, QueryAttribute_Int64_106) {
    doc.Parse("<root x=\"9876543210\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 9876543210LL);
}

TEST_F(XMLElementTest_106, QueryAttribute_Uint64_106) {
    doc.Parse("<root x=\"12345678901\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 12345678901ULL);
}

TEST_F(XMLElementTest_106, QueryAttribute_Bool_106) {
    doc.Parse("<root x=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_106, QueryAttribute_Double_106) {
    doc.Parse("<root x=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_106, QueryAttribute_Float_106) {
    doc.Parse("<root x=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 0.001f);
}

TEST_F(XMLElementTest_106, QueryAttribute_String_106) {
    doc.Parse("<root x=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_STREQ(val, "hello");
}

// --- Multiple attributes ---

TEST_F(XMLElementTest_106, MultipleAttributes_106) {
    doc.Parse("<root a=\"1\" b=\"two\" c=\"3.5\" d=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_STREQ(elem->Attribute("b"), "two");
    EXPECT_NEAR(elem->FloatAttribute("c", 0.0f), 3.5f, 0.001f);
    EXPECT_TRUE(elem->BoolAttribute("d", false));
}

// --- SetAttribute overwrites existing ---

TEST_F(XMLElementTest_106, SetAttribute_OverwriteExisting_106) {
    doc.Parse("<root a=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("a", "new");
    EXPECT_STREQ(elem->Attribute("a"), "new");
}

// --- Negative int attribute ---

TEST_F(XMLElementTest_106, IntAttribute_NegativeValue_106) {
    doc.Parse("<root num=\"-42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("num", 0), -42);
}

// --- Negative int text ---

TEST_F(XMLElementTest_106, QueryIntText_NegativeValue_106) {
    doc.Parse("<root>-100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, -100);
}

// --- Empty element text ---

TEST_F(XMLElementTest_106, GetText_EmptyElement_106) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

// --- Nested elements ---

TEST_F(XMLElementTest_106, NestedElements_106) {
    doc.Parse("<root><child><grandchild/></child></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    XMLElement* grandchild = child->FirstChildElement("grandchild");
    ASSERT_NE(grandchild, nullptr);
    EXPECT_STREQ(grandchild->Name(), "grandchild");
}

// --- Accept with visitor ---

TEST_F(XMLElementTest_106, Accept_WithPrinter_106) {
    doc.Parse("<root attr=\"val\">text</root>");
    XMLElement* elem = doc