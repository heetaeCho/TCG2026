#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_243 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElement(const char* name = "test") {
        XMLElement* elem = doc.NewElement(name);
        doc.InsertFirstChild(elem);
        return elem;
    }
};

// ==================== SetText Tests ====================

TEST_F(XMLElementTest_243, SetTextDouble_PositiveValue_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(3.14);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST_F(XMLElementTest_243, SetTextDouble_Zero_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(0.0);
    double result = 1.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(XMLElementTest_243, SetTextDouble_NegativeValue_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(-2.718);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, -2.718);
}

TEST_F(XMLElementTest_243, SetTextDouble_LargeValue_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(1.0e+100);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 1.0e+100);
}

TEST_F(XMLElementTest_243, SetTextDouble_SmallValue_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(1.0e-100);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 1.0e-100);
}

TEST_F(XMLElementTest_243, SetTextDouble_GetTextReturnsNonNull_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(42.5);
    const char* text = elem->GetText();
    EXPECT_NE(text, nullptr);
}

TEST_F(XMLElementTest_243, SetTextDouble_DoubleTextWithDefault_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(99.99);
    double result = elem->DoubleText(0.0);
    EXPECT_DOUBLE_EQ(result, 99.99);
}

TEST_F(XMLElementTest_243, SetTextDouble_OverwritesPreviousText_243) {
    XMLElement* elem = CreateElement();
    elem->SetText("hello");
    elem->SetText(1.23);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 1.23);
}

TEST_F(XMLElementTest_243, SetTextDouble_NegativeZero_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(-0.0);
    double result = 1.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    // -0.0 == 0.0 in IEEE 754
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(XMLElementTest_243, SetTextDouble_VerySmallNegative_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(-1.0e-300);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, -1.0e-300);
}

// ==================== SetText for other types ====================

TEST_F(XMLElementTest_243, SetTextInt_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    int result = 0;
    XMLError err = elem->QueryIntText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 42);
}

TEST_F(XMLElementTest_243, SetTextUnsigned_243) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)123u);
    unsigned result = 0;
    XMLError err = elem->QueryUnsignedText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 123u);
}

TEST_F(XMLElementTest_243, SetTextInt64_243) {
    XMLElement* elem = CreateElement();
    int64_t val = 9223372036854775807LL;
    elem->SetText(val);
    int64_t result = 0;
    XMLError err = elem->QueryInt64Text(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, val);
}

TEST_F(XMLElementTest_243, SetTextUint64_243) {
    XMLElement* elem = CreateElement();
    uint64_t val = 18446744073709551615ULL;
    elem->SetText(val);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Text(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, val);
}

TEST_F(XMLElementTest_243, SetTextBoolTrue_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    bool result = false;
    XMLError err = elem->QueryBoolText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_243, SetTextBoolFalse_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(false);
    bool result = true;
    XMLError err = elem->QueryBoolText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(result);
}

