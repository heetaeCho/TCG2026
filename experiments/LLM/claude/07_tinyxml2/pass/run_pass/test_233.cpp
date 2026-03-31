#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_233 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== DoubleAttribute Tests ====================

TEST_F(XMLElementTest_233, DoubleAttribute_ReturnsValue_WhenAttributeExists_233) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST_F(XMLElementTest_233, DoubleAttribute_ReturnsDefault_WhenAttributeMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("nonexistent", 99.5);
    EXPECT_DOUBLE_EQ(result, 99.5);
}

TEST_F(XMLElementTest_233, DoubleAttribute_ReturnsZeroDefault_WhenAttributeMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("missing", 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(XMLElementTest_233, DoubleAttribute_NegativeValue_233) {
    doc.Parse("<root val=\"-2.718\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(result, -2.718);
}

TEST_F(XMLElementTest_233, DoubleAttribute_ZeroValue_233) {
    doc.Parse("<root val=\"0.0\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 42.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(XMLElementTest_233, DoubleAttribute_LargeValue_233) {
    doc.Parse("<root val=\"1.7976931348623157e+308\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(result, 1.7976931348623157e+308);
}

TEST_F(XMLElementTest_233, DoubleAttribute_SmallValue_233) {
    doc.Parse("<root val=\"2.2250738585072014e-308\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(result, 2.2250738585072014e-308);
}

TEST_F(XMLElementTest_233, DoubleAttribute_IntegerAsDouble_233) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 0.0);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(XMLElementTest_233, DoubleAttribute_NonNumericReturnsDefault_233) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("val", 7.7);
    // Non-numeric string: behavior depends on QueryDoubleAttribute, 
    // but the default should be returned if parsing fails
    EXPECT_DOUBLE_EQ(result, 7.7);
}

TEST_F(XMLElementTest_233, DoubleAttribute_NegativeDefault_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double result = elem->DoubleAttribute("missing", -123.456);
    EXPECT_DOUBLE_EQ(result, -123.456);
}

TEST_F(XMLElementTest_233, DoubleAttribute_MultipleAttributes_233) {
    doc.Parse("<root a=\"1.1\" b=\"2.2\" c=\"3.3\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("a", 0.0), 1.1);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("b", 0.0), 2.2);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("c", 0.0), 3.3);
}

// ==================== IntAttribute Tests ====================

TEST_F(XMLElementTest_233, IntAttribute_ReturnsValue_WhenExists_233) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), 42);
}

TEST_F(XMLElementTest_233, IntAttribute_ReturnsDefault_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", -1), -1);
}

TEST_F(XMLElementTest_233, IntAttribute_NegativeValue_233) {
    doc.Parse("<root val=\"-100\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntAttribute("val", 0), -100);
}

// ==================== UnsignedAttribute Tests ====================

TEST_F(XMLElementTest_233, UnsignedAttribute_ReturnsValue_233) {
    doc.Parse("<root val=\"123\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0u), 123u);
}

TEST_F(XMLElementTest_233, UnsignedAttribute_ReturnsDefault_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedAttribute("val", 55u), 55u);
}

// ==================== Int64Attribute Tests ====================

TEST_F(XMLElementTest_233, Int64Attribute_ReturnsValue_233) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("val", 0), INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_233, Int64Attribute_ReturnsDefault_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Attribute("val", -999), -999);
}

// ==================== Unsigned64Attribute Tests ====================

TEST_F(XMLElementTest_233, Unsigned64Attribute_ReturnsValue_233) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("val", 0), UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_233, Unsigned64Attribute_ReturnsDefault_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Attribute("val", 42), uint64_t(42));
}

// ==================== BoolAttribute Tests ====================

TEST_F(XMLElementTest_233, BoolAttribute_ReturnsTrue_233) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("val", false));
}

TEST_F(XMLElementTest_233, BoolAttribute_ReturnsFalse_233) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolAttribute("val", true));
}

TEST_F(XMLElementTest_233, BoolAttribute_ReturnsDefault_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->BoolAttribute("val", true));
}

// ==================== FloatAttribute Tests ====================

TEST_F(XMLElementTest_233, FloatAttribute_ReturnsValue_233) {
    doc.Parse("<root val=\"1.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 1.5f);
}

TEST_F(XMLElementTest_233, FloatAttribute_ReturnsDefault_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 9.9f), 9.9f);
}

// ==================== SetAttribute / Attribute Tests ====================

TEST_F(XMLElementTest_233, SetAttribute_String_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("key", "value");
    EXPECT_STREQ(elem->Attribute("key"), "value");
}

TEST_F(XMLElementTest_233, SetAttribute_Int_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("num", 42);
    EXPECT_EQ(elem->IntAttribute("num", 0), 42);
}

TEST_F(XMLElementTest_233, SetAttribute_Double_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("pi", 3.14159);
    EXPECT_NEAR(elem->DoubleAttribute("pi", 0.0), 3.14159, 1e-4);
}

