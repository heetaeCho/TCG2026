#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_78 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ===================== Name() Tests =====================

TEST_F(XMLElementTest_78, Name_ReturnsElementName_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST_F(XMLElementTest_78, Name_ReturnsCorrectNameForNestedElement_78) {
    doc.Parse("<root><child/></root>");
    XMLElement* child = doc.RootElement()->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

TEST_F(XMLElementTest_78, Name_AfterSetName_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetName("newname");
    EXPECT_STREQ(root->Name(), "newname");
}

// ===================== SetName() Tests =====================

TEST_F(XMLElementTest_78, SetName_ChangesName_78) {
    doc.Parse("<original/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetName("changed");
    EXPECT_STREQ(root->Name(), "changed");
}

// ===================== Attribute() Tests =====================

TEST_F(XMLElementTest_78, Attribute_ReturnsValueWhenExists_78) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr"), "value");
}

TEST_F(XMLElementTest_78, Attribute_ReturnsNullWhenNotExists_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_78, Attribute_WithMatchingValue_78) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr", "value"), "value");
}

TEST_F(XMLElementTest_78, Attribute_WithNonMatchingValue_78) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Attribute("attr", "other"), nullptr);
}

// ===================== SetAttribute() / Query Tests =====================

TEST_F(XMLElementTest_78, SetAttribute_String_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("key", "val");
    EXPECT_STREQ(root->Attribute("key"), "val");
}

TEST_F(XMLElementTest_78, SetAttribute_Int_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("num", 42);
    EXPECT_EQ(root->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_78, SetAttribute_UnsignedInt_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("num", (unsigned)100);
    EXPECT_EQ(root->UnsignedAttribute("num", 0), 100u);
}

TEST_F(XMLElementTest_78, SetAttribute_Int64_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    int64_t bigVal = 9223372036854775807LL;
    root->SetAttribute("num", bigVal);
    EXPECT_EQ(root->Int64Attribute("num", 0), bigVal);
}

TEST_F(XMLElementTest_78, SetAttribute_Uint64_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    uint64_t bigVal = 18446744073709551615ULL;
    root->SetAttribute("num", bigVal);
    EXPECT_EQ(root->Unsigned64Attribute("num", 0), bigVal);
}

TEST_F(XMLElementTest_78, SetAttribute_Bool_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("flag", true);
    EXPECT_EQ(root->BoolAttribute("flag", false), true);
}

TEST_F(XMLElementTest_78, SetAttribute_Double_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("val", 3.14);
    EXPECT_NEAR(root->DoubleAttribute("val", 0.0), 3.14, 0.001);
}

TEST_F(XMLElementTest_78, SetAttribute_Float_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("val", 2.5f);
    EXPECT_NEAR(root->FloatAttribute("val", 0.0f), 2.5f, 0.001f);
}

// ===================== Default Attribute Values =====================

TEST_F(XMLElementTest_78, IntAttribute_DefaultValue_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->IntAttribute("missing", 99), 99);
}

TEST_F(XMLElementTest_78, UnsignedAttribute_DefaultValue_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->UnsignedAttribute("missing", 77u), 77u);
}

TEST_F(XMLElementTest_78, BoolAttribute_DefaultValue_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->BoolAttribute("missing", true), true);
}

TEST_F(XMLElementTest_78, DoubleAttribute_DefaultValue_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(root->DoubleAttribute("missing", 1.23), 1.23, 0.001);
}

TEST_F(XMLElementTest_78, FloatAttribute_DefaultValue_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(root->FloatAttribute("missing", 4.56f), 4.56f, 0.001f);
}

TEST_F(XMLElementTest_78, Int64Attribute_DefaultValue_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->Int64Attribute("missing", 123456789LL), 123456789LL);
}

TEST_F(XMLElementTest_78, Unsigned64Attribute_DefaultValue_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->Unsigned64Attribute("missing", 987654321ULL), 987654321ULL);
}

// ===================== QueryAttribute Tests =====================

TEST_F(XMLElementTest_78, QueryIntAttribute_Success_78) {
    doc.Parse("<root val=\"10\"/>");
    XMLElement* root = doc.RootElement();
    int v = 0;
    EXPECT_EQ(root->QueryIntAttribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 10);
}

