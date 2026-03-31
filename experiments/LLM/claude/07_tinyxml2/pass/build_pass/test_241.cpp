#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_241 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
        // Reset bool serialization to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

// ==================== SetText Tests ====================

TEST_F(XMLElementTest_241, SetTextBoolTrue_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "true");
}

TEST_F(XMLElementTest_241, SetTextBoolFalse_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(false);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "false");
}

TEST_F(XMLElementTest_241, SetTextBoolCustomSerialization_241) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "yes");
    
    elem->SetText(false);
    text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "no");
    
    // Reset
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLElementTest_241, SetTextInt_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");
}

TEST_F(XMLElementTest_241, SetTextIntNegative_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(-123);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "-123");
}

TEST_F(XMLElementTest_241, SetTextIntZero_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(0);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "0");
}

TEST_F(XMLElementTest_241, SetTextUnsigned_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((unsigned)4294967295u);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "4294967295");
}

TEST_F(XMLElementTest_241, SetTextInt64_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((int64_t)9223372036854775807LL);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "9223372036854775807");
}

TEST_F(XMLElementTest_241, SetTextUint64_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((uint64_t)18446744073709551615ULL);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "18446744073709551615");
}

TEST_F(XMLElementTest_241, SetTextFloat_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14f);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    float val;
    EXPECT_TRUE(XMLUtil::ToFloat(text, &val));
    EXPECT_FLOAT_EQ(val, 3.14f);
}

TEST_F(XMLElementTest_241, SetTextDouble_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14159265358979);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    double val;
    EXPECT_TRUE(XMLUtil::ToDouble(text, &val));
    EXPECT_DOUBLE_EQ(val, 3.14159265358979);
}

TEST_F(XMLElementTest_241, SetTextString_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("hello world");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello world");
}

TEST_F(XMLElementTest_241, SetTextStringEmpty_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("");
    // Setting empty text
    const char* text = elem->GetText();
    // May return nullptr or empty string depending on implementation
    if (text != nullptr) {
        EXPECT_STREQ(text, "");
    }
}

TEST_F(XMLElementTest_241, SetTextOverwritesPreviousText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("first");
    elem->SetText("second");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "second");
}

TEST_F(XMLElementTest_241, SetTextBoolOverwritesPreviousText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("original");
    elem->SetText(true);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "true");
}

// ==================== GetText Tests ====================

TEST_F(XMLElementTest_241, GetTextReturnsNullWhenNoText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    const char* text = elem->GetText();
    EXPECT_EQ(text, nullptr);
}

TEST_F(XMLElementTest_241, GetTextFromParsedXML_241) {
    const char* xml = "<root>Hello</root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello");
}

// ==================== QueryText Tests ====================

TEST_F(XMLElementTest_241, QueryBoolTextTrue_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_241, QueryBoolTextFalse_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(false);
    bool val = true;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_241, QueryIntText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_241, QueryUnsignedText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((unsigned)100);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_241, QueryInt64Text_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((int64_t)123456789012345LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123456789012345LL);
}

TEST_F(XMLElementTest_241, QueryUnsigned64Text_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((uint64_t)123456789012345ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123456789012345ULL);
}

TEST_F(XMLElementTest_241, QueryFloatText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLElementTest_241, QueryDoubleText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(2.5);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

TEST_F(XMLElementTest_241, QueryIntTextNoText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_241, QueryBoolTextNoText_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== Default Text Value Tests ====================

TEST_F(XMLElementTest_241, IntTextDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->IntText(99), 99);
}

TEST_F(XMLElementTest_241, IntTextWithValue_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42);
    EXPECT_EQ(elem->IntText(99), 42);
}

TEST_F(XMLElementTest_241, UnsignedTextDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->UnsignedText(99u), 99u);
}

TEST_F(XMLElementTest_241, BoolTextDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_TRUE(elem->BoolText(true));
    EXPECT_FALSE(elem->BoolText(false));
}

TEST_F(XMLElementTest_241, BoolTextWithValue_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_241, DoubleTextDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.5), 1.5);
}

TEST_F(XMLElementTest_241, FloatTextDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_FLOAT_EQ(elem->FloatText(1.5f), 1.5f);
}

TEST_F(XMLElementTest_241, Int64TextDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->Int64Text(999LL), 999LL);
}

TEST_F(XMLElementTest_241, Unsigned64TextDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->Unsigned64Text(999ULL), 999ULL);
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_241, SetAndGetAttribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("key", "value");
    const char* val = elem->Attribute("key");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "value");
}

