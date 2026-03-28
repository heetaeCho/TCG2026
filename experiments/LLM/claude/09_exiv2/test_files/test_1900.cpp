#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers from the project
#include "XMPCore_Impl.hpp"

// Forward declaration of the function under test
void CloneOffspring(const XMP_Node* origParent, XMP_Node* cloneParent);

class CloneOffspringTest_1900 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up nodes created during tests
        for (auto* node : nodesToCleanup) {
            delete node;
        }
        nodesToCleanup.clear();
    }

    // Helper to track nodes for cleanup
    std::vector<XMP_Node*> nodesToCleanup;

    XMP_Node* makeNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, value, options);
        nodesToCleanup.push_back(node);
        return node;
    }
};

// Test: Cloning from a parent with no children and no qualifiers
TEST_F(CloneOffspringTest_1900, EmptyParent_ClonesNothing_1900) {
    XMP_Node origParent(nullptr, "origParent", "origValue", 0);
    XMP_Node cloneParent(nullptr, "cloneParent", "cloneValue", 0);

    CloneOffspring(&origParent, &cloneParent);

    EXPECT_TRUE(cloneParent.children.empty());
    EXPECT_TRUE(cloneParent.qualifiers.empty());
}

// Test: Cloning a parent with one child
TEST_F(CloneOffspringTest_1900, SingleChild_IsCloned_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child = new XMP_Node(&origParent, "child1", "childValue1", 42);
    origParent.children.push_back(child);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->name, "child1");
    EXPECT_EQ(cloneParent.children[0]->value, "childValue1");
    EXPECT_EQ(cloneParent.children[0]->options, 42u);
    EXPECT_EQ(cloneParent.children[0]->parent, &cloneParent);

    // Cleanup
    delete child;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Cloning a parent with multiple children
TEST_F(CloneOffspringTest_1900, MultipleChildren_AreCloned_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child1 = new XMP_Node(&origParent, "child1", "val1", 1);
    XMP_Node* child2 = new XMP_Node(&origParent, "child2", "val2", 2);
    XMP_Node* child3 = new XMP_Node(&origParent, "child3", "val3", 3);
    origParent.children.push_back(child1);
    origParent.children.push_back(child2);
    origParent.children.push_back(child3);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 3u);
    EXPECT_EQ(cloneParent.children[0]->name, "child1");
    EXPECT_EQ(cloneParent.children[0]->value, "val1");
    EXPECT_EQ(cloneParent.children[0]->options, 1u);
    EXPECT_EQ(cloneParent.children[1]->name, "child2");
    EXPECT_EQ(cloneParent.children[1]->value, "val2");
    EXPECT_EQ(cloneParent.children[1]->options, 2u);
    EXPECT_EQ(cloneParent.children[2]->name, "child3");
    EXPECT_EQ(cloneParent.children[2]->value, "val3");
    EXPECT_EQ(cloneParent.children[2]->options, 3u);

    // Cleanup
    delete child1;
    delete child2;
    delete child3;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Cloning a parent with one qualifier
TEST_F(CloneOffspringTest_1900, SingleQualifier_IsCloned_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* qual = new XMP_Node(&origParent, "qual1", "qualValue1", 10);
    origParent.qualifiers.push_back(qual);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.qualifiers.size(), 1u);
    EXPECT_EQ(cloneParent.qualifiers[0]->name, "qual1");
    EXPECT_EQ(cloneParent.qualifiers[0]->value, "qualValue1");
    EXPECT_EQ(cloneParent.qualifiers[0]->options, 10u);
    EXPECT_EQ(cloneParent.qualifiers[0]->parent, &cloneParent);

    // Cleanup
    delete qual;
    for (auto* q : cloneParent.qualifiers) delete q;
}

