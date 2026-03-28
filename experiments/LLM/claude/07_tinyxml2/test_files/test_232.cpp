#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_232 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ============================================================
// BoolAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, BoolAttribute_ReturnsTrueWhenAttributeIsTrue_232) {
    doc.Parse("<root flag=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_232, BoolAttribute_ReturnsFalseWhenAttributeIsFalse_232) {
    doc.Parse("<root flag=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolAttribute("flag", true));
}

TEST_F(XMLElementTest_232, BoolAttribute_ReturnsDefaultWhenAttributeMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("nonexistent", true));
    EXPECT_FALSE(elem->BoolAttribute("nonexistent", false));
}

TEST_F(XMLElementTest_232, BoolAttribute_ReturnsDefaultTrueWhenAttributeMissing_232) {
    doc.Parse("<root other=\"123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
}

TEST_F(XMLElementTest_232, BoolAttribute_ReturnsDefaultFalseWhenAttributeMissing_232) {
    doc.Parse("<root other=\"123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_232, BoolAttribute_Handles1AsTrue_232) {
    doc.Parse("<root flag=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_232, BoolAttribute_Handles0AsFalse_232) {
    doc.Parse("<root flag=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolAttribute("flag", true));
}

// ============================================================
// IntAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, IntAttribute_ReturnsValueWhenPresent_232) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), 42);
}

TEST_F(XMLElementTest_232, IntAttribute_ReturnsDefaultWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", -1), -1);
}

TEST_F(XMLElementTest_232, IntAttribute_NegativeValue_232) {
    doc.Parse("<root val=\"-100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), -100);
}

TEST_F(XMLElementTest_232, IntAttribute_ZeroValue_232) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 99), 0);
}

// ============================================================
// UnsignedAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, UnsignedAttribute_ReturnsValueWhenPresent_232) {
    doc.Parse("<root val=\"100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0u), 100u);
}

TEST_F(XMLElementTest_232, UnsignedAttribute_ReturnsDefaultWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("val", 55u), 55u);
}

// ============================================================
// Int64Attribute Tests
// ============================================================

TEST_F(XMLElementTest_232, Int64Attribute_ReturnsValueWhenPresent_232) {
    doc.Parse("<root val=\"9999999999\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("val", 0), 9999999999LL);
}

TEST_F(XMLElementTest_232, Int64Attribute_ReturnsDefaultWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("val", -1), -1);
}

// ============================================================
// Unsigned64Attribute Tests
// ============================================================

TEST_F(XMLElementTest_232, Unsigned64Attribute_ReturnsValueWhenPresent_232) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("val", 0), 18446744073709551615ULL);
}

TEST_F(XMLElementTest_232, Unsigned64Attribute_ReturnsDefaultWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("val", 123ULL), 123ULL);
}

// ============================================================
// DoubleAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, DoubleAttribute_ReturnsValueWhenPresent_232) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("val", 0.0), 3.14);
}

TEST_F(XMLElementTest_232, DoubleAttribute_ReturnsDefaultWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("val", 2.71), 2.71);
}

// ============================================================
// FloatAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, FloatAttribute_ReturnsValueWhenPresent_232) {
    doc.Parse("<root val=\"1.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 1.5f);
}

TEST_F(XMLElementTest_232, FloatAttribute_ReturnsDefaultWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 9.9f), 9.9f);
}

// ============================================================
// Attribute (string) Tests
// ============================================================

TEST_F(XMLElementTest_232, Attribute_ReturnsValueWhenPresent_232) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = elem->Attribute("name");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "hello");
}

TEST_F(XMLElementTest_232, Attribute_ReturnsNullWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_232, Attribute_ReturnsValueWhenMatchesExpected_232) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = elem->Attribute("name", "hello");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "hello");
}

TEST_F(XMLElementTest_232, Attribute_ReturnsNullWhenValueDoesNotMatch_232) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("name", "world"), nullptr);
}

// ============================================================
// SetAttribute / QueryAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, SetAttribute_StringValue_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("key", "value");
    EXPECT_STREQ(elem->Attribute("key"), "value");
}

