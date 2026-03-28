#include <gtest/gtest.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentItemTest_1264 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects if necessary

        m_optContentItem = new OptContentItem();

    }



    void TearDown() override {

        delete m_optContentItem;

    }



    OptContentItem* m_optContentItem;

};



TEST_F(OptContentItemTest_1264, DefaultConstructorState_1264) {

    // Test the default state of an OptContentItem created with the default constructor

    EXPECT_EQ(m_optContentItem->state(), ItemState::Unknown); // Assuming Unknown is the default state

}



TEST_F(OptContentItemTest_1264, SetAndGetState_1264) {

    // Test setting and getting the state of an OptContentItem

    int changedItems = 0;

    m_optContentItem->setState(ItemState::On, true, changedItems);

    EXPECT_EQ(m_optContentItem->state(), ItemState::On);



    m_optContentItem->setState(ItemState::Off, false, changedItems);

    EXPECT_EQ(m_optContentItem->state(), ItemState::Off);

}



TEST_F(OptContentItemTest_1264, AddChild_1264) {

    // Test adding a child to an OptContentItem

    OptContentItem* child = new OptContentItem();

    m_optContentItem->addChild(child);



    QList<OptContentItem*> children = m_optContentItem->childList();

    EXPECT_EQ(children.size(), 1);

    EXPECT_EQ(children.first(), child);



    delete child; // Clean up the dynamically allocated child

}



TEST_F(OptContentItemTest_1264, RecurseListChildrenIncludeMe_1264) {

    // Test recurseListChildren with includeMe set to true

    OptContentItem* child = new OptContentItem();

    m_optContentItem->addChild(child);



    int count = m_optContentItem->recurseListChildren(true);

    EXPECT_EQ(count, 2); // One for the parent and one for the child



    delete child; // Clean up the dynamically allocated child

}



TEST_F(OptContentItemTest_1264, RecurseListChildrenExcludeMe_1264) {

    // Test recurseListChildren with includeMe set to false

    OptContentItem* child = new OptContentItem();

    m_optContentItem->addChild(child);



    int count = m_optContentItem->recurseListChildren(false);

    EXPECT_EQ(count, 1); // Only the child



    delete child; // Clean up the dynamically allocated child

}



TEST_F(OptContentItemTest_1264, SetParentAndGetParent_1264) {

    // Test setting and getting the parent of an OptContentItem

    OptContentItem* parent = new OptContentItem();

    m_optContentItem->setParent(parent);



    EXPECT_EQ(m_optContentItem->parent(), parent);



    delete parent; // Clean up the dynamically allocated parent

}



TEST_F(OptContentItemTest_1264, IsEnabledDefault_1264) {

    // Test the default enabled state of an OptContentItem

    EXPECT_TRUE(m_optContentItem->isEnabled());

}



TEST_F(OptContentItemTest_1264, BoundaryConditions_1264) {

    // Test boundary conditions for various functions

    int changedItems = 0;

    m_optContentItem->setState(ItemState::Off, true, changedItems);

    EXPECT_EQ(m_optContentItem->state(), ItemState::Off);



    QList<OptContentItem*> children = m_optContentItem->childList();

    EXPECT_TRUE(children.isEmpty());



    int count = m_optContentItem->recurseListChildren(true);

    EXPECT_EQ(count, 1); // Only the parent itself

}



TEST_F(OptContentItemTest_1264, DestructorNoCrash_1264) {

    // Test that the destructor does not cause a crash when children are added

    OptContentItem* child = new OptContentItem();

    m_optContentItem->addChild(child);



    // No explicit assertion needed; if this line is reached without crashing, the test passes

}



TEST_F(OptContentItemTest_1264, AppendRBGroup_1264) {

    // Test appending a radio button group to an OptContentItem

    RadioButtonGroup* rbgroup = new RadioButtonGroup();

    m_optContentItem->appendRBGroup(rbgroup);



    // No direct way to verify the addition, but this ensures no crash



    delete rbgroup; // Clean up the dynamically allocated radio button group

}
