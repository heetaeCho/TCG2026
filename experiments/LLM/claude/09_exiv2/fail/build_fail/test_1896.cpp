#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Forward declaration of the function under test
XMP_Node * FindQualifierNode ( XMP_Node * parent, XMP_StringPtr qualName, bool createNodes, XMP_NodePtrPos * ptrPos = 0 );

// We need kXMP_NewImplicitNode - it's typically defined in the XMP SDK internals
#ifndef kXMP_NewImplicitNode
#define kXMP_NewImplicitNode 0x20000000
#endif

class FindQualifierNodeTest_1896 : public ::testing::Test {
protected:
    void SetUp() override {
        parent = new XMP_Node(nullptr, "testParent", 0);
    }

    void TearDown() override {
        delete parent;
    }

    XMP_Node* parent;
};

// Test: Finding a qualifier that doesn't exist without creating nodes should return nullptr
TEST_F(FindQualifierNodeTest_1896, ReturnsNullWhenQualNotFoundAndCreateNodesFalse_1896) {
    XMP_Node* result = FindQualifierNode(parent, "nonexistent:qual", false);
    EXPECT_EQ(result, nullptr);
}

// Test: Finding a qualifier that doesn't exist with createNodes=true should create and return a new node
TEST_F(FindQualifierNodeTest_1896, CreatesNodeWhenNotFoundAndCreateNodesTrue_1896) {
    XMP_Node* result = FindQualifierNode(parent, "test:qualifier", true);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "test:qualifier");
    EXPECT_EQ(result->parent, parent);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
    EXPECT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0], result);
}

