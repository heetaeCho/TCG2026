#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QSet>
#include <QString>

namespace Poppler {
    class OptContentItem;
    class ItemState;
    class OptionalContentGroup;
    class RadioButtonGroup;
}

// Mock classes
class MockOptionalContentGroup : public Poppler::OptionalContentGroup {};
class MockRadioButtonGroup : public Poppler::RadioButtonGroup {};

class OptContentItemTest_1267 : public ::testing::Test {
protected:
    Poppler::OptContentItem* item;

    void SetUp() override {
        item = new Poppler::OptContentItem();
    }

    void TearDown() override {
        delete item;
    }
};

// Test normal operation of OptContentItem::isEnabled
TEST_F(OptContentItemTest_1267, IsEnabled_ReturnsTrueByDefault_1267) {
    EXPECT_TRUE(item->isEnabled());
}

// Test boundary condition: testing constructor with OptionalContentGroup
TEST_F(OptContentItemTest_1267, Constructor_WithOptionalContentGroup_1268) {
    Poppler::OptionalContentGroup* group = new MockOptionalContentGroup();
    Poppler::OptContentItem itemWithGroup(group);
    // Assuming m_enabled defaults to true as indicated in the constructor
    EXPECT_TRUE(itemWithGroup.isEnabled());
}

// Test boundary condition: testing constructor with label
TEST_F(OptContentItemTest_1269, Constructor_WithLabel_1269) {
    QString label = "Test Label";
    Poppler::OptContentItem itemWithLabel(label);
    EXPECT_TRUE(itemWithLabel.isEnabled()); // Check if item is enabled by default
}

// Test exceptional case: testing the state of an item after setting it
TEST_F(OptContentItemTest_1267, SetState_UpdatesStateCorrectly_1270) {
    Poppler::ItemState newState;
    int changedItems = 0;
    bool obeyRadioGroups = true;
    item->setState(newState, obeyRadioGroups, changedItems);

    // Assuming state update logic is tested here (observable through effects)
    EXPECT_EQ(changedItems, 1); // Expect at least one item to have changed
}

// Test exceptional case: testing adding a child to the OptContentItem
TEST_F(OptContentItemTest_1267, AddChild_SuccessfullyAddsChild_1271) {
    Poppler::OptContentItem* child = new Poppler::OptContentItem();
    item->addChild(child);
    auto children = item->childList();
    EXPECT_EQ(children.size(), 1); // Expect one child
    EXPECT_EQ(children.first(), child); // Ensure the child is added correctly
}

// Test boundary condition: testing appendRBGroup behavior
TEST_F(OptContentItemTest_1267, AppendRBGroup_SuccessfullyAppends_1272) {
    MockRadioButtonGroup* rbGroup = new MockRadioButtonGroup();
    item->appendRBGroup(rbGroup);

    // Assuming appendRBGroup modifies internal state or interacts with rbGroups
    // Since we cannot access internal state directly, we verify interaction through mock
    EXPECT_CALL(*rbGroup, someMockedMethod()) // Assuming some method to verify call
        .Times(1);
}

// Test boundary condition: testing recursion of children
TEST_F(OptContentItemTest_1267, RecurseListChildren_ReturnsCorrectCount_1273) {
    Poppler::OptContentItem* child = new Poppler::OptContentItem();
    item->addChild(child);

    QSet<Poppler::OptContentItem*> children = item->recurseListChildren(true);
    EXPECT_EQ(children.size(), 2); // Includes the parent and the added child
}

// Test exceptional case: testing setting parent of an item
TEST_F(OptContentItemTest_1267, SetParent_SuccessfullySetsParent_1274) {
    Poppler::OptContentItem* parent = new Poppler::OptContentItem();
    item->setParent(parent);

    EXPECT_EQ(item->parent(), parent); // Ensure the parent is set correctly
}

// Test boundary condition: test state retrieval
TEST_F(OptContentItemTest_1267, State_ReturnsCorrectState_1275) {
    Poppler::ItemState state = item->state();
    // Assuming state should be an initial state object (mocked or predefined)
    EXPECT_EQ(state, Poppler::ItemState());
}