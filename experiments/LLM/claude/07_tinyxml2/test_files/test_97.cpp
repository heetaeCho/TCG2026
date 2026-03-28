#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_97 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElement(const char* name = "test") {
        XMLElement* elem = doc.NewElement(name);
        doc.InsertEndChild(elem);
        return elem;
    }
};

// ========== SetAttribute (string) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeString_Basic_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("color", "red");
    EXPECT_STREQ(elem->Attribute("color"), "red");
}

TEST_F(XMLElementTest_97, SetAttributeString_OverwriteExisting_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("color", "red");
    elem->SetAttribute("color", "blue");
    EXPECT_STREQ(elem->Attribute("color"), "blue");
}

TEST_F(XMLElementTest_97, SetAttributeString_EmptyValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("name", "");
    EXPECT_STREQ(elem->Attribute("name"), "");
}

TEST_F(XMLElementTest_97, SetAttributeString_MultipleAttributes_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    elem->SetAttribute("c", "3");
    EXPECT_STREQ(elem->Attribute("a"), "1");
    EXPECT_STREQ(elem->Attribute("b"), "2");
    EXPECT_STREQ(elem->Attribute("c"), "3");
}

TEST_F(XMLElementTest_97, SetAttributeString_SpecialCharacters_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("data", "hello world & <tag>");
    EXPECT_STREQ(elem->Attribute("data"), "hello world & <tag>");
}

// ========== SetAttribute (int) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeInt_Basic_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("count", 42);
    EXPECT_EQ(elem->IntAttribute("count"), 42);
}

TEST_F(XMLElementTest_97, SetAttributeInt_Negative_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("value", -100);
    EXPECT_EQ(elem->IntAttribute("value"), -100);
}

TEST_F(XMLElementTest_97, SetAttributeInt_Zero_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("value", 0);
    EXPECT_EQ(elem->IntAttribute("value"), 0);
}

// ========== SetAttribute (unsigned) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeUnsigned_Basic_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("count", (unsigned)42);
    EXPECT_EQ(elem->UnsignedAttribute("count"), 42u);
}

TEST_F(XMLElementTest_97, SetAttributeUnsigned_LargeValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("big", (unsigned)4294967295u);
    EXPECT_EQ(elem->UnsignedAttribute("big"), 4294967295u);
}

// ========== SetAttribute (int64_t) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeInt64_Basic_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("bignum", (int64_t)9223372036854775807LL);
    EXPECT_EQ(elem->Int64Attribute("bignum"), 9223372036854775807LL);
}

TEST_F(XMLElementTest_97, SetAttributeInt64_Negative_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("negbig", (int64_t)-9223372036854775807LL);
    EXPECT_EQ(elem->Int64Attribute("negbig"), -9223372036854775807LL);
}

// ========== SetAttribute (uint64_t) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeUint64_Basic_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("ubig", (uint64_t)18446744073709551615ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("ubig"), 18446744073709551615ULL);
}

// ========== SetAttribute (bool) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeBool_True_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag"));
}

TEST_F(XMLElementTest_97, SetAttributeBool_False_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("flag", false);
    EXPECT_FALSE(elem->BoolAttribute("flag"));
}

// ========== SetAttribute (double) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeDouble_Basic_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("pi", 3.14159);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("pi"), 3.14159);
}

TEST_F(XMLElementTest_97, SetAttributeDouble_Negative_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("neg", -2.718);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("neg"), -2.718);
}

TEST_F(XMLElementTest_97, SetAttributeDouble_Zero_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("zero", 0.0);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("zero"), 0.0);
}

// ========== SetAttribute (float) Tests ==========

TEST_F(XMLElementTest_97, SetAttributeFloat_Basic_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("fval", 1.5f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("fval"), 1.5f);
}

TEST_F(XMLElementTest_97, SetAttributeFloat_Negative_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("fval", -3.25f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("fval"), -3.25f);
}

// ========== Attribute (lookup) Tests ==========

TEST_F(XMLElementTest_97, Attribute_NotFound_ReturnsNull_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_97, Attribute_WithValueMatch_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("color", "red");
    EXPECT_STREQ(elem->Attribute("color", "red"), "red");
}

TEST_F(XMLElementTest_97, Attribute_WithValueMismatch_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("color", "red");
    EXPECT_EQ(elem->Attribute("color", "blue"), nullptr);
}

// ========== FindAttribute Tests ==========

TEST_F(XMLElementTest_97, FindAttribute_Exists_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "value");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "key");
    EXPECT_STREQ(attr->Value(), "value");
}

