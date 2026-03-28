#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_80 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// --- ToElement ---

TEST_F(XMLElementTest_80, ToElement_ReturnsNonNull_80) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(nullptr, elem);
    EXPECT_EQ(elem, elem->ToElement());
}

// --- Name and SetName ---

TEST_F(XMLElementTest_80, Name_ReturnsElementName_80) {
    XMLElement* elem = doc.NewElement("myElement");
    EXPECT_STREQ("myElement", elem->Name());
}

TEST_F(XMLElementTest_80, SetName_ChangesElementName_80) {
    XMLElement* elem = doc.NewElement("original");
    elem->SetName("renamed");
    EXPECT_STREQ("renamed", elem->Name());
}

// --- SetAttribute / Attribute / FindAttribute ---

TEST_F(XMLElementTest_80, SetAttribute_String_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "value");
    EXPECT_STREQ("value", elem->Attribute("key"));
}

TEST_F(XMLElementTest_80, Attribute_ReturnsNullForMissing_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->Attribute("nonexistent"));
}

TEST_F(XMLElementTest_80, Attribute_WithValueMatch_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "value");
    EXPECT_STREQ("value", elem->Attribute("key", "value"));
    EXPECT_EQ(nullptr, elem->Attribute("key", "other"));
}

TEST_F(XMLElementTest_80, FindAttribute_ReturnsAttribute_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("attr1", "val1");
    const XMLAttribute* attr = elem->FindAttribute("attr1");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("attr1", attr->Name());
    EXPECT_STREQ("val1", attr->Value());
}

TEST_F(XMLElementTest_80, FindAttribute_ReturnsNullForMissing_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->FindAttribute("missing"));
}

TEST_F(XMLElementTest_80, FirstAttribute_ReturnsFirstAttribute_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");
    const XMLAttribute* first = elem->FirstAttribute();
    ASSERT_NE(nullptr, first);
    EXPECT_STREQ("first", first->Name());
}

TEST_F(XMLElementTest_80, FirstAttribute_ReturnsNullWhenNoAttributes_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->FirstAttribute());
}

// --- SetAttribute / QueryAttribute for int ---

TEST_F(XMLElementTest_80, SetAttribute_Int_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", 42);
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntAttribute("num", &val));
    EXPECT_EQ(42, val);
}

TEST_F(XMLElementTest_80, IntAttribute_DefaultValue_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(99, elem->IntAttribute("missing", 99));
}

TEST_F(XMLElementTest_80, IntAttribute_ExistingValue_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", -5);
    EXPECT_EQ(-5, elem->IntAttribute("num", 0));
}

// --- SetAttribute / QueryAttribute for unsigned ---

TEST_F(XMLElementTest_80, SetAttribute_Unsigned_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", (unsigned)100);
    unsigned val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsignedAttribute("num", &val));
    EXPECT_EQ(100u, val);
}

TEST_F(XMLElementTest_80, UnsignedAttribute_DefaultValue_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(55u, elem->UnsignedAttribute("missing", 55u));
}

// --- SetAttribute / QueryAttribute for int64 ---

TEST_F(XMLElementTest_80, SetAttribute_Int64_80) {
    XMLElement* elem = doc.NewElement("test");
    int64_t bigVal = 9223372036854775807LL;
    elem->SetAttribute("num", bigVal);
    int64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryInt64Attribute("num", &val));
    EXPECT_EQ(bigVal, val);
}

TEST_F(XMLElementTest_80, Int64Attribute_DefaultValue_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(123LL, elem->Int64Attribute("missing", 123LL));
}

// --- SetAttribute / QueryAttribute for uint64 ---

TEST_F(XMLElementTest_80, SetAttribute_Uint64_80) {
    XMLElement* elem = doc.NewElement("test");
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetAttribute("num", bigVal);
    uint64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsigned64Attribute("num", &val));
    EXPECT_EQ(bigVal, val);
}

TEST_F(XMLElementTest_80, Unsigned64Attribute_DefaultValue_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(456ULL, elem->Unsigned64Attribute("missing", 456ULL));
}

// --- SetAttribute / QueryAttribute for bool ---

TEST_F(XMLElementTest_80, SetAttribute_Bool_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("flag", true);
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolAttribute("flag", &val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_80, BoolAttribute_DefaultValue_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
}

// --- SetAttribute / QueryAttribute for double ---

TEST_F(XMLElementTest_80, SetAttribute_Double_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", 3.14159);
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryDoubleAttribute("val", &val));
    EXPECT_DOUBLE_EQ(3.14159, val);
}

