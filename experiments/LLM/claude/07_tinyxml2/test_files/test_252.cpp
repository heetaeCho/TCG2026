#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_252 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElementWithText(const char* tagName, const char* text) {
        XMLElement* elem = doc.NewElement(tagName);
        doc.InsertEndChild(elem);
        elem->SetText(text);
        return elem;
    }
};

// ==================== UnsignedText Tests ====================

TEST_F(XMLElementTest_252, UnsignedText_ValidUnsignedValue_252) {
    XMLElement* elem = CreateElementWithText("val", "42");
    EXPECT_EQ(42u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_252, UnsignedText_ReturnsDefaultWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(99u, elem->UnsignedText(99));
}

TEST_F(XMLElementTest_252, UnsignedText_ReturnsDefaultWhenInvalidText_252) {
    XMLElement* elem = CreateElementWithText("val", "notanumber");
    EXPECT_EQ(55u, elem->UnsignedText(55));
}

TEST_F(XMLElementTest_252, UnsignedText_ZeroValue_252) {
    XMLElement* elem = CreateElementWithText("val", "0");
    EXPECT_EQ(0u, elem->UnsignedText(100));
}

TEST_F(XMLElementTest_252, UnsignedText_LargeValue_252) {
    XMLElement* elem = CreateElementWithText("val", "4294967295");
    EXPECT_EQ(4294967295u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_252, UnsignedText_DefaultZero_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(0u, elem->UnsignedText(0));
}

// ==================== IntText Tests ====================

TEST_F(XMLElementTest_252, IntText_ValidPositiveInt_252) {
    XMLElement* elem = CreateElementWithText("val", "123");
    EXPECT_EQ(123, elem->IntText(0));
}

TEST_F(XMLElementTest_252, IntText_ValidNegativeInt_252) {
    XMLElement* elem = CreateElementWithText("val", "-456");
    EXPECT_EQ(-456, elem->IntText(0));
}

TEST_F(XMLElementTest_252, IntText_ReturnsDefaultWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(77, elem->IntText(77));
}

TEST_F(XMLElementTest_252, IntText_ReturnsDefaultWhenInvalidText_252) {
    XMLElement* elem = CreateElementWithText("val", "abc");
    EXPECT_EQ(33, elem->IntText(33));
}

// ==================== Int64Text Tests ====================

TEST_F(XMLElementTest_252, Int64Text_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "9223372036854775807");
    EXPECT_EQ(INT64_C(9223372036854775807), elem->Int64Text(0));
}

TEST_F(XMLElementTest_252, Int64Text_ReturnsDefaultWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(INT64_C(-1), elem->Int64Text(-1));
}

// ==================== Unsigned64Text Tests ====================

TEST_F(XMLElementTest_252, Unsigned64Text_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "18446744073709551615");
    EXPECT_EQ(UINT64_C(18446744073709551615), elem->Unsigned64Text(0));
}

TEST_F(XMLElementTest_252, Unsigned64Text_ReturnsDefaultWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(UINT64_C(42), elem->Unsigned64Text(42));
}

// ==================== BoolText Tests ====================

TEST_F(XMLElementTest_252, BoolText_TrueValue_252) {
    XMLElement* elem = CreateElementWithText("val", "true");
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_252, BoolText_FalseValue_252) {
    XMLElement* elem = CreateElementWithText("val", "false");
    EXPECT_FALSE(elem->BoolText(true));
}

TEST_F(XMLElementTest_252, BoolText_ReturnsDefaultWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_252, BoolText_ReturnsDefaultWhenInvalidText_252) {
    XMLElement* elem = CreateElementWithText("val", "maybe");
    EXPECT_TRUE(elem->BoolText(true));
}

// ==================== DoubleText Tests ====================

TEST_F(XMLElementTest_252, DoubleText_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "3.14159");
    EXPECT_DOUBLE_EQ(3.14159, elem->DoubleText(0.0));
}

TEST_F(XMLElementTest_252, DoubleText_ReturnsDefaultWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_DOUBLE_EQ(2.718, elem->DoubleText(2.718));
}

// ==================== FloatText Tests ====================

TEST_F(XMLElementTest_252, FloatText_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "1.5");
    EXPECT_FLOAT_EQ(1.5f, elem->FloatText(0.0f));
}

TEST_F(XMLElementTest_252, FloatText_ReturnsDefaultWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_FLOAT_EQ(9.9f, elem->FloatText(9.9f));
}

// ==================== GetText Tests ====================

TEST_F(XMLElementTest_252, GetText_ReturnsTextContent_252) {
    XMLElement* elem = CreateElementWithText("val", "hello");
    EXPECT_STREQ("hello", elem->GetText());
}

TEST_F(XMLElementTest_252, GetText_ReturnsNullWhenNoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->GetText());
}