// Test: Finding an existing qualifier should return it
TEST_F(FindQualifierNodeTest_1896, FindsExistingQualifier_1896) {
    XMP_Node* qual = new XMP_Node(parent, "existing:qual", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(qual);

    XMP_Node* result = FindQualifierNode(parent, "existing:qual", false);
    EXPECT_EQ(result, qual);
}

// Test: Finding an existing qualifier with ptrPos should set ptrPos correctly
TEST_F(FindQualifierNodeTest_1896, FindsExistingQualifierWithPtrPos_1896) {
    XMP_Node* qual = new XMP_Node(parent, "existing:qual", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(qual);

    XMP_NodePtrPos pos;
    XMP_Node* result = FindQualifierNode(parent, "existing:qual", false, &pos);
    EXPECT_EQ(result, qual);
    EXPECT_EQ(*pos, qual);
}

// Test: Creating an xml:lang qualifier should set kXMP_PropHasLang and place it first
TEST_F(FindQualifierNodeTest_1896, CreatesLangQualifierFirst_1896) {
    // First add a regular qualifier
    XMP_Node* regularQual = new XMP_Node(parent, "test:regular", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(regularQual);
    parent->options |= kXMP_PropHasQualifiers;

    XMP_Node* result = FindQualifierNode(parent, "xml:lang", true);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
    // xml:lang should be inserted at the beginning
    EXPECT_EQ(parent->qualifiers[0], result);
    EXPECT_EQ(parent->qualifiers[1], regularQual);
}

// Test: Creating an rdf:type qualifier should set kXMP_PropHasType
TEST_F(FindQualifierNodeTest_1896, CreatesTypeQualifier_1896) {
    XMP_Node* result = FindQualifierNode(parent, "rdf:type", true);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(parent->options & kXMP_PropHasType);
}

// Test: When both lang and type exist, type should be after lang
TEST_F(FindQualifierNodeTest_1896, TypeGoesAfterLang_1896) {
    // Create lang first
    XMP_Node* langNode = FindQualifierNode(parent, "xml:lang", true);
    ASSERT_NE(langNode, nullptr);

    // Now create type
    XMP_Node* typeNode = FindQualifierNode(parent, "rdf:type", true);
    ASSERT_NE(typeNode, nullptr);

    ASSERT_GE(parent->qualifiers.size(), 2u);
    EXPECT_EQ(parent->qualifiers[0], langNode);
    EXPECT_EQ(parent->qualifiers[1], typeNode);
}

// Test: rdf:type without lang goes first
TEST_F(FindQualifierNodeTest_1896, TypeGoesFirstWhenNoLang_1896) {
    // Add a regular qualifier first
    XMP_Node* regularQual = new XMP_Node(parent, "test:regular", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(regularQual);
    parent->options |= kXMP_PropHasQualifiers;

    // Create type qualifier
    XMP_Node* typeNode = FindQualifierNode(parent, "rdf:type", true);
    ASSERT_NE(typeNode, nullptr);

    EXPECT_EQ(parent->qualifiers[0], typeNode);
    EXPECT_EQ(parent->qualifiers[1], regularQual);
}

// Test: Creating a node with ptrPos should set ptrPos to the new node's position
TEST_F(FindQualifierNodeTest_1896, CreateNodeSetsPtrPos_1896) {
    XMP_NodePtrPos pos;
    XMP_Node* result = FindQualifierNode(parent, "test:newqual", true, &pos);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*pos, result);
}

// Test: Searching among multiple qualifiers returns the correct one
TEST_F(FindQualifierNodeTest_1896, FindsCorrectAmongMultipleQualifiers_1896) {
    XMP_Node* qual1 = new XMP_Node(parent, "test:qual1", kXMP_PropIsQualifier);
    XMP_Node* qual2 = new XMP_Node(parent, "test:qual2", kXMP_PropIsQualifier);
    XMP_Node* qual3 = new XMP_Node(parent, "test:qual3", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(qual1);
    parent->qualifiers.push_back(qual2);
    parent->qualifiers.push_back(qual3);

    XMP_Node* result = FindQualifierNode(parent, "test:qual2", false);
    EXPECT_EQ(result, qual2);
}

// Test: Searching for non-existent qualifier among multiple returns nullptr
TEST_F(FindQualifierNodeTest_1896, ReturnsNullForNonExistentAmongMultiple_1896) {
    XMP_Node* qual1 = new XMP_Node(parent, "test:qual1", kXMP_PropIsQualifier);
    XMP_Node* qual2 = new XMP_Node(parent, "test:qual2", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(qual1);
    parent->qualifiers.push_back(qual2);

    XMP_Node* result = FindQualifierNode(parent, "test:qual3", false);
    EXPECT_EQ(result, nullptr);
}

// Test: Passing nullptr for ptrPos should work fine
TEST_F(FindQualifierNodeTest_1896, NullPtrPosWorksForExisting_1896) {
    XMP_Node* qual = new XMP_Node(parent, "test:qual", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(qual);

    XMP_Node* result = FindQualifierNode(parent, "test:qual", false, nullptr);
    EXPECT_EQ(result, qual);
}

// Test: Created qualifier node should have kXMP_PropIsQualifier option
TEST_F(FindQualifierNodeTest_1896, CreatedNodeHasQualifierOption_1896) {
    XMP_Node* result = FindQualifierNode(parent, "test:newqual", true);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->options & kXMP_PropIsQualifier);
}

// Test: Created qualifier node should have kXMP_NewImplicitNode option
TEST_F(FindQualifierNodeTest_1896, CreatedNodeHasImplicitNodeOption_1896) {
    XMP_Node* result = FindQualifierNode(parent, "test:newqual", true);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->options & kXMP_NewImplicitNode);
}

// Test: Empty qualifiers list and createNodes=false returns nullptr
TEST_F(FindQualifierNodeTest_1896, EmptyQualifiersReturnNull_1896) {
    EXPECT_TRUE(parent->qualifiers.empty());
    XMP_Node* result = FindQualifierNode(parent, "test:qual", false);
    EXPECT_EQ(result, nullptr);
}

// Test: Regular qualifier appended to end when qualifiers exist
TEST_F(FindQualifierNodeTest_1896, RegularQualAppendedToEnd_1896) {
    XMP_Node* qual1 = new XMP_Node(parent, "test:qual1", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(qual1);
    parent->options |= kXMP_PropHasQualifiers;

    XMP_Node* result = FindQualifierNode(parent, "test:qual2", true);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(parent->qualifiers.size(), 2u);
    EXPECT_EQ(parent->qualifiers[0], qual1);
    EXPECT_EQ(parent->qualifiers[1], result);
}

// Test: Creating lang qualifier with ptrPos sets correct position
TEST_F(FindQualifierNodeTest_1896, LangQualifierPtrPosCorrect_1896) {
    // Add a regular qualifier first
    XMP_Node* regularQual = new XMP_Node(parent, "test:regular", kXMP_PropIsQualifier);
    parent->qualifiers.push_back(regularQual);
    parent->options |= kXMP_PropHasQualifiers;

    XMP_NodePtrPos pos;
    XMP_Node* result = FindQualifierNode(parent, "xml:lang", true, &pos);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*pos, result);
    EXPECT_EQ(parent->qualifiers[0], result);
}

// Test: Adding lang, type, and regular qualifier produces correct ordering
TEST_F(FindQualifierNodeTest_1896, FullOrderingLangTypeRegular_1896) {
    // Add regular first
    XMP_Node* regular = FindQualifierNode(parent, "test:regular", true);
    ASSERT_NE(regular, nullptr);

    // Add type
    XMP_Node* typeNode = FindQualifierNode(parent, "rdf:type", true);
    ASSERT_NE(typeNode, nullptr);

    // Add lang
    XMP_Node* langNode = FindQualifierNode(parent, "xml:lang", true);
    ASSERT_NE(langNode, nullptr);

    ASSERT_EQ(parent->qualifiers.size(), 3u);
    EXPECT_EQ(parent->qualifiers[0], langNode);
    EXPECT_EQ(parent->qualifiers[1], typeNode);
    EXPECT_EQ(parent->qualifiers[2], regular);
}

// Test: Finding the same qualifier twice returns the same node
TEST_F(FindQualifierNodeTest_1896, FindingSameQualifierTwiceReturnsSameNode_1896) {
    XMP_Node* result1 = FindQualifierNode(parent, "test:qual", true);
    XMP_Node* result2 = FindQualifierNode(parent, "test:qual", false);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(parent->qualifiers.size(), 1u);
}

// Test: Parent options are not cleared when adding qualifiers
TEST_F(FindQualifierNodeTest_1896, ParentOptionsPreserved_1896) {
    parent->options = kXMP_PropValueIsStruct;
    FindQualifierNode(parent, "test:qual", true);
    EXPECT_TRUE(parent->options & kXMP_PropValueIsStruct);
    EXPECT_TRUE(parent->options & kXMP_PropHasQualifiers);
}

// Test: Creating xml:lang qualifier when empty list just pushes back
TEST_F(FindQualifierNodeTest_1896, LangOnEmptyListPushesBack_1896) {
    EXPECT_TRUE(parent->qualifiers.empty());
    XMP_Node* langNode = FindQualifierNode(parent, "xml:lang", true);
    ASSERT_NE(langNode, nullptr);
    EXPECT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0], langNode);
    EXPECT_TRUE(parent->options & kXMP_PropHasLang);
}

// Test: Creating rdf:type qualifier when empty list just pushes back
TEST_F(FindQualifierNodeTest_1896, TypeOnEmptyListPushesBack_1896) {
    EXPECT_TRUE(parent->qualifiers.empty());
    XMP_Node* typeNode = FindQualifierNode(parent, "rdf:type", true);
    ASSERT_NE(typeNode, nullptr);
    EXPECT_EQ(parent->qualifiers.size(), 1u);
    EXPECT_EQ(parent->qualifiers[0], typeNode);
    EXPECT_TRUE(parent->options & kXMP_PropHasType);
}