TEST_F(XMLElementTest_80, DoubleAttribute_DefaultValue_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_DOUBLE_EQ(2.718, elem->DoubleAttribute("missing", 2.718));
}

// --- SetAttribute / QueryAttribute for float ---

TEST_F(XMLElementTest_80, SetAttribute_Float_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", 1.5f);
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryFloatAttribute("val", &val));
    EXPECT_FLOAT_EQ(1.5f, val);
}

TEST_F(XMLElementTest_80, FloatAttribute_DefaultValue_80) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_FLOAT_EQ(0.5f, elem->FloatAttribute("missing", 0.5f));
}

// --- QueryStringAttribute ---

TEST_F(XMLElementTest_80, QueryStringAttribute_Success_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("str", "hello");
    const char* val = nullptr;
    EXPECT_EQ(XML_SUCCESS, elem->QueryStringAttribute("str", &val));
    EXPECT_STREQ("hello", val);
}

TEST_F(XMLElementTest_80, QueryStringAttribute_NoAttribute_80) {
    XMLElement* elem = doc.NewElement("test");
    const char* val = nullptr;
    EXPECT_EQ(XML_NO_ATTRIBUTE, elem->QueryStringAttribute("missing", &val));
}

// --- QueryAttribute overloads ---

TEST_F(XMLElementTest_80, QueryAttribute_NoAttribute_Int_80) {
    XMLElement* elem = doc.NewElement("test");
    int val = 0;
    EXPECT_EQ(XML_NO_ATTRIBUTE, elem->QueryAttribute("missing", &val));
}

TEST_F(XMLElementTest_80, QueryAttribute_WrongType_Int_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", "notanumber");
    int val = 0;
    EXPECT_NE(XML_SUCCESS, elem->QueryIntAttribute("val", &val));
}

// --- DeleteAttribute ---

TEST_F(XMLElementTest_80, DeleteAttribute_RemovesAttribute_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "value");
    EXPECT_NE(nullptr, elem->Attribute("key"));
    elem->DeleteAttribute("key");
    EXPECT_EQ(nullptr, elem->Attribute("key"));
}

TEST_F(XMLElementTest_80, DeleteAttribute_NonExistent_80) {
    XMLElement* elem = doc.NewElement("test");
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_EQ(nullptr, elem->Attribute("nonexistent"));
}

// --- SetText / GetText ---

TEST_F(XMLElementTest_80, SetText_GetText_String_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("Hello World");
    EXPECT_STREQ("Hello World", elem->GetText());
}

TEST_F(XMLElementTest_80, GetText_ReturnsNullWhenNoText_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(nullptr, elem->GetText());
}

TEST_F(XMLElementTest_80, SetText_Int_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42);
    EXPECT_STREQ("42", elem->GetText());
}

TEST_F(XMLElementTest_80, SetText_UnsignedInt_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((unsigned)100);
    EXPECT_STREQ("100", elem->GetText());
}

TEST_F(XMLElementTest_80, SetText_Int64_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((int64_t)9223372036854775807LL);
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("9223372036854775807", text);
}

TEST_F(XMLElementTest_80, SetText_Uint64_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((uint64_t)18446744073709551615ULL);
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("18446744073709551615", text);
}

TEST_F(XMLElementTest_80, SetText_Bool_True_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    EXPECT_STREQ("true", elem->GetText());
}

TEST_F(XMLElementTest_80, SetText_Bool_False_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(false);
    EXPECT_STREQ("false", elem->GetText());
}

TEST_F(XMLElementTest_80, SetText_Float_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(1.5f);
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    // Float representation
    EXPECT_FLOAT_EQ(1.5f, (float)atof(text));
}

TEST_F(XMLElementTest_80, SetText_Double_80) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14159);
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_DOUBLE_EQ(3.14159, atof(text));
}

// --- QueryIntText / QueryUnsignedText / etc ---

TEST_F(XMLElementTest_80, QueryIntText_Success_80) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntText(&val));
    EXPECT_EQ(42, val);
}

TEST_F(XMLElementTest_80, QueryIntText_NoText_80) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    int val = 0;
    EXPECT_NE(XML_SUCCESS, elem->QueryIntText(&val));
}

TEST_F(XMLElementTest_80, QueryIntText_BadFormat_80) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* elem = doc.RootElement();
    int val = 0;
    EXPECT_NE(XML_SUCCESS, elem->QueryIntText(&val));
}

