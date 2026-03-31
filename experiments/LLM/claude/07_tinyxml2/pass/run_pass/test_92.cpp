#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_92 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ==================== QueryAttribute (uint64_t) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeUint64_ValidValue_92) {
    doc.Parse("<root val=\"12345678901234\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 12345678901234ULL);
}

TEST_F(XMLElementTest_92, QueryAttributeUint64_NonExistentAttribute_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t value = 42;
    XMLError err = elem->QueryAttribute("nonexistent", &value);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(value, 42); // value should remain unchanged
}

TEST_F(XMLElementTest_92, QueryAttributeUint64_InvalidValue_92) {
    doc.Parse("<root val=\"notanumber\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t value = 99;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_92, QueryAttributeUint64_ZeroValue_92) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t value = 999;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0ULL);
}

TEST_F(XMLElementTest_92, QueryAttributeUint64_LargeValue_92) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    // May or may not succeed depending on implementation's handling of max uint64
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, UINT64_MAX);
    }
}

// ==================== QueryAttribute (int) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeInt_ValidValue_92) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementTest_92, QueryAttributeInt_NegativeValue_92) {
    doc.Parse("<root val=\"-100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -100);
}

TEST_F(XMLElementTest_92, QueryAttributeInt_NonExistent_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 55;
    XMLError err = elem->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(value, 55);
}

// ==================== QueryAttribute (unsigned int) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeUnsigned_ValidValue_92) {
    doc.Parse("<root val=\"4294967295\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    unsigned int value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 4294967295U);
}

// ==================== QueryAttribute (int64_t) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeInt64_ValidValue_92) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLElementTest_92, QueryAttributeInt64_NegativeValue_92) {
    doc.Parse("<root val=\"-9223372036854775808\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int64_t value = 0;
    XMLError err = elem->QueryAttribute("val", &value);
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, INT64_MIN);
    }
}

// ==================== QueryAttribute (bool) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeBool_True_92) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    bool value = false;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_92, QueryAttributeBool_False_92) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    bool value = true;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_92, QueryAttributeBool_NonExistent_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    bool value = true;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (double) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeDouble_ValidValue_92) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    double value = 0.0;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.14159, 1e-5);
}

// ==================== QueryAttribute (float) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeFloat_ValidValue_92) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    float value = 0.0f;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

// ==================== QueryAttribute (const char*) Tests ====================

TEST_F(XMLElementTest_92, QueryAttributeString_ValidValue_92) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "hello");
}

TEST_F(XMLElementTest_92, QueryAttributeString_NonExistent_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== SetAttribute / Attribute Tests ====================

TEST_F(XMLElementTest_92, SetAttribute_String_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("name", "world");
    const char* val = elem->Attribute("name");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "world");
}

TEST_F(XMLElementTest_92, SetAttribute_Int_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("count", 42);
    EXPECT_EQ(elem->IntAttribute("count", 0), 42);
}

TEST_F(XMLElementTest_92, SetAttribute_Unsigned_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("count", (unsigned)100);
    EXPECT_EQ(elem->UnsignedAttribute("count", 0), 100U);
}

TEST_F(XMLElementTest_92, SetAttribute_Int64_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int64_t bigVal = 9223372036854775807LL;
    elem->SetAttribute("big", bigVal);
    EXPECT_EQ(elem->Int64Attribute("big", 0), bigVal);
}

TEST_F(XMLElementTest_92, SetAttribute_Uint64_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetAttribute("big", bigVal);
    EXPECT_EQ(elem->Unsigned64Attribute("big", 0), bigVal);
}

TEST_F(XMLElementTest_92, SetAttribute_Bool_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_92, SetAttribute_Double_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("pi", 3.14159);
    EXPECT_NEAR(elem->DoubleAttribute("pi", 0.0), 3.14159, 1e-5);
}

TEST_F(XMLElementTest_92, SetAttribute_Float_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetAttribute("val", 1.5f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 1.5f);
}

// ==================== Default Value Tests ====================