TEST_F(XMLElementTest_241, AttributeNotFound_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    const char* val = elem->Attribute("nonexistent");
    EXPECT_EQ(val, nullptr);
}

TEST_F(XMLElementTest_241, SetAttributeInt_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(elem->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_241, SetAttributeBool_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_241, SetAttributeDouble_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 3.14);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("val", 0.0), 3.14);
}

TEST_F(XMLElementTest_241, SetAttributeFloat_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 3.14f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 3.14f);
}

TEST_F(XMLElementTest_241, IntAttributeDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->IntAttribute("missing", 77), 77);
}

TEST_F(XMLElementTest_241, BoolAttributeDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_241, UnsignedAttributeDefault_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->UnsignedAttribute("missing", 55u), 55u);
}

TEST_F(XMLElementTest_241, Int64Attribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("big", (int64_t)9223372036854775807LL);
    EXPECT_EQ(elem->Int64Attribute("big", 0), 9223372036854775807LL);
}

TEST_F(XMLElementTest_241, Unsigned64Attribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("big", (uint64_t)18446744073709551615ULL);
    EXPECT_EQ(elem->Unsigned64Attribute("big", 0), 18446744073709551615ULL);
}

TEST_F(XMLElementTest_241, DeleteAttribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("key", "value");
    ASSERT_NE(elem->Attribute("key"), nullptr);
    elem->DeleteAttribute("key");
    EXPECT_EQ(elem->Attribute("key"), nullptr);
}

TEST_F(XMLElementTest_241, DeleteNonexistentAttribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    // Should not crash
    elem->DeleteAttribute("nonexistent");
}

TEST_F(XMLElementTest_241, FindAttribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("key", "value");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_241, FindAttributeNotFound_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    const XMLAttribute* attr = elem->FindAttribute("missing");
    EXPECT_EQ(attr, nullptr);
}

TEST_F(XMLElementTest_241, FirstAttributeEmpty_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

TEST_F(XMLElementTest_241, FirstAttributeExists_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", "1");
    EXPECT_NE(elem->FirstAttribute(), nullptr);
}

// ==================== Query Attribute Tests ====================

TEST_F(XMLElementTest_241, QueryIntAttribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("num", 42);
    int val = 0;
    EXPECT_EQ(elem->QueryIntAttribute("num", &val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_241, QueryIntAttributeMissing_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int val = 0;
    EXPECT_NE(elem->QueryIntAttribute("missing", &val), XML_SUCCESS);
}

TEST_F(XMLElementTest_241, QueryBoolAttribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("flag", true);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolAttribute("flag", &val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_241, QueryStringAttribute_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("name", "hello");
    const char* val = nullptr;
    EXPECT_EQ(elem->QueryStringAttribute("name", &val), XML_SUCCESS);
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "hello");
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_241, ElementName_241) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertFirstChild(elem);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_241, SetElementName_241) {
    XMLElement* elem = doc.NewElement("old");
    doc.InsertFirstChild(elem);
    elem->SetName("new");
    EXPECT_STREQ(elem->Name(), "new");
}

// ==================== InsertNew Tests ====================

TEST_F(XMLElementTest_241, InsertNewChildElement_241) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

TEST_F(XMLElementTest_241, InsertNewComment_241) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLComment* comment = root->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_241, InsertNewText_241) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLText* text = root->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(root->GetText(), "some text");
}

TEST_F(XMLElementTest_241, InsertNewDeclaration_241) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_241, InsertNewUnknown_241) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLUnknown* unk = root->InsertNewUnknown("something");
    ASSERT_NE(unk, nullptr);
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST_F(XMLElementTest_241, ShallowClone_241) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", "1");
    elem->SetText("hello");
    
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "original");
    EXPECT_STREQ(cloneElem->Attribute("a"), "1");
    // ShallowClone doesn't clone children, so no text
    EXPECT_EQ(cloneElem->GetText(), nullptr);
}

TEST_F(XMLElementTest_241, ShallowEqual_241) {
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("a", "1");
    XMLElement* elem2 = doc.NewElement("test");
    elem2->SetAttribute("a", "1");
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_241, ShallowEqualDifferentName_241) {
    XMLElement* elem1 = doc.NewElement("test1");
    XMLElement* elem2 = doc.NewElement("test2");
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_241, ShallowEqualDifferentAttributes_241) {
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("a", "1");
    XMLElement* elem2 = doc.NewElement("test");
    elem2->SetAttribute("a", "2");
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_241, ToElement_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== XMLUtil Tests ====================

TEST_F(XMLElementTest_241, XMLUtilToStrBoolTrue_241) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLElementTest_241, XMLUtilToStrBoolFalse_241) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLElementTest_241, XMLUtilToStrInt_241) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLElementTest_241, XMLUtilToStrIntNegative_241) {
    char buf[200];
    XMLUtil::ToStr(-7, buf, 200);
    EXPECT_STREQ(buf, "-7");
}

