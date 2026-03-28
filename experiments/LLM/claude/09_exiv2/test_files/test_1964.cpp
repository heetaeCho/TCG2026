#include <gtest/gtest.h>
#include <string>
#include <vector>

// Required XMP SDK headers and types
#define UNIX_ENV 1
#include "XMP_Environment.h"
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// Include the source file to access the static function
#include "XMPMeta-Parse.cpp"

class TransplantNamedAliasTest_1964 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up nodes properly - we need to be careful about ownership
    }
};

TEST_F(TransplantNamedAliasTest_1964, BasicTransplant_1964) {
    XMP_Node root(nullptr, "root", 0);
    XMP_Node oldParent(&root, "oldParent", 0);
    XMP_Node newParent(&root, "newParent", 0);

    XMP_Node* child = new XMP_Node(&oldParent, "oldName", 0);
    child->value = "childValue";
    oldParent.children.push_back(child);

    XMP_VarString newName = "newName";
    TransplantNamedAlias(&oldParent, 0, &newParent, newName);

    // Child should be removed from oldParent
    EXPECT_EQ(oldParent.children.size(), 0u);
    // Child should be added to newParent
    ASSERT_EQ(newParent.children.size(), 1u);
    // Child's name should be updated
    EXPECT_EQ(newParent.children[0]->name, "newName");
    // Child's parent should be newParent
    EXPECT_EQ(newParent.children[0]->parent, &newParent);
    // Child's value should be preserved
    EXPECT_EQ(newParent.children[0]->value, "childValue");

    // Cleanup
    delete child;
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantFromMiddle_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    XMP_Node* child0 = new XMP_Node(&oldParent, "child0", 0);
    XMP_Node* child1 = new XMP_Node(&oldParent, "child1", 0);
    XMP_Node* child2 = new XMP_Node(&oldParent, "child2", 0);
    oldParent.children.push_back(child0);
    oldParent.children.push_back(child1);
    oldParent.children.push_back(child2);

    XMP_VarString newName = "transplanted";
    TransplantNamedAlias(&oldParent, 1, &newParent, newName);

    // oldParent should have 2 children remaining
    ASSERT_EQ(oldParent.children.size(), 2u);
    EXPECT_EQ(oldParent.children[0]->name, "child0");
    EXPECT_EQ(oldParent.children[1]->name, "child2");

    // newParent should have the transplanted child
    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->name, "transplanted");
    EXPECT_EQ(newParent.children[0]->parent, &newParent);
    EXPECT_EQ(newParent.children[0], child1);

    delete child0;
    delete child1;
    delete child2;
    oldParent.children.clear();
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantLastChild_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    XMP_Node* child0 = new XMP_Node(&oldParent, "child0", 0);
    XMP_Node* child1 = new XMP_Node(&oldParent, "child1", 0);
    oldParent.children.push_back(child0);
    oldParent.children.push_back(child1);

    XMP_VarString newName = "movedLast";
    TransplantNamedAlias(&oldParent, 1, &newParent, newName);

    ASSERT_EQ(oldParent.children.size(), 1u);
    EXPECT_EQ(oldParent.children[0]->name, "child0");

    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->name, "movedLast");
    EXPECT_EQ(newParent.children[0]->parent, &newParent);

    delete child0;
    delete child1;
    oldParent.children.clear();
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantToParentWithExistingChildren_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    XMP_Node* oldChild = new XMP_Node(&oldParent, "oldChild", 0);
    oldParent.children.push_back(oldChild);

    XMP_Node* existingChild = new XMP_Node(&newParent, "existing", 0);
    newParent.children.push_back(existingChild);

    XMP_VarString newName = "transplanted";
    TransplantNamedAlias(&oldParent, 0, &newParent, newName);

    EXPECT_EQ(oldParent.children.size(), 0u);
    ASSERT_EQ(newParent.children.size(), 2u);
    EXPECT_EQ(newParent.children[0]->name, "existing");
    EXPECT_EQ(newParent.children[1]->name, "transplanted");
    EXPECT_EQ(newParent.children[1]->parent, &newParent);

    delete oldChild;
    delete existingChild;
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantPreservesChildrenOfNode_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    XMP_Node* child = new XMP_Node(&oldParent, "child", 0);
    XMP_Node* grandchild = new XMP_Node(child, "grandchild", 0);
    child->children.push_back(grandchild);
    oldParent.children.push_back(child);

    XMP_VarString newName = "renamed";
    TransplantNamedAlias(&oldParent, 0, &newParent, newName);

    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->name, "renamed");
    ASSERT_EQ(newParent.children[0]->children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->children[0]->name, "grandchild");

    delete grandchild;
    child->children.clear();
    delete child;
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantPreservesOptions_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    XMP_Node* child = new XMP_Node(&oldParent, "child", 0x1234);
    oldParent.children.push_back(child);

    XMP_VarString newName = "renamedChild";
    TransplantNamedAlias(&oldParent, 0, &newParent, newName);

    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->options, static_cast<XMP_OptionBits>(0x1234));

    delete child;
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantSameParent_1964) {
    XMP_Node parent(nullptr, "parent", 0);

    XMP_Node* child0 = new XMP_Node(&parent, "child0", 0);
    XMP_Node* child1 = new XMP_Node(&parent, "child1", 0);
    parent.children.push_back(child0);
    parent.children.push_back(child1);

    XMP_VarString newName = "renamedChild0";
    // Transplant first child back to same parent
    TransplantNamedAlias(&parent, 0, &parent, newName);

    // Should have removed the first, then appended at end
    ASSERT_EQ(parent.children.size(), 2u);
    EXPECT_EQ(parent.children[0]->name, "child1");
    EXPECT_EQ(parent.children[1]->name, "renamedChild0");
    EXPECT_EQ(parent.children[1]->parent, &parent);

    delete child0;
    delete child1;
    parent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantEmptyName_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    XMP_Node* child = new XMP_Node(&oldParent, "child", 0);
    oldParent.children.push_back(child);

    XMP_VarString newName = "";
    TransplantNamedAlias(&oldParent, 0, &newParent, newName);

    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->name, "");
    EXPECT_EQ(newParent.children[0]->parent, &newParent);

    delete child;
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantPreservesValue_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    XMP_Node* child = new XMP_Node(&oldParent, "child", "someValue", 0);
    oldParent.children.push_back(child);

    XMP_VarString newName = "newChild";
    TransplantNamedAlias(&oldParent, 0, &newParent, newName);

    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->value, "someValue");
    EXPECT_EQ(newParent.children[0]->name, "newChild");

    delete child;
    newParent.children.clear();
}

TEST_F(TransplantNamedAliasTest_1964, TransplantFirstOfMany_1964) {
    XMP_Node oldParent(nullptr, "oldParent", 0);
    XMP_Node newParent(nullptr, "newParent", 0);

    std::vector<XMP_Node*> children;
    for (int i = 0; i < 5; i++) {
        XMP_Node* c = new XMP_Node(&oldParent, std::string("child") + std::to_string(i), 0);
        children.push_back(c);
        oldParent.children.push_back(c);
    }

    XMP_VarString newName = "moved";
    TransplantNamedAlias(&oldParent, 0, &newParent, newName);

    ASSERT_EQ(oldParent.children.size(), 4u);
    EXPECT_EQ(oldParent.children[0]->name, "child1");
    EXPECT_EQ(oldParent.children[1]->name, "child2");
    EXPECT_EQ(oldParent.children[2]->name, "child3");
    EXPECT_EQ(oldParent.children[3]->name, "child4");

    ASSERT_EQ(newParent.children.size(), 1u);
    EXPECT_EQ(newParent.children[0]->name, "moved");

    for (auto* c : children) delete c;
    oldParent.children.clear();
    newParent.children.clear();
}
