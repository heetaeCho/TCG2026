#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_79 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ==================== SetName / Name Tests ====================

TEST_F(XMLElementTest_79, SetName_BasicName_79) {
    XMLElement* elem = doc.NewElement("initial");
    elem->SetName("newname");
    EXPECT_STREQ("newname", elem->Name());
}

TEST_F(XMLElementTest_79, SetName_EmptyString_79) {
    XMLElement* elem = doc.NewElement("initial");
    elem->SetName("");
    EXPECT_STREQ("", elem->Name());
}

TEST_F(XMLElementTest_79, Name_ReturnsInitialName_79) {
    XMLElement* elem = doc.NewElement("myElement");
    EXPECT_STREQ("myElement", elem->Name());
}

TEST_F(XMLElementTest_79, SetName_WithStaticMemTrue_79) {
    XMLElement* elem = doc.NewElement("initial");
    elem->SetName("staticName", true);
    EXPECT_STREQ("staticName", elem->Name());
}

TEST_F(XMLElementTest_79, SetName_WithStaticMemFalse_79) {
    XMLElement* elem = doc.NewElement("initial");
    elem->SetName("dynamicName", false);
    EXPECT_STREQ("dynamicName", elem->Name());
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_79, SetAttribute_String_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "value");
    EXPECT_STREQ("value", elem->Attribute("key"));
}

TEST_F(XMLElementTest_79, SetAttribute_Int_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", 42);
    EXPECT_EQ(42, elem->IntAttribute("num", 0));
}

TEST_F(XMLElementTest_79, SetAttribute_Unsigned_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", (unsigned)100);
    EXPECT_EQ(100u, elem->UnsignedAttribute("num", 0));
}

TEST_F(XMLElementTest_79, SetAttribute_Int64_79) {
    XMLElement* elem = doc.NewElement("test");
    int64_t val = 9223372036854775807LL;
    elem->SetAttribute("num", val);
    EXPECT_EQ(val, elem->Int64Attribute("num", 0));
}

TEST_F(XMLElementTest_79, SetAttribute_Uint64_79) {
    XMLElement* elem = doc.NewElement("test");
    uint64_t val = 18446744073709551615ULL;
    elem->SetAttribute("num", val);
    EXPECT_EQ(val, elem->Unsigned64Attribute("num", 0));
}

TEST_F(XMLElementTest_79, SetAttribute_Bool_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_79, SetAttribute_Double_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", 3.14159);
    EXPECT_DOUBLE_EQ(3.14159, elem->DoubleAttribute("val", 0.0));
}

TEST_F(XMLElementTest_79, SetAttribute_Float_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", 2.5f);
    EXPECT_FLOAT_EQ(2.5f, elem->FloatAttribute("val", 0.0f));
}

TEST_F(XMLElementTest_79, Attribute_NonExistent_ReturnsNull_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->Attribute("nonexistent"));
}

TEST_F(XMLElementTest_79, Attribute_WithValueMatch_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "value");
    EXPECT_STREQ("value", elem->Attribute("key", "value"));
}

TEST_F(XMLElementTest_79, Attribute_WithValueMismatch_ReturnsNull_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "value");
    EXPECT_EQ(nullptr, elem->Attribute("key", "other"));
}

// ==================== Query Attribute Tests ====================

TEST_F(XMLElementTest_79, QueryIntAttribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", 42);
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntAttribute("num", &val));
    EXPECT_EQ(42, val);
}

TEST_F(XMLElementTest_79, QueryIntAttribute_NotFound_79) {
    XMLElement* elem = doc.NewElement("test");
    int val = 0;
    EXPECT_EQ(XML_NO_ATTRIBUTE, elem->QueryIntAttribute("missing", &val));
}

TEST_F(XMLElementTest_79, QueryUnsignedAttribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", (unsigned)100);
    unsigned val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsignedAttribute("num", &val));
    EXPECT_EQ(100u, val);
}

TEST_F(XMLElementTest_79, QueryInt64Attribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", (int64_t)123456789012345LL);
    int64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryInt64Attribute("num", &val));
    EXPECT_EQ(123456789012345LL, val);
}

TEST_F(XMLElementTest_79, QueryUnsigned64Attribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", (uint64_t)123456789012345ULL);
    uint64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsigned64Attribute("num", &val));
    EXPECT_EQ(123456789012345ULL, val);
}

