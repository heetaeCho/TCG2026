#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_229 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// =====================================================
// UnsignedAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, UnsignedAttribute_ReturnsValue_WhenAttributeExists_229) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedAttribute("val", 0);
    EXPECT_EQ(result, 42u);
}

TEST_F(XMLElementTest_229, UnsignedAttribute_ReturnsDefault_WhenAttributeDoesNotExist_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedAttribute("nonexistent", 99);
    EXPECT_EQ(result, 99u);
}

TEST_F(XMLElementTest_229, UnsignedAttribute_ReturnsZero_WhenAttributeIsZero_229) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedAttribute("val", 999);
    EXPECT_EQ(result, 0u);
}

TEST_F(XMLElementTest_229, UnsignedAttribute_ReturnsLargeValue_229) {
    doc.Parse("<root val=\"4294967295\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedAttribute("val", 0);
    EXPECT_EQ(result, 4294967295u);
}

TEST_F(XMLElementTest_229, UnsignedAttribute_ReturnsDefault_WhenAttributeIsNonNumeric_229) {
    doc.Parse("<root val=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedAttribute("val", 55);
    // Non-numeric string may fail to parse, should return default
    EXPECT_EQ(result, 55u);
}

TEST_F(XMLElementTest_229, UnsignedAttribute_DefaultZero_WhenAttributeMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedAttribute("missing", 0);
    EXPECT_EQ(result, 0u);
}

// =====================================================
// IntAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, IntAttribute_ReturnsValue_WhenAttributeExists_229) {
    doc.Parse("<root val=\"-10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int result = elem->IntAttribute("val", 0);
    EXPECT_EQ(result, -10);
}

TEST_F(XMLElementTest_229, IntAttribute_ReturnsDefault_WhenAttributeMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int result = elem->IntAttribute("missing", -1);
    EXPECT_EQ(result, -1);
}

TEST_F(XMLElementTest_229, IntAttribute_ReturnsZero_229) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int result = elem->IntAttribute("val", 42);
    EXPECT_EQ(result, 0);
}

// =====================================================
// Int64Attribute Tests
// =====================================================

TEST_F(XMLElementTest_229, Int64Attribute_ReturnsValue_229) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_229, Int64Attribute_ReturnsDefault_WhenMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Attribute("missing", -100);
    EXPECT_EQ(result, -100);
}

// =====================================================
// Unsigned64Attribute Tests
// =====================================================

TEST_F(XMLElementTest_229, Unsigned64Attribute_ReturnsValue_229) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t result = elem->Unsigned64Attribute("val", 0);
    EXPECT_EQ(result, UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_229, Unsigned64Attribute_ReturnsDefault_WhenMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t result = elem->Unsigned64Attribute("missing", 77);
    EXPECT_EQ(result, 77u);
}

// =====================================================
// BoolAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, BoolAttribute_ReturnsTrue_229) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool result = elem->BoolAttribute("val", false);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_229, BoolAttribute_ReturnsFalse_229) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool result = elem->BoolAttribute("val", true);
    EXPECT_FALSE(result);
}

TEST_F(XMLElementTest_229, BoolAttribute_ReturnsDefault_WhenMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool result = elem->BoolAttribute("missing", true);
    EXPECT_TRUE(result);
}

// =====================================================
// DoubleAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, DoubleAttribute_ReturnsValue_229) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(result, 3.14159);
}

TEST_F(XMLElementTest_229, DoubleAttribute_ReturnsDefault_WhenMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("missing", 2.718);
    EXPECT_DOUBLE_EQ(result, 2.718);
}

// =====================================================
// FloatAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, FloatAttribute_ReturnsValue_229) {
    doc.Parse("<root val=\"1.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatAttribute("val", 0.0f);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST_F(XMLElementTest_229, FloatAttribute_ReturnsDefault_WhenMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatAttribute("missing", 9.9f);
    EXPECT_FLOAT_EQ(result, 9.9f);
}

// =====================================================
// Attribute (string) Tests
// =====================================================

TEST_F(XMLElementTest_229, Attribute_ReturnsValue_WhenExists_229) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("name");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(XMLElementTest_229, Attribute_ReturnsNull_WhenMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("missing");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementTest_229, Attribute_WithValueMatch_ReturnsValue_229) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("name", "hello");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(XMLElementTest_229, Attribute_WithValueMismatch_ReturnsNull_229) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("name", "world");
    EXPECT_EQ(result, nullptr);
}

