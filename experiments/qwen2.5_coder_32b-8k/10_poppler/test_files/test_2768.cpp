#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentItemTest_2768 : public ::testing::Test {

protected:

    void SetUp() override {

        item = new OptContentItem("Label");

    }



    void TearDown() override {

        delete item;

    }



    OptContentItem* item;

};



TEST_F(OptContentItemTest_2768, ConstructorInitializesName_2768) {

    EXPECT_EQ(item->name(), "Label");

}



TEST_F(OptContentItemTest_2768, ConstructorInitializesEnabledTrue_2768) {

    EXPECT_TRUE(item->isEnabled());

}



TEST_F(OptContentItemTest_2768, ConstructorInitializesParentNull_2768) {

    EXPECT_EQ(item->parent(), nullptr);

}



TEST_F(OptContentItemTest_2768, ConstructorInitializesStateHeadingOnly_2768) {

    EXPECT_EQ(item->state(), OptContentItem::HeadingOnly);

}



TEST_F(OptContentItemTest_2768, SetParentSetsParentPointer_2768) {

    OptContentItem parentItem("Parent");

    item->setParent(&parentItem);

    EXPECT_EQ(item->parent(), &parentItem);

}



TEST_F(OptContentItemTest_2768, AddChildAddsToChildList_2768) {

    OptContentItem childItem("Child");

    item->addChild(&childItem);

    EXPECT_EQ(item->childList().size(), 1);

    EXPECT_EQ(item->childList().at(0), &childItem);

}



TEST_F(OptContentItemTest_2768, AppendRBGroupAddsToGroups_2768) {

    RadioButtonGroup rbgroup;

    item->appendRBGroup(&rbgroup);

    // Assuming there is a way to check if the group was added, which is not directly exposed in the interface.

    // This test assumes that internal state change can be observed through side effects or other public methods.

}



TEST_F(OptContentItemTest_2768, RecurseListChildrenIncludesSelf_2768) {

    EXPECT_EQ(item->recurseListChildren(true).size(), 1);

}



TEST_F(OptContentItemTest_2768, RecurseListChildrenExcludesSelf_2768) {

    EXPECT_EQ(item->recurseListChildren(false).size(), 0);

}



TEST_F(OptContentItemTest_2768, SetStateChangesState_2768) {

    int changedItems = 0;

    item->setState(OptContentItem::On, true, changedItems);

    EXPECT_EQ(item->state(), OptContentItem::On);

}



TEST_F(OptContentItemTest_2768, SetStateChangedItemsCount_2768) {

    int changedItems = 0;

    item->setState(OptContentItem::On, true, changedItems);

    EXPECT_EQ(changedItems, 1); // Assuming changing state of self is counted as one change.

}



TEST_F(OptContentItemTest_2768, GroupInitiallyNull_2768) {

    EXPECT_EQ(item->group(), nullptr);

}