TEST_F(XMLElementTest_79, QueryBoolAttribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("flag", true);
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolAttribute("flag", &val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_79, QueryDoubleAttribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", 1.23);
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryDoubleAttribute("val", &val));
    EXPECT_DOUBLE_EQ(1.23, val);
}

TEST_F(XMLElementTest_79, QueryFloatAttribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", 1.5f);
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryFloatAttribute("val", &val));
    EXPECT_FLOAT_EQ(1.5f, val);
}

TEST_F(XMLElementTest_79, QueryStringAttribute_Success_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "hello");
    const char* val = nullptr;
    EXPECT_EQ(XML_SUCCESS, elem->QueryStringAttribute("key", &val));
    EXPECT_STREQ("hello", val);
}

TEST_F(XMLElementTest_79, QueryStringAttribute_NotFound_79) {
    XMLElement* elem = doc.NewElement("test");
    const char* val = nullptr;
    EXPECT_EQ(XML_NO_ATTRIBUTE, elem->QueryStringAttribute("missing", &val));
}

// ==================== Default Attribute Value Tests ====================

TEST_F(XMLElementTest_79, IntAttribute_DefaultValue_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(99, elem->IntAttribute("missing", 99));
}

TEST_F(XMLElementTest_79, UnsignedAttribute_DefaultValue_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(77u, elem->UnsignedAttribute("missing", 77u));
}

TEST_F(XMLElementTest_79, Int64Attribute_DefaultValue_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(55LL, elem->Int64Attribute("missing", 55LL));
}

TEST_F(XMLElementTest_79, Unsigned64Attribute_DefaultValue_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(33ULL, elem->Unsigned64Attribute("missing", 33ULL));
}

TEST_F(XMLElementTest_79, BoolAttribute_DefaultValue_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
}

TEST_F(XMLElementTest_79, DoubleAttribute_DefaultValue_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_DOUBLE_EQ(1.11, elem->DoubleAttribute("missing", 1.11));
}

TEST_F(XMLElementTest_79, FloatAttribute_DefaultValue_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_FLOAT_EQ(2.22f, elem->FloatAttribute("missing", 2.22f));
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_79, FindAttribute_Found_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("attr1", "val1");
    const XMLAttribute* attr = elem->FindAttribute("attr1");
    EXPECT_NE(nullptr, attr);
    EXPECT_STREQ("attr1", attr->Name());
    EXPECT_STREQ("val1", attr->Value());
}

TEST_F(XMLElementTest_79, FindAttribute_NotFound_79) {
    XMLElement* elem = doc.NewElement("test");
    const XMLAttribute* attr = elem->FindAttribute("nonexistent");
    EXPECT_EQ(nullptr, attr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_79, FirstAttribute_NoAttributes_ReturnsNull_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->FirstAttribute());
}

TEST_F(XMLElementTest_79, FirstAttribute_WithAttributes_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_NE(nullptr, attr);
    EXPECT_STREQ("first", attr->Name());
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_79, DeleteAttribute_Existing_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("toDelete", "value");
    EXPECT_NE(nullptr, elem->Attribute("toDelete"));
    elem->DeleteAttribute("toDelete");
    EXPECT_EQ(nullptr, elem->Attribute("toDelete"));
}

TEST_F(XMLElementTest_79, DeleteAttribute_NonExistent_79) {
    XMLElement* elem = doc.NewElement("test");
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_EQ(nullptr, elem->Attribute("nonexistent"));
}

// ==================== Text Tests ====================

TEST_F(XMLElementTest_79, SetText_String_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText("Hello World");
    EXPECT_STREQ("Hello World", elem->GetText());
}

TEST_F(XMLElementTest_79, SetText_Int_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText(42);
    EXPECT_STREQ("42", elem->GetText());
}

TEST_F(XMLElementTest_79, SetText_Unsigned_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText((unsigned)100);
    EXPECT_STREQ("100", elem->GetText());
}

TEST_F(XMLElementTest_79, SetText_Int64_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText((int64_t)123456789012345LL);
    EXPECT_STREQ("123456789012345", elem->GetText());
}

TEST_F(XMLElementTest_79, SetText_Uint64_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText((uint64_t)123456789012345ULL);
    EXPECT_STREQ("123456789012345", elem->GetText());
}

TEST_F(XMLElementTest_79, SetText_BoolTrue_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText(true);
    EXPECT_STREQ("true", elem->GetText());
}

TEST_F(XMLElementTest_79, SetText_BoolFalse_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText(false);
    EXPECT_STREQ("false", elem->GetText());
}

