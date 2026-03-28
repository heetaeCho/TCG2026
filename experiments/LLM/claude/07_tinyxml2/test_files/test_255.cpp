#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_255 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ==================== BoolText Tests ====================

TEST_F(XMLElementTest_255, BoolText_ReturnsTrue_WhenTextIsTrue_255) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_255, BoolText_ReturnsFalse_WhenTextIsFalse_255) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolText(true));
}

TEST_F(XMLElementTest_255, BoolText_ReturnsDefaultTrue_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(true));
}

TEST_F(XMLElementTest_255, BoolText_ReturnsDefaultFalse_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolText(false));
}

TEST_F(XMLElementTest_255, BoolText_ReturnsDefault_WhenTextIsInvalid_255) {
    doc.Parse("<root>notabool</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(true));
    EXPECT_FALSE(elem->BoolText(false));
}

TEST_F(XMLElementTest_255, BoolText_Returns1AsTrue_255) {
    doc.Parse("<root>1</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_255, BoolText_Returns0AsFalse_255) {
    doc.Parse("<root>0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolText(true));
}

// ==================== IntText Tests ====================

TEST_F(XMLElementTest_255, IntText_ReturnsValue_WhenTextIsValid_255) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(42, elem->IntText(0));
}

TEST_F(XMLElementTest_255, IntText_ReturnsDefault_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(99, elem->IntText(99));
}

TEST_F(XMLElementTest_255, IntText_ReturnsNegativeValue_255) {
    doc.Parse("<root>-100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(-100, elem->IntText(0));
}

TEST_F(XMLElementTest_255, IntText_ReturnsDefault_WhenTextIsInvalid_255) {
    doc.Parse("<root>abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(55, elem->IntText(55));
}

// ==================== UnsignedText Tests ====================

TEST_F(XMLElementTest_255, UnsignedText_ReturnsValue_WhenValid_255) {
    doc.Parse("<root>123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(123u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_255, UnsignedText_ReturnsDefault_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(77u, elem->UnsignedText(77));
}

// ==================== Int64Text Tests ====================

TEST_F(XMLElementTest_255, Int64Text_ReturnsValue_WhenValid_255) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(INT64_C(9223372036854775807), elem->Int64Text(0));
}

TEST_F(XMLElementTest_255, Int64Text_ReturnsDefault_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(INT64_C(-1), elem->Int64Text(-1));
}

// ==================== Unsigned64Text Tests ====================

TEST_F(XMLElementTest_255, Unsigned64Text_ReturnsValue_WhenValid_255) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(UINT64_C(18446744073709551615), elem->Unsigned64Text(0));
}

TEST_F(XMLElementTest_255, Unsigned64Text_ReturnsDefault_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(UINT64_C(42), elem->Unsigned64Text(42));
}

// ==================== DoubleText Tests ====================

TEST_F(XMLElementTest_255, DoubleText_ReturnsValue_WhenValid_255) {
    doc.Parse("<root>3.14159</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(3.14159, elem->DoubleText(0.0));
}

TEST_F(XMLElementTest_255, DoubleText_ReturnsDefault_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(2.718, elem->DoubleText(2.718));
}

TEST_F(XMLElementTest_255, DoubleText_ReturnsDefault_WhenInvalidText_255) {
    doc.Parse("<root>xyz</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(1.5, elem->DoubleText(1.5));
}

// ==================== FloatText Tests ====================

TEST_F(XMLElementTest_255, FloatText_ReturnsValue_WhenValid_255) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(1.5f, elem->FloatText(0.0f));
}

TEST_F(XMLElementTest_255, FloatText_ReturnsDefault_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(9.9f, elem->FloatText(9.9f));
}

// ==================== GetText Tests ====================

TEST_F(XMLElementTest_255, GetText_ReturnsText_WhenPresent_255) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("Hello World", elem->GetText());
}

TEST_F(XMLElementTest_255, GetText_ReturnsNull_WhenEmpty_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(nullptr, elem->GetText());
}

TEST_F(XMLElementTest_255, GetText_ReturnsNull_WhenOnlyChildElements_255) {
    doc.Parse("<root><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(nullptr, elem->GetText());
}

// ==================== SetText Tests ====================

TEST_F(XMLElementTest_255, SetText_String_SetsText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("test text");
    EXPECT_STREQ("test text", elem->GetText());
}

TEST_F(XMLElementTest_255, SetText_Int_SetsText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    EXPECT_EQ(42, elem->IntText(0));
}

TEST_F(XMLElementTest_255, SetText_Unsigned_SetsText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((unsigned)100);
    EXPECT_EQ(100u, elem->UnsignedText(0));
}

TEST_F(XMLElementTest_255, SetText_Int64_SetsText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(INT64_C(123456789012345));
    EXPECT_EQ(INT64_C(123456789012345), elem->Int64Text(0));
}

TEST_F(XMLElementTest_255, SetText_Uint64_SetsText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(UINT64_C(123456789012345));
    EXPECT_EQ(UINT64_C(123456789012345), elem->Unsigned64Text(0));
}

TEST_F(XMLElementTest_255, SetText_Bool_SetsTrue_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(XMLElementTest_255, SetText_Bool_SetsFalse_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(false);
    EXPECT_FALSE(elem->BoolText(true));
}

TEST_F(XMLElementTest_255, SetText_Double_SetsText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    EXPECT_NEAR(3.14, elem->DoubleText(0.0), 0.001);
}

TEST_F(XMLElementTest_255, SetText_Float_SetsText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(2.5f);
    EXPECT_NEAR(2.5f, elem->FloatText(0.0f), 0.001f);
}

TEST_F(XMLElementTest_255, SetText_ReplacesExistingText_255) {
    doc.Parse("<root>old text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("new text");
    EXPECT_STREQ("new text", elem->GetText());
}

// ==================== Query*Text Tests ====================

TEST_F(XMLElementTest_255, QueryIntText_ReturnsSuccess_WhenValid_255) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntText(&val));
    EXPECT_EQ(42, val);
}

TEST_F(XMLElementTest_255, QueryIntText_ReturnsError_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_NE(XML_SUCCESS, elem->QueryIntText(&val));
}

TEST_F(XMLElementTest_255, QueryBoolText_ReturnsSuccess_WhenTrue_255) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolText(&val));
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_255, QueryBoolText_ReturnsSuccess_WhenFalse_255) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = true;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolText(&val));
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_255, QueryBoolText_ReturnsError_WhenNoText_255) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_NE(XML_SUCCESS, elem->QueryBoolText(&val));
}