TEST_F(XMLElementTest_78, QueryIntAttribute_NoAttribute_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    int v = 0;
    EXPECT_EQ(root->QueryIntAttribute("missing", &v), XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_78, QueryUnsignedAttribute_Success_78) {
    doc.Parse("<root val=\"20\"/>");
    XMLElement* root = doc.RootElement();
    unsigned int v = 0;
    EXPECT_EQ(root->QueryUnsignedAttribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 20u);
}

TEST_F(XMLElementTest_78, QueryBoolAttribute_Success_78) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* root = doc.RootElement();
    bool v = false;
    EXPECT_EQ(root->QueryBoolAttribute("val", &v), XML_SUCCESS);
    EXPECT_TRUE(v);
}

TEST_F(XMLElementTest_78, QueryDoubleAttribute_Success_78) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* root = doc.RootElement();
    double v = 0;
    EXPECT_EQ(root->QueryDoubleAttribute("val", &v), XML_SUCCESS);
    EXPECT_NEAR(v, 3.14, 0.001);
}

TEST_F(XMLElementTest_78, QueryFloatAttribute_Success_78) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* root = doc.RootElement();
    float v = 0;
    EXPECT_EQ(root->QueryFloatAttribute("val", &v), XML_SUCCESS);
    EXPECT_NEAR(v, 2.5f, 0.001f);
}

TEST_F(XMLElementTest_78, QueryStringAttribute_Success_78) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    const char* v = nullptr;
    EXPECT_EQ(root->QueryStringAttribute("val", &v), XML_SUCCESS);
    EXPECT_STREQ(v, "hello");
}

TEST_F(XMLElementTest_78, QueryStringAttribute_NoAttribute_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    const char* v = nullptr;
    EXPECT_EQ(root->QueryStringAttribute("missing", &v), XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_78, QueryInt64Attribute_Success_78) {
    doc.Parse("<root val=\"123456789012345\"/>");
    XMLElement* root = doc.RootElement();
    int64_t v = 0;
    EXPECT_EQ(root->QueryInt64Attribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 123456789012345LL);
}

TEST_F(XMLElementTest_78, QueryUnsigned64Attribute_Success_78) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* root = doc.RootElement();
    uint64_t v = 0;
    EXPECT_EQ(root->QueryUnsigned64Attribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 18446744073709551615ULL);
}

// ===================== Text Content Tests =====================

TEST_F(XMLElementTest_78, GetText_ReturnsText_78) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Hello World");
}

