#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_98 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== SetAttribute Tests ====================

TEST_F(XMLElementTest_98, SetAttributeInt_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("value", 42);
    EXPECT_EQ(42, elem->IntAttribute("value", 0));
}

TEST_F(XMLElementTest_98, SetAttributeString_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("name", "hello");
    EXPECT_STREQ("hello", elem->Attribute("name"));
}

TEST_F(XMLElementTest_98, SetAttributeUnsigned_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (unsigned)123u);
    EXPECT_EQ(123u, elem->UnsignedAttribute("val", 0));
}

TEST_F(XMLElementTest_98, SetAttributeInt64_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t bigVal = 9223372036854775807LL;
    elem->SetAttribute("big", bigVal);
    EXPECT_EQ(bigVal, elem->Int64Attribute("big", 0));
}

TEST_F(XMLElementTest_98, SetAttributeUnsigned64_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetAttribute("ubig", bigVal);
    EXPECT_EQ(bigVal, elem->Unsigned64Attribute("ubig", 0));
}

TEST_F(XMLElementTest_98, SetAttributeBoolTrue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_98, SetAttributeBoolFalse_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("flag", false);
    EXPECT_FALSE(elem->BoolAttribute("flag", true));
}

TEST_F(XMLElementTest_98, SetAttributeDouble_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("dval", 3.14159);
    EXPECT_NEAR(3.14159, elem->DoubleAttribute("dval", 0.0), 0.0001);
}

TEST_F(XMLElementTest_98, SetAttributeFloat_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("fval", 2.5f);
    EXPECT_NEAR(2.5f, elem->FloatAttribute("fval", 0.0f), 0.001f);
}

TEST_F(XMLElementTest_98, SetAttributeOverwrite_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 10);
    EXPECT_EQ(10, elem->IntAttribute("val", 0));
    elem->SetAttribute("val", 20);
    EXPECT_EQ(20, elem->IntAttribute("val", 0));
}

TEST_F(XMLElementTest_98, SetAttributeOverwriteDifferentType_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 10);
    EXPECT_EQ(10, elem->IntAttribute("val", 0));
    elem->SetAttribute("val", "now_a_string");
    EXPECT_STREQ("now_a_string", elem->Attribute("val"));
}

// ==================== Attribute / FindAttribute Tests ====================

TEST_F(XMLElementTest_98, AttributeReturnsNullForNonExistent_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(nullptr, elem->Attribute("nonexistent"));
}

TEST_F(XMLElementTest_98, AttributeWithValueMatch_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("color", "red");
    EXPECT_STREQ("red", elem->Attribute("color", "red"));
}

TEST_F(XMLElementTest_98, AttributeWithValueMismatch_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("color", "red");
    EXPECT_EQ(nullptr, elem->Attribute("color", "blue"));
}

TEST_F(XMLElementTest_98, FindAttributeExisting_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("x", 5);
    const XMLAttribute* attr = elem->FindAttribute("x");
    EXPECT_NE(nullptr, attr);
    EXPECT_STREQ("x", attr->Name());
}

TEST_F(XMLElementTest_98, FindAttributeNonExisting_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    const XMLAttribute* attr = elem->FindAttribute("missing");
    EXPECT_EQ(nullptr, attr);
}

// ==================== Query Attribute Tests ====================