TEST_F(XMLElementTest_255, QueryBoolText_ReturnsError_WhenInvalidText_255) {
    doc.Parse("<root>notbool</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_NE(XML_SUCCESS, elem->QueryBoolText(&val));
}

TEST_F(XMLElementTest_255, QueryUnsignedText_ReturnsSuccess_255) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    unsigned val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsignedText(&val));
    EXPECT_EQ(100u, val);
}

TEST_F(XMLElementTest_255, QueryDoubleText_ReturnsSuccess_255) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryDoubleText(&val));
    EXPECT_DOUBLE_EQ(3.14, val);
}

TEST_F(XMLElementTest_255, QueryFloatText_ReturnsSuccess_255) {
    doc.Parse("<root>2.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    EXPECT_EQ(XML_SUCCESS, elem->QueryFloatText(&val));
    EXPECT_FLOAT_EQ(2.5f, val);
}

TEST_F(XMLElementTest_255, QueryInt64Text_ReturnsSuccess_255) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryInt64Text(&val));
    EXPECT_EQ(INT64_C(9223372036854775807), val);
}

TEST_F(XMLElementTest_255, QueryUnsigned64Text_ReturnsSuccess_255) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    uint64_t val = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryUnsigned64Text(&val));
    EXPECT_EQ(UINT64_C(18446744073709551615), val);
}

// ==================== Attribute Tests ====================

TEST_F(XMLElementTest_255, Attribute_ReturnsValue_WhenExists_255) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("hello", elem->Attribute("attr"));
}

TEST_F(XMLElementTest_255, Attribute_ReturnsNull_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(nullptr, elem->Attribute("nonexistent"));
}

TEST_F(XMLElementTest_255, Attribute_WithValueMatch_ReturnsValue_255) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("hello", elem->Attribute("attr", "hello"));
}

