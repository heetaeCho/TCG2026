#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_228 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== IntAttribute Tests ====================

TEST_F(XMLElementTest_228, IntAttribute_ReturnsValue_WhenAttributeExists_228) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), 42);
}

TEST_F(XMLElementTest_228, IntAttribute_ReturnsDefault_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("nonexistent", 99), 99);
}

TEST_F(XMLElementTest_228, IntAttribute_ReturnsNegativeValue_228) {
    doc.Parse("<root val=\"-100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), -100);
}

TEST_F(XMLElementTest_228, IntAttribute_ReturnsZero_WhenValueIsZero_228) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 55), 0);
}

TEST_F(XMLElementTest_228, IntAttribute_ReturnsDefault_WhenValueIsNotInt_228) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    // When attribute value is not a valid int, QueryIntAttribute fails, so default is returned
    EXPECT_EQ(elem->IntAttribute("val", 77), 77);
}

// ==================== UnsignedAttribute Tests ====================

TEST_F(XMLElementTest_228, UnsignedAttribute_ReturnsValue_WhenAttributeExists_228) {
    doc.Parse("<root val=\"123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0u), 123u);
}

TEST_F(XMLElementTest_228, UnsignedAttribute_ReturnsDefault_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("missing", 50u), 50u);
}

// ==================== Int64Attribute Tests ====================

TEST_F(XMLElementTest_228, Int64Attribute_ReturnsValue_WhenAttributeExists_228) {
    doc.Parse("<root val=\"9999999999\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("val", 0), 9999999999LL);
}

TEST_F(XMLElementTest_228, Int64Attribute_ReturnsDefault_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("missing", -1LL), -1LL);
}

// ==================== Unsigned64Attribute Tests ====================

TEST_F(XMLElementTest_228, Unsigned64Attribute_ReturnsValue_WhenAttributeExists_228) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("val", 0ULL), 18446744073709551615ULL);
}

TEST_F(XMLElementTest_228, Unsigned64Attribute_ReturnsDefault_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("missing", 42ULL), 42ULL);
}

// ==================== BoolAttribute Tests ====================

TEST_F(XMLElementTest_228, BoolAttribute_ReturnsTrue_WhenAttributeIsTrue_228) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolAttribute("val", false), true);
}

TEST_F(XMLElementTest_228, BoolAttribute_ReturnsFalse_WhenAttributeIsFalse_228) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolAttribute("val", true), false);
}

TEST_F(XMLElementTest_228, BoolAttribute_ReturnsDefault_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolAttribute("missing", true), true);
}

// ==================== DoubleAttribute Tests ====================

TEST_F(XMLElementTest_228, DoubleAttribute_ReturnsValue_WhenAttributeExists_228) {
    doc.Parse("<root val=\"3.14159\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("val", 0.0), 3.14159);
}

TEST_F(XMLElementTest_228, DoubleAttribute_ReturnsDefault_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("missing", 2.718), 2.718);
}

// ==================== FloatAttribute Tests ====================

TEST_F(XMLElementTest_228, FloatAttribute_ReturnsValue_WhenAttributeExists_228) {
    doc.Parse("<root val=\"1.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 1.5f);
}

TEST_F(XMLElementTest_228, FloatAttribute_ReturnsDefault_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 9.9f), 9.9f);
}

// ==================== Attribute (string) Tests ====================

TEST_F(XMLElementTest_228, Attribute_ReturnsValue_WhenAttributeExists_228) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = elem->Attribute("name");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "hello");
}

TEST_F(XMLElementTest_228, Attribute_ReturnsNull_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("missing"), nullptr);
}

TEST_F(XMLElementTest_228, Attribute_ReturnsValue_WhenMatchingValueProvided_228) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = elem->Attribute("name", "hello");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "hello");
}

TEST_F(XMLElementTest_228, Attribute_ReturnsNull_WhenValueDoesNotMatch_228) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("name", "world"), nullptr);
}

// ==================== SetAttribute / QueryAttribute Tests ====================

