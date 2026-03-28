#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_105 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_105, FirstAttribute_NoAttributes_ReturnsNull_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->FirstAttribute(), nullptr);
}

TEST_F(XMLElementTest_105, FirstAttribute_WithOneAttribute_ReturnsNonNull_105) {
    doc.Parse("<root attr1=\"value1\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr1");
    EXPECT_STREQ(attr->Value(), "value1");
}

TEST_F(XMLElementTest_105, FirstAttribute_WithMultipleAttributes_ReturnsFirst_105) {
    doc.Parse("<root attr1=\"v1\" attr2=\"v2\" attr3=\"v3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr1");
    EXPECT_STREQ(attr->Value(), "v1");
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_105, FindAttribute_Exists_ReturnsAttribute_105) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_105, FindAttribute_NotExists_ReturnsNull_105) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->FindAttribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_105, FindAttribute_EmptyElement_ReturnsNull_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->FindAttribute("anything"), nullptr);
}

// ==================== Attribute (string) Tests ====================

TEST_F(XMLElementTest_105, Attribute_Exists_ReturnsValue_105) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("name"), "hello");
}

TEST_F(XMLElementTest_105, Attribute_NotExists_ReturnsNull_105) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Attribute("missing"), nullptr);
}

TEST_F(XMLElementTest_105, Attribute_WithValueMatch_ReturnsValue_105) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("name", "hello"), "hello");
}

TEST_F(XMLElementTest_105, Attribute_WithValueMismatch_ReturnsNull_105) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Attribute("name", "world"), nullptr);
}

// ==================== SetAttribute / QueryAttribute Tests ====================

TEST_F(XMLElementTest_105, SetAttribute_String_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("key", "value");
    EXPECT_STREQ(root->Attribute("key"), "value");
}

TEST_F(XMLElementTest_105, SetAttribute_Int_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("num", 42);
    EXPECT_EQ(root->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_105, SetAttribute_Unsigned_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("num", (unsigned)100);
    EXPECT_EQ(root->UnsignedAttribute("num", 0), 100u);
}

TEST_F(XMLElementTest_105, SetAttribute_Int64_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int64_t val = 9223372036854775807LL;
    root->SetAttribute("num", val);
    EXPECT_EQ(root->Int64Attribute("num", 0), val);
}

TEST_F(XMLElementTest_105, SetAttribute_Uint64_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    uint64_t val = 18446744073709551615ULL;
    root->SetAttribute("num", val);
    EXPECT_EQ(root->Unsigned64Attribute("num", 0), val);
}

TEST_F(XMLElementTest_105, SetAttribute_Bool_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("flag", true);
    EXPECT_EQ(root->BoolAttribute("flag", false), true);
}

TEST_F(XMLElementTest_105, SetAttribute_Double_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("val", 3.14);
    EXPECT_NEAR(root->DoubleAttribute("val", 0.0), 3.14, 0.001);
}

TEST_F(XMLElementTest_105, SetAttribute_Float_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("val", 2.5f);
    EXPECT_NEAR(root->FloatAttribute("val", 0.0f), 2.5f, 0.001f);
}

// ==================== Attribute Default Value Tests ====================

TEST_F(XMLElementTest_105, IntAttribute_Default_WhenMissing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->IntAttribute("missing", 99), 99);
}

TEST_F(XMLElementTest_105, UnsignedAttribute_Default_WhenMissing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->UnsignedAttribute("missing", 99u), 99u);
}

TEST_F(XMLElementTest_105, Int64Attribute_Default_WhenMissing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Int64Attribute("missing", 123456789LL), 123456789LL);
}

TEST_F(XMLElementTest_105, Unsigned64Attribute_Default_WhenMissing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Unsigned64Attribute("missing", 123456789ULL), 123456789ULL);
}

TEST_F(XMLElementTest_105, BoolAttribute_Default_WhenMissing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->BoolAttribute("missing", true), true);
    EXPECT_EQ(root->BoolAttribute("missing", false), false);
}

TEST_F(XMLElementTest_105, DoubleAttribute_Default_WhenMissing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_DOUBLE_EQ(root->DoubleAttribute("missing", 1.23), 1.23);
}

TEST_F(XMLElementTest_105, FloatAttribute_Default_WhenMissing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_FLOAT_EQ(root->FloatAttribute("missing", 1.23f), 1.23f);
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_105, QueryIntAttribute_Success_105) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int v = 0;
    EXPECT_EQ(root->QueryIntAttribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 42);
}

