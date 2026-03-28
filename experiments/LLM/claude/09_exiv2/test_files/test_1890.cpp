#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Include necessary headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// Since DeleteSubtree is static in the .cpp file, we include it to get access
// This is a common technique for testing static functions
#define static  // temporarily remove static linkage for testing
#include "XMPCore_Impl.cpp"
#undef static

// If the above doesn't work, we provide a forward declaration
// extern void DeleteSubtree(XMP_NodePtrPos rootNodePos);

class DeleteSubtreeTest_1890 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Deleting a regular child node (not a qualifier) removes it from parent's children
TEST_F(DeleteSubtreeTest_1890, DeleteRegularChildRemovesFromParentChildren_1890) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&parent, "child", 0);
    parent.children.push_back(child);

    XMP_NodePtrPos pos = parent.children.begin();
    DeleteSubtree(pos);

    EXPECT_TRUE(parent.children.empty());
}

// Test: Deleting a qualifier node removes it from parent's qualifiers
TEST_F(DeleteSubtreeTest_1890, DeleteQualifierRemovesFromParentQualifiers_1890) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers);
    XMP_Node* qual = new XMP_Node(&parent, "someQual", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(qual);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_TRUE(parent.qualifiers.empty());
    // kXMP_PropHasQualifiers should be cleared since qualifiers is now empty
    EXPECT_FALSE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Deleting one qualifier when multiple exist keeps kXMP_PropHasQualifiers set
TEST_F(DeleteSubtreeTest_1890, DeleteOneQualifierOfManyKeepsHasQualifiersFlag_1890) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers);
    XMP_Node* qual1 = new XMP_Node(&parent, "qual1", kXMP_PropIsQualifier);
    XMP_Node* qual2 = new XMP_Node(&parent, "qual2", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(qual1);
    parent.qualifiers.push_back(qual2);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_EQ(parent.qualifiers.size(), 1u);
    EXPECT_TRUE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Deleting xml:lang qualifier clears kXMP_PropHasLang flag
TEST_F(DeleteSubtreeTest_1890, DeleteXmlLangQualifierClearsHasLangFlag_1890) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers | kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(&parent, "xml:lang", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(langQual);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_TRUE(parent.qualifiers.empty());
    EXPECT_FALSE(parent.options & kXMP_PropHasLang);
    EXPECT_FALSE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Deleting rdf:type qualifier clears kXMP_PropHasType flag
TEST_F(DeleteSubtreeTest_1890, DeleteRdfTypeQualifierClearsHasTypeFlag_1890) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers | kXMP_PropHasType);
    XMP_Node* typeQual = new XMP_Node(&parent, "rdf:type", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(typeQual);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_TRUE(parent.qualifiers.empty());
    EXPECT_FALSE(parent.options & kXMP_PropHasType);
    EXPECT_FALSE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Deleting a regular child does not affect parent options
TEST_F(DeleteSubtreeTest_1890, DeleteRegularChildDoesNotAffectParentOptions_1890) {
    XMP_OptionBits originalOptions = kXMP_PropHasQualifiers | kXMP_PropHasLang;
    XMP_Node parent(nullptr, "parent", originalOptions);
    XMP_Node* child = new XMP_Node(&parent, "child", 0);
    parent.children.push_back(child);

    XMP_NodePtrPos pos = parent.children.begin();
    DeleteSubtree(pos);

    EXPECT_EQ(parent.options, originalOptions);
}

// Test: Deleting a child from the middle of children list
TEST_F(DeleteSubtreeTest_1890, DeleteMiddleChildFromChildrenList_1890) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child1 = new XMP_Node(&parent, "child1", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "child2", 0);
    XMP_Node* child3 = new XMP_Node(&parent, "child3", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);
    parent.children.push_back(child3);

    // Delete middle child (child2)
    XMP_NodePtrPos pos = parent.children.begin() + 1;
    DeleteSubtree(pos);

    EXPECT_EQ(parent.children.size(), 2u);
    EXPECT_EQ(parent.children[0]->name, "child1");
    EXPECT_EQ(parent.children[1]->name, "child3");
}

// Test: Deleting a non-lang, non-type qualifier that is last qualifier
TEST_F(DeleteSubtreeTest_1890, DeleteGenericLastQualifierClearsHasQualifiers_1890) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers);
    XMP_Node* qual = new XMP_Node(&parent, "someOtherQual", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(qual);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_TRUE(parent.qualifiers.empty());
    EXPECT_FALSE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Deleting xml:lang qualifier when other qualifiers remain
TEST_F(DeleteSubtreeTest_1890, DeleteXmlLangWithOtherQualifiersRemaining_1890) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers | kXMP_PropHasLang);
    XMP_Node* langQual = new XMP_Node(&parent, "xml:lang", kXMP_PropIsQualifier);
    XMP_Node* otherQual = new XMP_Node(&parent, "otherQual", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(langQual);
    parent.qualifiers.push_back(otherQual);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_EQ(parent.qualifiers.size(), 1u);
    EXPECT_FALSE(parent.options & kXMP_PropHasLang);
    EXPECT_TRUE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Deleting rdf:type qualifier when other qualifiers remain
TEST_F(DeleteSubtreeTest_1890, DeleteRdfTypeWithOtherQualifiersRemaining_1890) {
    XMP_Node parent(nullptr, "parent", kXMP_PropHasQualifiers | kXMP_PropHasType);
    XMP_Node* typeQual = new XMP_Node(&parent, "rdf:type", kXMP_PropIsQualifier);
    XMP_Node* otherQual = new XMP_Node(&parent, "otherQual", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(typeQual);
    parent.qualifiers.push_back(otherQual);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_EQ(parent.qualifiers.size(), 1u);
    EXPECT_FALSE(parent.options & kXMP_PropHasType);
    EXPECT_TRUE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Deleting the last child leaves parent children empty
TEST_F(DeleteSubtreeTest_1890, DeleteLastChildLeavesParentChildrenEmpty_1890) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&parent, "onlyChild", 0);
    parent.children.push_back(child);

    EXPECT_EQ(parent.children.size(), 1u);

    XMP_NodePtrPos pos = parent.children.begin();
    DeleteSubtree(pos);

    EXPECT_TRUE(parent.children.empty());
}

// Test: Deleting first child from list with multiple children
TEST_F(DeleteSubtreeTest_1890, DeleteFirstChildFromMultipleChildren_1890) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child1 = new XMP_Node(&parent, "first", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "second", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);

    XMP_NodePtrPos pos = parent.children.begin();
    DeleteSubtree(pos);

    EXPECT_EQ(parent.children.size(), 1u);
    EXPECT_EQ(parent.children[0]->name, "second");
}

