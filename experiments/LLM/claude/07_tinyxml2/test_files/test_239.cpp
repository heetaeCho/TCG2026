#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_239 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElement(const char* name = "test") {
        XMLElement* elem = doc.NewElement(name);
        doc.InsertFirstChild(elem);
        return elem;
    }
};

// ===================== SetText Tests =====================

TEST_F(XMLElementTest_239, SetTextInt64Positive_239) {
    XMLElement* elem = CreateElement();
    int64_t val = 1234567890123LL;
    elem->SetText(val);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "1234567890123");
}

TEST_F(XMLElementTest_239, SetTextInt64Negative_239) {
    XMLElement* elem = CreateElement();
    int64_t val = -9876543210LL;
    elem->SetText(val);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "-9876543210");
}

TEST_F(XMLElementTest_239, SetTextInt64Zero_239) {
    XMLElement* elem = CreateElement();
    int64_t val = 0;
    elem->SetText(val);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "0");
}

TEST_F(XMLElementTest_239, SetTextInt64Max_239) {
    XMLElement* elem = CreateElement();
    int64_t val = INT64_MAX;
    elem->SetText(val);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "9223372036854775807");
}

TEST_F(XMLElementTest_239, SetTextInt64Min_239) {
    XMLElement* elem = CreateElement();
    int64_t val = INT64_MIN;
    elem->SetText(val);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "-9223372036854775808");
}

TEST_F(XMLElementTest_239, SetTextInt64QueryRoundTrip_239) {
    XMLElement* elem = CreateElement();
    int64_t val = 42424242424242LL;
    elem->SetText(val);
    int64_t result = 0;
    XMLError err = elem->QueryInt64Text(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, val);
}

TEST_F(XMLElementTest_239, SetTextInt64Int64Text_239) {
    XMLElement* elem = CreateElement();
    int64_t val = -11111111111LL;
    elem->SetText(val);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, val);
}

// ===================== SetText other overloads =====================

TEST_F(XMLElementTest_239, SetTextInt_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");
}

TEST_F(XMLElementTest_239, SetTextUnsigned_239) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned int)4294967295U);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "4294967295");
}

TEST_F(XMLElementTest_239, SetTextUint64_239) {
    XMLElement* elem = CreateElement();
    uint64_t val = 18446744073709551615ULL;
    elem->SetText(val);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "18446744073709551615");
}

TEST_F(XMLElementTest_239, SetTextBoolTrue_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "true");
}

TEST_F(XMLElementTest_239, SetTextBoolFalse_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(false);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "false");
}

TEST_F(XMLElementTest_239, SetTextFloat_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(3.14f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 3.14f, 0.01f);
}

TEST_F(XMLElementTest_239, SetTextDouble_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(2.718281828);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 2.718281828, 0.0001);
}

TEST_F(XMLElementTest_239, SetTextString_239) {
    XMLElement* elem = CreateElement();
    elem->SetText("hello world");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello world");
}

// ===================== GetText Tests =====================

TEST_F(XMLElementTest_239, GetTextNullWhenNoChild_239) {
    XMLElement* elem = CreateElement();
    const char* text = elem->GetText();
    EXPECT_EQ(text, nullptr);
}

TEST_F(XMLElementTest_239, GetTextAfterSetText_239) {
    XMLElement* elem = CreateElement();
    elem->SetText("test text");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "test text");
}

// ===================== Attribute Tests =====================

TEST_F(XMLElementTest_239, SetAndGetIntAttribute_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("myattr", 100);
    int val = elem->IntAttribute("myattr", 0);
    EXPECT_EQ(val, 100);
}

TEST_F(XMLElementTest_239, SetAndGetUnsignedAttribute_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("myattr", (unsigned)300);
    unsigned val = elem->UnsignedAttribute("myattr", 0);
    EXPECT_EQ(val, 300u);
}

TEST_F(XMLElementTest_239, SetAndGetInt64Attribute_239) {
    XMLElement* elem = CreateElement();
    int64_t expected = 9876543210LL;
    elem->SetAttribute("myattr", expected);
    int64_t val = elem->Int64Attribute("myattr", 0);
    EXPECT_EQ(val, expected);
}

TEST_F(XMLElementTest_239, SetAndGetUnsigned64Attribute_239) {
    XMLElement* elem = CreateElement();
    uint64_t expected = 18446744073709551000ULL;
    elem->SetAttribute("myattr", expected);
    uint64_t val = elem->Unsigned64Attribute("myattr", 0);
    EXPECT_EQ(val, expected);
}