TEST_F(XMLElementTest_105, QueryIntAttribute_NoAttribute_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int v = 0;
    EXPECT_EQ(root->QueryIntAttribute("val", &v), XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_105, QueryIntAttribute_WrongType_105) {
    doc.Parse("<root val=\"notanumber\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int v = 0;
    EXPECT_EQ(root->QueryIntAttribute("val", &v), XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLElementTest_105, QueryUnsignedAttribute_Success_105) {
    doc.Parse("<root val=\"100\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    unsigned v = 0;
    EXPECT_EQ(root->QueryUnsignedAttribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 100u);
}

TEST_F(XMLElementTest_105, QueryBoolAttribute_Success_True_105) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    bool v = false;
    EXPECT_EQ(root->QueryBoolAttribute("val", &v), XML_SUCCESS);
    EXPECT_TRUE(v);
}

TEST_F(XMLElementTest_105, QueryBoolAttribute_Success_False_105) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    bool v = true;
    EXPECT_EQ(root->QueryBoolAttribute("val", &v), XML_SUCCESS);
    EXPECT_FALSE(v);
}

TEST_F(XMLElementTest_105, QueryDoubleAttribute_Success_105) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    double v = 0;
    EXPECT_EQ(root->QueryDoubleAttribute("val", &v), XML_SUCCESS);
    EXPECT_NEAR(v, 3.14159, 0.00001);
}

TEST_F(XMLElementTest_105, QueryFloatAttribute_Success_105) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    float v = 0;
    EXPECT_EQ(root->QueryFloatAttribute("val", &v), XML_SUCCESS);
    EXPECT_NEAR(v, 2.5f, 0.001f);
}

TEST_F(XMLElementTest_105, QueryStringAttribute_Success_105) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const char* v = nullptr;
    EXPECT_EQ(root->QueryStringAttribute("val", &v), XML_SUCCESS);
    EXPECT_STREQ(v, "hello");
}

TEST_F(XMLElementTest_105, QueryStringAttribute_NoAttribute_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const char* v = nullptr;
    EXPECT_EQ(root->QueryStringAttribute("val", &v), XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_105, QueryInt64Attribute_Success_105) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int64_t v = 0;
    EXPECT_EQ(root->QueryInt64Attribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 9223372036854775807LL);
}

