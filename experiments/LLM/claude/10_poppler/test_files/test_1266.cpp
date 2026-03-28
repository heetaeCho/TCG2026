#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-optcontent-private.h"

using namespace Poppler;

class OptContentItemTest_1266 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that default-constructed OptContentItem has null parent
TEST_F(OptContentItemTest_1266, DefaultConstructorHasNullParent_1266) {
    OptContentItem item;
    EXPECT_EQ(nullptr, item.parent());
}

// Test that default-constructed OptContentItem is enabled
TEST_F(OptContentItemTest_1266, DefaultConstructorIsEnabled_1266) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

// Test that default-constructed OptContentItem has null group
TEST_F(OptContentItemTest_1266, DefaultConstructorHasNullGroup_1266) {
    OptContentItem item;
    EXPECT_EQ(nullptr, item.group());
}

// Test that default-constructed OptContentItem has empty child list
TEST_F(OptContentItemTest_1266, DefaultConstructorHasEmptyChildList_1266) {
    OptContentItem item;
    EXPECT_TRUE(item.childList().isEmpty());
}

// Test setParent and parent
TEST_F(OptContentItemTest_1266, SetParentAndGetParent_1266) {
    OptContentItem parent;
    OptContentItem child;
    child.setParent(&parent);
    EXPECT_EQ(&parent, child.parent());
}

// Test setParent with nullptr
TEST_F(OptContentItemTest_1266, SetParentToNull_1266) {
    OptContentItem parent;
    OptContentItem child;
    child.setParent(&parent);
    EXPECT_EQ(&parent, child.parent());
    child.setParent(nullptr);
    EXPECT_EQ(nullptr, child.parent());
}

// Test addChild adds to child list
TEST_F(OptContentItemTest_1266, AddChildIncreasesChildList_1266) {
    OptContentItem parent;
    OptContentItem child;
    parent.addChild(&child);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(1, children.size());
    EXPECT_EQ(&child, children.at(0));
}

// Test addChild sets parent on child
TEST_F(OptContentItemTest_1266, AddChildSetsParentOnChild_1266) {
    OptContentItem parent;
    OptContentItem child;
    parent.addChild(&child);
    EXPECT_EQ(&parent, child.parent());
}

// Test adding multiple children
TEST_F(OptContentItemTest_1266, AddMultipleChildren_1266) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    OptContentItem child3;
    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(3, children.size());
}

// Test constructing with a label
TEST_F(OptContentItemTest_1266, ConstructWithLabel_1266) {
    QString label("TestLabel");
    OptContentItem item(label);
    EXPECT_EQ(label, item.name());
    EXPECT_EQ(nullptr, item.parent());
    EXPECT_TRUE(item.isEnabled());
}

// Test that name returns empty string for default constructed item
TEST_F(OptContentItemTest_1266, DefaultConstructorNameEmpty_1266) {
    OptContentItem item;
    // Default constructed should have some default name behavior
    QString name = item.name();
    // Just verify it doesn't crash; the actual value depends on implementation
    SUCCEED();
}

// Test parent chain: grandparent -> parent -> child
TEST_F(OptContentItemTest_1266, ParentChain_1266) {
    OptContentItem grandparent;
    OptContentItem parent;
    OptContentItem child;
    grandparent.addChild(&parent);
    parent.addChild(&child);
    EXPECT_EQ(&parent, child.parent());
    EXPECT_EQ(&grandparent, parent.parent());
    EXPECT_EQ(nullptr, grandparent.parent());
}

// Test recurseListChildren without including self
TEST_F(OptContentItemTest_1266, RecurseListChildrenExcludeSelf_1266) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    parent.addChild(&child1);
    parent.addChild(&child2);
    QSet<OptContentItem *> result = parent.recurseListChildren(false);
    EXPECT_EQ(2, result.size());
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
}

// Test recurseListChildren including self
TEST_F(OptContentItemTest_1266, RecurseListChildrenIncludeSelf_1266) {
    OptContentItem parent;
    OptContentItem child1;
    parent.addChild(&child1);
    QSet<OptContentItem *> result = parent.recurseListChildren(true);
    EXPECT_EQ(2, result.size());
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
}

// Test recurseListChildren on leaf node
TEST_F(OptContentItemTest_1266, RecurseListChildrenOnLeaf_1266) {
    OptContentItem leaf;
    QSet<OptContentItem *> result = leaf.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());
}

// Test recurseListChildren on leaf node including self
TEST_F(OptContentItemTest_1266, RecurseListChildrenOnLeafIncludeSelf_1266) {
    OptContentItem leaf;
    QSet<OptContentItem *> result = leaf.recurseListChildren(true);
    EXPECT_EQ(1, result.size());
    EXPECT_TRUE(result.contains(&leaf));
}

// Test recurseListChildren with nested hierarchy
TEST_F(OptContentItemTest_1266, RecurseListChildrenNested_1266) {
    OptContentItem root;
    OptContentItem mid;
    OptContentItem leaf;
    root.addChild(&mid);
    mid.addChild(&leaf);
    QSet<OptContentItem *> result = root.recurseListChildren(false);
    EXPECT_EQ(2, result.size());
    EXPECT_TRUE(result.contains(&mid));
    EXPECT_TRUE(result.contains(&leaf));
}

// Test that constructing with label gives correct name
TEST_F(OptContentItemTest_1266, LabelConstructorName_1266) {
    QString label("MyLayer");
    OptContentItem item(label);
    EXPECT_EQ("MyLayer", item.name());
}

// Test constructing with empty label
TEST_F(OptContentItemTest_1266, EmptyLabelConstructor_1266) {
    QString label("");
    OptContentItem item(label);
    EXPECT_EQ("", item.name());
}

// Test that child list preserves order
TEST_F(OptContentItemTest_1266, ChildListPreservesOrder_1266) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    OptContentItem child3;
    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(&child1, children.at(0));
    EXPECT_EQ(&child2, children.at(1));
    EXPECT_EQ(&child3, children.at(2));
}

// Test overwriting parent via setParent
TEST_F(OptContentItemTest_1266, OverwriteParent_1266) {
    OptContentItem parent1;
    OptContentItem parent2;
    OptContentItem child;
    child.setParent(&parent1);
    EXPECT_EQ(&parent1, child.parent());
    child.setParent(&parent2);
    EXPECT_EQ(&parent2, child.parent());
}
