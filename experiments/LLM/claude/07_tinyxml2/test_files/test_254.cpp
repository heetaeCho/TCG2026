#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_254 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElementWithText(const char* tagName, const char* text) {
        XMLElement* elem = doc.NewElement(tagName);
        doc.InsertEndChild(elem);
        elem->SetText(text);
        return elem;
    }
};

// ==================== Unsigned64Text Tests ====================

TEST_F(XMLElementTest_254, Unsigned64Text_ValidValue_254) {
    XMLElement* elem = CreateElementWithText("val", "12345678901234");
    uint64_t result = elem->Unsigned64Text(0);
    EXPECT_EQ(result, 12345678901234ULL);
}

TEST_F(XMLElementTest_254, Unsigned64Text_Zero_254) {
    XMLElement* elem = CreateElementWithText("val", "0");
    uint64_t result = elem->Unsigned64Text(999);
    EXPECT_EQ(result, 0ULL);
}

TEST_F(XMLElementTest_254, Unsigned64Text_MaxValue_254) {
    XMLElement* elem = CreateElementWithText("val", "18446744073709551615");
    uint64_t result = elem->Unsigned64Text(0);
    EXPECT_EQ(result, UINT64_MAX);
}

TEST_F(XMLElementTest_254, Unsigned64Text_NoText_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    uint64_t result = elem->Unsigned64Text(42);
    EXPECT_EQ(result, 42ULL);
}

TEST_F(XMLElementTest_254, Unsigned64Text_InvalidText_ReturnsDefault_254) {
    XMLElement* elem = CreateElementWithText("val", "notanumber");
    uint64_t result = elem->Unsigned64Text(77);
    EXPECT_EQ(result, 77ULL);
}

TEST_F(XMLElementTest_254, Unsigned64Text_DefaultZero_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    uint64_t result = elem->Unsigned64Text(0);
    EXPECT_EQ(result, 0ULL);
}

TEST_F(XMLElementTest_254, Unsigned64Text_LargeDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    uint64_t result = elem->Unsigned64Text(UINT64_MAX);
    EXPECT_EQ(result, UINT64_MAX);
}

TEST_F(XMLElementTest_254, Unsigned64Text_SetTextUint64_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText((uint64_t)9999999999999ULL);
    uint64_t result = elem->Unsigned64Text(0);
    EXPECT_EQ(result, 9999999999999ULL);
}

// ==================== QueryUnsigned64Text Tests ====================

TEST_F(XMLElementTest_254, QueryUnsigned64Text_ValidValue_254) {
    XMLElement* elem = CreateElementWithText("val", "555");
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 555ULL);
}

TEST_F(XMLElementTest_254, QueryUnsigned64Text_NoText_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    uint64_t val = 123;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(val, 123ULL); // should remain unchanged
}

TEST_F(XMLElementTest_254, QueryUnsigned64Text_InvalidText_254) {
    XMLElement* elem = CreateElementWithText("val", "abc");
    uint64_t val = 456;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== IntText Tests ====================

TEST_F(XMLElementTest_254, IntText_ValidPositive_254) {
    XMLElement* elem = CreateElementWithText("val", "42");
    int result = elem->IntText(0);
    EXPECT_EQ(result, 42);
}

TEST_F(XMLElementTest_254, IntText_ValidNegative_254) {
    XMLElement* elem = CreateElementWithText("val", "-100");
    int result = elem->IntText(0);
    EXPECT_EQ(result, -100);
}

TEST_F(XMLElementTest_254, IntText_NoText_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    int result = elem->IntText(99);
    EXPECT_EQ(result, 99);
}

TEST_F(XMLElementTest_254, IntText_InvalidText_ReturnsDefault_254) {
    XMLElement* elem = CreateElementWithText("val", "xyz");
    int result = elem->IntText(55);
    EXPECT_EQ(result, 55);
}

// ==================== UnsignedText Tests ====================

TEST_F(XMLElementTest_254, UnsignedText_ValidValue_254) {
    XMLElement* elem = CreateElementWithText("val", "300");
    unsigned int result = elem->UnsignedText(0);
    EXPECT_EQ(result, 300u);
}

TEST_F(XMLElementTest_254, UnsignedText_NoText_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    unsigned int result = elem->UnsignedText(77u);
    EXPECT_EQ(result, 77u);
}

// ==================== Int64Text Tests ====================

TEST_F(XMLElementTest_254, Int64Text_ValidValue_254) {
    XMLElement* elem = CreateElementWithText("val", "9223372036854775807");
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, INT64_MAX);
}

