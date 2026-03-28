#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "./TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Mock;

class XMP_NodeTest : public ::testing::Test {
protected:
    XMP_Node parentNode{"parent", 0}; // Placeholder for the parent node
    XMP_Node childNode{"child", &parentNode}; // Placeholder for a child node
    XMP_Node qualifierNode{"qualifier", &parentNode}; // Placeholder for a qualifier node

    XMP_Node *qualNode = nullptr; // The result from FindQualifierNode
    XMP_NodePtrPos ptrPos = nullptr; // Pointer position

    // Setup and teardown methods
    void SetUp() override {
        parentNode.qualifiers.push_back(&qualifierNode);
    }
};

// Test case 1: Normal operation - Find an existing qualifier node.
TEST_F(XMP_NodeTest, FindExistingQualifierNode_1896) {
    qualNode = FindQualifierNode(&parentNode, "qualifier", false, &ptrPos);
    ASSERT_NE(qualNode, nullptr);
    ASSERT_EQ(qualNode, &qualifierNode);
    ASSERT_EQ(ptrPos, parentNode.qualifiers.begin());
}

// Test case 2: Normal operation - Create a new qualifier node if it doesn't exist and createNodes is true.
TEST_F(XMP_NodeTest, CreateNewQualifierNode_1897) {
    qualNode = FindQualifierNode(&parentNode, "newQualifier", true, &ptrPos);
    ASSERT_NE(qualNode, nullptr);
    ASSERT_EQ(qualNode->name, "newQualifier");
    ASSERT_EQ(ptrPos, parentNode.qualifiers.end() - 1);
}

// Test case 3: Boundary condition - Create a "xml:lang" qualifier node with special handling.
TEST_F(XMP_NodeTest, CreateLangQualifierNode_1898) {
    qualNode = FindQualifierNode(&parentNode, "xml:lang", true, &ptrPos);
    ASSERT_NE(qualNode, nullptr);
    ASSERT_EQ(qualNode->name, "xml:lang");
    ASSERT_TRUE(parentNode.options & kXMP_PropHasLang);
    ASSERT_EQ(ptrPos, parentNode.qualifiers.begin());
}

// Test case 4: Boundary condition - Create a "rdf:type" qualifier node with special handling.
TEST_F(XMP_NodeTest, CreateTypeQualifierNode_1899) {
    qualNode = FindQualifierNode(&parentNode, "rdf:type", true, &ptrPos);
    ASSERT_NE(qualNode, nullptr);
    ASSERT_EQ(qualNode->name, "rdf:type");
    ASSERT_TRUE(parentNode.options & kXMP_PropHasType);
    ASSERT_EQ(ptrPos, parentNode.qualifiers.begin());
}

// Test case 5: Exceptional case - Ensure that FindQualifierNode does not create a node if createNodes is false and the node does not exist.
TEST_F(XMP_NodeTest, NoCreateQualifierNode_1900) {
    qualNode = FindQualifierNode(&parentNode, "nonExistentQualifier", false, &ptrPos);
    ASSERT_EQ(qualNode, nullptr);
    ASSERT_EQ(ptrPos, nullptr);
}

// Test case 6: Exceptional case - Assert on invalid qualifier name (e.g., "?" name).
TEST_F(XMP_NodeTest, InvalidQualifierName_1901) {
    EXPECT_DEATH({
        FindQualifierNode(&parentNode, "?", true, &ptrPos);
    }, ".*");
}