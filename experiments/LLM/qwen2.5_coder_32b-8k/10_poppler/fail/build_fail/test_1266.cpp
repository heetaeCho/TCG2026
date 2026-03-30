#include <gtest/gtest.h>

#include "poppler-optcontent-private.h"

#include <QString>

#include <QList>

#include <QSet>



using namespace Poppler;



class OptContentItemTest_1266 : public ::testing::Test {

protected:

    OptContentItem* item;

    OptContentItem* childItem;

    OptionalContentGroup* group;

    RadioButtonGroup* rbgroup;

    

    void SetUp() override {

        group = new OptionalContentGroup();

        rbgroup = new RadioButtonGroup();

        item = new OptContentItem(group);

        childItem = new OptContentItem();

    }



    void TearDown() override {

        delete item;

        delete childItem;

        delete group;

        delete rbgroup;

    }

};



TEST_F(OptContentItemTest_1266, ConstructorWithGroup_1266) {

    EXPECT_EQ(item->group(), group);

}



TEST_F(OptContentItemTest_1266, DefaultConstructor_1266) {

    OptContentItem defaultItem;

    EXPECT_EQ(defaultItem.parent(), nullptr);

    EXPECT_TRUE(defaultItem.isEnabled());

}



TEST_F(OptContentItemTest_1266, SetAndGetParent_1266) {

    item->setParent(childItem);

    EXPECT_EQ(item->parent(), childItem);

}



TEST_F(OptContentItemTest_1266, AddAndRecurseListChildren_1266) {

    item->addChild(childItem);

    QSet<OptContentItem*> children = item->recurseListChildren(true);

    EXPECT_EQ(children.size(), 2); // one for the parent and one for the child

}



TEST_F(OptContentItemTest_1266, AppendRBGroup_1266) {

    int initialCount = item->recurseListChildren(false).size();

    item->appendRBGroup(rbgroup);

    int finalCount = item->recurseListChildren(false).size();

    EXPECT_EQ(finalCount - initialCount, 0); // No change in children count

}



TEST_F(OptContentItemTest_1266, SetAndGetState_1266) {

    QSet<OptContentItem*> changedItems;

    item->setState(ItemState::Off, true, changedItems);

    EXPECT_EQ(item->state(), ItemState::Off);

}



TEST_F(OptContentItemTest_1266, IsEnabled_1266) {

    item->setEnabled(false);

    EXPECT_FALSE(item->isEnabled());

}



TEST_F(OptContentItemTest_1266, ChildList_1266) {

    QList<OptContentItem*> initialChildren = item->childList();

    EXPECT_EQ(initialChildren.size(), 0);



    item->addChild(childItem);

    QList<OptContentItem*> finalChildren = item->childList();

    EXPECT_EQ(finalChildren.size(), 1);

}
