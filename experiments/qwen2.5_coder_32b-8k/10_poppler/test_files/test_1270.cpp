#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;

using ::testing::Return;

using ::testing::_;



class OptContentItemTest : public ::testing::Test {

protected:

    void SetUp() override {

        groupMock = new OptionalContentGroup();

        parentMock = new OptContentItem(groupMock);

        itemUnderTest = new OptContentItem(groupMock);

        childMock1 = new OptContentItem();

        childMock2 = new OptContentItem();



        itemUnderTest->setParent(parentMock);

        itemUnderTest->addChild(childMock1);

        itemUnderTest->addChild(childMock2);



        rbGroupMock = new RadioButtonGroup();

        itemUnderTest->appendRBGroup(rbGroupMock);

    }



    void TearDown() override {

        delete itemUnderTest;

        delete parentMock;

        delete childMock1;

        delete childMock2;

        delete groupMock;

        delete rbGroupMock;

    }



    OptContentItem* itemUnderTest;

    OptionalContentGroup* groupMock;

    OptContentItem* parentMock;

    OptContentItem* childMock1;

    OptContentItem* childMock2;

    RadioButtonGroup* rbGroupMock;

};



TEST_F(OptContentItemTest_1270, SetStateChangesState_1270) {

    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::On, true, changedItems);

    EXPECT_EQ(itemUnderTest->state(), ItemState::On);

}



TEST_F(OptContentItemTest_1270, SetStateAddsToChangedItems_1270) {

    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::On, true, changedItems);

    EXPECT_TRUE(changedItems.contains(itemUnderTest));

}



TEST_F(OptContentItemTest_1270, SetSameStateDoesNotChange_1270) {

    itemUnderTest->setState(ItemState::On, true, QSet<OptContentItem*>());

    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::On, true, changedItems);

    EXPECT_TRUE(changedItems.isEmpty());

}



TEST_F(OptContentItemTest_1270, SetStateUpdatesChildrenStates_1270) {

    EXPECT_CALL(*childMock1, setState(ItemState::Off, true, _));

    EXPECT_CALL(*childMock2, setState(ItemState::Off, true, _));



    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::Off, true, changedItems);

}



TEST_F(OptContentItemTest_1270, SetStateCallsGroupSetStateOn_1270) {

    EXPECT_CALL(*groupMock, setState(OptionalContentGroup::On));



    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::On, true, changedItems);

}



TEST_F(OptContentItemTest_1270, SetStateCallsGroupSetStateOff_1270) {

    EXPECT_CALL(*groupMock, setState(OptionalContentGroup::Off));



    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::Off, true, changedItems);

}



TEST_F(OptContentItemTest_1270, SetStateCallsRadioGroupsOn_1270) {

    EXPECT_CALL(*rbGroupMock, setItemOn(itemUnderTest)).WillOnce(Return(QSet<OptContentItem*>()));



    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::On, true, changedItems);

}



TEST_F(OptContentItemTest_1270, SetStateCallsRadioGroupsOff_1270) {

    EXPECT_CALL(*rbGroupMock, setItemOn(_)).Times(0);



    QSet<OptContentItem*> changedItems;

    itemUnderTest->setState(ItemState::Off, true, changedItems);

}