TEST_F(XMLElementTest_98, QueryIntAttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("num", 99);
    int val = 0;
    XMLError err = elem->QueryIntAttribute("num", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(99, val);
}

TEST_F(XMLElementTest_98, QueryIntAttributeNotFound_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int val = -1;
    XMLError err = elem->QueryIntAttribute("missing", &val);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
    EXPECT_EQ(-1, val);
}

TEST_F(XMLElementTest_98, QueryIntAttributeWrongType_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("str", "not_a_number");
    int val = 0;
    XMLError err = elem->QueryIntAttribute("str", &val);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementTest_98, QueryUnsignedAttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("uval", (unsigned)500u);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedAttribute("uval", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(500u, val);
}

TEST_F(XMLElementTest_98, QueryBoolAttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("flag", true);
    bool val = false;
    XMLError err = elem->QueryBoolAttribute("flag", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_98, QueryDoubleAttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("d", 1.5);
    double val = 0.0;
    XMLError err = elem->QueryDoubleAttribute("d", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(1.5, val, 0.0001);
}

TEST_F(XMLElementTest_98, QueryFloatAttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("f", 1.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatAttribute("f", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(1.5f, val, 0.001f);
}

TEST_F(XMLElementTest_98, QueryStringAttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("s", "hello");
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("s", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_STREQ("hello", val);
}

TEST_F(XMLElementTest_98, QueryStringAttributeNotFound_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("missing", &val);
    EXPECT_EQ(XML_NO_ATTRIBUTE, err);
}

TEST_F(XMLElementTest_98, QueryInt64AttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t expected = 1234567890123LL;
    elem->SetAttribute("i64", expected);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Attribute("i64", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(expected, val);
}

TEST_F(XMLElementTest_98, QueryUnsigned64AttributeSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    uint64_t expected = 9876543210ULL;
    elem->SetAttribute("u64", expected);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Attribute("u64", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(expected, val);
}

// ==================== Default Attribute Value Tests ====================

TEST_F(XMLElementTest_98, IntAttributeDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(77, elem->IntAttribute("missing", 77));
}

TEST_F(XMLElementTest_98, UnsignedAttributeDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(100u, elem->UnsignedAttribute("missing", 100u));
}

TEST_F(XMLElementTest_98, BoolAttributeDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
}

TEST_F(XMLElementTest_98, DoubleAttributeDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_NEAR(9.9, elem->DoubleAttribute("missing", 9.9), 0.0001);
}

TEST_F(XMLElementTest_98, FloatAttributeDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_NEAR(1.1f, elem->FloatAttribute("missing", 1.1f), 0.001f);
}

TEST_F(XMLElementTest_98, Int64AttributeDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(555LL, elem->Int64Attribute("missing", 555LL));
}

TEST_F(XMLElementTest_98, Unsigned64AttributeDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(999ULL, elem->Unsigned64Attribute("missing", 999ULL));
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_98, DeleteAttributeExisting_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", 1);
    elem->SetAttribute("b", 2);
    elem->DeleteAttribute("a");
    EXPECT_EQ(nullptr, elem->FindAttribute("a"));
    EXPECT_NE(nullptr, elem->FindAttribute("b"));
}

TEST_F(XMLElementTest_98, DeleteAttributeNonExisting_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", 1);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_NE(nullptr, elem->FindAttribute("a"));
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_98, FirstAttributeNull_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(nullptr, elem->FirstAttribute());
}

TEST_F(XMLElementTest_98, FirstAttributeExists_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("first", "value1");
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_NE(nullptr, attr);
    EXPECT_STREQ("first", attr->Name());
}

// ==================== XMLAttribute Next Tests ====================

TEST_F(XMLElementTest_98, AttributeNextIteration_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", 1);
    elem->SetAttribute("b", 2);
    elem->SetAttribute("c", 3);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(nullptr, attr);
    attr = attr->Next();
    ASSERT_NE(nullptr, attr);
    attr = attr->Next();
    ASSERT_NE(nullptr, attr);
    attr = attr->Next();
    EXPECT_EQ(nullptr, attr);
}

// ==================== SetText / GetText Tests ====================

TEST_F(XMLElementTest_98, SetTextAndGetText_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("Hello World");
    EXPECT_STREQ("Hello World", elem->GetText());
}

TEST_F(XMLElementTest_98, GetTextNullWhenNoText_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(nullptr, elem->GetText());
}

TEST_F(XMLElementTest_98, SetTextInt_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42);
    EXPECT_STREQ("42", elem->GetText());
}

TEST_F(XMLElementTest_98, SetTextUnsigned_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((unsigned)100u);
    EXPECT_STREQ("100", elem->GetText());
}

TEST_F(XMLElementTest_98, SetTextInt64_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((int64_t)1234567890123LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(1234567890123LL, val);
}

TEST_F(XMLElementTest_98, SetTextUnsigned64_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((uint64_t)9876543210ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(9876543210ULL, val);
}

TEST_F(XMLElementTest_98, SetTextBoolTrue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    EXPECT_STREQ("true", elem->GetText());
}

TEST_F(XMLElementTest_98, SetTextBoolFalse_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(false);
    EXPECT_STREQ("false", elem->GetText());
}

TEST_F(XMLElementTest_98, SetTextDouble_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14, val, 0.001);
}

TEST_F(XMLElementTest_98, SetTextFloat_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(2.5f, val, 0.001f);
}

// ==================== QueryText Tests ====================

TEST_F(XMLElementTest_98, QueryIntTextSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(123);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(123, val);
}

TEST_F(XMLElementTest_98, QueryIntTextNoText_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementTest_98, QueryUnsignedTextSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((unsigned)456u);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(456u, val);
}

TEST_F(XMLElementTest_98, QueryBoolTextSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_98, QueryDoubleTextSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(2.718);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(2.718, val, 0.001);
}

TEST_F(XMLElementTest_98, QueryFloatTextSuccess_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(1.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(1.5f, val, 0.001f);
}

// ==================== Default Text Value Tests ====================

TEST_F(XMLElementTest_98, IntTextDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(55, elem->IntText(55));
}

TEST_F(XMLElementTest_98, IntTextWithValue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(10);
    EXPECT_EQ(10, elem->IntText(55));
}

TEST_F(XMLElementTest_98, UnsignedTextDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(77u, elem->UnsignedText(77u));
}

TEST_F(XMLElementTest_98, Int64TextDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(12345LL, elem->Int64Text(12345LL));
}

TEST_F(XMLElementTest_98, Unsigned64TextDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(67890ULL, elem->Unsigned64Text(67890ULL));
}

TEST_F(XMLElementTest_98, BoolTextDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_98, DoubleTextDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_NEAR(3.14, elem->DoubleText(3.14), 0.001);
}

TEST_F(XMLElementTest_98, FloatTextDefault_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_NEAR(2.5f, elem->FloatText(2.5f), 0.001f);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_98, ElementName_98) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertFirstChild(elem);
    EXPECT_STREQ("myElement", elem->Name());
}

TEST_F(XMLElementTest_98, SetElementName_98) {
    XMLElement* elem = doc.NewElement("old");
    doc.InsertFirstChild(elem);
    elem->SetName("new");
    EXPECT_STREQ("new", elem->Name());
}

// ==================== InsertNew* Tests ====================

TEST_F(XMLElementTest_98, InsertNewChildElement_98) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertFirstChild(parent);
    XMLElement* child = parent->InsertNewChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
    EXPECT_EQ(child, parent->FirstChildElement("child"));
}

TEST_F(XMLElementTest_98, InsertNewComment_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ("a comment", comment->Value());
}

TEST_F(XMLElementTest_98, InsertNewText_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("some text", text->Value());
}

TEST_F(XMLElementTest_98, InsertNewDeclaration_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    XMLDeclaration* decl = elem->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(nullptr, decl);
}

TEST_F(XMLElementTest_98, InsertNewUnknown_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(nullptr, unknown);
}

// ==================== ToElement Test ====================

TEST_F(XMLElementTest_98, ToElement_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem, elem->ToElement());
}

// ==================== Multiple Attributes Test ====================

TEST_F(XMLElementTest_98, MultipleAttributesDifferentTypes_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("intVal", 42);
    elem->SetAttribute("strVal", "hello");
    elem->SetAttribute("boolVal", true);
    elem->SetAttribute("doubleVal", 3.14);

    EXPECT_EQ(42, elem->IntAttribute("intVal", 0));
    EXPECT_STREQ("hello", elem->Attribute("strVal"));
    EXPECT_TRUE(elem->BoolAttribute("boolVal", false));
    EXPECT_NEAR(3.14, elem->DoubleAttribute("doubleVal", 0.0), 0.001);
}

// ==================== Boundary Tests ====================

TEST_F(XMLElementTest_98, SetAttributeIntMax_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("max", INT32_MAX);
    EXPECT_EQ(INT32_MAX, elem->IntAttribute("max", 0));
}

TEST_F(XMLElementTest_98, SetAttributeIntMin_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("min", INT32_MIN);
    EXPECT_EQ(INT32_MIN, elem->IntAttribute("min", 0));
}

TEST_F(XMLElementTest_98, SetAttributeZero_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("zero", 0);
    EXPECT_EQ(0, elem->IntAttribute("zero", -1));
}

TEST_F(XMLElementTest_98, SetAttributeNegative_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("neg", -999);
    EXPECT_EQ(-999, elem->IntAttribute("neg", 0));
}

TEST_F(XMLElementTest_98, SetAttributeEmptyString_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("empty", "");
    EXPECT_STREQ("", elem->Attribute("empty"));
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST_F(XMLElementTest_98, ShallowClone_98) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", 1);
    elem->SetAttribute("b", "two");

    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(nullptr, clone);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(nullptr, cloneElem);
    EXPECT_STREQ("original", cloneElem->Name());
    EXPECT_EQ(1, cloneElem->IntAttribute("a", 0));
    EXPECT_STREQ("two", cloneElem->Attribute("b"));
}

TEST_F(XMLElementTest_98, ShallowEqualSame_98) {
    XMLElement* elem1 = doc.NewElement("test");
    doc.InsertFirstChild(elem1);
    elem1->SetAttribute("x", 5);

    XMLNode* clone = elem1->ShallowClone(&doc);
    ASSERT_NE(nullptr, clone);
    EXPECT_TRUE(elem1->ShallowEqual(clone));
}

TEST_F(XMLElementTest_98, ShallowEqualDifferent_98) {
    XMLElement* elem1 = doc.NewElement("test1");
    doc.InsertFirstChild(elem1);

    XMLElement* elem2 = doc.NewElement("test2");
    elem1->InsertEndChild(elem2);

    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// ==================== Parse and Roundtrip Test ====================

TEST_F(XMLElementTest_98, ParseAndRoundtrip_98) {
    const char* xml = "<root attr1=\"42\" attr2=\"hello\"><child>text</child></root>";
    XMLDocument parseDoc;
    XMLError err = parseDoc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);

    XMLElement* root = parseDoc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Name());
    EXPECT_EQ(42, root->IntAttribute("attr1", 0));
    EXPECT_STREQ("hello", root->Attribute("attr2"));

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("text", child->GetText());
}

// ==================== QueryAttribute Overloads Tests ====================

TEST_F(XMLElementTest_98, QueryAttributeIntOverload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 10);
    int v = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_EQ(10, v);
}

TEST_F(XMLElementTest_98, QueryAttributeUnsignedOverload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (unsigned)20u);
    unsigned v = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_EQ(20u, v);
}

TEST_F(XMLElementTest_98, QueryAttributeBoolOverload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", true);
    bool v = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_TRUE(v);
}

TEST_F(XMLElementTest_98, QueryAttributeDoubleOverload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 1.5);
    double v = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_NEAR(1.5, v, 0.001);
}

TEST_F(XMLElementTest_98, QueryAttributeFloatOverload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 2.5f);
    float v = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_NEAR(2.5f, v, 0.001f);
}

TEST_F(XMLElementTest_98, QueryAttributeStringOverload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", "test_string");
    const char* v = nullptr;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_STREQ("test_string", v);
}

TEST_F(XMLElementTest_98, QueryAttributeInt64Overload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (int64_t)123456789LL);
    int64_t v = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_EQ(123456789LL, v);
}

TEST_F(XMLElementTest_98, QueryAttributeUnsigned64Overload_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (uint64_t)987654321ULL);
    uint64_t v = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryAttribute("val", &v));
    EXPECT_EQ(987654321ULL, v);
}