TEST_F(XMLElementTest_239, SetAndGetBoolAttribute_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("flag", true);
    bool val = elem->BoolAttribute("flag", false);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_239, SetAndGetDoubleAttribute_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("dval", 1.23456);
    double val = elem->DoubleAttribute("dval", 0.0);
    EXPECT_NEAR(val, 1.23456, 0.001);
}

TEST_F(XMLElementTest_239, SetAndGetFloatAttribute_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("fval", 2.5f);
    float val = elem->FloatAttribute("fval", 0.0f);
    EXPECT_NEAR(val, 2.5f, 0.01f);
}

TEST_F(XMLElementTest_239, SetAndGetStringAttribute_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("name", "hello");
    const char* val = elem->Attribute("name");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "hello");
}

TEST_F(XMLElementTest_239, AttributeDefaultWhenMissing_239) {
    XMLElement* elem = CreateElement();
    int val = elem->IntAttribute("nonexist", 999);
    EXPECT_EQ(val, 999);
}

TEST_F(XMLElementTest_239, Int64AttributeDefaultWhenMissing_239) {
    XMLElement* elem = CreateElement();
    int64_t val = elem->Int64Attribute("nonexist", -1LL);
    EXPECT_EQ(val, -1LL);
}

TEST_F(XMLElementTest_239, BoolAttributeDefaultWhenMissing_239) {
    XMLElement* elem = CreateElement();
    bool val = elem->BoolAttribute("nonexist", true);
    EXPECT_TRUE(val);
}

// ===================== FindAttribute Tests =====================

TEST_F(XMLElementTest_239, FindAttributeExists_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "val");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_239, FindAttributeNotExists_239) {
    XMLElement* elem = CreateElement();
    const XMLAttribute* attr = elem->FindAttribute("nokey");
    EXPECT_EQ(attr, nullptr);
}

// ===================== DeleteAttribute Tests =====================

TEST_F(XMLElementTest_239, DeleteAttributeRemovesIt_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("toremove", "value");
    ASSERT_NE(elem->FindAttribute("toremove"), nullptr);
    elem->DeleteAttribute("toremove");
    EXPECT_EQ(elem->FindAttribute("toremove"), nullptr);
}

TEST_F(XMLElementTest_239, DeleteNonexistentAttribute_239) {
    XMLElement* elem = CreateElement();
    // Should not crash
    elem->DeleteAttribute("nothing");
    EXPECT_EQ(elem->FindAttribute("nothing"), nullptr);
}

// ===================== Query*Text Tests =====================

TEST_F(XMLElementTest_239, QueryIntTextValid_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(123);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_239, QueryIntTextNoChild_239) {
    XMLElement* elem = CreateElement();
    int val = 0;
    EXPECT_NE(elem->QueryIntText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_239, QueryUnsignedTextValid_239) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)456);
    unsigned val = 0;
    EXPECT_EQ(elem->QueryUnsignedText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 456u);
}

TEST_F(XMLElementTest_239, QueryInt64TextValid_239) {
    XMLElement* elem = CreateElement();
    elem->SetText((int64_t)9999999999LL);
    int64_t val = 0;
    EXPECT_EQ(elem->QueryInt64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 9999999999LL);
}

TEST_F(XMLElementTest_239, QueryUnsigned64TextValid_239) {
    XMLElement* elem = CreateElement();
    elem->SetText((uint64_t)18446744073709551000ULL);
    uint64_t val = 0;
    EXPECT_EQ(elem->QueryUnsigned64Text(&val), XML_SUCCESS);
    EXPECT_EQ(val, 18446744073709551000ULL);
}

TEST_F(XMLElementTest_239, QueryBoolTextValid_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_239, QueryDoubleTextValid_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(3.14159);
    double val = 0.0;
    EXPECT_EQ(elem->QueryDoubleText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 3.14159, 0.001);
}

TEST_F(XMLElementTest_239, QueryFloatTextValid_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(1.5f);
    float val = 0.0f;
    EXPECT_EQ(elem->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_NEAR(val, 1.5f, 0.01f);
}

// ===================== *Text default value Tests =====================

TEST_F(XMLElementTest_239, IntTextDefault_239) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->IntText(77), 77);
}

TEST_F(XMLElementTest_239, UnsignedTextDefault_239) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->UnsignedText(88u), 88u);
}

