#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// We need to know about kXMP_SchemaNode and kXMP_NewImplicitNode
// These are typically defined in the XMP SDK internals
#ifndef kXMP_SchemaNode
#define kXMP_SchemaNode 0x80000000UL
#endif

#ifndef kXMP_NewImplicitNode
#define kXMP_NewImplicitNode 0x20000000UL
#endif

// Forward declaration of the function under test
XMP_Node * FindChildNode ( XMP_Node * parent, XMP_StringPtr childName, bool createNodes, XMP_NodePtrPos * ptrPos = 0 );

class FindChildNodeTest_1895 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any nodes created during tests
        for (auto* node : nodesToClean) {
            node->RemoveChildren();
            node->RemoveQualifiers();
            delete node;
        }
        nodesToClean.clear();
    }

    // Helper to track nodes for cleanup
    std::vector<XMP_Node*> nodesToClean;

    XMP_Node* makeNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, options);
        nodesToClean.push_back(node);
        return node;
    }
};

// Test: Finding an existing child in a schema node
TEST_F(FindChildNodeTest_1895, FindExistingChildInSchemaNode_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);
    XMP_Node* child = new XMP_Node(&parent, "child1", 0);
    parent.children.push_back(child);

    XMP_Node* result = FindChildNode(&parent, "child1", false);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "child1");
    EXPECT_EQ(result, child);

    parent.RemoveChildren();
}

// Test: Finding a non-existing child without createNodes in schema node returns null
TEST_F(FindChildNodeTest_1895, FindNonExistingChildNoCreate_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* result = FindChildNode(&parent, "nonexistent", false);
    EXPECT_EQ(result, nullptr);
}

// Test: Creating a new child when not found and createNodes is true
TEST_F(FindChildNodeTest_1895, CreateNewChildWhenNotFound_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* result = FindChildNode(&parent, "newChild", true);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "newChild");
    EXPECT_EQ(result->parent, &parent);
    EXPECT_EQ(parent.children.size(), 1u);
    EXPECT_TRUE(result->options & kXMP_NewImplicitNode);

    parent.RemoveChildren();
}

// Test: Finding existing child in a struct node
TEST_F(FindChildNodeTest_1895, FindExistingChildInStructNode_1895) {
    XMP_Node parent(nullptr, "struct", kXMP_PropValueIsStruct);
    XMP_Node* child = new XMP_Node(&parent, "field1", 0);
    parent.children.push_back(child);

    XMP_Node* result = FindChildNode(&parent, "field1", false);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "field1");

    parent.RemoveChildren();
}

// Test: Throw when parent has no schema/struct/implicit options
TEST_F(FindChildNodeTest_1895, ThrowOnInvalidParentOptions_1895) {
    XMP_Node parent(nullptr, "plain", 0);

    EXPECT_THROW(FindChildNode(&parent, "child", false), XMP_Error);
}

// Test: Throw when parent is new implicit node but is also an array
TEST_F(FindChildNodeTest_1895, ThrowOnImplicitArrayNode_1895) {
    XMP_Node parent(nullptr, "array", kXMP_NewImplicitNode | kXMP_PropValueIsArray);

    EXPECT_THROW(FindChildNode(&parent, "child", true), XMP_Error);
}

// Test: Throw when parent is new implicit node but createNodes is false
TEST_F(FindChildNodeTest_1895, ThrowOnImplicitNodeWithoutCreate_1895) {
    XMP_Node parent(nullptr, "implicit", kXMP_NewImplicitNode);

    EXPECT_THROW(FindChildNode(&parent, "child", false), XMP_Error);
}

// Test: Implicit node becomes struct when createNodes is true
TEST_F(FindChildNodeTest_1895, ImplicitNodeBecomesStruct_1895) {
    XMP_Node parent(nullptr, "implicit", kXMP_NewImplicitNode);

    XMP_Node* result = FindChildNode(&parent, "child", true);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(parent.options & kXMP_PropValueIsStruct);
    EXPECT_EQ(result->name, "child");

    parent.RemoveChildren();
}

// Test: ptrPos is set correctly when finding existing child
TEST_F(FindChildNodeTest_1895, PtrPosSetForExistingChild_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);
    XMP_Node* child1 = new XMP_Node(&parent, "child1", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "child2", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);

    XMP_NodePtrPos pos;
    XMP_Node* result = FindChildNode(&parent, "child2", false, &pos);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child2);
    EXPECT_EQ(*pos, child2);

    parent.RemoveChildren();
}

// Test: ptrPos is set correctly when creating new child
TEST_F(FindChildNodeTest_1895, PtrPosSetForCreatedChild_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_NodePtrPos pos;
    XMP_Node* result = FindChildNode(&parent, "newChild", true, &pos);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*pos, result);

    parent.RemoveChildren();
}

// Test: ptrPos with null does not crash
TEST_F(FindChildNodeTest_1895, NullPtrPosDoesNotCrash_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* result = FindChildNode(&parent, "newChild", true, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "newChild");

    parent.RemoveChildren();
}

// Test: Finding first child among multiple children
TEST_F(FindChildNodeTest_1895, FindFirstChildAmongMultiple_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);
    XMP_Node* child1 = new XMP_Node(&parent, "alpha", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "beta", 0);
    XMP_Node* child3 = new XMP_Node(&parent, "gamma", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);
    parent.children.push_back(child3);

    XMP_NodePtrPos pos;
    XMP_Node* result = FindChildNode(&parent, "alpha", false, &pos);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child1);
    EXPECT_EQ(*pos, child1);

    parent.RemoveChildren();
}