// =====================================================
// SetAttribute / FindAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, SetAttribute_String_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("key", "value");
    const char* result = elem->Attribute("key");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "value");
}

TEST_F(XMLElementTest_229, SetAttribute_Int_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", 123);
    int result = elem->IntAttribute("num", 0);
    EXPECT_EQ(result, 123);
}

TEST_F(XMLElementTest_229, SetAttribute_Unsigned_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", 456u);
    unsigned result = elem->UnsignedAttribute("num", 0);
    EXPECT_EQ(result, 456u);
}

TEST_F(XMLElementTest_229, SetAttribute_Bool_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    bool result = elem->BoolAttribute("flag", false);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_229, SetAttribute_Double_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 3.14);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST_F(XMLElementTest_229, SetAttribute_Float_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 2.5f);
    float result = elem->FloatAttribute("val", 0.0f);
    EXPECT_FLOAT_EQ(result, 2.5f);
}

TEST_F(XMLElementTest_229, FindAttribute_ReturnsNonNull_WhenExists_229) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_229, FindAttribute_ReturnsNull_WhenMissing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("nonexistent");
    EXPECT_EQ(attr, nullptr);
}

// =====================================================
// DeleteAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, DeleteAttribute_RemovesAttribute_229) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("a");
    const char* result = elem->Attribute("a");
    EXPECT_EQ(result, nullptr);
    // b should still exist
    const char* resultB = elem->Attribute("b");
    ASSERT_NE(resultB, nullptr);
    EXPECT_STREQ(resultB, "2");
}

TEST_F(XMLElementTest_229, DeleteAttribute_NonExistent_NoEffect_229) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("nonexistent");
    const char* result = elem->Attribute("a");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "1");
}

// =====================================================
// Name Tests
// =====================================================

TEST_F(XMLElementTest_229, Name_ReturnsElementName_229) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_229, SetName_ChangesName_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// =====================================================
// GetText / SetText Tests
// =====================================================

TEST_F(XMLElementTest_229, GetText_ReturnsTextContent_229) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello World");
}

TEST_F(XMLElementTest_229, GetText_ReturnsNull_WhenNoText_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* text = elem->GetText();
    EXPECT_EQ(text, nullptr);
}

TEST_F(XMLElementTest_229, SetText_String_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("new text");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "new text");
}

TEST_F(XMLElementTest_229, SetText_Int_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_229, SetText_Unsigned_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(100u);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_229, SetText_Bool_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_229, SetText_Double_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(2.718);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 2.718);
}