TEST_F(XMLElementTest_239, Int64TextDefault_239) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->Int64Text(99LL), 99LL);
}

TEST_F(XMLElementTest_239, Unsigned64TextDefault_239) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->Unsigned64Text(100ULL), 100ULL);
}

TEST_F(XMLElementTest_239, BoolTextDefault_239) {
    XMLElement* elem = CreateElement();
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_239, DoubleTextDefault_239) {
    XMLElement* elem = CreateElement();
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.1), 1.1);
}

TEST_F(XMLElementTest_239, FloatTextDefault_239) {
    XMLElement* elem = CreateElement();
    EXPECT_FLOAT_EQ(elem->FloatText(2.2f), 2.2f);
}

// ===================== InsertNew* Tests =====================

TEST_F(XMLElementTest_239, InsertNewChildElement_239) {
    XMLElement* elem = CreateElement();
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

TEST_F(XMLElementTest_239, InsertNewComment_239) {
    XMLElement* elem = CreateElement();
    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_239, InsertNewText_239) {
    XMLElement* elem = CreateElement();
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
}

TEST_F(XMLElementTest_239, InsertNewDeclaration_239) {
    XMLElement* elem = CreateElement();
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_239, InsertNewUnknown_239) {
    XMLElement* elem = CreateElement();
    XMLUnknown* unk = elem->InsertNewUnknown("unknown");
    ASSERT_NE(unk, nullptr);
}

// ===================== Name Tests =====================

TEST_F(XMLElementTest_239, NameReturnsCorrectName_239) {
    XMLElement* elem = CreateElement("myelem");
    EXPECT_STREQ(elem->Name(), "myelem");
}

TEST_F(XMLElementTest_239, SetNameChangesName_239) {
    XMLElement* elem = CreateElement("old");
    elem->SetName("new");
    EXPECT_STREQ(elem->Name(), "new");
}

// ===================== ShallowClone / ShallowEqual Tests =====================

TEST_F(XMLElementTest_239, ShallowCloneCreatesClone_239) {
    XMLElement* elem = CreateElement("original");
    elem->SetAttribute("a", 1);
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "original");
    EXPECT_EQ(cloneElem->IntAttribute("a", 0), 1);
}

TEST_F(XMLElementTest_239, ShallowEqualSameElement_239) {
    XMLElement* elem1 = doc.NewElement("same");
    elem1->SetAttribute("x", 10);
    XMLElement* elem2 = doc.NewElement("same");
    elem2->SetAttribute("x", 10);
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_239, ShallowEqualDifferentElement_239) {
    XMLElement* elem1 = doc.NewElement("a");
    XMLElement* elem2 = doc.NewElement("b");
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// ===================== QueryAttribute Tests =====================

TEST_F(XMLElementTest_239, QueryIntAttributeSuccess_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("val", 55);
    int result = 0;
    EXPECT_EQ(elem->QueryIntAttribute("val", &result), XML_SUCCESS);
    EXPECT_EQ(result, 55);
}

TEST_F(XMLElementTest_239, QueryIntAttributeNoAttribute_239) {
    XMLElement* elem = CreateElement();
    int result = 0;
    EXPECT_NE(elem->QueryIntAttribute("missing", &result), XML_SUCCESS);
}

TEST_F(XMLElementTest_239, QueryStringAttribute_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("str", "hello");
    const char* result = nullptr;
    EXPECT_EQ(elem->QueryStringAttribute("str", &result), XML_SUCCESS);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

// ===================== Multiple SetText overwrites =====================

TEST_F(XMLElementTest_239, SetTextOverwritesPrevious_239) {
    XMLElement* elem = CreateElement();
    elem->SetText("first");
    elem->SetText("second");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "second");
}

TEST_F(XMLElementTest_239, SetTextIntThenInt64_239) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
    elem->SetText((int64_t)99999999999LL);
    EXPECT_STREQ(elem->GetText(), "99999999999");
}

// ===================== ToElement Tests =====================

TEST_F(XMLElementTest_239, ToElementReturnsSelf_239) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->ToElement(), elem);
}

// ===================== FirstAttribute Tests =====================

TEST_F(XMLElementTest_239, FirstAttributeNull_239) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

TEST_F(XMLElementTest_239, FirstAttributeNotNull_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("first", "val");
    EXPECT_NE(elem->FirstAttribute(), nullptr);
}

// ===================== XMLUtil ToStr/To* Tests =====================

