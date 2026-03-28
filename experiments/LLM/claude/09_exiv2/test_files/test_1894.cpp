#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for XMP SDK
#include "XMPCore_Impl.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
XMP_Node * FindSchemaNode ( XMP_Node * xmpTree, XMP_StringPtr nsURI, bool createNodes, XMP_NodePtrPos * ptrPos = 0 );

class FindSchemaNodeTest_1894 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit so namespace operations work
        XMPMeta::Initialize();
        // Register a test namespace
        XMPMeta::RegisterNamespace("http://test.ns/", "test:");
        XMPMeta::RegisterNamespace("http://other.ns/", "other:");
        XMPMeta::RegisterNamespace("http://third.ns/", "third:");
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test: Finding a schema node that does not exist, without creating
TEST_F(FindSchemaNodeTest_1894, FindNonExistentSchemaWithoutCreate_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://nonexistent.ns/", false);
    
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(xmpTree.children.size(), 0u);
}

// Test: Finding a schema node that does not exist, with creation enabled
TEST_F(FindSchemaNodeTest_1894, FindNonExistentSchemaWithCreate_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->name, "http://test.ns/");
    EXPECT_EQ(xmpTree.children.size(), 1u);
    EXPECT_EQ(xmpTree.children[0], result);
    EXPECT_EQ(result->parent, &xmpTree);
}