TEST_F(XMLElementTest_229, SetText_Float_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(1.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

// =====================================================
// QueryIntText / QueryUnsignedText etc. Error Cases
// =====================================================

TEST_F(XMLElementTest_229, QueryIntText_ReturnsError_WhenNoText_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_229, QueryUnsignedText_ReturnsError_WhenNoText_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// =====================================================
// IntText / UnsignedText / etc. with defaults
// =====================================================

TEST_F(XMLElementTest_229, IntText_ReturnsValue_229) {
    doc.Parse("<root>-5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int result = elem->IntText(0);
    EXPECT_EQ(result, -5);
}

TEST_F(XMLElementTest_229, IntText_ReturnsDefault_WhenNoText_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int result = elem->IntText(77);
    EXPECT_EQ(result, 77);
}

TEST_F(XMLElementTest_229, UnsignedText_ReturnsValue_229) {
    doc.Parse("<root>10</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedText(0);
    EXPECT_EQ(result, 10u);
}

TEST_F(XMLElementTest_229, UnsignedText_ReturnsDefault_WhenNoText_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned result = elem->UnsignedText(88);
    EXPECT_EQ(result, 88u);
}

TEST_F(XMLElementTest_229, BoolText_ReturnsValue_229) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool result = elem->BoolText(false);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_229, BoolText_ReturnsDefault_WhenNoText_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool result = elem->BoolText(true);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_229, DoubleText_ReturnsValue_229) {
    doc.Parse("<root>6.28</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleText(0.0);
    EXPECT_DOUBLE_EQ(result, 6.28);
}

TEST_F(XMLElementTest_229, FloatText_ReturnsValue_229) {
    doc.Parse("<root>3.0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float result = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(result, 3.0f);
}

TEST_F(XMLElementTest_229, Int64Text_ReturnsValue_229) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_229, Unsigned64Text_ReturnsValue_229) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t result = elem->Unsigned64Text(0);
    EXPECT_EQ(result, UINT64_C(18446744073709551615));
}

// =====================================================
// InsertNewChildElement Tests
// =====================================================

TEST_F(XMLElementTest_229, InsertNewChildElement_CreatesChild_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(elem->FirstChildElement("child"), child);
}

TEST_F(XMLElementTest_229, InsertNewComment_CreatesComment_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_229, InsertNewText_CreatesText_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    const char* result = elem->GetText();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "some text");
}

// =====================================================
// QueryAttribute overloads
// =====================================================

TEST_F(XMLElementTest_229, QueryIntAttribute_Success_229) {
    doc.Parse("<root val=\"10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    XMLError err = elem->QueryIntAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, 10);
}

TEST_F(XMLElementTest_229, QueryIntAttribute_Missing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    XMLError err = elem->QueryIntAttribute("val", &v);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_229, QueryUnsignedAttribute_Success_229) {
    doc.Parse("<root val=\"20\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned v = 0;
    XMLError err = elem->QueryUnsignedAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, 20u);
}

TEST_F(XMLElementTest_229, QueryBoolAttribute_Success_229) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool v = false;
    XMLError err = elem->QueryBoolAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(v);
}

TEST_F(XMLElementTest_229, QueryDoubleAttribute_Success_229) {
    doc.Parse("<root val=\"1.23\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double v = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(v, 1.23);
}

TEST_F(XMLElementTest_229, QueryFloatAttribute_Success_229) {
    doc.Parse("<root val=\"4.56\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float v = 0.0f;
    XMLError err = elem->QueryFloatAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(v, 4.56f);
}

TEST_F(XMLElementTest_229, QueryStringAttribute_Success_229) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* v = nullptr;
    XMLError err = elem->QueryStringAttribute("val", &v);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v, "hello");
}

TEST_F(XMLElementTest_229, QueryStringAttribute_Missing_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* v = nullptr;
    XMLError err = elem->QueryStringAttribute("val", &v);
    EXPECT_NE(err, XML_SUCCESS);
}

// =====================================================
// FirstAttribute Tests
// =====================================================

TEST_F(XMLElementTest_229, FirstAttribute_ReturnsFirst_229) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_229, FirstAttribute_ReturnsNull_WhenNoAttributes_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// =====================================================
// ShallowClone / ShallowEqual Tests
// =====================================================

TEST_F(XMLElementTest_229, ShallowClone_ClonesElement_229) {
    doc.Parse("<root attr=\"val\"><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
    // Shallow clone should not include children
    EXPECT_EQ(cloneElem->FirstChildElement(), nullptr);
}

TEST_F(XMLElementTest_229, ShallowEqual_SameElement_229) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_229, ShallowEqual_DifferentElement_229) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// =====================================================
// ToElement Tests
// =====================================================

TEST_F(XMLElementTest_229, ToElement_ReturnsSelf_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// =====================================================
// Multiple Attributes
// =====================================================

TEST_F(XMLElementTest_229, MultipleAttributes_AllAccessible_229) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_EQ(elem->IntAttribute("b", 0), 2);
    EXPECT_EQ(elem->IntAttribute("c", 0), 3);
}

TEST_F(XMLElementTest_229, SetAttribute_OverwritesExisting_229) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", "new");
    EXPECT_STREQ(elem->Attribute("val"), "new");
}

// =====================================================
// SetAttribute with int64/uint64
// =====================================================

TEST_F(XMLElementTest_229, SetAttribute_Int64_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", INT64_C(9223372036854775807));
    int64_t result = elem->Int64Attribute("val", 0);
    EXPECT_EQ(result, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_229, SetAttribute_Uint64_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", UINT64_C(18446744073709551615));
    uint64_t result = elem->Unsigned64Attribute("val", 0);
    EXPECT_EQ(result, UINT64_C(18446744073709551615));
}

// =====================================================
// InsertNewDeclaration / InsertNewUnknown
// =====================================================

TEST_F(XMLElementTest_229, InsertNewDeclaration_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_229, InsertNewUnknown_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// =====================================================
// Edge case: Empty attribute name/value
// =====================================================

TEST_F(XMLElementTest_229, Attribute_EmptyValue_229) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* result = elem->Attribute("val");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(XMLElementTest_229, SetAttribute_EmptyString_229) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("key", "");
    const char* result = elem->Attribute("key");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}