TEST_F(XMLElementTest_228, SetAttribute_Int_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("count", 42);
    int val = 0;
    EXPECT_EQ(elem->QueryIntAttribute("count", &val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_228, SetAttribute_String_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("label", "test");
    const char* val = nullptr;
    EXPECT_EQ(elem->QueryStringAttribute("label", &val), XML_SUCCESS);
    EXPECT_STREQ(val, "test");
}

TEST_F(XMLElementTest_228, SetAttribute_Bool_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolAttribute("flag", &val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_228, SetAttribute_Double_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("pi", 3.14159);
    double val = 0.0;
    EXPECT_EQ(elem->QueryDoubleAttribute("pi", &val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14159);
}

TEST_F(XMLElementTest_228, SetAttribute_Float_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("ratio", 2.5f);
    float val = 0.0f;
    EXPECT_EQ(elem->QueryFloatAttribute("ratio", &val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLElementTest_228, SetAttribute_Unsigned_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("uval", 300u);
    unsigned int val = 0;
    EXPECT_EQ(elem->QueryUnsignedAttribute("uval", &val), XML_SUCCESS);
    EXPECT_EQ(val, 300u);
}

TEST_F(XMLElementTest_228, SetAttribute_Int64_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("big", (int64_t)9876543210LL);
    int64_t val = 0;
    EXPECT_EQ(elem->QueryInt64Attribute("big", &val), XML_SUCCESS);
    EXPECT_EQ(val, 9876543210LL);
}

TEST_F(XMLElementTest_228, SetAttribute_Uint64_AndQueryBack_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("ubig", (uint64_t)12345678901234ULL);
    uint64_t val = 0;
    EXPECT_EQ(elem->QueryUnsigned64Attribute("ubig", &val), XML_SUCCESS);
    EXPECT_EQ(val, 12345678901234ULL);
}

// ==================== QueryIntAttribute Error Cases ====================

TEST_F(XMLElementTest_228, QueryIntAttribute_ReturnsError_WhenAttributeMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_NE(elem->QueryIntAttribute("missing", &val), XML_SUCCESS);
}

TEST_F(XMLElementTest_228, QueryIntAttribute_ReturnsError_WhenValueNotParseable_228) {
    doc.Parse("<root val=\"abc\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_NE(elem->QueryIntAttribute("val", &val), XML_SUCCESS);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_228, DeleteAttribute_RemovesExistingAttribute_228) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("a");
    EXPECT_EQ(elem->Attribute("a"), nullptr);
    EXPECT_NE(elem->Attribute("b"), nullptr);
}

TEST_F(XMLElementTest_228, DeleteAttribute_NoEffect_WhenAttributeMissing_228) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("nonexistent");
    EXPECT_NE(elem->Attribute("a"), nullptr);
}

// ==================== GetText / SetText Tests ====================

TEST_F(XMLElementTest_228, GetText_ReturnsTextContent_228) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

TEST_F(XMLElementTest_228, GetText_ReturnsNull_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_228, SetText_String_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("New Text");
    EXPECT_STREQ(elem->GetText(), "New Text");
}

TEST_F(XMLElementTest_228, SetText_Int_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(42);
    EXPECT_STREQ(elem->GetText(), "42");
}

TEST_F(XMLElementTest_228, SetText_Bool_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

TEST_F(XMLElementTest_228, SetText_Double_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    double val = atof(text);
    EXPECT_NEAR(val, 3.14, 0.001);
}

// ==================== QueryIntText / IntText Tests ====================

TEST_F(XMLElementTest_228, QueryIntText_Success_228) {
    doc.Parse("<root>123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_228, QueryIntText_Error_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_NE(elem->QueryIntText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_228, IntText_ReturnsValue_228) {
    doc.Parse("<root>456</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 456);
}

TEST_F(XMLElementTest_228, IntText_ReturnsDefault_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(99), 99);
}

// ==================== QueryBoolText / BoolText Tests ====================

TEST_F(XMLElementTest_228, QueryBoolText_Success_228) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_228, BoolText_ReturnsDefault_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->BoolText(true), true);
}

// ==================== QueryDoubleText / DoubleText Tests ====================

TEST_F(XMLElementTest_228, QueryDoubleText_Success_228) {
    doc.Parse("<root>2.718</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    EXPECT_EQ(elem->QueryDoubleText(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 2.718);
}

TEST_F(XMLElementTest_228, DoubleText_ReturnsDefault_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.23), 1.23);
}

// ==================== QueryFloatText / FloatText Tests ====================

TEST_F(XMLElementTest_228, QueryFloatText_Success_228) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    EXPECT_EQ(elem->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

TEST_F(XMLElementTest_228, FloatText_ReturnsDefault_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(7.7f), 7.7f);
}

// ==================== QueryUnsignedText / UnsignedText Tests ====================

TEST_F(XMLElementTest_228, UnsignedText_ReturnsValue_228) {
    doc.Parse("<root>500</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(0u), 500u);
}

TEST_F(XMLElementTest_228, UnsignedText_ReturnsDefault_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(33u), 33u);
}

// ==================== Int64Text / Unsigned64Text Tests ====================

TEST_F(XMLElementTest_228, Int64Text_ReturnsValue_228) {
    doc.Parse("<root>9876543210</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(0LL), 9876543210LL);
}

TEST_F(XMLElementTest_228, Int64Text_ReturnsDefault_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(-1LL), -1LL);
}

TEST_F(XMLElementTest_228, Unsigned64Text_ReturnsValue_228) {
    doc.Parse("<root>12345678901234</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(0ULL), 12345678901234ULL);
}

TEST_F(XMLElementTest_228, Unsigned64Text_ReturnsDefault_WhenNoText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(99ULL), 99ULL);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_228, Name_ReturnsElementName_228) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_228, SetName_ChangesName_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_228, FindAttribute_ReturnsAttribute_WhenExists_228) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_228, FindAttribute_ReturnsNull_WhenMissing_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FindAttribute("missing"), nullptr);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_228, FirstAttribute_ReturnsFirstAttribute_228) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_228, FirstAttribute_ReturnsNull_WhenNoAttributes_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

// ==================== InsertNewChildElement Tests ====================

TEST_F(XMLElementTest_228, InsertNewChildElement_CreatesChild_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(elem->FirstChildElement("child"), child);
}

// ==================== InsertNewComment Tests ====================

TEST_F(XMLElementTest_228, InsertNewComment_CreatesComment_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
}

// ==================== InsertNewText Tests ====================

TEST_F(XMLElementTest_228, InsertNewText_CreatesText_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

// ==================== InsertNewDeclaration Tests ====================

TEST_F(XMLElementTest_228, InsertNewDeclaration_CreatesDeclaration_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLDeclaration* decl = elem->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

// ==================== InsertNewUnknown Tests ====================

TEST_F(XMLElementTest_228, InsertNewUnknown_CreatesUnknown_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLUnknown* unknown = elem->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLElementTest_228, ShallowClone_ClonesElementWithAttributes_228) {
    doc.Parse("<root a=\"1\" b=\"2\"><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    XMLNode* clone = elem->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("a"), "1");
    EXPECT_STREQ(cloneElem->Attribute("b"), "2");
    // ShallowClone should not clone children
    EXPECT_EQ(cloneElem->FirstChildElement(), nullptr);

    doc2.InsertEndChild(clone);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLElementTest_228, ShallowEqual_ReturnsTrueForEqualElements_228) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root a=\"1\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_TRUE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_228, ShallowEqual_ReturnsFalseForDifferentAttributes_228) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root a=\"2\"/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

TEST_F(XMLElementTest_228, ShallowEqual_ReturnsFalseForDifferentNames_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    EXPECT_FALSE(elem->ShallowEqual(elem2));
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_228, ToElement_ReturnsSelf_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== Multiple Attributes Tests ====================

TEST_F(XMLElementTest_228, MultipleAttributes_AllAccessible_228) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\" d=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("a", 0), 1);
    EXPECT_EQ(elem->IntAttribute("b", 0), 2);
    EXPECT_EQ(elem->IntAttribute("c", 0), 3);
    EXPECT_STREQ(elem->Attribute("d"), "hello");
}

// ==================== Overwrite Attribute Tests ====================

TEST_F(XMLElementTest_228, SetAttribute_OverwritesExisting_228) {
    doc.Parse("<root val=\"10\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), 10);
    elem->SetAttribute("val", 20);
    EXPECT_EQ(elem->IntAttribute("val", 0), 20);
}

// ==================== Boundary: Large Integer Tests ====================

TEST_F(XMLElementTest_228, IntAttribute_MaxInt_228) {
    doc.Parse("<root val=\"2147483647\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), 2147483647);
}

TEST_F(XMLElementTest_228, IntAttribute_MinInt_228) {
    doc.Parse("<root val=\"-2147483648\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), -2147483648);
}

// ==================== SetText overwrite Tests ====================

TEST_F(XMLElementTest_228, SetText_OverwritesExistingText_228) {
    doc.Parse("<root>Old</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Old");
    elem->SetText("New");
    EXPECT_STREQ(elem->GetText(), "New");
}

// ==================== SetText Unsigned/Int64/Uint64/Float Tests ====================

TEST_F(XMLElementTest_228, SetText_Unsigned_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(100u);
    EXPECT_STREQ(elem->GetText(), "100");
}

TEST_F(XMLElementTest_228, SetText_Int64_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((int64_t)9876543210LL);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(elem->Int64Text(0LL), 9876543210LL);
}

TEST_F(XMLElementTest_228, SetText_Uint64_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText((uint64_t)12345678901234ULL);
    EXPECT_EQ(elem->Unsigned64Text(0ULL), 12345678901234ULL);
}

TEST_F(XMLElementTest_228, SetText_Float_228) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(1.5f);
    float val = 0.0f;
    EXPECT_EQ(elem->QueryFloatText(&val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

// ==================== Empty String Attribute Tests ====================

TEST_F(XMLElementTest_228, Attribute_EmptyStringValue_228) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = elem->Attribute("val");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "");
}

// ==================== QueryAttribute Overloads Tests ====================

TEST_F(XMLElementTest_228, QueryAttribute_IntOverload_228) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryAttribute("val", &val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_228, QueryAttribute_BoolOverload_228) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryAttribute("val", &val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_228, QueryAttribute_DoubleOverload_228) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    EXPECT_EQ(elem->QueryAttribute("val", &val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

TEST_F(XMLElementTest_228, QueryAttribute_FloatOverload_228) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float val = 0.0f;
    EXPECT_EQ(elem->QueryAttribute("val", &val), XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(XMLElementTest_228, QueryAttribute_StringOverload_228) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* val = nullptr;
    EXPECT_EQ(elem->QueryAttribute("val", &val), XML_SUCCESS);
    EXPECT_STREQ(val, "hello");
}
