#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

class XMPNodeTest : public testing::Test {
protected:
    XMP_Node *parentNode;
    XMP_Node *childNode;

    void SetUp() override {
        parentNode = new XMP_Node(nullptr, "parent", 0);
        childNode = new XMP_Node(parentNode, "child", "value", 0);
        parentNode->children.push_back(childNode);
    }

    void TearDown() override {
        delete parentNode;
        delete childNode;
    }
};

TEST_F(XMPNodeTest, DeleteSubtree_RemovesChildNode_1890) {
    // Test the normal case where the child node is deleted
    XMP_NodePtrPos childNodePos = parentNode->children.begin();
    DeleteSubtree(childNodePos);

    // After deletion, the parent should have no children
    ASSERT_TRUE(parentNode->children.empty());
}

TEST_F(XMPNodeTest, DeleteSubtree_RemovesQualifier_1891) {
    // Setup a parent node with a qualifier
    XMP_Node *qualifierNode = new XMP_Node(parentNode, "qualifier", "value", kXMP_PropIsQualifier);
    parentNode->qualifiers.push_back(qualifierNode);

    XMP_NodePtrPos qualifierNodePos = parentNode->qualifiers.begin();
    DeleteSubtree(qualifierNodePos);

    // After deletion, the parent should have no qualifiers
    ASSERT_TRUE(parentNode->qualifiers.empty());
}

TEST_F(XMPNodeTest, DeleteSubtree_UpdatesParentOptions_1892) {
    // Setup a parent node with the kXMP_PropHasQualifiers option set
    parentNode->options |= kXMP_PropHasQualifiers;

    XMP_Node *qualifierNode = new XMP_Node(parentNode, "qualifier", "value", kXMP_PropIsQualifier);
    parentNode->qualifiers.push_back(qualifierNode);

    XMP_NodePtrPos qualifierNodePos = parentNode->qualifiers.begin();
    DeleteSubtree(qualifierNodePos);

    // After deletion, the parent should have the kXMP_PropHasQualifiers option cleared
    ASSERT_FALSE(parentNode->options & kXMP_PropHasQualifiers);
}

TEST_F(XMPNodeTest, DeleteSubtree_DeletesXmlLang_1893) {
    // Test the case where "xml:lang" is deleted and the kXMP_PropHasLang option is cleared
    parentNode->options |= kXMP_PropHasLang;

    XMP_Node *langNode = new XMP_Node(parentNode, "xml:lang", "en", kXMP_PropIsQualifier);
    parentNode->qualifiers.push_back(langNode);

    XMP_NodePtrPos langNodePos = parentNode->qualifiers.begin();
    DeleteSubtree(langNodePos);

    // After deletion, the parent should have the kXMP_PropHasLang option cleared
    ASSERT_FALSE(parentNode->options & kXMP_PropHasLang);
}

TEST_F(XMPNodeTest, DeleteSubtree_DeletesRdfType_1894) {
    // Test the case where "rdf:type" is deleted and the kXMP_PropHasType option is cleared
    parentNode->options |= kXMP_PropHasType;

    XMP_Node *rdfTypeNode = new XMP_Node(parentNode, "rdf:type", "type", kXMP_PropIsQualifier);
    parentNode->qualifiers.push_back(rdfTypeNode);

    XMP_NodePtrPos rdfTypeNodePos = parentNode->qualifiers.begin();
    DeleteSubtree(rdfTypeNodePos);

    // After deletion, the parent should have the kXMP_PropHasType option cleared
    ASSERT_FALSE(parentNode->options & kXMP_PropHasType);
}

TEST_F(XMPNodeTest, DeleteSubtree_ParentWithoutQualifiers_1895) {
    // Test the case where a node is deleted and the parent node no longer has qualifiers
    parentNode->options |= kXMP_PropHasQualifiers;

    XMP_Node *qualifierNode = new XMP_Node(parentNode, "qualifier", "value", kXMP_PropIsQualifier);
    parentNode->qualifiers.push_back(qualifierNode);

    XMP_NodePtrPos qualifierNodePos = parentNode->qualifiers.begin();
    DeleteSubtree(qualifierNodePos);

    // After deletion, the parent should no longer have qualifiers
    ASSERT_FALSE(parentNode->options & kXMP_PropHasQualifiers);
}

TEST_F(XMPNodeTest, DeleteSubtree_ParentWithoutChildren_1896) {
    // Test the case where a node is deleted and the parent node no longer has children
    XMP_NodePtrPos childNodePos = parentNode->children.begin();
    DeleteSubtree(childNodePos);

    // After deletion, the parent should have no children
    ASSERT_TRUE(parentNode->children.empty());
}

TEST_F(XMPNodeTest, DeleteSubtree_WithEmptyParent_1897) {
    // Test the case where the parent has no children or qualifiers
    XMP_NodePtrPos nonExistentPos = parentNode->children.end();
    DeleteSubtree(nonExistentPos);

    // Ensure that no crash or undefined behavior occurs
    ASSERT_TRUE(parentNode->children.empty());
}

TEST_F(XMPNodeTest, DeleteSubtree_ParentWithNoName_1898) {
    // Test the case where the parent node doesn't have a name (empty name)
    XMP_Node *noNameNode = new XMP_Node(parentNode, "", 0);
    parentNode->children.push_back(noNameNode);

    XMP_NodePtrPos noNameNodePos = parentNode->children.begin();
    DeleteSubtree(noNameNodePos);

    // After deletion, the parent should have no children
    ASSERT_TRUE(parentNode->children.empty());
}