TEST_F(XMLElementTest_254, Int64Text_ValidNegative_254) {
    XMLElement* elem = CreateElementWithText("val", "-9223372036854775808");
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, INT64_MIN);
}

TEST_F(XMLElementTest_254, Int64Text_NoText_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    int64_t result = elem->Int64Text(12345LL);
    EXPECT_EQ(result, 12345LL);
}

// ==================== BoolText Tests ====================

TEST_F(XMLElementTest_254, BoolText_True_254) {
    XMLElement* elem = CreateElementWithText("val", "true");
    bool result = elem->BoolText(false);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_254, BoolText_False_254) {
    XMLElement* elem = CreateElementWithText("val", "false");
    bool result = elem->BoolText(true);
    EXPECT_FALSE(result);
}

TEST_F(XMLElementTest_254, BoolText_One_254) {
    XMLElement* elem = CreateElementWithText("val", "1");
    bool result = elem->BoolText(false);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_254, BoolText_Zero_254) {
    XMLElement* elem = CreateElementWithText("val", "0");
    bool result = elem->BoolText(true);
    EXPECT_FALSE(result);
}

TEST_F(XMLElementTest_254, BoolText_NoText_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    bool result = elem->BoolText(true);
    EXPECT_TRUE(result);
}

// ==================== DoubleText Tests ====================

TEST_F(XMLElementTest_254, DoubleText_ValidValue_254) {
    XMLElement* elem = CreateElementWithText("val", "3.14159");
    double result = elem->DoubleText(0.0);
    EXPECT_DOUBLE_EQ(result, 3.14159);
}

TEST_F(XMLElementTest_254, DoubleText_NoText_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    double result = elem->DoubleText(2.71828);
    EXPECT_DOUBLE_EQ(result, 2.71828);
}

// ==================== FloatText Tests ====================

TEST_F(XMLElementTest_254, FloatText_ValidValue_254) {
    XMLElement* elem = CreateElementWithText("val", "1.5");
    float result = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST_F(XMLElementTest_254, FloatText_NoText_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    float result = elem->FloatText(9.9f);
    EXPECT_FLOAT_EQ(result, 9.9f);
}

// ==================== GetText / SetText Tests ====================

TEST_F(XMLElementTest_254, GetText_SetTextString_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText("Hello World");
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

TEST_F(XMLElementTest_254, GetText_NoText_ReturnsNull_254) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_254, SetText_Int_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_254, SetText_UnsignedInt_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText((unsigned int)100);
    EXPECT_STREQ(elem->GetText(), "100");
}

TEST_F(XMLElementTest_254, SetText_Int64_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText((int64_t)-9876543210LL);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, -9876543210LL);
}

TEST_F(XMLElementTest_254, SetText_Bool_True_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_254, SetText_Bool_False_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(false);
    EXPECT_STREQ(elem->GetText(), "false");
}

TEST_F(XMLElementTest_254, SetText_Double_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(2.5);
    double result = elem->DoubleText(0.0);
    EXPECT_DOUBLE_EQ(result, 2.5);
}

TEST_F(XMLElementTest_254, SetText_Float_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText(1.25f);
    float result = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(result, 1.25f);
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_254, SetAndGetAttribute_String_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("name", "value");
    EXPECT_STREQ(elem->Attribute("name"), "value");
}

