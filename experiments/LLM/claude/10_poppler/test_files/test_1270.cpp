#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QSet>
#include <QString>

#include "poppler-optcontent-private.h"
#include "poppler-optcontent.h"

// We need to include necessary poppler headers
// Adjust paths as needed for the build system
#include "poppler-qt5.h"

namespace Poppler {

class OptContentItemTest_1270 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes correctly
TEST_F(OptContentItemTest_1270, DefaultConstructor_1270) {
    OptContentItem item;
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(item.group(), nullptr);
}

// Test constructor with QString label
TEST_F(OptContentItemTest_1270, StringConstructor_1270) {
    OptContentItem item(QString("TestLabel"));
    EXPECT_EQ(item.name(), QString("TestLabel"));
    EXPECT_EQ(item.parent(), nullptr);
    EXPECT_TRUE(item.isEnabled());
    EXPECT_EQ(item.group(), nullptr);
}

// Test setParent and parent
TEST_F(OptContentItemTest_1270, SetParentAndParent_1270) {
    OptContentItem parentItem(QString("Parent"));
    OptContentItem childItem(QString("Child"));
    
    EXPECT_EQ(childItem.parent(), nullptr);
    childItem.setParent(&parentItem);
    EXPECT_EQ(childItem.parent(), &parentItem);
}

// Test addChild and childList
TEST_F(OptContentItemTest_1270, AddChildAndChildList_1270) {
    OptContentItem parentItem(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    
    EXPECT_TRUE(parentItem.childList().isEmpty());
    
    parentItem.addChild(&child1);
    EXPECT_EQ(parentItem.childList().size(), 1);
    EXPECT_EQ(parentItem.childList().at(0), &child1);
    
    parentItem.addChild(&child2);
    EXPECT_EQ(parentItem.childList().size(), 2);
}

// Test isEnabled default value
TEST_F(OptContentItemTest_1270, IsEnabledDefault_1270) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

// Test setState with same state (no change expected)
TEST_F(OptContentItemTest_1270, SetStateSameStateNoChange_1270) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> changedItems;
    
    // Get current state
    OptContentItem::ItemState currentState = item.state();
    
    // Set to same state - should not add to changedItems
    item.setState(currentState, false, changedItems);
    EXPECT_TRUE(changedItems.isEmpty());
}

// Test setState changes state and records in changedItems (no group)
TEST_F(OptContentItemTest_1270, SetStateChangesStateNoGroup_1270) {
    OptContentItem item(QString("Test"));
    QSet<OptContentItem *> changedItems;
    
    OptContentItem::ItemState initialState = item.state();
    
    // Try to change to a different state
    OptContentItem::ItemState newState = (initialState == OptContentItem::On) ? OptContentItem::Off : OptContentItem::On;
    item.setState(newState, false, changedItems);
    
    // The item should be in changedItems since state changed
    EXPECT_TRUE(changedItems.contains(&item));
    EXPECT_EQ(item.state(), newState);
}

// Test setState with children - turning off parent disables children
TEST_F(OptContentItemTest_1270, SetStateOffDisablesChildren_1270) {
    OptContentItem parentItem(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    
    parentItem.addChild(&child1);
    parentItem.addChild(&child2);
    
    QSet<OptContentItem *> changedItems;
    
    // First set parent On
    parentItem.setState(OptContentItem::On, false, changedItems);
    changedItems.clear();
    
    // Now set parent Off - children should be disabled
    parentItem.setState(OptContentItem::Off, false, changedItems);
    
    EXPECT_TRUE(changedItems.contains(&parentItem));
    EXPECT_EQ(parentItem.state(), OptContentItem::Off);
    
    // Children should be disabled
    EXPECT_FALSE(child1.isEnabled());
    EXPECT_FALSE(child2.isEnabled());
}

// Test setState with children - turning on parent enables children
TEST_F(OptContentItemTest_1270, SetStateOnEnablesChildren_1270) {
    OptContentItem parentItem(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    
    parentItem.addChild(&child1);
    
    QSet<OptContentItem *> changedItems;
    
    // Set parent On first
    parentItem.setState(OptContentItem::On, false, changedItems);
    changedItems.clear();
    
    // Set parent Off
    parentItem.setState(OptContentItem::Off, false, changedItems);
    EXPECT_FALSE(child1.isEnabled());
    changedItems.clear();
    
    // Set parent On again - children should be re-enabled
    parentItem.setState(OptContentItem::On, false, changedItems);
    EXPECT_TRUE(child1.isEnabled());
}

// Test recurseListChildren without including self
TEST_F(OptContentItemTest_1270, RecurseListChildrenExcludeSelf_1270) {
    OptContentItem parentItem(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    OptContentItem child2(QString("Child2"));
    
    parentItem.addChild(&child1);
    parentItem.addChild(&child2);
    
    QSet<OptContentItem *> children = parentItem.recurseListChildren(false);
    EXPECT_FALSE(children.contains(&parentItem));
    EXPECT_TRUE(children.contains(&child1));
    EXPECT_TRUE(children.contains(&child2));
}

// Test recurseListChildren including self
TEST_F(OptContentItemTest_1270, RecurseListChildrenIncludeSelf_1270) {
    OptContentItem parentItem(QString("Parent"));
    OptContentItem child1(QString("Child1"));
    
    parentItem.addChild(&child1);
    
    QSet<OptContentItem *> children = parentItem.recurseListChildren(true);
    EXPECT_TRUE(children.contains(&parentItem));
    EXPECT_TRUE(children.contains(&child1));
}

// Test recurseListChildren with no children
TEST_F(OptContentItemTest_1270, RecurseListChildrenNoChildren_1270) {
    OptContentItem item(QString("Leaf"));
    
    QSet<OptContentItem *> children = item.recurseListChildren(false);
    EXPECT_TRUE(children.isEmpty());
    
    QSet<OptContentItem *> childrenWithSelf = item.recurseListChildren(true);
    EXPECT_EQ(childrenWithSelf.size(), 1);
    EXPECT_TRUE(childrenWithSelf.contains(&item));
}

// Test recurseListChildren with nested hierarchy
TEST_F(OptContentItemTest_1270, RecurseListChildrenNested_1270) {
    OptContentItem grandparent(QString("Grandparent"));
    OptContentItem parent(QString("Parent"));
    OptContentItem child(QString("Child"));
    
    grandparent.addChild(&parent);
    parent.addChild(&child);
    
    QSet<OptContentItem *> descendants = grandparent.recurseListChildren(false);
    EXPECT_TRUE(descendants.contains(&parent));
    EXPECT_TRUE(descendants.contains(&child));
    EXPECT_FALSE(descendants.contains(&grandparent));
}

// Test name returns correct label
TEST_F(OptContentItemTest_1270, NameReturnsLabel_1270) {
    OptContentItem item(QString("MyLabel"));
    EXPECT_EQ(item.name(), QString("MyLabel"));
}

// Test childList is initially empty
TEST_F(OptContentItemTest_1270, ChildListInitiallyEmpty_1270) {
    OptContentItem item(QString("Test"));
    EXPECT_TRUE(item.childList().isEmpty());
}

// Test group returns nullptr for non-group item
TEST_F(OptContentItemTest_1270, GroupReturnsNullForLabelItem_1270) {
    OptContentItem item(QString("LabelOnly"));
    EXPECT_EQ(item.group(), nullptr);
}

// Test multiple setState calls toggle correctly
TEST_F(OptContentItemTest_1270, SetStateToggle_1270) {
    OptContentItem item(QString("Toggle"));
    QSet<OptContentItem *> changedItems;
    
    item.setState(OptContentItem::On, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::On);
    changedItems.clear();
    
    item.setState(OptContentItem::Off, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::Off);
    EXPECT_TRUE(changedItems.contains(&item));
    changedItems.clear();
    
    item.setState(OptContentItem::On, false, changedItems);
    EXPECT_EQ(item.state(), OptContentItem::On);
    EXPECT_TRUE(changedItems.contains(&item));
}

// Test setState called twice with same state only records once
TEST_F(OptContentItemTest_1270, SetStateIdempotent_1270) {
    OptContentItem item(QString("Idempotent"));
    QSet<OptContentItem *> changedItems;
    
    item.setState(OptContentItem::On, false, changedItems);
    int firstSize = changedItems.size();
    
    // Calling again with same state should not add again
    item.setState(OptContentItem::On, false, changedItems);
    EXPECT_EQ(changedItems.size(), firstSize);
}

} // namespace Poppler