TEST_F(XMLElementTest_255, Attribute_WithValueMismatch_ReturnsNull_255) {
    doc.Parse("<root attr=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(nullptr, elem->Attribute("attr", "world"));
}

// ==================== SetAttribute/Query Tests ====================

TEST_F(XMLElementTest_255, SetAttribute_String_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("key", "value");
    EXPECT_STREQ("value", elem->Attribute("key"));
}

TEST_F(XMLElementTest_255, SetAttribute_Int_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(42, elem->IntAttribute("num", 0));
}

TEST_F(XMLElementTest_255, SetAttribute_Unsigned_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", (unsigned)100);
    EXPECT_EQ(100u, elem->UnsignedAttribute("num", 0));
}

TEST_F(XMLElementTest_255, SetAttribute_Bool_True_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_255, SetAttribute_Bool_False_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", false);
    EXPECT_FALSE(elem->BoolAttribute("flag", true));
}

TEST_F(XMLElementTest_255, SetAttribute_Double_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 3.14);
    EXPECT_NEAR(3.14, elem->DoubleAttribute("val", 0.0), 0.001);
}

TEST_F(XMLElementTest_255, SetAttribute_Float_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", 2.5f);
    EXPECT_NEAR(2.5f, elem->FloatAttribute("val", 0.0f), 0.001f);
}

TEST_F(XMLElementTest_255, SetAttribute_Int64_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", INT64_C(123456789012345));
    EXPECT_EQ(INT64_C(123456789012345), elem->Int64Attribute("val", 0));
}

TEST_F(XMLElementTest_255, SetAttribute_Uint64_AndQueryBack_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", UINT64_C(123456789012345));
    EXPECT_EQ(UINT64_C(123456789012345), elem->Unsigned64Attribute("val", 0));
}

// ==================== IntAttribute default value Tests ====================

TEST_F(XMLElementTest_255, IntAttribute_ReturnsDefault_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(99, elem->IntAttribute("missing", 99));
}

TEST_F(XMLElementTest_255, UnsignedAttribute_ReturnsDefault_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(99u, elem->UnsignedAttribute("missing", 99));
}

TEST_F(XMLElementTest_255, BoolAttribute_ReturnsDefault_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("missing", true));
    EXPECT_FALSE(elem->BoolAttribute("missing", false));
}

TEST_F(XMLElementTest_255, DoubleAttribute_ReturnsDefault_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(1.23, elem->DoubleAttribute("missing", 1.23));
}

TEST_F(XMLElementTest_255, FloatAttribute_ReturnsDefault_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(1.23f, elem->FloatAttribute("missing", 1.23f));
}

TEST_F(XMLElementTest_255, Int64Attribute_ReturnsDefault_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(INT64_C(-999), elem->Int64Attribute("missing", -999));
}

TEST_F(XMLElementTest_255, Unsigned64Attribute_ReturnsDefault_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(UINT64_C(999), elem->Unsigned64Attribute("missing", 999));
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_255, DeleteAttribute_RemovesAttribute_255) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("value", elem->Attribute("attr"));
    elem->DeleteAttribute("attr");
    EXPECT_EQ(nullptr, elem->Attribute("attr"));
}

TEST_F(XMLElementTest_255, DeleteAttribute_NonExistent_DoesNotCrash_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("nonexistent");
    // Should not crash
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_255, FindAttribute_ReturnsAttribute_WhenExists_255) {
    doc.Parse("<root attr=\"value\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ("value", attr->Value());
}

TEST_F(XMLElementTest_255, FindAttribute_ReturnsNull_WhenNotExists_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(nullptr, elem->FindAttribute("missing"));
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_255, FirstAttribute_ReturnsFirstAttribute_255) {
    doc.Parse("<root first=\"1\" second=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ("first", attr->Name());
    EXPECT_STREQ("1", attr->Value());
}

TEST_F(XMLElementTest_255, FirstAttribute_ReturnsNull_WhenNoAttributes_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(nullptr, elem->FirstAttribute());
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_255, Name_ReturnsElementName_255) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("myElement", elem->Name());
}

TEST_F(XMLElementTest_255, SetName_ChangesName_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ("newName", elem->Name());
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_255, ToElement_ReturnsSelf_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem, elem->ToElement());
}