// Test: Cloning a parent with multiple qualifiers
TEST_F(CloneOffspringTest_1900, MultipleQualifiers_AreCloned_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* qual1 = new XMP_Node(&origParent, "qual1", "qv1", 100);
    XMP_Node* qual2 = new XMP_Node(&origParent, "qual2", "qv2", 200);
    origParent.qualifiers.push_back(qual1);
    origParent.qualifiers.push_back(qual2);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.qualifiers.size(), 2u);
    EXPECT_EQ(cloneParent.qualifiers[0]->name, "qual1");
    EXPECT_EQ(cloneParent.qualifiers[0]->value, "qv1");
    EXPECT_EQ(cloneParent.qualifiers[1]->name, "qual2");
    EXPECT_EQ(cloneParent.qualifiers[1]->value, "qv2");

    // Cleanup
    delete qual1;
    delete qual2;
    for (auto* q : cloneParent.qualifiers) delete q;
}

// Test: Cloning a parent with both children and qualifiers
TEST_F(CloneOffspringTest_1900, ChildrenAndQualifiers_AreBothCloned_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child = new XMP_Node(&origParent, "child1", "cv1", 5);
    XMP_Node* qual = new XMP_Node(&origParent, "qual1", "qv1", 15);
    origParent.children.push_back(child);
    origParent.qualifiers.push_back(qual);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 1u);
    ASSERT_EQ(cloneParent.qualifiers.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->name, "child1");
    EXPECT_EQ(cloneParent.children[0]->value, "cv1");
    EXPECT_EQ(cloneParent.qualifiers[0]->name, "qual1");
    EXPECT_EQ(cloneParent.qualifiers[0]->value, "qv1");

    // Cleanup
    delete child;
    delete qual;
    for (auto* c : cloneParent.children) delete c;
    for (auto* q : cloneParent.qualifiers) delete q;
}

// Test: Recursive cloning - child has its own children
TEST_F(CloneOffspringTest_1900, NestedChildren_AreClonedRecursively_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child = new XMP_Node(&origParent, "child1", "cv1", 1);
    XMP_Node* grandchild = new XMP_Node(child, "grandchild1", "gv1", 2);
    child->children.push_back(grandchild);
    origParent.children.push_back(child);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->name, "child1");
    ASSERT_EQ(cloneParent.children[0]->children.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->children[0]->name, "grandchild1");
    EXPECT_EQ(cloneParent.children[0]->children[0]->value, "gv1");
    EXPECT_EQ(cloneParent.children[0]->children[0]->options, 2u);
    EXPECT_EQ(cloneParent.children[0]->children[0]->parent, cloneParent.children[0]);

    // Cleanup
    delete grandchild;
    delete child;
    // Recursive cleanup for clone
    for (auto* gc : cloneParent.children[0]->children) delete gc;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Recursive cloning - child has qualifiers
TEST_F(CloneOffspringTest_1900, ChildWithQualifiers_QualifiersClonedRecursively_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child = new XMP_Node(&origParent, "child1", "cv1", 1);
    XMP_Node* childQual = new XMP_Node(child, "childQual", "cqv", 99);
    child->qualifiers.push_back(childQual);
    origParent.children.push_back(child);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 1u);
    ASSERT_EQ(cloneParent.children[0]->qualifiers.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->qualifiers[0]->name, "childQual");
    EXPECT_EQ(cloneParent.children[0]->qualifiers[0]->value, "cqv");
    EXPECT_EQ(cloneParent.children[0]->qualifiers[0]->options, 99u);
    EXPECT_EQ(cloneParent.children[0]->qualifiers[0]->parent, cloneParent.children[0]);

    // Cleanup
    delete childQual;
    delete child;
    for (auto* q : cloneParent.children[0]->qualifiers) delete q;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Deep nesting - 3 levels of children