TEST_F(XMLElementTest_80, QueryUnsignedText_Success_80) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    unsigned val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsignedText(&val));
    EXPECT_EQ(100u, val);
}

TEST_F(XMLElementTest_80, QueryInt64Text_Success_80) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    int64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryInt64Text(&val));
    EXPECT_EQ(9223372036854775807LL, val);
}

TEST_F(XMLElementTest_80, QueryUnsigned64Text_Success_80) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    uint64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsigned64Text(&val));
    EXPECT_EQ(18446744073709551615ULL, val);
}

TEST_F(XMLElementTest_80, QueryBoolText_True_80) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolText(&val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_80, QueryBoolText_False_80) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    bool val = true;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolText(&val));
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_80, QueryDoubleText_Success_80) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryDoubleText(&val));
    EXPECT_DOUBLE_EQ(3.14, val);
}

TEST_F(XMLElementTest_80, QueryFloatText_Success_80) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryFloatText(&val));
    EXPECT_FLOAT_EQ(1.5f, val);
}

// --- IntText / UnsignedText / etc with defaults ---

TEST_F(XMLElementTest_80, IntText_WithValue_80) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_EQ(42, elem->IntText(0));
}

TEST_F(XMLElementTest_80, IntText_DefaultWhenNoText_80) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_EQ(99, elem->IntText(99));
}

TEST_F(XMLElementTest_80, UnsignedText_WithValue_80) {
    doc.Parse("<root>200</root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_EQ(200u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_80, Int64Text_WithValue_80) {
    doc.Parse("<root>123456789012345</root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_EQ(123456789012345LL, elem->Int64Text(0));
}

TEST_F(XMLElementTest_80, Unsigned64Text_WithValue_80) {
    doc.Parse("<root>123456789012345</root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_EQ(123456789012345ULL, elem->Unsigned64Text(0));
}

TEST_F(XMLElementTest_80, BoolText_True_80) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_80, BoolText_DefaultWhenNoText_80) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_TRUE(elem->BoolText(true));
    EXPECT_FALSE(elem->BoolText(false));
}

TEST_F(XMLElementTest_80, DoubleText_WithValue_80) {
    doc.Parse("<root>2.718</root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_DOUBLE_EQ(2.718, elem->DoubleText(0.0));
}

TEST_F(XMLElementTest_80, FloatText_WithValue_80) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    EXPECT_FLOAT_EQ(1.5f, elem->FloatText(0.0f));
}

// --- InsertNewChildElement ---

TEST_F(XMLElementTest_80, InsertNewChildElement_80) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
    EXPECT_EQ(child, root->FirstChildElement("child"));
}

// --- InsertNewComment ---

TEST_F(XMLElementTest_80, InsertNewComment_80) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLComment* comment = root->InsertNewComment("test comment");
    ASSERT_NE(nullptr, comment);
    EXPECT_NE(nullptr, root->FirstChild());
}

// --- InsertNewText ---

TEST_F(XMLElementTest_80, InsertNewText_80) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLText* text = root->InsertNewText("hello");
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("hello", root->GetText());
}

// --- InsertNewDeclaration ---

TEST_F(XMLElementTest_80, InsertNewDeclaration_80) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLDeclaration* decl = root->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(nullptr, decl);
}

// --- InsertNewUnknown ---

TEST_F(XMLElementTest_80, InsertNewUnknown_80) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLUnknown* unknown = root->InsertNewUnknown("something");
    ASSERT_NE(nullptr, unknown);
}

// --- ShallowClone ---

TEST_F(XMLElementTest_80, ShallowClone_CopiesElementNameAndAttributes_80) {
    doc.Parse("<root attr1=\"val1\" attr2=\"val2\"><child/></root>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    XMLNode* clone = root->ShallowClone(&doc2);
    ASSERT_NE(nullptr, clone);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(nullptr, cloneElem);
    EXPECT_STREQ("root", cloneElem->Name());
    EXPECT_STREQ("val1", cloneElem->Attribute("attr1"));
    EXPECT_STREQ("val2", cloneElem->Attribute("attr2"));
    // Shallow clone should not copy children
    EXPECT_EQ(nullptr, cloneElem->FirstChild());
}

// --- ShallowEqual ---

TEST_F(XMLElementTest_80, ShallowEqual_SameElement_80) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* root2 = doc2.RootElement();

    EXPECT_TRUE(root->ShallowEqual(root2));
}