TEST_F(XMLElementTest_78, GetText_ReturnsNullForEmptyElement_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

TEST_F(XMLElementTest_78, SetText_String_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText("test text");
    EXPECT_STREQ(root->GetText(), "test text");
}

TEST_F(XMLElementTest_78, SetText_Int_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(42);
    EXPECT_STREQ(root->GetText(), "42");
}

TEST_F(XMLElementTest_78, SetText_Unsigned_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText((unsigned)100);
    EXPECT_STREQ(root->GetText(), "100");
}

TEST_F(XMLElementTest_78, SetText_Bool_True_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(true);
    EXPECT_STREQ(root->GetText(), "true");
}

TEST_F(XMLElementTest_78, SetText_Bool_False_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(false);
    EXPECT_STREQ(root->GetText(), "false");
}

TEST_F(XMLElementTest_78, SetText_Double_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(3.14);
    double val = 0;
    root->QueryDoubleText(&val);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_78, SetText_Float_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText(2.5f);
    float val = 0;
    root->QueryFloatText(&val);
    EXPECT_NEAR(val, 2.5f, 0.01f);
}

TEST_F(XMLElementTest_78, SetText_Int64_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText((int64_t)123456789012345LL);
    int64_t val = 0;
    root->QueryInt64Text(&val);
    EXPECT_EQ(val, 123456789012345LL);
}

TEST_F(XMLElementTest_78, SetText_Uint64_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    root->SetText((uint64_t)18446744073709551615ULL);
    uint64_t val = 0;
    root->QueryUnsigned64Text(&val);
    EXPECT_EQ(val, 18446744073709551615ULL);
}

// ===================== QueryText Tests =====================

TEST_F(XMLElementTest_78, QueryIntText_Success_78) {
    doc.Parse("<root>42</root>");
    XMLElement* root = doc.RootElement();
    int val = 0;
    EXPECT_EQ(root->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_78, QueryIntText_NoText_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    int val = 0;
    EXPECT_NE(root->QueryIntText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_78, QueryUnsignedText_Success_78) {
    doc.Parse("<root>100</root>");
    XMLElement* root = doc.RootElement();
    unsigned val = 0;
    EXPECT_EQ(root->QueryUnsignedText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_78, QueryBoolText_Success_78) {
    doc.Parse("<root>true</root>");
    XMLElement* root = doc.RootElement();
    bool val = false;
    EXPECT_EQ(root->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_78, QueryDoubleText_Success_78) {
    doc.Parse("<root>3.14</root>");
    XMLElement* root = doc.RootElement();
    double val = 0;
    EXPECT_EQ(root->QueryDoubleText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_78, QueryFloatText_Success_78) {
    doc.Parse("<root>2.5</root>");
    XMLElement* root = doc.RootElement();
    float val = 0;
    EXPECT_EQ(root->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 0.001f);
}

TEST_F(XMLElementTest_78, QueryInt64Text_Success_78) {
    doc.Parse("<root>123456789012345</root>");
    XMLElement* root = doc.RootElement();
    int64_t val = 0;
    EXPECT_EQ(root->QueryInt64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 123456789012345LL);
}

TEST_F(XMLElementTest_78, QueryUnsigned64Text_Success_78) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* root = doc.RootElement();
    uint64_t val = 0;
    EXPECT_EQ(root->QueryUnsigned64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 18446744073709551615ULL);
}

// ===================== DefaultText Tests =====================

TEST_F(XMLElementTest_78, IntText_ReturnsValue_78) {
    doc.Parse("<root>42</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->IntText(0), 42);
}

TEST_F(XMLElementTest_78, IntText_DefaultWhenNoText_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->IntText(99), 99);
}

TEST_F(XMLElementTest_78, UnsignedText_ReturnsValue_78) {
    doc.Parse("<root>50</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->UnsignedText(0), 50u);
}

TEST_F(XMLElementTest_78, UnsignedText_DefaultWhenNoText_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->UnsignedText(88u), 88u);
}

TEST_F(XMLElementTest_78, Int64Text_ReturnsValue_78) {
    doc.Parse("<root>123456789012345</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->Int64Text(0), 123456789012345LL);
}

TEST_F(XMLElementTest_78, Unsigned64Text_ReturnsValue_78) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->Unsigned64Text(0), 18446744073709551615ULL);
}

TEST_F(XMLElementTest_78, BoolText_ReturnsValue_78) {
    doc.Parse("<root>true</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_TRUE(root->BoolText(false));
}

TEST_F(XMLElementTest_78, BoolText_DefaultWhenNoText_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_TRUE(root->BoolText(true));
}

TEST_F(XMLElementTest_78, DoubleText_ReturnsValue_78) {
    doc.Parse("<root>3.14</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(root->DoubleText(0.0), 3.14, 0.001);
}

TEST_F(XMLElementTest_78, FloatText_ReturnsValue_78) {
    doc.Parse("<root>2.5</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_NEAR(root->FloatText(0.0f), 2.5f, 0.001f);
}

// ===================== FindAttribute Tests =====================

TEST_F(XMLElementTest_78, FindAttribute_Exists_78) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    const XMLAttribute* attr = root->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_78, FindAttribute_NotExists_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->FindAttribute("missing"), nullptr);
}

// ===================== FirstAttribute Tests =====================

TEST_F(XMLElementTest_78, FirstAttribute_Exists_78) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* root = doc.RootElement();
    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_78, FirstAttribute_Empty_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->FirstAttribute(), nullptr);
}

// ===================== DeleteAttribute Tests =====================

TEST_F(XMLElementTest_78, DeleteAttribute_RemovesAttribute_78) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root->FindAttribute("key"), nullptr);
    root->DeleteAttribute("key");
    EXPECT_EQ(root->FindAttribute("key"), nullptr);
}

TEST_F(XMLElementTest_78, DeleteAttribute_NonExistent_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    // Should not crash when deleting non-existent attribute
    root->DeleteAttribute("nonexistent");
    EXPECT_EQ(root->FindAttribute("nonexistent"), nullptr);
}

// ===================== InsertNewChildElement Tests =====================

TEST_F(XMLElementTest_78, InsertNewChildElement_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(root->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_78, InsertNewComment_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLComment* comment = root->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_FALSE(root->NoChildren());
}

TEST_F(XMLElementTest_78, InsertNewText_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLText* text = root->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(root->GetText(), "some text");
}

TEST_F(XMLElementTest_78, InsertNewDeclaration_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLDeclaration* decl = root->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    EXPECT_FALSE(root->NoChildren());
}

TEST_F(XMLElementTest_78, InsertNewUnknown_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLUnknown* unknown = root->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
    EXPECT_FALSE(root->NoChildren());
}

// ===================== ToElement Tests =====================

TEST_F(XMLElementTest_78, ToElement_ReturnsThis_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->ToElement(), root);
}

// ===================== Child Navigation Tests =====================

TEST_F(XMLElementTest_78, FirstChildElement_ByName_78) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
}