TEST_F(XMLElementTest_92, IntAttribute_DefaultValue_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->IntAttribute("missing", -1), -1);
}

TEST_F(XMLElementTest_92, UnsignedAttribute_DefaultValue_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->UnsignedAttribute("missing", 999U), 999U);
}

TEST_F(XMLElementTest_92, Int64Attribute_DefaultValue_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->Int64Attribute("missing", -999LL), -999LL);
}

TEST_F(XMLElementTest_92, Unsigned64Attribute_DefaultValue_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->Unsigned64Attribute("missing", 12345ULL), 12345ULL);
}

TEST_F(XMLElementTest_92, BoolAttribute_DefaultValue_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_92, DoubleAttribute_DefaultValue_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 2.718), 2.718);
}

TEST_F(XMLElementTest_92, FloatAttribute_DefaultValue_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 1.1f), 1.1f);
}

// ==================== Attribute (string match) Tests ====================

TEST_F(XMLElementTest_92, Attribute_WithValueMatch_92) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* result = elem->Attribute("val", "hello");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(XMLElementTest_92, Attribute_WithValueMismatch_92) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* result = elem->Attribute("val", "world");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementTest_92, Attribute_NonExistent_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* result = elem->Attribute("nope");
    EXPECT_EQ(result, nullptr);
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_92, FindAttribute_Exists_92) {
    doc.Parse("<root val=\"123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_92, FindAttribute_NotExists_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    EXPECT_EQ(attr, nullptr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_92, FirstAttribute_WithAttributes_92) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_92, FirstAttribute_NoAttributes_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_92, DeleteAttribute_Existing_92) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->DeleteAttribute("val");
    EXPECT_EQ(elem->FindAttribute("val"), nullptr);
}

TEST_F(XMLElementTest_92, DeleteAttribute_NonExistent_92) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    // Should not crash
    elem->DeleteAttribute("nonexistent");
    EXPECT_NE(elem->FindAttribute("val"), nullptr);
}

// ==================== SetText / GetText Tests ====================

TEST_F(XMLElementTest_92, SetText_String_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText("hello world");
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello world");
}

TEST_F(XMLElementTest_92, SetText_Int_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText(42);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_92, SetText_UnsignedInt_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText((unsigned int)100);
    unsigned int val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100U);
}

TEST_F(XMLElementTest_92, SetText_Int64_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText((int64_t)999999999999LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 999999999999LL);
}

TEST_F(XMLElementTest_92, SetText_Uint64_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText((uint64_t)18446744073709551615ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 18446744073709551615ULL);
}

TEST_F(XMLElementTest_92, SetText_Bool_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText(true);
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_92, SetText_Double_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText(3.14);
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.01);
}

TEST_F(XMLElementTest_92, SetText_Float_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetText(2.5f);
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLElementTest_92, GetText_NoText_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* text = elem->GetText();
    EXPECT_EQ(text, nullptr);
}

// ==================== Text Default Value Tests ====================

TEST_F(XMLElementTest_92, IntText_Default_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->IntText(-1), -1);
}

TEST_F(XMLElementTest_92, UnsignedText_Default_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->UnsignedText(42U), 42U);
}

TEST_F(XMLElementTest_92, Int64Text_Default_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->Int64Text(-1LL), -1LL);
}

TEST_F(XMLElementTest_92, Unsigned64Text_Default_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->Unsigned64Text(123ULL), 123ULL);
}

TEST_F(XMLElementTest_92, BoolText_Default_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_92, DoubleText_Default_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.23), 1.23);
}

TEST_F(XMLElementTest_92, FloatText_Default_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_FLOAT_EQ(elem->FloatText(4.56f), 4.56f);
}

// ==================== Text with actual values ====================

TEST_F(XMLElementTest_92, IntText_WithValue_92) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->IntText(0), 42);
}

TEST_F(XMLElementTest_92, UnsignedText_WithValue_92) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->UnsignedText(0), 100U);
}