TEST_F(CloneOffspringTest_1900, DeeplyNestedChildren_AreCloned_1900) {
    XMP_Node origParent(nullptr, "root", "", 0);
    XMP_Node* level1 = new XMP_Node(&origParent, "L1", "v1", 1);
    XMP_Node* level2 = new XMP_Node(level1, "L2", "v2", 2);
    XMP_Node* level3 = new XMP_Node(level2, "L3", "v3", 3);
    level2->children.push_back(level3);
    level1->children.push_back(level2);
    origParent.children.push_back(level1);

    XMP_Node cloneParent(nullptr, "cloneRoot", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 1u);
    XMP_Node* cL1 = cloneParent.children[0];
    EXPECT_EQ(cL1->name, "L1");
    ASSERT_EQ(cL1->children.size(), 1u);
    XMP_Node* cL2 = cL1->children[0];
    EXPECT_EQ(cL2->name, "L2");
    EXPECT_EQ(cL2->parent, cL1);
    ASSERT_EQ(cL2->children.size(), 1u);
    XMP_Node* cL3 = cL2->children[0];
    EXPECT_EQ(cL3->name, "L3");
    EXPECT_EQ(cL3->value, "v3");
    EXPECT_EQ(cL3->options, 3u);
    EXPECT_EQ(cL3->parent, cL2);
    EXPECT_TRUE(cL3->children.empty());

    // Cleanup originals
    delete level3;
    delete level2;
    delete level1;
    // Cleanup clones
    delete cL3;
    delete cL2;
    delete cL1;
}

// Test: Cloned nodes are independent from original (modification does not affect clone)
TEST_F(CloneOffspringTest_1900, ClonedNodesAreIndependent_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child = new XMP_Node(&origParent, "child1", "originalValue", 0);
    origParent.children.push_back(child);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    // Modify original
    child->value = "modifiedValue";
    child->name = "modifiedName";

    // Clone should still have original values
    ASSERT_EQ(cloneParent.children.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->value, "originalValue");
    EXPECT_EQ(cloneParent.children[0]->name, "child1");

    // Cleanup
    delete child;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Qualifier has its own children (nested qualifiers/children structure)
TEST_F(CloneOffspringTest_1900, QualifierWithChildren_ClonedRecursively_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* qual = new XMP_Node(&origParent, "qual1", "qv1", 50);
    XMP_Node* qualChild = new XMP_Node(qual, "qualChild1", "qcv1", 55);
    qual->children.push_back(qualChild);
    origParent.qualifiers.push_back(qual);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.qualifiers.size(), 1u);
    EXPECT_EQ(cloneParent.qualifiers[0]->name, "qual1");
    ASSERT_EQ(cloneParent.qualifiers[0]->children.size(), 1u);
    EXPECT_EQ(cloneParent.qualifiers[0]->children[0]->name, "qualChild1");
    EXPECT_EQ(cloneParent.qualifiers[0]->children[0]->value, "qcv1");
    EXPECT_EQ(cloneParent.qualifiers[0]->children[0]->parent, cloneParent.qualifiers[0]);

    // Cleanup
    delete qualChild;
    delete qual;
    for (auto* qc : cloneParent.qualifiers[0]->children) delete qc;
    for (auto* q : cloneParent.qualifiers) delete q;
}

// Test: Empty string values are handled correctly
TEST_F(CloneOffspringTest_1900, EmptyStringValues_AreClonedCorrectly_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child = new XMP_Node(&origParent, "", "", 0);
    origParent.children.push_back(child);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->name, "");
    EXPECT_EQ(cloneParent.children[0]->value, "");
    EXPECT_EQ(cloneParent.children[0]->options, 0u);

    // Cleanup
    delete child;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Options bits are preserved exactly
TEST_F(CloneOffspringTest_1900, OptionsBits_ArePreservedExactly_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_OptionBits testOptions = 0xDEADBEEF;
    XMP_Node* child = new XMP_Node(&origParent, "child1", "val", testOptions);
    origParent.children.push_back(child);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 1u);
    EXPECT_EQ(cloneParent.children[0]->options, testOptions);

    // Cleanup
    delete child;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Parent pointers of cloned children point to clone parent, not original
TEST_F(CloneOffspringTest_1900, ParentPointers_PointToCloneParent_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* child1 = new XMP_Node(&origParent, "c1", "v1", 0);
    XMP_Node* child2 = new XMP_Node(&origParent, "c2", "v2", 0);
    origParent.children.push_back(child1);
    origParent.children.push_back(child2);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), 2u);
    EXPECT_EQ(cloneParent.children[0]->parent, &cloneParent);
    EXPECT_EQ(cloneParent.children[1]->parent, &cloneParent);
    // Ensure they don't point to the original parent
    EXPECT_NE(cloneParent.children[0]->parent, &origParent);
    EXPECT_NE(cloneParent.children[1]->parent, &origParent);

    // Cleanup
    delete child1;
    delete child2;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Cloning does not modify the original