TEST_F(XMLElementTest_232, SetAttribute_IntValue_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(elem->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_232, SetAttribute_BoolValue_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_232, SetAttribute_DoubleValue_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("pi", 3.14159);
    EXPECT_NEAR(elem->DoubleAttribute("pi", 0.0), 3.14159, 0.001);
}

TEST_F(XMLElementTest_232, SetAttribute_OverwriteExisting_232) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", "new");
    EXPECT_STREQ(elem->Attribute("val"), "new");
}

// ============================================================
// QueryBoolAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, QueryBoolAttribute_ReturnsSuccess_232) {
    doc.Parse("<root flag=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    XMLError err = elem->QueryBoolAttribute("flag", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_232, QueryBoolAttribute_ReturnsNoAttributeWhenMissing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    XMLError err = elem->QueryBoolAttribute("flag", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    // val should remain unchanged
    EXPECT_TRUE(val);
}

// ============================================================
// QueryIntAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, QueryIntAttribute_Success_232) {
    doc.Parse("<root num=\"7\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntAttribute("num", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 7);
}

TEST_F(XMLElementTest_232, QueryIntAttribute_NoAttribute_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 99;
    XMLError err = elem->QueryIntAttribute("num", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_EQ(val, 99);
}

TEST_F(XMLElementTest_232, QueryIntAttribute_WrongType_232) {
    doc.Parse("<root num=\"notanumber\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntAttribute("num", &val);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// DeleteAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, DeleteAttribute_RemovesExistingAttribute_232) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("a");
    EXPECT_EQ(elem->Attribute("a"), nullptr);
    EXPECT_STREQ(elem->Attribute("b"), "2");
}

TEST_F(XMLElementTest_232, DeleteAttribute_NonExistentAttributeIsNoOp_232) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("nonexistent");
    EXPECT_STREQ(elem->Attribute("a"), "1");
}

// ============================================================
// FindAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, FindAttribute_ReturnsAttributeWhenFound_232) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_232, FindAttribute_ReturnsNullWhenNotFound_232) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FindAttribute("missing"), nullptr);
}

// ============================================================
// GetText / SetText Tests
// ============================================================

TEST_F(XMLElementTest_232, GetText_ReturnsTextContent_232) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

TEST_F(XMLElementTest_232, GetText_ReturnsNullWhenNoText_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_232, SetText_StringSetsTextContent_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("New Text");
    EXPECT_STREQ(elem->GetText(), "New Text");
}

TEST_F(XMLElementTest_232, SetText_IntSetsTextContent_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_232, SetText_BoolTrueSetsTextContent_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_232, SetText_BoolFalseSetsTextContent_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(false);
    EXPECT_STREQ(elem->GetText(), "false");
}

