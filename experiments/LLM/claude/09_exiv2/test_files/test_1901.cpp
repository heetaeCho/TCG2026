#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers
#include "XMPCore_Impl.hpp"

// We need access to CloneSubtree and related functions
// These are declared in XMPCore_Impl.hpp or similar headers
extern XMP_Node * CloneSubtree(const XMP_Node * origRoot, XMP_Node * cloneParent);
extern void CloneOffspring(const XMP_Node * origRoot, XMP_Node * cloneRoot);

class CloneSubtreeTest_1901 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up all allocated nodes
        for (auto* node : nodesToCleanup) {
            if (node) {
                node->RemoveChildren();
                node->RemoveQualifiers();
                delete node;
            }
        }
        nodesToCleanup.clear();
    }

    // Helper to track nodes for cleanup
    XMP_Node* MakeNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, value, options);
        nodesToCleanup.push_back(node);
        return node;
    }

    XMP_Node* MakeNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, options);
        nodesToCleanup.push_back(node);
        return node;
    }

    // Track the clone result separately since it gets added to parent's children
    void TrackNode(XMP_Node* node) {
        nodesToCleanup.push_back(node);
    }

    std::vector<XMP_Node*> nodesToCleanup;
};

// Test that CloneSubtree creates a new node with the same name as origRoot
TEST_F(CloneSubtreeTest_1901, CloneCopiesName_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "testNode", "testValue", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode; // non-null parent to avoid schema assertions

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);
    // Don't track result separately - it's in cloneParent->children

    EXPECT_EQ(result->name, "testNode");
}

// Test that CloneSubtree creates a new node with the same value as origRoot
TEST_F(CloneSubtreeTest_1901, CloneCopiesValue_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "origChild", "someValue", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->value, "someValue");
}

// Test that CloneSubtree creates a new node with the same options as origRoot
TEST_F(CloneSubtreeTest_1901, CloneCopiesOptions_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_OptionBits testOptions = kXMP_PropValueIsArray;
    XMP_Node* origRoot = MakeNode(parentNode, "origChild", "val", testOptions);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->options, testOptions);
}

// Test that CloneSubtree sets the parent of the cloned node to cloneParent
TEST_F(CloneSubtreeTest_1901, CloneSetsParent_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "origChild", "val", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->parent, cloneParent);
}

// Test that CloneSubtree adds the cloned node to cloneParent's children
TEST_F(CloneSubtreeTest_1901, CloneAddedToParentChildren_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "origChild", "val", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    size_t childrenBefore = cloneParent->children.size();
    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(cloneParent->children.size(), childrenBefore + 1);
    EXPECT_EQ(cloneParent->children.back(), result);
}

// Test that CloneSubtree with an empty value works correctly
TEST_F(CloneSubtreeTest_1901, CloneWithEmptyValue_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "emptyNode", "", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->value, "");
    EXPECT_EQ(result->name, "emptyNode");
}

// Test that CloneSubtree returns a different pointer than origRoot (it's a new node)
TEST_F(CloneSubtreeTest_1901, CloneReturnsNewNode_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "origChild", "val", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_NE(result, origRoot);
}

// Test cloning a node that has children (offspring should be cloned)
TEST_F(CloneSubtreeTest_1901, CloneWithChildren_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "origParent", "", kXMP_PropValueIsStruct);
    
    // Add children to origRoot
    XMP_Node* child1 = MakeNode(origRoot, "child1", "val1", 0);
    origRoot->children.push_back(child1);
    XMP_Node* child2 = MakeNode(origRoot, "child2", "val2", 0);
    origRoot->children.push_back(child2);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->children.size(), 2u);
    EXPECT_EQ(result->children[0]->name, "child1");
    EXPECT_EQ(result->children[0]->value, "val1");
    EXPECT_EQ(result->children[1]->name, "child2");
    EXPECT_EQ(result->children[1]->value, "val2");
}