TEST_F(XMLElementTest_78, LastChildElement_ByName_78) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* last_a = root->LastChildElement("a");
    ASSERT_NE(last_a, nullptr);
    // It should be the last 'a', not the first
    EXPECT_EQ(last_a->NextSiblingElement("a"), nullptr);
}

TEST_F(XMLElementTest_78, NextSiblingElement_78) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
}

TEST_F(XMLElementTest_78, PreviousSiblingElement_78) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* c = root->LastChildElement("c");
    ASSERT_NE(c, nullptr);
    XMLElement* b = c->PreviousSiblingElement();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
}

// ===================== ChildElementCount Tests =====================

TEST_F(XMLElementTest_78, ChildElementCount_All_78) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->ChildElementCount(), 3);
}

TEST_F(XMLElementTest_78, ChildElementCount_ByName_78) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->ChildElementCount("a"), 2);
    EXPECT_EQ(root->ChildElementCount("b"), 1);
    EXPECT_EQ(root->ChildElementCount("c"), 0);
}

TEST_F(XMLElementTest_78, ChildElementCount_Empty_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// ===================== ShallowClone Tests =====================

TEST_F(XMLElementTest_78, ShallowClone_CopiesNameAndAttributes_78) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.RootElement();
    XMLDocument targetDoc;
    XMLNode* clone = root->ShallowClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
    targetDoc.InsertEndChild(clone);
}

// ===================== DeepClone Tests =====================

TEST_F(XMLElementTest_78, DeepClone_CopiesChildren_78) {
    doc.Parse("<root><child>text</child></root>");
    XMLElement* root = doc.RootElement();
    XMLDocument targetDoc;
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    XMLElement* cloneChild = cloneElem->FirstChildElement("child");
    ASSERT_NE(cloneChild, nullptr);
    EXPECT_STREQ(cloneChild->GetText(), "text");
}

// ===================== ShallowEqual Tests =====================

TEST_F(XMLElementTest_78, ShallowEqual_SameElement_78) {
    doc.Parse("<root attr=\"1\"/>");
    XMLElement* root = doc.RootElement();
    XMLDocument doc2;
    doc2.Parse("<root attr=\"1\"/>");
    XMLElement* root2 = doc2.RootElement();
    EXPECT_TRUE(root->ShallowEqual(root2));
}

TEST_F(XMLElementTest_78, ShallowEqual_DifferentAttributes_78) {
    doc.Parse("<root attr=\"1\"/>");
    XMLElement* root = doc.RootElement();
    XMLDocument doc2;
    doc2.Parse("<root attr=\"2\"/>");
    XMLElement* root2 = doc2.RootElement();
    EXPECT_FALSE(root->ShallowEqual(root2));
}

TEST_F(XMLElementTest_78, ShallowEqual_DifferentNames_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* root2 = doc2.RootElement();
    EXPECT_FALSE(root->ShallowEqual(root2));
}

// ===================== DeleteChildren Tests =====================

TEST_F(XMLElementTest_78, DeleteChildren_RemovesAll_78) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// ===================== InsertEndChild Tests =====================

TEST_F(XMLElementTest_78, InsertEndChild_AppendsChild_78) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* newElem = doc.NewElement("b");
    root->InsertEndChild(newElem);
    EXPECT_STREQ(root->LastChildElement()->Name(), "b");
}

// ===================== InsertFirstChild Tests =====================

TEST_F(XMLElementTest_78, InsertFirstChild_PrependsChild_78) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* newElem = doc.NewElement("b");
    root->InsertFirstChild(newElem);
    EXPECT_STREQ(root->FirstChildElement()->Name(), "b");
}

// ===================== InsertAfterChild Tests =====================