TEST_F(CloneOffspringTest_1900, OriginalIsNotModified_1900) {
    XMP_Node origParent(nullptr, "origParent", "origVal", 0);
    XMP_Node* child = new XMP_Node(&origParent, "child1", "cv1", 7);
    XMP_Node* qual = new XMP_Node(&origParent, "qual1", "qv1", 8);
    origParent.children.push_back(child);
    origParent.qualifiers.push_back(qual);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    // Verify original is untouched
    EXPECT_EQ(origParent.children.size(), 1u);
    EXPECT_EQ(origParent.qualifiers.size(), 1u);
    EXPECT_EQ(origParent.children[0]->name, "child1");
    EXPECT_EQ(origParent.children[0]->value, "cv1");
    EXPECT_EQ(origParent.qualifiers[0]->name, "qual1");
    EXPECT_EQ(origParent.qualifiers[0]->value, "qv1");

    // Cleanup
    delete child;
    delete qual;
    for (auto* c : cloneParent.children) delete c;
    for (auto* q : cloneParent.qualifiers) delete q;
}

// Test: Large number of children
TEST_F(CloneOffspringTest_1900, LargeNumberOfChildren_AllCloned_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    const int numChildren = 100;
    std::vector<XMP_Node*> origChildren;
    for (int i = 0; i < numChildren; ++i) {
        std::string name = "child_" + std::to_string(i);
        std::string value = "value_" + std::to_string(i);
        XMP_Node* child = new XMP_Node(&origParent, name.c_str(), value.c_str(), static_cast<XMP_OptionBits>(i));
        origParent.children.push_back(child);
        origChildren.push_back(child);
    }

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.children.size(), static_cast<size_t>(numChildren));
    for (int i = 0; i < numChildren; ++i) {
        std::string expectedName = "child_" + std::to_string(i);
        std::string expectedValue = "value_" + std::to_string(i);
        EXPECT_EQ(cloneParent.children[i]->name, expectedName);
        EXPECT_EQ(cloneParent.children[i]->value, expectedValue);
        EXPECT_EQ(cloneParent.children[i]->options, static_cast<XMP_OptionBits>(i));
    }

    // Cleanup
    for (auto* c : origChildren) delete c;
    for (auto* c : cloneParent.children) delete c;
}

// Test: Qualifier with its own qualifiers (recursive qualifier cloning)
TEST_F(CloneOffspringTest_1900, QualifierWithQualifiers_ClonedRecursively_1900) {
    XMP_Node origParent(nullptr, "origParent", "", 0);
    XMP_Node* qual = new XMP_Node(&origParent, "qual1", "qv1", 10);
    XMP_Node* subQual = new XMP_Node(qual, "subQual1", "sqv1", 20);
    qual->qualifiers.push_back(subQual);
    origParent.qualifiers.push_back(qual);

    XMP_Node cloneParent(nullptr, "cloneParent", "", 0);

    CloneOffspring(&origParent, &cloneParent);

    ASSERT_EQ(cloneParent.qualifiers.size(), 1u);
    ASSERT_EQ(cloneParent.qualifiers[0]->qualifiers.size(), 1u);
    EXPECT_EQ(cloneParent.qualifiers[0]->qualifiers[0]->name, "subQual1");
    EXPECT_EQ(cloneParent.qualifiers[0]->qualifiers[0]->value, "sqv1");
    EXPECT_EQ(cloneParent.qualifiers[0]->qualifiers[0]->options, 20u);
    EXPECT_EQ(cloneParent.qualifiers[0]->qualifiers[0]->parent, cloneParent.qualifiers[0]);

    // Cleanup
    delete subQual;
    delete qual;
    for (auto* sq : cloneParent.qualifiers[0]->qualifiers) delete sq;
    for (auto* q : cloneParent.qualifiers) delete q;
}
