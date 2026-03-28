#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;

using ::testing::NiceMock;



class MockOptContentItem : public OptContentItem {

public:

    MOCK_METHOD(void, setState, (ItemState state, bool obeyRadioGroups, QSet<OptContentItem*>& changedItems), (override));

};



class RadioButtonGroupTest_1269 : public ::testing::Test {

protected:

    NiceMock<MockOptContentItem> item1;

    NiceMock<MockOptContentItem> item2;

    NiceMock<MockOptContentItem> item3;

    std::vector<OptContentItem*> itemsInGroup;

    RadioButtonGroup radioButtonGroup;



    RadioButtonGroupTest_1269()

        : radioButtonGroup(nullptr, nullptr) {

        itemsInGroup.push_back(&item1);

        itemsInGroup.push_back(&item2);

        itemsInGroup.push_back(&item3);

        // Assuming a way to inject the items into the group for testing purposes

    }

};



TEST_F(RadioButtonGroupTest_1269, SetItemOnChangesStateOfOthers_1269) {

    QSet<OptContentItem*> changedItems;

    EXPECT_CALL(item1, setState(OptContentItem::Off, false, ::testing::_));

    EXPECT_CALL(item2, setState(OptContentItem::Off, false, ::testing::_));



    radioButtonGroup.setItemOn(&item3);



    // Assuming that item3 is not included in the returned set

}



TEST_F(RadioButtonGroupTest_1269, SetItemOnNoItemsInGroup_1269) {

    RadioButtonGroup emptyRadioButtonGroup(nullptr, nullptr);

    QSet<OptContentItem*> changedItems = emptyRadioButtonGroup.setItemOn(&item1);



    EXPECT_TRUE(changedItems.isEmpty());

}



TEST_F(RadioButtonGroupTest_1269, SetItemOnSingleItemInGroup_1269) {

    RadioButtonGroup singleItemGroup(nullptr, nullptr);

    std::vector<OptContentItem*> singleItem = {&item1};

    // Assuming a way to inject the items into the group for testing purposes

    QSet<OptContentItem*> changedItems = singleItemGroup.setItemOn(&item1);



    EXPECT_TRUE(changedItems.isEmpty());

}



TEST_F(RadioButtonGroupTest_1269, SetItemOnNullPointer_1269) {

    QSet<OptContentItem*> changedItems = radioButtonGroup.setItemOn(nullptr);



    // Assuming that no changes are made when a null pointer is passed

    EXPECT_TRUE(changedItems.isEmpty());

}



TEST_F(RadioButtonGroupTest_1269, SetItemOnSameItemMultipleTimes_1269) {

    QSet<OptContentItem*> changedItemsFirstCall = radioButtonGroup.setItemOn(&item1);

    QSet<OptContentItem*> changedItemsSecondCall = radioButtonGroup.setItemOn(&item1);



    // Assuming that no changes are made when the same item is set on multiple times

    EXPECT_EQ(changedItemsFirstCall, changedItemsSecondCall);

}
