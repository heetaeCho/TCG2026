#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <string>
#include <cstdint>
#include <climits>
#include <cmath>

using namespace tinyxml2;

class XMLElementSetTextTest_237 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
        // Create a root element for testing
    }
    
    XMLElement* CreateElement(const char* name = "test") {
        XMLElement* elem = doc.NewElement(name);
        doc.InsertEndChild(elem);
        return elem;
    }
};

// =============================================================================
// SetText(int) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextInt_PositiveValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    EXPECT_STREQ("42", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_NegativeValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(-123);
    EXPECT_STREQ("-123", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_Zero_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(0);
    EXPECT_STREQ("0", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_MaxInt_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(INT_MAX);
    int result = 0;
    XMLError err = elem->QueryIntText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(INT_MAX, result);
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_MinInt_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(INT_MIN);
    int result = 0;
    XMLError err = elem->QueryIntText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(INT_MIN, result);
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_QueryBackAsInt_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(12345);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(12345, val);
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_OverwritesPreviousText_237) {
    XMLElement* elem = CreateElement();
    elem->SetText("hello");
    elem->SetText(99);
    EXPECT_STREQ("99", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_IntTextReturnsSameValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(777);
    EXPECT_EQ(777, elem->IntText(0));
}

// =============================================================================
// SetText(unsigned int) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextUnsigned_PositiveValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned int)100);
    EXPECT_STREQ("100", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextUnsigned_Zero_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned int)0);
    EXPECT_STREQ("0", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextUnsigned_MaxUint_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(UINT_MAX);
    unsigned int result = 0;
    XMLError err = elem->QueryUnsignedText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(UINT_MAX, result);
}

TEST_F(XMLElementSetTextTest_237, SetTextUnsigned_QueryBackAsUnsigned_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned int)54321);
    unsigned int val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(54321u, val);
}

// =============================================================================
// SetText(int64_t) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextInt64_PositiveValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((int64_t)1234567890123LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(1234567890123LL, val);
}

TEST_F(XMLElementSetTextTest_237, SetTextInt64_NegativeValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((int64_t)-9876543210LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(-9876543210LL, val);
}

TEST_F(XMLElementSetTextTest_237, SetTextInt64_Zero_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((int64_t)0);
    EXPECT_STREQ("0", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextInt64_MaxValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(INT64_MAX);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(INT64_MAX, val);
}

TEST_F(XMLElementSetTextTest_237, SetTextInt64_MinValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(INT64_MIN);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(INT64_MIN, val);
}

// =============================================================================
// SetText(uint64_t) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextUint64_PositiveValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((uint64_t)9876543210ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(9876543210ULL, val);
}

TEST_F(XMLElementSetTextTest_237, SetTextUint64_Zero_237) {
    XMLElement* elem = CreateElement();
    elem->SetText((uint64_t)0);
    EXPECT_STREQ("0", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextUint64_MaxValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(UINT64_MAX);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(UINT64_MAX, val);
}

// =============================================================================
// SetText(bool) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextBool_True_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementSetTextTest_237, SetTextBool_False_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(false);
    bool val = true;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementSetTextTest_237, SetTextBool_BoolTextReturnsCorrectValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    EXPECT_TRUE(elem->BoolText(false));
}

// =============================================================================
// SetText(float) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextFloat_PositiveValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(3.14f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14f, val, 0.001f);
}

TEST_F(XMLElementSetTextTest_237, SetTextFloat_NegativeValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(-2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(-2.5f, val, 0.001f);
}

TEST_F(XMLElementSetTextTest_237, SetTextFloat_Zero_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(0.0f);
    float val = 1.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(0.0f, val);
}

// =============================================================================
// SetText(double) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextDouble_PositiveValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(3.141592653589793);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.141592653589793, val, 1e-10);
}

TEST_F(XMLElementSetTextTest_237, SetTextDouble_NegativeValue_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(-1.23456789);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(-1.23456789, val, 1e-7);
}

TEST_F(XMLElementSetTextTest_237, SetTextDouble_Zero_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(0.0);
    double val = 1.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(0.0, val);
}

// =============================================================================
// SetText(const char*) tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextString_NormalString_237) {
    XMLElement* elem = CreateElement();
    elem->SetText("Hello World");
    EXPECT_STREQ("Hello World", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, SetTextString_EmptyString_237) {
    XMLElement* elem = CreateElement();
    elem->SetText("");
    // GetText may return nullptr or empty string for empty text
    const char* text = elem->GetText();
    if (text != nullptr) {
        EXPECT_STREQ("", text);
    }
}

