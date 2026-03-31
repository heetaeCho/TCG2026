#include <gtest/gtest.h>
#include <QSet>
#include <QString>
#include <QList>

// Include the header that declares OptContentItem
#include "poppler-optcontent-private.h"

namespace Poppler {

class OptContentItemTest_1272 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto item : allocatedItems) {
            delete item;
        }
        allocatedItems.clear();
    }

    OptContentItem* createItem() {
        auto* item = new OptContentItem();
        allocatedItems.push_back(item);
        return item;
    }

    OptContentItem* createItem(const QString& label) {
        auto* item = new OptContentItem(label);
        allocatedItems.push_back(item);
        return item;
    }

    std::vector<OptContentItem*> allocatedItems;
};

// Test default constructor creates a valid item
TEST_F(OptContentItemTest_1272, DefaultConstructor_1272) {
    OptContentItem* item = createItem();
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(item->parent(), nullptr);
    EXPECT_TRUE(item->isEnabled());
}

// Test constructor with label
TEST_F(OptContentItemTest_1272, LabelConstructor_1272) {
    OptContentItem* item = createItem(QString("TestLabel"));
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(item->name(), QString("TestLabel"));
}

// Test recurseListChildren with includeMe=true on a leaf node
TEST_F(OptContentItemTest_1272, RecurseListChildrenIncludeMeLeaf_1272) {
    OptContentItem* item = createItem();
    QSet<OptContentItem*> result = item->recurseListChildren(true);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.contains(item));
}

// Test recurseListChildren with includeMe=false on a leaf node
TEST_F(OptContentItemTest_1272, RecurseListChildrenExcludeMeLeaf_1272) {
    OptContentItem* item = createItem();
    QSet<OptContentItem*> result = item->recurseListChildren(false);
    EXPECT_EQ(result.size(), 0);
}

// Test recurseListChildren with one child, includeMe=true
TEST_F(OptContentItemTest_1272, RecurseListChildrenOneChildIncludeMe_1272) {
    OptContentItem* parent = createItem();
    OptContentItem* child = createItem();
    parent->addChild(child);

    QSet<OptContentItem*> result = parent->recurseListChildren(true);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains(parent));
    EXPECT_TRUE(result.contains(child));
}

// Test recurseListChildren with one child, includeMe=false
TEST_F(OptContentItemTest_1272, RecurseListChildrenOneChildExcludeMe_1272) {
    OptContentItem* parent = createItem();
    OptContentItem* child = createItem();
    parent->addChild(child);

    QSet<OptContentItem*> result = parent->recurseListChildren(false);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.contains(child));
}

// Test recurseListChildren with multiple levels of children
TEST_F(OptContentItemTest_1272, RecurseListChildrenDeepHierarchy_1272) {
    OptContentItem* root = createItem();
    OptContentItem* child1 = createItem();
    OptContentItem* child2 = createItem();
    OptContentItem* grandchild1 = createItem();

    root->addChild(child1);
    root->addChild(child2);
    child1->addChild(grandchild1);

    QSet<OptContentItem*> result = root->recurseListChildren(true);
    EXPECT_EQ(result.size(), 4);
    EXPECT_TRUE(result.contains(root));
    EXPECT_TRUE(result.contains(child1));
    EXPECT_TRUE(result.contains(child2));
    EXPECT_TRUE(result.contains(grandchild1));
}

// Test recurseListChildren with deep hierarchy, excludeMe
TEST_F(OptContentItemTest_1272, RecurseListChildrenDeepHierarchyExcludeMe_1272) {
    OptContentItem* root = createItem();
    OptContentItem* child1 = createItem();
    OptContentItem* child2 = createItem();
    OptContentItem* grandchild1 = createItem();

    root->addChild(child1);
    root->addChild(child2);
    child1->addChild(grandchild1);

    QSet<OptContentItem*> result = root->recurseListChildren(false);
    EXPECT_EQ(result.size(), 3);
    EXPECT_FALSE(result.contains(root));
    EXPECT_TRUE(result.contains(child1));
    EXPECT_TRUE(result.contains(child2));
    EXPECT_TRUE(result.contains(grandchild1));
}

