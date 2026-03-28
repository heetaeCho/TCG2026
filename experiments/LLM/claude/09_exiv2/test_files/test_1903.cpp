#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Include necessary headers from the project
#include "XMPCore_Impl.hpp"

// We need access to DeleteEmptySchema
// It's declared somewhere in the headers; if not, we declare it extern
extern void DeleteEmptySchema(XMP_Node* schemaNode);

class DeleteEmptySchemaTest_1903 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: An empty schema node (no children, schema option set) should be removed from parent
TEST_F(DeleteEmptySchemaTest_1903, EmptySchemaNodeIsDeletedFromParent_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* schemaNode = new XMP_Node(xmpTree, "schema1", kXMP_SchemaNode);
    xmpTree->children.push_back(schemaNode);

    ASSERT_EQ(xmpTree->children.size(), 1u);

    DeleteEmptySchema(schemaNode);
    // schemaNode is now deleted, parent should have no children
    EXPECT_EQ(xmpTree->children.size(), 0u);

    delete xmpTree;
}

// Test: A schema node with children should NOT be deleted
TEST_F(DeleteEmptySchemaTest_1903, NonEmptySchemaNodeIsNotDeleted_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* schemaNode = new XMP_Node(xmpTree, "schema1", kXMP_SchemaNode);
    XMP_Node* childNode = new XMP_Node(schemaNode, "child1", 0);
    schemaNode->children.push_back(childNode);
    xmpTree->children.push_back(schemaNode);

    ASSERT_EQ(xmpTree->children.size(), 1u);

    DeleteEmptySchema(schemaNode);
    // schemaNode should still exist because it has children
    EXPECT_EQ(xmpTree->children.size(), 1u);
    EXPECT_EQ(xmpTree->children[0], schemaNode);

    delete xmpTree;
}

// Test: A node that is NOT a schema node (no schema option) should not be deleted even if empty
TEST_F(DeleteEmptySchemaTest_1903, NonSchemaNodeIsNotDeleted_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* regularNode = new XMP_Node(xmpTree, "regular1", 0);  // No schema flag
    xmpTree->children.push_back(regularNode);

    ASSERT_EQ(xmpTree->children.size(), 1u);

    DeleteEmptySchema(regularNode);
    // regularNode should still be there since it's not a schema node
    EXPECT_EQ(xmpTree->children.size(), 1u);
    EXPECT_EQ(xmpTree->children[0], regularNode);

    delete xmpTree;
}

// Test: Deleting an empty schema that is the first child among multiple children
TEST_F(DeleteEmptySchemaTest_1903, EmptySchemaFirstChildAmongMultiple_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* schema1 = new XMP_Node(xmpTree, "schema1", kXMP_SchemaNode);
    XMP_Node* schema2 = new XMP_Node(xmpTree, "schema2", kXMP_SchemaNode);
    XMP_Node* schema3 = new XMP_Node(xmpTree, "schema3", kXMP_SchemaNode);

    // Give schema2 and schema3 children so they aren't empty
    XMP_Node* child2 = new XMP_Node(schema2, "child2", 0);
    schema2->children.push_back(child2);
    XMP_Node* child3 = new XMP_Node(schema3, "child3", 0);
    schema3->children.push_back(child3);

    xmpTree->children.push_back(schema1);
    xmpTree->children.push_back(schema2);
    xmpTree->children.push_back(schema3);

    ASSERT_EQ(xmpTree->children.size(), 3u);

    DeleteEmptySchema(schema1);
    // schema1 should be deleted, schema2 and schema3 remain
    EXPECT_EQ(xmpTree->children.size(), 2u);
    EXPECT_EQ(xmpTree->children[0], schema2);
    EXPECT_EQ(xmpTree->children[1], schema3);

    delete xmpTree;
}

// Test: Deleting an empty schema that is the last child among multiple children
TEST_F(DeleteEmptySchemaTest_1903, EmptySchemaLastChildAmongMultiple_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* schema1 = new XMP_Node(xmpTree, "schema1", kXMP_SchemaNode);
    XMP_Node* schema2 = new XMP_Node(xmpTree, "schema2", kXMP_SchemaNode);
    XMP_Node* schema3 = new XMP_Node(xmpTree, "schema3", kXMP_SchemaNode);  // empty

    XMP_Node* child1 = new XMP_Node(schema1, "child1", 0);
    schema1->children.push_back(child1);
    XMP_Node* child2 = new XMP_Node(schema2, "child2", 0);
    schema2->children.push_back(child2);

    xmpTree->children.push_back(schema1);
    xmpTree->children.push_back(schema2);
    xmpTree->children.push_back(schema3);

    ASSERT_EQ(xmpTree->children.size(), 3u);

    DeleteEmptySchema(schema3);
    // schema3 should be deleted
    EXPECT_EQ(xmpTree->children.size(), 2u);
    EXPECT_EQ(xmpTree->children[0], schema1);
    EXPECT_EQ(xmpTree->children[1], schema2);

    delete xmpTree;
}

// Test: Deleting an empty schema that is the middle child among multiple children
TEST_F(DeleteEmptySchemaTest_1903, EmptySchemaMiddleChildAmongMultiple_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* schema1 = new XMP_Node(xmpTree, "schema1", kXMP_SchemaNode);
    XMP_Node* schema2 = new XMP_Node(xmpTree, "schema2", kXMP_SchemaNode);  // empty, middle
    XMP_Node* schema3 = new XMP_Node(xmpTree, "schema3", kXMP_SchemaNode);

    XMP_Node* child1 = new XMP_Node(schema1, "child1", 0);
    schema1->children.push_back(child1);
    XMP_Node* child3 = new XMP_Node(schema3, "child3", 0);
    schema3->children.push_back(child3);

    xmpTree->children.push_back(schema1);
    xmpTree->children.push_back(schema2);
    xmpTree->children.push_back(schema3);

    ASSERT_EQ(xmpTree->children.size(), 3u);

    DeleteEmptySchema(schema2);
    // schema2 (middle) should be deleted
    EXPECT_EQ(xmpTree->children.size(), 2u);
    EXPECT_EQ(xmpTree->children[0], schema1);
    EXPECT_EQ(xmpTree->children[1], schema3);

    delete xmpTree;
}

// Test: A non-schema node with children should not be deleted
TEST_F(DeleteEmptySchemaTest_1903, NonSchemaNodeWithChildrenIsNotDeleted_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* regularNode = new XMP_Node(xmpTree, "regular", 0);
    XMP_Node* childNode = new XMP_Node(regularNode, "child", 0);
    regularNode->children.push_back(childNode);
    xmpTree->children.push_back(regularNode);

    ASSERT_EQ(xmpTree->children.size(), 1u);

    DeleteEmptySchema(regularNode);
    EXPECT_EQ(xmpTree->children.size(), 1u);
    EXPECT_EQ(xmpTree->children[0], regularNode);

    delete xmpTree;
}

// Test: Only child that is an empty schema - parent becomes empty after deletion
TEST_F(DeleteEmptySchemaTest_1903, OnlyChildEmptySchemaParentBecomesEmpty_1903) {
    XMP_Node* xmpTree = new XMP_Node(nullptr, "xmpTree", 0);
    XMP_Node* schemaNode = new XMP_Node(xmpTree, "onlySchema", kXMP_SchemaNode);
    xmpTree->children.push_back(schemaNode);

    ASSERT_EQ(xmpTree->children.size(), 1u);

    DeleteEmptySchema(schemaNode);

    EXPECT_TRUE(xmpTree->children.empty());

    delete xmpTree;
}