TEST_F(XMLElementTest_241, XMLUtilToStrDouble_241) {
    char buf[200];
    XMLUtil::ToStr(3.14, buf, 200);
    double val;
    EXPECT_TRUE(XMLUtil::ToDouble(buf, &val));
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(XMLElementTest_241, XMLUtilToBool_241) {
    bool val;
    EXPECT_TRUE(XMLUtil::ToBool("true", &val));
    EXPECT_TRUE(val);
    EXPECT_TRUE(XMLUtil::ToBool("false", &val));
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_241, XMLUtilToBoolInvalid_241) {
    bool val;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &val));
}

TEST_F(XMLElementTest_241, XMLUtilToInt_241) {
    int val;
    EXPECT_TRUE(XMLUtil::ToInt("123", &val));
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_241, XMLUtilToIntInvalid_241) {
    int val;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &val));
}

TEST_F(XMLElementTest_241, XMLUtilToFloat_241) {
    float val;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &val));
    EXPECT_FLOAT_EQ(val, 3.14f);
}

TEST_F(XMLElementTest_241, XMLUtilToDouble_241) {
    double val;
    EXPECT_TRUE(XMLUtil::ToDouble("2.718281828", &val));
    EXPECT_NEAR(val, 2.718281828, 1e-9);
}

TEST_F(XMLElementTest_241, XMLUtilIsWhiteSpace_241) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLElementTest_241, XMLUtilStringEqual_241) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helloworld", 5));
}

TEST_F(XMLElementTest_241, XMLUtilToUnsigned_241) {
    unsigned val;
    EXPECT_TRUE(XMLUtil::ToUnsigned("12345", &val));
    EXPECT_EQ(val, 12345u);
}

TEST_F(XMLElementTest_241, XMLUtilToInt64_241) {
    int64_t val;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &val));
    EXPECT_EQ(val, 9223372036854775807LL);
}

TEST_F(XMLElementTest_241, XMLUtilToUnsigned64_241) {
    uint64_t val;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &val));
    EXPECT_EQ(val, 18446744073709551615ULL);
}

// ==================== Parsing Tests ====================

TEST_F(XMLElementTest_241, ParseBoolText_241) {
    const char* xml = "<root>true</root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    bool val = false;
    EXPECT_EQ(root->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_241, ParseIntText_241) {
    const char* xml = "<root>42</root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int val = 0;
    EXPECT_EQ(root->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_241, ParseWithAttributes_241) {
    const char* xml = "<root attr1=\"hello\" attr2=\"42\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr1"), "hello");
    EXPECT_EQ(root->IntAttribute("attr2", 0), 42);
}

TEST_F(XMLElementTest_241, ParseNestedElements_241) {
    const char* xml = "<root><child>text</child></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->GetText(), "text");
}

// ==================== SetBoolSerialization Tests ====================

TEST_F(XMLElementTest_241, SetBoolSerializationCustom_241) {
    XMLUtil::SetBoolSerialization("1", "0");
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "1");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "0");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLElementTest_241, SetBoolSerializationResetToDefault_241) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

// ==================== ReadBOM Test ====================

TEST_F(XMLElementTest_241, ReadBOMNoBOM_241) {
    bool hasBOM = true;
    const char* input = "<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLElementTest_241, ReadBOMWithBOM_241) {
    bool hasBOM = false;
    // UTF-8 BOM: EF BB BF
    const char input[] = "\xEF\xBB\xBF<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, input + 3);
}

// ==================== Attribute with value match ====================

TEST_F(XMLElementTest_241, AttributeWithValueMatch_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("key", "value");
    const char* val = elem->Attribute("key", "value");
    EXPECT_STREQ(val, "value");
}

TEST_F(XMLElementTest_241, AttributeWithValueMismatch_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("key", "value");
    const char* val = elem->Attribute("key", "other");
    EXPECT_EQ(val, nullptr);
}

// ==================== Multiple SetText overloads roundtrip ====================

TEST_F(XMLElementTest_241, SetTextBoolRoundtrip_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
    
    elem->SetText(false);
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_241, SetTextIntRoundtrip_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(INT_MAX);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, INT_MAX);
}

TEST_F(XMLElementTest_241, SetTextIntMinRoundtrip_241) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(INT_MIN);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, INT_MIN);
}