// Test: Deleting last child from list with multiple children
TEST_F(DeleteSubtreeTest_1890, DeleteLastChildFromMultipleChildren_1890) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child1 = new XMP_Node(&parent, "first", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "second", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);

    XMP_NodePtrPos pos = parent.children.begin() + 1;
    DeleteSubtree(pos);

    EXPECT_EQ(parent.children.size(), 1u);
    EXPECT_EQ(parent.children[0]->name, "first");
}

// Test: Parent options with both lang and type, deleting lang qualifier only clears lang
TEST_F(DeleteSubtreeTest_1890, DeleteLangQualPreservesTypeFlag_1890) {
    XMP_Node parent(nullptr, "parent",
                    kXMP_PropHasQualifiers | kXMP_PropHasLang | kXMP_PropHasType);
    XMP_Node* langQual = new XMP_Node(&parent, "xml:lang", kXMP_PropIsQualifier);
    XMP_Node* typeQual = new XMP_Node(&parent, "rdf:type", kXMP_PropIsQualifier);
    parent.qualifiers.push_back(langQual);
    parent.qualifiers.push_back(typeQual);

    XMP_NodePtrPos pos = parent.qualifiers.begin();
    DeleteSubtree(pos);

    EXPECT_EQ(parent.qualifiers.size(), 1u);
    EXPECT_FALSE(parent.options & kXMP_PropHasLang);
    EXPECT_TRUE(parent.options & kXMP_PropHasType);
    EXPECT_TRUE(parent.options & kXMP_PropHasQualifiers);
}

// Test: Node with children subtree - verify the root node and its subtree are deleted
TEST_F(DeleteSubtreeTest_1890, DeleteNodeWithChildrenSubtree_1890) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&parent, "child", 0);
    // Add grandchild to child
    XMP_Node* grandchild = new XMP_Node(child, "grandchild", 0);
    child->children.push_back(grandchild);
    parent.children.push_back(child);

    XMP_NodePtrPos pos = parent.children.begin();
    DeleteSubtree(pos);

    EXPECT_TRUE(parent.children.empty());
    // The delete of child should cascade to grandchild via XMP_Node destructor
}