// Test: Finding last child among multiple children
TEST_F(FindChildNodeTest_1895, FindLastChildAmongMultiple_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);
    XMP_Node* child1 = new XMP_Node(&parent, "alpha", 0);
    XMP_Node* child2 = new XMP_Node(&parent, "beta", 0);
    XMP_Node* child3 = new XMP_Node(&parent, "gamma", 0);
    parent.children.push_back(child1);
    parent.children.push_back(child2);
    parent.children.push_back(child3);

    XMP_NodePtrPos pos;
    XMP_Node* result = FindChildNode(&parent, "gamma", false, &pos);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child3);
    EXPECT_EQ(*pos, child3);

    parent.RemoveChildren();
}

// Test: Parent with no children, createNodes false returns null
TEST_F(FindChildNodeTest_1895, EmptyParentNoCreateReturnsNull_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);
    EXPECT_TRUE(parent.children.empty());

    XMP_Node* result = FindChildNode(&parent, "anything", false);
    EXPECT_EQ(result, nullptr);
}

// Test: Parent with no children, createNodes true creates and returns child
TEST_F(FindChildNodeTest_1895, EmptyParentCreateReturnsNewChild_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);
    EXPECT_TRUE(parent.children.empty());

    XMP_Node* result = FindChildNode(&parent, "newChild", true);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(parent.children.size(), 1u);
    EXPECT_EQ(parent.children[0], result);

    parent.RemoveChildren();
}

// Test: Creating multiple children sequentially
TEST_F(FindChildNodeTest_1895, CreateMultipleChildrenSequentially_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* child1 = FindChildNode(&parent, "first", true);
    XMP_Node* child2 = FindChildNode(&parent, "second", true);
    XMP_Node* child3 = FindChildNode(&parent, "third", true);

    ASSERT_NE(child1, nullptr);
    ASSERT_NE(child2, nullptr);
    ASSERT_NE(child3, nullptr);
    EXPECT_NE(child1, child2);
    EXPECT_NE(child2, child3);
    EXPECT_EQ(parent.children.size(), 3u);

    parent.RemoveChildren();
}

// Test: Finding same child twice returns same pointer
TEST_F(FindChildNodeTest_1895, FindSameChildTwiceReturnsSamePointer_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* created = FindChildNode(&parent, "child", true);
    ASSERT_NE(created, nullptr);

    XMP_Node* found = FindChildNode(&parent, "child", false);
    EXPECT_EQ(found, created);

    parent.RemoveChildren();
}

// Test: createNodes true for existing child returns existing (no duplicate)
TEST_F(FindChildNodeTest_1895, CreateNodesDoesNotDuplicateExisting_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* first = FindChildNode(&parent, "child", true);
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(parent.children.size(), 1u);

    XMP_Node* second = FindChildNode(&parent, "child", true);
    EXPECT_EQ(second, first);
    EXPECT_EQ(parent.children.size(), 1u);

    parent.RemoveChildren();
}

// Test: Error code for named children on non-struct/schema
TEST_F(FindChildNodeTest_1895, ThrowBadXPathForPlainNode_1895) {
    XMP_Node parent(nullptr, "plain", 0);

    try {
        FindChildNode(&parent, "child", true);
        FAIL() << "Expected exception";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);
    }
}

// Test: Error code for named children on array with no implicit flag
TEST_F(FindChildNodeTest_1895, ThrowBadXPathForArrayParent_1895) {
    XMP_Node parent(nullptr, "array", kXMP_NewImplicitNode | kXMP_PropValueIsArray);

    try {
        FindChildNode(&parent, "child", true);
        FAIL() << "Expected exception";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);
    }
}

// Test: Error code for implicit node with createNodes false
TEST_F(FindChildNodeTest_1895, ThrowInternalFailureForImplicitNoCreate_1895) {
    XMP_Node parent(nullptr, "implicit", kXMP_NewImplicitNode);

    try {
        FindChildNode(&parent, "child", false);
        FAIL() << "Expected exception";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_InternalFailure);
    }
}

// Test: Created child has correct parent pointer
TEST_F(FindChildNodeTest_1895, CreatedChildHasCorrectParent_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* child = FindChildNode(&parent, "child", true);
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->parent, &parent);

    parent.RemoveChildren();
}

// Test: ptrPos not set when child not found and not created
TEST_F(FindChildNodeTest_1895, PtrPosNotFoundNoCreate_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_NodePtrPos pos = parent.children.end();
    XMP_Node* result = FindChildNode(&parent, "missing", false, &pos);
    EXPECT_EQ(result, nullptr);
}

// Test: Schema node with both kXMP_SchemaNode flag works correctly
TEST_F(FindChildNodeTest_1895, SchemaNodeFlagWorksCorrectly_1895) {
    XMP_Node parent(nullptr, "ns:schema", kXMP_SchemaNode);

    XMP_Node* result = FindChildNode(&parent, "ns:property", true);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "ns:property");

    parent.RemoveChildren();
}

// Test: Struct node works for finding children
TEST_F(FindChildNodeTest_1895, StructNodeWorksForChildren_1895) {
    XMP_Node parent(nullptr, "myStruct", kXMP_PropValueIsStruct);
    XMP_Node* child = new XMP_Node(&parent, "field", 0);
    parent.children.push_back(child);

    XMP_Node* result = FindChildNode(&parent, "field", false);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child);

    parent.RemoveChildren();
}

// Test: Empty child name search
TEST_F(FindChildNodeTest_1895, EmptyChildNameSearch_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* result = FindChildNode(&parent, "", false);
    EXPECT_EQ(result, nullptr);
}

// Test: Empty child name can be created
TEST_F(FindChildNodeTest_1895, EmptyChildNameCanBeCreated_1895) {
    XMP_Node parent(nullptr, "schema", kXMP_SchemaNode);

    XMP_Node* result = FindChildNode(&parent, "", true);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "");

    parent.RemoveChildren();
}