// Test: Finding an existing schema node returns it
TEST_F(FindSchemaNodeTest_1894, FindExistingSchema_1894) {
    XMP_Node xmpTree(0, "", 0);
    XMP_Node* child = new XMP_Node(&xmpTree, "http://test.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    child->value = "test:";
    xmpTree.children.push_back(child);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", false);
    
    EXPECT_EQ(result, child);
    EXPECT_EQ(xmpTree.children.size(), 1u);
}

// Test: Finding existing schema with createNodes=true should not create duplicate
TEST_F(FindSchemaNodeTest_1894, FindExistingSchemaWithCreateDoesNotDuplicate_1894) {
    XMP_Node xmpTree(0, "", 0);
    XMP_Node* child = new XMP_Node(&xmpTree, "http://test.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    child->value = "test:";
    xmpTree.children.push_back(child);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    
    EXPECT_EQ(result, child);
    EXPECT_EQ(xmpTree.children.size(), 1u);
}

// Test: ptrPos is correctly set when finding an existing schema node
TEST_F(FindSchemaNodeTest_1894, PtrPosSetCorrectlyForExistingNode_1894) {
    XMP_Node xmpTree(0, "", 0);
    XMP_Node* child1 = new XMP_Node(&xmpTree, "http://test.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    XMP_Node* child2 = new XMP_Node(&xmpTree, "http://other.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    xmpTree.children.push_back(child1);
    xmpTree.children.push_back(child2);
    
    XMP_NodePtrPos pos;
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://other.ns/", false, &pos);
    
    EXPECT_EQ(result, child2);
    EXPECT_EQ(*pos, child2);
}

// Test: ptrPos is correctly set when creating a new schema node
TEST_F(FindSchemaNodeTest_1894, PtrPosSetCorrectlyForCreatedNode_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_NodePtrPos pos;
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", true, &pos);
    
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*pos, result);
}

// Test: ptrPos is not modified when node not found and createNodes=false
TEST_F(FindSchemaNodeTest_1894, PtrPosNotFoundNoCreate_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://nonexistent.ns/", false);
    
    EXPECT_EQ(result, nullptr);
}

// Test: Multiple children, find first one
TEST_F(FindSchemaNodeTest_1894, FindFirstAmongMultipleChildren_1894) {
    XMP_Node xmpTree(0, "", 0);
    XMP_Node* child1 = new XMP_Node(&xmpTree, "http://test.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    XMP_Node* child2 = new XMP_Node(&xmpTree, "http://other.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    XMP_Node* child3 = new XMP_Node(&xmpTree, "http://third.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    xmpTree.children.push_back(child1);
    xmpTree.children.push_back(child2);
    xmpTree.children.push_back(child3);
    
    XMP_NodePtrPos pos;
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", false, &pos);
    
    EXPECT_EQ(result, child1);
    EXPECT_EQ(*pos, child1);
}

// Test: Multiple children, find last one
TEST_F(FindSchemaNodeTest_1894, FindLastAmongMultipleChildren_1894) {
    XMP_Node xmpTree(0, "", 0);
    XMP_Node* child1 = new XMP_Node(&xmpTree, "http://test.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    XMP_Node* child2 = new XMP_Node(&xmpTree, "http://other.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    XMP_Node* child3 = new XMP_Node(&xmpTree, "http://third.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    xmpTree.children.push_back(child1);
    xmpTree.children.push_back(child2);
    xmpTree.children.push_back(child3);
    
    XMP_NodePtrPos pos;
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://third.ns/", false, &pos);
    
    EXPECT_EQ(result, child3);
    EXPECT_EQ(*pos, child3);
}

// Test: Created node has correct value (namespace prefix)
TEST_F(FindSchemaNodeTest_1894, CreatedNodeHasCorrectPrefixValue_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->value, "test:");
}

// Test: Created node with different namespace has correct prefix
TEST_F(FindSchemaNodeTest_1894, CreatedNodeDifferentNamespacePrefix_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://other.ns/", true);
    
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->value, "other:");
}

// Test: ptrPos with null pointer should not crash
TEST_F(FindSchemaNodeTest_1894, NullPtrPosDoesNotCrash_1894) {
    XMP_Node xmpTree(0, "", 0);
    XMP_Node* child = new XMP_Node(&xmpTree, "http://test.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    xmpTree.children.push_back(child);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", false, nullptr);
    
    EXPECT_EQ(result, child);
}

// Test: Empty tree with no creation returns null
TEST_F(FindSchemaNodeTest_1894, EmptyTreeNoCreateReturnsNull_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", false, nullptr);
    
    EXPECT_EQ(result, nullptr);
}

// Test: Creating multiple schema nodes sequentially
TEST_F(FindSchemaNodeTest_1894, CreateMultipleSchemasSequentially_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result1 = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    XMP_Node* result2 = FindSchemaNode(&xmpTree, "http://other.ns/", true);
    
    EXPECT_NE(result1, nullptr);
    EXPECT_NE(result2, nullptr);
    EXPECT_NE(result1, result2);
    EXPECT_EQ(xmpTree.children.size(), 2u);
    EXPECT_EQ(result1->name, "http://test.ns/");
    EXPECT_EQ(result2->name, "http://other.ns/");
}

// Test: Created node's parent pointer is correctly set
TEST_F(FindSchemaNodeTest_1894, CreatedNodeParentPointerCorrect_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->parent, &xmpTree);
}

// Test: Find with ptrPos pointing to first element among multiple children
TEST_F(FindSchemaNodeTest_1894, PtrPosFirstElement_1894) {
    XMP_Node xmpTree(0, "", 0);
    XMP_Node* child1 = new XMP_Node(&xmpTree, "http://test.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    XMP_Node* child2 = new XMP_Node(&xmpTree, "http://other.ns/", (kXMP_SchemaNode | kXMP_NewImplicitNode));
    xmpTree.children.push_back(child1);
    xmpTree.children.push_back(child2);
    
    XMP_NodePtrPos pos;
    FindSchemaNode(&xmpTree, "http://test.ns/", false, &pos);
    
    // pos should point to the first element
    EXPECT_EQ(pos, xmpTree.children.begin());
}

// Test: Second call to create same schema returns existing, no duplication
TEST_F(FindSchemaNodeTest_1894, SecondCreateCallReturnsSameNode_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result1 = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    XMP_Node* result2 = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(xmpTree.children.size(), 1u);
}

// Test: Created schema node has kXMP_SchemaNode option
TEST_F(FindSchemaNodeTest_1894, CreatedNodeHasSchemaNodeOption_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(result->options & kXMP_SchemaNode);
}

// Test: Created schema node has kXMP_NewImplicitNode option
TEST_F(FindSchemaNodeTest_1894, CreatedNodeHasNewImplicitNodeOption_1894) {
    XMP_Node xmpTree(0, "", 0);
    
    XMP_Node* result = FindSchemaNode(&xmpTree, "http://test.ns/", true);
    
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(result->options & kXMP_NewImplicitNode);
}