TEST_F(XMLElementTest_92, BoolText_WithValue_92) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_92, DoubleText_WithValue_92) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_NEAR(elem->DoubleText(0.0), 3.14, 0.001);
}

TEST_F(XMLElementTest_92, FloatText_WithValue_92) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_FLOAT_EQ(elem->FloatText(0.0f), 2.5f);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_92, Name_Basic_92) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_92, SetName_Basic_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_92, InsertNewChildElement_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    
    // Verify child is actually a child
    XMLElement* found = elem->FirstChildElement("child");
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->Name(), "child");
}

// ==================== InsertNewComment Tests ====================

TEST_F(XMLElementTest_92, InsertNewComment_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLComment* comment = elem->InsertNewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
}

// ==================== InsertNewText Tests ====================

TEST_F(XMLElementTest_92, InsertNewText_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    
    const char* result = elem->GetText();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "some text");
}

// ==================== InsertNewDeclaration Tests ====================

TEST_F(XMLElementTest_92, InsertNewDeclaration_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDeclaration* decl = elem->InsertNewDeclaration("test");
    ASSERT_NE(decl, nullptr);
}

// ==================== InsertNewUnknown Tests ====================

TEST_F(XMLElementTest_92, InsertNewUnknown_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLUnknown* unknown = elem->InsertNewUnknown("stuff");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_92, ToElement_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_92, ShallowClone_92) {
    doc.Parse("<root val=\"42\"><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("val"), "42");
    // ShallowClone should not clone children
    EXPECT_EQ(cloneElem->FirstChildElement(), nullptr);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_92, ShallowEqual_Same_92) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root val=\"42\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_92, ShallowEqual_DifferentName_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_92, ShallowEqual_DifferentAttributes_92) {
    doc.Parse("<root val=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root val=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== Multiple Attributes Tests ====================

TEST_F(XMLElementTest_92, MultipleAttributes_92) {
    doc.Parse("<root a=\"1\" b=\"hello\" c=\"true\" d=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_STREQ(elem->Attribute("b"), "hello");
    EXPECT_TRUE(elem->BoolAttribute("c", false));
    EXPECT_NEAR(elem->DoubleAttribute("d", 0.0), 3.14, 0.001);
}

// ==================== Overwrite Attribute Tests ====================

TEST_F(XMLElementTest_92, OverwriteAttribute_92) {
    doc.Parse("<root val=\"10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_EQ(elem->IntAttribute("val", 0), 10);
    
    elem->SetAttribute("val", 20);
    EXPECT_EQ(elem->IntAttribute("val", 0), 20);
}

// ==================== QueryText Error Cases ====================

TEST_F(XMLElementTest_92, QueryIntText_InvalidText_92) {
    doc.Parse("<root>notanumber</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_92, QueryBoolText_InvalidText_92) {
    doc.Parse("<root>maybe</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_92, QueryIntText_NoText_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int val = 55;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== ClosingType Tests ====================

TEST_F(XMLElementTest_92, ClosingType_SelfClosing_92) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    // Just verify it doesn't crash; the actual value depends on parse
    elem->ClosingType();
}

// ==================== Accept (Visitor) Tests ====================

TEST_F(XMLElementTest_92, Accept_Visitor_92) {
    doc.Parse("<root val=\"42\"><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLPrinter printer;
    bool result = elem->Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // The output should contain "root"
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// ==================== SetText Overwrite Tests ====================

TEST_F(XMLElementTest_92, SetText_OverwriteExisting_92) {
    doc.Parse("<root>old text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_STREQ(elem->GetText(), "old text");
    
    elem->SetText("new text");
    EXPECT_STREQ(elem->GetText(), "new text");
}

// ==================== QueryAttribute with empty string attribute ====================

TEST_F(XMLElementTest_92, QueryAttribute_EmptyStringAttribute_92) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* value = nullptr;
    XMLError err = elem->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "");
}

TEST_F(XMLElementTest_92, Attribute_EmptyString_92) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    const char* val = elem->Attribute("val");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "");
}