TEST_F(XMLElementTest_233, SetAttribute_Bool_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("flag", true);
    EXPECT_TRUE(elem->BoolAttribute("flag", false));
}

TEST_F(XMLElementTest_233, SetAttribute_OverwriteExisting_233) {
    doc.Parse("<root val=\"old\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("val", "new");
    EXPECT_STREQ(elem->Attribute("val"), "new");
}

// ==================== Attribute (string comparison) Tests ====================

TEST_F(XMLElementTest_233, Attribute_ReturnsNull_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("nonexistent"), nullptr);
}

TEST_F(XMLElementTest_233, Attribute_WithValueMatch_233) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("val", "hello"), "hello");
}

TEST_F(XMLElementTest_233, Attribute_WithValueMismatch_233) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Attribute("val", "world"), nullptr);
}

// ==================== DeleteAttribute Tests ====================

TEST_F(XMLElementTest_233, DeleteAttribute_RemovesAttribute_233) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("a");
    EXPECT_EQ(elem->Attribute("a"), nullptr);
    EXPECT_STREQ(elem->Attribute("b"), "2");
}

TEST_F(XMLElementTest_233, DeleteAttribute_NonExistent_DoesNotCrash_233) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->DeleteAttribute("nonexistent");
    EXPECT_STREQ(elem->Attribute("a"), "1");
}

// ==================== FindAttribute Tests ====================

TEST_F(XMLElementTest_233, FindAttribute_ReturnsNonNull_WhenExists_233) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
}

TEST_F(XMLElementTest_233, FindAttribute_ReturnsNull_WhenMissing_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FindAttribute("val"), nullptr);
}

// ==================== GetText / SetText Tests ====================

TEST_F(XMLElementTest_233, GetText_ReturnsText_233) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

TEST_F(XMLElementTest_233, GetText_ReturnsNull_WhenNoText_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_233, SetText_String_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText("test text");
    EXPECT_STREQ(elem->GetText(), "test text");
}

TEST_F(XMLElementTest_233, SetText_Int_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(123);
    EXPECT_STREQ(elem->GetText(), "123");
}

TEST_F(XMLElementTest_233, SetText_Double_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(3.14);
    // We just check it's not null; exact format may vary
    EXPECT_NE(elem->GetText(), nullptr);
}

TEST_F(XMLElementTest_233, SetText_Bool_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(true);
    EXPECT_STREQ(elem->GetText(), "true");
}

// ==================== QueryText Tests ====================

TEST_F(XMLElementTest_233, QueryIntText_Success_233) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_EQ(elem->QueryIntText(&val), XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_233, QueryIntText_NoText_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int val = 0;
    EXPECT_NE(elem->QueryIntText(&val), XML_SUCCESS);
}

TEST_F(XMLElementTest_233, QueryDoubleText_Success_233) {
    doc.Parse("<root>2.718</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double val = 0.0;
    EXPECT_EQ(elem->QueryDoubleText(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 2.718);
}

TEST_F(XMLElementTest_233, QueryBoolText_Success_233) {
    doc.Parse("<root>true</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool val = false;
    EXPECT_EQ(elem->QueryBoolText(&val), XML_SUCCESS);
    EXPECT_TRUE(val);
}

// ==================== IntText / DoubleText / etc. with defaults ====================

TEST_F(XMLElementTest_233, IntText_ReturnsValue_233) {
    doc.Parse("<root>99</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(0), 99);
}

TEST_F(XMLElementTest_233, IntText_ReturnsDefault_WhenNoText_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->IntText(-1), -1);
}

TEST_F(XMLElementTest_233, DoubleText_ReturnsValue_233) {
    doc.Parse("<root>6.28</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(0.0), 6.28);
}

TEST_F(XMLElementTest_233, DoubleText_ReturnsDefault_WhenNoText_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_DOUBLE_EQ(elem->DoubleText(1.23), 1.23);
}

TEST_F(XMLElementTest_233, BoolText_ReturnsValue_233) {
    doc.Parse("<root>false</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FALSE(elem->BoolText(true));
}

TEST_F(XMLElementTest_233, FloatText_ReturnsValue_233) {
    doc.Parse("<root>1.5</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(elem->FloatText(0.0f), 1.5f);
}

TEST_F(XMLElementTest_233, UnsignedText_ReturnsValue_233) {
    doc.Parse("<root>500</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->UnsignedText(0u), 500u);
}

TEST_F(XMLElementTest_233, Int64Text_ReturnsValue_233) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Int64Text(0), INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_233, Unsigned64Text_ReturnsValue_233) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->Unsigned64Text(0), UINT64_C(18446744073709551615));
}

// ==================== InsertNew* Tests ====================

TEST_F(XMLElementTest_233, InsertNewChildElement_233) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

TEST_F(XMLElementTest_233, InsertNewComment_233) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLComment* comment = root->InsertNewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLElementTest_233, InsertNewText_233) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLText* text = root->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(root->GetText(), "some text");
}

TEST_F(XMLElementTest_233, InsertNewDeclaration_233) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLDeclaration* decl = root->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLElementTest_233, InsertNewUnknown_233) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLUnknown* unknown = root->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== Name Tests ====================

TEST_F(XMLElementTest_233, Name_ReturnsCorrectName_233) {
    doc.Parse("<myElement/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "myElement");
}

TEST_F(XMLElementTest_233, SetName_ChangesName_233) {
    doc.Parse("<old/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetName("newName");
    EXPECT_STREQ(elem->Name(), "newName");
}

// ==================== ToElement Tests ====================

TEST_F(XMLElementTest_233, ToElement_ReturnsSelf_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToElement(), elem);
}

// ==================== FirstAttribute Tests ====================

TEST_F(XMLElementTest_233, FirstAttribute_ReturnsFirst_233) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_233, FirstAttribute_ReturnsNull_WhenNoAttributes_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST_F(XMLElementTest_233, ShallowClone_ClonesElement_233) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
    // Clean up: the clone is not inserted into the doc tree, so we need to delete it
    doc.DeleteNode(clone);
}

TEST_F(XMLElementTest_233, ShallowEqual_SameElement_233) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    EXPECT_TRUE(elem->ShallowEqual(clone));
    doc.DeleteNode(clone);
}