// ==================== SetText Tests ====================

TEST_F(XMLElementTest_252, SetText_String_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText("world");
    EXPECT_STREQ("world", elem->GetText());
}

TEST_F(XMLElementTest_252, SetText_Int_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(42);
    EXPECT_EQ(42, elem->IntText(0));
}

TEST_F(XMLElementTest_252, SetText_UnsignedInt_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(100u);
    EXPECT_EQ(100u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_252, SetText_Int64_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(INT64_C(123456789012345));
    EXPECT_EQ(INT64_C(123456789012345), elem->Int64Text(0));
}

TEST_F(XMLElementTest_252, SetText_Uint64_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(UINT64_C(123456789012345));
    EXPECT_EQ(UINT64_C(123456789012345), elem->Unsigned64Text(0));
}

TEST_F(XMLElementTest_252, SetText_Bool_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(true);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_252, SetText_Double_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(3.14);
    EXPECT_DOUBLE_EQ(3.14, elem->DoubleText(0.0));
}

TEST_F(XMLElementTest_252, SetText_Float_252) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(2.5f);
    EXPECT_FLOAT_EQ(2.5f, elem->FloatText(0.0f));
}

// ==================== QueryText Tests ====================

TEST_F(XMLElementTest_252, QueryIntText_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "10");
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntText(&val));
    EXPECT_EQ(10, val);
}

TEST_F(XMLElementTest_252, QueryIntText_NoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    int val = -1;
    EXPECT_NE(XML_SUCCESS, elem->QueryIntText(&val));
}

TEST_F(XMLElementTest_252, QueryUnsignedText_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "20");
    unsigned val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsignedText(&val));
    EXPECT_EQ(20u, val);
}

TEST_F(XMLElementTest_252, QueryUnsignedText_NoText_252) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    unsigned val = 99;
    EXPECT_NE(XML_SUCCESS, elem->QueryUnsignedText(&val));
}

TEST_F(XMLElementTest_252, QueryBoolText_ValidTrue_252) {
    XMLElement* elem = CreateElementWithText("val", "true");
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolText(&val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_252, QueryBoolText_ValidFalse_252) {
    XMLElement* elem = CreateElementWithText("val", "false");
    bool val = true;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolText(&val));
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_252, QueryDoubleText_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "1.23");
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryDoubleText(&val));
    EXPECT_DOUBLE_EQ(1.23, val);
}

TEST_F(XMLElementTest_252, QueryFloatText_ValidValue_252) {
    XMLElement* elem = CreateElementWithText("val", "4.56");
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryFloatText(&val));
    EXPECT_FLOAT_EQ(4.56f, val);
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_252, SetAndGetAttribute_String_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "value");
    EXPECT_STREQ("value", elem->Attribute("key"));
}

TEST_F(XMLElementTest_252, Attribute_NonExistent_ReturnsNull_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->Attribute("nonexistent"));
}

TEST_F(XMLElementTest_252, IntAttribute_ValidValue_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(42, elem->IntAttribute("num", 0));
}

TEST_F(XMLElementTest_252, IntAttribute_DefaultOnMissing_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(99, elem->IntAttribute("missing", 99));
}

TEST_F(XMLElementTest_252, UnsignedAttribute_ValidValue_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", 100u);
    EXPECT_EQ(100u, elem->UnsignedAttribute("num", 0));
}

TEST_F(XMLElementTest_252, BoolAttribute_True_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_252, DoubleAttribute_ValidValue_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("dbl", 3.14);
    EXPECT_DOUBLE_EQ(3.14, elem->DoubleAttribute("dbl", 0.0));
}

TEST_F(XMLElementTest_252, FloatAttribute_ValidValue_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("flt", 1.5f);
    EXPECT_FLOAT_EQ(1.5f, elem->FloatAttribute("flt", 0.0f));
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_252, DeleteAttribute_ExistingAttribute_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "value");
    EXPECT_NE(nullptr, elem->Attribute("key"));
    elem->DeleteAttribute("key");
    EXPECT_EQ(nullptr, elem->Attribute("key"));
}

TEST_F(XMLElementTest_252, DeleteAttribute_NonExistent_NoError_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_252, FindAttribute_Found_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("name", "val");
    const XMLAttribute* attr = elem->FindAttribute("name");
    EXPECT_NE(nullptr, attr);
}

TEST_F(XMLElementTest_252, FindAttribute_NotFound_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    const XMLAttribute* attr = elem->FindAttribute("nonexistent");
    EXPECT_EQ(nullptr, attr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_252, FirstAttribute_Empty_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->FirstAttribute());
}

TEST_F(XMLElementTest_252, FirstAttribute_NonEmpty_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("a", "1");
    EXPECT_NE(nullptr, elem->FirstAttribute());
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_252, Name_ReturnsCorrectName_252) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertEndChild(elem);
    EXPECT_STREQ("myElement", elem->Name());
}

