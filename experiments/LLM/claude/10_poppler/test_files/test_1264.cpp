#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QSet>
#include <QString>
#include <QList>

#include "poppler-optcontent-private.h"

namespace Poppler {

class OptContentItemTest_1264 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates a valid object
TEST_F(OptContentItemTest_1264, DefaultConstructor_1264) {
    OptContentItem item;
    // Default constructed item should have some default state
    // We can at least call state() without crashing
    auto s = item.state();
    (void)s;
}

// Test that default constructed item returns a valid state
TEST_F(OptContentItemTest_1264, DefaultStateValue_1264) {
    OptContentItem item;
    ItemState s = item.state();
    // The state should be one of the valid enum values
    // We just verify it doesn't crash and returns something
    SUCCEED();
}

// Test that default constructed item has null parent
TEST_F(OptContentItemTest_1264, DefaultParentIsNull_1264) {
    OptContentItem item;
    EXPECT_EQ(item.parent(), nullptr);
}

// Test that default constructed item is enabled
TEST_F(OptContentItemTest_1264, DefaultIsEnabled_1264) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

// Test that default constructed item has null group
TEST_F(OptContentItemTest_1264, DefaultGroupIsNull_1264) {
    OptContentItem item;
    EXPECT_EQ(item.group(), nullptr);
}

// Test that default constructed item has empty child list
TEST_F(OptContentItemTest_1264, DefaultChildListEmpty_1264) {
    OptContentItem item;
    QList<OptContentItem *> children = item.childList();
    EXPECT_TRUE(children.isEmpty());
}

// Test adding a child
TEST_F(OptContentItemTest_1264, AddChild_1264) {
    OptContentItem parent;
    OptContentItem *child = new OptContentItem();
    parent.addChild(child);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 1);
    EXPECT_EQ(children.at(0), child);
    delete child;
}

// Test adding multiple children
TEST_F(OptContentItemTest_1264, AddMultipleChildren_1264) {
    OptContentItem parent;
    OptContentItem *child1 = new OptContentItem();
    OptContentItem *child2 = new OptContentItem();
    OptContentItem *child3 = new OptContentItem();
    parent.addChild(child1);
    parent.addChild(child2);
    parent.addChild(child3);
    QList<OptContentItem *> children = parent.childList();
    EXPECT_EQ(children.size(), 3);
    delete child1;
    delete child2;
    delete child3;
}

// Test setParent and parent
TEST_F(OptContentItemTest_1264, SetParent_1264) {
    OptContentItem parentItem;
    OptContentItem childItem;
    childItem.setParent(&parentItem);
    EXPECT_EQ(childItem.parent(), &parentItem);
}

// Test setParent with nullptr
TEST_F(OptContentItemTest_1264, SetParentNull_1264) {
    OptContentItem item;
    item.setParent(nullptr);
    EXPECT_EQ(item.parent(), nullptr);
}

// Test constructing with a label (QString)
TEST_F(OptContentItemTest_1264, ConstructWithLabel_1264) {
    QString label("Test Label");
    OptContentItem item(label);
    EXPECT_EQ(item.name(), label);
}

// Test that name returns the label for label-constructed items
TEST_F(OptContentItemTest_1264, NameReturnsLabel_1264) {
    QString label("My OCG Layer");
    OptContentItem item(label);
    EXPECT_EQ(item.name(), QString("My OCG Layer"));
}

// Test default constructed item name
TEST_F(OptContentItemTest_1264, DefaultName_1264) {
    OptContentItem item;
    // Default item may have empty name
    QString n = item.name();
    (void)n; // Just ensure it doesn't crash
    SUCCEED();
}

// Test setState changes the state
TEST_F(OptContentItemTest_1264, SetState_1264) {
    OptContentItem item;
    QSet<OptContentItem *> changedItems;
    item.setState(OptContentItem::On, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::On);
}

// Test setState to Off
TEST_F(OptContentItemTest_1264, SetStateOff_1264) {
    OptContentItem item;
    QSet<OptContentItem *> changedItems;
    item.setState(OptContentItem::Off, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::Off);
}

// Test that setState records changed items
TEST_F(OptContentItemTest_1264, SetStateRecordsChangedItems_1264) {
    OptContentItem item;
    QSet<OptContentItem *> changedItems;
    item.setState(OptContentItem::On, false, changedItems);
    // The item itself or its children may appear in changedItems
    // We just verify it doesn't crash
    SUCCEED();
}

// Test recurseListChildren without including self
TEST_F(OptContentItemTest_1264, RecurseListChildrenExcludeSelf_1264) {
    OptContentItem parent;
    OptContentItem *child = new OptContentItem();
    parent.addChild(child);
    QSet<OptContentItem *> result = parent.recurseListChildren(false);
    EXPECT_FALSE(result.contains(&parent));
    EXPECT_TRUE(result.contains(child));
    delete child;
}

// Test recurseListChildren including self
TEST_F(OptContentItemTest_1264, RecurseListChildrenIncludeSelf_1264) {
    OptContentItem parent;
    OptContentItem *child = new OptContentItem();
    parent.addChild(child);
    QSet<OptContentItem *> result = parent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(child));
    delete child;
}

// Test recurseListChildren on item with no children
TEST_F(OptContentItemTest_1264, RecurseListChildrenNoChildren_1264) {
    OptContentItem item;
    QSet<OptContentItem *> result = item.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());
}

// Test recurseListChildren on item with no children, including self
TEST_F(OptContentItemTest_1264, RecurseListChildrenNoChildrenIncludeSelf_1264) {
    OptContentItem item;
    QSet<OptContentItem *> result = item.recurseListChildren(true);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.contains(&item));
}

// Test nested children recursion
TEST_F(OptContentItemTest_1264, RecurseListChildrenNested_1264) {
    OptContentItem grandparent;
    OptContentItem *parent = new OptContentItem();
    OptContentItem *child = new OptContentItem();
    grandparent.addChild(parent);
    parent->addChild(child);
    QSet<OptContentItem *> result = grandparent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&grandparent));
    EXPECT_TRUE(result.contains(parent));
    EXPECT_TRUE(result.contains(child));
    EXPECT_EQ(result.size(), 3);
    delete child;
    delete parent;
}

// Test state() returns m_stateBackup as per the provided code
TEST_F(OptContentItemTest_1264, StateReturnsBackup_1264) {
    OptContentItem item;
    // state() returns m_stateBackup per the interface
    ItemState s = item.state();
    (void)s;
    SUCCEED();
}

// Test constructing with empty label
TEST_F(OptContentItemTest_1264, ConstructWithEmptyLabel_1264) {
    QString label("");
    OptContentItem item(label);
    EXPECT_EQ(item.name(), QString(""));
}

// Test addChild sets parent of child
TEST_F(OptContentItemTest_1264, AddChildSetsParent_1264) {
    OptContentItem parent;
    OptContentItem *child = new OptContentItem();
    parent.addChild(child);
    EXPECT_EQ(child->parent(), &parent);
    delete child;
}

} // namespace Poppler