TEST_F(XMLElementTest_80, ShallowEqual_DifferentName_80) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* other = doc2.RootElement();

    EXPECT_FALSE(root->ShallowEqual(other));
}

TEST_F(XMLElementTest_80, ShallowEqual_DifferentAttributes_80) {
    doc.Parse("<root attr=\"val1\"/>");
    XMLElement* root = doc.RootElement();

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val2\"/>");
    XMLElement* other = doc2.RootElement();

    EXPECT_FALSE(root->ShallowEqual(other));
}

// --- Multiple attributes ---

TEST_F(XMLElementTest_80, MultipleAttributes_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("a", 1);
    elem->SetAttribute("b", 2);
    elem->SetAttribute("c", 3);

    EXPECT_EQ(1, elem->IntAttribute("a", 0));
    EXPECT_EQ(2, elem->IntAttribute("b", 0));
    EXPECT_EQ(3, elem->IntAttribute("c", 0));
}

TEST_F(XMLElementTest_80, OverwriteAttribute_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "first");
    elem->SetAttribute("key", "second");
    EXPECT_STREQ("second", elem->Attribute("key"));
}

// --- Parsing from XML string ---

TEST_F(XMLElementTest_80, ParseComplexDocument_80) {
    const char* xml = "<root><a x=\"1\">text1</a><b y=\"2\">text2</b></root>";
    doc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());

    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Name());

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);
    EXPECT_STREQ("1", a->Attribute("x"));
    EXPECT_STREQ("text1", a->GetText());

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(nullptr, b);
    EXPECT_STREQ("2", b->Attribute("y"));
    EXPECT_STREQ("text2", b->GetText());
}

// --- SetText overwrites existing text ---

TEST_F(XMLElementTest_80, SetText_OverwritesExistingText_80) {
    doc.Parse("<root>old</root>");
    XMLElement* root = doc.RootElement();
    root->SetText("new");
    EXPECT_STREQ("new", root->GetText());
}

// --- ClosingType ---

TEST_F(XMLElementTest_80, ClosingType_OpenElement_80) {
    doc.Parse("<root></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    // OPEN is typically 0
    // Just verify it doesn't crash and returns a valid value
    auto ct = root->ClosingType();
    (void)ct; // Just ensure accessible
}

// --- Accept with XMLPrinter ---

TEST_F(XMLElementTest_80, Accept_XMLPrinter_80) {
    doc.Parse("<root attr=\"val\"><child>text</child></root>");
    XMLPrinter printer;
    doc.RootElement()->Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(nullptr, result);
    // The output should contain the element
    EXPECT_NE(nullptr, strstr(result, "root"));
    EXPECT_NE(nullptr, strstr(result, "child"));
    EXPECT_NE(nullptr, strstr(result, "text"));
}

// --- Negative values ---

TEST_F(XMLElementTest_80, SetAttribute_NegativeInt_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("neg", -100);
    EXPECT_EQ(-100, elem->IntAttribute("neg", 0));
}

TEST_F(XMLElementTest_80, SetAttribute_NegativeInt64_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("neg", (int64_t)-9223372036854775807LL);
    EXPECT_EQ(-9223372036854775807LL, elem->Int64Attribute("neg", 0));
}

// --- Empty string attribute ---

TEST_F(XMLElementTest_80, SetAttribute_EmptyString_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("empty", "");
    EXPECT_STREQ("", elem->Attribute("empty"));
}

// --- DeleteAttribute middle of list ---

TEST_F(XMLElementTest_80, DeleteAttribute_Middle_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    elem->SetAttribute("c", "3");
    elem->DeleteAttribute("b");
    EXPECT_STREQ("1", elem->Attribute("a"));
    EXPECT_EQ(nullptr, elem->Attribute("b"));
    EXPECT_STREQ("3", elem->Attribute("c"));
}

// --- SetText with special characters ---

TEST_F(XMLElementTest_80, SetText_SpecialChars_80) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetText("Hello <World> & \"Friends\"");
    // GetText should return the unescaped text
    const char* text = root->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Hello <World> & \"Friends\"", text);
}

// --- QueryAttribute overload for const char** ---

TEST_F(XMLElementTest_80, QueryAttribute_ConstCharPtr_80) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("s", "value");
    const char* val = nullptr;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("s", &val));
    EXPECT_STREQ("value", val);
}
