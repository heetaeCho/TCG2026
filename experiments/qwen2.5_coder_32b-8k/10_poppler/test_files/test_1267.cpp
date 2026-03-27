#include <gtest/gtest.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentItemTest : public ::testing::Test {

protected:

    OptContentItem* item;



    void SetUp() override {

        item = new OptContentItem();

    }



    void TearDown() override {

        delete item;

    }

};



TEST_F(OptContentItemTest_1267, IsEnabled_DefaultState_1267) {

    EXPECT_TRUE(item->isEnabled());

}



TEST_F(OptContentItemTest_1267, SetState_ChangesEnabledStatus_1267) {

    QSet<OptContentItem*> changedItems;

    item->setState(ItemState::Off, true, changedItems);

    EXPECT_FALSE(item->isEnabled());



    item->setState(ItemState::On, true, changedItems);

    EXPECT_TRUE(item->isEnabled());

}



TEST_F(OptContentItemTest_1267, AddChild_IncreasesChildCount_1267) {

    OptContentItem* child = new OptContentItem();

    item->addChild(child);

    EXPECT_EQ(item->childList().size(), 1);



    delete child;

}



TEST_F(OptContentItemTest_1267, RecurseListChildren_WithSelf_1267) {

    int count = item->recurseListChildren(true);

    EXPECT_EQ(count, 1); // Only the root item itself

}



TEST_F(OptContentItemTest_1267, RecurseListChildren_WithoutSelf_1267) {

    int count = item->recurseListChildren(false);

    EXPECT_EQ(count, 0); // No children and not including self

}



TEST_F(OptContentItemTest_1267, SetParent_ChangesParentReference_1267) {

    OptContentItem* parent = new OptContentItem();

    item->setParent(parent);

    EXPECT_EQ(item->parent(), parent);



    delete parent;

}