TEST_F(XMLElementTest_97, FindAttribute_NotExists_97) {
    XMLElement* elem = CreateElement();
    const XMLAttribute* attr = elem->FindAttribute("missing");
    EXPECT_EQ(attr, nullptr);
}

// ========== FirstAttribute Tests ==========

TEST_F(XMLElementTest_97, FirstAttribute_NoAttributes_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

TEST_F(XMLElementTest_97, FirstAttribute_WithAttributes_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
}

// ========== XMLAttribute::Next Tests ==========

TEST_F(XMLElementTest_97, AttributeNext_TraverseAll_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    elem->SetAttribute("c", "3");

    const XMLAttribute* attr = elem->FirstAttribute();
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

// ========== DeleteAttribute Tests ==========

TEST_F(XMLElementTest_97, DeleteAttribute_Existing_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "value");
    EXPECT_NE(elem->Attribute("key"), nullptr);
    elem->DeleteAttribute("key");
    EXPECT_EQ(elem->Attribute("key"), nullptr);
}

TEST_F(XMLElementTest_97, DeleteAttribute_NonExisting_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "value");
    elem->DeleteAttribute("nonexistent"); // Should not crash
    EXPECT_STREQ(elem->Attribute("key"), "value");
}

TEST_F(XMLElementTest_97, DeleteAttribute_MiddleAttribute_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    elem->SetAttribute("c", "3");
    elem->DeleteAttribute("b");
    EXPECT_STREQ(elem->Attribute("a"), "1");
    EXPECT_EQ(elem->Attribute("b"), nullptr);
    EXPECT_STREQ(elem->Attribute("c"), "3");
}

// ========== QueryAttribute Tests ==========

TEST_F(XMLElementTest_97, QueryIntAttribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("num", 123);
    int val = 0;
    XMLError err = elem->QueryIntAttribute("num", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_97, QueryIntAttribute_NotFound_97) {
    XMLElement* elem = CreateElement();
    int val = 0;
    XMLError err = elem->QueryIntAttribute("missing", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_97, QueryIntAttribute_WrongType_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("text", "not_a_number");
    int val = 0;
    XMLError err = elem->QueryIntAttribute("text", &val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_97, QueryUnsignedAttribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("u", (unsigned)500);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedAttribute("u", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 500u);
}

TEST_F(XMLElementTest_97, QueryBoolAttribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("flag", true);
    bool val = false;
    XMLError err = elem->QueryBoolAttribute("flag", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_97, QueryDoubleAttribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("d", 3.14);
    double val = 0.0;
    XMLError err = elem->QueryDoubleAttribute("d", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(XMLElementTest_97, QueryFloatAttribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("f", 2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatAttribute("f", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLElementTest_97, QueryStringAttribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("s", "hello");
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("s", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(val, "hello");
}

TEST_F(XMLElementTest_97, QueryStringAttribute_NotFound_97) {
    XMLElement* elem = CreateElement();
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("missing", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(XMLElementTest_97, QueryInt64Attribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("big", (int64_t)1234567890123LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Attribute("big", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 1234567890123LL);
}

TEST_F(XMLElementTest_97, QueryUnsigned64Attribute_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("ubig", (uint64_t)9876543210ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Attribute("ubig", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 9876543210ULL);
}

// ========== Default Value Attribute Methods ==========

TEST_F(XMLElementTest_97, IntAttribute_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->IntAttribute("missing", 42), 42);
}

TEST_F(XMLElementTest_97, UnsignedAttribute_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->UnsignedAttribute("missing", 99u), 99u);
}

TEST_F(XMLElementTest_97, Int64Attribute_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->Int64Attribute("missing", 999LL), 999LL);
}

TEST_F(XMLElementTest_97, Unsigned64Attribute_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->Unsigned64Attribute("missing", 888ULL), 888ULL);
}

TEST_F(XMLElementTest_97, BoolAttribute_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_97, DoubleAttribute_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 1.23), 1.23);
}

TEST_F(XMLElementTest_97, FloatAttribute_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 4.56f), 4.56f);
}

// ========== SetText / GetText Tests ==========

TEST_F(XMLElementTest_97, SetText_GetText_String_97) {
    XMLElement* elem = CreateElement();
    elem->SetText("Hello World");
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

TEST_F(XMLElementTest_97, SetText_Int_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_97, SetText_Unsigned_97) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)100);
    EXPECT_STREQ(elem->GetText(), "100");
}

TEST_F(XMLElementTest_97, SetText_Int64_97) {
    XMLElement* elem = CreateElement();
    elem->SetText((int64_t)1234567890123LL);
    EXPECT_STREQ(elem->GetText(), "1234567890123");
}

TEST_F(XMLElementTest_97, SetText_Uint64_97) {
    XMLElement* elem = CreateElement();
    elem->SetText((uint64_t)9876543210ULL);
    EXPECT_STREQ(elem->GetText(), "9876543210");
}

TEST_F(XMLElementTest_97, SetText_Bool_True_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_97, SetText_Bool_False_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(false);
    EXPECT_STREQ(elem->GetText(), "false");
}

TEST_F(XMLElementTest_97, GetText_NoTextChild_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_97, SetText_Overwrite_97) {
    XMLElement* elem = CreateElement();
    elem->SetText("first");
    elem->SetText("second");
    EXPECT_STREQ(elem->GetText(), "second");
}

// ========== QueryText Tests ==========

TEST_F(XMLElementTest_97, QueryIntText_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_97, QueryIntText_NoText_97) {
    XMLElement* elem = CreateElement();
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_97, QueryUnsignedText_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)55);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 55u);
}