TEST_F(XMLElementTest_239, XMLUtilToStrInt_239) {
    char buf[200];
    XMLUtil::ToStr(42, buf, 200);
    EXPECT_STREQ(buf, "42");
}

TEST_F(XMLElementTest_239, XMLUtilToStrUnsigned_239) {
    char buf[200];
    XMLUtil::ToStr((unsigned)100, buf, 200);
    EXPECT_STREQ(buf, "100");
}

TEST_F(XMLElementTest_239, XMLUtilToStrBoolTrue_239) {
    char buf[200];
    XMLUtil::ToStr(true, buf, 200);
    EXPECT_STREQ(buf, "true");
}

TEST_F(XMLElementTest_239, XMLUtilToStrBoolFalse_239) {
    char buf[200];
    XMLUtil::ToStr(false, buf, 200);
    EXPECT_STREQ(buf, "false");
}

TEST_F(XMLElementTest_239, XMLUtilToStrInt64_239) {
    char buf[200];
    XMLUtil::ToStr((int64_t)1234567890123LL, buf, 200);
    EXPECT_STREQ(buf, "1234567890123");
}

TEST_F(XMLElementTest_239, XMLUtilToStrUint64_239) {
    char buf[200];
    XMLUtil::ToStr((uint64_t)18446744073709551615ULL, buf, 200);
    EXPECT_STREQ(buf, "18446744073709551615");
}

TEST_F(XMLElementTest_239, XMLUtilToIntValid_239) {
    int val = 0;
    EXPECT_TRUE(XMLUtil::ToInt("123", &val));
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_239, XMLUtilToIntInvalid_239) {
    int val = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &val));
}

TEST_F(XMLElementTest_239, XMLUtilToInt64Valid_239) {
    int64_t val = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9999999999999", &val));
    EXPECT_EQ(val, 9999999999999LL);
}

TEST_F(XMLElementTest_239, XMLUtilToInt64Invalid_239) {
    int64_t val = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("notanumber", &val));
}

TEST_F(XMLElementTest_239, XMLUtilToBoolTrue_239) {
    bool val = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_239, XMLUtilToBoolFalse_239) {
    bool val = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &val));
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_239, XMLUtilToBoolInvalid_239) {
    bool val = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &val));
}

TEST_F(XMLElementTest_239, XMLUtilToDoubleValid_239) {
    double val = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14", &val));
    EXPECT_NEAR(val, 3.14, 0.01);
}

TEST_F(XMLElementTest_239, XMLUtilToFloatValid_239) {
    float val = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("2.5", &val));
    EXPECT_NEAR(val, 2.5f, 0.01f);
}

TEST_F(XMLElementTest_239, XMLUtilIsWhiteSpaceTrue_239) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLElementTest_239, XMLUtilIsWhiteSpaceFalse_239) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('1'));
}

TEST_F(XMLElementTest_239, XMLUtilStringEqual_239) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLElementTest_239, XMLUtilStringEqualPartial_239) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "help", 3));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "help", 4));
}

// ===================== Parsing round trip via XMLDocument =====================

TEST_F(XMLElementTest_239, ParseAndQueryInt64Text_239) {
    const char* xml = "<root><val>-555555555555</val></root>";
    XMLDocument doc2;
    doc2.Parse(xml);
    XMLElement* val = doc2.FirstChildElement("root")->FirstChildElement("val");
    ASSERT_NE(val, nullptr);
    int64_t result = 0;
    EXPECT_EQ(val->QueryInt64Text(&result), XML_SUCCESS);
    EXPECT_EQ(result, -555555555555LL);
}

TEST_F(XMLElementTest_239, ParseAndAttributeAccess_239) {
    const char* xml = "<root attr=\"42\"/>";
    XMLDocument doc2;
    doc2.Parse(xml);
    XMLElement* root = doc2.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->IntAttribute("attr", 0), 42);
}

// ===================== Attribute with matching value =====================

TEST_F(XMLElementTest_239, AttributeWithValueMatch_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "expected");
    const char* val = elem->Attribute("key", "expected");
    EXPECT_STREQ(val, "expected");
}

TEST_F(XMLElementTest_239, AttributeWithValueNoMatch_239) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "actual");
    const char* val = elem->Attribute("key", "different");
    EXPECT_EQ(val, nullptr);
}

TEST_F(XMLElementTest_239, AttributeNullWhenMissing_239) {
    XMLElement* elem = CreateElement();
    const char* val = elem->Attribute("nonexistent");
    EXPECT_EQ(val, nullptr);
}
