#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Forward declarations for helper functions used by CompareSubtrees
extern bool CompareSubtrees(const XMP_Node& leftNode, const XMP_Node& rightNode);
extern const XMP_Node* FindConstQualifier(const XMP_Node* node, XMP_StringPtr qualName);
extern const XMP_Node* FindConstChild(const XMP_Node* node, XMP_StringPtr childName);
extern XMP_Index LookupLangItem(const XMP_Node* arrayNode, const XMP_VarString& lang);

// Helper to clean up nodes (children and qualifiers)
static void CleanupNode(XMP_Node* node) {
    for (size_t i = 0; i < node->children.size(); ++i) {
        CleanupNode(node->children[i]);
        delete node->children[i];
    }
    node->children.clear();
    for (size_t i = 0; i < node->qualifiers.size(); ++i) {
        CleanupNode(node->qualifiers[i]);
        delete node->qualifiers[i];
    }
    node->qualifiers.clear();
}

class CompareSubtreesTest_1902 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup is handled per test
    }
};

// Test: Two identical leaf nodes with same value and options
TEST_F(CompareSubtreesTest_1902, IdenticalLeafNodes_1902) {
    XMP_Node left(nullptr, "prop", "value", 0);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    // parent is nullptr, so it will use the schema/struct child comparison path
    // But with no children, it should return true
    EXPECT_TRUE(CompareSubtrees(left, right));
}

// Test: Different values should return false
TEST_F(CompareSubtreesTest_1902, DifferentValues_1902) {
    XMP_Node left(nullptr, "prop", "value1", 0);
    XMP_Node right(nullptr, "prop", "value2", 0);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
}

// Test: Different options should return false
TEST_F(CompareSubtreesTest_1902, DifferentOptions_1902) {
    XMP_Node left(nullptr, "prop", "value", kXMP_PropValueIsURI);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
}