TEST_F(XMLElementTest_254, Attribute_NotFound_ReturnsNull_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_254, IntAttribute_ValidValue_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(elem->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_254, IntAttribute_NotFound_ReturnsDefault_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->IntAttribute("missing", 99), 99);
}

TEST_F(XMLElementTest_254, UnsignedAttribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", (unsigned)500);
    EXPECT_EQ(elem->UnsignedAttribute("num", 0), 500u);
}

TEST_F(XMLElementTest_254, Int64Attribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", (int64_t)1234567890123LL);
    EXPECT_EQ(elem->Int64Attribute("num", 0), 1234567890123LL);
}

TEST_F(XMLElementTest_254, Unsigned64Attribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("num", (uint64_t)9876543210ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("num", 0), 9876543210ULL);
}

TEST_F(XMLElementTest_254, BoolAttribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_254, DoubleAttribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("val", 3.14);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("val", 0.0), 3.14);
}

TEST_F(XMLElementTest_254, FloatAttribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("val", 2.5f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 2.5f);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_254, DeleteAttribute_Existing_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("attr", "value");
    EXPECT_STREQ(elem->Attribute("attr"), "value");
    elem->DeleteAttribute("attr");
    EXPECT_EQ(elem->Attribute("attr"), nullptr);
}

TEST_F(XMLElementTest_254, DeleteAttribute_NonExisting_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_254, FindAttribute_Exists_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "val");
    const XMLAttribute* attr = elem->FindAttribute("key");
    EXPECT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_254, FindAttribute_NotExists_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    const XMLAttribute* attr = elem->FindAttribute("nokey");
    EXPECT_EQ(attr, nullptr);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_254, Name_254) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertEndChild(elem);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_254, SetName_254) {
    XMLElement* elem = doc.NewElement("old");
    doc.InsertEndChild(elem);
    elem->SetName("new");
    EXPECT_STREQ(elem->Name(), "new");
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_254, InsertNewChildElement_254) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = parent->InsertNewChildElement("child");
    EXPECT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(parent->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_254, InsertNewComment_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    XMLComment* comment = elem->InsertNewComment("test comment");
    EXPECT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_254, InsertNewText_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    XMLText* text = elem->InsertNewText("some text");
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

TEST_F(XMLElementTest_254, InsertNewDeclaration_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    XMLDeclaration* decl = elem->InsertNewDeclaration("test");
    EXPECT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_254, InsertNewUnknown_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    XMLUnknown* unk = elem->InsertNewUnknown("test");
    EXPECT_NE(unk, nullptr);
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_254, QueryIntAttribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("val", 10);
    int v = 0;
    XMLError err = elem->QueryIntAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, 10);
}

TEST_F(XMLElementTest_254, QueryIntAttribute_NotFound_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    int v = 0;
    XMLError err = elem->QueryIntAttribute("missing", &v);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_254, QueryStringAttribute_Valid_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("str", "hello");
    const char* v = nullptr;
    XMLError err = elem->QueryStringAttribute("str", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(v, "hello");
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_254, FirstAttribute_NoAttributes_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

TEST_F(XMLElementTest_254, FirstAttribute_HasAttributes_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("a", "1");
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_NE(attr, nullptr);
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_254, ToElement_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_254, ShallowClone_254) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "value");
    XMLNode* clone = elem->ShallowClone(&doc);
    EXPECT_NE(clone, nullptr);
    XMLElement* clonedElem = clone->ToElement();
    EXPECT_NE(clonedElem, nullptr);
    EXPECT_STREQ(clonedElem->Name(), "original");
    EXPECT_STREQ(clonedElem->Attribute("key"), "value");
    doc.DeleteNode(clone);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_254, ShallowEqual_SameElements_254) {
    XMLElement* elem1 = doc.NewElement("test");
    doc.InsertEndChild(elem1);
    elem1->SetAttribute("a", "1");

    XMLElement* elem2 = doc.NewElement("test");
    elem2->SetAttribute("a", "1");

    EXPECT_TRUE(elem1->ShallowEqual(elem2));
    doc.DeleteNode(elem2);
}