TEST_F(XMLElementTest_79, SetText_Double_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText(3.14);
    const char* text = elem->GetText();
    EXPECT_NE(nullptr, text);
}

TEST_F(XMLElementTest_79, SetText_Float_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetText(2.5f);
    const char* text = elem->GetText();
    EXPECT_NE(nullptr, text);
}

TEST_F(XMLElementTest_79, GetText_NoText_ReturnsNull_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->GetText());
}

// ==================== QueryText Tests ====================

TEST_F(XMLElementTest_79, QueryIntText_Success_79) {
    const char* xml = "<root><num>42</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntText(&val));
    EXPECT_EQ(42, val);
}

TEST_F(XMLElementTest_79, QueryIntText_NoText_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    int val = 0;
    EXPECT_NE(XML_SUCCESS, elem->QueryIntText(&val));
}

TEST_F(XMLElementTest_79, QueryUnsignedText_Success_79) {
    const char* xml = "<root><num>100</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    unsigned val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsignedText(&val));
    EXPECT_EQ(100u, val);
}

TEST_F(XMLElementTest_79, QueryInt64Text_Success_79) {
    const char* xml = "<root><num>123456789012345</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    int64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryInt64Text(&val));
    EXPECT_EQ(123456789012345LL, val);
}

TEST_F(XMLElementTest_79, QueryUnsigned64Text_Success_79) {
    const char* xml = "<root><num>123456789012345</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    uint64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsigned64Text(&val));
    EXPECT_EQ(123456789012345ULL, val);
}

TEST_F(XMLElementTest_79, QueryBoolText_True_79) {
    const char* xml = "<root><flag>true</flag></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("flag");
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolText(&val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_79, QueryDoubleText_Success_79) {
    const char* xml = "<root><val>3.14</val></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("val");
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryDoubleText(&val));
    EXPECT_DOUBLE_EQ(3.14, val);
}

TEST_F(XMLElementTest_79, QueryFloatText_Success_79) {
    const char* xml = "<root><val>2.5</val></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("val");
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryFloatText(&val));
    EXPECT_FLOAT_EQ(2.5f, val);
}

// ==================== IntText/UnsignedText/etc. with defaults ====================

TEST_F(XMLElementTest_79, IntText_WithValue_79) {
    const char* xml = "<root><num>42</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    EXPECT_EQ(42, elem->IntText(0));
}

TEST_F(XMLElementTest_79, IntText_NoValue_DefaultReturned_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(99, elem->IntText(99));
}

TEST_F(XMLElementTest_79, UnsignedText_WithValue_79) {
    const char* xml = "<root><num>100</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    EXPECT_EQ(100u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_79, Int64Text_WithValue_79) {
    const char* xml = "<root><num>123456789012345</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    EXPECT_EQ(123456789012345LL, elem->Int64Text(0));
}

TEST_F(XMLElementTest_79, Unsigned64Text_WithValue_79) {
    const char* xml = "<root><num>123456789012345</num></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("num");
    EXPECT_EQ(123456789012345ULL, elem->Unsigned64Text(0));
}

TEST_F(XMLElementTest_79, BoolText_WithValue_79) {
    const char* xml = "<root><flag>true</flag></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("flag");
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_79, DoubleText_WithValue_79) {
    const char* xml = "<root><val>3.14</val></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("val");
    EXPECT_DOUBLE_EQ(3.14, elem->DoubleText(0.0));
}

TEST_F(XMLElementTest_79, FloatText_WithValue_79) {
    const char* xml = "<root><val>2.5</val></root>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("val");
    EXPECT_FLOAT_EQ(2.5f, elem->FloatText(0.0f));
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_79, InsertNewChildElement_79) {
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    XMLElement* child = elem->InsertNewChildElement("child");
    EXPECT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
    EXPECT_EQ(child, elem->FirstChildElement("child"));
}

TEST_F(XMLElementTest_79, InsertNewComment_79) {
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    XMLComment* comment = elem->InsertNewComment("This is a comment");
    EXPECT_NE(nullptr, comment);
}

TEST_F(XMLElementTest_79, InsertNewText_79) {
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    XMLText* text = elem->InsertNewText("Some text");
    EXPECT_NE(nullptr, text);
    EXPECT_STREQ("Some text", elem->GetText());
}

TEST_F(XMLElementTest_79, InsertNewDeclaration_79) {
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    EXPECT_NE(nullptr, decl);
}