TEST_F(XMLElementTest_78, InsertAfterChild_InsertsCorrectly_78) {
    doc.Parse("<root><a/><c/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* a = root->FirstChildElement("a");
    XMLElement* newElem = doc.NewElement("b");
    root->InsertAfterChild(a, newElem);
    XMLElement* afterA = a->NextSiblingElement();
    ASSERT_NE(afterA, nullptr);
    EXPECT_STREQ(afterA->Name(), "b");
}

// ===================== DeleteChild Tests =====================

TEST_F(XMLElementTest_78, DeleteChild_RemovesSpecificChild_78) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* b = root->FirstChildElement("b");
    root->DeleteChild(b);
    EXPECT_EQ(root->FirstChildElement("b"), nullptr);
    EXPECT_EQ(root->ChildElementCount(), 2);
}

// ===================== NoChildren Tests =====================

TEST_F(XMLElementTest_78, NoChildren_ReturnsTrueWhenEmpty_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLElementTest_78, NoChildren_ReturnsFalseWithChildren_78) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    EXPECT_FALSE(root->NoChildren());
}

// ===================== UserData Tests =====================

TEST_F(XMLElementTest_78, UserData_SetAndGet_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);
}

TEST_F(XMLElementTest_78, UserData_DefaultNull_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->GetUserData(), nullptr);
}

// ===================== GetDocument Tests =====================

TEST_F(XMLElementTest_78, GetDocument_ReturnsOwningDocument_78) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->GetDocument(), &doc);
}

// ===================== Parent Tests =====================

TEST_F(XMLElementTest_78, Parent_ReturnsParent_78) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->Parent(), root);
}

// ===================== Multiple Attributes Tests =====================

TEST_F(XMLElementTest_78, MultipleAttributes_78) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* root = doc.RootElement();
    EXPECT_STREQ(root->Attribute("a"), "1");
    EXPECT_STREQ(root->Attribute("b"), "2");
    EXPECT_STREQ(root->Attribute("c"), "3");
}

TEST_F(XMLElementTest_78, SetAttribute_OverwritesExisting_78) {
    doc.Parse("<root key=\"old\"/>");
    XMLElement* root = doc.RootElement();
    root->SetAttribute("key", "new");
    EXPECT_STREQ(root->Attribute("key"), "new");
}

// ===================== Query Attribute wrong type =====================

TEST_F(XMLElementTest_78, QueryIntAttribute_WrongType_78) {
    doc.Parse("<root val=\"notanumber\"/>");
    XMLElement* root = doc.RootElement();
    int v = 0;
    XMLError err = root->QueryIntAttribute("val", &v);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_78, QueryBoolAttribute_WrongType_78) {
    doc.Parse("<root val=\"notabool\"/>");
    XMLElement* root = doc.RootElement();
    bool v = false;
    XMLError err = root->QueryBoolAttribute("val", &v);
    EXPECT_NE(err, XML_SUCCESS);
}

// ===================== Complex Document Tests =====================

TEST_F(XMLElementTest_78, ComplexDocument_NavigateAndRead_78) {
    const char* xml = 
        "<library>"
        "  <book title=\"A\" pages=\"100\">"
        "    <author>Author1</author>"
        "  </book>"
        "  <book title=\"B\" pages=\"200\">"
        "    <author>Author2</author>"
        "  </book>"
        "</library>";
    doc.Parse(xml);
    XMLElement* library = doc.RootElement();
    ASSERT_NE(library, nullptr);
    EXPECT_STREQ(library->Name(), "library");
    
    XMLElement* book1 = library->FirstChildElement("book");
    ASSERT_NE(book1, nullptr);
    EXPECT_STREQ(book1->Attribute("title"), "A");
    EXPECT_EQ(book1->IntAttribute("pages", 0), 100);
    
    XMLElement* author1 = book1->FirstChildElement("author");
    ASSERT_NE(author1, nullptr);
    EXPECT_STREQ(author1->GetText(), "Author1");
    
    XMLElement* book2 = book1->NextSiblingElement("book");
    ASSERT_NE(book2, nullptr);
    EXPECT_STREQ(book2->Attribute("title"), "B");
    EXPECT_EQ(book2->IntAttribute("pages", 0), 200);
    
    XMLElement* author2 = book2->FirstChildElement("author");
    ASSERT_NE(author2, nullptr);
    EXPECT_STREQ(author2->GetText(), "Author2");
}

// ===================== SetText replaces existing text =====================

TEST_F(XMLElementTest_78, SetText_ReplacesExistingText_78) {
    doc.Parse("<root>old text</root>");
    XMLElement* root = doc.RootElement();
    EXPECT_STREQ(root->GetText(), "old text");
    root->SetText("new text");
    EXPECT_STREQ(root->GetText(), "new text");
}

// ===================== Accept Visitor Test =====================

TEST_F(XML