// Test cloning a node with nested children (deep clone)
TEST_F(CloneSubtreeTest_1901, CloneDeepNestedChildren_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "origRoot", "", kXMP_PropValueIsStruct);
    
    XMP_Node* child = MakeNode(origRoot, "child", "", kXMP_PropValueIsStruct);
    origRoot->children.push_back(child);
    
    XMP_Node* grandChild = MakeNode(child, "grandChild", "deepVal", 0);
    child->children.push_back(grandChild);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    ASSERT_EQ(result->children.size(), 1u);
    ASSERT_EQ(result->children[0]->children.size(), 1u);
    EXPECT_EQ(result->children[0]->children[0]->name, "grandChild");
    EXPECT_EQ(result->children[0]->children[0]->value, "deepVal");
}

// Test cloning a leaf node (no children)
TEST_F(CloneSubtreeTest_1901, CloneLeafNode_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "leaf", "leafValue", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->children.size(), 0u);
    EXPECT_EQ(result->name, "leaf");
    EXPECT_EQ(result->value, "leafValue");
}

// Test that multiple calls to CloneSubtree add multiple children to cloneParent
TEST_F(CloneSubtreeTest_1901, MultipleClonesToSameParent_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* orig1 = MakeNode(parentNode, "node1", "val1", 0);
    XMP_Node* orig2 = MakeNode(parentNode, "node2", "val2", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    CloneSubtree(orig1, cloneParent);
    CloneSubtree(orig2, cloneParent);

    EXPECT_EQ(cloneParent->children.size(), 2u);
    EXPECT_EQ(cloneParent->children[0]->name, "node1");
    EXPECT_EQ(cloneParent->children[1]->name, "node2");
}

// Test cloning a node with array options
TEST_F(CloneSubtreeTest_1901, CloneArrayNode_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_OptionBits arrayOptions = kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered;
    XMP_Node* origRoot = MakeNode(parentNode, "arrayNode", "", arrayOptions);
    
    // Array items
    XMP_Node* item1 = MakeNode(origRoot, "item[1]", "first", 0);
    origRoot->children.push_back(item1);
    XMP_Node* item2 = MakeNode(origRoot, "item[2]", "second", 0);
    origRoot->children.push_back(item2);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->options, arrayOptions);
    EXPECT_EQ(result->children.size(), 2u);
}

// Test that cloned children have their parent set to the cloned root (not origRoot)
TEST_F(CloneSubtreeTest_1901, ClonedChildrenPointToClonedParent_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "origRoot", "", kXMP_PropValueIsStruct);
    
    XMP_Node* child = MakeNode(origRoot, "child", "childVal", 0);
    origRoot->children.push_back(child);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    ASSERT_EQ(result->children.size(), 1u);
    EXPECT_EQ(result->children[0]->parent, result);
    EXPECT_NE(result->children[0]->parent, origRoot);
}

// Test cloning with a long name and value
TEST_F(CloneSubtreeTest_1901, CloneLongNameAndValue_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    std::string longName(500, 'n');
    std::string longValue(1000, 'v');
    XMP_Node* origRoot = MakeNode(parentNode, longName.c_str(), longValue.c_str(), 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result->name, longName);
    EXPECT_EQ(result->value, longValue);
}

// Test that the returned pointer is the same as the last child added to cloneParent
TEST_F(CloneSubtreeTest_1901, ReturnValueIsLastChild_1901) {
    XMP_Node* parentNode = MakeNode(nullptr, "parent", "", 0);
    XMP_Node* origRoot = MakeNode(parentNode, "node", "val", 0);
    
    XMP_Node* cloneParent = MakeNode(nullptr, "cloneParent", "", kXMP_PropValueIsStruct);
    cloneParent->parent = parentNode;

    XMP_Node* result = CloneSubtree(origRoot, cloneParent);

    EXPECT_EQ(result, cloneParent->children.back());
}