// ==================== InsertNew* Tests ====================

TEST_F(XMLElementTest_255, InsertNewChildElement_CreatesChild_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ("child", child->Name());
    EXPECT_NE(nullptr, elem->FirstChildElement("child"));
}

TEST_F(XMLElementTest_255, InsertNewComment_CreatesComment_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("test comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_255, InsertNewText_CreatesTextNode_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("hello");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ("hello", elem->GetText());
}

TEST_F(XMLElementTest_255, InsertNewDeclaration_CreatesDecl_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_255, InsertNewUnknown_CreatesUnknown_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("unknown stuff");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST_F(XMLElementTest_255, ShallowClone_ClonesElement_255) {
    doc.Parse("<root attr=\"val\">text</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ("root", cloneElem->Name());
    EXPECT_STREQ("val", cloneElem->Attribute("attr"));
}

TEST_F(XMLElementTest_255, ShallowEqual_ReturnsTrue_WhenEqual_255) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_255, ShallowEqual_ReturnsFalse_WhenDifferentName_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_255, ShallowEqual_ReturnsFalse_WhenDifferentAttributes_255) {
    doc.Parse("<root attr=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root attr=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_255, QueryIntAttribute_ReturnsSuccess_255) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    EXPECT_EQ(XML_SUCCESS, elem->QueryIntAttribute("val", &v));
    EXPECT_EQ(42, v);
}

TEST_F(XMLElementTest_255, QueryIntAttribute_ReturnsNoAttribute_WhenMissing_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int v = 0;
    EXPECT_EQ(XML_NO_ATTRIBUTE, elem->QueryIntAttribute("missing", &v));
}

TEST_F(XMLElementTest_255, QueryBoolAttribute_ReturnsSuccess_255) {
    doc.Parse("<root flag=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool v = false;
    EXPECT_EQ(XML_SUCCESS, elem->QueryBoolAttribute("flag", &v));
    EXPECT_TRUE(v);
}

TEST_F(XMLElementTest_255, QueryStringAttribute_ReturnsSuccess_255) {
    doc.Parse("<root name=\"test\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* v = nullptr;
    EXPECT_EQ(XML_SUCCESS, elem->QueryStringAttribute("name", &v));
    EXPECT_STREQ("test", v);
}

TEST_F(XMLElementTest_255, QueryStringAttribute_ReturnsNoAttribute_WhenMissing_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* v = nullptr;
    EXPECT_EQ(XML_NO_ATTRIBUTE, elem->QueryStringAttribute("missing", &v));
}

// ==================== Multiple Attributes Tests ====================

TEST_F(XMLElementTest_255, MultipleAttributes_AllAccessible_255) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("1", elem->Attribute("a"));
    EXPECT_STREQ("2", elem->Attribute("b"));
    EXPECT_STREQ("3", elem->Attribute("c"));
}

TEST_F(XMLElementTest_255, SetAttribute_OverwritesExisting_255) {
    doc.Parse("<root attr=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("attr", "new");
    EXPECT_STREQ("new", elem->Attribute("attr"));
}

// ==================== Boundary/Edge Tests ====================

TEST_F(XMLElementTest_255, IntText_Zero_255) {
    doc.Parse("<root>0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(0, elem->IntText(99));
}

TEST_F(XMLElementTest_255, BoolText_WithWhitespace_255) {
    doc.Parse("<root> true </root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Whitespace handling depends on implementation
    bool val = elem->BoolText(false);
    // Just make sure it doesn't crash; result depends on implementation
    (void)val;
}

TEST_F(XMLElementTest_255, SetText_Overwrites_ExistingText_255) {
    doc.Parse("<root>old</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(123);
    EXPECT_EQ(123, elem->IntText(0));
}

TEST_F(XMLElementTest_255, EmptyElementName_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("root", elem->Name());
}

TEST_F(XMLElementTest_255, NestedElements_GetText_FirstTextNode_255) {
    doc.Parse("<root>Hello<child>World</child></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ("Hello", elem->GetText());
}

TEST_F(XMLElementTest_255, ClosingType_ForSelfClosing_255) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // Just check it doesn't crash
    auto ct = elem->ClosingType();
    (void)ct;
}