TEST_F(XMLElementSetTextTest_237, SetTextString_OverwritesPrevious_237) {
    XMLElement* elem = CreateElement();
    elem->SetText("first");
    EXPECT_STREQ("first", elem->GetText());
    elem->SetText("second");
    EXPECT_STREQ("second", elem->GetText());
}

// =============================================================================
// GetText() tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, GetText_NoText_ReturnsNull_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(nullptr, elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, GetText_AfterSetTextInt_ReturnsString_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(1);
    EXPECT_NE(nullptr, elem->GetText());
    EXPECT_STREQ("1", elem->GetText());
}

// =============================================================================
// Query*Text with no text content
// =============================================================================

TEST_F(XMLElementSetTextTest_237, QueryIntText_NoText_ReturnsError_237) {
    XMLElement* elem = CreateElement();
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementSetTextTest_237, QueryDoubleText_NoText_ReturnsError_237) {
    XMLElement* elem = CreateElement();
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementSetTextTest_237, QueryBoolText_NoText_ReturnsError_237) {
    XMLElement* elem = CreateElement();
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

// =============================================================================
// Default value text methods
// =============================================================================

TEST_F(XMLElementSetTextTest_237, IntText_NoText_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(42, elem->IntText(42));
}

TEST_F(XMLElementSetTextTest_237, UnsignedText_NoText_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(100u, elem->UnsignedText(100u));
}

TEST_F(XMLElementSetTextTest_237, DoubleText_NoText_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_DOUBLE_EQ(9.99, elem->DoubleText(9.99));
}

TEST_F(XMLElementSetTextTest_237, FloatText_NoText_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_FLOAT_EQ(1.5f, elem->FloatText(1.5f));
}

TEST_F(XMLElementSetTextTest_237, BoolText_NoText_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_TRUE(elem->BoolText(true));
    EXPECT_FALSE(elem->BoolText(false));
}

TEST_F(XMLElementSetTextTest_237, Int64Text_NoText_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(123456789012345LL, elem->Int64Text(123456789012345LL));
}

TEST_F(XMLElementSetTextTest_237, Unsigned64Text_NoText_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(999999999999ULL, elem->Unsigned64Text(999999999999ULL));
}

// =============================================================================
// SetText then query as different type
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextInt_QueryAsDouble_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(42.0, val);
}

TEST_F(XMLElementSetTextTest_237, SetTextDouble_QueryAsFloat_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(1.5);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(1.5f, val, 0.001f);
}

// =============================================================================
// Multiple SetText calls - ensure last one wins
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetTextMultipleTimes_LastValueWins_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(10);
    elem->SetText(20);
    elem->SetText(30);
    EXPECT_EQ(30, elem->IntText(0));
}

TEST_F(XMLElementSetTextTest_237, SetTextMixedTypes_LastValueWins_237) {
    XMLElement* elem = CreateElement();
    elem->SetText(42);
    elem->SetText("not a number");
    EXPECT_STREQ("not a number", elem->GetText());
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

// =============================================================================
// Attribute tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, SetAttribute_Int_237) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("count", 5);
    EXPECT_EQ(5, elem->IntAttribute("count", 0));
}

TEST_F(XMLElementSetTextTest_237, SetAttribute_String_237) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("name", "value");
    EXPECT_STREQ("value", elem->Attribute("name"));
}

TEST_F(XMLElementSetTextTest_237, SetAttribute_Bool_237) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementSetTextTest_237, SetAttribute_Double_237) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("pi", 3.14159);
    EXPECT_NEAR(3.14159, elem->DoubleAttribute("pi", 0.0), 1e-5);
}

TEST_F(XMLElementSetTextTest_237, FindAttribute_Exists_237) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("key", "val");
    const XMLAttribute* attr = elem->FindAttribute("key");
    EXPECT_NE(nullptr, attr);
}

TEST_F(XMLElementSetTextTest_237, FindAttribute_NotExists_237) {
    XMLElement* elem = CreateElement();
    const XMLAttribute* attr = elem->FindAttribute("nonexistent");
    EXPECT_EQ(nullptr, attr);
}

TEST_F(XMLElementSetTextTest_237, Attribute_NotExists_ReturnsNull_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(nullptr, elem->Attribute("missing"));
}

TEST_F(XMLElementSetTextTest_237, IntAttribute_NotExists_ReturnsDefault_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(99, elem->IntAttribute("missing", 99));
}

