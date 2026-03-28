#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLTextShallowEqualTest_195 : public ::testing::Test {
protected:
    XMLDocument doc1;
    XMLDocument doc2;
};

// Test that ShallowEqual returns true when comparing two XMLText nodes with the same value
TEST_F(XMLTextShallowEqualTest_195, SameValueReturnsTrue_195) {
    doc1.Parse("<root>Hello</root>");
    doc2.Parse("<root>Hello</root>");

    const XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();
    const XMLText* text2 = doc2.FirstChildElement("root")->FirstChild()->ToText();

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test that ShallowEqual returns false when comparing two XMLText nodes with different values
TEST_F(XMLTextShallowEqualTest_195, DifferentValueReturnsFalse_195) {
    doc1.Parse("<root>Hello</root>");
    doc2.Parse("<root>World</root>");

    const XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();
    const XMLText* text2 = doc2.FirstChildElement("root")->FirstChild()->ToText();

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(text2));
}

// Test that ShallowEqual returns false when comparing XMLText with a non-text XMLNode (e.g., XMLElement)
TEST_F(XMLTextShallowEqualTest_195, CompareWithElementReturnsFalse_195) {
    doc1.Parse("<root>Hello</root>");
    doc2.Parse("<root><child/></root>");

    const XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();
    const XMLNode* element2 = doc2.FirstChildElement("root")->FirstChildElement("child");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(element2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(element2));
}

// Test that ShallowEqual returns true when comparing a text node with itself
TEST_F(XMLTextShallowEqualTest_195, CompareWithSelfReturnsTrue_195) {
    doc1.Parse("<root>Hello</root>");

    const XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();

    ASSERT_NE(text1, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text1));
}

// Test that ShallowEqual returns true for empty text nodes
TEST_F(XMLTextShallowEqualTest_195, EmptyTextNodesAreEqual_195) {
    doc1.Parse("<root></root>");
    // Manually create text nodes with empty values
    XMLText* text1 = doc1.NewText("");
    XMLText* text2 = doc1.NewText("");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test that ShallowEqual returns false when comparing XMLText with XMLComment
TEST_F(XMLTextShallowEqualTest_195, CompareWithCommentReturnsFalse_195) {
    doc1.Parse("<root>Hello</root>");
    doc2.Parse("<root><!-- Hello --></root>");

    const XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();
    const XMLNode* comment2 = doc2.FirstChildElement("root")->FirstChild();

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(comment2, nullptr);
    ASSERT_NE(comment2->ToComment(), nullptr);
    EXPECT_FALSE(text1->ShallowEqual(comment2));
}

// Test that ShallowEqual works with text nodes created via NewText
TEST_F(XMLTextShallowEqualTest_195, NewTextNodesWithSameValue_195) {
    XMLText* text1 = doc1.NewText("TestValue");
    XMLText* text2 = doc1.NewText("TestValue");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test that ShallowEqual returns false for NewText nodes with different values
TEST_F(XMLTextShallowEqualTest_195, NewTextNodesWithDifferentValues_195) {
    XMLText* text1 = doc1.NewText("Value1");
    XMLText* text2 = doc1.NewText("Value2");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(text2));
}

// Test ShallowEqual with text that has special characters
TEST_F(XMLTextShallowEqualTest_195, SpecialCharactersEqual_195) {
    XMLText* text1 = doc1.NewText("Hello & World < > \" '");
    XMLText* text2 = doc1.NewText("Hello & World < > \" '");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test ShallowEqual with text nodes from different documents
TEST_F(XMLTextShallowEqualTest_195, TextNodesFromDifferentDocsSameValue_195) {
    XMLText* text1 = doc1.NewText("CrossDoc");
    XMLText* text2 = doc2.NewText("CrossDoc");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test ShallowEqual with text nodes from different documents with different values
TEST_F(XMLTextShallowEqualTest_195, TextNodesFromDifferentDocsDifferentValue_195) {
    XMLText* text1 = doc1.NewText("Value1");
    XMLText* text2 = doc2.NewText("Value2");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(text2));
}

// Test ShallowEqual comparing XMLText with XMLDeclaration
TEST_F(XMLTextShallowEqualTest_195, CompareWithDeclarationReturnsFalse_195) {
    doc1.Parse("<root>text</root>");
    doc2.Parse("<?xml version=\"1.0\"?><root/>");

    const XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();
    const XMLNode* decl = doc2.FirstChild();

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(decl, nullptr);
    ASSERT_NE(decl->ToDeclaration(), nullptr);
    EXPECT_FALSE(text1->ShallowEqual(decl));
}

// Test ShallowEqual with CData text node vs regular text node with same value
TEST_F(XMLTextShallowEqualTest_195, CDataVsRegularTextSameValue_195) {
    // Both have the same string value. ShallowEqual only checks Value(), not CData flag.
    XMLText* text1 = doc1.NewText("data");
    XMLText* text2 = doc1.NewText("data");
    text2->SetCData(true);

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    // ShallowEqual only compares if both are text and have the same Value()
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test ShallowEqual symmetry
TEST_F(XMLTextShallowEqualTest_195, SymmetryCheck_195) {
    XMLText* text1 = doc1.NewText("symmetric");
    XMLText* text2 = doc2.NewText("symmetric");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
    EXPECT_TRUE(text2->ShallowEqual(text1));
}

// Test ShallowEqual symmetry for non-equal
TEST_F(XMLTextShallowEqualTest_195, SymmetryCheckNotEqual_195) {
    XMLText* text1 = doc1.NewText("aaa");
    XMLText* text2 = doc2.NewText("bbb");

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(text2));
    EXPECT_FALSE(text2->ShallowEqual(text1));
}

// Test with long text value
TEST_F(XMLTextShallowEqualTest_195, LongTextValuesEqual_195) {
    std::string longStr(10000, 'x');
    XMLText* text1 = doc1.NewText(longStr.c_str());
    XMLText* text2 = doc2.NewText(longStr.c_str());

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test with long text values that differ by one character
TEST_F(XMLTextShallowEqualTest_195, LongTextValuesDifferByOne_195) {
    std::string longStr1(10000, 'x');
    std::string longStr2 = longStr1;
    longStr2[9999] = 'y';
    
    XMLText* text1 = doc1.NewText(longStr1.c_str());
    XMLText* text2 = doc2.NewText(longStr2.c_str());

    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(text2));
}