TEST_F(XMLElementTest_233, ShallowEqual_DifferentElements_233) {
    XMLDocument doc2;
    doc.Parse("<root a=\"1\"/>");
    doc2.Parse("<other b=\"2\"/>");
    XMLElement* e1 = doc.RootElement();
    XMLElement* e2 = doc2.RootElement();
    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

// ==================== QueryAttribute Tests ====================

TEST_F(XMLElementTest_233, QueryDoubleAttribute_Success_233) {
    doc.Parse("<root val=\"1.23\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double d = 0.0;
    EXPECT_EQ(elem->QueryDoubleAttribute("val", &d), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(d, 1.23);
}

TEST_F(XMLElementTest_233, QueryDoubleAttribute_NoSuchAttribute_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    double d = 5.0;
    EXPECT_NE(elem->QueryDoubleAttribute("val", &d), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(d, 5.0);
}

TEST_F(XMLElementTest_233, QueryIntAttribute_Success_233) {
    doc.Parse("<root val=\"7\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int i = 0;
    EXPECT_EQ(elem->QueryIntAttribute("val", &i), XML_SUCCESS);
    EXPECT_EQ(i, 7);
}

TEST_F(XMLElementTest_233, QueryStringAttribute_Success_233) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    const char* s = nullptr;
    EXPECT_EQ(elem->QueryStringAttribute("val", &s), XML_SUCCESS);
    EXPECT_STREQ(s, "hello");
}

TEST_F(XMLElementTest_233, QueryBoolAttribute_Success_233) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    bool b = false;
    EXPECT_EQ(elem->QueryBoolAttribute("val", &b), XML_SUCCESS);
    EXPECT_TRUE(b);
}

TEST_F(XMLElementTest_233, QueryFloatAttribute_Success_233) {
    doc.Parse("<root val=\"2.5\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    float f = 0.0f;
    EXPECT_EQ(elem->QueryFloatAttribute("val", &f), XML_SUCCESS);
    EXPECT_FLOAT_EQ(f, 2.5f);
}

// ==================== SetAttribute with various types ====================

TEST_F(XMLElementTest_233, SetAttribute_Unsigned_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("u", 100u);
    EXPECT_EQ(elem->UnsignedAttribute("u", 0u), 100u);
}

TEST_F(XMLElementTest_233, SetAttribute_Int64_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("i64", INT64_C(9223372036854775807));
    EXPECT_EQ(elem->Int64Attribute("i64", 0), INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_233, SetAttribute_Uint64_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("u64", UINT64_C(18446744073709551615));
    EXPECT_EQ(elem->Unsigned64Attribute("u64", 0), UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_233, SetAttribute_Float_233) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetAttribute("f", 1.5f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("f", 0.0f), 1.5f);
}

// ==================== Accept (Visitor) Tests ====================

TEST_F(XMLElementTest_233, Accept_WithPrinter_233) {
    doc.Parse("<root attr=\"val\"><child/></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    XMLPrinter printer;
    bool result = elem->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    // The output should contain "root"
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// ==================== Complex document Tests ====================

TEST_F(XMLElementTest_233, NestedElements_DoubleAttribute_233) {
    doc.Parse("<root><child val=\"6.28\"/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_DOUBLE_EQ(child->DoubleAttribute("val", 0.0), 6.28);
}

TEST_F(XMLElementTest_233, EmptyAttributeValue_233) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("val"), "");
    // Empty string is not a valid double, so default should be returned
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("val", 5.5), 5.5);
}