// ==================== XMLAttribute Value Tests ====================

TEST_F(XMLElementTest_98, AttributeIntValue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("n", 42);
    const XMLAttribute* attr = elem->FindAttribute("n");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(42, attr->IntValue());
}

TEST_F(XMLElementTest_98, AttributeUnsignedValue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("n", (unsigned)100u);
    const XMLAttribute* attr = elem->FindAttribute("n");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(100u, attr->UnsignedValue());
}

TEST_F(XMLElementTest_98, AttributeInt64Value_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("n", (int64_t)999999999999LL);
    const XMLAttribute* attr = elem->FindAttribute("n");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(999999999999LL, attr->Int64Value());
}

TEST_F(XMLElementTest_98, AttributeUnsigned64Value_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("n", (uint64_t)888888888888ULL);
    const XMLAttribute* attr = elem->FindAttribute("n");
    ASSERT_NE(nullptr, attr);
    EXPECT_EQ(888888888888ULL, attr->Unsigned64Value());
}

TEST_F(XMLElementTest_98, AttributeBoolValue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("b", true);
    const XMLAttribute* attr = elem->FindAttribute("b");
    ASSERT_NE(nullptr, attr);
    EXPECT_TRUE(attr->BoolValue());
}

TEST_F(XMLElementTest_98, AttributeDoubleValue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("d", 2.718);
    const XMLAttribute* attr = elem->FindAttribute("d");
    ASSERT_NE(nullptr, attr);
    EXPECT_NEAR(2.718, attr->DoubleValue(), 0.001);
}

TEST_F(XMLElementTest_98, AttributeFloatValue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("f", 1.5f);
    const XMLAttribute* attr = elem->FindAttribute("f");
    ASSERT_NE(nullptr, attr);
    EXPECT_NEAR(1.5f, attr->FloatValue(), 0.001f);
}

TEST_F(XMLElementTest_98, AttributeValue_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("s", "value_str");
    const XMLAttribute* attr = elem->FindAttribute("s");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("value_str", attr->Value());
}

// ==================== SetText Overwrite Tests ====================

TEST_F(XMLElementTest_98, SetTextOverwriteExisting_98) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("first");
    EXPECT_STREQ("first", elem->GetText());
    elem->SetText("second");
    EXPECT_STREQ("second", elem->GetText());
}

// ==================== Accept Test ====================

TEST_F(XMLElementTest_98, AcceptVisitor_98) {
    const char* xml = "<root><child/></root>";
    XMLDocument parseDoc;
    parseDoc.Parse(xml);
    XMLPrinter printer;
    parseDoc.RootElement()->Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_N