TEST_F(XMLElementTest_254, ShallowEqual_DifferentNames_254) {
    XMLElement* elem1 = doc.NewElement("test1");
    doc.InsertEndChild(elem1);

    XMLElement* elem2 = doc.NewElement("test2");

    EXPECT_FALSE(elem1->ShallowEqual(elem2));
    doc.DeleteNode(elem2);
}

// ==================== Parsing from XML string ====================

TEST_F(XMLElementTest_254, ParseAndReadUnsigned64Text_254) {
    const char* xml = "<root><val>18446744073709551615</val></root>";
    doc.Parse(xml);
    XMLElement* val = doc.FirstChildElement("root")->FirstChildElement("val");
    EXPECT_NE(val, nullptr);
    uint64_t result = val->Unsigned64Text(0);
    EXPECT_EQ(result, UINT64_MAX);
}

TEST_F(XMLElementTest_254, ParseAndReadMultipleTextTypes_254) {
    const char* xml = "<root>"
                      "<i>-10</i>"
                      "<u>20</u>"
                      "<i64>-999999999999</i64>"
                      "<u64>888888888888</u64>"
                      "<b>true</b>"
                      "<d>1.23456789</d>"
                      "<f>3.14</f>"
                      "</root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    EXPECT_NE(root, nullptr);

    EXPECT_EQ(root->FirstChildElement("i")->IntText(0), -10);
    EXPECT_EQ(root->FirstChildElement("u")->UnsignedText(0), 20u);
    EXPECT_EQ(root->FirstChildElement("i64")->Int64Text(0), -999999999999LL);
    EXPECT_EQ(root->FirstChildElement("u64")->Unsigned64Text(0), 888888888888ULL);
    EXPECT_TRUE(root->FirstChildElement("b")->BoolText(false));
    EXPECT_DOUBLE_EQ(root->FirstChildElement("d")->DoubleText(0.0), 1.23456789);
    EXPECT_NEAR(root->FirstChildElement("f")->FloatText(0.0f), 3.14f, 0.001f);
}

// ==================== Multiple attributes ====================

TEST_F(XMLElementTest_254, MultipleAttributes_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("a", 1);
    elem->SetAttribute("b", 2);
    elem->SetAttribute("c", 3);
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_EQ(elem->IntAttribute("b", 0), 2);
    EXPECT_EQ(elem->IntAttribute("c", 0), 3);
}

TEST_F(XMLElementTest_254, OverwriteAttribute_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("key", "old");
    elem->SetAttribute("key", "new");
    EXPECT_STREQ(elem->Attribute("key"), "new");
}

// ==================== Attribute with value check ====================

TEST_F(XMLElementTest_254, Attribute_WithMatchingValue_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("attr", "expected");
    EXPECT_STREQ(elem->Attribute("attr", "expected"), "expected");
}

TEST_F(XMLElementTest_254, Attribute_WithNonMatchingValue_254) {
    XMLElement* elem = doc.NewElement("elem");
    doc.InsertEndChild(elem);
    elem->SetAttribute("attr", "actual");
    EXPECT_EQ(elem->Attribute("attr", "wrong"), nullptr);
}

// ==================== SetText overwrite ====================

TEST_F(XMLElementTest_254, SetText_OverwriteExisting_254) {
    XMLElement* elem = doc.NewElement("val");
    doc.InsertEndChild(elem);
    elem->SetText("first");
    EXPECT_STREQ(elem->GetText(), "first");
    elem->SetText("second");
    EXPECT_STREQ(elem->GetText(), "second");
}