TEST_F(XMLElementTest_97, QueryInt64Text_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetText((int64_t)9876543210LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 9876543210LL);
}

TEST_F(XMLElementTest_97, QueryUnsigned64Text_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetText((uint64_t)1234567890123ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 1234567890123ULL);
}

TEST_F(XMLElementTest_97, QueryBoolText_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_97, QueryDoubleText_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(2.718);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 2.718);
}

TEST_F(XMLElementTest_97, QueryFloatText_Valid_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(1.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

// ========== Default Text Methods ==========

TEST_F(XMLElementTest_97, IntText_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->IntText(99), 99);
}

TEST_F(XMLElementTest_97, IntText_WithValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetText(10);
    EXPECT_EQ(elem->IntText(99), 10);
}

TEST_F(XMLElementTest_97, UnsignedText_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->UnsignedText(77u), 77u);
}

TEST_F(XMLElementTest_97, Int64Text_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->Int64Text(555LL), 555LL);
}

TEST_F(XMLElementTest_97, Unsigned64Text_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->Unsigned64Text(666ULL), 666ULL);
}

TEST_F(XMLElementTest_97, BoolText_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_97, DoubleText_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.11), 1.11);
}

TEST_F(XMLElementTest_97, FloatText_Default_97) {
    XMLElement* elem = CreateElement();
    EXPECT_FLOAT_EQ(elem->FloatText(2.22f), 2.22f);
}

// ========== InsertNewChildElement Tests ==========

TEST_F(XMLElementTest_97, InsertNewChildElement_Basic_97) {
    XMLElement* elem = CreateElement();
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(child->Parent(), elem);
}

TEST_F(XMLElementTest_97, InsertNewComment_Basic_97) {
    XMLElement* elem = CreateElement();
    XMLComment* comment = elem->InsertNewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_97, InsertNewText_Basic_97) {
    XMLElement* elem = CreateElement();
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
}

TEST_F(XMLElementTest_97, InsertNewDeclaration_Basic_97) {
    XMLElement* elem = CreateElement();
    XMLDeclaration* decl = elem->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_97, InsertNewUnknown_Basic_97) {
    XMLElement* elem = CreateElement();
    XMLUnknown* unknown = elem->InsertNewUnknown("!SOMETHING");
    ASSERT_NE(unknown, nullptr);
}

// ========== Name Tests ==========

TEST_F(XMLElementTest_97, Name_Basic_97) {
    XMLElement* elem = CreateElement("myelem");
    EXPECT_STREQ(elem->Name(), "myelem");
}

TEST_F(XMLElementTest_97, SetName_Basic_97) {
    XMLElement* elem = CreateElement("original");
    elem->SetName("renamed");
    EXPECT_STREQ(elem->Name(), "renamed");
}

// ========== ToElement Tests ==========

TEST_F(XMLElementTest_97, ToElement_ReturnsThis_97) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->ToElement(), elem);
}

// ========== ShallowClone Tests ==========

TEST_F(XMLElementTest_97, ShallowClone_Basic_97) {
    XMLElement* elem = CreateElement("original");
    elem->SetAttribute("key", "value");

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "original");
    EXPECT_STREQ(cloneElem->Attribute("key"), "value");
}

// ========== ShallowEqual Tests ==========

TEST_F(XMLElementTest_97, ShallowEqual_SameAttributes_97) {
    XMLElement* e1 = doc.NewElement("elem");
    XMLElement* e2 = doc.NewElement("elem");
    e1->SetAttribute("a", "1");
    e2->SetAttribute("a", "1");
    EXPECT_TRUE(e1->ShallowEqual(e2));
}

