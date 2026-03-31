#include <gtest/gtest.h>
#include <QString>
#include <QSet>
#include <QList>

// Include the necessary headers
#include "poppler-optcontent-private.h"

namespace Poppler {

class OptContentItemTest_1271 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates a valid object
TEST_F(OptContentItemTest_1271, DefaultConstructor_1271) {
    OptContentItem item;
    // Default constructed item should have no parent
    EXPECT_EQ(item.parent(), nullptr);
    // Default constructed item should be enabled
    EXPECT_TRUE(item.isEnabled());
    // Default constructed item should have no group
    EXPECT_EQ(item.group(), nullptr);
}

// Test constructor with QString label
TEST_F(OptContentItemTest_1271, LabelConstructor_1271) {
    QString label = "TestLabel";
    OptContentItem item(label);
    EXPECT_EQ(item.name(), label);
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(item.group(), nullptr);
}

// Test addChild sets parent-child relationship
TEST_F(OptContentItemTest_1271, AddChildSetsParent_1271) {
    OptContentItem parent;
    OptContentItem child;

    parent.addChild(&child);

    EXPECT_EQ(child.parent(), &parent);
}

// Test addChild adds to child list
TEST_F(OptContentItemTest_1271, AddChildAppearsInChildList_1271) {
    OptContentItem parent;
    OptContentItem child;

    parent.addChild(&child);

    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 1);
    EXPECT_EQ(children.at(0), &child);
}

// Test adding multiple children
TEST_F(OptContentItemTest_1271, AddMultipleChildren_1271) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    OptContentItem child3;

    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);

    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 3);
    EXPECT_EQ(children.at(0), &child1);
    EXPECT_EQ(children.at(1), &child2);
    EXPECT_EQ(children.at(2), &child3);
}

// Test setParent
TEST_F(OptContentItemTest_1271, SetParent_1271) {
    OptContentItem parent;
    OptContentItem child;

    child.setParent(&parent);

    EXPECT_EQ(child.parent(), &parent);
}

// Test setParent to nullptr
TEST_F(OptContentItemTest_1271, SetParentToNull_1271) {
    OptContentItem parent;
    OptContentItem child;

    child.setParent(&parent);
    EXPECT_EQ(child.parent(), &parent);

    child.setParent(nullptr);
    EXPECT_EQ(child.parent(), nullptr);
}

// Test childList returns empty list for item with no children
TEST_F(OptContentItemTest_1271, EmptyChildList_1271) {
    OptContentItem item;
    QList<OptContentItem *> children = item.childList();
    EXPECT_TRUE(children.isEmpty());
}

// Test parent returns nullptr for root item
TEST_F(OptContentItemTest_1271, ParentOfRootIsNull_1271) {
    OptContentItem root;
    EXPECT_EQ(root.parent(), nullptr);
}

// Test isEnabled returns true by default
TEST_F(OptContentItemTest_1271, IsEnabledByDefault_1271) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

// Test name for label constructor
TEST_F(OptContentItemTest_1271, NameReturnsLabel_1271) {
    QString label = "MyOptionalContent";
    OptContentItem item(label);
    EXPECT_EQ(item.name(), label);
}

// Test name with empty string label
TEST_F(OptContentItemTest_1271, NameWithEmptyLabel_1271) {
    QString label = "";
    OptContentItem item(label);
    EXPECT_EQ(item.name(), label);
}

// Test recurseListChildren with includeMe = true on a leaf node
TEST_F(OptContentItemTest_1271, RecurseListChildrenIncludeMeLeaf_1271) {
    OptContentItem item;
    QSet<OptContentItem *> result = item.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&item));
    EXPECT_EQ(result.size(), 1);
}

// Test recurseListChildren with includeMe = false on a leaf node
TEST_F(OptContentItemTest_1271, RecurseListChildrenExcludeMeLeaf_1271) {
    OptContentItem item;
    QSet<OptContentItem *> result = item.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());
}

// Test recurseListChildren with children and includeMe = true
TEST_F(OptContentItemTest_1271, RecurseListChildrenWithChildren_1271) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;

    parent.addChild(&child1);
    parent.addChild(&child2);

    QSet<OptContentItem *> result = parent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
    EXPECT_EQ(result.size(), 3);
}

// Test recurseListChildren with children and includeMe = false
TEST_F(OptContentItemTest_1271, RecurseListChildrenWithChildrenExcludeMe_1271) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;

    parent.addChild(&child1);
    parent.addChild(&child2);

    QSet<OptContentItem *> result = parent.recurseListChildren(false);
    EXPECT_FALSE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
    EXPECT_EQ(result.size(), 2);
}

// Test recurseListChildren with nested children
TEST_F(OptContentItemTest_1271, RecurseListChildrenNested_1271) {
    OptContentItem root;
    OptContentItem child;
    OptContentItem grandchild;

    root.addChild(&child);
    child.addChild(&grandchild);

    QSet<OptContentItem *> result = root.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&root));
    EXPECT_TRUE(result.contains(&child));
    EXPECT_TRUE(result.contains(&grandchild));
    EXPECT_EQ(result.size(), 3);
}

// Test deeply nested tree structure
TEST_F(OptContentItemTest_1271, DeeplyNestedAddChild_1271) {
    OptContentItem level0;
    OptContentItem level1;
    OptContentItem level2;
    OptContentItem level3;

    level0.addChild(&level1);
    level1.addChild(&level2);
    level2.addChild(&level3);

    EXPECT_EQ(level3.parent(), &level2);
    EXPECT_EQ(level2.parent(), &level1);
    EXPECT_EQ(level1.parent(), &level0);
    EXPECT_EQ(level0.parent(), nullptr);
}

// Test group returns nullptr for default constructed item
TEST_F(OptContentItemTest_1271, GroupIsNullForDefaultItem_1271) {
    OptContentItem item;
    EXPECT_EQ(item.group(), nullptr);
}

// Test group returns nullptr for label constructed item
TEST_F(OptContentItemTest_1271, GroupIsNullForLabelItem_1271) {
    QString label = "Test";
    OptContentItem item(label);
    EXPECT_EQ(item.group(), nullptr);
}

} // namespace Poppler