TEST_F(XMLElementSetTextTest_237, DeleteAttribute_237) {
    XMLElement* elem = CreateElement();
    elem->SetAttribute("toDelete", 10);
    EXPECT_NE(nullptr, elem->FindAttribute("toDelete"));
    elem->DeleteAttribute("toDelete");
    EXPECT_EQ(nullptr, elem->FindAttribute("toDelete"));
}

// =============================================================================
// InsertNew* tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, InsertNewChildElement_237) {
    XMLElement* parent = CreateElement("parent");
    XMLElement* child = parent->InsertNewChildElement("child");
    EXPECT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
}

TEST_F(XMLElementSetTextTest_237, InsertNewText_237) {
    XMLElement* elem = CreateElement();
    XMLText* text = elem->InsertNewText("some text");
    EXPECT_NE(nullptr, text);
    EXPECT_STREQ("some text", elem->GetText());
}

TEST_F(XMLElementSetTextTest_237, InsertNewComment_237) {
    XMLElement* elem = CreateElement();
    XMLComment* comment = elem->InsertNewComment("a comment");
    EXPECT_NE(nullptr, comment);
}

// =============================================================================
// Name tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, Name_ReturnsCorrectName_237) {
    XMLElement* elem = CreateElement("myElement");
    EXPECT_STREQ("myElement", elem->Name());
}

TEST_F(XMLElementSetTextTest_237, SetName_ChangesName_237) {
    XMLElement* elem = CreateElement("old");
    elem->SetName("new");
    EXPECT_STREQ("new", elem->Name());
}

// =============================================================================
// ShallowClone and ShallowEqual tests
// =============================================================================

TEST_F(XMLElementSetTextTest_237, ShallowClone_CreatesClone_237) {
    XMLElement* elem = CreateElement("original");
    elem->SetAttribute("a", 1);
    XMLNode* clone = elem->ShallowClone(&doc);
    EXPECT_NE(nullptr, clone);
    XMLElement* cloneElem = clone->ToElement();
    EXPECT_NE(nullptr, cloneElem);
    EXPECT_STREQ("original", cloneElem->Name());
    EXPECT_EQ(1, cloneElem->IntAttribute("a", 0));
}

TEST_F(XMLElementSetTextTest_237, ShallowEqual_SameAttributes_237) {
    XMLDocument doc2;
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("x", 10);
    XMLElement* elem2 = doc2.NewElement("test");
    elem2->SetAttribute("x", 10);
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
    doc.DeleteNode(elem1);
    doc2.DeleteNode(elem2);
}

TEST_F(XMLElementSetTextTest_237, ShallowEqual_DifferentAttributes_237) {
    XMLDocument doc2;
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("x", 10);
    XMLElement* elem2 = doc2.NewElement("test");
    elem2->SetAttribute("x", 20);
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
    doc.DeleteNode(elem1);
    doc2.DeleteNode(elem2);
}

// =============================================================================
// Parse and roundtrip via XMLDocument
// =============================================================================

TEST_F(XMLElementSetTextTest_237, ParseAndQueryIntText_237) {
    const char* xml = "<root><value>12345</value></root>";
    XMLDocument parseDoc;
    EXPECT_EQ(XML_SUCCESS, parseDoc.Parse(xml));
    XMLElement* root = parseDoc.RootElement();
    EXPECT_NE(nullptr, root);
    XMLElement* value = root->FirstChildElement("value");
    EXPECT_NE(nullptr, value);
    int ival = 0;
    EXPECT_EQ(XML_SUCCESS, value->QueryIntText(&ival));
    EXPECT_EQ(12345, ival);
}

TEST_F(XMLElementSetTextTest_237, SetTextInt_RoundtripViaPrint_237) {
    XMLElement* elem = CreateElement("num");
    elem->SetText(42);
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    XMLDocument doc2;
    EXPECT_EQ(XML_SUCCESS, doc2.Parse(printer.CStr()));
    XMLElement* root = doc2.RootElement();
    EXPECT_NE(nullptr, root);
    EXPECT_EQ(42, root->IntText(0));
}

// =============================================================================
// Query methods on non-numeric text
// =============================================================================

TEST_F(XMLElementSetTextTest_237, QueryIntText_NonNumericText_ReturnsError_237) {
    XMLElement* elem = CreateElement();
    elem->SetText("abc");
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementSetTextTest_237, QueryFloatText_NonNumericText_ReturnsError_237) {
    XMLElement* elem = CreateElement();
    elem->SetText("not a float");
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

// =============================================================================
// ToElement
// =============================================================================

TEST_F(XMLElementSetTextTest_237, ToElement_ReturnsNonNull_237) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(elem, elem->ToElement());
}