// Test: Different number of children should return false
TEST_F(CompareSubtreesTest_1902, DifferentChildCount_1902) {
    XMP_Node left(nullptr, "prop", "value", 0);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    XMP_Node* leftChild = new XMP_Node(&left, "child1", "val", 0);
    left.children.push_back(leftChild);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Different number of qualifiers should return false
TEST_F(CompareSubtreesTest_1902, DifferentQualifierCount_1902) {
    XMP_Node left(nullptr, "prop", "value", 0);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    XMP_Node* leftQual = new XMP_Node(&left, "qual1", "qval", kXMP_PropIsQualifier);
    left.qualifiers.push_back(leftQual);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Nodes with same qualifiers (same name and value)
TEST_F(CompareSubtreesTest_1902, SameQualifiers_1902) {
    XMP_Node left(nullptr, "prop", "value", 0);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    XMP_Node* leftQual = new XMP_Node(&left, "qual1", "qval", kXMP_PropIsQualifier);
    left.qualifiers.push_back(leftQual);
    
    XMP_Node* rightQual = new XMP_Node(&right, "qual1", "qval", kXMP_PropIsQualifier);
    right.qualifiers.push_back(rightQual);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Qualifiers with different values should return false
TEST_F(CompareSubtreesTest_1902, QualifiersDifferentValues_1902) {
    XMP_Node left(nullptr, "prop", "value", 0);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    XMP_Node* leftQual = new XMP_Node(&left, "qual1", "qval1", kXMP_PropIsQualifier);
    left.qualifiers.push_back(leftQual);
    
    XMP_Node* rightQual = new XMP_Node(&right, "qual1", "qval2", kXMP_PropIsQualifier);
    right.qualifiers.push_back(rightQual);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Schema nodes with same children (matched by name)
TEST_F(CompareSubtreesTest_1902, SchemaNodesSameChildren_1902) {
    // parent == nullptr triggers the schema/struct path
    XMP_Node left(nullptr, "schema", "", kXMP_SchemaNode);
    XMP_Node right(nullptr, "schema", "", kXMP_SchemaNode);
    
    XMP_Node* leftChild = new XMP_Node(&left, "child1", "val1", 0);
    left.children.push_back(leftChild);
    
    XMP_Node* rightChild = new XMP_Node(&right, "child1", "val1", 0);
    right.children.push_back(rightChild);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Schema nodes with different child values
TEST_F(CompareSubtreesTest_1902, SchemaNodesDifferentChildValues_1902) {
    XMP_Node left(nullptr, "schema", "", kXMP_SchemaNode);
    XMP_Node right(nullptr, "schema", "", kXMP_SchemaNode);
    
    XMP_Node* leftChild = new XMP_Node(&left, "child1", "val1", 0);
    left.children.push_back(leftChild);
    
    XMP_Node* rightChild = new XMP_Node(&right, "child1", "val2", 0);
    right.children.push_back(rightChild);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Struct nodes with same children (matched by name)
TEST_F(CompareSubtreesTest_1902, StructNodesSameChildren_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "struct", "", kXMP_PropValueIsStruct);
    XMP_Node right(&parent, "struct", "", kXMP_PropValueIsStruct);
    
    XMP_Node* leftChild = new XMP_Node(&left, "field1", "val1", 0);
    left.children.push_back(leftChild);
    
    XMP_Node* rightChild = new XMP_Node(&right, "field1", "val1", 0);
    right.children.push_back(rightChild);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Struct nodes where right is missing a child by name
TEST_F(CompareSubtreesTest_1902, StructNodesMissingChild_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "struct", "", kXMP_PropValueIsStruct);
    XMP_Node right(&parent, "struct", "", kXMP_PropValueIsStruct);
    
    XMP_Node* leftChild = new XMP_Node(&left, "field1", "val1", 0);
    left.children.push_back(leftChild);
    
    XMP_Node* rightChild = new XMP_Node(&right, "field2", "val1", 0);
    right.children.push_back(rightChild);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Array nodes (non-alt-text) with same children by position
TEST_F(CompareSubtreesTest_1902, ArrayNodesSameChildrenByPosition_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "array", "", kXMP_PropValueIsArray);
    XMP_Node right(&parent, "array", "", kXMP_PropValueIsArray);
    
    XMP_Node* leftChild1 = new XMP_Node(&left, "item1", "val1", 0);
    XMP_Node* leftChild2 = new XMP_Node(&left, "item2", "val2", 0);
    left.children.push_back(leftChild1);
    left.children.push_back(leftChild2);
    
    XMP_Node* rightChild1 = new XMP_Node(&right, "item1", "val1", 0);
    XMP_Node* rightChild2 = new XMP_Node(&right, "item2", "val2", 0);
    right.children.push_back(rightChild1);
    right.children.push_back(rightChild2);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Array nodes with different values at same position
TEST_F(CompareSubtreesTest_1902, ArrayNodesDifferentChildAtPosition_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "array", "", kXMP_PropValueIsArray);
    XMP_Node right(&parent, "array", "", kXMP_PropValueIsArray);
    
    XMP_Node* leftChild = new XMP_Node(&left, "item1", "val1", 0);
    left.children.push_back(leftChild);
    
    XMP_Node* rightChild = new XMP_Node(&right, "item1", "val2", 0);
    right.children.push_back(rightChild);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: AltText array nodes with same lang items
TEST_F(CompareSubtreesTest_1902, AltTextSameLangItems_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "alttext", "", kXMP_PropArrayIsAltText | kXMP_PropValueIsArray);
    XMP_Node right(&parent, "alttext", "", kXMP_PropArrayIsAltText | kXMP_PropValueIsArray);
    
    // Left child with xml:lang qualifier
    XMP_Node* leftChild = new XMP_Node(&left, "item", "English Text", 0);
    XMP_Node* leftLangQual = new XMP_Node(leftChild, "xml:lang", "en", kXMP_PropIsQualifier);
    leftChild->qualifiers.push_back(leftLangQual);
    left.children.push_back(leftChild);
    
    // Right child with xml:lang qualifier
    XMP_Node* rightChild = new XMP_Node(&right, "item", "English Text", 0);
    XMP_Node* rightLangQual = new XMP_Node(rightChild, "xml:lang", "en", kXMP_PropIsQualifier);
    rightChild->qualifiers.push_back(rightLangQual);
    right.children.push_back(rightChild);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: AltText array nodes with different lang values
TEST_F(CompareSubtreesTest_1902, AltTextDifferentLangValues_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "alttext", "", kXMP_PropArrayIsAltText | kXMP_PropValueIsArray);
    XMP_Node right(&parent, "alttext", "", kXMP_PropArrayIsAltText | kXMP_PropValueIsArray);
    
    // Left child with xml:lang "en"
    XMP_Node* leftChild = new XMP_Node(&left, "item", "English Text", 0);
    XMP_Node* leftLangQual = new XMP_Node(leftChild, "xml:lang", "en", kXMP_PropIsQualifier);
    leftChild->qualifiers.push_back(leftLangQual);
    left.children.push_back(leftChild);
    
    // Right child with xml:lang "en" but different text
    XMP_Node* rightChild = new XMP_Node(&right, "item", "Different Text", 0);
    XMP_Node* rightLangQual = new XMP_Node(rightChild, "xml:lang", "en", kXMP_PropIsQualifier);
    rightChild->qualifiers.push_back(rightLangQual);
    right.children.push_back(rightChild);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: AltText array where right node is missing a language
TEST_F(CompareSubtreesTest_1902, AltTextMissingLang_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "alttext", "", kXMP_PropArrayIsAltText | kXMP_PropValueIsArray);
    XMP_Node right(&parent, "alttext", "", kXMP_PropArrayIsAltText | kXMP_PropValueIsArray);
    
    // Left has "en" and "fr"
    XMP_Node* leftChild1 = new XMP_Node(&left, "item", "English", 0);
    XMP_Node* leftLang1 = new XMP_Node(leftChild1, "xml:lang", "en", kXMP_PropIsQualifier);
    leftChild1->qualifiers.push_back(leftLang1);
    left.children.push_back(leftChild1);
    
    XMP_Node* leftChild2 = new XMP_Node(&left, "item", "French", 0);
    XMP_Node* leftLang2 = new XMP_Node(leftChild2, "xml:lang", "fr", kXMP_PropIsQualifier);
    leftChild2->qualifiers.push_back(leftLang2);
    left.children.push_back(leftChild2);
    
    // Right has "en" and "de" (missing "fr")
    XMP_Node* rightChild1 = new XMP_Node(&right, "item", "English", 0);
    XMP_Node* rightLang1 = new XMP_Node(rightChild1, "xml:lang", "en", kXMP_PropIsQualifier);
    rightChild1->qualifiers.push_back(rightLang1);
    right.children.push_back(rightChild1);
    
    XMP_Node* rightChild2 = new XMP_Node(&right, "item", "German", 0);
    XMP_Node* rightLang2 = new XMP_Node(rightChild2, "xml:lang", "de", kXMP_PropIsQualifier);
    rightChild2->qualifiers.push_back(rightLang2);
    right.children.push_back(rightChild2);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Empty nodes should be equal
TEST_F(CompareSubtreesTest_1902, EmptyNodes_1902) {
    XMP_Node left(nullptr, "prop", "", 0);
    XMP_Node right(nullptr, "prop", "", 0);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
}

// Test: Parent is null (root-level comparison) with children matched by name
TEST_F(CompareSubtreesTest_1902, RootLevelWithChildren_1902) {
    // parent == nullptr triggers name-based child matching
    XMP_Node left(nullptr, "root", "", 0);
    XMP_Node right(nullptr, "root", "", 0);
    
    XMP_Node* leftChild1 = new XMP_Node(&left, "childA", "valA", 0);
    XMP_Node* leftChild2 = new XMP_Node(&left, "childB", "valB", 0);
    left.children.push_back(leftChild1);
    left.children.push_back(leftChild2);
    
    // Right has same children but in different order (since it uses FindConstChild by name)
    XMP_Node* rightChild1 = new XMP_Node(&right, "childB", "valB", 0);
    XMP_Node* rightChild2 = new XMP_Node(&right, "childA", "valA", 0);
    right.children.push_back(rightChild1);
    right.children.push_back(rightChild2);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Multiple qualifiers, one differs
TEST_F(CompareSubtreesTest_1902, MultipleQualifiersOneDiffers_1902) {
    XMP_Node left(nullptr, "prop", "value", 0);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    XMP_Node* leftQual1 = new XMP_Node(&left, "qual1", "qval1", kXMP_PropIsQualifier);
    XMP_Node* leftQual2 = new XMP_Node(&left, "qual2", "qval2", kXMP_PropIsQualifier);
    left.qualifiers.push_back(leftQual1);
    left.qualifiers.push_back(leftQual2);
    
    XMP_Node* rightQual1 = new XMP_Node(&right, "qual1", "qval1", kXMP_PropIsQualifier);
    XMP_Node* rightQual2 = new XMP_Node(&right, "qual2", "different", kXMP_PropIsQualifier);
    right.qualifiers.push_back(rightQual1);
    right.qualifiers.push_back(rightQual2);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Ordered array nodes compared by position
TEST_F(CompareSubtreesTest_1902, OrderedArrayByPosition_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "array", "", kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray);
    XMP_Node right(&parent, "array", "", kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray);
    
    XMP_Node* leftChild1 = new XMP_Node(&left, "item[1]", "first", 0);
    XMP_Node* leftChild2 = new XMP_Node(&left, "item[2]", "second", 0);
    left.children.push_back(leftChild1);
    left.children.push_back(leftChild2);
    
    XMP_Node* rightChild1 = new XMP_Node(&right, "item[1]", "first", 0);
    XMP_Node* rightChild2 = new XMP_Node(&right, "item[2]", "second", 0);
    right.children.push_back(rightChild1);
    right.children.push_back(rightChild2);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Ordered array with swapped children should fail (positional comparison)
TEST_F(CompareSubtreesTest_1902, OrderedArraySwappedChildren_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "array", "", kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray);
    XMP_Node right(&parent, "array", "", kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray);
    
    XMP_Node* leftChild1 = new XMP_Node(&left, "item[1]", "first", 0);
    XMP_Node* leftChild2 = new XMP_Node(&left, "item[2]", "second", 0);
    left.children.push_back(leftChild1);
    left.children.push_back(leftChild2);
    
    // Swapped order
    XMP_Node* rightChild1 = new XMP_Node(&right, "item[1]", "second", 0);
    XMP_Node* rightChild2 = new XMP_Node(&right, "item[2]", "first", 0);
    right.children.push_back(rightChild1);
    right.children.push_back(rightChild2);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Nested struct comparison
TEST_F(CompareSubtreesTest_1902, NestedStructComparison_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "struct", "", kXMP_PropValueIsStruct);
    XMP_Node right(&parent, "struct", "", kXMP_PropValueIsStruct);
    
    // Left: struct with a nested struct child
    XMP_Node* leftChild = new XMP_Node(&left, "nested", "", kXMP_PropValueIsStruct);
    XMP_Node* leftGrandChild = new XMP_Node(leftChild, "field", "deep_value", 0);
    leftChild->children.push_back(leftGrandChild);
    left.children.push_back(leftChild);
    
    // Right: same structure
    XMP_Node* rightChild = new XMP_Node(&right, "nested", "", kXMP_PropValueIsStruct);
    XMP_Node* rightGrandChild = new XMP_Node(rightChild, "field", "deep_value", 0);
    rightChild->children.push_back(rightGrandChild);
    right.children.push_back(rightChild);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Nested struct with different deep value
TEST_F(CompareSubtreesTest_1902, NestedStructDifferentDeepValue_1902) {
    XMP_Node parent(nullptr, "root", "", 0);
    XMP_Node left(&parent, "struct", "", kXMP_PropValueIsStruct);
    XMP_Node right(&parent, "struct", "", kXMP_PropValueIsStruct);
    
    XMP_Node* leftChild = new XMP_Node(&left, "nested", "", kXMP_PropValueIsStruct);
    XMP_Node* leftGrandChild = new XMP_Node(leftChild, "field", "value1", 0);
    leftChild->children.push_back(leftGrandChild);
    left.children.push_back(leftChild);
    
    XMP_Node* rightChild = new XMP_Node(&right, "nested", "", kXMP_PropValueIsStruct);
    XMP_Node* rightGrandChild = new XMP_Node(rightChild, "field", "value2", 0);
    rightChild->children.push_back(rightGrandChild);
    right.children.push_back(rightChild);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Qualifier name not found in right node
TEST_F(CompareSubtreesTest_1902, QualifierNotFoundInRight_1902) {
    XMP_Node left(nullptr, "prop", "value", 0);
    XMP_Node right(nullptr, "prop", "value", 0);
    
    XMP_Node* leftQual = new XMP_Node(&left, "qual1", "qval", kXMP_PropIsQualifier);
    left.qualifiers.push_back(leftQual);
    
    XMP_Node* rightQual = new XMP_Node(&right, "qual_other", "qval", kXMP_PropIsQualifier);
    right.qualifiers.push_back(rightQual);
    
    EXPECT_FALSE(CompareSubtrees(left, right));
    
    CleanupNode(&left);
    CleanupNode(&right);
}

// Test: Both nodes have empty children and qualifiers
TEST_F(CompareSubtreesTest_1902, BothEmptyChildrenAndQualifiers_1902) {
    XMP_Node left(nullptr, "prop", "same_value", 0);
    XMP_Node right(nullptr, "prop", "same_value", 0);
    
    EXPECT_TRUE(CompareSubtrees(left, right));
}

// Test: Same node compared to itself
TEST_F(CompareSubtreesTest_1902, SameNodeSelfComparison_1902) {
    XMP_Node node(nullptr, "prop", "value", 0);
    
    EXPECT_TRUE(CompareSubtrees(node, node));
}
