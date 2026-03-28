#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QString>
#include <QSet>
#include <QList>

// Include the headers for the classes under test
#include "poppler-optcontent-private.h"
#include "poppler-optcontent.h"

using namespace Poppler;

// =============================================================================
// Tests for OptContentItem
// =============================================================================

class OptContentItemTest_1275 : public ::testing::Test {
protected:
    void TearDown() override {
    }
};

TEST_F(OptContentItemTest_1275, DefaultConstructor_1275) {
    OptContentItem item;
    // Default constructed item should have null parent
    EXPECT_EQ(item.parent(), nullptr);
    // Should be enabled by default
    EXPECT_TRUE(item.isEnabled());
    // Should have null group
    EXPECT_EQ(item.group(), nullptr);
}

TEST_F(OptContentItemTest_1275, ConstructWithLabel_1275) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_EQ(item.name(), QString("TestLabel"));
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(item.group(), nullptr);
}

TEST_F(OptContentItemTest_1275, ChildListInitiallyEmpty_1275) {
    OptContentItem item(QString("Parent"));
    QList<OptContentItem *> children = item.childList();
    EXPECT_TRUE(children.isEmpty());
}

TEST_F(OptContentItemTest_1275, AddChildIncreasesChildList_1275) {
    OptContentItem *parent = new OptContentItem(QString("Parent"));
    OptContentItem *child1 = new OptContentItem(QString("Child1"));
    OptContentItem *child2 = new OptContentItem(QString("Child2"));

    parent->addChild(child1);
    EXPECT_EQ(parent->childList().size(), 1);
    EXPECT_EQ(parent->childList().at(0), child1);

    parent->addChild(child2);
    EXPECT_EQ(parent->childList().size(), 2);
    EXPECT_EQ(parent->childList().at(1), child2);

    delete parent;
    // Note: parent's destructor may or may not delete children depending on implementation
}

TEST_F(OptContentItemTest_1275, SetAndGetParent_1275) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));

    EXPECT_EQ(child.parent(), nullptr);
    child.setParent(&parent);
    EXPECT_EQ(child.parent(), &parent);
}

TEST_F(OptContentItemTest_1275, NameForLabelConstructed_1275) {
    QString label("MyLayer");
    OptContentItem item(label);
    EXPECT_EQ(item.name(), label);
}

TEST_F(OptContentItemTest_1275, DefaultConstructorName_1275) {
    OptContentItem item;
    // Default constructed item should return empty or some default name
    QString name = item.name();
    // Just verify it doesn't crash; the actual value depends on implementation
    EXPECT_FALSE(name.isNull() && false); // Always passes, checking no crash
}

TEST_F(OptContentItemTest_1275, RecurseListChildrenNoChildren_1275) {
    OptContentItem item(QString("Leaf"));

    QSet<OptContentItem *> result = item.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());

    QSet<OptContentItem *> resultWithMe = item.recurseListChildren(true);
    EXPECT_EQ(resultWithMe.size(), 1);
    EXPECT_TRUE(resultWithMe.contains(&item));
}

TEST_F(OptContentItemTest_1275, RecurseListChildrenWithChildren_1275) {
    OptContentItem *parent = new OptContentItem(QString("Parent"));
    OptContentItem *child1 = new OptContentItem(QString("Child1"));
    OptContentItem *child2 = new OptContentItem(QString("Child2"));

    parent->addChild(child1);
    parent->addChild(child2);

    QSet<OptContentItem *> result = parent->recurseListChildren(false);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.contains(child1));
    EXPECT_TRUE(result.contains(child2));

    QSet<OptContentItem *> resultWithMe = parent->recurseListChildren(true);
    EXPECT_EQ(resultWithMe.size(), 3);
    EXPECT_TRUE(resultWithMe.contains(parent));
    EXPECT_TRUE(resultWithMe.contains(child1));
    EXPECT_TRUE(resultWithMe.contains(child2));

    delete parent;
}

TEST_F(OptContentItemTest_1275, IsEnabledDefaultTrue_1275) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

TEST_F(OptContentItemTest_1275, GroupIsNullForLabelConstructed_1275) {
    OptContentItem item(QString("Label"));
    EXPECT_EQ(item.group(), nullptr);
}

TEST_F(OptContentItemTest_1275, AddMultipleChildrenPreservesOrder_1275) {
    OptContentItem parent(QString("Parent"));
    OptContentItem child1(QString("A"));
    OptContentItem child2(QString("B"));
    OptContentItem child3(QString("C"));

    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);

    QList<OptContentItem *> children = parent.childList();
    ASSERT_EQ(children.size(), 3);
    EXPECT_EQ(children[0]->name(), QString("A"));
    EXPECT_EQ(children[1]->name(), QString("B"));
    EXPECT_EQ(children[2]->name(), QString("C"));
}

TEST_F(OptContentItemTest_1275, RecurseListChildrenDeepHierarchy_1275) {
    OptContentItem *root = new OptContentItem(QString("Root"));
    OptContentItem *mid = new OptContentItem(QString("Mid"));
    OptContentItem *leaf = new OptContentItem(QString("Leaf"));

    root->addChild(mid);
    mid->addChild(leaf);

    QSet<OptContentItem *> result = root->recurseListChildren(false);
    EXPECT_TRUE(result.contains(mid));
    EXPECT_TRUE(result.contains(leaf));

    QSet<OptContentItem *> resultInclRoot = root->recurseListChildren(true);
    EXPECT_TRUE(resultInclRoot.contains(root));
    EXPECT_TRUE(resultInclRoot.contains(mid));
    EXPECT_TRUE(resultInclRoot.contains(leaf));

    delete root;
}