TEST_F(XMLElementTest_79, InsertNewUnknown_79) {
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    XMLUnknown* unknown = elem->InsertNewUnknown("unknown stuff");
    EXPECT_NE(nullptr, unknown);
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_79, ToElement_ReturnsThis_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(elem, elem->ToElement());
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_79, ShallowClone_CopiesNameAndAttributes_79) {
    XMLElement* elem = doc.NewElement("original");
    elem->SetAttribute("attr1", "val1");
    elem->SetAttribute("attr2", 42);
    
    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(nullptr, clone);
    XMLElement* clonedElem = clone->ToElement();
    ASSERT_NE(nullptr, clonedElem);
    EXPECT_STREQ("original", clonedElem->Name());
    EXPECT_STREQ("val1", clonedElem->Attribute("attr1"));
    EXPECT_EQ(42, clonedElem->IntAttribute("attr2", 0));
}

TEST_F(XMLElementTest_79, ShallowClone_DoesNotCopyChildren_79) {
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    elem->InsertNewChildElement("child");
    
    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(nullptr, clone);
    EXPECT_TRUE(clone->NoChildren());
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_79, ShallowEqual_SameNameAndAttributes_79) {
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("key", "value");
    
    XMLDocument doc2;
    XMLElement* elem2 = doc2.NewElement("test");
    elem2->SetAttribute("key", "value");
    
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_79, ShallowEqual_DifferentName_79) {
    XMLElement* elem1 = doc.NewElement("test1");
    
    XMLDocument doc2;
    XMLElement* elem2 = doc2.NewElement("test2");
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_79, ShallowEqual_DifferentAttributes_79) {
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("key", "value1");
    
    XMLDocument doc2;
    XMLElement* elem2 = doc2.NewElement("test");
    elem2->SetAttribute("key", "value2");
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// ==================== DeepClone Tests ====================

TEST_F(XMLElementTest_79, DeepClone_CopiesChildElements_79) {
    const char* xml = "<root><child1>text1</child1><child2 attr=\"val\"/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    
    XMLDocument doc2;
    XMLNode* clone = root->DeepClone(&doc2);
    ASSERT_NE(nullptr, clone);
    doc2.InsertEndChild(clone);
    
    XMLElement* clonedRoot = clone->ToElement();
    ASSERT_NE(nullptr, clonedRoot);
    EXPECT_STREQ("root", clonedRoot->Name());
    
    XMLElement* child1 = clonedRoot->FirstChildElement("child1");
    ASSERT_NE(nullptr, child1);
    EXPECT_STREQ("text1", child1->GetText());
    
    XMLElement* child2 = clonedRoot->FirstChildElement("child2");
    ASSERT_NE(nullptr, child2);
    EXPECT_STREQ("val", child2->Attribute("attr"));
}

// ==================== Child Element Navigation Tests ====================

TEST_F(XMLElementTest_79, FirstChildElement_ByName_79) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(nullptr, b);
    EXPECT_STREQ("b", b->Name());
}

TEST_F(XMLElementTest_79, LastChildElement_ByName_79) {
    const char* xml = "<root><a/><b/><a/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(nullptr, lastA);
    EXPECT_STREQ("a", lastA->Name());
}

TEST_F(XMLElementTest_79, NextSiblingElement_79) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(nullptr, b);
    EXPECT_STREQ("b", b->Name());
}

TEST_F(XMLElementTest_79, PreviousSiblingElement_79) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    XMLElement* c = root->LastChildElement("c");
    XMLElement* b = c->PreviousSiblingElement();
    ASSERT_NE(nullptr, b);
    EXPECT_STREQ("b", b->Name());
}

// ==================== ChildElementCount Tests ====================

TEST_F(XMLElementTest_79, ChildElementCount_All_79) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    EXPECT_EQ(3, root->ChildElementCount());
}

TEST_F(XMLElementTest_79, ChildElementCount_ByName_79) {
    const char* xml = "<root><a/><b/><a/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    EXPECT_EQ(2, root->ChildElementCount("a"));
    EXPECT_EQ(1, root->ChildElementCount("b"));
    EXPECT_EQ(0, root->ChildElementCount("c"));
}

TEST_F(XMLElementTest_79, ChildElementCount_Empty_79) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(0, elem->ChildElementCount());
}

// ==================== DeleteChildren Tests ====================

TEST_F(XMLElementTest_79, DeleteChildren_79) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// ==================== InsertEndChild / InsertFirstChild Tests ====================

TEST_F(XMLElementTest_79, InsertEndChild_79) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    EXPECT_STREQ("child1", parent->FirstChildElement()->Name());
    EXPECT_STREQ("child2", parent->LastChildElement()->Name());
}