TEST_F(XMLElementTest_105, QueryUnsigned64Attribute_Success_105) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    uint64_t v = 0;
    EXPECT_EQ(root->QueryUnsigned64Attribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 18446744073709551615ULL);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_105, DeleteAttribute_Exists_105) {
    doc.Parse("<root attr1=\"v1\" attr2=\"v2\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->DeleteAttribute("attr1");
    EXPECT_EQ(root->FindAttribute("attr1"), nullptr);
    EXPECT_NE(root->FindAttribute("attr2"), nullptr);
}

TEST_F(XMLElementTest_105, DeleteAttribute_NotExists_NoError_105) {
    doc.Parse("<root attr1=\"v1\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->DeleteAttribute("nonexistent");
    EXPECT_NE(root->FindAttribute("attr1"), nullptr);
}

TEST_F(XMLElementTest_105, DeleteAttribute_AllAttributes_105) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->DeleteAttribute("a");
    root->DeleteAttribute("b");
    root->DeleteAttribute("c");
    EXPECT_EQ(root->FirstAttribute(), nullptr);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_105, Name_ReturnsElementName_105) {
    doc.Parse("<myElement/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "myElement");
}

TEST_F(XMLElementTest_105, SetName_ChangesElementName_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetName("newName");
    EXPECT_STREQ(root->Name(), "newName");
}

// ==================== GetText / SetText Tests ====================

TEST_F(XMLElementTest_105, GetText_WithTextContent_105) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Hello World");
}

TEST_F(XMLElementTest_105, GetText_Empty_ReturnsNull_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

TEST_F(XMLElementTest_105, SetText_String_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText("Test text");
    EXPECT_STREQ(root->GetText(), "Test text");
}

TEST_F(XMLElementTest_105, SetText_Int_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText(42);
    int val = 0;
    EXPECT_EQ(root->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_105, SetText_Unsigned_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText((unsigned)100);
    unsigned val = 0;
    EXPECT_EQ(root->QueryUnsignedText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_105, SetText_Int64_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText((int64_t)123456789012345LL);
    int64_t val = 0;
    EXPECT_EQ(root->QueryInt64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 123456789012345LL);
}

TEST_F(XMLElementTest_105, SetText_Uint64_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText((uint64_t)123456789012345ULL);
    uint64_t val = 0;
    EXPECT_EQ(root->QueryUnsigned64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 123456789012345ULL);
}

TEST_F(XMLElementTest_105, SetText_Bool_True_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText(true);
    bool val = false;
    EXPECT_EQ(root->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_105, SetText_Bool_False_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText(false);
    bool val = true;
    EXPECT_EQ(root->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_105, SetText_Double_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText(3.14);
    double val = 0;
    EXPECT_EQ(root->QueryDoubleText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

TEST_F(XMLElementTest_105, SetText_Float_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText(2.5f);
    float val = 0;
    EXPECT_EQ(root->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 0.001f);
}

// ==================== QueryText Tests ====================

TEST_F(XMLElementTest_105, QueryIntText_NoText_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int val = 0;
    EXPECT_NE(root->QueryIntText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_105, QueryIntText_InvalidText_105) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int val = 0;
    EXPECT_EQ(root->QueryIntText(&val), XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(XMLElementTest_105, QueryUnsignedText_NoText_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    unsigned val = 0;
    EXPECT_NE(root->QueryUnsignedText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_105, QueryBoolText_NoText_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    bool val = false;
    EXPECT_NE(root->QueryBoolText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_105, QueryDoubleText_NoText_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    double val = 0;
    EXPECT_NE(root->QueryDoubleText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_105, QueryFloatText_NoText_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    float val = 0;
    EXPECT_NE(root->QueryFloatText(&val), XML_SUCCESS);
}

// ==================== Default Text Value Tests ====================

TEST_F(XMLElementTest_105, IntText_WithText_105) {
    doc.Parse("<root>42</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->IntText(0), 42);
}

TEST_F(XMLElementTest_105, IntText_Default_WhenEmpty_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->IntText(99), 99);
}

TEST_F(XMLElementTest_105, UnsignedText_WithText_105) {
    doc.Parse("<root>100</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->UnsignedText(0), 100u);
}

TEST_F(XMLElementTest_105, UnsignedText_Default_WhenEmpty_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->UnsignedText(77u), 77u);
}

TEST_F(XMLElementTest_105, Int64Text_WithText_105) {
    doc.Parse("<root>123456789012345</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Int64Text(0), 123456789012345LL);
}

TEST_F(XMLElementTest_105, Int64Text_Default_WhenEmpty_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Int64Text(555LL), 555LL);
}

TEST_F(XMLElementTest_105, Unsigned64Text_Default_WhenEmpty_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Unsigned64Text(555ULL), 555ULL);
}

TEST_F(XMLElementTest_105, BoolText_WithText_True_105) {
    doc.Parse("<root>true</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->BoolText(false));
}

TEST_F(XMLElementTest_105, BoolText_Default_WhenEmpty_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->BoolText(true));
    EXPECT_FALSE(root->BoolText(false));
}

TEST_F(XMLElementTest_105, DoubleText_WithText_105) {
    doc.Parse("<root>3.14</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_NEAR(root->DoubleText(0.0), 3.14, 0.001);
}

TEST_F(XMLElementTest_105, DoubleText_Default_WhenEmpty_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_DOUBLE_EQ(root->DoubleText(9.99), 9.99);
}

TEST_F(XMLElementTest_105, FloatText_WithText_105) {
    doc.Parse("<root>2.5</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_NEAR(root->FloatText(0.0f), 2.5f, 0.001f);
}

TEST_F(XMLElementTest_105, FloatText_Default_WhenEmpty_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_FLOAT_EQ(root->FloatText(9.99f), 9.99f);
}

// ==================== InsertNew* Tests ====================

TEST_F(XMLElementTest_105, InsertNewChildElement_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(root->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_105, InsertNewComment_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLComment* comment = root->InsertNewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
}

TEST_F(XMLElementTest_105, InsertNewText_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLText* text = root->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(root->GetText(), "some text");
}

TEST_F(XMLElementTest_105, InsertNewDeclaration_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLDeclaration* decl = root->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_105, InsertNewUnknown_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLUnknown* unknown = root->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_105, ToElement_ReturnsThis_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ToElement(), root);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_105, ShallowClone_ClonesNameAndAttributes_105) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");

    doc.DeleteNode(clone);
}

TEST_F(XMLElementTest_105, ShallowClone_DoesNotCloneChildren_105) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_EQ(cloneElem->FirstChildElement(), nullptr);

    doc.DeleteNode(clone);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_105, ShallowEqual_SameNameAndAttributes_105) {
    XMLDocument doc2;
    doc.Parse("<root attr=\"val\"/>");
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* e1 = doc.RootElement();
    XMLElement* e2 = doc2.RootElement();
    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    EXPECT_TRUE(e1->ShallowEqual(e2));
}

TEST_F(XMLElementTest_105, ShallowEqual_DifferentName_105) {
    XMLDocument doc2;
    doc.Parse("<root/>");
    doc2.Parse("<other/>");
    XMLElement* e1 = doc.RootElement();
    XMLElement* e2 = doc2.RootElement();
    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

TEST_F(XMLElementTest_105, ShallowEqual_DifferentAttributes_105) {
    XMLDocument doc2;
    doc.Parse("<root attr=\"val1\"/>");
    doc2.Parse("<root attr=\"val2\"/>");
    XMLElement* e1 = doc.RootElement();
    XMLElement* e2 = doc2.RootElement();
    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

TEST_F(XMLElementTest_105, ShallowEqual_DifferentAttributeCount_105) {
    XMLDocument doc2;
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    doc2.Parse("<root a=\"1\"/>");
    XMLElement* e1 = doc.RootElement();
    XMLElement* e2 = doc2.RootElement();
    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

// ==================== SetAttribute Overwrite Tests ====================

TEST_F(XMLElementTest_105, SetAttribute_OverwriteExisting_105) {
    doc.Parse("<root key=\"old\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("key", "new");
    EXPECT_STREQ(root->Attribute("key"), "new");
}

// ==================== Multiple Children Tests ====================

TEST_F(XMLElementTest_105, InsertMultipleChildElements_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->InsertNewChildElement("a");
    root->InsertNewChildElement("b");
    root->InsertNewChildElement("c");

    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "a");

    XMLElement* second = first->NextSiblingElement();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Name(), "b");

    XMLElement* third = second->NextSiblingElement();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Name(), "c");

    EXPECT_EQ(third->NextSiblingElement(), nullptr);
}

// ==================== Attribute Iteration Tests ====================

TEST_F(XMLElementTest_105, AttributeIteration_105) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");

    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "b");

    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "c");

    attr = attr->Next();
    EXPECT_EQ(attr, nullptr);
}

// ==================== ClosingType Tests ====================

TEST_F(XMLElementTest_105, ClosingType_SelfClosing_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    // Just call it to ensure it doesn't crash; the exact value is implementation-defined
    root->ClosingType();
}

// ==================== Edge Cases ====================

TEST_F(XMLElementTest_105, SetText_OverwriteExisting_105) {
    doc.Parse("<root>old text</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetText("new text");
    EXPECT_STREQ(root->GetText(), "new text");
}

TEST_F(XMLElementTest_105, SetAttribute_EmptyString_105) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    root->SetAttribute("key", "");
    EXPECT_STREQ(root->Attribute("key"), "");
}

TEST_F(XMLElementTest_105, GetText_WithChildElement_NoDirectText_105) {
    doc.Parse("<root><child>text</child></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    // GetText returns text of the first child text node
    // If first child is an element, GetText should return nullptr
    EXPECT_EQ(root->GetText(), nullptr);
}

TEST_F(XMLElementTest_105, NegativeIntAttribute_105) {
    doc.Parse("<root val=\"-42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->IntAttribute("val", 0), -42);
}

TEST_F(XMLElementTest_105, NegativeInt64Attribute_105) {
    doc.Parse("<root val=\"-9223372036854775807\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Int64Attribute("val", 0), -9223372036854775807LL);
}

TEST_F(XMLElementTest_105, ZeroIntAttribute_105) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->IntAttribute("val", 99), 0);
}

TEST_F(XMLElementTest_105, QueryAttribute_Int_Overload_105) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int v = 0;
    EXPECT_EQ(root->QueryAttribute("val", &v), XML_SUCCESS);
    EXPECT_EQ(v, 42);
}