// Test addChild and childList
TEST_F(OptContentItemTest_1272, AddChildAndChildList_1272) {
    OptContentItem* parent = createItem();
    OptContentItem* child1 = createItem();
    OptContentItem* child2 = createItem();

    parent->addChild(child1);
    parent->addChild(child2);

    QList<OptContentItem*> children = parent->childList();
    EXPECT_EQ(children.size(), 2);
    EXPECT_TRUE(children.contains(child1));
    EXPECT_TRUE(children.contains(child2));
}

// Test setParent and parent
TEST_F(OptContentItemTest_1272, SetParentAndParent_1272) {
    OptContentItem* parent = createItem();
    OptContentItem* child = createItem();

    EXPECT_EQ(child->parent(), nullptr);
    child->setParent(parent);
    EXPECT_EQ(child->parent(), parent);
}

// Test isEnabled returns true by default
TEST_F(OptContentItemTest_1272, IsEnabledDefault_1272) {
    OptContentItem* item = createItem();
    EXPECT_TRUE(item->isEnabled());
}

// Test group returns nullptr for default-constructed item
TEST_F(OptContentItemTest_1272, GroupNullForDefaultItem_1272) {
    OptContentItem* item = createItem();
    EXPECT_EQ(item->group(), nullptr);
}

// Test name for label-constructed item
TEST_F(OptContentItemTest_1272, NameForLabelItem_1272) {
    OptContentItem* item = createItem(QString("MyLayer"));
    EXPECT_EQ(item->name(), QString("MyLayer"));
}

// Test childList is empty for new item
TEST_F(OptContentItemTest_1272, ChildListEmptyInitially_1272) {
    OptContentItem* item = createItem();
    QList<OptContentItem*> children = item->childList();
    EXPECT_EQ(children.size(), 0);
}

// Test recurseListChildren from a middle node
TEST_F(OptContentItemTest_1272, RecurseListChildrenFromMiddleNode_1272) {
    OptContentItem* root = createItem();
    OptContentItem* mid = createItem();
    OptContentItem* leaf = createItem();

    root->addChild(mid);
    mid->addChild(leaf);

    QSet<OptContentItem*> result = mid->recurseListChildren(true);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains(mid));
    EXPECT_TRUE(result.contains(leaf));
    EXPECT_FALSE(result.contains(root));
}

// Test recurseListChildren with many children (wide tree)
TEST_F(OptContentItemTest_1272, RecurseListChildrenWideTree_1272) {
    OptContentItem* root = createItem();
    const int numChildren = 10;
    for (int i = 0; i < numChildren; ++i) {
        OptContentItem* child = createItem();
        root->addChild(child);
    }

    QSet<OptContentItem*> result = root->recurseListChildren(true);
    EXPECT_EQ(result.size(), numChildren + 1);
}

// Test setState with changedItems tracking
TEST_F(OptContentItemTest_1272, SetStateChangedItems_1272) {
    OptContentItem* item = createItem(QString("StateTest"));
    QSet<OptContentItem*> changedItems;

    // Call setState - we verify it doesn't crash and produces observable results
    item->setState(OptContentItem::On, false, changedItems);
    // The item should be in changed set or state should reflect the change
    // We can check the state
    EXPECT_EQ(item->state(), OptContentItem::On);
}

// Test that recurseListChildren on leaf called from child perspective
TEST_F(OptContentItemTest_1272, RecurseListChildrenLeafIncludeMe_1272) {
    OptContentItem* root = createItem();
    OptContentItem* leaf = createItem();
    root->addChild(leaf);

    QSet<OptContentItem*> result = leaf->recurseListChildren(true);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.contains(leaf));
    EXPECT_FALSE(result.contains(root));
}

// Test empty name for default constructed item
TEST_F(OptContentItemTest_1272, EmptyNameDefaultItem_1272) {
    OptContentItem* item = createItem();
    // Default constructed item should have empty or null name
    QString name = item->name();
    EXPECT_TRUE(name.isEmpty());
}

} // namespace Poppler
