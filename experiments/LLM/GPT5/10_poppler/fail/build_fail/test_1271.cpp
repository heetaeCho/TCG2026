#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-optcontent-private.h"

namespace Poppler {

class OptContentItemTest : public ::testing::Test {
protected:
    // Create the OptContentItem objects needed for the tests
    OptionalContentGroup group;
    OptContentItem item1;
    OptContentItem item2;
    OptContentItem item3;
};

TEST_F(OptContentItemTest, AddChild_NormalOperation_1271) {
    // Test adding a child to an OptContentItem
    item1.addChild(&item2);
    auto children = item1.childList();

    ASSERT_EQ(children.size(), 1);
    EXPECT_EQ(children[0], &item2);
    EXPECT_EQ(item2.parent(), &item1);
}

TEST_F(OptContentItemTest, AddChild_BoundaryCondition_1272) {
    // Test adding a child when the item has no previous children
    OptContentItem item4;
    item3.addChild(&item4);
    auto children = item3.childList();

    ASSERT_EQ(children.size(), 1);
    EXPECT_EQ(children[0], &item4);
    EXPECT_EQ(item4.parent(), &item3);
}

TEST_F(OptContentItemTest, AddChild_NullChild_1273) {
    // Test adding a null child (expecting no changes)
    item1.addChild(nullptr);
    auto children = item1.childList();

    ASSERT_EQ(children.size(), 0);
}

TEST_F(OptContentItemTest, SetState_NormalOperation_1274) {
    // Test setting the state of an OptContentItem
    ItemState newState;
    QSet<OptContentItem*> changedItems;
    item1.setState(newState, true, changedItems);

    // Verify that state is changed (based on the implementation of setState)
    // For this test case, assume the state is changed
    ASSERT_TRUE(changedItems.contains(&item1));
}

TEST_F(OptContentItemTest, SetParent_NormalOperation_1275) {
    // Test setting a parent for an OptContentItem
    item2.setParent(&item1);
    EXPECT_EQ(item2.parent(), &item1);
}

TEST_F(OptContentItemTest, IsEnabled_NormalOperation_1276) {
    // Test checking the enabled state of an OptContentItem
    EXPECT_TRUE(item1.isEnabled());
}

TEST_F(OptContentItemTest, Group_NormalOperation_1277) {
    // Test retrieving the group of an OptContentItem
    EXPECT_EQ(item1.group(), &group);
}

TEST_F(OptContentItemTest, RecurseListChildren_NormalOperation_1278) {
    // Test recursion to list all children
    item1.addChild(&item2);
    item1.addChild(&item3);
    auto children = item1.recurseListChildren(true);

    EXPECT_EQ(children.size(), 3);  // Including item1 itself
}

TEST_F(OptContentItemTest, AddChild_ExternalInteraction_1279) {
    // Test verifying the call to addChild
    MockOptContentItem mockItem;
    EXPECT_CALL(mockItem, addChild(::testing::_)).Times(1);
    mockItem.addChild(&item1);
}

}  // namespace Poppler