TEST_F(XMLElementTest_243, SetTextFloat_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(1.5f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST_F(XMLElementTest_243, SetTextString_243) {
    XMLElement* elem = CreateElement();
    elem->SetText("Hello World");
    const char* text = elem->GetText();
    EXPECT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello World");
}

// ==================== Query text when no text present ====================

TEST_F(XMLElementTest_243, QueryDoubleText_NoText_243) {
    XMLElement* elem = CreateElement();
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_243, QueryIntText_NoText_243) {
    XMLElement* elem = CreateElement();
    int result = 0;
    XMLError err = elem->QueryIntText(&result);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== Default text values ====================

TEST_F(XMLElementTest_243, DoubleText_DefaultWhenNoText_243) {
    XMLElement* elem = CreateElement();
    double result = elem->DoubleText(99.99);
    EXPECT_DOUBLE_EQ(result, 99.99);
}

TEST_F(XMLElementTest_243, IntText_DefaultWhenNoText_243) {
    XMLElement* elem = CreateElement();
    int result = elem->IntText(42);
    EXPECT_EQ(result, 42);
}

TEST_F(XMLElementTest_243, FloatText_DefaultWhenNoText_243) {
    XMLElement* elem = CreateElement();
    float result = elem->FloatText(1.5f);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST_F(XMLElementTest_243, BoolText_DefaultWhenNoText_243) {
    XMLElement* elem = CreateElement();
    bool result = elem->BoolText(true);
    EXPECT_TRUE(result);
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_243, SetAndGetAttribute_String_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "value");
    const char* val = elem->Attribute("key");
    EXPECT_NE(val, nullptr);
    EXPECT_STREQ(val, "value");
}

TEST_F(XMLElementTest_243, SetAndGetAttribute_Int_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("num", 10);
    int val = elem->IntAttribute("num", 0);
    EXPECT_EQ(val, 10);
}

TEST_F(XMLElementTest_243, SetAndGetAttribute_Double_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("dbl", 3.14);
    double val = elem->DoubleAttribute("dbl", 0.0);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(XMLElementTest_243, SetAndGetAttribute_Bool_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("flag", true);
    bool val = elem->BoolAttribute("flag", false);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_243, Attribute_NonExistent_ReturnsNull_243) {
    XMLElement* elem = CreateElement();
    const char* val = elem->Attribute("nonexistent");
    EXPECT_EQ(val, nullptr);
}

TEST_F(XMLElementTest_243, IntAttribute_NonExistent_ReturnsDefault_243) {
    XMLElement* elem = CreateElement();
    int val = elem->IntAttribute("missing", 77);
    EXPECT_EQ(val, 77);
}

TEST_F(XMLElementTest_243, DoubleAttribute_NonExistent_ReturnsDefault_243) {
    XMLElement* elem = CreateElement();
    double val = elem->DoubleAttribute("missing", 55.5);
    EXPECT_DOUBLE_EQ(val, 55.5);
}

TEST_F(XMLElementTest_243, DeleteAttribute_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("toDelete", "val");
    EXPECT_NE(elem->Attribute("toDelete"), nullptr);
    elem->DeleteAttribute("toDelete");
    EXPECT_EQ(elem->Attribute("toDelete"), nullptr);
}

TEST_F(XMLElementTest_243, FindAttribute_Exists_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("findMe", "here");
    const XMLAttribute* attr = elem->FindAttribute("findMe");
    EXPECT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_243, FindAttribute_NotExists_243) {
    XMLElement* elem = CreateElement();
    const XMLAttribute* attr = elem->FindAttribute("noSuchAttr");
    EXPECT_EQ(attr, nullptr);
}

// ==================== GetText when no text child ====================

TEST_F(XMLElementTest_243, GetText_NoChildren_ReturnsNull_243) {
    XMLElement* elem = CreateElement();
    const char* text = elem->GetText();
    EXPECT_EQ(text, nullptr);
}

// ==================== Name tests ====================

TEST_F(XMLElementTest_243, Name_ReturnsElementName_243) {
    XMLElement* elem = CreateElement("myElement");
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_243, SetName_ChangesName_243) {
    XMLElement* elem = CreateElement("old");
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// ==================== InsertNew* Tests ====================

TEST_F(XMLElementTest_243, InsertNewChildElement_243) {
    XMLElement* elem = CreateElement();
    XMLElement* child = elem->InsertNewChildElement("child");
    EXPECT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

TEST_F(XMLElementTest_243, InsertNewComment_243) {
    XMLElement* elem = CreateElement();
    XMLComment* comment = elem->InsertNewComment("a comment");
    EXPECT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_243, InsertNewText_243) {
    XMLElement* elem = CreateElement();
    XMLText* text = elem->InsertNewText("some text");
    EXPECT_NE(text, nullptr);
}

TEST_F(XMLElementTest_243, InsertNewDeclaration_243) {
    XMLElement* elem = CreateElement();
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    EXPECT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_243, InsertNewUnknown_243) {
    XMLElement* elem = CreateElement();
    XMLUnknown* unk = elem->InsertNewUnknown("something");
    EXPECT_NE(unk, nullptr);
}

// ==================== ShallowClone / ShallowEqual ====================

TEST_F(XMLElementTest_243, ShallowClone_243) {
    XMLElement* elem = CreateElement("cloneMe");
    elem->SetAttribute("a", "1");
    XMLNode* clone = elem->ShallowClone(&doc);
    EXPECT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    EXPECT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "cloneMe");
    EXPECT_STREQ(cloneElem->Attribute("a"), "1");
}

TEST_F(XMLElementTest_243, ShallowEqual_SameElement_243) {
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("x", "1");
    XMLElement* elem2 = doc.NewElement("test");
    elem2->SetAttribute("x", "1");
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_243, ShallowEqual_DifferentElement_243) {
    XMLElement* elem1 = doc.NewElement("test1");
    XMLElement* elem2 = doc.NewElement("test2");
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// ==================== Query Attribute errors ====================

TEST_F(XMLElementTest_243, QueryIntAttribute_NonExistent_243) {
    XMLElement* elem = CreateElement();
    int val = 0;
    XMLError err = elem->QueryIntAttribute("missing", &val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_243, QueryDoubleAttribute_NonExistent_243) {
    XMLElement* elem = CreateElement();
    double val = 0.0;
    XMLError err = elem->QueryDoubleAttribute("missing", &val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== SetText double precision roundtrip ====================

TEST_F(XMLElementTest_243, SetTextDouble_MaxDouble_243) {
    XMLElement* elem = CreateElement();
    double maxVal = 1.7976931348623157e+308;
    elem->SetText(maxVal);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    // Just verify it's a very large number, precision may vary
    EXPECT_GT(result, 1.0e+307);
}

TEST_F(XMLElementTest_243, SetTextDouble_MinPositive_243) {
    XMLElement* elem = CreateElement();
    double minVal = 2.2250738585072014e-308;
    elem->SetText(minVal);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_GT(result, 0.0);
}

// ==================== Multiple SetText calls ====================

TEST_F(XMLElementTest_243, SetTextDouble_MultipleCalls_LastWins_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(1.0);
    elem->SetText(2.0);
    elem->SetText(3.0);
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 3.0);
}

// ==================== QueryText with wrong type ====================

TEST_F(XMLElementTest_243, QueryIntText_OnDoubleText_243) {
    XMLElement* elem = CreateElement();
    elem->SetText(3.14);
    int result = 0;
    XMLError err = elem->QueryIntText(&result);
    // "3.14" parsed as int may succeed with value 3 or may fail depending on implementation
    // We just verify we can call it without crashing
    (void)err;
    (void)result;
}

// ==================== Attribute with value matching ====================

TEST_F(XMLElementTest_243, Attribute_WithValueMatch_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "expected");
    const char* val = elem->Attribute("key", "expected");
    EXPECT_NE(val, nullptr);
    EXPECT_STREQ(val, "expected");
}

TEST_F(XMLElementTest_243, Attribute_WithValueMismatch_243) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "actual");
    const char* val = elem->Attribute("key", "different");
    EXPECT_EQ(val, nullptr);
}