TEST_F(XMLElementTest_252, SetName_ChangesName_252) {
    XMLElement* elem = doc.NewElement("old");
    doc.InsertEndChild(elem);
    elem->SetName("new");
    EXPECT_STREQ("new", elem->Name());
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_252, InsertNewChildElement_CreatesChild_252) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = parent->InsertNewChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
}

TEST_F(XMLElementTest_252, InsertNewComment_CreatesComment_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLComment* comment = elem->InsertNewComment("a comment");
    EXPECT_NE(nullptr, comment);
}

TEST_F(XMLElementTest_252, InsertNewText_CreatesText_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLText* text = elem->InsertNewText("some text");
    EXPECT_NE(nullptr, text);
}

TEST_F(XMLElementTest_252, InsertNewDeclaration_CreatesDeclaration_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLDeclaration* decl = elem->InsertNewDeclaration("xml version='1.0'");
    EXPECT_NE(nullptr, decl);
}

TEST_F(XMLElementTest_252, InsertNewUnknown_CreatesUnknown_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    EXPECT_NE(nullptr, unknown);
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_252, ToElement_ReturnsThis_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem, elem->ToElement());
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_252, ShallowClone_ClonesElement_252) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    elem->SetAttribute("attr", "val");

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(nullptr, clone);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(nullptr, cloneElem);
    EXPECT_STREQ("original", cloneElem->Name());
    EXPECT_STREQ("val", cloneElem->Attribute("attr"));
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_252, ShallowEqual_SameElement_252) {
    XMLElement* elem1 = doc.NewElement("test");
    doc.InsertEndChild(elem1);
    elem1->SetAttribute("a", "1");

    XMLElement* elem2 = doc.NewElement("test");
    elem2->SetAttribute("a", "1");

    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_252, ShallowEqual_DifferentName_252) {
    XMLElement* elem1 = doc.NewElement("test1");
    doc.InsertEndChild(elem1);

    XMLElement* elem2 = doc.NewElement("test2");

    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_252, QueryIntAttribute_Success_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("val", 10);
    int v = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntAttribute("val", &v));
    EXPECT_EQ(10, v);
}

TEST_F(XMLElementTest_252, QueryIntAttribute_NoAttribute_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    int v = -1;
    EXPECT_NE(XML_SUCCESS, elem->QueryIntAttribute("missing", &v));
}

TEST_F(XMLElementTest_252, QueryStringAttribute_Success_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("str", "hello");
    const char* v = nullptr;
    EXPECT_EQ(XML_SUCCESS, elem->QueryStringAttribute("str", &v));
    EXPECT_STREQ("hello", v);
}

// ==================== Parsing via XMLDocument Tests ====================

TEST_F(XMLElementTest_252, ParseDocument_UnsignedText_252) {
    const char* xml = "<root><val>12345</val></root>";
    doc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());
    XMLElement* val = doc.FirstChildElement("root")->FirstChildElement("val");
    ASSERT_NE(nullptr, val);
    EXPECT_EQ(12345u, val->UnsignedText(0));
}

TEST_F(XMLElementTest_252, ParseDocument_MultipleAttributes_252) {
    const char* xml = "<root a=\"1\" b=\"2\" c=\"3\"/>";
    doc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(1, root->IntAttribute("a", 0));
    EXPECT_EQ(2, root->IntAttribute("b", 0));
    EXPECT_EQ(3, root->IntAttribute("c", 0));
}

TEST_F(XMLElementTest_252, UnsignedText_OverwriteText_252) {
    XMLElement* elem = CreateElementWithText("val", "10");
    EXPECT_EQ(10u, elem->UnsignedText(0));
    elem->SetText(20u);
    EXPECT_EQ(20u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_252, SetText_OverwritesExistingText_252) {
    XMLElement* elem = CreateElementWithText("val", "first");
    EXPECT_STREQ("first", elem->GetText());
    elem->SetText("second");
    EXPECT_STREQ("second", elem->GetText());
}

// ==================== Bool values as 1/0 ====================

TEST_F(XMLElementTest_252, BoolText_NumericOne_252) {
    XMLElement* elem = CreateElementWithText("val", "1");
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_252, BoolText_NumericZero_252) {
    XMLElement* elem = CreateElementWithText("val", "0");
    EXPECT_FALSE(elem->BoolText(true));
}

// ==================== Attribute with value match ====================

TEST_F(XMLElementTest_252, Attribute_WithMatchingValue_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "expected");
    EXPECT_STREQ("expected", elem->Attribute("key", "expected"));
}

TEST_F(XMLElementTest_252, Attribute_WithNonMatchingValue_252) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "actual");
    EXPECT_EQ(nullptr, elem->Attribute("key", "different"));
}