TEST_F(XMLElementTest_79, InsertFirstChild_79) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertFirstChild(child2);
    EXPECT_STREQ("child2", parent->FirstChildElement()->Name());
    EXPECT_STREQ("child1", parent->LastChildElement()->Name());
}

TEST_F(XMLElementTest_79, InsertAfterChild_79) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child3 = doc.NewElement("child3");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child3);
    parent->InsertAfterChild(child1, child2);
    
    XMLElement* first = parent->FirstChildElement();
    ASSERT_NE(nullptr, first);
    EXPECT_STREQ("child1", first->Name());
    XMLElement* second = first->NextSiblingElement();
    ASSERT_NE(nullptr, second);
    EXPECT_STREQ("child2", second->Name());
    XMLElement* third = second->NextSiblingElement();
    ASSERT_NE(nullptr, third);
    EXPECT_STREQ("child3", third->Name());
}

// ==================== NoChildren Tests ====================

TEST_F(XMLElementTest_79, NoChildren_True_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_TRUE(elem->NoChildren());
}

TEST_F(XMLElementTest_79, NoChildren_False_79) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->InsertNewChildElement("child");
    EXPECT_FALSE(elem->NoChildren());
}

// ==================== UserData Tests ====================

TEST_F(XMLElementTest_79, UserData_SetAndGet_79) {
    XMLElement* elem = doc.NewElement("test");
    int data = 42;
    elem->SetUserData(&data);
    EXPECT_EQ(&data, elem->GetUserData());
}

TEST_F(XMLElementTest_79, UserData_DefaultNull_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->GetUserData());
}

// ==================== Parsing Tests ====================

TEST_F(XMLElementTest_79, ParseFromXML_SimpleElement_79) {
    const char* xml = "<root attr=\"value\">text</root>";
    EXPECT_EQ(XML_SUCCESS, doc.Parse(xml));
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Name());
    EXPECT_STREQ("value", root->Attribute("attr"));
    EXPECT_STREQ("text", root->GetText());
}

TEST_F(XMLElementTest_79, ParseFromXML_NestedElements_79) {
    const char* xml = "<root><level1><level2/></level1></root>";
    EXPECT_EQ(XML_SUCCESS, doc.Parse(xml));
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    XMLElement* level1 = root->FirstChildElement("level1");
    ASSERT_NE(nullptr, level1);
    XMLElement* level2 = level1->FirstChildElement("level2");
    ASSERT_NE(nullptr, level2);
}

// ==================== Multiple Attribute Overwrite Test ====================

TEST_F(XMLElementTest_79, SetAttribute_OverwriteExisting_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("key", "old");
    EXPECT_STREQ("old", elem->Attribute("key"));
    elem->SetAttribute("key", "new");
    EXPECT_STREQ("new", elem->Attribute("key"));
}

// ==================== Accept with XMLVisitor ====================

TEST_F(XMLElementTest_79, Accept_XMLPrinter_79) {
    const char* xml = "<root><child>text</child></root>";
    doc.Parse(xml);
    XMLPrinter printer;
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    bool result = root->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(nullptr, output);
    EXPECT_NE(std::string::npos, std::string(output).find("root"));
}

// ==================== GetDocument Tests ====================

TEST_F(XMLElementTest_79, GetDocument_ReturnsOwningDocument_79) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(&doc, elem->GetDocument());
}

// ==================== Negative value parsing ====================

TEST_F(XMLElementTest_79, IntAttribute_NegativeValue_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", -42);
    EXPECT_EQ(-42, elem->IntAttribute("num", 0));
}

TEST_F(XMLElementTest_79, Int64Attribute_NegativeValue_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", (int64_t)-123456789012345LL);
    EXPECT_EQ(-123456789012345LL, elem->Int64Attribute("num", 0));
}

// ==================== QueryAttribute overloaded versions ====================

TEST_F(XMLElementTest_79, QueryAttribute_IntOverload_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("num", 42);
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("num", &val));
    EXPECT_EQ(42, val);
}

TEST_F(XMLElementTest_79, QueryAttribute_BoolOverload_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("flag", true);
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("flag", &val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_79, QueryAttribute_DoubleOverload_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("val", 3.14);
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &val));
    EXPECT_DOUBLE_EQ(3.14, val);
}

TEST_F(XMLElementTest_79, QueryAttribute_FloatOverload_79) {
    XMLElement* elem = doc.NewElement("test");
    elem->