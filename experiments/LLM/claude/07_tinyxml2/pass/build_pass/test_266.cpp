#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementShallowEqualTest_266 : public ::testing::Test {
protected:
    XMLDocument doc1;
    XMLDocument doc2;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that two elements with the same name and no attributes are ShallowEqual
TEST_F(XMLElementShallowEqualTest_266, SameNameNoAttributes_266) {
    doc1.Parse("<root/>");
    doc2.Parse("<root/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

// Test that two elements with different names are not ShallowEqual
TEST_F(XMLElementShallowEqualTest_266, DifferentNames_266) {
    doc1.Parse("<root/>");
    doc2.Parse("<other/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test that two elements with the same name and same attributes are ShallowEqual
TEST_F(XMLElementShallowEqualTest_266, SameNameSameAttributes_266) {
    doc1.Parse("<root a='1' b='2'/>");
    doc2.Parse("<root a='1' b='2'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

// Test that two elements with the same name but different attribute values are not ShallowEqual
TEST_F(XMLElementShallowEqualTest_266, SameNameDifferentAttributeValues_266) {
    doc1.Parse("<root a='1'/>");
    doc2.Parse("<root a='2'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test that two elements with the same name but different number of attributes are not ShallowEqual
TEST_F(XMLElementShallowEqualTest_266, DifferentNumberOfAttributes_266) {
    doc1.Parse("<root a='1'/>");
    doc2.Parse("<root a='1' b='2'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test the reverse: more attributes on the first element
TEST_F(XMLElementShallowEqualTest_266, MoreAttributesOnFirst_266) {
    doc1.Parse("<root a='1' b='2'/>");
    doc2.Parse("<root a='1'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test that ShallowEqual is symmetric
TEST_F(XMLElementShallowEqualTest_266, Symmetry_266) {
    doc1.Parse("<root a='1' b='2'/>");
    doc2.Parse("<root a='1' b='2'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
    EXPECT_TRUE(elem2->ShallowEqual(elem1));
}

// Test that comparing an element with a non-element node returns false
TEST_F(XMLElementShallowEqualTest_266, CompareWithNonElement_266) {
    doc1.Parse("<root/><!-- comment -->");
    doc2.Parse("<!-- comment -->");
    
    // Insert a comment into a doc so we can compare
    XMLDocument docWithComment;
    docWithComment.Parse("<!-- comment -->");
    
    XMLDocument docWithElement;
    docWithElement.Parse("<root/>");
    
    const XMLElement* elem = docWithElement.RootElement();
    const XMLNode* comment = docWithComment.FirstChild();
    
    ASSERT_NE(elem, nullptr);
    ASSERT_NE(comment, nullptr);
    
    // A comment's ToElement() should return null, so ShallowEqual should return false
    EXPECT_FALSE(elem->ShallowEqual(comment));
}

// Test that ShallowEqual ignores child elements (only compares name and attributes)
TEST_F(XMLElementShallowEqualTest_266, IgnoresChildren_266) {
    doc1.Parse("<root a='1'><child1/></root>");
    doc2.Parse("<root a='1'><child2/><child3/></root>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    // ShallowEqual only checks name and attributes, not children
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

// Test ShallowEqual with empty attribute values
TEST_F(XMLElementShallowEqualTest_266, EmptyAttributeValues_266) {
    doc1.Parse("<root a=''/>");
    doc2.Parse("<root a=''/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

// Test ShallowEqual with one empty attribute and one non-empty
TEST_F(XMLElementShallowEqualTest_266, EmptyVsNonEmptyAttributeValue_266) {
    doc1.Parse("<root a=''/>");
    doc2.Parse("<root a='value'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test ShallowEqual with multiple attributes, all matching
TEST_F(XMLElementShallowEqualTest_266, MultipleAttributesAllMatch_266) {
    doc1.Parse("<root a='1' b='2' c='3'/>");
    doc2.Parse("<root a='1' b='2' c='3'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

// Test ShallowEqual with multiple attributes, last one differs
TEST_F(XMLElementShallowEqualTest_266, MultipleAttributesLastDiffers_266) {
    doc1.Parse("<root a='1' b='2' c='3'/>");
    doc2.Parse("<root a='1' b='2' c='999'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test ShallowEqual comparing element with itself (reflexive)
TEST_F(XMLElementShallowEqualTest_266, Reflexive_266) {
    doc1.Parse("<root a='1' b='2'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    
    EXPECT_TRUE(elem1->ShallowEqual(elem1));
}

// Test that attributes with same values but different names still compare by value
// (ShallowEqual compares attribute values in order, not names)
TEST_F(XMLElementShallowEqualTest_266, DifferentAttributeNamesSameValues_266) {
    doc1.Parse("<root a='val'/>");
    doc2.Parse("<root b='val'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    // The implementation only checks attribute values (not names) in order
    // Both have one attribute with value 'val', so this should be true
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}

// Test with no attributes on first, attributes on second
TEST_F(XMLElementShallowEqualTest_266, NoAttributesVsAttributes_266) {
    doc1.Parse("<root/>");
    doc2.Parse("<root a='1'/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test with attributes on first, no attributes on second
TEST_F(XMLElementShallowEqualTest_266, AttributesVsNoAttributes_266) {
    doc1.Parse("<root a='1'/>");
    doc2.Parse("<root/>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
}

// Test ShallowEqual with elements having text content (text is child, not attribute)
TEST_F(XMLElementShallowEqualTest_266, ElementsWithTextContent_266) {
    doc1.Parse("<root>Hello</root>");
    doc2.Parse("<root>World</root>");
    
    const XMLElement* elem1 = doc1.RootElement();
    const XMLElement* elem2 = doc2.RootElement();
    
    ASSERT_NE(elem1, nullptr);
    ASSERT_NE(elem2, nullptr);
    
    // ShallowEqual should not compare children/text, only name and attributes
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
}
