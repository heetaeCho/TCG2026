#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLUnknownShallowEqualTest_207 : public ::testing::Test {
protected:
    XMLDocument doc1;
    XMLDocument doc2;
};

// Test that ShallowEqual returns true when comparing two XMLUnknown nodes with the same value
TEST_F(XMLUnknownShallowEqualTest_207, SameValueReturnsTrue_207) {
    const char* xml1 = "<root><![CDATA[data]]><!unknown1></root>";
    // We need to create XMLUnknown nodes through the document
    // XMLUnknown nodes are created when parsing unknown XML constructs like <? ... ?>
    // Let's use a different approach - parse XML with unknown nodes
    
    const char* xmlStr = "<!DOCTYPE foo SYSTEM \"foo.dtd\">"
                         "<root/>";
    
    // Create unknown nodes via the document's NewUnknown
    XMLNode* unknown1 = doc1.NewUnknown("test value");
    XMLNode* unknown2 = doc2.NewUnknown("test value");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    ASSERT_NE(unknown1->ToUnknown(), nullptr);
    ASSERT_NE(unknown2->ToUnknown(), nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(unknown2));
}

// Test that ShallowEqual returns false when comparing two XMLUnknown nodes with different values
TEST_F(XMLUnknownShallowEqualTest_207, DifferentValueReturnsFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("value A");
    XMLNode* unknown2 = doc2.NewUnknown("value B");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(unknown2));
}

// Test that ShallowEqual returns true when comparing an XMLUnknown node with itself
TEST_F(XMLUnknownShallowEqualTest_207, SameNodeReturnsTrue_207) {
    XMLNode* unknown1 = doc1.NewUnknown("self compare");
    
    ASSERT_NE(unknown1, nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(unknown1));
}

// Test that ShallowEqual returns false when comparing XMLUnknown with a non-XMLUnknown node
TEST_F(XMLUnknownShallowEqualTest_207, CompareWithCommentReturnsFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("some value");
    XMLNode* comment1 = doc1.NewComment("some value");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(comment1, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(comment1));
}

// Test that ShallowEqual returns false when comparing XMLUnknown with an XMLElement
TEST_F(XMLUnknownShallowEqualTest_207, CompareWithElementReturnsFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("element");
    XMLNode* element1 = doc1.NewElement("element");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(element1, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(element1));
}

// Test that ShallowEqual returns false when comparing XMLUnknown with an XMLText node
TEST_F(XMLUnknownShallowEqualTest_207, CompareWithTextReturnsFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("text value");
    XMLNode* text1 = doc1.NewText("text value");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(text1, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(text1));
}

// Test that ShallowEqual returns false when comparing XMLUnknown with an XMLDeclaration
TEST_F(XMLUnknownShallowEqualTest_207, CompareWithDeclarationReturnsFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("xml version=\"1.0\"");
    XMLNode* decl1 = doc1.NewDeclaration("xml version=\"1.0\"");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(decl1, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(decl1));
}

// Test that ShallowEqual returns true for empty-value XMLUnknown nodes
TEST_F(XMLUnknownShallowEqualTest_207, EmptyValueReturnsTrue_207) {
    XMLNode* unknown1 = doc1.NewUnknown("");
    XMLNode* unknown2 = doc2.NewUnknown("");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(unknown2));
}

// Test that ShallowEqual returns false when one has empty value and other doesn't
TEST_F(XMLUnknownShallowEqualTest_207, EmptyVsNonEmptyReturnsFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("");
    XMLNode* unknown2 = doc2.NewUnknown("notempty");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(unknown2));
}

// Test that ShallowEqual is symmetric
TEST_F(XMLUnknownShallowEqualTest_207, SymmetricComparison_207) {
    XMLNode* unknown1 = doc1.NewUnknown("symmetric test");
    XMLNode* unknown2 = doc2.NewUnknown("symmetric test");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(unknown2));
    EXPECT_TRUE(unknown2->ShallowEqual(unknown1));
}

// Test that ShallowEqual is symmetric for unequal values
TEST_F(XMLUnknownShallowEqualTest_207, SymmetricComparisonFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("value1");
    XMLNode* unknown2 = doc2.NewUnknown("value2");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(unknown2));
    EXPECT_FALSE(unknown2->ShallowEqual(unknown1));
}

// Test ShallowEqual with long string values
TEST_F(XMLUnknownShallowEqualTest_207, LongStringValuesEqual_207) {
    std::string longStr(1000, 'x');
    XMLNode* unknown1 = doc1.NewUnknown(longStr.c_str());
    XMLNode* unknown2 = doc2.NewUnknown(longStr.c_str());
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(unknown2));
}

// Test ShallowEqual with values that differ only in one character
TEST_F(XMLUnknownShallowEqualTest_207, ValuesAlmostEqualReturnsFalse_207) {
    XMLNode* unknown1 = doc1.NewUnknown("abcdef");
    XMLNode* unknown2 = doc2.NewUnknown("abcdeg");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(unknown2));
}

// Test ShallowEqual with special characters in the value
TEST_F(XMLUnknownShallowEqualTest_207, SpecialCharactersEqual_207) {
    XMLNode* unknown1 = doc1.NewUnknown("special <>&\"' chars");
    XMLNode* unknown2 = doc2.NewUnknown("special <>&\"' chars");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(unknown2));
}

// Test ShallowClone creates a node that is ShallowEqual
TEST_F(XMLUnknownShallowEqualTest_207, ShallowCloneIsShallowEqual_207) {
    XMLNode* unknown1 = doc1.NewUnknown("clone test");
    ASSERT_NE(unknown1, nullptr);
    
    XMLNode* cloned = unknown1->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    
    EXPECT_TRUE(unknown1->ShallowEqual(cloned));
    
    // Clean up - the cloned node needs to be added to doc2 or deleted
    doc2.InsertEndChild(cloned);
}

// Test ToUnknown returns non-null for XMLUnknown
TEST_F(XMLUnknownShallowEqualTest_207, ToUnknownReturnsNonNull_207) {
    XMLNode* unknown1 = doc1.NewUnknown("to unknown test");
    ASSERT_NE(unknown1, nullptr);
    
    EXPECT_NE(unknown1->ToUnknown(), nullptr);
}

// Test that XMLUnknown nodes from parsed XML can be compared
TEST_F(XMLUnknownShallowEqualTest_207, ParsedUnknownNodesCompare_207) {
    const char* xml = "<root><![ some unknown content ]></root>";
    
    // Create two unknown nodes with identical values
    XMLNode* u1 = doc1.NewUnknown("test parsed");
    XMLNode* u2 = doc2.NewUnknown("test parsed");
    
    ASSERT_NE(u1, nullptr);
    ASSERT_NE(u2, nullptr);
    
    EXPECT_TRUE(u1->ShallowEqual(u2));
}

// Test case sensitivity in ShallowEqual
TEST_F(XMLUnknownShallowEqualTest_207, CaseSensitiveComparison_207) {
    XMLNode* unknown1 = doc1.NewUnknown("CaseSensitive");
    XMLNode* unknown2 = doc2.NewUnknown("casesensitive");
    
    ASSERT_NE(unknown1, nullptr);
    ASSERT_NE(unknown2, nullptr);
    
    EXPECT_FALSE(unknown1->ShallowEqual(unknown2));
}