TEST_F(XMLElementTest_97, ShallowEqual_DifferentNames_97) {
    XMLElement* e1 = doc.NewElement("elem1");
    XMLElement* e2 = doc.NewElement("elem2");
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

TEST_F(XMLElementTest_97, ShallowEqual_DifferentAttributes_97) {
    XMLElement* e1 = doc.NewElement("elem");
    XMLElement* e2 = doc.NewElement("elem");
    e1->SetAttribute("a", "1");
    e2->SetAttribute("a", "2");
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

TEST_F(XMLElementTest_97, ShallowEqual_DifferentAttributeCount_97) {
    XMLElement* e1 = doc.NewElement("elem");
    XMLElement* e2 = doc.NewElement("elem");
    e1->SetAttribute("a", "1");
    e1->SetAttribute("b", "2");
    e2->SetAttribute("a", "1");
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

// ========== Parsing roundtrip Tests ==========

TEST_F(XMLElementTest_97, ParseAndRetrieveAttributes_97) {
    const char* xml = "<root attr1=\"hello\" attr2=\"42\" />";
    XMLDocument doc2;
    doc2.Parse(xml);
    XMLElement* root = doc2.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr1"), "hello");
    EXPECT_EQ(root->IntAttribute("attr2"), 42);
}

TEST_F(XMLElementTest_97, ParseNestedElements_97) {
    const char* xml = "<root><child name=\"c1\">text</child></root>";
    XMLDocument doc2;
    doc2.Parse(xml);
    XMLElement* root = doc2.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Attribute("name"), "c1");
    EXPECT_STREQ(child->GetText(), "text");
}

// ========== XMLAttribute value accessors ==========

TEST_F(XMLElementTest_97, AttributeIntValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("num", 7);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 7);
}

TEST_F(XMLElementTest_97, AttributeUnsignedValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("num", (unsigned)77);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 77u);
}

TEST_F(XMLElementTest_97, AttributeInt64Value_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("num", (int64_t)123456789012LL);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 123456789012LL);
}

TEST_F(XMLElementTest_97, AttributeUnsigned64Value_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("num", (uint64_t)987654321098ULL);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 987654321098ULL);
}

TEST_F(XMLElementTest_97, AttributeBoolValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("flag", true);
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

TEST_F(XMLElementTest_97, AttributeDoubleValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("d", 6.28);
    const XMLAttribute* attr = elem->FindAttribute("d");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 6.28);
}

TEST_F(XMLElementTest_97, AttributeFloatValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("f", 1.25f);
    const XMLAttribute* attr = elem->FindAttribute("f");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.25f);
}

// ========== XMLAttribute Query methods ==========

TEST_F(XMLElementTest_97, AttributeQueryIntValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("v", 99);
    const XMLAttribute* attr = elem->FindAttribute("v");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    EXPECT_EQ(attr->QueryIntValue(&val), XML_SUCCESS);
    EXPECT_EQ(val, 99);
}

TEST_F(XMLElementTest_97, AttributeQueryBoolValue_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("b", false);
    const XMLAttribute* attr = elem->FindAttribute("b");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    EXPECT_EQ(attr->QueryBoolValue(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

// ========== Overwriting attribute with different type ==========

TEST_F(XMLElementTest_97, SetAttribute_OverwriteTypeChange_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("val", "text");
    EXPECT_STREQ(elem->Attribute("val"), "text");

    elem->SetAttribute("val", 123);
    EXPECT_EQ(elem->IntAttribute("val"), 123);

    elem->SetAttribute("val", true);
    EXPECT_TRUE(elem->BoolAttribute("val"));
}

// ========== QueryAttribute overloaded versions ==========

TEST_F(XMLElementTest_97, QueryAttribute_Int_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", 50);
    int val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 50);
}

TEST_F(XMLElementTest_97, QueryAttribute_Unsigned_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", (unsigned)60);
    unsigned val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 60u);
}

TEST_F(XMLElementTest_97, QueryAttribute_Bool_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", true);
    bool val = false;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_97, QueryAttribute_Double_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", 9.81);
    double val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 9.81);
}

TEST_F(XMLElementTest_97, QueryAttribute_Float_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", 3.0f);
    float val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 3.0f);
}

TEST_F(XMLElementTest_97, QueryAttribute_String_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", "test");
    const char* val = nullptr;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_STREQ(val, "test");
}

TEST_F(XMLElementTest_97, QueryAttribute_Int64_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", (int64_t)1000000000000LL);
    int64_t val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 1000000000000LL);
}

TEST_F(XMLElementTest_97, QueryAttribute_Uint64_97) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("x", (uint64_t)2000000000000ULL);
    uint64_t val = 0;
    EXPECT_EQ(elem->QueryAttribute("x", &val), XML_SUCCESS);
    EXPECT_EQ(val, 2000000000000ULL);
}