TEST_F(XMLElementTest_232, SetText_OverwritesExistingText_232) {
    doc.Parse("<root>Old</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("New");
    EXPECT_STREQ(elem->GetText(), "New");
}

// ============================================================
// QueryIntText / QueryBoolText Tests
// ============================================================

TEST_F(XMLElementTest_232, QueryIntText_Success_232) {
    doc.Parse("<root>123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_232, QueryIntText_NoTextContent_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_232, QueryBoolText_True_232) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_232, QueryBoolText_False_232) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

// ============================================================
// IntText / BoolText / DoubleText / FloatText with defaults
// ============================================================

TEST_F(XMLElementTest_232, IntText_ReturnsValueWhenPresent_232) {
    doc.Parse("<root>99</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 99);
}

TEST_F(XMLElementTest_232, IntText_ReturnsDefaultWhenNoText_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(-1), -1);
}

TEST_F(XMLElementTest_232, BoolText_ReturnsValueWhenPresent_232) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_232, BoolText_ReturnsDefaultWhenNoText_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_232, DoubleText_ReturnsValueWhenPresent_232) {
    doc.Parse("<root>2.718</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_NEAR(elem->DoubleText(0.0), 2.718, 0.001);
}

TEST_F(XMLElementTest_232, FloatText_ReturnsValueWhenPresent_232) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(0.0f), 1.5f);
}

// ============================================================
// Name / SetName Tests
// ============================================================

TEST_F(XMLElementTest_232, Name_ReturnsElementName_232) {
    doc.Parse("<myelem/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myelem");
}

TEST_F(XMLElementTest_232, SetName_ChangesElementName_232) {
    doc.Parse("<old/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newname");
    EXPECT_STREQ(elem->Name(), "newname");
}

// ============================================================
// InsertNewChildElement Tests
// ============================================================

TEST_F(XMLElementTest_232, InsertNewChildElement_CreatesChild_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(child->Parent(), elem);
}

TEST_F(XMLElementTest_232, InsertNewComment_CreatesComment_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("This is a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_232, InsertNewText_CreatesText_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

// ============================================================
// FirstAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, FirstAttribute_ReturnsFirstWhenPresent_232) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_232, FirstAttribute_ReturnsNullWhenNone_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

// ============================================================
// ToElement Tests
// ============================================================

TEST_F(XMLElementTest_232, ToElement_ReturnsSelf_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================

TEST_F(XMLElementTest_232, ShallowClone_CreatesClone_232) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
    // Clean up
    doc.DeleteNode(clone);
}

TEST_F(XMLElementTest_232, ShallowEqual_ReturnsTrueForSameElement_232) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    EXPECT_TRUE(elem->ShallowEqual(clone));
    doc.DeleteNode(clone);
}

TEST_F(XMLElementTest_232, ShallowEqual_ReturnsFalseForDifferentAttributes_232) {
    XMLDocument doc2;
    doc.Parse("<root a=\"1\"/>");
    doc2.Parse("<root a=\"2\"/>");
    XMLElement* elem1 = doc.RootElement();
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// ============================================================
// Multiple attribute types on same element
// ============================================================

TEST_F(XMLElementTest_232, MultipleAttributeTypes_232) {
    doc.Parse("<root intval=\"10\" floatval=\"1.5\" boolval=\"true\" strval=\"text\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("intval", 0), 10);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("floatval", 0.0f), 1.5f);
    EXPECT_TRUE(elem->BoolAttribute("boolval", false));
    EXPECT_STREQ(elem->Attribute("strval"), "text");
}

// ============================================================
// QueryStringAttribute Tests
// ============================================================

TEST_F(XMLElementTest_232, QueryStringAttribute_Success_232) {
    doc.Parse("<root key=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("key", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(val, "value");
}

TEST_F(XMLElementTest_232, QueryStringAttribute_Missing_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("key", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// ============================================================
// UnsignedText / Int64Text / Unsigned64Text Tests
// ============================================================

TEST_F(XMLElementTest_232, UnsignedText_ReturnsValueWhenPresent_232) {
    doc.Parse("<root>500</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(0u), 500u);
}

TEST_F(XMLElementTest_232, Int64Text_ReturnsValueWhenPresent_232) {
    doc.Parse("<root>9999999999</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(0), 9999999999LL);
}

TEST_F(XMLElementTest_232, Unsigned64Text_ReturnsDefaultWhenNoText_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(12345ULL), 12345ULL);
}

// ============================================================
// SetText with various types
// ============================================================

TEST_F(XMLElementTest_232, SetText_UnsignedInt_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((unsigned int)200);
    EXPECT_STREQ(elem->GetText(), "200");
}

TEST_F(XMLElementTest_232, SetText_Int64_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((int64_t)9999999999LL);
    EXPECT_STREQ(elem->GetText(), "9999999999");
}

TEST_F(XMLElementTest_232, SetText_Uint64_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((uint64_t)18446744073709551615ULL);
    EXPECT_STREQ(elem->GetText(), "18446744073709551615");
}

TEST_F(XMLElementTest_232, SetText_Float_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(1.5f);
    float result = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

TEST_F(XMLElementTest_232, SetText_Double_232) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14159);
    double result = elem->DoubleText(0.0);
    EXPECT_NEAR(result, 3.14159, 0.001);
}

// ============================================================
// Edge case: Empty attribute value
// ============================================================

TEST_F(XMLElementTest_232, Attribute_EmptyString_232) {
    doc.Parse("<root key=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = elem->Attribute("key");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "");
}

// ============================================================
// Edge case: BoolAttribute with invalid string returns default
// ============================================================

TEST_F(XMLElementTest_232, BoolAttribute_InvalidStringReturnsDefault_232) {
    doc.Parse("<root flag=\"notabool\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // QueryBoolAttribute should fail, so BoolAttribute returns the default
    bool result = elem->BoolAttribute("flag", true);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementTest_232, BoolAttribute_InvalidStringReturnsDefaultFalse_232) {
    doc.Parse("<root flag=\"notabool\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool result = elem->BoolAttribute("flag", false);
    EXPECT_FALSE(result);
}
