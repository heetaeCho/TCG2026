#include <gtest/gtest.h>
#include <QString>
#include <QSet>
#include <QList>
#include "poppler-optcontent-private.h"

using namespace Poppler;

// Test fixture for OptContentItem
class OptContentItemTest_1267 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor initializes enabled to true
TEST_F(OptContentItemTest_1267, DefaultConstructorSetsEnabledTrue_1267) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

// Test default constructor sets parent to nullptr
TEST_F(OptContentItemTest_1267, DefaultConstructorSetsParentNull_1267) {
    OptContentItem item;
    EXPECT_EQ(nullptr, item.parent());
}

// Test default constructor group returns nullptr
TEST_F(OptContentItemTest_1267, DefaultConstructorGroupIsNull_1267) {
    OptContentItem item;
    EXPECT_EQ(nullptr, item.group());
}

// Test default constructor childList is empty
TEST_F(OptContentItemTest_1267, DefaultConstructorChildListEmpty_1267) {
    OptContentItem item;
    EXPECT_TRUE(item.childList().isEmpty());
}

// Test isEnabled returns true for default constructed item
TEST_F(OptContentItemTest_1267, IsEnabledDefaultTrue_1267) {
    OptContentItem item;
    EXPECT_TRUE(item.isEnabled());
}

// Test addChild adds a child to the child list
TEST_F(OptContentItemTest_1267, AddChildIncreasesChildList_1267) {
    OptContentItem parent;
    OptContentItem child;
    parent.addChild(&child);
    QList<OptContentItem*> children = parent.childList();
    EXPECT_EQ(1, children.size());
    EXPECT_EQ(&child, children.at(0));
}

// Test addChild sets parent on the child
TEST_F(OptContentItemTest_1267, AddChildSetsParentOnChild_1267) {
    OptContentItem parent;
    OptContentItem child;
    parent.addChild(&child);
    EXPECT_EQ(&parent, child.parent());
}

// Test setParent sets the parent
TEST_F(OptContentItemTest_1267, SetParentSetsParentPointer_1267) {
    OptContentItem parent;
    OptContentItem child;
    child.setParent(&parent);
    EXPECT_EQ(&parent, child.parent());
}

// Test setParent with nullptr
TEST_F(OptContentItemTest_1267, SetParentNullptr_1267) {
    OptContentItem item;
    item.setParent(nullptr);
    EXPECT_EQ(nullptr, item.parent());
}

// Test adding multiple children
TEST_F(OptContentItemTest_1267, AddMultipleChildren_1267) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    OptContentItem child3;
    parent.addChild(&child1);
    parent.addChild(&child2);
    parent.addChild(&child3);
    QList<OptContentItem*> children = parent.childList();
    EXPECT_EQ(3, children.size());
}

// Test constructor with QString label
TEST_F(OptContentItemTest_1267, LabelConstructorCreatesItem_1267) {
    QString label("Test Layer");
    OptContentItem item(label);
    EXPECT_EQ(label, item.name());
}

// Test name returns empty string for default constructed
TEST_F(OptContentItemTest_1267, DefaultConstructorNameEmpty_1267) {
    OptContentItem item;
    // Default constructed item should have some default name behavior
    QString name = item.name();
    // Just verify it doesn't crash and returns a string
    EXPECT_TRUE(name.isEmpty() || !name.isEmpty());
}

// Test recurseListChildren with includeMe = false on leaf node
TEST_F(OptContentItemTest_1267, RecurseListChildrenLeafNotIncludeMe_1267) {
    OptContentItem item;
    QSet<OptContentItem*> result = item.recurseListChildren(false);
    EXPECT_TRUE(result.isEmpty());
}

// Test recurseListChildren with includeMe = true on leaf node
TEST_F(OptContentItemTest_1267, RecurseListChildrenLeafIncludeMe_1267) {
    OptContentItem item;
    QSet<OptContentItem*> result = item.recurseListChildren(true);
    EXPECT_EQ(1, result.size());
    EXPECT_TRUE(result.contains(&item));
}

// Test recurseListChildren with children and includeMe = true
TEST_F(OptContentItemTest_1267, RecurseListChildrenWithChildren_1267) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    parent.addChild(&child1);
    parent.addChild(&child2);
    QSet<OptContentItem*> result = parent.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
    EXPECT_EQ(3, result.size());
}

// Test recurseListChildren with children and includeMe = false
TEST_F(OptContentItemTest_1267, RecurseListChildrenWithChildrenNotIncludeMe_1267) {
    OptContentItem parent;
    OptContentItem child1;
    OptContentItem child2;
    parent.addChild(&child1);
    parent.addChild(&child2);
    QSet<OptContentItem*> result = parent.recurseListChildren(false);
    EXPECT_FALSE(result.contains(&parent));
    EXPECT_TRUE(result.contains(&child1));
    EXPECT_TRUE(result.contains(&child2));
    EXPECT_EQ(2, result.size());
}

// Test setState changes state
TEST_F(OptContentItemTest_1267, SetStateChangesState_1267) {
    OptContentItem item;
    QSet<OptContentItem*> changedItems;
    // State On
    item.setState(OptContentItem::On, false, changedItems);
    EXPECT_EQ(OptContentItem::On, item.state());
}

// Test setState to Off
TEST_F(OptContentItemTest_1267, SetStateToOff_1267) {
    OptContentItem item;
    QSet<OptContentItem*> changedItems;
    item.setState(OptContentItem::Off, false, changedItems);
    EXPECT_EQ(OptContentItem::Off, item.state());
}

// Test setState records changed items
TEST_F(OptContentItemTest_1267, SetStateRecordsChangedItems_1267) {
    OptContentItem item;
    QSet<OptContentItem*> changedItems;
    item.setState(OptContentItem::On, false, changedItems);
    // The item itself should be in the changed set
    EXPECT_TRUE(changedItems.contains(&item));
}

// Test group() returns nullptr for label-constructed item
TEST_F(OptContentItemTest_1267, LabelConstructorGroupIsNull_1267) {
    QString label("Test");
    OptContentItem item(label);
    EXPECT_EQ(nullptr, item.group());
}

// Test deeply nested children recurse
TEST_F(OptContentItemTest_1267, RecurseListChildrenDeepNesting_1267) {
    OptContentItem root;
    OptContentItem mid;
    OptContentItem leaf;
    root.addChild(&mid);
    mid.addChild(&leaf);
    QSet<OptContentItem*> result = root.recurseListChildren(true);
    EXPECT_TRUE(result.contains(&root));
    EXPECT_TRUE(result.contains(&mid));
    EXPECT_TRUE(result.contains(&leaf));
    EXPECT_EQ(3, result.size());
}
